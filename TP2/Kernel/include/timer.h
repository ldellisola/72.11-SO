#ifndef _TIMER_API_H_
#define _TIMER_API_H_

/***************************************************************/
/*                 Functiones Publicas                         */
/***************************************************************/

//  It manages the context swithc when the timer interrupt happens
void * timer_handler(void * ptr);

//  It calculates how many ticks happpened since boot
int ticks_elapsed();

//  It calculates hoy many seconds passed since boot
int seconds_elapsed();

#endif
