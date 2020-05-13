#include "include/Process.h"
#include "../Include/Pipes.h"
#include "../Include/Syscalls.h"
#include "include/Exec.h"
#include "../Include/String.h"

int stop=1;

void ReadingEnd(){
  int fdr=openPipe("hola",READ);
  int x=0;
  stop=0;
  char buffer[1024];
  readPipe(fdr,buffer,1024);
  printf("lei %s\n",buffer);
  exit_process();
}



void testPipes(){
  int fdw=openPipe("hola",WRITE);
  exec("reading",1,ReadingEnd,-1,-1,0,NULL);
  int x=0;
  char aux[100];
  while(stop==1){}
  writePipe(fdw,"Holis como andas?");
  //pipe();
}

