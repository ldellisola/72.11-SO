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

#define FD_STDOUT (0x01)
#define FD_STDERR (0x02)
#define FD_STDIN (0x03)
#define FD_SPEAKER (0x04)
#define FD_SQUARES (0x05)
#define FD_MEMORY (0x06)
#define FD_REGISTERS (0x07)
#define FD_DEVICE_INFO (0x08)
#define FD_TIMER (0x09)
#define FD_TIME (0x0A)
#define FD_STDOUT_COLOR (0x0B)

#define DELETE_CURRENT_CHAR 1
#define DELETE_ALL_DISPLAY 3

void dispatchWrite(int fd, void *firstParam, void *secondParam, void *thirdParam, void *fourthParam);
void dispatchDelete(int fd, void *firstParam, void *secondParam, void *thirdParam, void *fourthParam);
void dispatchRead(int fd, void *firstParam, void *secondParam, void *thirdParam, void *fourthParam);


void dispatchWrite(int fd,void * firstParam, void * secondParam,void * thirdParam,void * fourthParam);
void dispatchDelete(int fd,void * firstParam, void * secondParam,void * thirdParam,void * fourthParam);
void dispatchRead(int fd,void * firstParam, void * secondParam,void * thirdParam,void * fourthParam);
void dispatchSbrk(int increment, void ** buffer);


static void int_20();
static void int_21();

void irqDispatcher(uint64_t irq, void *firstParam, void *secondParam, void *thirdParam, void *fourthParam, void *fifthParam)
{

	switch (irq)
	{
	case 0:
		int_20();
		break;
		case 0x82:
			dispatchDelete(firstParam,secondParam,thirdParam,fourthParam,fifthParam);
			break;
		case 0x86:{
		
			dispatchSbrk(firstParam, secondParam);
			break;
		}
		case 0x87: dispatchBRK(firstParam, (int*)secondParam);
	}
}

void int_20()
{
	timer_handler();
}

void int_21()
{

	readKey();
}

void dispatchRead(int fd, void *firstParam, void *secondParam, void *thirdParam, void *fourthParam)
{

void dispatchSbrk(int increment, void ** buffer) { 
	sbrk_handler(increment, buffer);
}

void dispatchBRK(void * ptr,int * retValue){

	*retValue = brk_handler(ptr);
}


void dispatchRead(int fd,void * firstParam, void * secondParam,void * thirdParam,void * fourthParam){

		break;
	}
	case FD_SPEAKER:
	{
		break;
	}
	case FD_SQUARES:
	{
		break;
	}
	case FD_MEMORY:
	{

		uint64_t position = (uint64_t)firstParam;
		char *buff = (char *)secondParam;
		int size = (int)thirdParam;

		readMem(position, buff, size);

		break;
	}
	case FD_REGISTERS:
	{
		getRegisters((Registers *)firstParam, (uint64_t *)secondParam, (uint64_t *)thirdParam);
		break;
	}
	case FD_DEVICE_INFO:
	{

		// printf("FD: %d. PAR1 %d. PAR2 %d. PAR3 %d. PAR4 %d.",fd,firstParam,secondParam,thirdParam,fourthParam);

		getDeviceInfo(firstParam);
		break;
	}
	case FD_TIMER:
	{

		uint64_t *ticks = (uint64_t *)firstParam;
		*ticks = ticks_elapsed();
		break;
	}
	case FD_TIME:
	{
		int *value = (int *)secondParam;
		*value = handleTimeRequest((int)firstParam);

		break;
	}
	case FD_STDOUT_COLOR:
	{
		break;
	}
	}
}

void dispatchDelete(int fd, void *firstParam, void *secondParam, void *thirdParam, void *fourthParam)
{
	switch (fd)
	{
	case FD_STDOUT:
	{

		if ((int)firstParam == DELETE_CURRENT_CHAR)
		{
			removeLastChar();
		}
		else if ((int)firstParam == DELETE_ALL_DISPLAY)
		{
			clearConsole();
		}
		break;
	}
	case FD_STDERR:
	{
		break;
	}
	case FD_STDIN:
	{
		break;
	}
	case FD_SPEAKER:
	{
		stopSound();
		break;
	}
	case FD_SQUARES:
	{
		break;
	}
	case FD_MEMORY:
	{
		break;
	}
	case FD_REGISTERS:
	{
		break;
	}
	case FD_DEVICE_INFO:
	{
		break;
	}
	case FD_TIMER:
	{
		break;
	}
	case FD_TIME:
	{
		break;
	}
	case FD_STDOUT_COLOR:
	{
		break;
	}
	}
}

void dispatchWrite(int fd, void *firstParam, void *secondParam, void *thirdParam, void *fourthParam)
{

	switch (fd)
	{
	case FD_STDOUT:
	{
		char *buffer = (char *)firstParam;

		if (buffer[1] == 0)
			putChar(*buffer);
		else
			printf(buffer);

		break;

		return;
	}
	case FD_STDERR:
	{
		char *buffer = (char *)firstParam;
		if (buffer[1] == 0)
			putCharColor(*buffer, 0xFF0000, 0x0000);
		else
			printfColor(0xFF0000, 0x0000, buffer);
		break;
	}
	case FD_STDIN:
		break;
	case FD_SPEAKER:
	{
		playSound((uint32_t)firstParam);
		break;
	}
	case FD_SQUARES:
	{
		int *pos = (int *)firstParam;
		int length = (int)secondParam;
		int height = (int)thirdParam;
		int fontColor = (int)fourthParam;

		print(pos, length, height, fontColor);
		break;
	}
	case FD_MEMORY:
		break;
	case FD_REGISTERS:
		break;
	case FD_DEVICE_INFO:
	{
		setSize((unsigned int)firstParam);
		break;
	}
	case FD_TIMER:
		break;
	case FD_TIME:
		break;
	case FD_STDOUT_COLOR:
	{
		printLineColorAt((ColorChar *)firstParam);

		break;
	}
	}
}
