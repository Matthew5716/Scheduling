//
// Created by Matthew Martinez on 11/4/21.
//
#include "Process.h"
#ifndef SCHED_AVERAGE_H
#define SCHED_AVERAGE_H

class Average {
private:
    int numProcesses;
    long totalWaitTime;
    long totalTurnAroundTime;
public:
    Average() {
        numProcesses = 0;
        totalTurnAroundTime = 0;
        totalWaitTime = 0;
    }

    double getAverageWaitTime();

    double getAverageTurnAroundTime();

    void addProcessToAverages(Process &process);
};
#endif //SCHED_AVERAGE_H
