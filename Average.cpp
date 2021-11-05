#include "Average.h"


double Average::getAverageWaitTime() {
    if(numProcesses == 0) {
        return 0;
    }
    return totalWaitTime / numProcesses;
}

double Average::getAverageTurnAroundTime() {
    if(numProcesses == 0) {
        return 0;
    }
    return totalTurnAroundTime / numProcesses;

}
void Average::addProcessToAverages(Process& process) {
    int waitTime = process.getWaitTime();
    int turnAroundTime = process.getTurnaroundTime();
    if(waitTime != -1 && turnAroundTime != -1) {
        numProcesses++;
        totalWaitTime += waitTime;
        turnAroundTime += turnAroundTime;
    }
}

