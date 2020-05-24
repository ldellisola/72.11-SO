// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "include/Syscalls.h"

extern void _exit();
extern void __ForceTimerTick__();
extern void sleep_process();
extern void get_pid(int * ret);



int getpid(){
	int ret;
	get_pid(&ret);
	return ret;
}

void exit_process(){
	_exit();
	
	__ForceTimerTick__();
}

void BlockAndSwitchProcess(int * pid){
	block_process(pid);
	__ForceTimerTick__();
}

void SleepUntilUserInput(){
	sleep_process();
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