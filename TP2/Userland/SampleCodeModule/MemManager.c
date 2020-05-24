
#include "../Include/MemManager.h"
#include "../Include/Syscalls.h"
#include "../Include/Curses.h"

void *malloc(size_t size)
{
	void * prt;
	mem_manager(0,(void *)size,(void*)&prt,NULL);
	//mem_manager(size,&prt);
	return prt;
}

void free(void *block)
{
	mem_manager(1,(void *)block,NULL,NULL);
	//_free(&block);
}
