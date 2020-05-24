#ifndef PROCESS_H
#define PROCESS_H
#include <stdbool.h>
#include <stdint.h>

/***************************************************************/
/*                 Functiones Publicas                         */
/***************************************************************/


//  loops
int loop(int argc, char ** argv);

//  filters vowels
int filter(int argc,char ** argv);

//  phylo
int phylo(int argc,char ** argv);


uint32_t my_kill(uint32_t pid);

uint32_t my_block(uint32_t pid);

uint32_t my_unblock(uint32_t pid);

//  CATs
int cat(int argc, char ** argv);

//  counts lines
int wc(int argc, char ** argv);

//  test for memory manager
int test_mm(int argc,char ** argv);

//  test for processes
int test_processes(int argc,char ** argv);

//  test for priorities
int test_prio(int argc,char ** argv);

//  test pipes
int testPipes(int argc,char ** argv);

//  test semapghores
int test_sync(int argc,char ** argv);

//  also test semaphores
int test_no_sync(int argc,char ** argv);

//  Again, more semaphores
int test_semaforito(int argc,char ** argv);

//  Ok, one las timeunctiones Publicas
int test_semaforito2(int argc,char ** argv);

#endif