#include "Average.h"


double Average::getAverageWaitTime() {
    if(numProcesses == 0) {
        return 0;
    }
    return double(double(totalWaitTime) / numProcesses);
}

double Average::getAverageTurnAroundTime() {
    if(numProcesses == 0) {
        return 0;
    }
    return double(double(totalTurnAroundTime) / numProcesses);

}
void Average::addProcessToAverages(Process& process, bool hasIO) {
    int waitTime = process.getWaitTime(hasIO);
    int pTurnAroundTime = process.getTurnaroundTime();
    if(waitTime != -1 && pTurnAroundTime != -1) {
        numProcesses++;
        totalWaitTime += waitTime;
        totalTurnAroundTime += pTurnAroundTime;
    }
}

