#ifndef SPEAKER_H
#define SPEAKER_H
#include <stdint.h>

/***************************************************************/
/*                 Functiones Publicas                         */
/***************************************************************/

//  stops playing sound
void stopSound();

//  starts playing sound at a given frecuency
void playSound(uint64_t frecuency);


#endif