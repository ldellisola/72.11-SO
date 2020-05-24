// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

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
