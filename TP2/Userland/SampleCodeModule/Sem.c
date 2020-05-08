#include "../Include/Sem.h"
#include "../Include/Syscalls.h"
#include "../Include/Curses.h"
#include <stdbool.h>

void extern spin_lock();

void extern spin_unlock();

int var = 0;

sem_t semopen(char *name)
{
    sem_t aux;
    sem(0, (void *)name, (void **)&aux);
    return aux;
}

void semwait(void *semp)
{
    bool try = true;
    do
    {
        spin_lock();
        //printf("Hola %d\n",getpid());
        sem(1, (void *)semp, &try);
        //printf("Sali %d y devolvio %d\n",getpid(),try);
        spin_unlock();
        if(try){
            int pid=getpid();
            block_process(&pid);
            __asm__("hlt");
            __asm__("hlt");
            __asm__("hlt");
            __asm__("hlt");
            __asm__("hlt");
            __asm__("hlt");
            __asm__("hlt");
            __asm__("hlt");
            __asm__("hlt");
            __asm__("hlt");
            __asm__("hlt");
            __asm__("hlt");
        }
        //DEBUG("checkeando %d\n",getpid());
        
    } while (try);
    //DEBUG("chau %d\n",getpid());
    
}

void sempost(void *semp)
{
    spin_lock();

    sem(2, (void *)semp, NULL);
    spin_unlock();
}

void semclose(void *semp)
{
    sem(3, (void *)semp, NULL);
}

void semInfo()
{
    sem(4, NULL, NULL);
}