#ifndef DEVICEINFO_H
#define DEVICEINFO_H

#include <stdint.h>

/***************************************************************/
/*                 Functiones Publicas                         */
/***************************************************************/

//  Reads bytes from mewmory
void readMem(uint64_t position, char * buff, uint64_t size);

//  gets the Bits Per Pixel value of the screen
void getBpp(unsigned int * bpp);

//  Sets the Bits per Pixel size of the screen
void setSize(uint64_t  bpp);


void getCharHeight(unsigned int * c);
void getCharWidth(unsigned int * c);
void getScreenWidth(unsigned int * s);
void getScreenHeight(unsigned int * s);
#endif