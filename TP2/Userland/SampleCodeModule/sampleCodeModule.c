/* sampleCodeModule.c */
#include "../Include/Time.h"
#include "../Include/String.h"
#include "../Include/Syscalls.h"
#include "include/Exec.h"
#include "include/Terminal.h"
#include "../Include/Curses.h"
#include <stdlib.h>
#include "../Include/deviceInfo.h"
void menu(){
	unsigned int init;
	unsigned int aux;
	unsigned int charHeight;
	getCharHeight(&charHeight);
	getBpp(&init);
	setSize(5*init);
	getBpp(&aux);

	printf("BBP: %d",init);
	
	int position=67;
	int y=30;
	printfColorAt("TPE DE PC",0xFF44FF,0x00,position,y);
    setSize(init*2);
	getBpp(&aux);
    y+=charHeight*aux+3;
    printfColorAt("58025,Dellisola   58489,Torrusio   59820,PUIG",0xFFFFFF,0x00,position,y);
    y+=charHeight*aux+3;
    printfColorAt("1) Game",0xFFFFFF,0x00,position*2,y);
    printfColorAt("2) Terminal",0xFFFFFF,0x00,position*4+30,y);
	y+=charHeight+20;
	printfColorAt("3) Exit",0xFFFFFF,0x00,position*3+20,y);
    setSize(init);

}

static int selector = -1;

int main() {
	//iría exec("terminal",0,runTerminal,0);
	// printf("HI! Ask \"help\" for a command menu\n");
	// runTerminal();
	 DEBUG("%s","Por correr terminal")
	exec("terminal",0,runTerminal,0);

	

	for(long i = 99999999; i > 0 ; i--);
	for(long i = 99999999; i > 0 ; i--);
	for(long i = 99999999; i > 0 ; i--);
	for(long i = 99999999; i > 0 ; i--);
	for(long i = 99999999; i > 0 ; i--);
	for(long i = 99999999; i > 0 ; i--);
	for(long i = 99999999; i > 0 ; i--);
	for(long i = 99999999; i > 0 ; i--);
	for(long i = 99999999; i > 0 ; i--);
	for(long i = 99999999; i > 0 ; i--);
	for(long i = 99999999; i > 0 ; i--);
	for(long i = 99999999; i > 0 ; i--);
	for(long i = 99999999; i > 0 ; i--);
	for(long i = 99999999; i > 0 ; i--);
	for(long i = 99999999; i > 0 ; i--);
	for(long i = 99999999; i > 0 ; i--);
	for(long i = 99999999; i > 0 ; i--);
	for(long i = 99999999; i > 0 ; i--);
	for(long i = 99999999; i > 0 ; i--);
	for(long i = 99999999; i > 0 ; i--);
	

	DEBUG("%s","Saliendo de terminal")

	// clearConsole();

	// unsigned int init;
	// getBpp(&init);
	// setSize(6*init);
	
	// int position=70;
	// int y=50;
	// printfColorAt("BYE!",0xFF44FF,0x00,position,y);
	return 0xDEA;
}

