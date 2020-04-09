/* sampleCodeModule.c */
#include "../Include/Time.h"
#include "../Include/String.h"
#include "../Include/Syscalls.h"

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
	printfColorAt(0xFF44FF,0x00,position,y,"TPE DE PC");
    setSize(init*2);
	getBpp(&aux);
    y+=charHeight*aux+3;
    printfColorAt(0xFFFFFF,0x00,position,y,"58025,Dellisola   58489,Torrusio   59820,PUIG");
    y+=charHeight*aux+3;
    printfColorAt(0xFFFFFF,0x00,position*4+30,y,"1) Terminal");
	y+=charHeight+20;
	printfColorAt(0xFFFFFF,0x00,position*3+20,y,"2) Exit");
    setSize(init);

}

static int selector = -1;

int main() {

	int exit=0;
	while(exit!=1)
	{
		
		if(selector == -1){
			clearConsole();
			menu();
			while(((selector=readKey())!='1') && (selector!='2'));
			clearConsole();
			if(selector == '1')
				printf("HI! Ask \"man\" for a command menu\n");
		}

		if(selector == '1'){

			
			switch(runTerminal()){
				case 1: exit = 1; break;
			}
		}
		else{
			exit = 1;
		}


		
	}

	clearConsole();

	unsigned int init;
	getBpp(&init);
	setSize(6*init);
	
	int position=70;
	int y=50;
	printfColorAt("BYE!",0xFF44FF,0x00,position,y);
	return 0xDEA;
}

