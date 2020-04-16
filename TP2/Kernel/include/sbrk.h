#ifndef SBRK_H
#define SBRK_H
#include <stdint.h>

void sbrk_handler(int increment, void ** buffer);
int brk_handler( void * addr);

#endif
