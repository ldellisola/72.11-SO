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
   sem_t sem=semopen("test");
    for(int i=0;i<MAX;i++){
    semwait(sem);
    printf("holi\n");
    int cant=variable;
    cant++;
    variable=cant;
    sempost(sem);  
    printf("chau\n");
    }
    semclose(sem);
    printf("\n SALIO 1\n");
    flag++;
    exit_process();
}
void resta(){
   sem_t sem=semopen("test");
    for(int i=0;i<MAX;i++){
    semwait(sem);
    printf("holi\n");
    int cant=variable;
    cant--;
    variable=cant;
    sempost(sem);  
    printf("chau\n");
    }
    semclose(sem);
    printf("\n SALIO 1\n");
    flag++;
    exit_process();
}
void spin(){
    sem_t sem=semopen("test");
    int pid=getpid();
    printf("Me crearon %d\n",pid);
    semwait(sem);
    printf("Hola soy %d\n",pid);
    //ps();
    int x=0;
    while(x!=1000000000){
        x++;
        if(x==1000000000)
        ps();
    };
    sempost(sem);
    exit_process();
}
void spin1(){
   printf("chau\n"); 
   exit_process();
}
void testSem(){
    sem_t sem=semopen("test");
    /*for(int i=0;i<3;i++){
        int status=1;
        exec("suma",status,sum,0);
        exec("resta",status,resta,0);
        
    }
    while(flag!=6);
    printf("%d\n",variable);
    variable=0;
    flag=0;*/
    for(int i=0;i<5;i++){
        exec("spin",1,spin,0);
    }
}