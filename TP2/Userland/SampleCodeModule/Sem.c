#include "../Include/Sem.h"
#include "../Include/Syscalls.h"
#include "../Include/Curses.h"
#include <stdbool.h>

void extern spin_lock();

void extern spin_unlock();

int var=0;

sem_t semopen(char * name){
    sem_t aux;
    sem(0,(void *)name,(void **)&aux);
    return aux;
}

void semwait(void * semp){


    int try;
    spin_lock();
    printf("hola soy %d\n",var++);
    ps();
        //sem(1,(void *) semp,&try);
        
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
    //while(1);    
    spin_unlock();    
    printf("ya salí %d\n",var-1);
}

void sempost(void * semp){
        spin_lock();

    sem(2,(void *) semp,NULL);
            spin_unlock();

    
}

void semclose(void * semp){
    sem(3,(void *) semp,NULL);
    
}

void semInfo(){
    sem(4,NULL,NULL);
}