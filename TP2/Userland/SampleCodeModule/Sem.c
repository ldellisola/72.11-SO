#include "../Include/Sem.h"
#include "../Include/Syscalls.h"
#include "../Include/Curses.h"
#include <stdbool.h>



int var = 0;

sem_t semopen(char *name)
{
    sem_t aux;
    sem(0, (void *)name, (void **)&aux);
    return aux;
}

void semwait(void *semp)
{
    bool hasToBeBlocked = true;
    sem(1, (void *)semp, &hasToBeBlocked);

    // if(hasToBeBlocked){
    //     int pid = getpid();
    //     BlockAndSwitchProcess(&pid);
    // }
    
}

void sempost(void *semp)
{
    sem(2, (void *)semp, NULL);
}

void semclose(void *semp)
{
    sem(3, (void *)semp, NULL);
}

void semInfo(int argc, char ** argv)
{
    sem(4, NULL, NULL);
}