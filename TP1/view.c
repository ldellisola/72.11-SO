// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "shmHelper.h"
#include "semaphoreHelper.h"

/********************************************************************************
*                                Constantes                                     *
*********************************************************************************/

// Indica el tama;o predeterminado de los strings
#define MAX 1024

// Es un string terminador a partir del cual se va a evalual la condicion de retorno del programa
#define TERMINATOR "&exit;"

/********************************************************************************
*                                   Set Up                                      *
*********************************************************************************/

// Inicializa la memoria compartida y los semaforos
//
//      - shmData: Es un puntero a una estructura que almacena informacion sobre la memoria compartida
//      - semData: Es un puntero a una estructura que almacena informacion sobre los semaforos
void initialize(SemData_t *semData, SHMData_t *shmData);

// Se encarga de eliminar los recursos utilizados por el sistema
//
//      - shmData: Es un puntero a una estructura que almacena informacion sobre la memoria compartida
//      - semData: Es un puntero a una estructura que almacena informacion sobre los semaforos
void finalize(SemData_t *semData, SHMData_t *shmData);

/********************************************************************************
*                            Funciones Auxiliares                               *
*********************************************************************************/

// Esta funcion verifica si se cumple la condicion de retorno
//
//      - response: Es el string a partir de cual se va a evaluar la condicion de retorno
//      - size:     Es el tama;o del string a evaluar.
bool resolveExitCondition(char *response, int size);

int main(void)
{

    SemData_t semData;
    SHMData_t shmData;

    initialize(&semData, &shmData);

    // Loop principal

    bool exitCondition = false;
    char shmResponse[MAX];
    do
    {

        semaphoreWait(&semData);
        int size = shmRead(shmResponse, MAX, &shmData);
        shmResponse[size] = 0;

        exitCondition = resolveExitCondition(shmResponse, size);

        if (!exitCondition || size > 7)
            printf(shmResponse);

    } while (!exitCondition);

    finalize(&semData, &shmData);

    return 0;
}

bool resolveExitCondition(char *response, int size)
{

    if (size > 6)
    {

        char *str = response + size - 6;
        if (strcmp(str, TERMINATOR) == 0)
        {
            response[size - 6] = 0;
            return true;
        }
    }
    return false;
}

void initialize(SemData_t *semData, SHMData_t *shmData)
{

    // Desactivo el buffer
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stdin, NULL, _IONBF, 0);

    // Leo el codigo para acceder a memoria compartida y semaforos
    char num[10];
    int size = read(STDIN_FILENO, num, 10);
    num[size] = 0;

    // Configuro Semaforo

    char semName[200];
    sprintf(semName, "/SEM_%s", num);
    *semData = semaphoreOpen(semName);

    // Configuro shared memory

    char shmName[200];
    sprintf(shmName, "/SHM_%s", num);
    *shmData = shmOpen(shmName, MAX * 100);
}

void finalize(SemData_t *semData, SHMData_t *shmData)
{
    // Destruyo semaforo
    semaphoreClose(semData);

    // Destruyo memoria compartida
    shmClose(shmData);
}