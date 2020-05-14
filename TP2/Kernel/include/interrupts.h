 /*
 *   interrupts.h
 *
 *  Created on: Apr 18, 2010
 *      Author: anizzomc
 */

#ifndef INTERRUPS_H_
#define INTERRUPS_H_

#include "idtLoader.h"

void _irq00Handler(void);
void _irq01Handler(void);
void _irq02Handler(void);
void _irq03Handler(void);
void _irq04Handler(void);
void _irq05Handler(void);
void _irq80Handler(void* ptr, int interval);
void _irq81Handler(void * ptr, void * ptr2, void * ptr3);
void _irq82Handler(void * ptr, void * timeid, void * saveTime);
void _irq83Handler(void * firstParam,void * secondParam,void * thirdParam,void * fourthParam,void * fifthParam);


void _irq85Handler(void * ptr, void * timeid);
void _irq86Handler(void * increment, void* buffer);
void _irq87Handler(void * address , int * retValue);
void _irq88Handler(void * address , int * retValue);
void _irq89Handler(void * firstParam,void * secondParam,void * thirdParam);
void _irq90Handler(int * firstParam);
void _irq91Handler(int * firstParam,int secondParam);
void _irq92Handler(int * firstParam);
void _irq93Handler(int * firstParam);
void _irq94Handler(int * firstParam);
void _irq95Handler();
void _irq96Handler(int fd,void*first,void**second);
void _irq97Handler();
void _irq98Handler(void *);

void _exception0Handler(void);
void _exception6Handler(void);
void _exception4Handler();
void _exception8Handler();
void _exception0xCHandler();
void _exception0xDHandler();
void _exception0xEHandler();


void _cli(void);

void _sti(void);

void _hlt(void);

void picMasterMask(uint8_t mask);

void picSlaveMask(uint8_t mask);

//Termina la ejecución de la cpu.
void haltcpu(void);

#endif /* INTERRUPS_H_ */
