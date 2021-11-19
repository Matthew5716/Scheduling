#include "InputManager.h"
#include "Scheduler.h"
#include "RTScheduler.h"
using namespace std;

int main() {
    InputManager input;
    input.getInput();
    if(input.getAlgorithmType() == 0) {
        Scheduler* scheduler = new Scheduler(input.getTimeQuantum(), input.getProcesses(), input.getNumQueues(),
                                        input.getAgeing(), input.getMinArrival());
        if (input.getHandleIO()) {
            scheduler->setHandleIO(input.getHandleIO());
            scheduler->setIoOffset(input.getIO_Offset());
        }
        scheduler->runMFQS();
    } else {
        bool hard = input.getRealTimeType() == 1;
        RTScheduler* scheduler = new RTScheduler(input.getProcesses(), hard);
        scheduler->run();
    }

    return 0;
};
