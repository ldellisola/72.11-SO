#ifndef SEM_H
#define SEM_H

typedef enum{LOCK,UNLOCK} lock;
#define MAX 20 //maximos procesos por sem

typedef struct
{
    int id;
    char name[1024];
    lock lock;
    int cant;
    int block[MAX];
} SemData_t;


SemData_t * semopen(char * name);

void semwait(SemData_t * sem);

void sempost(SemData_t * sem);

void semclose(SemData_t * sem);

#endif