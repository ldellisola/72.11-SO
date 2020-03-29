#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



#include "shmHelper.h"
#include "semaphoreHelper.h"

#define MAX 1024

// Funciones

// Esta funcion valida el input del usuario y toma como parametros los mismo que le main.
void validateInput(int argc, char ** argv);

// FALTA IMPLEMENTAR LA SE:AL DE DESTRUCCION

int main(int argc, char ** argv){

    validateInput(argc,argv);

        setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stdin, NULL, _IONBF, 0);


    // Configuro Semaforo
    char semName[200];
    sprintf(semName,"sem_%s",argv[1]);
    SemData_t semData = semaphoreSetUp(semName,false);

    SemaphoreWait(&semData);

    // Configuro shared memory

    char shmName[200];
    sprintf(shmName,"shm_%s",argv[1]);
    SHMData_t shmData = shmCreate(shmName,MAX * 50);

    // Loop principal

    printf("Configuro todo\n");

    do{
        printf("Espero en el semaforo\n");
        SemaphoreWait(&semData);
        printf("Leo input de memoria\n");
        char shmResponse[MAX];
        shmRead(shmResponse,MAX,&shmData);

        printf("Mandaron: %s\n",shmResponse);
        printf("Activo el semaforo\n");
        SemaphorePost(&semData);

    }while(true);
    


    // Destruyo semaforo

    semaphoreDestroy(&semData);


    // Destruyo memoria compartida

    shmDestroy(&shmData);

}




void validateInput(int argc, char ** argv){
    if(argc != 2){
        fprintf(stderr,"This program only takes 1 argumen.\n");
        exit(-1);
    }
    // Atoi no es seguro, pero para nuestros propositos sirve por que el numero que tenemos que recibir siempre va a ser mayor que cero
    // y atoi() siempre devuelve 0 si no puede convertir el string (ej: es una palabra). Otra alternativa seria usar strtol().
    int number = atoi(argv[1]);
    if( number <1){
        fprintf(stderr,"Invalid SHM name: %d.\n",number);
    }
}