#ifndef SEMAPHORE_HELPER
#define SEMAPHORE_HELPER

#include <semaphore.h>
#include <stdbool.h>

typedef struct{
    char name[500];
    sem_t * id;
} SemData_t;

// Creates an instance of a named semaphore to connect with another process
SemData_t semaphoreSetUp(const char * name,bool initialValue);

// Destroys and disconnects the semaphore instance created
void semaphoreDestroy(SemData_t * data);

// Waits
void SemaphoreWait(SemData_t * data);

// Posts
void SemaphorePost(SemData_t * data);


#endif