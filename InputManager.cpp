#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
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
    inputFile.open("test.txt");
    getline(inputFile, fileLine); // ignore first line of column headers
    if (inputFile.is_open() ) { 
        char fileChars;
        while (inputFile) {
            fileChars = inputFile.get();

            if(fileChars == '\t') {
                lineCount = 1;
            } else if (lineCount == 0) {
                pidString += fileChars;
            }

            if(fileChars == '\t') {
                lineCount = 2;
            } else if (lineCount == 1){
                burstString += fileChars;
            }

            if(fileChars == '\n') {
                cout << "Pid: " << pidString << endl;
                cout << "Burst: " << burstString << endl;


                cout << "Add New Process:" << endl;
                lineCount = 0;
                pidString = "";
                burstString = "";
            }
        }
    }   
    inputFile.close();
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

    input.readFile();
    return 0;
};
