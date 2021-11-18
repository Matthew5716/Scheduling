#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H
#include <vector>
#include "Process.h"
using std::vector;
class InputManager {

private:
    int algorithmType; //0 is MFQS and 1 is Real Time
    int readType; //0 is read from file and 1 is read from user
    int realTimeType; //0 is soft and 1 is hard
    int numQueues;
    int timeQuantum;
    bool handleIO;
    int io_Offset;
    int ageing;
    int pid, burst, arrival, priority, deadline, io;
    int minArrival;
    std::vector<Process> processes;


public:
    void welcomeMessage();

    void setAlgorithmType();
    int getAlgorithmType() { return algorithmType; };

    void setReadType();
    int getReadType() { return readType; };

    void readFile();
    void readFromUser();

    void setRealTimeType();
    int getRealTimeType() { return realTimeType; };

    void setNumQueues();
    int getNumQueues() { return numQueues; };

    void setTimeQuantum();
    int getTimeQuantum() { return timeQuantum; };

    void setHandleIO();
    bool getHandleIO() { return handleIO; }

    void setIO_Offset();
    int getIO_Offset() { return io_Offset; }

    void setAgeing();
    int getAgeing() { return ageing; }

    void setMinArrival(int arrival) { minArrival = arrival < minArrival ? arrival : minArrival; };
    int getMinArrival() { return minArrival; }

    bool goodInput(int input);
    bool isSanitized(Process process);

    void getInput();
    vector<Process>& getProcesses() { return processes; }

};


#endif