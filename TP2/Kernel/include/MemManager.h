#ifndef MEM_MANAGER_H
#define MEM_MANAGER_H
#include <stdlib.h>

//#define ENABLE_BUDDY

void *malloc(size_t size);
void free(void * ptr);


#endif