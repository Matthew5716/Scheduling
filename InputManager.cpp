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

    return 0;
};
