#ifndef SEM_H
#define SEM_H
typedef void * sem_t;

sem_t semopen(char * name);

void semwait(void * semp);

void sempost(void * semp);

void semclose(void * semp);

void semInfo();

#endif