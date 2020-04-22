#include "../Include/Syscalls.h"
int getpid(){
	int ret;
	get_pid(&ret);
	return ret;
}