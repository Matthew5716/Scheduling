#include "Scheduler.h"
#include <cmath>
#include <iostream>

using std::cout;
using std::min;

Scheduler::Scheduler(int timeQuantum, int IoOffset, vector<Process>& allProcesses, int nQueues) {
    quantum = timeQuantum;
    handleIO = true;
    this->IoOffset = IoOffset;
    processes = allProcesses;
    processIterator = processes.begin();
    finished = false;
    numQueues = nQueues;
    for(int i = 0; i < nQueues; i++) {
        queues[i].quantum = timeQuantum * pow(2,i);
    }
}

Scheduler::Scheduler(int timeQuantum, vector<Process>& allProcesses, int nQueues) {
    handleIO = false;
    quantum = timeQuantum;
    processes = allProcesses;
    processIterator = processes.begin();
    finished = false;
    numQueues = nQueues;
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
        //TODO: print process that arrived
        next(processIterator,1);
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

void Scheduler::runMFQS() {
    clock = 0;
    vector<Process> shiftedProcesses;
    bool allProcessesHaveArrived;

    Process * runningProcess = NULL; // process on CPU
    Process * topProcess; // front of top queue that's not empty

    while(!finished) {
        //TODO:Print Clock Tick
        allProcessesHaveArrived = addArrivedProcesses(clock);
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
            // TODO: IF No more arriving procesees and IO QUEUE is empty set finsihed true;
            continue;
        } else if(topProcess != NULL && runningProcess == NULL) { // Nothing ON CPU just put top process on
            // Pop it off queue
            queues[topProcess->getQueueIndex()].queue.pop_front();
            runningProcess = topProcess;
            int timeQuantum = queues[topProcess->getQueueIndex()].quantum;
            if (handleIO) {
                runningProcess->setEndClockTick(clock, IoOffset, timeQuantum);
            } else {
                runningProcess->setEndClockTick(clock, timeQuantum);
            }
        }
        else if(topProcess->getQueueIndex() > runningProcess->getQueueIndex()) { // Preempt
            int queueIndex = runningProcess->getQueueIndex();
            if(queueIndex == numQueues - 1) {
                queues[runningProcess->getQueueIndex()].queue.push_front(*runningProcess); // last queue FCFS
            } else {
                queues[runningProcess->getQueueIndex()].queue.push_back(*runningProcess); // other queues RR
            }
            //TODO: Add print statement
            queues[topProcess->getQueueIndex()].queue.pop_front();
            runningProcess = topProcess;
        }

        //TODO: Handle IO queue

        //TODO: Handle Ageing

        //TODO: ReInsert shifted Processes to queues

        //TODO: Handle Finished Statement

        //If process Arrived And
    }



}