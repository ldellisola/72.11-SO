#include "../include/timer.h"
#include <Curses.h>
#include <stdlib.h>

#include <Scheduler.h>

static unsigned long ticks = 0;



void * timer_handler(void * ptr) {
	ticks++;

	process * old = GetCurrentProcess();
	int quantumtime = 1;
	

	if(ticks % (18 * 5) != 0)
		return ptr;
	DEBUG("Intentando de cambiar de proceso. Viene SP 0x%x",ptr)



	if(old != NULL){

		old->pcb->sp = ptr;
	}

	// DEBUG("SP Actual: 0X%x",old->pcb->sp)

	

	roundRobin();

	process * new = GetCurrentProcess();
	
	if(new == NULL)
		return ptr;
	DEBUG("SP Nuevo: 0X%x",new->pcb->sp)


	return new->pcb->sp;

}

int ticks_elapsed() {
	return ticks;
}

int seconds_elapsed() {
	return ticks / 18;
}





