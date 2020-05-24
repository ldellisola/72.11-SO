
#include "include/MemManager.h"
#include "include/Syscalls.h"
#include "include/Curses.h"

void *malloc(size_t size)
{
	void * prt;
	_malloc(size,&prt);
	return prt;
}

void free(void *block)
{
	_free(&block);
}
