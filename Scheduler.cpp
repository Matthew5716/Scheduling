#include "Scheduler.h"
#include <cmath>
#include <iostream>
#include <algorithm>

using std::cout;
using std::min;
using std::sort;
using std::stringstream;
using std::ostringstream;

Scheduler::Scheduler(int timeQuantum, vector<Process>& allProcesses, int nQueues, int ageing) {
    handleIO = false;
    IoOffset = -1;
    quantum = timeQuantum;
    processes = allProcesses;
    processIterator = processes.begin();
    finished = false;
    numQueues = nQueues;
    ageLimit = ageing;
    for(int i = 0; i < nQueues; i++) {
        queues[i].quantum = timeQuantum * pow(2,i);
    }
}


/**
 * Use clcok and process iterator to determine if any processes have arrived,
 * if so add them to the top queue. If no more processes set
 */
bool Scheduler::addArrivedProcesses(int clockTime) {
    while(processIterator->getArrival() == clockTime) {
        // add processes to top queue
        processIterator->setQuantumLeft(queues[0].quantum);
        if (handleIO && processIterator->getIoTimeLeft() > 0) {
            processIterator->setIOOffsetLeft(IoOffset);
        }
        queues[0].queue.push_back(&(*processIterator));
        buffer << "Process " << processIterator->getPid() << " has arrived. \n";
        ++processIterator;
        if(processIterator == processes.end()) {
            return true;
        }
    }
    return false;
}

Process* Scheduler::getTopProcess() {
    for(int i = 0; i < numQueues; i++) {
        if(!queues[i].queue.empty()) {
            return queues[i].queue.front();
        }
    }
    return nullptr;
}

void Scheduler::updateAgeing(vector<Process*>& shiftedProcesses) {
    size_t size = queues[numQueues - 1].queue.size();
    if(size > 0) {
        Process* temp = queues[numQueues -1].queue.front();
        for (size_t i = 0; i < size; i++) {
            temp = queues[numQueues - 1].queue.front();
            queues[numQueues - 1].queue.pop_front();
            temp->incrementAge();
            if (temp->getAgeTime() == ageLimit) {
                temp->setQueueIndex(temp->getQueueIndex() - 1);
                shiftedProcesses.push_back(temp);
            } else {
                queues[numQueues - 1].queue.push_back(temp);
            }
        }
    }
}

void updateIO(queue<Process*>& IOQueue, vector<Process*>& shiftedProcesses, Average& average, int clock, stringstream& buffer) {
    size_t size = IOQueue.size();
    if(size > 0) {
        Process *ioProcess;
        for (size_t i = 0; i < size; i++) {
            ioProcess = IOQueue.front();
            IOQueue.pop();
            if (ioProcess->decrementIoTimeLeft()) {
                if (ioProcess->getBurstLeft() == 0) {
                    buffer << "Process " << ioProcess->getPid() << " finished I/O and has finished running. \n";
                    ioProcess->setCompletionTime(clock);
                    average.addProcessToAverages(*ioProcess);
                } else {
                    ioProcess->setQueueIndex(std::max(ioProcess->getQueueIndex() - 1, 0));
                    shiftedProcesses.push_back(ioProcess);
                    buffer << "Process " << ioProcess->getPid() << " finished I/O \n";
                }
            } else {
                IOQueue.push(ioProcess);
            }
        }
    }
}

