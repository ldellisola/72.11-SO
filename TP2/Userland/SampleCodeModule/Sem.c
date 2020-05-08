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


    int try;

    while (!__sync_bool_compare_and_swap(&try,0,1))
    {
        while(try)
            __builtin_ia32_pause();    
    }
    sem(1,(void *) semp,&try);
    
    // do{
    //     // spin_lock();
    //     __asm__("cli");

    //     sem(1,(void *) semp,&try);
    //    __asm__("sti");
    //    // spin_unlock();
    //     // for(int i = 0 ; i < 9999999 ; i++);

    //     if(try){
    //         // DEBUG("ANTES DE HALT%s","")
    //         __asm__("hlt");

    //         // DEBUG("DESP DE HALT%s","")

    //     }

    // }while(try);
    
}

void sempost(void * semp){
        spin_lock();

    sem(2,(void *) semp,NULL);
            spin_unlock();

    
}

void semclose(void * semp){
    sem(3,(void *) semp,NULL);
    
}