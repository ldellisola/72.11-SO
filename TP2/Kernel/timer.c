#include "../include/timer.h"
#include <Curses.h>
#include <stdlib.h>

#include <Scheduler.h>


static unsigned long ticks = 0;
static int priorityCounter = 0;

void *timer_handler(void *ptr)
{
	ticks++;


	if(ticks %(2*1) != 0)
	{
		return ptr;
	}
	if(priorityCounter != 0)
	{
		priorityCounter--;
		return ptr;
	}
	
	process *old = GetCurrentProcess();

	if (old != NULL)
	{
		old->pcb->sp = ptr;
	}

	
	
	roundRobin();

	process *new = GetCurrentProcess();

	priorityCounter = new->pcb->priority;

	if (new == NULL)
		return ptr;


	return new->pcb->sp;
}

int ticks_elapsed()
{
	return ticks;
}

int seconds_elapsed()
{
	return ticks / 18;
}
