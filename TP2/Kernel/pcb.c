#include "include/pcb.h"
#include "include/sbrk.h"
#include "include/Curses.h"
#include "include/String.h"

#define CANT 20
#define STACK 10000
#define NULL 0
static int pid=0;

pcb pcbs[CANT];
int cant=0;

pcb * create(char * name, int * state, function * function){
    if(cant==CANT){
        *state=-1;
        return NULL;
    }

    int i;
    for(i=0;i<CANT && pcbs[i].state!=KILL;i++);
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

    