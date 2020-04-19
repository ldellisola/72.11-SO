#include <stdio.h>
#include "include/Scheduler.h"
#include "include/sbrk.h"

#define quantum 20/1000

Priority priorities[3];

void RoundRobin(){
    while(priorities[0].cant!=0 ||priorities[1].cant!=0 ||priorities[2].cant!=0  ){
        //
    }
}

void createProcess(char * name, int * state, function * function){
    
    pcb * new=create(name,state,function);
    priorities[1].cant++;  
    
    if(priorities[1].first==NULL){
        sbrk_handler(sizeof(process),&priorities[1].first);
        priorities[1].last=priorities[1].first;
        priorities[1].first->pcb=new;
        priorities[1].first->next=priorities[1].first;
        priorities[1].first->prev=priorities[1].first;
    }
    
    else{
        sbrk_handler(sizeof(process),&priorities[1].last);
        
        priorities[1].last->prev=priorities[1].first->prev->next;
        priorities[1].last->next=priorities[1].first;
        priorities[1].first->prev->next=priorities[1].last;
        priorities[1].first->prev=priorities[1].last;

    }

    if(new!=NULL){
        //checkear status
        //bloquear al que esta corriendo y correr a este
    }

}    
void killProcess(int * pid){
    int pr=kill(pid);  
    if(pr!=-1){

        priorities[pr].cant--;
        process * process=priorities[pr].first;
        if(priorities[pr].cant==0){
            priorities[pr].first=NULL;
            priorities[pr].last=NULL;
            //free process;
            return;
        }

        while(process->pcb->pid!=*pid){
            process=process->next;
        }

        process->prev->next=process->next;
        process->next->prev=process->prev;
        //free process
    }  
}    
    
