#ifndef PCB_H
#define PCB_H
#include "deviceInfo.h"


typedef struct{
    int (*function)();
    int argc;
    char ** args;
}function;
typedef enum {KILL,READY,BLOCK}State;

typedef struct{
    char * name;
    int pid;
    int priority;
    void * stack;
    void * bp; //base pointer
    int status; //foreground  background
    Registers registers;
    State state; 
}pcb;

pcb * create(char * name, int * state, function * function);
void * kill(pcb * process);
#endif