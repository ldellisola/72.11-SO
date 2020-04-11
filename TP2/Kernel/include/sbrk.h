#ifndef SBRK_H
#define SBRK_H
#include <stdint.h>

void sbrk_handler(intptr_t increment, void ** buffer);

#endif
