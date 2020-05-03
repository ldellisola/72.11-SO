#include "../Include/Sem.h"
#include "../Include/Syscalls.h"

sem_t semopen(char * name){
    sem_t aux;
    sem(0,(void *)name,(void **)&aux);
    return aux;
}

void semwait(void * semp){
    
    sem(1,(void *) semp,NULL);
}

void sempost(void * semp){

    sem(2,(void *) semp,NULL);
    
}

void semclose(void * semp){
    sem(3,(void *) semp,NULL);
    
}