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

void InputManager::readFile() {
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
//    std::vector <Process> processes;
    string fileName = "";
    cout << "Enter the name of the text file you want to read: ";
    cin >> fileName;
    inputFile.open(fileName);
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

            // cout << "pid: " << pid << endl;
            // cout << "burst: " << burst << endl;
            // cout << "arrival: " << arrival << endl;
            // cout << "priority: " << priority << endl;
            // cout << "deadline: " << deadline << endl;
            // cout << "io: " << io << endl;

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
}

void InputManager::readFromUser() {
    cout << endl << "You have chosen to input your processes manually." << endl;
    cout << "For each process, you will be prompted for burst, arrival, priority, deadline, and I/O." << endl;
    
//    std::vector <Process> processes;
    bool exitFlag = false;
    pid = 0;
    int processCount = 0;

    while(!exitFlag) {
        //pid++;
        cout << "Input Process " << pid << " Burst: ";
        cin >> burst;
        cout << "Input Process " << pid << " Arrival: ";
        cin >> arrival;
        cout << "Input Process " << pid << " Priority: ";
        cin >> priority;
        cout << "Input Process " << pid << " Deadline: ";
        cin >> deadline;
        cout << "Input Process " << pid << " I/O: ";
        cin >> io;
        
        Process newProcess = Process(arrival, burst, deadline, priority, io);

        if (isSanitized(newProcess)) {
            cout << "pid: " << pid << " is sanitized " << endl;      
            processes.push_back(newProcess);
            processCount++;
            pid++;
        } else {
            cout << "pid: " << pid << " contains invalid input, re-enter the data." << endl;
        }

        string anotherProcess;
        cout << "* * * Would you like to input another process? (\'y\'/\'n\') * * *" << endl;
        cin >> anotherProcess;
        if (anotherProcess != "y" && anotherProcess != "Y") {
            exitFlag = true;
        }
        anotherProcess = "";            
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

void InputManager::setHandleIO() {
    cout << "Do you want to enter an I/O offset?" << endl;
    cout << "Enter \'0\' to have NO I/O, and enter \'1\' to have I/O: ";
    int input;
    cin >> input;

    while (!goodInput(input)) {
        cout << "Please only input values 1 and 0." << endl;
        cout << "Enter \'0\' to NOT enter I/O, and enter \'1\' enter I/O." << endl;
        cout << "Input your choice here: ";
        cin >> input;
    }

    if (input == 0) {
        handleIO = 0;
    } else {
        handleIO = 1;
    }

}

void InputManager::setIO_Offset() {
    cout << endl << "What do you want your I/O offset to be?" << endl;
    cout << "Enter an integer here: ";
    int input;
    cin >> input;
    input = io_Offset;
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

    if (handleIO) {
        if (process.getBurst() < io_Offset) {
        return false;
        }
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

    setHandleIO();

    if(getHandleIO() == true) {
        setIO_Offset();
    }

    setReadType();
    cout << getReadType() << endl;


    if(getReadType() == 0) {
        readFile();

        if(processes.size() == 0) {
            cout << "Unable to read file; file does not exist or error reading file." << endl;
        } else {
             cout << "Number of valid processes: " <<processes.size() << endl;
        }

       

        sort(processes.begin(), processes.end());


        // for (int i = 0; i < processes.size(); i++) {
        //     cout << "Process " << i << "'s arrival time: " << processes.at(i).getArrival() << endl;
        // }

    } else {
        readFromUser();
        
        cout << "Number of valid processes:: " << processes.size() << endl;

        sort(processes.begin(), processes.end());
        // for (int i = 0; i < processes.size(); i++) {
        //     cout << "Process " << i << "'s arrival time: " << processes.at(i).getArrival() << endl;
        // }
    }
}

