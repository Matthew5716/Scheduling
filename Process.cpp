#include "Process.h"
#include <algorithm>

// Default Constructor
Process::Process() {
    arrival = -1;
    burst = -1;
    burstLeft = -1;
    completionTime = -1;
    deadline = -1;
    priority = -1;
    ioTime = -1;
    ioTimeLeft = -1;
}


Process::Process(int pid, int arrival, int burst, int deadline, int priority, int ioTime) {
    this->pid = pid;
    this->arrival = arrival;
    this->burst = burst;
    this->burstLeft = burst;
    this->deadline = deadline;
    this->priority = priority;
    this->ioTime = ioTime;
    this->ioTimeLeft = ioTime;
    this->completionTime = -1;
    this->endClockTick = -1;
    this->queueIndex = 0;
    this->quantumLeft = -1;

}

int Process::getTurnaroundTime() {
    if (completionTime == -1) {
        return -1;
    }
    return completionTime - arrival;
}

int Process::getWaitTime() {
    if (completionTime == -1) {
        return -1;
    }
    return completionTime - arrival - burst - ioTime;
}

 void Process::setEndClockTick(int currentClockTick, int ioOffset) {
     if(ioTimeLeft <= 0) {
         endClockTick = currentClockTick + std::min(burstLeft, quantumLeft);
     } else {
         int offsetLeft = ioOffset - (burst - burstLeft);
         endClockTick = currentClockTick + std::min(std::min(burstLeft, quantumLeft), offsetLeft);
     }
}



