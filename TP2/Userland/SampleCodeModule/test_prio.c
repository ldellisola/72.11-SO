#include "../Include/Curses.h"
#include "../Include/Syscalls.h"
#include "include/Exec.h"
#include "include/Process.h"


#define MINOR_WAIT 1000000                               // TODO: To prevent a process from flooding the screen
#define WAIT      10000000                              // TODO: Long enough to see theese processes beeing run at least twice

int endless_loop_prio(int argc,char ** argv);

uint64_t my_getpid(){
  return getpid();
}

uint64_t my_create_process_prio(char * name){
  return exec(name,1,endless_loop_prio,-1,-1,0,0);
}

uint64_t my_nice(uint64_t pid, uint64_t newPrio){
  uint64_t aux=pid;
  
  process_manager(4,(void *)&aux,(void *)newPrio,0);
  return aux;
}

/*uint64_t my_kill(uint64_t pid){
  uint64_t aux=pid;
  kill_process(&aux);
  return aux;
}

uint64_t my_block(uint64_t pid){
  uint64_t aux=pid;
  block_process(&aux);
  return aux;
}

uint64_t my_unblock(uint64_t pid){
  uint64_t aux=pid;
  block_process(&aux);
  return aux;
}
*/
void bussy_wait(uint64_t n){
  uint64_t i;
  for (i = 0; i < n; i++);
}

int endless_loop_prio(int argc,char ** argv){
  uint64_t pid = my_getpid();

  while(1){
    printf("%d ",pid);
    bussy_wait(MINOR_WAIT);
  }
  return 0;
}

#define TOTAL_PROCESSES 3

int test_prio(int argc,char ** argv){
  uint64_t pids[TOTAL_PROCESSES];
  uint64_t i;

  for(i = 0; i < TOTAL_PROCESSES; i++)
    pids[i] = my_create_process_prio("endless_loop");

  bussy_wait(WAIT);
  printf("\nCHANGING PRIORITIES...\n");

  for(i = 0; i < TOTAL_PROCESSES; i++){
    switch (i % 3){
      case 0:
        my_nice(pids[i], 0); //lowest priority 
        break;
      case 1:
        my_nice(pids[i], 1); //medium priority
        break;
      case 2:
        my_nice(pids[i], 2); //highest priority
        break;
    }
  }

  bussy_wait(WAIT);
  printf("\nBLOCKING...\n");

  for(i = 0; i < TOTAL_PROCESSES; i++)
    my_block(pids[i]);

  printf("CHANGING PRIORITIES WHILE BLOCKED...\n");
  for(i = 0; i < TOTAL_PROCESSES; i++){
    switch (i % 3){
      case 0:
        my_nice(pids[i], 1); //medium priority 
        break;
      case 1:
        my_nice(pids[i], 1); //medium priority
        break;
      case 2:
        my_nice(pids[i], 1); //medium priority
        break;
    }
  }

  printf("UNBLOCKING...\n");

  for(i = 0; i < TOTAL_PROCESSES; i++)
    my_unblock(pids[i]);

  bussy_wait(WAIT);
  printf("\nKILLING...\n");

  for(i = 0; i < TOTAL_PROCESSES; i++)
    my_kill(pids[i]);
exit_process();    
return 0;
}
