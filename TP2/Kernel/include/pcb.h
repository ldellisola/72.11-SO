#ifndef PCB_H
#define PCB_H
#include "deviceInfo.h"

#define MAX_NAME 50


typedef struct{
    int (*function)();
    int argc;
    char ** args;
}function_t;
typedef enum {KILL,READY,BLOCK,WAITING_INPUT}State;
typedef enum {FOREGROUND,BACKGROUND}Status;

typedef struct{
    char name[MAX_NAME];
    int pid;
    int priority;
    uint64_t * stack;
    uint64_t * bp; //base pointer
    uint64_t * sp;
    Status status; //foreground  background
    int pidP;
    State state; 
    char ** argv;
    int argc;
}pcb;

pcb * create(char * name, int * status, function_t * function,int pidp);

void kill(int * pid);

void block (int *pid);

void unlock(int pid);

void nice(int * pid, int pr);

void ps();
#endif