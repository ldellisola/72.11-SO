#ifndef MEM_MANAGER_H
#define MEM_MANAGER_H
#include <stdlib.h>

void *malloc(size_t size);
void * sbrk(int increment);


#endif