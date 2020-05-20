#ifndef SEM_H
#define SEM_H

#include <stdbool.h>
#define MAX_PROC_SEM 20 //maximos procesos por sem

typedef struct
{
    int id;
    char name[1024];
    int value;
    int cant;
    int processesBlocked[MAX_PROC_SEM];
} SemData_t;

int semopen(char * name, int * initialValue);

bool semwait(char * sem);

int sempost(char * sem);

void semclose(char * sem);

void semInfo();

#endif