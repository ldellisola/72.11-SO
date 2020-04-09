#include "SpeakerDriver.h"
#include <stdint.h>
#include <timer.h>

/**********************************************************************
*                           funciones ASM                             *
***********************************************************************/

extern void WritePITConfiguration(uint8_t val);
extern void WritePIT2Data(uint8_t val);
extern uint8_t ReadSpeakerData();
extern void WriteSpeakerData(uint8_t val);

/**********************************************************************
*                           Declaraciones                             *
***********************************************************************/


/**********************************************************************
*                      funciones Publicas                             *
***********************************************************************/


void playSound(uint32_t nFrequence) {
 	uint32_t Div;
 	uint8_t tmp;
 
 	Div = 1193180 / nFrequence;
 	WritePITConfiguration(0xb6);
 	WritePIT2Data((uint8_t) (Div) );
 	WritePIT2Data((uint8_t) (Div >> 8));
 
 	tmp = ReadSpeakerData();
  	if (tmp != (tmp | 3)) {
 		WriteSpeakerData( tmp | 3);
 	}
 }
 
 void stopSound() {
 	uint8_t tmp = ReadSpeakerData() & 0xFC;
 	WriteSpeakerData(tmp);
 }
 
