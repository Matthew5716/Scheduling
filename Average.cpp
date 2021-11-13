#include "Average.h"


double Average::getAverageWaitTime() {
    if(numProcesses == 0) {
        return 0;
    }
    return (double) totalWaitTime / numProcesses;
}

double Average::getAverageTurnAroundTime() {
    if(numProcesses == 0) {
        return 0;
    }
    return (double) totalTurnAroundTime / numProcesses;

}
void Average::addProcessToAverages(Process& process) {
    int waitTime = process.getWaitTime();
    int pTurnAroundTime = process.getTurnaroundTime();
    if(waitTime != -1 && pTurnAroundTime != -1) {
        numProcesses++;
        totalWaitTime += waitTime;
        totalTurnAroundTime += pTurnAroundTime;
    }
}

