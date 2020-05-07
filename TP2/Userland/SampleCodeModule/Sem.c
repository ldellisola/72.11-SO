#include "../Include/Sem.h"
#include "../Include/Syscalls.h"
#include "../Include/Curses.h"
#include <stdbool.h>

void extern spin_lock();

void extern spin_unlock();


sem_t semopen(char * name){
    sem_t aux;
    sem(0,(void *)name,(void **)&aux);
    return aux;
}

void semwait(void * semp){


    bool try = true;
    
    do{
        spin_lock();

        while(1);

        sem(1,(void *) semp,&try);
        spin_unlock();
        // for(int i = 0 ; i < 9999999 ; i++);

        if(try){
            // DEBUG("ANTES DE HALT%s","")
            __asm__("hlt");
            __asm__("hlt");
            // DEBUG("DESP DE HALT%s","")

        }

    }while(try);
    
}

void sempost(void * semp){
        spin_lock();

    sem(2,(void *) semp,NULL);
            spin_unlock();

    
}

void semclose(void * semp){
    sem(3,(void *) semp,NULL);
    
}