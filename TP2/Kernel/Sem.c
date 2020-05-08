#include "include/Sem.h"
#include "include/Mutex.h"
#include "include/Curses.h"
#include "include/String.h"
#include "include/Scheduler.h"
#include <stdlib.h>
#define MAX 20
SemData_t sems[MAX];

int lookSem(char * name);
int GetSemaphoreByName(char * name);
int FindUnusedSemaphore();
int semCheck(SemData_t * sem);

SemData_t * semopen(char * name){


    int pos = GetSemaphoreByName(name);

    if(pos == -1){
        // Creo el semaforo
        pos = FindUnusedSemaphore();

        if (pos == -1) {
            printf("All semaphores are occupied\n");
            return NULL;
        }

        sems[pos].id=pos+1;
        sems[pos].lock=UNLOCK;
        sems[pos].cant++;

        for (int i = 0; i < MAX_PROC_SEM; i++)
        {
            sems[pos].processesBlocked[i] = 0;
        }
        
        CopyString(name, sems[pos].name, strlen(name));
    }

    void * ptr = &sems[pos];
    return ptr;
}

void semwait(SemData_t * sem){
    int pid=getpid();
    printf("Entre en wait %d\n",pid);
    if (semCheck(sem) != 0) {
        printf("Error waiting semaphore\n");
        return;
    }
    // printf("Semwait at beginning\n");
    bool try = true;
    
    do{
        printf("entre en el do %d\n",pid);
        spin_lock();
        printf("pase el spin %d\n",pid);
        if(sem->lock == LOCK){
            process * p = GetCurrentProcess();
            
            // if (p->pcb->state == BLOCK){
            //     try = false;
            // }
            
            p->pcb->state = BLOCK;
            
            int i = 0;

            do{
                if(sem->processesBlocked[i] == 0){
                    sem->processesBlocked[i] = p->pcb->pid;
                }
            }while(sem->processesBlocked[i++] != p->pcb->pid);
            
        }else{
            try = false;
            sem->lock = LOCK;
            printf("sem lock %d\n",sem->lock,pid);
        }
        spin_unlock();
        printf("salio del spin y try es %d y %d\n",try,pid);
        /*if(try){
            //__asm__("hlt");
        }*/
    }while(try);
    // printf("Semwait  exited\n");
}

void sempost(SemData_t * sem){
    int pid=getpid();
    printf("Entre en post %d\n",pid);
    
    if (semCheck(sem) != 0) {
        printf("Error posting semaphore\n");
        return;
    }
    // printf("Sempost at beginning\n");
    //¿Habría que chequear esto?¿Miramos si es de verdad un sem o es trabajo del usuario?
    sem->lock=UNLOCK;

    printf("sem unlock %d\n",sem->lock,pid);
    int i = 0;
    for(i = 0 ; i < MAX_PROC_SEM; i++){
        int pid = sem->processesBlocked[i];
        if(pid != 0){
            printf("Desbloqueo a %d\n",pid);
            process * p = GetProcess(sem->processesBlocked[i]);
            p->pcb->state = READY;
            break;
        }
    }
    // printf("Sempost at ending\n");
    return;
}

void semclose(SemData_t * sem){
    if (semCheck(sem) != 0) {
        printf("Error closing semaphore\n");
        return;
    }
    sem->cant--;
    if(sem->cant==0){
        CopyString(0, sem->name, 1);
        sem->id=0;    
    }
}

int GetSemaphoreByName(char * name){
    for(int i = 0; i < MAX_PROC_SEM ; i++){
        if(strcmp(name,sems[i].name)){
            printf("Encontre un sem. Posicion: %d. Nombre: %s\n",i,name);
            return i;
        }
    }

    return -1;
}

int FindUnusedSemaphore(){

    for(int i = 0; i < MAX_PROC_SEM ; i++){
        if(sems[i].id == 0){
            return i;
        }
    }

    return -1;
}

int semCheck(SemData_t * sem) {
    int i;
    if (sem->name == NULL) {
        printf("Sem name was null\n");
        return -1;
    }
    else if ((i = lookSem(sem->name)) == -1) {
        printf("Sem could not be found\n");
        return -1;
    }
    return 0;
}

int lookSem(char * name){
    int i;
    for(i=0;i<MAX_PROC_SEM;i++) {
        if (strcmp(name,sems[i].name)) {
            return i;
        }
    };
    return -1;
}

void semInfo(){
    int i;
    printf("\n Id  Lock  Cantidad  Nombre\n");
    for(i=0;i<MAX;i++){
        if(sems[i].id!=0){
            printf("%d %d %d %s\n",sems[i].id,sems[i].lock,sems[i].cant,sems[i].name);
        }
    }
}