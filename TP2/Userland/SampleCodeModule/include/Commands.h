#ifndef COMMANDS_H
#define COMMANDS_H


#include <stdarg.h>

#include <stdint.h>

void semTest(int argc, char ** argv);
void SemTestPrint(int argc, char ** argv);

void printMem(int argc, char ** argv);

extern int infoReg(int argc, char **argv);

int time(int argc, char **argv);

int help(int argc, char **argv);

int killProcess(int argc, char **argv);

int niceProcess(int argc, char ** argv);

int blockProcess(int argc, char ** argv);

int ProcessState(int argc, char ** argv);

int quotient(int argc, char ** argv);

int invalidOpcode(int argc, char **argv);

int malloc_test(int argc, char ** argv);

void fillString(char * test);

int printMemoryState(int argc, char ** argv);


#endif