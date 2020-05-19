#ifndef SCHEDULER_H
#define SCHEDULER_H
#include "pcb.h"
#include <stdbool.h>

typedef void (*process_Func_t)(int, char**);


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

process * roundRobin();

process * GetDummyProcess();

void setDummyProcess( process_Func_t func);


void AwakeAllProcesses();

process * GetCurrentProcess();

process * GetProcess(int pid);

void createProcess(char * name, int * status, function_t * function);

void killProcess(int * pid);

void blockProcess(int * pid);

void niceProcess(int * pid, int priority);

void killCurrentForegroundProcess();

int getpid();

void Exit();

#endif