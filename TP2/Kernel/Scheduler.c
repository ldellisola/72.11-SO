#include <stdio.h>
#include "include/Scheduler.h"

#define quantum 20/1000

fifo * priorities[3];

void RoundRobin();

void * createProcess(char * name, int * state, function * function){
    pcb * new=create(name,state,function);
    if(new!=NULL){
        //checkear status
        //bloquear al que esta corriendo y correr a este
    }
    
}