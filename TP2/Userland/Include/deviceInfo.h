#ifndef DEVICEINFO_H
#define DEVICEINFO_H

#include <stdint.h>



void readMem(uint64_t position, char * buff, uint64_t size);
void getBpp(unsigned int * bpp);
void setSize(uint64_t  bpp);
void getCharHeight(unsigned int * c);
void getCharWidth(unsigned int * c);
void getScreenWidth(unsigned int * s);
void getScreenHeight(unsigned int * s);
#endif