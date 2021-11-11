#include "Scheduler.h"
#include <cmath>
#include <iostream>

using std::cout;

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
void Scheduler::addArrivedProcesses(int clockTime) {
    if(processIterator->getArrival() == clockTime)
    while(processIterator->getArrival() == clockTime) {
        // add processes to top queue
        queues[0].queue.push(*processIterator);
        //TODO: print process that arrived
        next(processIterator,1);
    }
}

Process* Scheduler::getTopProcess() {
    for(int i = 0; i < numQueues) {
        if(!queues[i].queue.empty()) {
            return (Process *) &queues[i].queue.front();
        }
    }
    return NULL;
}

void Scheduler::runMFQS() {
    clock = 0;
    vector<Process> shiftedProcesses;

    Process * runningProcess = NULL; // process on CPU
    Process * topProcess; // front of top queue that's not empty

    while(!finished) {
        //TODO:Print Clock Tick
        addArrivedProcesses(clock);
        // Check for top queue that is not empty, check if queue num is the same as process running

        topProcess = getTopProcess();

        if (runningProcess != NULL) { // if there is a running process
            runningProcess->decrementBurstLeft();
            runningProcess->decrementQuantumLeft();
            if (runningProcess->getBurstLeft() == 0) { // If process finished
                average.addProcessToAverages(*runningProcess);
                cout << "Process " << runningProcess->getPid() << " has finished running at time " << clock << ".\n";
                runningProcess = NULL:
            }
            if (runningProcess->getEndClockTick() == clock) { // kicked off cpu but not finished
                bool hitOffset = runningProcess->getBurstLeft() == runningProcess->getBurst() - IoOffset;
                bool quantumExpired = runningProcess->getQuantumLeft() == 0;

                if (quantumExpired) {
                    int queueIndex = runningProcess->getQueueIndex() + 1;
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
            continue;
        } else if(topProcess != NULL && runningProcess == NULL) { // Nothing ON CPU just put top process on
            // Pop it off queue
            queues[topProcess->getQueueIndex()].queue.pop();
            runningProcess = topProcess;
            int timeQuantum = queues[topProcess->getQueueIndex()].quantum;
            if (handleIO) {
                runningProcess->setEndClockTick(clock, IoOffset, timeQuantum);
            } else {
                runningProcess->setEndClockTick(clock, timeQuantum);
            }
        }
        else if(topProcess->getQueueIndex() > runningProcess->getQueueIndex()) { // Preempt

        }







        //If process Arrived And
    }



}