// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <Curses.h>
#include <stdint.h>
#include <String.h>
#include <stdbool.h>
#include <Debugger.h>
#include <KernelHelper.h>
#include <Scheduler.h>

#define ZERO_EXCEPTION_ID 0
#define OVERFLOW_EXCEPTION_ID 0x04 
#define INVALID_OPCODE_EXCEPTION_ID 0x06 
#define DOBLE_FAULT_EXCEPTION_ID 0x08 
#define STACK_FAULT_EXCEPTION 0x0C 
#define GENERAL_PROTECTION_FAULT_EXCEPTION_ID 0x0d 
#define PAGE_FAULT_EXCEPTION_ID 0x0e 
 
 
 
void exceptionDispatcher(int exception, uint64_t * stackPointer) { 
 
	printfColor(0xFF0000,0xFFFFFF,"Occurred Exception \n\n\n"); 
	printfColor(0xFF0000,0xFFFFFF,"In Process: %d\n",getpid()); 
		switch(exception){ 
			case ZERO_EXCEPTION_ID: 
			{ 
				PrintExceptionDetails("DIVISION BY ZERO",stackPointer,*(stackPointer+15)); 
 
				break; 
			} 
			case INVALID_OPCODE_EXCEPTION_ID: 
			{ 
				PrintExceptionDetails("Invalid OPCODE",stackPointer,*(stackPointer+15)); 
 
				break; 
			} 
			case OVERFLOW_EXCEPTION_ID:{ 
				PrintExceptionDetails("Overflow",stackPointer,*(stackPointer+15)); 
				break; 
			} 
			case PAGE_FAULT_EXCEPTION_ID:{ 
				PrintExceptionDetails("Page Fault",stackPointer,*(stackPointer+15)); 
				break; 
			} 
			case DOBLE_FAULT_EXCEPTION_ID:{ 
				PrintExceptionDetails("Double Fault",stackPointer,*(stackPointer+15)); 
				break; 
			} 
			case STACK_FAULT_EXCEPTION:{ 
				PrintExceptionDetails("Stack Fault",stackPointer,*(stackPointer+15)); 
				break; 
			} 
			case GENERAL_PROTECTION_FAULT_EXCEPTION_ID:{ 
				PrintExceptionDetails("General Protection",stackPointer,*(stackPointer+15)); 
				break; 
			} 
			default:{ 
				PrintExceptionDetails("UNKNOWN EXCEPTION",stackPointer,*(stackPointer+15)); 
			} 
 
		}	

	while(1);	 
} 

