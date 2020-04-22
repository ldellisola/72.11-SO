#include "../include/timer.h"
#include <stdint.h>
#include <Curses.h>
#include <String.h>
#include <keyboard.h>
#include <deviceInfo.h>
#include <Time.h>
#include <ReadDispatcher.h>
#include <Debugger.h>
#include <SpeakerDriver.h>
#include <font.h>
#include <VideoDriver.h>
#include <ConsoleDriver.h>
#include <sbrk.h>
#include <pcb.h>
#include <Scheduler.h>


#define FD_STDOUT 				(0x01)
#define FD_STDERR 				(0x02)
#define FD_STDIN 				(0x03)
#define FD_SPEAKER 				(0x04)
#define FD_SQUARES 				(0x05)
#define FD_MEMORY 				(0x06)
#define FD_REGISTERS			(0x07)
#define FD_DEVICE_INFO 			(0x08)
#define FD_TIMER				(0x09)
#define FD_TIME					(0x0A)
#define FD_STDOUT_COLOR			(0x0B)

#define DELETE_CURRENT_CHAR 1
#define DELETE_ALL_DISPLAY 3



void dispatchWrite(int fd,void * firstParam, void * secondParam,void * thirdParam,void * fourthParam);
void dispatchDelete(int fd,void * firstParam, void * secondParam,void * thirdParam,void * fourthParam);
void dispatchRead(int fd,void * firstParam, void * secondParam,void * thirdParam,void * fourthParam);
void dispatchSbrk(int increment, void ** buffer);
void dispatchMemState(void ** firstParam, void ** secondParam,void ** thirdParam);
void * dispatchCreateProcess(char * firstParam, int * secondParam,function_t * thirdParam);
void * dispatchKillProcess(int * firstParam);
void dispatchBlockProcess(int * firstParam);
void dispatchNiceProcess(int * firstParam,int secondParam);
void dispatchPs();
void dispatchGetPid(int * ret);

static void * int_20(void * ptr);
static void int_21();



void * irqDispatcher(uint64_t irq, void * firstParam,void * secondParam, void * thirdParam,void * fourthParam,void * fifthParam) {


	switch (irq) {
		case 0:{
			void * ptrsp = int_20(firstParam);
			return ptrsp;
			break;
		}
		case 1:
			int_21();
			break;
		case 0x80:
			dispatchRead(firstParam,secondParam,thirdParam,fourthParam,fifthParam);
			break;
		case 0x81:
			dispatchWrite(firstParam,secondParam,thirdParam,fourthParam,fifthParam);
		break;
		case 0x82:
			dispatchDelete(firstParam,secondParam,thirdParam,fourthParam,fifthParam);
			break;
		case 0x86:{
		
			dispatchSbrk(firstParam, secondParam);
			break;
		}
		case 0x87:{ 
			dispatchBRK(firstParam, (int*)secondParam);
			break;
			}
		case 0x88:{ 
			dispatchMemState(firstParam, secondParam,thirdParam);
			break;
			}
		case 0x89:{ 
			//DEBUG("%s","LLego syscall CREATE Process")
			uint64_t * p = dispatchCreateProcess(firstParam, secondParam,thirdParam);
			DEBUG("Nuevo SP: 0x%x",p)
			return p;
			break;
			}
		case 0x90:{ 
			return dispatchKillProcess(firstParam);
			break;
			}
		case 0x91:{ 
			dispatchNiceProcess(firstParam,secondParam);
			break;
			}
		case 0x92:{ 
			dispatchBlockProcess(firstParam);
			break;
			}
		case 0x93:{ 
			dispatchPs();
			break;
			}					
		case 0x94:{ 
			dispatchGetPid(firstParam);
			break;
			}
	}

	return 0;
}
void * int_20(void * ptr) {
	void * ptr2 = timer_handler(ptr);

	return ptr2;
}

void int_21(){

	 readKey();
	
}


void dispatchSbrk(int increment, void ** buffer) { 
	sbrk_handler(increment, buffer);
}

void dispatchBRK(void * ptr,int * retValue){

	*retValue = brk_handler(ptr);
}

void dispatchMemState(void ** firstParam,void ** secondParam,void ** thirdParam){
	mem_state(firstParam,secondParam,thirdParam);
}

