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




void _exception0Handler(void);
void _exception6Handler(void);


void _cli(void);

void _sti(void);

void _hlt(void);

void picMasterMask(uint8_t mask);

void picSlaveMask(uint8_t mask);

//Termina la ejecución de la cpu.
void haltcpu(void);

#endif /* INTERRUPS_H_ */
