#include "../Include/Syscalls.h"

void * sbrk(int increment) {
	void * resp;
	// printf("DEBUG: por ejecutar SBRK asm\n");
	sbrk_asm(increment, &resp);
	// No entiendo este printf. 
	// printf("Se llamo a sbrk con un size de %d, el puntero retorno %p\n", increment, resp);
	return resp;
}

int brk(void * ptr){
    int ret = -1;

    brk_asm(ptr,&ret);
    return ret;
}

int getpid(){
	int ret;
	get_pid(&ret);
	return ret;
}