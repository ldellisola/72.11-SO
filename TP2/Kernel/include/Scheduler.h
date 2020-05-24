#ifndef SCHEDULER_H
#define SCHEDULER_H
#include "pcb.h"
#include <stdbool.h>

/***************************************************************/
/*                      Estructuras                            */
/***************************************************************/

typedef int (*process_Func_t)(int, char **);

typedef struct process
{
    pcb *pcb;
    struct process *next;
    struct process *prev;
} process;

typedef struct Priority
{
    int cant;
    process *first;
    process *last;
} Priority;

/***************************************************************/
/*                 Functiones Publicas                         */
/***************************************************************/

//  It allows a process blocked by STDINT to resume working.
//  It will put said process as the next in line to execute.
void AwakeProcess();

//  It sets up a dummy process to run in the background when all other processes are
//  blocked.
void setDummyProcess(process_Func_t func);

//  It returns a pointer to the Dummy process
process *GetDummyProcess();

//  It calculates and returns the next process that must be executed.
//  If all processes are blocked it will return the dummy process
process *roundRobin();

//  It returns the process that is currently running
process *GetCurrentProcess();

//  It returns a process by its pid
process *GetProcess(int pid);

//  It creates a process
void createProcess(char *name, int *status, function_t *function);

//  It kills a process by its pid
//! It won't kill the terminal (pid 0)
void killProcess(int *pid);

//  It blocks a process by its pid
//! It won't block the terminal (pid 0)
void blockProcess(int *pid);

//  It changes the priority of a process
//! It won't affect the terminal (pid 0)
void niceProcess(int *pid, int priority);

//  It returns the PID of the process that is currently running.
int getpid();

//  It safely stops and exits the process that is currently running.
//! It won't stop the terminal
void Exit();

//  It blocks a process until new input from the keyboard is found.
void SleepProcess();

#endif