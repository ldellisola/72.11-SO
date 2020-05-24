// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/* sampleCodeModule.c */
#include "include/Time.h"
#include "include/String.h"
#include "include/Syscalls.h"
#include "include/Exec.h"
#include "include/Terminal.h"
#include "include/Curses.h"
#include <stdlib.h>
#include "include/deviceInfo.h"

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