void * dispatchCreateProcess(char * firstParam, int * secondParam,function_t * thirdParam){
	return createProcess(firstParam,secondParam,thirdParam);
}
void * dispatchKillProcess(int * firstParam){
	return killProcess(firstParam);
}


void dispatchBlockProcess(int * firstParam){
	blockProcess(firstParam);
}
void dispatchNiceProcess(int * firstParam,int secondParam){
	niceProcess(firstParam,secondParam);
}
void dispatchPs(){
	ps();
}

void dispatchGetPid(int * ret){
	*ret=getpid();
}
void dispatchRead(int fd,void * firstParam, void * secondParam,void * thirdParam,void * fourthParam){

	switch(fd){
		case FD_STDOUT: { break;}
		case FD_STDERR: { break;}
		case FD_STDIN: { 

			char * buffer = (char *) firstParam;
            int bufferSize = secondParam;
			int i = 0;		
			int temp;
			do{
				temp = returnKey();
				
				if( temp != -1 ){
					buffer[i++]=temp;
				}

			}while( temp!= -1 && i <bufferSize-1 );
			buffer[i] = 0;
			
			break;
		}
		case FD_SPEAKER: { break;}
		case FD_SQUARES: { break;}
		case FD_MEMORY: { 
			
			uint64_t position = firstParam;
			char * buff = secondParam;
			int size = thirdParam;

			readMem(position,buff,size);


			break;
		}
		case FD_REGISTERS: { 
			getRegisters(firstParam,secondParam,thirdParam);
			break;
		}
		case FD_DEVICE_INFO: { 

			// printf("FD: %d. PAR1 %d. PAR2 %d. PAR3 %d. PAR4 %d.",fd,firstParam,secondParam,thirdParam,fourthParam);

			getDeviceInfo(firstParam);
			break;
		}
		case FD_TIMER: { 

			uint64_t * ticks = firstParam;
            *ticks = ticks_elapsed();	
			break;
		}
		case FD_TIME: { 
			int * value = secondParam;
			*value = handleTimeRequest(firstParam);

			break;
			}
		case FD_STDOUT_COLOR: { break;}
	}
}




void dispatchDelete(int fd,void * firstParam, void * secondParam,void * thirdParam,void * fourthParam){
	switch(fd){
		case FD_STDOUT: { 

			if(firstParam == DELETE_CURRENT_CHAR){
				removeLastChar();
			}else if(firstParam == DELETE_ALL_DISPLAY){
				clearConsole();
			}
			break;
		}
		case FD_STDERR: { break;}
		case FD_STDIN: { break;}
		case FD_SPEAKER: { 
			stopSound();
			break;
		}
		case FD_SQUARES: { break;}
		case FD_MEMORY: { break;}
		case FD_REGISTERS: { break;}
		case FD_DEVICE_INFO: { break;}
		case FD_TIMER: { break;}
		case FD_TIME: { break;}
		case FD_STDOUT_COLOR: { break;}
	}
	
}



void dispatchWrite(int fd,void * firstParam, void * secondParam,void * thirdParam,void * fourthParam){

	switch(fd){
		case FD_STDOUT:{
			char * buffer = firstParam;

            if(buffer[1] == 0)
                putChar(*buffer);
			else
                printf(buffer);
	
			break;

			return;
		}
		case FD_STDERR:{
            char * buffer = firstParam;
			if(buffer[1] == 0)
			   putCharColor(*buffer,0xFF0000,0x0000);
			else
				printfColor(buffer,0xFF0000,0x0000);
            break;
        }
		case FD_STDIN: break;
        case FD_SPEAKER:{
            playSound(firstParam);
            break;
        }
		case FD_SQUARES:{ 
			int * pos = firstParam;
			int length = secondParam;
			int height=thirdParam;
			int fontColor=fourthParam;
			
			print(pos,length,height,fontColor);
			break;
			}
		case FD_MEMORY: break;
		case FD_REGISTERS: break;
		case FD_DEVICE_INFO: {
			setSize(firstParam);
			break;
		}
		case FD_TIMER: break;
		case FD_TIME: break;
		case FD_STDOUT_COLOR:{
			 printLineColorAt(firstParam);

			break;
		}
	}
	
}



