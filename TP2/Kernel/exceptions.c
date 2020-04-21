#include <Curses.h>
#include <stdint.h>
#include <String.h>
#include <stdbool.h>
#include <Debugger.h>
#include <KernelHelper.h>

#define ZERO_EXCEPTION_ID 0
#define INVALID_OPCODE_EXCEPTION_ID 0x06
#define GENERAL_PROTECTION_FAULT_EXCEPTION_ID 0x0D
#define PAGE_FAULT_EXCEPTION_ID 0x0E




void exceptionDispatcher(int exception, uint64_t * stackPointer) {
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
			case PAGE_FAULT_EXCEPTION_ID:{
				PrintExceptionDetails("PAGE FAULT",stackPointer,*(stackPointer+15));

				break;
			}
			case GENERAL_PROTECTION_FAULT_EXCEPTION_ID:{
				PrintExceptionDetails("GENERAL PROTECTION FAULT",stackPointer,*(stackPointer+15));

				break;
			}
			default:{
				PrintExceptionDetails("UNKNOWN EXCEPTION",stackPointer,*(stackPointer+15));
			}

		}		
}





