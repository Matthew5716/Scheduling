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
    int pid, burst, arrival, priority, deadline, io;
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
    int getRealTimeType();

    void setNumQueues();
    int getNumQueues();

    void setTimeQuantum();
    int getTimeQuantum();

    bool getHandleIO() { return handleIO; }
    int getIO_Offset() { return io_Offset; }

    bool goodInput(int input);
    bool isSanitized(Process process);

    void getInput();
    vector<Process>& getProcesses() { return processes; }

};


#endif