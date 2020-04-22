#include "../include/timer.h"
#include <Curses.h>
#include <stdlib.h>

#include <Scheduler.h>


static unsigned long ticks = 0;
static int priorityCounter = 0;

void *timer_handler(void *ptr)
{
	ticks++;

	if(HasStoppedExcecution()){
		return ptr;
	}

	// DEBUG("PRIOTITY: %d",priorityCounter)
	if(ticks %(2)!= 0)//if (priorityCounter != 0)
	{
		return ptr;
	}
	if(priorityCounter != 0)
	{
		priorityCounter--;
		return ptr;
	}
	 //DEBUG("Intentando de cambiar de proceso. Viene SP 0x%x", ptr)
	
	process *old = GetCurrentProcess();

	if (old != NULL)
	{
		old->pcb->sp = ptr;
	}
	 else
	 	SaveExitAddress(ptr);

	// DEBUG("SP Actual: 0X%x",old->pcb->sp)

	roundRobin();


	process *new = GetCurrentProcess();

	priorityCounter = new->pcb->priority;

	if (new == NULL)
		return ptr;
	// DEBUG("SP Nuevo: 0X%x", new->pcb->sp)

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
