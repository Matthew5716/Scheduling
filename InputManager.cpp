#include <iostream>
#include <vector>
#include "InputManager.h"
using namespace std;

void InputManager::setAlgorithmType(int input) {
    cout << "done" << endl;
    algorithmType = input;
};

int InputManager::getAlgorithmType() {
    return algorithmType;
}

int main() {
    InputManager input;

    input.setAlgorithmType(2);
    cout << input.getAlgorithmType();

    return 0;
};
