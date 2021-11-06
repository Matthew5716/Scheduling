#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H
#include <vector>
#include "Process.h"

class InputManager {

private:
    int algorithmType; //0 is MFQS and 1 is Real Time
    int readType; //0 is read from file and 1 is read from user
    int realTimeType; //0 is soft and 1 is hard
    int numQueues;
    int timeQuantum;
    bool handleIO; 
    int pid, burst, arrival, priority, deadline, io;
    std::vector<Process> processes;


public:
    void welcomeMessage();

    void setAlgorithmType();
    int getAlgorithmType() { return algorithmType; };

    void setReadType();
    int getReadType() { return readType; };

    std::vector <Process> readFile();
    std::vector <Process> readFromUser();

    void setRealTimeType();
    int getRealTimeType();

    void setNumQueues();
    int getNumQueues();

    void setTimeQuantum();
    int getTimeQuantum();

    bool goodInput(int input);
    bool isSanitized(Process process);

    void getInput();

};


#endif