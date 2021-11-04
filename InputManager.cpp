#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include "InputManager.h"
using namespace std;

void InputManager::welcomeMessage() {
    cout << "****** Welcome to CS452's Lab 2: Process Scheduling Assignment. ******" << endl;
    cout << "You will be asked to choose running options below, please only enter inputs 1 or 0. " << endl << endl;
}

void InputManager::setAlgorithmType() {
    cout << "Choose the algorithm you would like to run for process scheduling:" << endl;
    cout << "Enter \'0\' for a MFQS algorithm, and enter \'1\' for a real time algorithm" << endl;
    cout << "Input your choice here: ";
    int input;
    cin >> input;
    
    if (!goodInput(input)) {
        while (!goodInput(input)) {
            cout << "Please only input values 1 and 0." << endl;
            cout << "Enter \'0\' for a MFQS algorithm, and enter \'1\' for a real time algorithm" << endl;
            cout << "Input your choice here: ";
            cin >> input;
        }
    }
    algorithmType = input;
};

int InputManager::getAlgorithmType() {
    return algorithmType;
}

void InputManager::setReadType() {
    cout << endl << "Choose if you would like to read from a file or manually input processes:" << endl;
    cout << "Enter \'0\' to read from a file, and enter \'1\' to manually enter processes" << endl;
    cout << "Input your choice here: ";
    int input;
    cin >> input;
    if (!goodInput(input)) {
        while (!goodInput(input)) {
            cout << "Please only input values 1 and 0." << endl;
            cout << "Enter \'0\' to read from a file, and enter \'1\'  to manually enter processes" << endl;
            cout << "Input your choice here: ";
            cin >> input;
        }
    }
    readType = input;
}

int InputManager::getReadType() {
    return readType;
}

void InputManager::readFile() {
    ifstream inputFile; 
    int lineCount = 0;
    string fileLine;
    string pidString;
    string burstString;
    string arrivalString;
    string priorityString;
    string deadlineString;
    string IOString;
    inputFile.open("test.txt");
    getline(inputFile, fileLine); // ignore first line of column headers
    if (inputFile.is_open() ) {
        string line;
        while(getline(inputFile, line)){
            int len = line.length();
            char lineChars[len+1];
            int itemCount = 0;
            strcpy(lineChars, line.c_str());

            for (int i = 0; i < len; i++) {
                if(itemCount == 0) {
                    if(lineChars[i] != '\t') {
                        pidString += lineChars[i];
                    } else {
                        itemCount = 1;
                        i++;
                    }
                }

                if(itemCount == 1) {
                    if(lineChars[i] != '\t') {
                        burstString += lineChars[i];
                    } else {
                        itemCount = 2;
                        i++;
                    }
                }

                if(itemCount == 2) {
                    if(lineChars[i] != '\t') {
                        arrivalString += lineChars[i];
                    } else {
                        itemCount = 3;
                        i++;
                    }
                }

                if(itemCount == 3) {
                    if(lineChars[i] != '\t') {
                        priorityString += lineChars[i];
                    } else {
                        itemCount = 4;
                        i++;
                    }
                }

                if(itemCount == 4) {
                    if(lineChars[i] != '\t') {
                        deadlineString += lineChars[i];
                    } else {
                        itemCount = 5;
                        i++;
                    }
                }

                if(itemCount == 5) {
                    if(lineChars[i] != '\t') {
                        IOString += lineChars[i];
                    } else {
                        itemCount = 6;
                        i++;
                    }
                }

            }

            cout << "pid: " << pidString << endl;
            cout << "burst: " << burstString << endl;
            cout << "arrival: " << arrivalString << endl;
            cout << "priority: " << priorityString << endl;
            cout << "priority: " << deadlineString << endl;
            cout << "priority: " << IOString << endl;
            cout << endl;
            pidString = "";
            burstString = "";
            arrivalString = "";
            priorityString = "";
            deadlineString = "";
            IOString = "";
        }
    }   
    inputFile.close();
}

void InputManager::readFromUser() {
    cout << endl << "You have chosen to input your processes manually." << endl;
    cout << "For each process, you will be prompted for burst, arrival, priority, deadline, and I/O." << endl;
    
    bool exitFlag = false;
    int pID;
    int burst;
    int arrival;
    int priority;
    int deadline;
    int io;
    string anotherProcess;

    while(!exitFlag) {
        pID++;
        cout << "Input Process " << pID << " Burst: ";
        cin >> burst;
        cout << "Input Process " << pID << " Arrival: ";
        cin >> arrival;
        cout << "Input Process " << pID << " Priority: ";
        cin >> priority;
        cout << "Input Process " << pID << " Deadline: ";
        cin >> deadline;
        cout << "Input Process " << pID << " I/O: ";
        cin >> io;
        cout << "*** Would you like to input another process? (\'y\'/\'n\')***" << endl;
        cin >> anotherProcess;
        if (anotherProcess == "n") {
            exitFlag = true;
        }
    }
    

}

bool InputManager::goodInput(int input) {
    if(input == 1 || input == 0) {
        return true;
    }
    return false;
}

int main() {
    InputManager input;
    input.welcomeMessage();
    input.setAlgorithmType();
    cout << input.getAlgorithmType() << endl;
    input.setReadType();
    cout << input.getReadType() << endl;

    if(input.getReadType() == 0) {         
        input.readFile();       
    } else {
        input.readFromUser();
    }

    return 0;
};
