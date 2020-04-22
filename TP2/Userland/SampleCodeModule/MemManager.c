
#include "../Include/MemManager.h"
#include "../Include/Syscalls.h"
#include "../Include/Curses.h"

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
