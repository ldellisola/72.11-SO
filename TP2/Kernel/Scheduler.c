// #include <stdio.h>/
#include "include/Scheduler.h"
#include "include/MemManager.h"
#include "include/Curses.h"

#define quantum 20/1000
#define INIT_QUEUE 1

Priority priority;
process * curr=0;
int currPr=0;

void insertQueue(process * process);
void deleteQueue(int * pid,process ** process);

void roundRobin(){

    if(priority.cant == 0){
        DEBUG("No process%s","")
        curr = NULL;
        return ;
    }

    if(priority.cant == 1){
        curr = priority.first;
        return;
    }
        
    curr=priority.first;

    process * newLast = priority.first;

    priority.first = priority.first->next;
    priority.first->prev = NULL;

    process * oldLast = priority.last;

    oldLast->next = newLast;
    newLast->prev = oldLast;    

    priority.last = newLast;




    // while(priority.cant!=0){
    //     if(curr->pcb->state!=BLOCK){}
    //         //run
    //     else
    //         curr=curr->next;
    // }
}

process * GetCurrentProcess(){

    return curr;
}


void * createProcess(char * name, int * state, function_t * function){
    
    DEBUG("Creando proceso: %s",name)
    pcb * new=create(name,state,function);
    priority.cant++;  
    if(new!=NULL){
        process * procs=(process *) malloc(sizeof(process));
        procs->pcb=new;
        insertQueue(procs);
        //checkear status
        //bloquear al que esta corriendo y correr a este
        
        return new->sp;
    }
    return NULL;

}    
void killProcess(int * pid){
    kill(pid);  
    if(*pid!=-1){
        priority.cant--;
        process * process=priority.first;
        deleteQueue(pid,&process);
        free(process);
    }  
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