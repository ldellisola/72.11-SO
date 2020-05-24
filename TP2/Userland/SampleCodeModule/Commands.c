#include "include/Commands.h"

#include <stdbool.h>

#include "../Include/deviceInfo.h"
#include "../Include/String.h"
#include "../Include/Curses.h"
#include "../Include/Time.h"
#include "../Include/MemManager.h"
#include "../Include/Sem.h"
#include "../Include/Syscalls.h"

extern void __UD2__();


int quotient(int argc, char ** argv){

    if(argc != 2){
        printf("This functions take 2 arguments");
        return 0;
    }
    
    int a = stringToInt(argv[0]), b = stringToInt(argv[1]);

    printf("I'm going to calculate the quotient of %d divided by %d\n",a,b);

    int result =  (a)/ (b);
    
    printf("The result is %d\n",result);
    return 0;
}



int blockProcess(int argc, char ** argv){

    if(argc != 1){
        printf("this function takes 1 argument\n");
        return 0;
    }

    int pid=stringToInt(argv[0]);
    process_manager(3,(void *)&pid,0,0);

    if(pid == -2)
        printf("No tiene permiso para acceder a ese proceso\n");
    else if(pid == -1)
        printf("No es un proceso %s, no esta permitida esa accion\n",argv[0]);
    return 0;
}

int ProcessState(int argc, char ** argv){
    ps();
    return 0;
}

int killProcess(int argc, char **argv){

    if( argc != argc){
        printf("The function only takes 1 parameter\n");
        return 0;
    }

    int pid = stringToInt(argv[0]);

    process_manager(1,(void *)&pid,0,0);
    if(pid==-1)
        printf("No es un proceso %s, no esta permitida esa accion\n",argv[0]);
    else if(pid== -2)
        printf("No tiene permiso para acceder a ese proceso\n");
    return 0;
}

int niceProcess(int argc, char ** argv){

    if(argc != 2){
        printf("This function only takes 2 arguments\n");
        return 0;
    }

    int pid=stringToInt(argv[0]);
    int prior=stringToInt(argv[1]);

    process_manager(4,(void *)&pid,(void *)prior,0);
    //nice_process(&pid,prior);

    if(pid==-1)
        printf("No es un proceso %s, no esta permitida esa accion\n",argv[0]);
    else if(pid == -2)
        printf("No tiene permiso para acceder a ese proceso\n");
    else if(pid == -3)
        printf("No es una prioridad aceptada, seleccione 0-1-2\n");
    return 0;
}


int invalidOpcode(int argc, char **argv){
    
    __UD2__();

    return 0;
}

int printMemoryState(int argc, char ** argv){
    void * first=NULL;
    void * last=NULL;
    void *next=NULL;

    mem_manager(2,(void *)&first,(void *)&last,(void *)&next);
    printf("\nMemory starts at: 0x%x and finishes at : 0x%x\n",first,last);
    printf("Next free position: 0x%x\n",next);
    return 0;
}

void printMem(int argc, char ** argv){

    if(argc != 1){
        printf("Invalid Arguments");
        return;
    }

    uint64_t memDirection = stringToHexa(argv[0]);

    if(memDirection == -1){
        printf("Invalid Position\n");
        return;
    }

    char rawMem[32];
    readMem(memDirection,rawMem,32);
    
    char printStr[(16 * 3) + 1];

    for(int j=0 ; j <2 ; j++){
        for(int i = 0 ; i < 16 ; i++){
            HexToStringSPECIAL(printStr + i*3,3,rawMem[16 * j +i]);
            printStr[(i*3)-1] = ' ';
        }
        printf("%s\n",printStr);
    }

    return;

}


void cleanArr(char * arr, int size){
    for(int i = 0; i < size ; i++)
        arr[i] = 0;
}


void printRegisters(uint64_t * storage){
    
	printf("RAX: 0x%x\n",storage[14]);
    
	printf("RBX: 0x%x\n",storage[13]);
    
	printf("RCX: 0x%x\n",storage[12]);
    	
	printf("RDX: 0x%x\n",storage[11]);
    
	printf("RBP: 0x%x\n",storage[15]);

	printf("RDI: 0x%x\n",storage[9]);

	printf("RSI: 0x%x\n",storage[8]);
    	
	printf("R8: 0x%x\n",storage[7]);

	printf("R9: 0x%x\n",storage[6]);
	
	printf("R10: 0x%x\n",storage[5]);

	printf("R11: 0x%x\n",storage[4]);
	
	printf("R12: 0x%x\n",storage[3]);
	
	printf("R13: 0x%x\n",storage[2]);
	
	printf("R14: 0x%x\n",storage[1]);
	
	printf("R15: 0x%x\n",storage[0]);

	printf("RSP: 0x%x\n",storage[10]);	
    return;

}

int time(int argc, char **argv){
    int dayofMonth = GetDayOfMonth();
    int month = GetMonth();
    int year = GetYear();
    int hour = GetHours();
    int minutes = GetMinutes();
    int seconds = GetSeconds();
    printf("%d/%d/%d %d:%d:%d \n",dayofMonth,month,year,hour, minutes,seconds);   
    return 0;

}

int malloc_test(int argc, char ** argv) {

    printMemoryState(0,NULL);
    printf("TEST PIDE 100:");
    char * test = (char *) malloc(100);
    printf("Mi direccion es %x \n",test);
    printMemoryState(0,NULL);
    
    printf("\nTEST 0 PIDE 10:");
    char * test0= (char *) malloc(10);
    printf("Mi direccion es %x \n",test0);
    printMemoryState(0,NULL);
    printf("\nTEST LIBERA 100\n");
    free(test);

    printMemoryState(0,NULL);
    printf("\nTEST PIDE 2\n");
    test = (char *) malloc(2);
    printf("Mi direccion es %x \n",test);
    printMemoryState(0,NULL);
    printf("\nTEST 1 PIDE 5:");
    char * test1 = (char *) malloc(5);
    printf("Mi direccion es %x \n",test1);
    printMemoryState(0,NULL);
    printf("\nTEST LIBERA 2\n");
    printf("\nTEST 1 LIBERA 5\n");    
    free(test);
    free(test1);
    printMemoryState(0,NULL);
    printf("\nTEST 2 PIDE 10:");
    char * test2= (char *) malloc(10);
    printf("Mi direccion es %x \n",test2);
    printMemoryState(0,NULL);
    free(test);
    free(test1);
    free(test2);
    free(test0);

    return 0;
}

void fillString(char * test) {

    char * str = "works:D";
    for(int i = 0 ; str[i]!= 0; i++){
        test[i] = str[i];
    }


}