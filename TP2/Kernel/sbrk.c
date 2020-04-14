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
        
        if (topAddress + increment <= maxAddress) {
        
                *buffer = topAddress;
                topAddress += increment;
        }
        else{
                *buffer = NULL;
        }

        return;
}


int brk_handler( void * addr){
        if (topAddress == NULL) {
                topAddress = sampleDataModuleAddress;
        }
        
        // No puede reservar mas memoria que la que tiene asignada el proceso, o
        // un valor menor al que tiene ya asignado
        if(addr > maxAddress  || addr < topAddress)
        {
                return -1;
        }
        
        topAddress = addr;
        return 0;

}