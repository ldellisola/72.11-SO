#include "../Include/Curses.h"
#include "../Include/Syscalls.h"
#include "include/Exec.h"
#include "include/Process.h"
#include "../Include/Sem.h"


uint64_t my_create_process_sem(char * name,int (* func)(int, char **)){
  return exec(name,1,func,-1,-1,0,NULL);
}

uint64_t my_sem_open(char *sem_id, int initialValue){
  return semopen(sem_id,initialValue);
}

uint64_t my_sem_wait(char *sem_id){
  return semwait(sem_id);
}

uint64_t my_sem_post(char *sem_id){
  return sempost(sem_id);
}

uint64_t my_sem_close(char *sem_id){
  return semclose(sem_id);
}

void printfNeg(int64_t g) {
  int64_t neg = g*(-1);
  printf("Final value: -%d\n", neg);
}

#define N 100000000
#define SEM_ID "sem"
#define TOTAL_PAIR_PROCESSES 2

int64_t global;  //shared memory

void slowInc(int64_t *p, int64_t inc){
  int64_t aux = *p;
  aux += inc;
  *p = aux;
}

int my_process_inc(int argc,char ** argv){
  uint64_t i;

  if (my_sem_open(SEM_ID, 1)){
    printf("ERROR OPENING SEM\n");
    exit_process();
    return 0;
  }
  
  for (i = 0; i < N; i++){
    my_sem_wait(SEM_ID);
    slowInc(&global, 1);
    my_sem_post(SEM_ID);
  }

  my_sem_close(SEM_ID);
  
  if (global < 0) {
    printfNeg(global);
  }
  printf("Final value: %d\n", global);

  exit_process();
  return 0;
}

int my_process_dec(int argc,char ** argv){
  uint64_t i;

  if (my_sem_open(SEM_ID, 1)){
    printf("ERROR OPENING SEM\n");
    exit_process();
    return 0;
  }
  
  for (i = 0; i < N; i++){
    my_sem_wait(SEM_ID);
    slowInc(&global, -1);
    my_sem_post(SEM_ID);
  }

  my_sem_close(SEM_ID);

  if (global < 0) {
    printfNeg(global);
  }
  printf("Final value: %d\n", global);
  exit_process();
  return 0;
}

int test_sync(int argc,char ** argv){
  uint64_t i;

  global = 0;

  printf("CREATING PROCESSES...\n");

  for(i = 0; i < TOTAL_PAIR_PROCESSES; i++){
    my_create_process_sem("my_process_inc",my_process_inc);
    my_create_process_sem("my_process_dec",my_process_dec);
  }

  exit_process();
  return 0;
  // The last one should print 0
}

int my_process_inc_no_sem(int argc,char ** argv){
  uint64_t i;
  for (i = 0; i < N; i++){
    slowInc(&global, 1);
  }
    if (global < 0) {
    printfNeg(global);
  }
  printf("Final value: %d\n", global);

  exit_process();
  return 0;
}

int my_process_dec_no_sem(int argc,char ** argv){
  uint64_t i;
  for (i = 0; i < N; i++){
    slowInc(&global, -1);
  }

    if (global < 0) {
    printfNeg(global);
  }
  printf("Final value: %d\n", global);

  exit_process();
  return 0;
}

int test_no_sync(int argc,char ** argv){
  uint64_t i;

  global = 0;

  printf("CREATING PROCESSES...\n");

  for(i = 0; i < TOTAL_PAIR_PROCESSES; i++){
    my_create_process_sem("my_process_inc_no_sem",my_process_inc_no_sem);
    my_create_process_sem("my_process_dec_no_sem",my_process_dec_no_sem);
  }

  exit_process();
  return 0;
  // The last one should not print 0
}

/*int main(){
  test_sync();
  test_no_sync();
  
}*/