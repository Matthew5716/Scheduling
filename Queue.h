#include "Process.h"
#ifndef SCHED_QUEUE_H
#define SCHED_QUEUE_H

typedef struct Queue {
    std::queue<Process> queue;
    int quantum;
} Queue;

//class Queue {
//private:
//    queue<Process> queue;
//    int quantum;
//
//public:
//    Queue(int quant);


#endif //SCHED_QUEUE_H
