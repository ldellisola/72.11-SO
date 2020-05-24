// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "include/pcb.h"
#include "include/MemManager.h"
#include "include/Curses.h"
#include "include/String.h"
#include "include/Pipe.h"

/***************************************************************/
/*                      Constantes                             */
/***************************************************************/

#define MAX_PROC 20

/***************************************************************/
/*                        Variables                            */
/***************************************************************/

static int pid = 0;
uint64_t stck[MAX_PROC][STACK];
pcb pcbs[MAX_PROC];
int cant = 0;

/***************************************************************/
/*                      Declaraciones                          */
/***************************************************************/

int findProcess(int pid);

/***************************************************************/
/*                   Funciones Publicas                        */
/***************************************************************/

void LoadPCB(pcb *pcb, uint64_t *stack, char *name, int *status, function_t *function, int pid, int parentPid)
{

    CopyString(name, pcb->name, strlen(name));
    pcb->pid = pid++;
    pcb->priority = 1;
    pcb->pidP = parentPid;

    /// Copio argumentos a pcb

    pcb->argv = malloc(function->argc * sizeof(char *));

    if(pcb->argv == NULL){
        ERROR("Could't allocate memory to copy arguments for process %s",name)
        return;
    }

    for (int j = 0; j < function->argc; j++)
    {
        int t;
        for (t = 0; function->args[j][t] != 0; t++);
        pcb->argv[j] = malloc((t + 1) * sizeof(char));

        if(pcb->argv[j] == NULL){
            ERROR("Could't allocate memory to copy arguments for process %s",name)
        }

        CopyString(function->args[j], pcb->argv[j], (t + 1));
    }

    pcb->argc = function->argc;

    // Armo FDs

    pcb->fd[READ] = function->read == -1 ? STDIN : function->read;
    pcb->fd[WRITE] = function->write == -1 ? STDOUT : function->write;

    pcb->isWaitingForInput = false;

    /// Continuo

    pcb->stack = stack;
    pcb->state = READY;
    pcb->status = *status;

    // Set up stack

    pcb->sp = (stack + STACK) - 1;

    *(pcb->sp--) = 0; //ss
    pcb->bp = pcb->sp + 1;
    *(pcb->sp--) = (uint64_t) pcb->bp;       
    *(pcb->sp--) = 0x202;              // flags
    *(pcb->sp--) = 0x8;                // CS
    *(pcb->sp--) = (uint64_t) function->function; //rip

    *(pcb->sp--) = 1;              //rax
    *(pcb->sp--) = 2;              //rbx
    *(pcb->sp--) = 3;              //rcx
    *(pcb->sp--) = 4;              //rdx
    *(pcb->sp--) = (uint64_t) pcb->bp;        //rbp
    *(pcb->sp--) = (uint64_t) function->argc; //rdi
    *(pcb->sp--) = (uint64_t) pcb->argv;      // rsi
    *(pcb->sp--) = 8;              //r8
    *(pcb->sp--) = 9;              //r9
    *(pcb->sp--) = 10;             //r10
    *(pcb->sp--) = 11;             //r11
    *(pcb->sp--) = 12;             //r12
    *(pcb->sp--) = 13;             //r13
    *(pcb->sp--) = 14;             //r14
    *(pcb->sp) = 15;               //r15
}

pcb *create(char *name, int *status, function_t *function, int pidp)
{
    if (cant == MAX_PROC)
    {
        *status = -1;
        return NULL;
    }

    int i;
    cant++;
    for (i = 0; i < MAX_PROC && pcbs[i].state != KILL; i++);

    LoadPCB(&pcbs[i], stck[i], name, status, function, pid++, pidp);

    return &pcbs[i];
}

void kill(int *pid)
{
    int i = findProcess(*pid);
    if (i != -1)
    {
        pcbs[i].state = KILL;

        //cierro los pipes desde aca
        if (pcbs[i].fd[READ] != STDIN)
            closePipes(&pcbs[i].fd[READ]);
        if (pcbs[i].fd[WRITE] != STDOUT)
            closePipes(&pcbs[i].fd[WRITE]);
        for (int j = 0; j < pcbs[i].argc; j++)
        {
            free(pcbs[i].argv[j]);
        }

        free(pcbs[i].argv);
        cant--;
        return;
    }
    ERROR("Failed to delete PCB of process %d", *pid)
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
    else{
        ERROR("Failed to block PCB of process %d", *pid)
        *pid = -1;
    }
}

void unlock(int pid)
{
    int i = findProcess(pid);
    if (i != -1)
    {
        pcbs[i].state = READY;
    }else
    {
        ERROR("Failed to unlock PCB of process %d", pid)
    }
    
}

int getFd(int pid, int action)
{
    int i = findProcess(pid);
    if (i == -1){
        ERROR("Failed to get File descriptor of process %d", pid)
        return i;
    }
    return pcbs[i].fd[action];
}

void ps()
{
    printf("pid  prioridad   stack        bp     status  estado   fdr  fdw  nombre  Bloqueado por STDINT\n");
    for (int i = 0; i < MAX_PROC; i++)
    {
        if (pcbs[i].state != KILL)
        {
            printf(" %d      %d      0x%p    0x%p      %d     ", pcbs[i].pid, pcbs[i].priority, pcbs[i].stack, pcbs[i].bp, pcbs[i].status);
            if (pcbs[i].state == READY)
                printf("ready");
            else if (pcbs[i].state == BLOCK)
                printf("block");
            else
                printf("waiting");
            printf("    %d   %d", pcbs[i].fd[READ], pcbs[i].fd[WRITE]);
            printf("    %s", pcbs[i].name);

            if (pcbs[i].isWaitingForInput)
            {
                printf("      yes\n");
            }
            else
            {
                printf("      no\n");
            }
        }
    }
}


/***************************************************************/
/*                   Funciones Privadas                        */
/***************************************************************/

int findProcess(int pid)
{
    int i;

    for (i = 0; i < MAX_PROC && pcbs[i].pid != pid; i++);

    if (i == MAX_PROC){
        ERROR("Failed to find PCB of process %d", pid)
        return -1;
    }

    return i;
}
