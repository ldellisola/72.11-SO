/* sampleCodeModule.c */
#include "../Include/Time.h"
#include "../Include/String.h"
#include "../Include/Syscalls.h"
#include "include/Exec.h"
#include "include/Terminal.h"
#include "../Include/Curses.h"
#include <stdlib.h>
#include "../Include/deviceInfo.h"

#include "include/Process.h"

#define STDIN 0
#define STDOUT 1


extern void __halt__();
extern void LoadDummyProcess(process_Function_t func); 

int dummy (int argc, char ** argv);

int main() {	
	char * args[] = {"TP2 de SO"};

	
	LoadDummyProcess(dummy);

	exec("terminal",0,runTerminal,STDIN,STDOUT,1,args);

	__halt__();
	__halt__();
	__halt__();
	__halt__();
	
	return 0xDEA;
}

int dummy (int argc, char ** argv){ 
	while (1) 
	{ 
		__asm__("hlt"); 
 
	} 
	return 0; 
} 
