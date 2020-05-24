// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "include/Process.h"
#include "include/Pipes.h"
#include "include/Syscalls.h"
#include "include/Exec.h"
#include "include/String.h"
#include "include/Curses.h"

int stop=1;

int WritingEnd(int argc,char ** argv){
  //char EOF=-20;
  printf("hola, funciona!\n");
  exit_process();
  return 0;
}
int ReadingEnd(int argc,char ** argv){
  char aux[100];
  read(FD_STDIN,aux,100);
  printf("lei: %s",aux);
  exit_process();
  return 0;
}
int testPipes(int argc,char ** argv){
  int fdw=openPipe("hola",WRITE);
  int fdr=openPipe("hola",READ);
  exec("reading",1,ReadingEnd,fdr,-1,0,NULL);
  exec("writing",1,WritingEnd,-1,fdw,0,NULL);
  //pipe();
  return 0;
}

