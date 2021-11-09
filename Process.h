
#ifndef SCHED_PROCESS_H
#define SCHED_PROCESS_H

class Process {
private:
    int arrival;
    int burst;
    int burstLeft;
    int completionTime;
    int deadline;
    int priority;
    int ioTime;
    int ioTimeLeft;
    int queueIndex;
    int endClockTick;
public:
    // Constructor
    Process(); // default constructor
    Process(int arrival, int burst, int deadline, int priority, int ioTime);
    // Getters
    int getTurnaroundTime();
    int getWaitTime();
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
    // Setters
    void setArrival(int arr) { arrival = arr; }
    void setBurst(int b) { burst = b;}
    void setBurstLeft(int burstL) { burstLeft = burstL; }
    void setCompletionTime(int compTime) { completionTime = compTime; }
    void setDeadline(int dead_line) { deadline = dead_line; }
    void setPriority(int prior) { priority = prior; }
    void setIoTime(int io_time) { ioTime = io_time; }
    void setIoTimeLeft(int io_time_left) { ioTimeLeft = io_time_left; }
    void setQueueIndex(int queue) { queueIndex = queue; }
    //calculates when the process should be kicked off cpu if not preempted.
    void setEndClockTick(int currentClockTick, int ioOffset);
    // if not handling I/O
    void setEndClockTick(int currentClockTick) { endClockTick = currentClockTick + burstLeft; };

    // methods
    bool operator < (const Process& process) const {
        if( arrival != process.arrival) {
            return arrival < process.arrival;
        } else { // If arrival is the same put higher priority process first.
            return priority > process.priority;
        }
    }

};
#endif //SCHED_PROCESS_H
