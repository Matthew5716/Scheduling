#include "Average.h"
#include <vector>
#include <queue>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include "Process.h"

#ifndef SCHED_RTSCHEDULER_H
#define SCHED_RTSCHEDULER_H

using std::vector;
using std::stringstream;
using std::priority_queue;

class RTComparator {
public:
    bool operator()(Process *lh, Process *rh) {
        if (lh->getDeadline() != rh->getDeadline()) {
            return lh->getDeadline() > rh->getDeadline(); // want lower getDeadline()s first
        } else {
            // If arrival is the same put higher priority process first. Lower priority value means higher priority
            return lh->getPriority() > rh->getPriority();
        }
    }
};

class RTScheduler {

 private:
        int clock;
        Average average;
        vector<Process> processes;
        vector<Process>::iterator processIterator;
        vector<Process*> topProcesses;
        bool finished;
        bool hard;
        stringstream buffer;
        priority_queue<Process*, vector<Process*>, RTComparator> queue;
        bool addArrivedProcesses(int clockTime);
        bool updateTopProcesses(int clockTime);
//        Process* getTopProcess();


    public:
//        RTScheduler();
        RTScheduler(vector<Process>& allProcesses, bool hard);
        void run();


        void setProccees(vector<Process>& allProcesses) { processes = allProcesses;}
};


#endif //SCHED_RTSCHEDULER_H
