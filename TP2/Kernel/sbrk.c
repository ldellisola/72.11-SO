#include <stdlib.h>

static void * const sampleDataModuleAddress = (void*)0x500000;
static void * topAddress = sampleDataModuleAddress;


// sbrk_handler() increments the end of DataSeg and return the beginning of the allocked space 
void sbrk_handler(intptr_t increment, void * buffer){
        buffer = (void*) topAddress;
        // falta chequear si supera el espacio "permitido"
        topAddress += increment;
}