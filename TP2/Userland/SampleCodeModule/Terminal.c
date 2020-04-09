#include <stdarg.h>
#include "include/Terminal.h"
#include "../Include/Curses.h"
#include "include/Commands.h"
#include "../Include/String.h"
#include "include/Game.h"
#include <stdlib.h>
#include <stdbool.h>


/***************************************************************/
/*                        Constantes                           */
/***************************************************************/

#define MAXBUFFER (600)

/***************************************************************/
/*                         Variables                           */
/***************************************************************/

static char TerminalType [MAXBUFFER];
static unsigned int TypeIndex = 0;

/***************************************************************/
/*                         Declaraciones                       */
/***************************************************************/

void clearArray(char * arr, int size);
void overwriteArray(char * src, char * dest);
void printTerminal();
int interpretCommand();
void overwriteArrayUpTo(char * src, char * dest,char c);

/***************************************************************/
/*                      Funciones Publicas                     */
/***************************************************************/

int runTerminal(){

    clearArray(TerminalType,MAXBUFFER);
    TypeIndex = 0;
    printf(">>>>  "); 
    int exit=0;
    do{
        
		int key = readKey();

		if(key >0){     
            if(key == 8 ){
                if(TypeIndex>0){
                    TerminalType[--TypeIndex] = 0;
                    RemoveLastCharFromDisplay();
                }

            }else{ 

                TerminalType[TypeIndex++] = key;
                printTerminal();

                if(key == '\n'){
                    exit=interpretCommand();
                    clearArray(TerminalType,MAXBUFFER);
                    TypeIndex = 0;  
                    printf(">>>>  ");        
                }
                
            }
        }
	}while(!exit);

    return exit;
}

/***************************************************************/
/*                      Funciones Privadas                     */
/***************************************************************/

int interpretCommand(){
    char command[MAXBUFFER];
    char param1[MAXBUFFER];
    char param2[MAXBUFFER];
    char param3[MAXBUFFER];


    overwriteArrayUpTo(TerminalType,command,' ');
    overwriteArrayUpTo(TerminalType+strlen(command)+1,param1,' ');
    overwriteArrayUpTo(TerminalType+strlen(command)+strlen(param1)+2,param2,' ');
    overwriteArrayUpTo(TerminalType+strlen(command)+strlen(param1)+strlen(param2)+3,param3,' ');

    bool hasParam1 = !strcmp(param1,"");
    bool hasParam2 = !strcmp(param2,"");
    bool hasParam3 = !strcmp(param3,"");
    
    if(hasParam3){
        printfError("ERROR\n");
        return 0;
    }
    if(strcmp(command,"time") && !hasParam1 && !hasParam2)
        time();
    else if(strcmp(command,"man") && !hasParam1 && !hasParam2)
        man();
    else if(strcmp(command,"man") && hasParam1 && !hasParam2)
        explainCommand(param1);
    else if(strcmp(command,"infoReg") && !hasParam1 && !hasParam2)
        infoReg();
    else if(strcmp(command,"printMem") && hasParam1 && !hasParam2){
        int a = stringToHexa(param1);
        if(a==-1){
        printf("Invalid Position\n");
        return 0;
        }
        printMem(a);
    }
    else if(strcmp(command,"game") && !hasParam1 && !hasParam2){
        clearConsole();
        return 2;
    }
    else if(strcmp(command,"exit") && !hasParam1 && !hasParam2)
        return 1;
    else if(strcmp(command,"invalidOpcode") && !hasParam1 && !hasParam2){
        invalidOpcode();
        }
    else if(strcmp(command,"clear") && !hasParam1 && !hasParam2)
        clearConsole();
    else if(strcmp(command,"quotient") && hasParam1 && hasParam2){
        int a = stringToInt(param1), b = stringToInt(param2);
        quotient(a,b);
    }
    else
        printfError("%s%s%s%s: command not found \n",command,param1,param2,param3);    
    
    return  0;
}



void printTerminal(){
    
    if(TerminalType[0])
        putChar(TerminalType[TypeIndex-1]);
}



void clearArray(char * arr, int size){

    for (int i = 0; i < size; i++)
        arr[i] = 0;
}


void overwriteArray(char * src, char * dest){
    overwriteArrayUpTo(src,dest,0);
}

void overwriteArrayUpTo(char * src, char * dest,char c){
    clearArray(dest,MAXBUFFER);
    int i;
    for (i = 0; src[i]!=0 && src[i]!='\n' && i < MAXBUFFER && src[i]!=c; i++)
        dest[i] = src[i];
    if(i!=MAXBUFFER){
        dest[i]=0;
    }
}


