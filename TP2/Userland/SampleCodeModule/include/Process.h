#ifndef PROCESS_H
#define PROCESS_H
#include <stdbool.h>

void loop();

void filter();

bool isVowel(char c);

void phylo();

void cat(int argc, char ** argv);

void test_mm();

void test_processes();

//void testSem(int argc, char ** argv);

void test_prio();

void testPipes();

void test_sync();

void test_no_sync();

void test_semaforito();

void test_semaforito2();

#endif