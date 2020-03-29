#include "semaphoreHelper.h"


#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
// Shared memory
#include <sys/mman.h>
#include <fcntl.h>

#include <sys/stat.h>



SemData_t semaphoreSetUp(const char * name,bool initialValue){

    SemData_t data;

    strncpy(data.name,name,500);

    data.id = sem_open(name, O_CREAT | O_RDWR | O_CREAT ,S_IWOTH | S_IROTH , 1);

    if(initialValue)
        sem_post(data.id);

    if(data.id == SEM_FAILED){
        perror("Creating Semaphore");
        exit(-1);
    }

    return data;

}



void semaphoreDestroy(SemData_t * data){

    if (sem_close(data->id) != 0){
        perror("Closing Semaphore"); 
        exit(-1);
    }
    if (sem_unlink(data->name) < 0){
        perror("Unlinking Semaphore"); 
        exit(-1);
    }

}


void SemaphoreWait(SemData_t * data){
    sem_wait(data->id);
}


void SemaphorePost(SemData_t * data){
    sem_post(data->id);
}