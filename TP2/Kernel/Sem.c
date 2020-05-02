#include "include/Sem.h"
#include "include/Mutex.h"
#include "include/Curses.h"
#include "include/String.h"
#include "include/Scheduler.h"

SemData_t sems[MAX];

int lookSem(char * name);

SemData_t * semopen(char * name){
    //NO SE SI VA A FUNCIONAR
    int id=lookSem(0);
    
    if(id==MAX)
        return -1;

    sems[id].id=id+1;
    sems[id].lock=UNLOCK;
    sems[id].cant++;
    CopyString(name, sems[id].name, strlen(name));
    return &sems[id];
}

void semwait(SemData_t * sem);

void sempost(SemData_t * sem){
    //¿Habría que chequear esto?¿Miramos si es de verdad un sem o es trabajo del usuario?
    sem->lock=UNLOCK;
}

void semclose(SemData_t * sem){
    sem->cant--;
    if(sem->cant==0)
        CopyString(0, sem->name, 1);
}

int lookSem(char * name){
    int i;
    for(i=0;i<MAX && !strcmp(name,sems[i].name);i++);
    return i;
}