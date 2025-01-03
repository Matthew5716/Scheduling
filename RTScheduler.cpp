
#include "RTScheduler.h"
using std::cout;

RTScheduler::RTScheduler(vector<Process>& allProcesses, bool hard, int clockStart) {
    processes = allProcesses;
    processIterator = processes.begin();
    this->hard -= hard;
    clock = clockStart;
    failureTime = 1000000;
}


// issue with deadline, need to empty out topProcesses if the deadline is equal to the clock tick.
void RTScheduler::run() {
    if (processes.size() == 0) {
        cout << "No processes.";
        return;
    }
    bool allProcessesHaveArrived = false;
    Process *runningProcess = nullptr; // process on CPU
    Process *topProcess = nullptr; // top of topProcesses
    Process *topOfQueue = nullptr; // top of topProcesses
    finished = false;
    failed = false;
    buffer.clear();
    buffer.str("");
    bool finishedBurst;
    while (!finished) {
        buffer << "Clock Time: " << clock << "\n";
        if(!allProcessesHaveArrived) {
            allProcessesHaveArrived = addArrivedProcesses(clock);
        }

        if (runningProcess != nullptr) { // if there is a running process
            finishedBurst = runningProcess->decrementBurstLeft();
            if(finishedBurst) {
                runningProcess->setCompletionTime(clock);
                average.addProcessToAverages(*runningProcess, false);
                buffer << "Process " << runningProcess->getPid() << " has finished running at time " << clock
                       << ".\n";
                runningProcess = nullptr;
            } else {
                runningProcess->setSlackTime(clock);
                if (runningProcess->getSlackTime() < 0) {
                    buffer << "Process with pid " << runningProcess->getPid() << " didn't finish bursting in time \n";
                    failed = true;
                    setFailureTime(runningProcess->getDeadline());
                    runningProcess = nullptr;
                }
            }
        }

        // update state of topProcesses
        vector<Process*> temps;
        Process* temp = nullptr;
        while(!topProcesses.empty()) { // set slack time
            temp = topProcesses.top();
            topProcesses.pop();
            temp->setSlackTime(clock);
            if (temp->getSlackTime() < 0) {
                failed = true;
                buffer << "Process with pid " << temp->getPid() << " will not get scheduled \n";
                setFailureTime(temp->getDeadline());
            } else {
                temps.push_back(temp);
            }
        }

        while (!temps.empty()){ // add temps back to queue
            temp = temps.back();
            temps.pop_back();
            topProcesses.push(temp);
        }


        topOfQueue = getTopOfQueue();
        int deadline;
        if(topOfQueue != nullptr) {
            deadline = topOfQueue->getDeadline();
        } else {
            deadline = -1;
        }

        if(!topProcesses.empty()) {
            topProcess = topProcesses.top();
        } else {
            topProcess = nullptr;
        }

        if(topOfQueue != nullptr) {
            if (topProcess == nullptr && topOfQueue != nullptr) { // topProcesses empty
                addToTopProcesses(deadline);
            } else if (topOfQueue->getDeadline() < topProcess->getDeadline()) { // switch out top temps
                while (!topProcesses.empty()) { // empty out top process
                    queue.push(topProcesses.top());
                    topProcesses.pop();
                }
                addToTopProcesses(topOfQueue->getDeadline());
            } else if (topOfQueue->getDeadline() == topProcess->getDeadline()) { // add to topProcesses
                addToTopProcesses(topOfQueue->getDeadline());
            }
        }

        if(runningProcess == nullptr && !topProcesses.empty()) { // no running process
            runningProcess = topProcesses.top();
            topProcesses.pop();
        } else if(!topProcesses.empty() ){
            topProcess = topProcesses.top();
            topProcess->setSlackTime(clock);
            runningProcess->setSlackTime(clock);
            bool earlier = topProcess->getDeadline() < runningProcess->getDeadline();
            bool same =  topProcess->getDeadline() == runningProcess->getDeadline();
            bool lessSlack = topProcess->getSlackTime() < runningProcess->getSlackTime();
            if(earlier || (same && lessSlack)) { // preempt
                queue.push(runningProcess);
                runningProcess = topProcesses.top();
                topProcesses.pop();
                buffer << *runningProcess << " was preempted by " << *topProcess << "\n" << *topProcess
                       << " is now on cpu. \n";
            }
        }

        if(hard && failed && failureTime == clock) {
            buffer << "A process did not get scheduled before its deadline terminating. \n ";
            finished = true;
        }

        if(runningProcess != nullptr) {
            buffer << "Process with pid: " << runningProcess->getPid() << " is on CPU. \n";
        }

        if(allProcessesHaveArrived && topProcesses.empty() && queue.empty() && runningProcess == nullptr) {
            finished = true;
        }
        clock++;

        // reset variables

        if (clock % 200 == 0) {
            cout << buffer.str();
            buffer.str("");
            buffer.clear();
        }
    }

    cout << buffer.str();
    buffer.str("");
    buffer.clear();

    cout << "\nTotal Processes Scheduled: " << average.getNumProcesses() << "\nAverage wait time was: "
         << average.getAverageWaitTime() << "\n"
         << "Average TurnAroundTime was: " << average.getAverageTurnAroundTime() << "\n";
}

void RTScheduler::addToTopProcesses(int deadline) {
    Process* topOfQueue;
    while (!queue.empty() &&
           queue.top()->getDeadline() == deadline) { // populate top Proccesses with first deadline
        topOfQueue = getTopOfQueue();
        if(topOfQueue != nullptr && topOfQueue->getDeadline() == deadline) {
            topProcesses.push(queue.top());
            queue.pop();
        }
    }
}

Process* RTScheduler::getTopOfQueue() {
    bool valid = false;
    //update state of queue
    while(!queue.empty() && !valid) { // set slack time
        queue.top()->setSlackTime(clock);
        if ( queue.top()->getSlackTime() < 0) {
            failed = true;
                buffer << "Process with pid " << queue.top()->getPid() << " will not get scheduled \n";
            setFailureTime(queue.top()->getDeadline());
            queue.pop();
        } else {
            valid = true;
        }
    }
    if (!queue.empty()) {
        return queue.top();
    } else {
        return nullptr;
    }
}

bool RTScheduler::addArrivedProcesses(int clockTime) {
    while(processIterator->getArrival() == clockTime) {
        processIterator->setSlackTime(clockTime);
        if(processIterator->getSlackTime() < 0) {
            buffer << "Process with pid " << processIterator->getPid() << " will not get scheduled \n";
            failed = true;
            setFailureTime(processIterator->getDeadline());
        } else {
            queue.push(&(*processIterator));
        }
        buffer << "Process " << processIterator->getPid() << " with deadline " << processIterator->getDeadline() << " has arrived. \n";
        ++processIterator;
        if(processIterator == processes.end()) {
            return true;
        }
    }
    return false;
}





