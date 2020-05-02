#ifndef SEM_H
#define SEM_H
typedef void * sem_t;

sem_t semopen(char * name);

void semwait(sem_t semp);

int sempost(sem_t semp);

int semclose(sem_t semp);

#endif