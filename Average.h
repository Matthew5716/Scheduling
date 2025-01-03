//
// Created by Matthew Martinez on 11/4/21.
//
#include "Process.h"
#include <iostream>
#ifndef SCHED_AVERAGE_H
#define SCHED_AVERAGE_H

class Average {
private:
    long numProcesses;
    unsigned long long totalWaitTime;
    unsigned long long totalTurnAroundTime;
public:
    Average() {
        numProcesses = 0;
        totalTurnAroundTime = 0;
        totalWaitTime = 0;
    }

    double getAverageWaitTime();

    double getAverageTurnAroundTime();
    long getNumProcesses() { return numProcesses; }

    void addProcessToAverages(Process &process, bool hasIO);

};
#endif //SCHED_AVERAGE_H
