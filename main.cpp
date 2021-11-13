#include <fstream>
#include "InputManager.h"
#include "Scheduler.h"
using namespace std;

int main() {
    InputManager input;
    input.getInput();
    if(input.getAlgorithmType() == 0) {
        Scheduler scheduler = Scheduler(input.getTimeQuantum(), input.getProcesses(), input.getNumQueues(),
                                        input.getAgeing());
        if (input.getHandleIO()) {
            scheduler.setHandleIO(input.getHandleIO());
            scheduler.setIoOffset(input.getIO_Offset());
        }
        scheduler.runMFQS();
    }

    return 0;
};
