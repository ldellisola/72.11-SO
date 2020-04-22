#include "include/pcb.h"
#include "include/MemManager.h"
#include "include/Curses.h"
#include "include/String.h"

#define MAX 20
#define STACK 10000
#define NULL 0
static int pid = 0;

pcb pcbs[MAX];
int cant = 0;

int findProcess(int pid);

pcb *create(char *name, int *status, function_t *function)
{
    if (cant == MAX)
    {
        *status = -1;
        return NULL;
    }

    int i;
    cant++;
    for (i = 0; i < MAX && pcbs[i].state != KILL; i++)
        ;
    CopyString(name, pcbs[i].name, strlen(name));
    pcbs[i].pid = pid++;
    pcbs[i].priority = 1;

    uint64_t *stack = malloc(0x1000);

    // for(int i = 0x1000-1 ; i >=0 ;i--){
    //     stack[i]=0x1000-1 - i;
    // }

    pcbs[i].stack = stack;
    pcbs[i].state = READY;
    pcbs[i].status = *status;

    // Set up stack
    pcb *proc = &pcbs[i];

    //DEBUG("Stack TOP en 0X%x", stack);

    proc->sp = stack + 0x1000 - 1;

    //DEBUG("Stack Base en 0X%x", proc->sp);

    *(proc->sp--) = 0; //ss

    proc->bp = proc->sp + 1;
    *(proc->sp--) = proc->sp + 1; // pongo el sp al tope del stack?? PREGUNTAR

    *(proc->sp--) = 0x202; // flags

    *(proc->sp--) = 0x8; // CS

    *(proc->sp--) = function->function; //rip

    *(proc->sp--) = 0; //rax

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

    DEBUG("Stacj pointer en: 0x%x", proc->sp)
    //DEBUG("Stacj pointer Contiene a %d", *proc->sp)

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

int findProcess(int pid)
{
    int i;

    if (pid != 0)
        for (i = 0; i < MAX && pcbs[i].pid != pid; i++)
            ;

    if (pid == 0 || i == MAX || pcbs[i].state == KILL)
        return -1;

    return i;
}

void ps()
{
    printf("nombre  pid prioridad stack  bp  status registros estado\n");
    for (int i = 0; i < MAX; i++)
    {
        if (pcbs[i].state != KILL)
        {
            printf("%s      %d     %d       --    --     %d     --      ", pcbs[i].name, pcbs[i].pid, pcbs[i].priority, pcbs[i].status);
            if (pcbs[i].state == READY)
                printf("ready\n");
            else
                printf("block\n");
        }
    }
}
