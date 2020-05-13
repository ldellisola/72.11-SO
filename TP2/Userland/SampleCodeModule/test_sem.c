/*
#include "../Include/Curses.h"
#include "../Include/Syscalls.h"
#include "include/Exec.h"
#include "include/Process.h"


uint64_t my_create_process_sem(char * name,void (* func)(int, char **)){
  return exec(name,1,func,-1,-1,0,NULL);
}

uint64_t my_sem_open(char *sem_id, uint64_t initialValue){
  return 0;
}

uint64_t my_sem_wait(char *sem_id){
  return 0;
}

uint64_t my_sem_post(char *sem_id){
  return 0;
}

uint64_t my_sem_close(char *sem_id){
  return 0;
}

#define N 100000000
#define SEM_ID "sem"
#define TOTAL_PAIR_PROCESSES 2

uint64_t global;  //shared memory

void slowInc(uint64_t *p, uint64_t inc){
  uint64_t aux = *p;
  aux += inc;
  *p = aux;
}

void my_process_inc(){
  uint64_t i;

  if (!my_sem_open(SEM_ID, 1)){
    printf("ERROR OPENING SEM\n");
    return;
  }
  
  for (i = 0; i < N; i++){
    my_sem_wait(SEM_ID);
    slowInc(&global, 1);
    my_sem_post(SEM_ID);
  }

  my_sem_close(SEM_ID);
  
  printf("Final value: %d\n", global);
}

void my_process_dec(){
  uint64_t i;

  if (!my_sem_open(SEM_ID, 1)){
    printf("ERROR OPENING SEM\n");
    return;
  }
  
  for (i = 0; i < N; i++){
    my_sem_wait(SEM_ID);
    slowInc(&global, -1);
    my_sem_post(SEM_ID);
  }

  my_sem_close(SEM_ID);

  printf("Final value: %d\n", global);
}

void test_sync(){
  uint64_t i;

  global = 0;

  printf("CREATING PROCESSES...\n");

  for(i = 0; i < TOTAL_PAIR_PROCESSES; i++){
    my_create_process_sem("my_process_inc",my_process_inc);
    my_create_process_sem("my_process_dec",my_process_dec);
  }
  
  // The last one should print 0
}

void my_process_inc_no_sem(){
  uint64_t i;
  for (i = 0; i < N; i++){
    slowInc(&global, 1);
  }

  printf("Final value: %d\n", global);
}

void my_process_dec_no_sem(){
  uint64_t i;
  for (i = 0; i < N; i++){
    slowInc(&global, -1);
  }

  printf("Final value: %d\n", global);
}

void test_no_sync(){
  uint64_t i;

  global = 0;

  printf("CREATING PROCESSES...\n");

  for(i = 0; i < TOTAL_PAIR_PROCESSES; i++){
    my_create_process_sem("my_process_inc_no_sem",my_process_inc_no_sem);
    my_create_process_sem("my_process_dec_no_sem",my_process_dec_no_sem);
  }

  // The last one should not print 0
}

int test_sem(){
  test_sync();
  test_no_sync();
  
}*/