#ifndef PCB_H
#define PCB_H
#include "deviceInfo.h"
#include <stdbool.h>

/***************************************************************/
/*                        Constantes                           */
/***************************************************************/

#define MAX_NAME 50
#define STACK 0x300

#define STDIN 0
#define STDOUT 1

/***************************************************************/
/*                   Estructuras  y Enums                      */
/***************************************************************/

typedef enum {KILL,READY,BLOCK}State;

typedef enum {FOREGROUND,BACKGROUND}Status;

typedef struct{
    int (* function)(int, char **);
    int argc;
    char ** args;
    int read;
    int write;
}function_t;

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
    bool isWaitingForInput;
}pcb;

/***************************************************************/
/*                   Funciones Publicas                        */
/***************************************************************/



//  It sets up the structure of the PCB for any process.
//  It copies the arguments to allocated memory and sets up the stack
void LoadPCB(pcb * pcb,uint64_t * stack, char * name, int * status, function_t *function,int pid,int parentPid);

//  It creates a PCB in one of the reserved lots of the program.
pcb * create(char * name, int * status, function_t * function,int pidp);

//  It kills the process , freeing all the pipes and memory used to create the process but
//  not the memory allocated by the process during its runtime.
void kill(int * pid);

//  It pauses a process until its resumed
void block (int *pid);

//  It resumes a process
void unlock(int pid);

//  It changes the priority of a process
void nice(int * pid, int pr);

//  It prints information about all running processes
void ps();

//  It return the Read and Write File Descriptors of a given process
int getFd(int pid,int action);

#endif