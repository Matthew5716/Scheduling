
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
    while (!allProcessesHaveArrived) {
        if(!allProcessesHaveArrived) {
            allProcessesHaveArrived = addArrivedProcesses(clock);
        }

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
