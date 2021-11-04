//
// Created by Matthew Martinez on 11/4/21.
//
#include Process.h
#ifndef SCHED_AVERAGE_H
#define SCHED_AVERAGE_H

class Average {
private:
    int numProcesses;
    long totalWaitTime;
    long totalTurnAroundTime;
public:
    Average() { numProcesses = 0; totalTurnA}
    double getAverageWaitTime();
    double getAverageTurnAroundTime();
    void addProcessToAverage();
#endif //SCHED_AVERAGE_H
