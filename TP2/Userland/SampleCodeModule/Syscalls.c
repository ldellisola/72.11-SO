// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "include/Syscalls.h"

// extern void _exit();
// extern void sleep_process();
// extern void get_pid(int * ret);
extern void __ForceTimerTick__();



int getpid(){
	int ret;
	process_manager(6,(void *)&ret,0,0);
	return ret;
}

void exit_process(){
	process_manager(7,0,0,0);
	__ForceTimerTick__();
}

void ps(){
	process_manager(5,0,0,0);
}

void BlockAndSwitchProcess(int * pid){
	process_manager(3,(void *)pid,0,0);
	__ForceTimerTick__();
}

void SleepUntilUserInput(){
	process_manager(2,0,0,0);
}

int read(int fd,char * buffer,uint64_t size){
	int ans;
	//SleepUntilUserInput();
	_read(fd, buffer, (void *)size, &ans,NULL);
	return ans;
}
int write(int fd, char * buffer){
	int ans;
	_write( fd, buffer, &ans, NULL, NULL);
	return ans;
}