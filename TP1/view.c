#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



#include "shmHelper.h"
#include "semaphoreHelper.h"

#define MAX 1024

int main(void){

    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stdin, NULL, _IONBF, 0);


    char num[10];
    int size=read(STDIN_FILENO,num,10);
    num[size]=0;


    // Configuro Semaforo
    char semName[200];
    sprintf(semName,"/SEM_%s",num);

    printf("SEMAPHORE: %s\n",semName);
    SemData_t semData = semaphoreOpen(semName);


    // Configuro shared memory
    
    char shmName[200];

    sprintf(shmName,"/SHM_%s",num);
    
    printf("SHARED MEMORY: %s\n",shmName);

    SHMData_t shmData = shmOpen(shmName,MAX * 100);


    // Loop principal

    bool exitCondition = false;

    do{
        SemaphoreWait(&semData);
        char shmResponse[MAX];
        int size=shmRead(shmResponse,MAX,&shmData);
        shmResponse[size] = 0;


        exitCondition= size > 7 && shmResponse[size-1] == ';' && shmResponse[size-2] == 't'
                        && shmResponse[size-3] == 'i' && shmResponse[size-4] == 'x'
                        && shmResponse[size-5] == 'e' && shmResponse[size-6] == '&';   

        if(exitCondition && size > 7)
            shmResponse[size-6] = 0;
        if(!exitCondition || size > 7)
            printf(shmResponse);
        else{
            printf("\nFinish.Bye. \n");
        }

        
    }while(!exitCondition);
    


    // Destruyo semaforo

    semaphoreDestroy(&semData);


    // Destruyo memoria compartida

    shmDestroy(&shmData);

}

