#include <Curses.h>
#include <stdint.h>
#include <String.h>
#include <stdbool.h>
#include <Debugger.h>
#include <KernelHelper.h>
#include <Scheduler.h>

#define ZERO_EXCEPTION_ID 0
#define INVALID_OPCODE_EXCEPTION_ID 0x06




void exceptionDispatcher(int exception, uint64_t * stackPointer) {

	printfColor("In Process: %d",0xFF0000,0xFFFFFF,getpid());
		switch(exception){
			case ZERO_EXCEPTION_ID:
			{
				PrintExceptionDetails("DIVISION BY ZERO",stackPointer,*(stackPointer+15));

				break;
			}
			case INVALID_OPCODE_EXCEPTION_ID:
			{
				PrintExceptionDetails("Invalid OPCODE",stackPointer,*(stackPointer+15));
				DEBUG("La excepcion me la tira %d",getpid());
				break;
			}
			default:{
				PrintExceptionDetails("UNKNOWN EXCEPTION",stackPointer,*(stackPointer+15));
			}

		}		
}





