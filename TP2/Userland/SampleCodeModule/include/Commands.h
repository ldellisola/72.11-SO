#ifndef COMMANDS_H
#define COMMANDS_H


#include <stdarg.h>

#include <stdint.h>


/***************************************************************/
/*                 Functiones Publicas                         */
/***************************************************************/

//  It retrieves the values of the registers
extern int infoReg(int argc, char **argv);

//  It prints thw current time
int time(int argc, char **argv);

//  It kills a process
int killProcess(int argc, char **argv);

//  It changes the priority of a process
int niceProcess(int argc, char ** argv);

//  It blocks a process
int blockProcess(int argc, char ** argv);

//  It prints the state of the states
int ProcessState(int argc, char ** argv);

// divides
int quotient(int argc, char ** argv);

//  throws exception
int invalidOpcode(int argc, char **argv);

//  tests for malloc
int malloc_test(int argc, char ** argv);

//  prints memory state
int printMemoryState(int argc, char ** argv);


#endif