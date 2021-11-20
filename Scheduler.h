#include "Average.h"
#include <vector>
#include <queue>
#include <stdlib.h>
#include "Queue.h"
#include <iostream>
#include <sstream>

#ifndef SCHED_SCHEDULER_H
#define SCHED_SCHEDULER_H
using std::vector;
using std::queue;
using std::stringstream;

class Scheduler {
private:
    int clock;
    Average average;
    vector<Process> processes;
    vector<Process>::iterator processIterator;
    Queue queues[5];
    int quantum;
    int numQueues;
    bool handleIO;
    int IoOffset;
    bool finished;
    queue<Process*> IOQueue;
    int ageLimit;
    stringstream buffer;

    void insertShiftedProcesses(vector<Process*>& shiftedProcesses);
    bool addArrivedProcesses(int clockTime);
    Process* getTopProcess();
    void updateAgeing(vector<Process*>& shiftedProcesses);



public:
    Scheduler();
    Scheduler(int timeQuantum, vector<Process>& allProcesses, int nQueues, int ageing, int startTick);
    void runMFQS();

    void setHandleIO(bool handleIo) { handleIO = handleIo; }
    void setIoOffset(int ioOffset) { IoOffset = ioOffset; }
};

#endif //SCHED_SCHEDULER_H
