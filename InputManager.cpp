#include <iostream>
#include <vector>
#include "InputManager.h"
using namespace std;

void InputManager::setAlgorithmType(int input) {
    cout << "done" << endl;
    algorithmType = input;
};

int main() {
    InputManager input;

    input.setAlgorithmType(2);
    return 0;
};