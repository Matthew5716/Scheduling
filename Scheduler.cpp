#include "Scheduler.h"
#include <cmath>

Scheduler::Scheduler(int timeQuantum, int IoOffset, vector<Process>& allProcesses, int nQueues) {
    quantum = timeQuantum;
    handleIO = true;
    this->IoOffset = IoOffset;
    processes = allProcesses;
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
void Scheduler::addArrivedProcesses() {

}

void Scheduler::runMFQS() {
    clock = 0;
    Process * runningProcess = NULL;

    while(!finished) {
        addArrivedProcesses();
        // Check for top queue that is not empty, check if queue num is the same as process running

    }



}