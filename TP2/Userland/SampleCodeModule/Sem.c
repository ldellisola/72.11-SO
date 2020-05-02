#include "../Include/Sem.h"
#include "../Include/Syscalls.h"

sem_t semopen(char * name){
    sem_t aux;
    sem(0,(void *)name,(void **)&aux);
    return aux;
}

void semwait(sem_t semp){
    
    sem(1,(void *) sem,(void **)&semp);
}

void sempost(sem_t semp){

    sem(2,(void *) sem,(void **)&semp);
    
}

void semclose(sem_t semp){
    sem(3,(void *) sem,(void **)&semp);
    
}