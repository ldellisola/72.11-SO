#ifndef SCHEDULER_H
#define SCHEDULER_H
#include "pcb.h"
typedef struct fifo{
    pcb * function;
    struct fifo * next;
    struct fifo * prev;
}fifo;

void * createProcess(char * name, int * state, function * function);
#endif