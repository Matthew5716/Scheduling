#include <stdio.h>;
#include <string.h>;

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
        int getArrival() {
            return arrival;
        }

        int getBurst() {
            return burst;
        }

        int getBurstLeft() {
            return burstLeft;
        }

        int getCompletionTime() {
            return completionTime;
        }

        int getDeadline() {
            return deadline;
        }

        int getPriority() {
            return priority;
        }

        int getIoTime() {
            return ioTime;
        }

        int getIoTimeLeft() {
            return ioTimeLeft;
        }

        int setArrival(int arr) {
            arrival = arr;
        }
        int setBurst(int b) {
            burst = b;
        }
        int setBurstLeft(int burstL) {
            burstLeft = burstL;
        }
        int setCompletionTime(int compTime) {
            completionTime = compTime;
        }
        int setDeadline(int dead_line) {
            deadLine = dead_line;

        }
        int setPriority(int prior) {
            priority = prior;
        }
        int setIoTime(int io_time) {
            ioTime = io_time;
        }
        int setIoTimeLeft(int io_time_left) {
            ioTimeLeft = io_time_left;
        }


};