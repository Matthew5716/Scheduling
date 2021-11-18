#include "InputManager.h"
#include "Scheduler.h"
#include "RTScheduler.h"
using namespace std;

int main() {
    InputManager input;
    input.getInput();
    if(input.getAlgorithmType() == 0) {
        Scheduler* scheduler = new Scheduler(input.getTimeQuantum(), input.getProcesses(), input.getNumQueues(),
                                        input.getAgeing());
        if (input.getHandleIO()) {
            scheduler->setHandleIO(input.getHandleIO());
            scheduler->setIoOffset(input.getIO_Offset());
        }
        scheduler->runMFQS();
    } else {
        RTScheduler* scheduler = new RTScheduler(input.getProcesses(),input.getRealTimeType());
        scheduler->run();
    }

    return 0;
};
