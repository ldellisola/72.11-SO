#ifndef SEM_H
#define SEM_H

#include <stdbool.h>

/***************************************************************/
/*                        Constantes                           */
/***************************************************************/

//maximos procesos por sem
#define MAX_PROC_SEM 20

/***************************************************************/
/*                        Estructuras                          */
/***************************************************************/

typedef struct
{
    int id;
    char name[1024];
    int value;
    int cant;
    int processesBlocked[MAX_PROC_SEM];
} SemData_t;

/***************************************************************/
/*                 Functiones Publicas                         */
/***************************************************************/

//  Creates or opens a semaphore. It the semaphore already existed it will
//  ignore the initial value
int semopen(char *name, int *initialValue);

//  It will wait on the semaphore until it can access it
bool semwait(char *sem);

//  It will post the semaphore
void sempost(char *sem);

//  It will close the semafore if no one else is using it.
void semclose(char *sem);

//  It prints information about the semaphores.
void semInfo();

#endif