#include "include/sbrk.h"
#include <stdlib.h>
#include <Curses.h>
static void * const sampleDataModuleAddress = (void*)0x600000;
static void * const maxAddress = (void*) 0x700000;
void * topAddress = NULL;


// sbrk_handler() increments the end of DataSeg and return the beginning of the allocked space 
void sbrk_handler(intptr_t increment, void ** buffer){
        if (topAddress == NULL) {
                topAddress = sampleDataModuleAddress;
        }

        printf("KERNEL: Memoria tope actual: 0x%x\n",topAddress);
        
        if (topAddress + increment <= maxAddress) {
        
                *buffer = topAddress;
                topAddress += increment;
                printf("KERNEL: Aumento en %d el tope de la memoria\n",increment);
        }
        else{
                printf("KERNEL: 0x%x + 0x%x es mayor al tope de memoria: 0x%x\n",increment,topAddress,maxAddress);
                *buffer = NULL;
        }

        return;
}