#include "../include/timer.h"
#include <Curses.h>
#include <stdlib.h>

#include <Scheduler.h>

static unsigned long ticks = 0;



void * timer_handler(void * ptr) {
	ticks++;

	if(ticks %36 != 0)
		return ptr;
	DEBUG("%s","Intentando de cambiar de proceso")


	process * old = GetCurrentProcess();

	if(old == NULL)
		return ptr;

	DEBUG("Proceso Actual: %s",old->pcb->name)

	old->pcb->sp = ptr;

	roundRobin();

	process * new = GetCurrentProcess();
	
	if(new == NULL)
		return ptr;
			DEBUG("Proceso Nuevo: %s",new->pcb->name)


	return new->pcb->sp;

}

int ticks_elapsed() {
	return ticks;
}

int seconds_elapsed() {
	return ticks / 18;
}





