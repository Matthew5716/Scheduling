#include "Scheduler.h"
#include <cmath>

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
    while(processIterator->getArrival() == clockTime) {
        // add processes to top queue
        queues[0].queue.push(*processIterator);
        next(processIterator,1);
    }
}

void Scheduler::runMFQS() {
    clock = 0;
    vector<Process> shiftedProcesses;

    Process * runningProcess = NULL;

    while(!finished) {

        addArrivedProcesses(clock);
        // Check for top queue that is not empty, check if queue num is the same as process running

        //If process Arrived And
    }



}