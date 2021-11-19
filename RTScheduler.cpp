
#include "RTScheduler.h"
using std::cout;

RTScheduler::RTScheduler(vector<Process>& allProcesses, bool hard) {
    processes = allProcesses;
    processIterator = processes.begin();
    this->hard -= hard;
}



void RTScheduler::run() {
    if (processes.size() == 0) {
        cout << "No processes.";
        return;
    }
    clock = 0;
    bool allProcessesHaveArrived = false;
    Process *runningProcess = nullptr; // process on CPU
    Process *topProcess = nullptr; // front of top queue that's not empty
    buffer.clear();
    bool finishedBurst;
    while (!allProcessesHaveArrived) {
        if(!allProcessesHaveArrived) {
            allProcessesHaveArrived = addArrivedProcesses(clock);
        }

        //TODO: update state of running process
        if (runningProcess != nullptr) { // if there is a running process
            finishedBurst = runningProcess->decrementBurstLeft();
        }

        //TODO: update the state of top processes, if any miss deadline and its hard realtime fail
        // Check if the top process on priority_queue has the same deadline, pop that and add
        // If it has earlier deadline, push top processes back and grab new list based on earlier deadline
        // else update slack times

        //TODO: check for preemption
        // check if topProcess in topProcesses has earlier deadline or same dealine earlier slack, potentially also arrival


        //TODO:

        clock++;
        // reset variables

//        if (clock % 200 == 0) {
//            cout << buffer.str();
//            buffer.str("");
//            buffer.clear();
//        }
    }

    while(!queue.empty()) {
        runningProcess = queue.top();
        queue.pop();
        cout << "Process with deadline: " << runningProcess->getDeadline() << " and priority: " << runningProcess->getPriority() << "\n";
    }
//    cout << buffer.str();
//    buffer.str("");
//    buffer.clear();
//    cout << "\n Total Processes Scheduled: " << average.getNumProcesses() << "\nAverage wait time was: "
//         << average.getAverageWaitTime() << "\n"
//         << "Average TurnAroundTime was: " << average.getAverageTurnAroundTime() << "\n";
}

bool RTScheduler::addArrivedProcesses(int clockTime) {
    while(processIterator->getArrival() == clockTime) {
        // add processes to top queue
        queue.push(&(*processIterator));
        buffer << "Process " << processIterator->getPid() << " has arrived. \n";
        ++processIterator;
        if(processIterator == processes.end()) {
            return true;
        }
    }
    return false;
}

bool RTScheduler::updateTopProcesses(int clockTime) {



   //update the state of top processes, if any miss deadline and its hard realtime fail
    // Check if the top process on priority_queue has the same deadline, pop that and add
    // If it has earlier deadline, push top processes back and grab new list based on earlier deadline
    // else update slack times

}

