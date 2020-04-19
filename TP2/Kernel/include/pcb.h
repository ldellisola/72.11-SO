#ifndef PCB_H
#define PCB_H
#include "deviceInfo.h"

#define MAX_NAME 50


typedef struct{
    int (*function)();
    int argc;
    char ** args;
}function;
typedef enum {KILL,READY,BLOCK}State;
typedef enum {FOREGROUND,BACKGROUND}Status;

typedef struct{
    char name[MAX_NAME];
    int pid;
    int priority;
    void * stack;
    void * bp; //base pointer
    Status status; //foreground  background
    Registers registers;
    State state; 
}pcb;

pcb * create(char * name, int * status, function * function);

int kill(int * pid);

void block (int *pid);

int nice(int * pid, int pr);

void ps();
#endif