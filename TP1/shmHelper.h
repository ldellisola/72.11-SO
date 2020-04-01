#ifndef SHM_HELPER
#define SHM_HELPER

#include <unistd.h>

typedef struct
{
    int fd;
    char name[1024];
    int writeIndex;
    int readIndex;
    char * map;
    unsigned int size;
}SHMData_t;

// Configura el acceso a memoria compartida
SHMData_t shmCreate(const char * shmName,  size_t shmSize);
SHMData_t shmOpen(const char * shmName,  size_t shmSize);



// Escribe una cantidad determinada de chars a la memoria compartida
void shmWrite(char * buffer, int bSize, SHMData_t * data);

// Lee una cantidad determinada de caracteres de la memoria compartida
int shmRead(char * buffer, int bSize,SHMData_t * data );

// Elimina la memoria compartida
void shmDestroy(SHMData_t * data);



#endif