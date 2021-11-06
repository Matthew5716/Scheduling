#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include "InputManager.h"
#include "Process.h" //temporary include for process
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

std::vector <Process> InputManager::readFile() {
    ifstream inputFile; 
    int lineCount = 0;
    int processCount = 0;
    string fileLine;
    string pidString;
    string burstString;
    string arrivalString;
    string priorityString;
    string deadlineString;
    string IOString;
    std::vector <Process> processes;
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

            pid = stoi(pidString);
            burst = stoi(burstString);
            arrival = stoi(arrivalString);
            priority = stoi(priorityString);
            deadline = stoi(deadlineString);
            io = stoi(IOString);

            cout << "pid: " << pid << endl;
            cout << "burst: " << burst << endl;
            cout << "arrival: " << arrival << endl;
            cout << "priority: " << priority << endl;
            cout << "deadline: " << deadline << endl;
            cout << "io: " << io << endl;

            Process newProcess = Process(arrival, burst, deadline, priority, io);

            if (isSanitized(newProcess)) {
                cout << "pid: " << pid << " is sanitized " <<endl;
                processes.push_back(newProcess);
                processCount++;
            }

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
    return processes;
}

void InputManager::readFromUser() {
    cout << endl << "You have chosen to input your processes manually." << endl;
    cout << "For each process, you will be prompted for burst, arrival, priority, deadline, and I/O." << endl;
    
    bool exitFlag = false;
    int pID = 0;
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
        if (anotherProcess != "y" && anotherProcess != "Y") {
            exitFlag = true;
        }
        anotherProcess = "";            //not sure if this matters 
    }
}

void InputManager::setRealTimeType() {
    cout << endl << "Choose the type of Real Time Algorithm" << endl;
    cout << "Enter \'0\' for Soft RT, and enter \'1\' for Hard RT." << endl;
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
    realTimeType = input;
}

int InputManager::getRealTimeType() {
    return realTimeType;
}

void InputManager::setNumQueues() {
    cout << "How many queues would you like MFQS to use (2-5)?" << endl;
    cout << "Input your choice here: ";
    int input;
    cin >> input;
    
    if (input < 2 || input > 5) {
        while (input < 2 || input > 5) {
            cout << "The number you entered is out of range for number of queues." << endl;
            cout << "How many queus would you like MFQS to use (2-5)?" << endl;
            cout << "Input your choice here: ";
            cin >> input;
        }
    }
    numQueues = input;
}

int InputManager::getNumQueues() {
    return numQueues;
}

void InputManager::setTimeQuantum() {
    cout << "What time quantum do you want MFQS to use?" << endl;
    cout << "Input your choice here: ";
    int input;
    cin >> input;
    
    timeQuantum = input;
}

int InputManager::getTimeQuantum() {
    return timeQuantum;
}

bool InputManager::goodInput(int input) {
    if(input == 1 || input == 0) {
        return true;
    }
    return false;
}

bool InputManager::isSanitized(Process process) {
    if (process.getArrival() < 0 || process.getPriority() < 0 || process.getIoTime() < 0) {
        return false;
    }

    if (process.getBurst() <= 0 || process.getDeadline() <= 0) {
        return false;
    }

    return true;
}

void InputManager::getInput() {
    welcomeMessage();
    setAlgorithmType();
    cout << getAlgorithmType() << endl;

    if(getAlgorithmType() == 1) {   //real time algorithm
        setRealTimeType();
    } else {
        setNumQueues();
        setTimeQuantum();
    }

    setReadType();
    cout << getReadType() << endl;


    if(getReadType() == 0) {
        processes = readFile();

        cout << "vector size: " <<processes.size() << endl;

        sort(processes.begin(), processes.end());


        for (int i = 0; i < processes.size(); i++) {
            cout << "Process " << i << "'s arrival time: " << processes.at(i).getArrival() << endl;
        }

    } else {
        readFromUser();
    }
}