void Scheduler::runMFQS() {
    if(processes.size() == 0) {
        cout << "No processes.";
        return;
    }
    clock = 0;
    vector<Process*> shiftedProcesses;
    bool allProcessesHaveArrived;

    Process * runningProcess = nullptr; // process on CPU
    Process * topProcess = nullptr; // front of top queue that's not empty
    bool finishedBurst = false;
    bool finishedQuantum = false;
    bool hitIoOffset = false;
    bool newProcessOnCpu = false;
    buffer.clear();
    while(!finished) {
        buffer << "ClockTick: " << clock << " \n";
        if(!allProcessesHaveArrived) {
            allProcessesHaveArrived = addArrivedProcesses(clock);
        }

        // update state of IO queue to reflect passed clock tick
        if (handleIO) {
            updateIO(IOQueue, shiftedProcesses, average, clock, buffer);
        }
        // update state of ageing and queues to reflect passed clock tick
        updateAgeing(shiftedProcesses);

        // update state of running process to reflect passed clock tick
        if (runningProcess != nullptr) { // if there is a running process
            finishedBurst = runningProcess->decrementBurstLeft();
            finishedQuantum = runningProcess->decrementQuantumLeft();
            if (handleIO && runningProcess->getIOOffsetLeft() > 0) {
                hitIoOffset = runningProcess->decrementIOOffsetLeft();
            }
            if (finishedBurst) { // If process finished
                if (handleIO && runningProcess->getIoTimeLeft() > 0) { // finished bursting but needs to do I/O
                    IOQueue.push(runningProcess);
                } else {
                    runningProcess->setCompletionTime(clock);
                    average.addProcessToAverages(*runningProcess);
                    buffer << "Process " << runningProcess->getPid() << " has finished running at time " << clock
                         << ".\n";
                }
                runningProcess = nullptr;
            } else if (finishedQuantum) { // not finished bursting but finished quantum and maybe I/O offset
                int queueIndex = min(runningProcess->getQueueIndex() + 1,
                                     numQueues - 1); // can't go above last queue
                runningProcess->setQueueIndex(queueIndex);
                buffer << "Process " << runningProcess->getPid() << " has been demoted to queue "
                     << runningProcess->getQueueIndex() << ".\n";

                if(handleIO && hitIoOffset) {
                    IOQueue.push(runningProcess);
                } else {
                    shiftedProcesses.push_back(runningProcess);
                }
                runningProcess = nullptr;
            } else if (handleIO && hitIoOffset) { // only thing it hit was I/O offset
                IOQueue.push(runningProcess);
                runningProcess = nullptr;
            }
        }

        // reinsert all process where they should be before updating cpu
        insertShiftedProcesses(shiftedProcesses);

        // Check for top queue that is not empty, check if queue num is the same as process running
        topProcess = getTopProcess();

        if (topProcess != nullptr && runningProcess != nullptr &&
            topProcess->getQueueIndex() < runningProcess->getQueueIndex()) { // Preempt
            int queueIndex = runningProcess->getQueueIndex();
            if (queueIndex == numQueues - 1) {
                queues[runningProcess->getQueueIndex()].queue.push_front(runningProcess); // last queue FCFS
            } else {
                queues[runningProcess->getQueueIndex()].queue.push_back(runningProcess); // other queues RR
            }
            buffer << *runningProcess << " was preempted by " << *topProcess << "\n" << *topProcess
                 << " is now on cpu. \n";
            newProcessOnCpu = true;
        } else if (topProcess != nullptr && runningProcess == nullptr) { // Nothing ON CPU just put top process on
            newProcessOnCpu = true;
        }

        if (newProcessOnCpu) {
            queues[topProcess->getQueueIndex()].queue.pop_front();
            runningProcess = topProcess;
            runningProcess->setQuantumLeft(queues[runningProcess->getQueueIndex()].quantum);
            topProcess = nullptr;
            buffer << *runningProcess << " has obtained CPU.\n";
            newProcessOnCpu = false;
        } else if(runningProcess != nullptr) {
            buffer << *runningProcess << " is on CPU.\n";
        }


        //Check to see if were finsihed
        if(topProcess == nullptr && runningProcess == nullptr && allProcessesHaveArrived
            && IOQueue.empty() && shiftedProcesses.empty()) { // No processes left in system
                finished = true;
        }

        clock++;

        // reset variables
        finishedQuantum  = false;
        finishedBurst = false;
        hitIoOffset = false;

        cout << buffer.str();
        buffer.clear();
    }
    cout << buffer.str();
    buffer.clear();
    cout << "\n Total Processes Scheduled: " << average.getNumProcesses() << "\nAverage wait time was: " << average.getAverageWaitTime() << "\n"
       << "Average TurnAroundTime was: " << average.getAverageTurnAroundTime() << "\n";
}


bool processPtrCompare(Process* l, Process* r){ // lower prioirty value means higher priority
    return l->getPriority() < r->getPriority();
}

void Scheduler::insertShiftedProcesses(vector<Process*>& shiftedProcesses) {
    if(!shiftedProcesses.empty()) {
        sort(shiftedProcesses.begin(), shiftedProcesses.end(), processPtrCompare);
        auto iter = shiftedProcesses.begin();
        int index;
        while (iter != shiftedProcesses.end()) {
            index = (*iter)->getQueueIndex();
            (*iter)->setQuantumLeft(queues[index].quantum);
            queues[index].queue.push_back(*iter);
            buffer << "Process " << (*iter)->getPid() << " has been shifted to queue " <<(*iter)->getQueueIndex() << ".\n";
            ++iter;
        }
        shiftedProcesses.clear();
    }
}



