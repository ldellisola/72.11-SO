#ifndef PCB_H
#define PCB_H
#include "deviceInfo.h"
#include <stdbool.h>

#define MAX_NAME 50

#define STACK 0x300

typedef struct{
    int (* function)(int, char **);
    int argc;
    char ** args;
    int read;
    int write;
}function_t;
typedef enum {KILL,READY,BLOCK}State;
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

void LoadPCB(pcb * pcb,uint64_t * stack, char * name, int * status, function_t *function,int pid,int parentPid);

pcb * create(char * name, int * status, function_t * function,int pidp);

void kill(int * pid);

void block (int *pid);

void unlock(int pid);

void nice(int * pid, int pr);

void ps();

int getFd(int pid,int action);

#endif