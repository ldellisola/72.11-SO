#ifndef DEVICEINFO_H
#define DEVICEINFO_H

#include <stdint.h>



void readMem(uint64_t position, char * buff, int size);
void getBpp(unsigned int * bpp);
void setSize(unsigned int  bpp);
void getCharHeight(unsigned int * c);
void getCharWidth(unsigned int * c);
void getScreenWidth(unsigned int * s);
void getScreenHeight(unsigned int * s);
#endif