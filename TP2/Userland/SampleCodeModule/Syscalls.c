#include "../Include/Syscalls.h"
extern void _exit();


int getpid(){
	int ret;
	get_pid(&ret);
	return ret;
}

void exit_process(){
	_exit();
	__asm__("hlt");
}