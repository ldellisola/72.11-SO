#ifndef COMMANDS_H
#define COMMANDS_H
#include <stdarg.h>

#include <stdint.h>

void semTest(int argc, char ** argv);
void SemTestPrint(int argc, char ** argv);

void printMem(int argc, char ** argv);

extern int infoReg();

void time();

void help();

void killProcess(int argc, char **argv);

void niceProcess(int argc, char ** argv);

void blockProcess(int argc, char ** argv);

void ProcessState(int argc, char ** argv);

void quotient(int argc, char ** argv);

void invalidOpcode();

void malloc_test(int argc, char ** argv);

void fillString(char * test);

void printMemoryState(int argc, char ** argv);


#endif