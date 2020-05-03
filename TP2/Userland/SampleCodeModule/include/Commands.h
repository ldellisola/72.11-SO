#ifndef COMMANDS_H
#define COMMANDS_H
#include <stdarg.h>

#include <stdint.h>

void semTest(int argc, char ** argv);

int printMem(uint64_t memDirection);

extern int infoReg();

int time();

int help();

int quotient(int a, int b);

int invalidOpcode();

int help();

int explainCommand(char * command);

int malloc_test();
void fillString(char * test);

int printMemoryState();

void test_mm();

#endif