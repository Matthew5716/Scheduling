#include "Scheduler.h"
#include <cmath>
#include <iostream>
#include <algorithm>

using std::cout;
using std::min;
using std::sort;

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
        queues[0].queue.push_back(*processIterator);
        cout << "Process " << processIterator->getPid() << " has arrived. \n";
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
            return (Process *) &queues[i].queue.front();
        }
    }
    return NULL;
}

void Scheduler::updateAgeing(vector<Process>& shiftedProcesses) {
    size_t size = queues[numQueues - 1].queue.size();
    Process& temp =  queues[numQueues -1].queue.front();
    for(size_t i = 0; i < size; i++) {
        temp = queues[numQueues -1].queue.front();
        queues[numQueues -1].queue.pop_front();
        temp.incrementAge();
        if(temp.getAgeTime() == ageLimit) {
            temp.setQueueIndex(temp.getQueueIndex() - 1);
            shiftedProcesses.push_back(temp);
        } else {
            queues[numQueues -1].queue.push_back(temp);
        }
    }
}

void updateIO(queue<Process>& IOQueue, vector<Process>& shiftedProcesses) {
    Process &ioProcess = IOQueue.front();
    if (ioProcess.decrementIoTimeLeft()) {
        ioProcess.setQueueIndex(ioProcess.getQueueIndex() + 1);
        shiftedProcesses.push_back(ioProcess);
        IOQueue.pop();
        cout << "Process " << ioProcess.getPid() << " finished I/O \n";
    }
}

void Scheduler::runMFQS() {
    clock = 0;
    vector<Process> shiftedProcesses;
    bool allProcessesHaveArrived;

    Process * runningProcess = NULL; // process on CPU
    Process * topProcess; // front of top queue that's not empty

    while(!finished) {
        cout << "ClockTick: " << clock << " \n";
        if(!allProcessesHaveArrived) {
            allProcessesHaveArrived = addArrivedProcesses(clock);
        }

        // Check for top queue that is not empty, check if queue num is the same as process running
        topProcess = getTopProcess();

        if (runningProcess != NULL) { // if there is a running process
            runningProcess->decrementBurstLeft();
            runningProcess->decrementQuantumLeft();
            if (runningProcess->getBurstLeft() == 0) { // If process finished
                average.addProcessToAverages(*runningProcess);
                cout << "Process " << runningProcess->getPid() << " has finished running at time " << clock << ".\n";
                runningProcess = NULL;
            }
            if (runningProcess->getEndClockTick() == clock) { // kicked off cpu but not finished
                bool hitOffset = runningProcess->getBurstLeft() == runningProcess->getBurst() - IoOffset;
                bool quantumExpired = runningProcess->getQuantumLeft() == 0;

                if (quantumExpired) {
                    int queueIndex = min(runningProcess->getQueueIndex() + 1, numQueues - 1); // can't go above last queue
                    runningProcess->setQueueIndex(queueIndex);
                    cout << "Process " << runningProcess->getPid() << " has been demoted to queue "
                         << runningProcess->getQueueIndex() << ".\n";
                }
                if (hitOffset) {
                    IOQueue.push(*runningProcess);
                } else {
                    shiftedProcesses.push_back(*runningProcess);
                }
                runningProcess = NULL;
            }
        }

        if(topProcess == NULL && runningProcess == NULL) { // Nothing to put in CPU
            clock++;
            if(allProcessesHaveArrived && IOQueue.empty() && shiftedProcesses.empty()) {
                finished = true;
            }
            continue;
        } else if(topProcess != NULL && runningProcess == NULL) { // Nothing ON CPU just put top process on
            // Pop it off queue
            queues[topProcess->getQueueIndex()].queue.pop_front();
            runningProcess = topProcess;
            if (handleIO) {
                runningProcess->setEndClockTick(clock, IoOffset);
            } else {
                runningProcess->setEndClockTick(clock);
            }
        }
        else if(topProcess->getQueueIndex() > runningProcess->getQueueIndex()) { // Preempt
            int queueIndex = runningProcess->getQueueIndex();
            if(queueIndex == numQueues - 1) {
                queues[runningProcess->getQueueIndex()].queue.push_front(*runningProcess); // last queue FCFS
            } else {
                queues[runningProcess->getQueueIndex()].queue.push_back(*runningProcess); // other queues RR
            }
            cout << *runningProcess << " was preempted by " << *topProcess << "\n" << *topProcess << " is now on cpu. \n";
            queues[topProcess->getQueueIndex()].queue.pop_front();
            runningProcess = topProcess;
        }


        //Handle Ageing
        updateAgeing(shiftedProcesses);

        // IO queue
        if (handleIO) {
            updateIO(IOQueue, shiftedProcesses);
        }

        insertShiftedProcesses(shiftedProcesses);
        clock++;
    }
}

void Scheduler::insertShiftedProcesses(vector<Process>& shiftedProcesses) {
    sort(shiftedProcesses.begin(), shiftedProcesses.end());
    auto iter = shiftedProcesses.begin();
    int index;
    while (iter != shiftedProcesses.end()) {
        index = iter->getQueueIndex();
        iter->setQuantumLeft(queues[index].quantum);
        queues[index].queue.push_back(*iter);
        cout << "Process " << iter->getPid() << " has been shifted to queue " << iter->getQueueIndex() << ".\n";
        ++iter;
    }
    shiftedProcesses.clear();
}