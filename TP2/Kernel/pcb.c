#include "include/pcb.h"
#include "include/MemManager.h"
#include "include/Curses.h"
#include "include/String.h"

#define NULL 0
#define MAX_PROC 20

static int pid = 0;

uint64_t stck[MAX_PROC][STACK];
pcb pcbs[MAX_PROC];
int cant = 0;

int findProcess(int pid);

void LoadPCB(pcb * pcb,uint64_t * stack, char * name, int * status, function_t *function,int pid,int parentPid){

    CopyString(name, pcb->name, strlen(name));
    pcb->pid = pid++;
    pcb->priority = 1;
    pcb->pidP=parentPid;

    /// Copio argumentos a pcb

    pcb->argv = malloc(function->argc * sizeof(char *));

    for(int j = 0 ; j < function->argc; j++){
        int t;
        for(t = 0 ; function->args[j][t] !=0 ; t++)

        pcb->argv[j] = malloc((t+1) * sizeof(char));
        CopyString(function->args[j],pcb->argv[j],(t+1));
    }

    pcb->argc = function->argc;
    pcb->isWaitingForInput = false;


    /// Continuo


    pcb->stack = stack;
    pcb->state = READY;
    pcb->status = *status;

    // Set up stack

    pcb->sp = stack + STACK - 1;


    *(pcb->sp--) = 0; //ss
    pcb->bp = pcb->sp + 1;
    *(pcb->sp--) = pcb->sp + 1; // pongo el sp al tope del stack?? PREGUNTAR
    *(pcb->sp--) = 0x202; // flags
    *(pcb->sp--) = 0x8; // CS
    *(pcb->sp--) = function->function; //rip

    *(pcb->sp--) = 1;              //rax
    *(pcb->sp--) = 2;              //rbx
    *(pcb->sp--) = 3;              //rcx
    *(pcb->sp--) = 4;              //rdx
    *(pcb->sp--) = pcb->bp;       //rbp
    *(pcb->sp--) = function->argc; //rdi
    *(pcb->sp--) = pcb->argv;   // rsi        
    *(pcb->sp--) = 8;              //r8
    *(pcb->sp--) = 9;              //r9
    *(pcb->sp--) = 10;              //r10
    *(pcb->sp--) = 11;              //r11
    *(pcb->sp--) = 12;              //r12
    *(pcb->sp--) = 13;              //r13
    *(pcb->sp--) = 14;              //r14
    *(pcb->sp) = 15;              //r15



}

pcb *create(char *name, int *status, function_t *function,int pidp)
{
    if (cant == MAX_PROC)
    {
        *status = -1;
        return NULL;
    }

    int i;
    cant++;
    for (i = 0; i < MAX_PROC && pcbs[i].state != KILL; i++);
    
    LoadPCB(&pcbs[i],stck[i],name,status,function,pid++,pidp);

    return &pcbs[i];
}

void kill(int *pid)
{
    int i = findProcess(*pid);
    if (i != -1)
    {
        pcbs[i].state = KILL;
        for(int j = 0 ; j < pcbs[i].argc ; j++){
            free(pcbs[i].argv[j]);
        }

        free(pcbs[i].argv);
        cant--;
        return;
    }
    DEBUG("KILL Failed%s","")
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
        //pcbs[i].status = FOREGROUND;
    }
}

int findProcess(int pid)
{
    int i;

    for (i = 0; i < MAX_PROC && pcbs[i].pid != pid; i++);

    if (i == MAX_PROC)
        return -1;

    return i;
}

void ps()
{
    printf("pid  prioridad   stack        bp     status  estado     nombre\n");
    for (int i = 0; i < MAX_PROC; i++)
    {
        if (pcbs[i].state != KILL)
        {
            printf(" %d      %d      0x%x    0x%x     %d     ", pcbs[i].pid, pcbs[i].priority, pcbs[i].stack,pcbs[i].bp, pcbs[i].status);
            if (pcbs[i].state == READY)
                printf("ready");
            else if(pcbs[i].state == BLOCK)
                printf("block");
            else 
                printf("waiting");
            printf("    %s\n",pcbs[i].name);    
        }
    }
}

