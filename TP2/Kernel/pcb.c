#include "include/pcb.h"
#include "include/sbrk.h"
#include "include/Curses.h"
#include "include/String.h"

#define MAX 20
#define STACK 10000
#define NULL 0
static int pid=1;

pcb pcbs[MAX];
int cant=0;

pcb * create(char * name, int * state, function * function){
    if(cant==MAX){
        *state=-1;
        return NULL;
    }

    int i;
    cant++;
    for(i=0;i<MAX && pcbs[i].state!=KILL;i++);
    CopyString(name,pcbs[i].name,strlen(name));
    pcbs[i].pid=pid++;
    pcbs[i].priority=1;

    void * stack;
    sbrk_handler(10000,&stack);
    
    pcbs[i].stack=stack;
    pcbs[i].state=READY;
    pcbs[i].status=*state;
    //pcbs[i].registers=getRegisters(&pcbs[i].registers??,stack,??);
    //pcbs[i].pb=??
    return &pcbs[i];
}

int kill(int * pid){
    if(*pid!=0){
    for(int i=0;i<MAX;i++){
        if(pcbs[i].pid==*pid && pcbs[i].state!=KILL){
            pcbs[i].state=KILL;            
            //¿como libero memoria del stack? mm...
            cant--;
            return pcbs[i].priority;
        }
    }
    }
    *pid=-1;
    return -1;
}

    