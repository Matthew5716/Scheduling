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
using std::ostringstream;

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
    int processIndex;
    bool finished;
    queue<Process> arrivedProcesses;
    queue<Process*> IOQueue;
    int ageLimit;
    ostringstream buffer;

    void insertShiftedProcesses(vector<Process*>& shiftedProcesses);
    bool addArrivedProcesses(int clockTime);
    Process* getTopProcess();
    void updateAgeing(vector<Process*>& shiftedProcesses);



public:
    Scheduler();
    Scheduler(int timeQuantum, vector<Process>& allProcesses, int nQueues, int ageing);
    void runMFQS();

    void setHandleIO(bool handleIo) { handleIO = handleIo; }
    void setProccees(vector<Process>& allProcesses) { processes = allProcesses ;}
    void setNumQueues(int nQueues) { numQueues = nQueues; }
    void setIoOffset(int ioOffset) { IoOffset = ioOffset; }
};

#endif //SCHED_SCHEDULER_H
