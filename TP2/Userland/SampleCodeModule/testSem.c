#include "../Include/Sem.h"
#include "../Include/Syscalls.h"
#include "include/Exec.h"
#include "include/Process.h"
#define MAX 100000000

int variable=0;
int flag=0;

void sum();
void resta();

void sum(){
    flag++;
    for(int i=0;i<MAX;i++){
    int cant=variable;
    cant++;
    variable=cant;  
    }
    exit_process();
}
void resta(){
    flag++;
    for(int i=0;i<MAX;i++){
    int cant=variable;
    cant--;
    variable=cant;  
    }
    exit_process();
}

void testSem(){
    for(int i=0;i<3;i++){
        int status=1;
        exec("suma",status,sum,0);
        exec("resta",status,resta,0);
        
    }
    while(flag!=6);
    printf("%d\n",variable);
    variable=0;
    flag=0;
}