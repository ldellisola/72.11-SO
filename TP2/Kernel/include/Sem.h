#ifndef SEM_H
#define SEM_H

#define MAX 20 //maximos procesos por sem

typedef struct
{
    int id;
    char name[1024];
    int lock;
    int procs[MAX];
} SemData_t;


SemData_t * semopen(char * name);

void semwait(SemData_t * sem);

int sempost(SemData_t * sem);

int semclose(SemData_t * sem);

#endif