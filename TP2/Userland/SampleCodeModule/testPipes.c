#include "include/Process.h"
#include "../Include/Pipes.h"
#include "../Include/Syscalls.h"
#include "include/Exec.h"
#include "../Include/String.h"

int stop=1;

void ReadingEnd(){
  int x=0;
  stop=0;
  char buffer[1024];
  read(FD_STDIN,buffer,1024,0,0);
  printf("lei %s\n",buffer);
  exit_process();
}



void testPipes(){
  int fdw=openPipe("hola",WRITE);
  int fdr=openPipe("hola",READ);
  exec("reading",1,ReadingEnd,fdr,-1,0,NULL);
  int x=0;
  char aux[100];
  while(stop==1){}
  writePipe(fdw,"Holis como andas?");
  //pipe();
}

