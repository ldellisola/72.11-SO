#include "include/pcb.h"
#include "include/MemManager.h"
#include "include/Curses.h"
#include "include/String.h"

#define MAX 20
#define STACK 10000
#define NULL 0
static int pid=0;

pcb pcbs[MAX];
int cant=0;

int findProcess(int pid);

pcb * create(char * name, int * status, function * function){
    if(cant==MAX){
        *status=-1;
        return NULL;
    }

    int i;
    cant++;
    for(i=0;i<MAX && pcbs[i].state!=KILL;i++);
    CopyString(name,pcbs[i].name,strlen(name));
    pcbs[i].pid=pid++;
    pcbs[i].priority=1;

    void * stack=malloc(10000);
    
    pcbs[i].stack=stack;
    pcbs[i].state=READY;
    pcbs[i].status=*status;
    //pcbs[i].registers=getRegisters(&pcbs[i].registers??,stack,??);
    //pcbs[i].pb=??
    return &pcbs[i];
}

void kill(int * pid){
    int i=findProcess(*pid);
    if(i!=-1){
        pcbs[i].state=KILL;
        free(pcbs[i].stack);
        return;
    }
    *pid=-1;
}

void nice(int * pid, int pr){
    int i=findProcess(*pid);
    if(i!=-1){
        pcbs[i].priority=pr;
        return;
    }
    *pid=-1;
}

void block(int * pid){
    int i=findProcess(*pid);
    if(i!=-1){
     if(pcbs[i].state==READY)   
           pcbs[i].state=BLOCK;
      else
        pcbs[i].state=READY;
    }else 
        *pid=-1;
}

int findProcess(int pid){
    int i;
    
    if(pid!=0)
        for(i=0;i<MAX && pcbs[i].pid!=pid;i++);
    
    if(pid==0||i==MAX||pcbs[i].state==KILL)
        return -1;

    return i;
}

void ps(){
    printf("nombre  pid prioridad stack  bp  status registros estado\n");
    for(int i=0;i<MAX;i++){
        if(pcbs[i].state!=KILL){
        printf("%s      %d     %d       --    --     %d     --      ",pcbs[i].name,pcbs[i].pid,pcbs[i].priority,pcbs[i].status);
            if(pcbs[i].state==READY)
                printf("ready\n");
            else 
                printf("block\n");            
        }
    }
}
    