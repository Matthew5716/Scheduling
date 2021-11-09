#include "Process.h"
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


Process::Process(int arrival, int burst, int deadline, int priority, int ioTime) {
    this->arrival = arrival;
    this->burst = burst;
    this->burstLeft = burst;
    this->deadline = deadline;
    this->priority = priority;
    this->ioTime = ioTime;
    this->ioTimeLeft = ioTime;
    this->completionTime = -1;
    this->endClockTick = -1;
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
    if(ioTimeLeft <= 0 || burstLeft <= ioOffset) {
        endClockTick = currentClockTick + burstLeft;
    } else {
        endClockTick = currentClockTick + ioOffset;
    }
}



