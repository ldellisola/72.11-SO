// #include <stdio.h>/
#include "include/Scheduler.h"
#include "include/MemManager.h"
#include "include/Curses.h"

#define quantum 20/1000
#define INIT_QUEUE 1

Priority priority;
process * curr=0;
int currPr=0;

void * exitAddress = NULL;
bool hasExited = false;

void insertQueue(process * process);
void deleteQueue(int * pid,process ** process);

void roundRobin(){

    if(priority.cant == 0){
        // DEBUG("No process%s","");

        curr = NULL;
        return ;
    }

    if(priority.cant == 1){
        curr = priority.first;
        return;
    }
    
    do{
        curr=curr->next;
    }while(curr->pcb->state==BLOCK);
    
}

process * GetCurrentProcess(){

    return curr;
}

void SaveExitAddress(void * add){
    exitAddress = add;
}

bool HasStoppedExcecution(){
    return hasExited;
}

void * GetExitAddress(){
    return exitAddress;
}

void * createProcess(char * name, int * status, function_t * function){
    
    //DEBUG("Creando proceso: %s",name)
    int pidP;
    if(priority.cant==0){
        pidP=-1;
    }else{
        pidP=curr->pcb->pid;
    }
    pcb * new=create(name,status,function,pidP);
    if(new!=NULL){
        priority.cant++;  
        process * procs=(process *) malloc(sizeof(process));
        procs->pcb=new;
        insertQueue(procs);
        //checkear status
        //bloquear al que esta corriendo y correr a este
        if(*status==0 && pidP!=-1){
            int pid=curr->pcb->pid;
            curr->pcb->state=BLOCK;
        }
        else if(pidP==-1){
            new->priority=2;
        }
        return new->sp;
    }
    return NULL;

}    
void * killProcess(int * pid){
    hasExited = false;

    if(*pid == 0)
        hasExited = true;

    kill(pid);  
    if(*pid!=-1){
        priority.cant--;
        process * process=priority.first;
        deleteQueue(pid,&process);
        int pidP=process->pcb->pidP;
        block(&pidP);
        free(process);
    }  

    if(hasExited)
        return exitAddress;
    else
        return NULL;


}  

void blockProcess(int * pid){
    block(pid);
}

void niceProcess(int * pid, int priority){
    nice(pid,priority);
}
    
void insertQueue(process * procs){
        priority.last=procs;
    if(priority.first==NULL){
        
        priority.first=priority.last;
        priority.first->next=priority.first;
        priority.first->prev=priority.first;

    }
    
    else{
        priority.last->prev=priority.first->prev;
        priority.last->next=priority.first;
        priority.first->prev->next=priority.last;
        priority.first->prev=priority.last;

    }
}
void deleteQueue(int * pid, process ** process){
    if(priority.cant==0){

            priority.first=NULL;
            priority.last=NULL;
            return;
        }

        while((*process)->pcb->pid!=*pid){
            *process=(*process)->next;
        }
        (*process)->prev->next=(*process)->next;
        (*process)->next->prev=(*process)->prev;
}

int getpid(){
    return curr->pcb->pid;
}