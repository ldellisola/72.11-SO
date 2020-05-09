#ifndef SCHEDULER_H
#define SCHEDULER_H
#include "pcb.h"
#include <stdbool.h>


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

void roundRobin();

void AwakeAllProcesses();

process * GetCurrentProcess();

process * GetProcess(int pid);

void createProcess(char * name, int * status, function_t * function);

void killProcess(int * pid);

void blockProcess(int * pid);

void niceProcess(int * pid, int priority);

int getpid();

void Exit();

#endif