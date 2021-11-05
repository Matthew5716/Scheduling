
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
    // Setters
    void setArrival(int arr) { arrival = arr; }
    void setBurst(int b) { burst = b;}
    void setBurstLeft(int burstL) { burstLeft = burstL; }
    void setCompletionTime(int compTime) { completionTime = compTime; }
    void setDeadline(int dead_line) { deadline = dead_line; }
    void setPriority(int prior) { priority = prior; }
    void setIoTime(int io_time) { ioTime = io_time; }
    void setIoTimeLeft(int io_time_left) { ioTimeLeft = io_time_left; }

    // methods
    bool operator < (const Process& process) { return arrival < process.arrival; }
    static bool arrivalComparator(Process& lhs, Process& rhs) { return lhs.getArrival() < rhs.getArrival() ;}

};
#endif //SCHED_PROCESS_H
