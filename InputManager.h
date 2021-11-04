#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

class InputManager {

private:
    int algorithmType; //0 is MFQS and 1 is Real Time
    int readType; //0 is read from file and 1 is read from user
    bool handleIO; 


public:
    void welcomeMessage();
    void setAlgorithmType();
    int getAlgorithmType();
    void setReadType();
    int getReadType();
    bool goodInput(int input);
};


#endif