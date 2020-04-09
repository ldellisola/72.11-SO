#include <deviceInfo.h>
#include <Curses.h>
#include <VideoDriver.h>
#include <font.h>


typedef struct{
    unsigned int bbp;
    unsigned int charHeight;
    unsigned int charWidht;
    unsigned int screenHeight;
    unsigned int screenWidth;
}DeviceInfo;


void getDeviceInfo(void* ptr){
    DeviceInfo * dev = ptr;

    int bbp;

    getBpp(&bbp);
    dev->bbp = bbp;

    dev->charHeight = CHAR_HEIGHT;
    dev->charWidht = CHAR_WIDTH;
    dev->screenHeight = SCREEN_HEIGHT;
    dev->screenWidth = SCREEN_WIDTH;

	// printf("SCREEN H: %d, W: %d\n", SCREEN_WIDTH, SCREEN_WIDTH);

    

}


void getRegisters(Registers * reg,uint64_t * stackPointer,uint64_t * instructionPointer){
   
    reg->rax = *(stackPointer+14);
    reg->rbx = *(stackPointer+13);
    reg->rcx = *(stackPointer+12);
    reg->rdx = *(stackPointer+11);
    reg->rbp = *(stackPointer+10);
    reg->rdi = *(stackPointer+9);
    reg->rsi = *(stackPointer+8);
    reg -> r8 = *(stackPointer+7);
    reg -> r9 = *(stackPointer+6);
    reg->r10 = *(stackPointer+5);
    reg->r11 = *(stackPointer+4);
    reg->r12 = *(stackPointer+3);
    reg->r13 = *(stackPointer+2);
    reg->r14 = *(stackPointer+1);
    reg->r15 = *(stackPointer);
    reg->rip = instructionPointer;

}

void readMem(uint64_t position, char * buff, unsigned size){

    char * memory = (char *) position;

    for (int i = 0; i < size; i++)
        buff[i] = memory[i];
    
}