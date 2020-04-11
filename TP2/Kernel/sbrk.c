#include <stdlib.h>
#include <stdint.h>

static void * const sampleDataModuleAddress = (void*)0x600000;
static void * const maxAddress = (void*) 0x700000;
void * topAddress = NULL;


// sbrk_handler() increments the end of DataSeg and return the beginning of the allocked space 
void sbrk_handler(intptr_t increment, void * buffer){
        if (topAddress == NULL) {
                topAddress = sampleDataModuleAddress;
        }
        
        if (topAddress + increment <= maxAddress) {
                buffer = topAddress;
                topAddress += increment;
        }
        buffer = NULL;
}