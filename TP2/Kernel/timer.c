#include "../include/timer.h"
#include <naiveConsole.h>
#include <stdlib.h>

static unsigned long ticks = 0;



void timer_handler() {
		ticks++;	
}

int ticks_elapsed() {
	return ticks;
}

int seconds_elapsed() {
	return ticks / 18;
}





