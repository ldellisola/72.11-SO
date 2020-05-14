#ifndef SEM_H
#define SEM_H
//typedef void * sem_t;
#include <stdarg.h>
#include <stdint.h>

uint64_t semopen(char * name,uint64_t initValue);

uint64_t semwait(char * semp);

uint64_t sempost(char * semp);

uint64_t semclose(char * semp);

void semInfo(int argc, char ** argv);

#endif