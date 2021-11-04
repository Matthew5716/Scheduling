#include <iostream>
#include <vector>
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
    return 0;
};
