#ifndef SCHEDULER_H
#define SCHEDULER_H
#include "pcb.h"

typedef struct process{
    pcb * pcb;
    struct process * next;
    struct process * prev;
}process;
typedef struct Priority{
    int cant;
    process * first;
    process * last;
} Priority;

void createProcess(char * name, int * state, function * function);

void killProcess(int * pid);
#endif