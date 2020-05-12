#include "include/Pipe.h"
#include "include/pcb.h"
#include "include/String.h"
#include "include/Scheduler.h"
#include "include/Curses.h"
#include <keyboard.h>


/* ----------------------------------------*/
  #define MAX 10
  #define FIRST 20
  t_pipe files[MAX];
  int cantidad=0;
  int minFd=FIRST; 
/* ----------------------------------------*/
  int lookPipe(char * name);
  int pipeCheck(int fd,actions action);
  void readStdin();
  void writeStdout();
  //int getFree();
/* ----------------------------------------*/

void openPipe(char * name,actions action,int*fd){
  int i=lookPipe(name);
  //si no se puede tener más de dos procesos esto cambia
  if(i==-1){
    if(cantidad==MAX){
      *fd=-1;
      return;}  
    i=freePipe();
    cantidad++;
    files[i].fd[READ]=minFd++;
    files[i].fd[WRITE]=minFd++;
    CopyString(name,files[i].name,strlen(name));
    files[i].read=files[i].buffer;
    files[i].write=files[i].buffer;
    files[i].state=1;
  }
  *fd=files[i].fd[action];
}

void read(char * buffer,int bufferSize){
  process * current= GetCurrentProcess();
  int fd=current->pcb->fd[READ];
  if(fd==STDIN){
    readStdin(buffer,bufferSize);
    return;
  }
  readPipe(fd,buffer,bufferSize);
  
}
void readPipe(int fd,char * buffer,int bufferSize){
  int i=pipeCheck(fd,READ);
  int j=0;
  if(i==-1){
    //*fd=i;
    return;
  }
  char * read=files[i].read;
  char * write=files[i].write;
  //cuando el write dio la vuelta
  if(read==write){
    //voy a asumir que si son iguales hay dos posibilidades, que el write no haya escrito 
    //o que haya escrito y dado toda la vuelta hasta justo quedar en el read
    if(*read==0)
      return;
    read++;  
  }
  if(read>write){
      while(read<(files[i].buffer+BUFFER) && j<bufferSize-1){
      buffer[j++]=*read;
      *read=0;
      read++;
    }
    //checkeo si me quede sin espacio o llegue al final del buffer
    if(j==bufferSize-1){
      buffer[j]=0;
      files[i].read=read;
      return;
    }
    read=files[i].buffer;
    DEBUG("CAMBIE\n",0);
  }
 
  while(read<write && j<bufferSize-1){
      buffer[j++]=*read;
      *read=0;
      read++;
    }
  buffer[j]=0;
  files[i].read=read;
  return;
}

void write(char * buffer){
  process * current= GetCurrentProcess();
  int fd=current->pcb->fd[WRITE];
  if(fd==STDOUT){
    writeStdout(buffer);
    return;
  }
  writePipe(fd,buffer);
}

void writePipe(int fd,char * buffer){
  int i=pipeCheck(fd,WRITE);
  int j=0;
  if(i==-1){
    //*fd=i;
    return;
  }
  char * write=files[i].write;
  while(buffer[j]!=0){
    if(write<(files[i].buffer+BUFFER)){
      *write=buffer[j++];
      write++;
    }
    else
      write=files[i].buffer;
  }  
    *write=0;
    files[i].write=write;
    return;
  }


void pipes(){
  printf("\nPipes\n");
  for(int i=0; i<MAX;i++){
    if(files[i].state==1){
      printf("\nNombre: %s\n",files[i].name);
      printf("Estado: ");
      for(int j=0;j<BUFFER;j++){
        char c;
        if((c=files[i].buffer[j])!=0)
          putChar(c);
        else
          putChar('-');
      }
      putChar('\n');
      printf("FALTAN PROCESOS BLOQUEADOS\n");
    }
  }
}

void closePipes(int * fd){
  int i;
  if ((i=pipeCheck(*fd,*fd%2==0?READ:WRITE)) == -1) {
        *fd=-1;
        return;
    }
    cantidad--;
    CopyString(0, files[i].name, 1);
    files[i].state=0;
}

int lookPipe(char * name){
  for(int i = 0; i < MAX ; i++){
    if(strcmp(name,files[i].name)){
        return i;
    }
  }
return -1;  
}

int freePipe(){
  for(int i=0;i<MAX;i++){
    if(files[i].state==0)
      return i;
  }
  return -1;
}

int pipeCheck(int fd,actions action){
  if(fd<FIRST || fd>=(FIRST+2*MAX))
    return -1;
  if(action==READ){
    if(fd%2!=0)
      return -1;
     return fd-FIRST; 
  }
  if(fd%2==0)
    return-1;
  return fd-1-FIRST;  
}

void readStdin(char * buffer,int bufferSize){
			int i = 0;		
			int temp;
			do{
				temp = returnKey();
				
				if( temp != -1 ){
					buffer[i++]=temp;
				}

			}while( temp!= -1 && i <bufferSize-1 );
			buffer[i] = 0;

}

void writeStdout(char * buffer){
  if(buffer[1] == 0)
    putChar(*buffer);
  else
    printf(buffer);
}