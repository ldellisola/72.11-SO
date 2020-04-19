#include <stdio.h>
#include "include/Scheduler.h"
#include "include/MemManager.h"

#define quantum 20/1000
#define INIT_QUEUE 1

Priority priorities[3];
process * curr=0;
int currPr=0;

void insertQueue(process * process,int priority);
void deleteQueue(int * pid, int pr,process ** process);

void RoundRobin(){
    curr=priorities[currPr].first;
    while(priorities[0].cant!=0 ||priorities[1].cant!=0 ||priorities[2].cant!=0  ){
        if(curr->pcb->state!=BLOCK)
            //run
        if(curr==priorities[currPr].last){
           if(currPr==2)
                currPr=0;
            else
                currPr++;
                
           curr=priorities[currPr].first;     
        }
        else
            curr=curr->next;
    }
}

void createProcess(char * name, int * state, function * function){
    
    pcb * new=create(name,state,function);
    priorities[INIT_QUEUE].cant++;  
    if(new!=NULL){
        process * procs=(process *) malloc(sizeof(process));
        procs->pcb=new;
        insertQueue(procs,INIT_QUEUE);
        //checkear status
        //bloquear al que esta corriendo y correr a este
        
        
    }

}    
void killProcess(int * pid){
    int pr=kill(pid);  
    if(pr!=-1){
        priorities[pr].cant--;
        process * process=priorities[pr].first;
        deleteQueue(pid,pr,&process);
        free(process);
    }  
}  

void blockProcess(int * pid){
    block(pid);
}

void niceProcess(int * pid, int priority){
    int pr=nice(pid,priority);
    if(pr!=-1){
        process * process=priorities[pr].first;
        priorities[pr].cant--;
        deleteQueue(pid,pr,&process);
        insertQueue(process,priority);
    }
}
    
void insertQueue(process * procs,int priority){
        priorities[priority].last=procs;
    if(priorities[priority].first==NULL){
        
        priorities[priority].first=priorities[priority].last;
        priorities[priority].first->next=priorities[priority].first;
        priorities[priority].first->prev=priorities[priority].first;
    }
    
    else{
        priorities[priority].last->prev=priorities[priority].first->prev;
        priorities[priority].last->next=priorities[priority].first;
        priorities[priority].first->prev->next=priorities[priority].last;
        priorities[priority].first->prev=priorities[priority].last;

    }
}
void deleteQueue(int * pid, int pr,process ** process){
    if(priorities[pr].cant==0){
            priorities[pr].first=NULL;
            priorities[pr].last=NULL;
            return;
        }

        while((*process)->pcb->pid!=*pid){
            *process=(*process)->next;
        }
        (*process)->prev->next=(*process)->next;
        (*process)->next->prev=(*process)->prev;
}