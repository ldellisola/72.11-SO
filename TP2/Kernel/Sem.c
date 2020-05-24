#include "include/Sem.h"
#include "include/Curses.h"
#include "include/String.h"
#include "include/Scheduler.h"
#include "include/SpinLock.h"
#include <stdlib.h>

/***************************************************************/
/*                     Functiones ASM                          */
/***************************************************************/

extern void __ForceTimerTick__();

/***************************************************************/
/*                        Constantes                           */
/***************************************************************/

#define MAX 20
#define NO_VALUE -1

/***************************************************************/
/*                        Variables                            */
/***************************************************************/

SemData_t sems[MAX];

/***************************************************************/
/*                       Declaraciones                         */
/***************************************************************/

int lookSem(char *name);
int GetSemaphoreByName(char *name);
int FindUnusedSemaphore();
int semCheck(SemData_t *sem);
SemData_t *getSem(char *name);

/***************************************************************/
/*                 Functiones Publicas                         */
/***************************************************************/

int semopen(char *name, int *initialValue)
{
    SpinLock();
    int pos = GetSemaphoreByName(name);

    if (pos == -1)
    {
        // Creo el semaforo
        pos = FindUnusedSemaphore();

        if (pos == -1)
        {
            ERROR("All semaphores are occupied", 0)
            return -1;
        }

        sems[pos].id = pos + 1;
        sems[pos].value = *initialValue;
        sems[pos].cant = 0;

        for (int i = 0; i < MAX_PROC_SEM; i++)
        {
            sems[pos].processesBlocked[i] = NO_VALUE;
        }

        CopyString(name, sems[pos].name, strlen(name));
    }
    sems[pos].cant++;

    SpinUnlock();
    return 0;
}

bool semwait(char * semName){

    SemData_t * sem = &sems[GetSemaphoreByName(semName)];

    bool hasToBeBlocked = true;

    if (semCheck(sem) != 0)
    {
        ERROR("Waiting semaphore", 0)
        return false;
    }
    
    SpinLock(); 
    if(sem->value < 1){
        int pid = getpid();
        int i = 0;

        do
        {
            if (sem->processesBlocked[i] == NO_VALUE)
            {
                sem->processesBlocked[i] = pid;
            }
        } while (sem->processesBlocked[i++] != pid);

        block(&pid);

        if (pid != getpid())
        {
            ERROR("blocking process %d on semaphore", pid)
        }

    }else{
        hasToBeBlocked =  false;
        sem->value--;
    }
    else
    {
        hasToBeBlocked = false;
    }
    SpinUnlock();

    if (hasToBeBlocked)
    {
        __ForceTimerTick__();
    }

    return hasToBeBlocked;
}

void sempost(char * semName){
    SemData_t * sem = &sems[GetSemaphoreByName(semName)];

    if (semCheck(sem) != 0)
    {
        ERROR("Posting semaphore", 0);
        return;
    }
    SpinLock(); 
    if (sem->processesBlocked[0] != NO_VALUE) {
    // desbloqueo el primero, debido al Queue
    process * p = GetProcess(sem->processesBlocked[0]);
            p->pcb->state = READY;
    // muevo toda la queue uno hacia adelante y actualizo el último
    for(int i = 0 ; i < MAX_PROC_SEM-1; i++) {
        sem->processesBlocked[i] = sem->processesBlocked[i+1];
        }
        sem->processesBlocked[MAX_PROC_SEM - 1] = NO_VALUE;
    }
    else sem->value++;
    SpinUnlock();
}

void semclose(char *semName)
{
    SemData_t *sem = getSem(semName);

    if (semCheck(sem) != 0)
    {
        ERROR("Closing semaphore", 0);
        return;
    }
    sem->cant--;
    if (sem->cant == 0)
    {
        CopyString(0, sem->name, 1);
        sem->id = 0;
    }
}

int GetSemaphoreByName(char *name)
{
    for (int i = 0; i < MAX_PROC_SEM; i++)
    {
        if (strcmp(name, sems[i].name))
        {
            return i;
        }
    }

    return -1;
}

int FindUnusedSemaphore()
{

    for (int i = 0; i < MAX_PROC_SEM; i++)
    {
        if (sems[i].id == 0)
        {
            return i;
        }
    }

    return -1;
}

int semCheck(SemData_t *sem)
{
    int i;
    if (sem == NULL || sem->name == NULL)
    {
        ERROR("Sem name was null", 0);
        return -1;
    }
    else if ((i = lookSem(sem->name)) == -1)
    {
        ERROR("Sem could not be found", 0);
        return -1;
    }
    return 0;
}

int lookSem(char *name)
{
    int i;
    for (i = 0; i < MAX_PROC_SEM; i++)
    {
        if (strcmp(name, sems[i].name))
        {
            return i;
        }
    };
    return -1;
}

void semInfo()
{
    int i;
    printf("\n Id  Value  Cantidad  Nombre\n");
    for (i = 0; i < MAX; i++)
    {
        if (sems[i].id != 0)
        {
            if (sems[i].value < 0)
            {
                int aux = sems[i].value * -1;
                printf("%d -%d %d %s\n", sems[i].id, aux, sems[i].cant, sems[i].name);
            }
            else
                printf("%d %d %d %s\n", sems[i].id, sems[i].value, sems[i].cant, sems[i].name);
        }
    }
}

SemData_t *getSem(char *name)
{
    int index = GetSemaphoreByName(name);
    if (index == -1)
    {
        return NULL;
    }
    SemData_t *ptr = &sems[index];
    return ptr;
}