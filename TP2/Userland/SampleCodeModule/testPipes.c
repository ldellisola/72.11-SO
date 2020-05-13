#include "include/Process.h"
#include "../Include/Pipes.h"
#include "../Include/Syscalls.h"
#include "include/Exec.h"
#include "../Include/String.h"


void testPipes(){
  int fdw=openPipe("hola",WRITE);
  int fdr=openPipe("hola",READ);
  int x=0;
  char aux[100];
  char buffer[1024];
  while(x!=1000000000){
    x++;
    IntToString(aux,100,x);
    writePipe(fdw,aux);
    readPipe(fdr,buffer,1024);
    //printf("lei %s\n",buffer);
  }
  //pipe();
}

