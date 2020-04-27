/* sampleCodeModule.c */
#include "../Include/Time.h"
#include "../Include/String.h"
#include "../Include/Syscalls.h"
#include "include/Exec.h"
#include "include/Terminal.h"
#include "../Include/Curses.h"
#include <stdlib.h>
#include "../Include/deviceInfo.h"


extern void __halt__();


int main() {	
	
	exec("terminal",0,runTerminal,0);

	__halt__();
	
	return 0xDEA;
}

