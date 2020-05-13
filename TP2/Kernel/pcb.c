#include "include/pcb.h"
#include "include/MemManager.h"
#include "include/Curses.h"
#include "include/String.h"
#include "include/Pipe.h"

#define STACK 0x300
#define NULL 0
#define MAX_PROC 20

static int pid = 0;

uint64_t stck[MAX_PROC][STACK];
pcb pcbs[MAX_PROC];
int cant = 0;

int findProcess(int pid);

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
    
    CopyString(name, pcbs[i].name, strlen(name));
    pcbs[i].pid = pid++;
    pcbs[i].priority = 1;
    pcbs[i].pidP=pidp;

    /// Copio argumentos a pcb

    pcbs[i].argv = malloc(function->argc * sizeof(char *));

    for(int j = 0 ; j < function->argc; j++){
        int t;
        for(t = 0 ; function->args[j][t] !=0 ; t++)

        pcbs[i].argv[j] = malloc((t+1) * sizeof(char));
        CopyString(function->args[j],pcbs[i].argv[j],(t+1));
    }

    pcbs[i].argc = function->argc;



    /// Continuo


    pcbs[i].stack = stck[i];
    pcbs[i].state = READY;
    pcbs[i].status = *status;
    int read=function->fd[READ];
    int write=function->fd[WRITE];
    pcbs[i].fd[READ]=read==-1?STDIN:read;
    pcbs[i].fd[WRITE]=write==-1?STDOUT:write;

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
    *(proc->sp--) = pcbs[i].argv;   // rsi        
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
        
        //cierro los pipes desde aca
        if(pcbs[i].fd[READ]!=STDIN)
            closePipes(pcbs[i].fd[READ]);
        if(pcbs[i].fd[WRITE]!=STDOUT)
            closePipes(pcbs[i].fd[WRITE]);  

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
    }
}

int getFd(int pid,actions action){
    int i=findProcess(pid);
    if(i==-1)
        return i;
    return pcbs[i].fd[action];
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

