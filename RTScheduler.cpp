
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
    Process *topProcess = nullptr; // top of topProcesses
    Process *topOfQueue = nullptr; // top of topProcesses
    finished = false;
    bool failed = false;
    buffer.clear();
    bool finishedBurst;
    while (!finished) {
        if(!allProcessesHaveArrived) {
            allProcessesHaveArrived = addArrivedProcesses(clock);
        }

        //TODO: update state of running process
        if (runningProcess != nullptr) { // if there is a running process
            finishedBurst = runningProcess->decrementBurstLeft();
            if(finishedBurst) {
                runningProcess->setCompletionTime(clock);
                average.addProcessToAverages(*runningProcess);
                buffer << "Process " << runningProcess->getPid() << " has finished running at time " << clock
                       << ".\n";
                runningProcess = nullptr;
            } else {
                runningProcess->setSlackTime(clock);
                if (runningProcess->getSlackTime() < 0) {
                    cout << "Process with pid " << runningProcess->getPid() << " didn't finish bursting in time \n";
                    failed = true;
                    runningProcess = nullptr;
                }
            }
        }

        // update state of topProcesses
        int deadline;
        if(!queue.empty()) {
            topOfQueue = queue.top();
            deadline = topOfQueue->getDeadline();
        } else {
            topOfQueue = nullptr;
            deadline = -1;
        }

        if(!topProcesses.empty()) {
            topProcess = topProcesses.top();
        } else {
            topProcess = nullptr;
        }

        if(topOfQueue != nullptr) {
            if (topProcess == nullptr && topOfQueue != nullptr) { // topProcesses empty
                while (!queue.empty() &&
                       queue.top()->getDeadline() == deadline) { // populate topProccesses with first deadline
                    topProcesses.push(queue.top());
                    queue.pop();
                }
            } else if (topOfQueue->getDeadline() < topProcess->getDeadline()) { // switch out top temps
                while (!topProcesses.empty()) { // empty out top process
                    queue.push(topProcesses.top());
                    topProcesses.pop();
                }
                while (!queue.empty() &&
                       queue.top()->getDeadline() == deadline) { // populate topProccesses with earlier deadline
                    topProcesses.push(queue.top());
                    queue.pop();
                }
            } else if (topOfQueue->getDeadline() == topProcess->getDeadline()) { // add to topProcesses
                while (!queue.empty() &&
                       queue.top()->getDeadline() == deadline) { // populate topProccesses with earlier deadline
                    topProcesses.push(queue.top());
                    queue.pop();
                }
            }
        }

        vector<Process*> temps;
        Process* temp = nullptr;
        while(!topProcesses.empty()) { // set slack time
            temp = topProcesses.top();
            topProcesses.pop();
            temp->setSlackTime(clock);
            if (temp->getSlackTime() <= 0) {
                failed = true;
                cout << "Process with pid " << temp->getPid() << " will not get scheduled \n";
            } else {
                temps.push_back(temp);
            }
        }

        while (!temps.empty()){ // add temps back to queue
            temp = temps.back();
            temps.pop_back();
            topProcesses.push(temp);
        }


        if(runningProcess == nullptr && !topProcesses.empty()) { // no running process
            runningProcess = topProcesses.top();
            topProcesses.pop();
        } else if(!topProcesses.empty() ){
            topProcess = topProcesses.top();
            bool earlier = topProcess->getDeadline() < runningProcess->getDeadline();
            bool same =  topProcess->getDeadline() == runningProcess->getDeadline();
            bool lessSlack = topProcess->getSlackTime() < runningProcess->getSlackTime();
            if(earlier || (same && lessSlack)) { // preempt
                queue.push(runningProcess);
                runningProcess = topProcesses.top();
                topProcesses.pop();
                cout << *runningProcess << " was preempted by " << *topProcess << "\n" << *topProcess
                       << " is now on cpu. \n";
            }
        }

        if(hard && failed) {
            cout << "A process did not get scheduled terminating. \n ";
            finished = true;
        }

        if(allProcessesHaveArrived && topProcesses.empty() && queue.empty() && runningProcess == nullptr) {
            finished = true;
        }
        clock++;

        // reset variables

//        if (clock % 200 == 0) {
//            cout << buffer.str();
//            buffer.str("");
//            buffer.clear();
//        }
    }

//    cout << buffer.str();
//    buffer.str("");
//    buffer.clear();
    cout << "\n Total Processes Scheduled: " << average.getNumProcesses() << "\nAverage wait time was: "
         << average.getAverageWaitTime() << "\n"
         << "Average TurnAroundTime was: " << average.getAverageTurnAroundTime() << "\n";
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





