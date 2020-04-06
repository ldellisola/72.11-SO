#ifndef SEMAPHORE_HELPER
#define SEMAPHORE_HELPER

#include <semaphore.h>
#include <stdbool.h>

/********************************************************************************
*                               Estructuras                                     *
*********************************************************************************/

typedef struct
{
    char name[1024];
    sem_t *id;
} SemData_t;

/********************************************************************************
*                                 Funciones                                     *
*********************************************************************************/

// Crea un named semaphore y devuelve una estructura a partir de la cual puede
// controlar al semaforo
//
//      - name: Nombre del semaforo
SemData_t semaphoreSetUp(const char *name);

// Abre un name semaphore que ya fue creado por otro proceso y devuelve una instancia de
// una estructura mediante la cual puede interactuar con el semaforo.
//
//      - name: Nombre del semaforo
SemData_t semaphoreOpen(const char *name);

// Destruye y libera los recursos utilizados por el semaforo.
//
//      - data: Es un puntero a una estructura creada mediante las funciones semaphoreSetUp
//              o sempahoreOpen
void semaphoreDestroy(SemData_t *data);

// Destruye y libera los recursos utilizados por el semaforo. Esta funcion solo debe ser usada
// si data se creo con la funcion semaphoreOpen
//
//      - data: Es un puntero a una estructura creada mediante las funciones semaphoreSetUp
//              o sempahoreOpen
void semaphoreClose(SemData_t *data);

// Bloquea al flujo del programa hasta que se llame a la funcion semaphorePost con el mismo
// semafor abierto desde otro proceso.
//
//      - data: Es un puntero a una estructura creada mediante las funciones semaphoreSetUp
//              o sempahoreOpen
void semaphoreWait(SemData_t *data);

// En caso de estar bloqueado el flujo de otro programa con el mismo semaforo, llamar a esta funcion
// puede que lo libere, ya que ejecuta a la funcion sem_post
//
//      - data: Es un puntero a una estructura creada mediante las funciones semaphoreSetUp
//              o sempahoreOpen
void semaphorePost(SemData_t *data);



#endif