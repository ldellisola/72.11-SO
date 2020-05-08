#include "../include/timer.h"
#include <Curses.h>
#include <stdlib.h>

#include <Scheduler.h>

static unsigned long ticks = 0;
static int priorityCounter = 0;

void *timer_handler(void *ptr)
{
	ticks++;
	process *old = GetCurrentProcess();

	if (old == NULL || old->pcb->state == READY)
	{
		if (priorityCounter != 0)
		{
			priorityCounter--;
			return ptr;
		}
	}

	if (old != NULL)
	{
		old->pcb->sp = ptr;
	}

	roundRobin();

	process *new = GetCurrentProcess();


	if (new == NULL)
		return ptr;

	priorityCounter = new->pcb->priority; 

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
