#include "../Include/Sem.h"
#include "../Include/Syscalls.h"

sem_t semopen(char * name){
    sem_t aux;
    sem(0,(void *)name,(void **)&aux);
    return aux;
}

void semwait(sem_t semp){
    int aux;
    sem(1,(void *) sem,(void *)&aux);
}

int sempost(sem_t semp){
    int aux;
    int * paux=&aux;
    sem(2,(void *) sem,(void **)&paux);
    return aux;
}

int semclose(sem_t semp){
    int aux;
    int * paux=&aux;
    sem(3,(void *) sem,(void **)&paux);
    return aux;
}