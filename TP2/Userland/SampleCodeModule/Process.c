#include "../Include/Curses.h"
#include "../Include/Syscalls.h"
#include "../Include/Time.h"
#include "include/Process.h"

#define LOOP_TIME 1 //1seg

void loop(){
int t1=GetSeconds();
int t2=-1;
do{
    if(t2==-1|| t2-t1>=LOOP_TIME)
       printf("Hey, im %d. See you in %d s",getpid(),LOOP_TIME);
}while(1);
    
}