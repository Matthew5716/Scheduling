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

class MinSlackComparator {
public:
    bool operator()(Process *lh, Process *rh) {
        if (lh->getSlackTime() != rh->getSlackTime()) {
            return lh->getSlackTime() > rh->getSlackTime(); // want lower slacktime first
        } else {
            return lh->getArrival() > rh->getArrival();
        }
    }
};

class RTScheduler {

 private:
        int clock;
        Average average;
        vector<Process> processes;
        vector<Process>::iterator processIterator;
        bool finished;
        bool hard;
        bool failed;
        int failureTime;
        stringstream buffer;
        priority_queue<Process*, vector<Process*>, RTComparator> queue;
        priority_queue<Process*, vector<Process*>, MinSlackComparator> topProcesses;
        bool addArrivedProcesses(int clockTime);
        void addToTopProcesses(int deadline);
        void setFailureTime(int time) { failureTime = std::min(failureTime, time);}

        Process *getTopOfQueue();


    public:
        RTScheduler(vector<Process>& allProcesses, bool hard, int clockStart);
        void run();


};


#endif //SCHED_RTSCHEDULER_H
