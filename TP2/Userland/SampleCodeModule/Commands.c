#include "include/Commands.h"

#include "../Include/deviceInfo.h"
#include "../Include/String.h"
#include "../Include/Curses.h"
#include "../Include/Time.h"
#include "../Include/MemManager.h"


extern void __UD2__();

int quotient(int a, int b){

    printf("I'm going to calculate the quotient of %d divided by %d\n",a,b);

    int result =  (a)/ (b);
    
    printf("The result is %d\n",result);
    return 0;
}

int help(){
    printf("\nCOMMANDS\n\nmalloctest\ntime\ninvalidOpcode\ninfoReg\nquotient\nprintMem\nclear\nblock\nkill\nnice\nloop\nmem\n\nTESTS\n\ntestMem\n\nhelp\n");
    return 0;
}

int explainCommand(char * command){

    if(strcmp(command,"time")){
        printf("Command:\n        time\n");
        printf("It shows the current date and time.\n");
    }
    else if(strcmp(command,"help")){
        printf("Command:\n        help ?[Argument_1]\n");
        printf("It enumerates all the commands available on this shell\n");
        printf("If there's an argument, it will tell you the funcition of that command\n");
    }
    else if(strcmp(command,"infoReg")){
        printf("Command:\n        infoReg\n");
        printf("It prints on screen the actual value of the registers\n");
    }
    else if(strcmp(command,"printMem")){
        printf("Command:\n        printMem [Argument_1]\n");
        printf("It prints on screen the first 32 bytes of memory from any given memory position.\n");
    }
    else if(strcmp(command,"invalidOpcode")){
        printf("Command:\n        invalidOpcode\n");
        printf("It is a test to validate the INVALID OPCODE exception.\n");
    }
    else if(strcmp(command,"clear")){
        printf("Command:\n        clear\n");
        printf("It clears the screen.\n");
    }
    else if(strcmp(command,"quotient")){
        printf("Command:\n        quotient [Argument_1] [Argument_2]\n");
        printf("It calculates the quotient of the division of [Argument_1] by [Argument_2]. This can be used to test the DIVISION BY ZERO exception.\n");
    }else{
        printf("That command does not exist!\n");
    }
    return 0;
}

int invalidOpcode(){
    
    __UD2__();

    return 0;
}

int printMemoryState(){
    void * first=NULL;
    void * last=NULL;
    void *next=NULL;

    memory_state(&first,&last,&next);
    printf("\nMemory starts at: 0x%x and finishes at : 0x%x\n",first,last);
    printf("Proxima memoria libre: 0x%x\n",next);
    return 0;
}

int printMem(uint64_t memDirection){

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

    return 0;

}


void cleanArr(char * arr, int size){
    for(int i = 0; i < size ; i++)
        arr[i] = 0;
}


int printRegisters(uint64_t * storage){
    
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
    return 0;

}

int time(){
    int dayofMonth = GetDayOfMonth();
    int month = GetMonth();
    int year = GetYear();
    int hour = GetHours();
    int minutes = GetMinutes();
    int seconds = GetSeconds();
    printf("%d/%d/%d %d:%d:%d \n",dayofMonth,month,year,hour, minutes,seconds);   
    return 0;

}

int malloc_test() {

    printMemoryState();
    printf("TEST PIDE 100:");
    char * test = (char *) malloc(100);
    printf("Mi direccion es %x \n",test);
    printMemoryState();
    
    printf("\nTEST 0 PIDE 10:");
    char * test0= (char *) malloc(10);
    printf("Mi direccion es %x \n",test0);
    printMemoryState();
    printf("\nTEST LIBERA 100\n");
    free(test);
    printMemoryState();
    printf("\nTEST PIDE 2\n");
    test = (char *) malloc(2);
    printf("Mi direccion es %x \n",test);
    printMemoryState();
    printf("\nTEST 1 PIDE 5:");
    char * test1 = (char *) malloc(5);
    printf("Mi direccion es %x \n",test1);
    printMemoryState();
    printf("\nTEST LIBERA 2\n");
    printf("\nTEST 1 LIBERA 5\n");    
    free(test);
    free(test1);
    printMemoryState();
    printf("\nTEST 2 PIDE 10:");
    char * test2= (char *) malloc(10);
    printf("Mi direccion es %x \n",test2);
    printMemoryState();
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