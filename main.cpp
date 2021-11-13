#include <iostream>
#include <fstream>
#include <vector>
#include "InputManager.h"
#include "Scheduler.h"
#include "Process.h"
using namespace std;

int main() {
    InputManager input;
    input.getInput();
    Scheduler scheduler =  Scheduler(input.getTimeQuantum(), input.getProcesses(), input.getNumQueues(), input.getAgeing());
    if(input.getHandleIO()) {
        scheduler.setHandleIO(input.getHandleIO());
        scheduler.setIoOffset(input.getIO_Offset());
    }

    return 0;
};
