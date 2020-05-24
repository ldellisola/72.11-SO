#include "include/Debugger.h"
#include <deviceInfo.h>
#include <Curses.h>

/***************************************************************/
/*                         CONSTANTES                          */
/***************************************************************/

#define WHITE 0xFFFFFF
#define RED 0xFF0000

/***************************************************************/
/*                    Funciones Publicas                       */
/***************************************************************/

void PrintExceptionDetails(char *name, uint64_t *stackPointer, uint64_t *instructionPointer)
{
    Registers reg;
    getRegisters(&reg, stackPointer, instructionPointer);

    printfColor(WHITE, RED, "EXCEPTION: %s | IP: 0X%X\n", name, reg.rip);

    printf("RAX: 0X%X | RBX: 0X%X | RCX: 0X%X | RDX: 0X%X\n", reg.rax, reg.rbx, reg.rcx, reg.rdx);

    printf("RDI: 0X%X | RSI: 0X%X | R08: 0X%X | R09: 0X%X\n", reg.rdi, reg.rsi, reg.r8, reg.r9);

    printf("R10: 0X%X | R11: 0X%X | R12: 0X%X | R13: 0X%X\n", reg.r10, reg.r11, reg.r12, reg.r13);

    printf("R14: 0X%X | R15: 0X%X \n", reg.r14, reg.r15);

    return;
}
