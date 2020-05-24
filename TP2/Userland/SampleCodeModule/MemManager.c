// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "include/MemManager.h"
#include "include/Syscalls.h"
#include "include/Curses.h"

void *malloc(size_t size)
{
	void * prt;
	mem_manager(0,(void *)size,(void*)&prt,NULL);
	return prt;
}

void free(void *block)
{
	mem_manager(1,(void*)&block,NULL,NULL);
}
