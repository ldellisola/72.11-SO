#ifndef PCB_H
#define PCB_H
#include "deviceInfo.h"

#define MAX_NAME 50


typedef struct{
    int (* function)(int, char **);
    int argc;
    char ** args;
    int fd[2];
}function_t;
typedef enum {KILL,READY,BLOCK,WAITING_INPUT}State;
typedef enum {FOREGROUND,BACKGROUND}Status;

#define STDIN 0
#define STDOUT 1

typedef struct{
    char name[MAX_NAME];
    int pid;
    int priority;
    uint64_t * stack;
    uint64_t * bp; //base pointer
    uint64_t * sp;
    Status status; //foreground  background
    int pidP;
    int fd[2];
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

int getFd(int pid,int action);

#endif