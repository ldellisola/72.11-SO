#include "../include/timer.h"
#include <stdlib.h>

#include <Scheduler.h>

/***************************************************************/
/*                 			Variables                          */
/***************************************************************/

static unsigned long ticks = 0;
static int priorityCounter = 0;
static bool isDummyProcessRunning = false; 

/***************************************************************/
/*                 Functiones Publicas                         */
/***************************************************************/

void *timer_handler(void *ptr)
{
	ticks++;
	process *old = GetCurrentProcess();

	if ((old == NULL || old->pcb->state == READY) && !isDummyProcessRunning)
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

	// Se que esta corriendo el proceso dummy si el next y prev son 
	// null
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
