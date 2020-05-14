#ifndef PROCESS_H
#define PROCESS_H

void loop();

void cat(int argc, char ** argv);

void wc(int argc, char ** argv);

void test_mm();

void test_processes();

//void testSem(int argc, char ** argv);

void test_prio();

void testPipes();

void test_sync();

void test_no_sync();

#endif