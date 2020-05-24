#include "../include/timer.h"
#include <Scheduler.h>
#include <MemManager.h>
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
#include <Pipe.h>
#include <ConsoleDriver.h>
#include <pcb.h>
#include <Sem.h>
#include <sbrk.h>


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
void dispatchMalloc(int increment, void ** buffer);
void dispatchFree(void ** buffer);
void dispatchMemState(void ** firstParam, void ** secondParam,void ** thirdParam);
void dispatchCreateProcess(char * firstParam, int * secondParam,function_t * thirdParam);
void dispatchKillProcess(int * firstParam);
void dispatchBlockProcess(int * firstParam);
void dispatchNiceProcess(int * firstParam,int secondParam);
void dispatchPs();
void dispatchGetPid(int * ret);
void dispatchExit();
void dispatchSem(int fd,void * firstParam, void * secondParam);
void dispatchSleep();
void dispatchPipes(int ind,void * firstParam, int secondParam,int * thirdParam);


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
			dispatchRead((uint64_t)firstParam,secondParam,thirdParam,fourthParam,fifthParam);
			break;
		case 0x81:
			dispatchWrite((uint64_t)firstParam,secondParam,thirdParam,fourthParam,fifthParam);
		break;
		case 0x82:
			dispatchDelete((uint64_t)firstParam,secondParam,thirdParam,fourthParam,fifthParam);
			break;
		case 0x86:{
		
			dispatchMalloc((uint64_t)firstParam,(void **) secondParam);
			break;
		}
		case 0x87:{ 
			dispatchFree((void **)firstParam);
			break;
			}
		case 0x88:{ 
			dispatchMemState((void **)firstParam, (void **)secondParam,(void **)thirdParam);
			break;
			}
		case 0x89:{ 
			dispatchCreateProcess((char *)firstParam,(int *) secondParam,(function_t *)thirdParam);
			break;
			}
		case 0x90:{ 
			dispatchKillProcess((int *)firstParam);
			break;
			}
		case 0x91:{ 
			dispatchNiceProcess((int *)firstParam,(uint64_t)secondParam);
			break;
			}
		case 0x92:{ 
			dispatchBlockProcess((int*)firstParam);
			break;
			}
		case 0x93:{ 
			dispatchPs();
			break;
			}					
		case 0x94:{ 
			dispatchGetPid((int*)firstParam);
			break;
			}					
		case 0x95:{ 
			dispatchExit();
			break;
			}
		case 0x96:{ 
			dispatchSem((uint64_t)firstParam,secondParam,thirdParam);
			break;
			}	
		case 0x97:{
			dispatchSleep();
			break;
		}
		case 0x98:{
			dispatchPipes((uint64_t)firstParam,secondParam,(uint64_t)thirdParam,(int*)fourthParam);
			break;
		}
		case 0x99:{
			setDummyProcess((process_Func_t)firstParam);
			break;
		}
		default: break;
	}

	return 0;
}
void * int_20(void * ptr) {
	return timer_handler(ptr);
}

void int_21(){

	readKey();

	//char * sem = getKeyboardSem();

	//sempost(sem);

	AwakeProcess();

}




void dispatchMalloc(int increment, void ** buffer) { 
	void * aux=malloc(increment);
	*buffer=aux;

}

void dispatchFree(void ** ptr){

	free(*ptr);
}

void dispatchMemState(void ** firstParam,void ** secondParam,void ** thirdParam){
	mem_state(firstParam,secondParam,thirdParam);
}

void dispatchCreateProcess(char * firstParam, int * secondParam,function_t * thirdParam){
	 createProcess(firstParam,secondParam,thirdParam);
}
void dispatchKillProcess(int * firstParam){
	killProcess(firstParam);
}

void dispatchSleep(){
	SleepProcess();
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

void dispatchExit(){
	Exit();
}

void  dispatchSem(int fd,void * firstParam, void * secondParam){
	switch (fd)
	{
	case 0:{
		*(int *) secondParam = semopen((char *)firstParam, (int *) secondParam);
		break;
		}
	case 1:{
		*(bool *)secondParam =  semwait((char *)firstParam);
		break;
		}
	case 2:{
		sempost((char *)firstParam);
		break;
		}
	case 3:{
		semclose((char *)firstParam);
		break;
	}
	case 4:{
		semInfo();
		break;
	}

	
	default:
		break;
	}

}

void  dispatchPipes(int ind,void * firstParam, int secondParam,int * thirdParam){
	switch (ind){
	case 0:{
		openPipe((char *)firstParam,secondParam,thirdParam);
		break;
		}
	case 1:{
		closePipes((int*)firstParam);
		break;
		}
	case 2:{
		pipes();
		break;
		}
	default:
		break;
	}

}


void dispatchRead(int fd,void * firstParam, void * secondParam,void * thirdParam,void * fourthParam){

	switch(fd){
		case FD_STDOUT: { break;}
		case FD_STDERR: { break;}
		case FD_STDIN: { 

			char * buffer = (char *) firstParam;
      		int bufferSize = (uint64_t)secondParam;
			
			read(buffer,bufferSize,(int *) thirdParam);			
			
			break;
		}
		case FD_SPEAKER: { break;}
		case FD_SQUARES: { break;}
		case FD_MEMORY: { 
			
			uint64_t position = (uint64_t)firstParam;
			char * buff = secondParam;
			int size = (uint64_t)thirdParam;

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
			*value = handleTimeRequest((uint64_t)firstParam);

			break;
			}
		case FD_STDOUT_COLOR: { break;}
		default:{
			char * buffer = (char *) firstParam;
			int bufferSize = (uint64_t)secondParam;
			readPipe(fd,buffer,bufferSize,(int *)thirdParam);			
			
		}
	}
}




void dispatchDelete(int fd,void * firstParam, void * secondParam,void * thirdParam,void * fourthParam){
	switch(fd){
		case FD_STDOUT: { 

			if((uint64_t)firstParam == DELETE_CURRENT_CHAR){
				removeLastChar();
			}else if((uint64_t)firstParam == DELETE_ALL_DISPLAY){
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
			write(buffer,(int *)secondParam);
			break;
			return;
		}
		case FD_STDERR:{
            char * buffer = firstParam;
			if(buffer[1] == 0)
			   putCharColor(*buffer,0xFF0000,0x0000);
			else
				printfColor(0xFF0000,0x0000,buffer);
            break;
        }
		case FD_STDIN: break;
        case FD_SPEAKER:{
            playSound((uint64_t)firstParam);
            break;
        }
		case FD_SQUARES:{ 
			int * pos = firstParam;
			int length = (uint64_t)secondParam;
			int height=(uint64_t)thirdParam;
			int fontColor=(uint64_t)fourthParam;
			
			print(pos,length,height,fontColor);
			break;
			}
		case FD_MEMORY: break;
		case FD_REGISTERS: break;
		case FD_DEVICE_INFO: {
			setSize((uint64_t)firstParam);
			break;
		}
		case FD_TIMER: break;
		case FD_TIME: break;
		case FD_STDOUT_COLOR:{
			 printLineColor(firstParam);

			break;
		}
		default:{
			char * buffer = firstParam;
			writePipe(fd,buffer,(int *)secondParam);
			break;
						
		}
	
	}
	
}



