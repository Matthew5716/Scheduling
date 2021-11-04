#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

class InputManager {

private:
    int algorithmType; //0 is MFQS and 1 is Real Time
    int readType; //0 is read from file and 1 is read from user
    bool handleIO; 
    int pid, burst, arrival, priority, deadline, io;


public:
    void welcomeMessage();

    void setAlgorithmType();
    int getAlgorithmType();

    void setReadType();
    int getReadType();

    void readFile();

    bool goodInput(int input);

};


#endif