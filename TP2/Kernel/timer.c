#include "../include/timer.h"
#include <Curses.h>
#include <stdlib.h>

#include <Scheduler.h>

static unsigned long ticks = 0;
static int priorityCounter = 0;
static bool isDummyProcessRunning = false;

void *timer_handler(void *ptr)
{
	ticks++;
	process *old = GetCurrentProcess();

	if (old == NULL || (old->pcb->state == READY && !old->pcb->isWaitingForInput))
	{
		if (priorityCounter != 0)
		{
			priorityCounter--;
			return ptr;
		}
	}

	if (old != NULL)
	{
		if(isDummyProcessRunning){
			GetDummyProcess()->pcb->sp = ptr;
		}
		else{
			old->pcb->sp = ptr;
		}
	}
	

	

	process *new = roundRobin();


	if (new == NULL)
		return ptr;

	if(new->next == new->prev && new->prev == NULL){
		isDummyProcessRunning = true;
	}
	else
		isDummyProcessRunning = false;
		
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
