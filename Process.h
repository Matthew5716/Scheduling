#ifndef SCHED_PROCESS_H
#define SCHED_PROCESS_H
#include <algorithm>
#include <iostream>
using std::ostream;


class Process {
private:
    int arrival;
    int pid;
    int burst;
    int burstLeft;
    int completionTime;
    int deadline;
    int priority;
    int ioTime;
    int ioTimeLeft;
    int queueIndex;
    int endClockTick;
    int quantumLeft;
    int ageTime;
    int ioOffsetLeft;
    int slackTime;
public:
    // Constructor
    Process(); // default constructor
    Process(int pid, int arrival, int burst, int deadline, int priority, int ioTime);
    // Getters
    int getTurnaroundTime();
    int getWaitTime(bool hasIO);
    int getArrival() { return arrival; }
    int getBurst() { return burst; }
    int getBurstLeft() { return burstLeft; }
    int getCompletionTime() { return completionTime; }
    int getDeadline() { return deadline; }
    int getPriority() { return priority; }
    int getIoTime() { return ioTime; }
    int getIoTimeLeft() { return ioTimeLeft; }
    int getQueueIndex() { return queueIndex; }
    int getEndClockTick() { return endClockTick; }
    int getPid() { return pid; }
    int getQuantumLeft() { return quantumLeft; }
    int getAgeTime() { return ageTime; }
    int getIOOffsetLeft() { return ioOffsetLeft; };
    int getSlackTime() { return slackTime; }
    // Setters
    void setArrival(int arr) { arrival = arr; }
    void setBurst(int b) { burst = b;}
    bool decrementBurstLeft() { --burstLeft; return burstLeft <= 0;}
    void setBurstLeft(int burstL) { burstLeft = burstL; }
    void setCompletionTime(int compTime) { completionTime = compTime; }
    void setDeadline(int dead_line) { deadline = dead_line; }
    void setPriority(int prior) { priority = prior; }
    void setIoTime(int io_time) { ioTime = io_time; }
    void setIoTimeLeft(int io_time_left) { ioTimeLeft = io_time_left; }
    bool decrementIoTimeLeft() { ioTimeLeft--; return ioTimeLeft == 0;}
    void setQueueIndex(int queue) { queueIndex = queue; }
    //calculates when the process should be kicked off cpu if not preempted.
    void setEndClockTick(int currentClockTick, int ioOffset);
    // if not handling I/O
    void setEndClockTick(int currentClockTick) { endClockTick = currentClockTick + std::min(burstLeft, quantumLeft); }
    void setPid(int P_id) { pid = P_id; }
    bool decrementQuantumLeft() { --quantumLeft; return quantumLeft == 0; }
    void setQuantumLeft(int quant) { quantumLeft = quant; }
    void setAgeTime() { ageTime = 0; }
    void incrementAge() { ageTime++; }
    bool decrementIOOffsetLeft() { --ioOffsetLeft; return ioOffsetLeft == 0;}
    void setIOOffsetLeft(int offset) { ioOffsetLeft = offset; }
    void setSlackTime(int currentClockTick) { slackTime = deadline - (currentClockTick + burstLeft); }

    // methods
    bool operator < (const Process& process) const {
        if( arrival != process.arrival) {
            return arrival < process.arrival;
        } else { // If arrival is the same put higher priority process first. Lower priority value means higher priority
            return priority < process.priority;
        }
    }

    friend ostream& operator<<(ostream &os, const Process& process) {
        os << "Process with Pid: " << process.pid << " and queue level: " << process.queueIndex;
        return os;
    }

};
#endif //SCHED_PROCESS_H
