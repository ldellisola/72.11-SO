#ifndef COMMANDS_H
#define COMMANDS_H
#include <stdarg.h>

#include <stdint.h>

int printMem(uint64_t memDirection);

extern int infoReg();

int time();

int help();

int quotient(int a, int b);

int invalidOpcode();

int man();

int explainCommand(char * command);




#endif