#include "include/pcb.h"
#include "include/MemManager.h"
#include "include/Curses.h"
#include "include/String.h"

#define MAX 20
#define STACK 0x300
#define NULL 0
static int pid = 0;

uint64_t stck[MAX][STACK];
pcb pcbs[MAX];
int cant = 0;

int findProcess(int pid);

pcb *create(char *name, int *status, function_t *function,int pidp)
{
    if (cant == MAX)
    {
        *status = -1;
        return NULL;
    }

    int i;
    cant++;
    for (i = 0; i < MAX && pcbs[i].state != KILL; i++);
    
    CopyString(name, pcbs[i].name, strlen(name));
    pcbs[i].pid = pid++;
    pcbs[i].priority = 1;
    pcbs[i].pidP=pidp;


    pcbs[i].stack = stck[i];
    pcbs[i].state = READY;
    pcbs[i].status = *status;

    // Set up stack
    pcb *proc = &pcbs[i];

    proc->sp = stck[i] + STACK - 1;

    *(proc->sp--) = 0; //ss
    proc->bp = proc->sp + 1;
    *(proc->sp--) = proc->sp + 1; // pongo el sp al tope del stack?? PREGUNTAR
    *(proc->sp--) = 0x202; // flags
    *(proc->sp--) = 0x8; // CS
    *(proc->sp--) = function->function; //rip

    *(proc->sp--) = 0;              //rax
    *(proc->sp--) = 0;              //rbx
    *(proc->sp--) = 0;              //rcx
    *(proc->sp--) = 0;              //rdx
    *(proc->sp--) = proc->bp;       //rbp
    *(proc->sp--) = function->argc; //rdi
    *(proc->sp--) = function->args; // rsi        
    *(proc->sp--) = 0;              //r8
    *(proc->sp--) = 0;              //r9
    *(proc->sp--) = 0;              //r10
    *(proc->sp--) = 0;              //r11
    *(proc->sp--) = 0;              //r12
    *(proc->sp--) = 0;              //r13
    *(proc->sp--) = 0;              //r14
    *(proc->sp) = 123;              //r15

    return &pcbs[i];
}

void kill(int *pid)
{
    int i = findProcess(*pid);
    if (i != -1)
    {
        pcbs[i].state = KILL;
        free(pcbs[i].stack);
        return;
    }
    *pid = -1;
}

void nice(int *pid, int pr)
{
    int i = findProcess(*pid);
    if (i != -1)
    {
        pcbs[i].priority = pr;
        return;
    }
    *pid = -1;
}

void block(int *pid)
{
    int i = findProcess(*pid);
    if (i != -1)
    {
        if (pcbs[i].state == READY)
            pcbs[i].state = BLOCK;
        else
            pcbs[i].state = READY;
    }
    else
        *pid = -1;
}
void unlock(int pid){
    int i=findProcess(pid);
    if(i!=-1){
        pcbs[i].state=READY;
    }
}

int findProcess(int pid)
{
    int i;

    for (i = 0; i < MAX && pcbs[i].pid != pid; i++)
            ;

    if (i == MAX || pcbs[i].state == KILL)
        return -1;

    return i;
}

void ps()
{
    printf("pid  prioridad   stack        bp     status  estado     nombre\n");
    for (int i = 0; i < MAX; i++)
    {
        if (pcbs[i].state != KILL)
        {
            printf(" %d      %d      0x%x    0x%x     %d     ", pcbs[i].pid, pcbs[i].priority, pcbs[i].stack,pcbs[i].bp, pcbs[i].status);
            if (pcbs[i].state == READY)
                printf("ready");
            else
                printf("block");
            printf("    %s\n",pcbs[i].name);    
        }
    }
}
