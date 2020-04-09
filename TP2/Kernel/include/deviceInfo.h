
#ifndef DEVICEINFO_API_H
#define DEVICEINFO_API_H

#include <stdint.h>

typedef struct 
{
    uint64_t rax;
    uint64_t rbx;
    uint64_t rcx;
    uint64_t rdx;
    uint64_t rbp;
    uint64_t rsi;
    uint64_t rdi;
    uint64_t r8;
    uint64_t r9;
    uint64_t r10;
    uint64_t r11;
    uint64_t r12;
    uint64_t r13;
    uint64_t r14;
    uint64_t r15;

    uint64_t rip;
    
}Registers;



void getDeviceInfo(void* ptr);
void getRegisters(Registers * reg,uint64_t * stackPointer,uint64_t * instructionPointer);
void readMem(uint64_t position, char * buff, unsigned size);



#endif