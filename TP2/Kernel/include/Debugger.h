#ifndef DEBUGGER_API_H
#define DEBUGGER_API_H

#include <stdint.h>



//  Prints all the registers, the process that generated the exception and other details
void PrintExceptionDetails(char * name,uint64_t * stackPointer,uint64_t* instructionPointer);

























#endif