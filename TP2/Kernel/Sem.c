#include "include/Sem.h"
#include "include/Curses.h"
#include "include/String.h"
#include "include/Scheduler.h"
#include "include/SpinLock.h"
#include <stdlib.h>

extern void __ForceTimerTick__();

#define MAX 20
#define NO_VALUE -1
SemData_t sems[MAX];

int lookSem(char * name);
int GetSemaphoreByName(char * name);
int FindUnusedSemaphore();
int semCheck(SemData_t * sem);
SemData_t * getSem(char * name);

int semopen(char * name, int * initialValue){

    SpinLock();
    int pos = GetSemaphoreByName(name);

    if(pos == -1){
        // Creo el semaforo
        pos = FindUnusedSemaphore();

        if (pos == -1) {
            printf("All semaphores are occupied\n");
            return -1;
        }

        sems[pos].id=pos+1;
        sems[pos].value=*initialValue;
        sems[pos].cant=0;

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
    

    SpinLock();

    SemData_t * sem = &sems[GetSemaphoreByName(semName)];

    bool hasToBeBlocked = true;

    if (semCheck(sem) != 0) {
        printf("Error waiting semaphore\n");
        return;
    }

    sem->value--;

    if(sem->value < 0){
        int pid = getpid();
                
        int i = 0;

        do{
            if(sem->processesBlocked[i] == NO_VALUE){
                sem->processesBlocked[i] = pid;
            }
        }while(sem->processesBlocked[i++] != pid);

        // Cambie la funcion por que la otra no permite bloquear a la terminal
        block(&pid);

        if(pid != getpid()){
            printfColor("ERROR blocking process on semaphore",0xFF0000,0);
        }

    }else{
        hasToBeBlocked =  false;
    }

    SpinUnlock();


    if(hasToBeBlocked){
        __ForceTimerTick__();
    }

    return hasToBeBlocked;

}

int sempost(char * semName){

    SpinLock();

    SemData_t * sem = &sems[GetSemaphoreByName(semName)];

    if (semCheck(sem) != 0) {
        printf("Error posting semaphore\n");
        return;
    }

    (sem->value)+=1;

    int pid = sem->processesBlocked[0];

    if (sem->value <= 0) {
    //int myPID = getpid();

    // desbloqueo el primero, debido al Queue
    process * p = GetProcess(sem->processesBlocked[0]);
    p->pcb->state = READY;

    // muevo toda la queue uno hacia adelante y actualizo el último
    for(int i = 0 ; i < MAX_PROC_SEM-1; i++) {
        sem->processesBlocked[i] = sem->processesBlocked[i+1];
        }
    sem->processesBlocked[MAX_PROC_SEM-1]=NO_VALUE;

    // for(i = 0 ; i < MAX_PROC_SEM; i++){
    //     int pid = sem->processesBlocked[i];
    //     if(pid != 0 && pid != myPID){
    //         process * p = GetProcess(sem->processesBlocked[i]);
    //         p->pcb->state = READY;
    //         break;
    //     }
    // }
    }
    else{
        pid = -1;
    }
    
    SpinUnlock();

    return pid;
}

void semclose(char * semName){
    SemData_t * sem = getSem(semName);

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
            //printf("Encontre un sem. Posicion: %d. Nombre: %s\n",i,name);
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
    if (sem == NULL || sem->name == NULL) {
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
    printf("\n Id  Value  Cantidad  Nombre\n");
    for(i=0;i<MAX;i++){
        if(sems[i].id!=0){
            printf("%d %d %d %s\n",sems[i].id,sems[i].value,sems[i].cant,sems[i].name);
        }
    }
}

SemData_t * getSem(char * name) {
    int index = GetSemaphoreByName(name);
    if (index == -1) {
        return NULL;
    }
    SemData_t * ptr = &sems[index];
    return ptr;
}