#include "include/Debugger.h"
#include <deviceInfo.h>
#include <Curses.h>

void ThrowCustomException(char * str){
    PrintExceptionDetails(str,0,0);

    printfColor("\n\n\nPress any key to continue",0xFF0000,0xFFFFFF);

	do{
		readKey();
	}
	while (returnKey() == -1);

	clearConsole();
}
#define WHITE 0xFFFFFF
#define RED 0xFF0000

void PrintExceptionDetails(char * name, uint64_t * stackPointer, uint64_t * instructionPointer){


	char temp[17]={'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0',0};
    
	Registers reg;
    getRegisters(&reg,stackPointer,instructionPointer);



	printfColor("EXCEPTION: %s | IP: 0X%X\n",WHITE,RED,name,reg.rip);

	printf("RAX: 0X%X | RBX: 0X%X | RCX: 0X%X | RDX: 0X%X\n",reg.rax,reg.rbx,reg.rcx,reg.rdx);

	printf("RDI: 0X%X | RSI: 0X%X | R08: 0X%X | R09: 0X%X\n",reg.rdi,reg.rsi,reg.r8,reg.r9);

	printf("R10: 0X%X | R11: 0X%X | R12: 0X%X | R13: 0X%X\n",reg.r10,reg.r11,reg.r12,reg.r13);

	printf("R14: 0X%X | R15: 0X%X \n",reg.r14,reg.r15);

    return;

    

}

bool assertEqual(void * val1, void * val2){

    if(val1 == val2){
        char temp[100];
        char temp2 [20];

        append("Values EQUAL:  ",temp,100);
        IntToString(temp2,20,val1);
        
        append(temp2,temp,100);
        
        for(int i = 0 ; i < 20 ;i++)
            temp2[i] = 0;
        
        IntToString(temp2,20,val2);

        append(" == ",temp,100);

        append(temp2,temp,100);

       // formatString(temp,75,"Values %d == %d",val1,val2);
        ThrowCustomException(temp);
    }

    return val1 == val2;
}

bool assertNotEqual(void * val1, void * val2){

        if(val1 != val2){
        char temp[100];
        char temp2 [20];

        append("Values NOT EQUAL:  ",temp,75);
        IntToString(temp2,20,val1);
        
        append(temp2,temp,100);
        
        for(int i = 0 ; i < 20 ;i++)
            temp2[i] = 0;
        
        IntToString(temp2,20,val2);

        append(" != ",temp,100);

        append(temp2,temp,100);

       // formatString(temp,75,"Values %d == %d",val1,val2);
        ThrowCustomException(temp);
    }

    return val1 != val2;

}