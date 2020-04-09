#ifndef SPEAKER_DRIVER
#define SPEAKER_DRIVER

#include <stdint.h>

/*
    SpeakerDriver support based on https://wiki.osdev.org/PC_Speaker. 

*/


void playSound(uint32_t nFrequence);

void stopSound();


#endif