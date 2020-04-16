#ifndef SHM_HELPER
#define SHM_HELPER

#include <unistd.h>

/********************************************************************************
*                               Estructuras                                     *
*********************************************************************************/

typedef struct
{
    int fd;
    char name[1024];
    int writeIndex;
    int readIndex;
    char *map;
    unsigned int size;
} SHMData_t;

/********************************************************************************
*                                 Funciones                                     *
*********************************************************************************/

// Crea una memoria compartida y devuelve una estructura a partir de la cual se puede
// interactuar con ella
//
//      - shmName: Nombre de la memoria compartida
//      - shmSize: Tama;o de la memoria compartida
SHMData_t shmCreate(const char *shmName, size_t shmSize);

// Abre una memoria compartida y devuelve una estructura a partir de la cual se puede
// interactuar con ella
//
//      - shmName: Nombre de la memoria compartida
//      - shmSize: Tama;o de la memoria compartida
SHMData_t shmOpen(const char *shmName, size_t shmSize);

// Escribe una cantidad determinada de caracteres a una memoria compartida
//
//      - buffer: String que va a ser escrito en la memoria.
//      - bSize:  Cantidad de caracteres a escribir.
//      - data:   Estructura que almacena la informacion de la memoria compartida
void shmWrite(char *buffer, int bSize, SHMData_t *data);

// Lee una cantidad determinada de caracteres de la memoria compartida o hasta el fin de
// la memoria escrita. Devuelve la cantidad de caracteres leidos.
//
//      - buffer: String que va a ser escrito en la memoria.
//      - bSize:  Cantidad de caracteres a escribir.
//      - data:   Estructura que almacena la informacion de la memoria compartida
int shmRead(char *buffer, int bSize, SHMData_t *data);

// Destruye y libera los recursos utilizados por la memoria compartida.
//
//      - data:   Estructura que almacena la informacion de la memoria compartida
void shmDestroy(SHMData_t *data);

// Destruye y libera los recursos utilizados por la memoria compartida. Esta funcion solo
// debe ser llamada si a data se la creo con la funcion shmOpen
//
//      - data:   Estructura que almacena la informacion de la memoria compartida
void shmClose(SHMData_t *data);

#endif