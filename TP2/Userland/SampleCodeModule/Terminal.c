#include <stdarg.h>
#include "../Include/Syscalls.h"
#include "include/Terminal.h"
#include "../Include/Curses.h"
#include "include/Commands.h"
#include "../Include/String.h"
#include <stdlib.h>
#include <stdbool.h>
#include "include/Exec.h"
#include "include/Process.h"



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
    else if(strcmp(command,"help") && !hasParam1 && !hasParam2)
        help();
    else if(strcmp(command,"help") && hasParam1 && !hasParam2)
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
    else if(strcmp(command,"invalidOpcode") && !hasParam1 && !hasParam2){
        invalidOpcode();
        }
    else if(strcmp(command,"clear") && !hasParam1 && !hasParam2)
        clearConsole();
    else if(strcmp(command,"quotient") && hasParam1 && hasParam2){
        int a = stringToInt(param1), b = stringToInt(param2);
        quotient(a,b);
    }
    else if (strcmp(command,"malloctest")) {
        malloc_test();
    }
    else if (strcmp(command,"mem")) {
        printMemoryState();
    }
     else if(strcmp(command,"loop")){
        int status=0;
        if(hasParam1 && strcmp(param1,"&"))
            status=1;
        exec(command,status,loop,0);
        
    }
    else if(strcmp(command,"kill") && hasParam1){
        int pid = stringToInt(param1);    
        
        kill_process(&pid);
        if(pid==-1)
            printf("No es un proceso %s, no esta permitida esa accion\n",param1);
        else if(pid== -2)
            printf("No tiene permiso para acceder a ese proceso\n");
    }
    else if(strcmp(command,"nice") && hasParam1 && hasParam2){
        int pid=stringToInt(param1);   
        
        int prior=stringToInt(param2); 
        
        nice_process(&pid,prior);
        
        if(pid==-1)
            printf("No es un proceso %s, no esta permitida esa accion\n",param1);
        else if(pid == -2)
            printf("No tiene permiso para acceder a ese proceso\n");
        else if(pid == -3)
            printf("No es una prioridad aceptada, seleccione 0-1-2\n");

    }
       else if(strcmp(command,"block") && hasParam1){
        int pid=stringToInt(param1);    
        block_process(&pid);

        if(pid == -2)
            printf("No tiene permiso para acceder a ese proceso\n");
        else if(pid == -1)
            printf("No es un proceso %s, no esta permitida esa accion\n",param1);
        
    }
     else if (strcmp(command,"ps")) {
        ps();
    }
    else if (strcmp(command,"testMem")) {
        int status=0;
        if(strcmp(param1,"&"))
            status=1;
        exec(command,status,test_mm,0);
    }
    else if (strcmp(command,"testProcess")) {
        int status=0;
        if(strcmp(param1,"&"))
            status=1;
        exec(command,status,test_processes,0);
    }
    else if(strcmp(command,"semTest") && hasParam1){
        int status=0;
        if(hasParam2 && strcmp(param2,"&"))
            status=1;
        exec("semTest",status,semTest,1,param1);
        
    }
    else if(strcmp(command,"sem"))
        semInfo();
    else if(strcmp(command,"testSem"))
        testSem();    
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


