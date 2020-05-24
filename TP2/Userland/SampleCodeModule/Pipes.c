#include "include/Pipes.h"
#include "include/Syscalls.h"
#include "include/MemManager.h"

int openPipe(char * name,actions action){
  int fd;
  pipes(0,(void*)name,(void *)action,(void *)&fd);
  return fd;
}

int readPipe(int pipe,char * buffer,int bufferSize){
  
  return read(pipe,buffer,bufferSize);
}

int writePipe(int pipe,char * buffer){
  
  return write(pipe,buffer);
}


int closePipes(int pipe){
  int ans=pipe;
  pipes(1,(void *)&ans,NULL,NULL);
  return ans;
}

int pipe(int argc, char **argv){
  pipes(2,NULL,NULL,NULL);
  return 0;
}
