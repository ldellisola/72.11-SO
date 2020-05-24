// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "include/Scheduler.h"
#include "include/MemManager.h"
#include "include/Curses.h"
#include "include/pcb.h"

/***************************************************************/
/*                    Funciones ASM                            */
/***************************************************************/

extern void __ForceTimerTick__();

/***************************************************************/
/*                        Variables                            */
/***************************************************************/

pcb DummyProcessPCB;
process DummyProcess;
uint64_t DummyProcessStack[STACK];

Priority priority;
process *curr = 0;
int currPr = 0;
int hasTodelete = 0;
bool killedCurrentProcess = false;

/***************************************************************/
/*                     Declaraciones                           */
/***************************************************************/

void insertQueue(process *process);
void deleteQueue(int *pid, process **process);

/***************************************************************/
/*                  Funciones Publicas                         */
/***************************************************************/

void AwakeProcess()
{
    process *aux = curr;

    bool found = false;

    for (int i = 0; i < priority.cant; i++)
    {

        if (aux->pcb->state == BLOCK && aux->pcb->isWaitingForInput)
        {
            found = true;
            break;
        }
        else
        {
            aux = aux->next;
        }
    }

    if (found)
    {
        process *next = curr->next;
        pcb *temp = aux->pcb;
        temp->state = READY;
        temp->isWaitingForInput = false;

        aux->pcb = next->pcb;
        next->pcb = temp;
    }
}

void setDummyProcess(process_Func_t func)
{

    int status = BACKGROUND;

    function_t function;
    function.function = func;
    function.argc = 0;
    function.args = NULL;
    function.read = function.write = -1;

    LoadPCB(&DummyProcessPCB, DummyProcessStack, "Dummy", &status, &function, -100, 0);

    DummyProcess.next = NULL;
    DummyProcess.prev = NULL;
    DummyProcess.pcb = &DummyProcessPCB;
}

process *GetDummyProcess()
{
    return &DummyProcess;
}

process *roundRobin()
{
    killedCurrentProcess = false;
    if (priority.cant == 0)
    {
        curr = NULL;
        return curr;
    }

    if (hasTodelete > 0)
    {
        process *aux = curr;

        do
        {
            if (curr->pcb->state == KILL)
            {
                process *aux = curr->prev;
                killProcess(&curr->pcb->pid);
                hasTodelete--;
                curr = aux;
            }
            else
            {
                aux = aux->next;
            }
        } while (aux != curr);
    }

    if (priority.cant == 1)
    {
        curr = priority.first;
        if (curr->pcb->state == BLOCK)
            return GetDummyProcess();
        else
            return curr;
    }

    int counter = 0;
    do
    {
        if (counter++ == priority.cant)
        {
            return GetDummyProcess();
        }
        curr = curr->next;
    } while (curr->pcb->state == BLOCK || curr->pcb->state == KILL);

    return curr;
}

process *GetCurrentProcess()
{
    return killedCurrentProcess ? NULL : curr;
}

process *GetProcess(int pid)
{
    process *p = NULL;
    process *temp = curr;

    do
    {
        if (temp->pcb->pid == pid)
        {
            p = temp;
        }
        else
        {
            temp = temp->next;
        }

        if (temp->pcb == curr->pcb)
        {
            break;
        }

    } while (p == NULL);

    return p;
}

void createProcess(char *name, int *status, function_t *function)
{
    int pidP;
    if (priority.cant == 0)
    {
        pidP = -1;
    }
    else
    {
        pidP = curr->pcb->pid;
    }
    pcb *new = create(name, status, function, pidP);
    if (new != NULL)
    {
        priority.cant++;
        process *procs = (process *)malloc(sizeof(process));
        procs->pcb = new;
        insertQueue(procs);
        //checkear status
        //bloquear al que esta corriendo y correr a este
        if (*status == 0 && pidP != -1)
        {
            int pid = curr->pcb->pid;
            curr->pcb->state = BLOCK;
            procs->pcb->pidP = pid;
        }
        else if (pidP == -1)
        {
            new->priority = 3;
        }
        *status = new->pid;
    }
}

void killProcess(int *pid)
{

    if (*pid == 0)
    {
        WARNING("Terminal can't be killed", 0)
        *pid = -2;
        return;
    }

    kill(pid);
    if (*pid != -1)
    {
        priority.cant--;
        process *process = priority.first;
        deleteQueue(pid, &process);

        if (process->pcb->status == 0)
        {
            int pidP = process->pcb->pidP;
            unlock(pidP);
        }
        free(process);
    }
}

void blockProcess(int *pid)
{
    if (*pid == 0)
    {
        WARNING("Terminal can't be blocked", 0)
        *pid = -2;
        return;
    }
    block(pid);
}

void SleepProcess()
{
    int pid = getpid();

    process *p = GetProcess(pid);

    if (p != NULL)
    {
        p->pcb->isWaitingForInput = true;
        p->pcb->state = BLOCK;
        __ForceTimerTick__();
    }
}

void niceProcess(int *pid, int priority)
{
    if (*pid == 0)
    {
        WARNING("Can't change the priority of the terminal", 0)
        *pid = -2;
        return;
    }

    if (priority < 0 || priority > 2)
    {
        ERROR("The priority indicated is not valid", 0)
        *pid = -3;
        return;
    }

    nice(pid, priority);
}

void Exit()
{
    if (getpid() != 0)
    {
        hasTodelete++;
        curr->pcb->state = KILL;
    }
    else
    {
        WARNING("Can't kill the terminal", 0)
    }
}

int getpid()
{
    return curr->pcb->pid;
}

/***************************************************************/
/*                  Funciones Privadas                         */
/***************************************************************/

void insertQueue(process *procs)
{

    priority.last = procs;
    if (priority.first == NULL)
    {

        priority.first = priority.last;
        priority.first->next = priority.first;
        priority.first->prev = priority.first;
    }

    else
    {
        priority.last->prev = priority.first->prev;
        priority.last->next = priority.first;
        priority.first->prev->next = priority.last;
        priority.first->prev = priority.last;
    }
}
void deleteQueue(int *pid, process **process)
{
    if (priority.cant == 0)
    {
        priority.first = NULL;
        priority.last = NULL;
        return;
    }

    while ((*process)->pcb->pid != *pid)
    {
        *process = (*process)->next;
    }

    (*process)->prev->next = (*process)->next;
    (*process)->next->prev = (*process)->prev;

    if (priority.first->pcb->state == KILL)
    {
        priority.first = priority.first->next;
    }
}
