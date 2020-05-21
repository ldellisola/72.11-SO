#ifndef PROCESS_H
#define PROCESS_H
#include <stdbool.h>
#include <stdint.h>


int loop(int argc, char ** argv);

int filter(int argc,char ** argv);

bool isVowel(char c);

int phylo(int argc,char ** argv);

uint32_t my_kill(uint32_t pid);

uint32_t my_block(uint32_t pid);

uint32_t my_unblock(uint32_t pid);

int cat(int argc, char ** argv);

int wc(int argc, char ** argv);

int test_mm(int argc,char ** argv);

int test_processes(int argc,char ** argv);

//void testSem(int argc, char ** argv);

int test_prio(int argc,char ** argv);

int testPipes(int argc,char ** argv);

int test_sync(int argc,char ** argv);

int test_no_sync(int argc,char ** argv);

int test_semaforito(int argc,char ** argv);

int test_semaforito2(int argc,char ** argv);

#endif