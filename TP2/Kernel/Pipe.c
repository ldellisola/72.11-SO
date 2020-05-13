#include "include/Pipe.h"
#include "include/SpinLock.h"
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
  extern void __ForceTimerTick__();

  //int getFree();
/* ----------------------------------------*/

void openPipe(char * name,actions action,int*fd){
  int i=lookPipe(name);
  //si no se puede tener más de dos procesos esto cambia
  if(i==-1){
    if(cantidad==MAX){
      *fd=-1;
      return;
    }  
    
    i=freePipe();
    cantidad++;
    files[i].sem=semopen(name);
    files[i].fd[READ]=minFd++;
    files[i].fd[WRITE]=minFd++;
    CopyString(name,files[i].name,strlen(name));
    files[i].read=files[i].buffer;
    files[i].write=files[i].buffer;
    int buffer=files[i].buffer;
    int read=files[i].read;
    int write=files[i].write;
    //me aseguro que lo primero sea 0 por read y write
    *files[i].buffer=0;
    files[i].state=1;
  }
  *fd=files[i].fd[action];
}

void read(char * buffer,int bufferSize){
  int pid=getpid();
  int fd=getFd(pid,READ);
  
  if(fd==STDIN){
    readStdin(buffer,bufferSize);
    return;
  }
  readPipe(fd,buffer,bufferSize,false);
  
}

void readPipe(int fd,char * buffer,int * bufferSize,bool pipe){
 
 //checkeo que exista el pipe
  int i=pipeCheck(fd,READ);
  
  //sino -1
  if(i==-1){
    if(pipe)
    *bufferSize=i;
    return;
  }
  
  int j=0;
  int count=0;
  bool blocking=false;
  char * read=files[i].read;
  char * write=files[i].write;
  //aseguro que soy yo solo
  
  SpinLock();
  
  //cuando el write dio la vuelta
  if(read==write){
    //voy a asumir que si son iguales hay dos posibilidades, que el write no haya escrito 
    //o que haya escrito y dado toda la vuelta hasta justo quedar en el read
    
    //como write se para en el proximo que tiene que escribir, tengo que preguntar si el anterior
    //esta en 0 o no (Seria lo ultimo que escribio)
    if((*read==0)){
       int pid=getpid();

      //lo guardo en los procesos bloqueados     
      files[i].processesBlocked=pid;
      //bloqueo al proceso
      blockProcess(&pid);
      blocking=true;
    }
    else{
      read++;
    }
  }
  //libero el lock porque ya me fije si habia alguien más y como en kernel no interrupme
  //si estoy aca nadie más está acá

  //genero la interrupcion
  if(blocking){
      SpinUnlock();
    __ForceTimerTick__();
    write=files[i].write;
}
  if(read>write){
      while(read<(files[i].buffer+BUFFER) && j<bufferSize-1){
      buffer[j++]=*read;
      *read=0;
      read++;
      count++;
    }
    //checkeo si me quede sin espacio o llegue al final del buffer
    if(j==bufferSize-1){
      buffer[j]=0;
      files[i].read=read;
      if(pipe)
      *bufferSize=count;

      //desbloqueo al otro
      if(files[i].processesBlocked!=0){
        block(&files[i].processesBlocked);
        files[i].processesBlocked=0;
        return;  
      }
      SpinUnlock();
      return;
    }
    read=files[i].buffer;

    DEBUG("CAMBIE\n",0);
  }
 
  while(read<write && j<bufferSize-1){
      buffer[j++]=*read;
      *read=0;
      read++;
      count++;
  }
  buffer[j]=0;
  files[i].read=read;
  if(pipe)
  *bufferSize=count;

  //desbloqueo al otro
  if(files[i].processesBlocked!=0){
    block(&files[i].processesBlocked);
    files[i].processesBlocked=0;  
    return;
  }
  SpinUnlock();
  return;
}

void write(char * buffer,int * ans){
  int pid=getpid();
  int fd=getFd(pid,WRITE);
  if(fd==STDOUT){
    writeStdout(buffer);
    return;
  }
  writePipe(fd,buffer,ans,false);
}

void writePipe(int fd,char * buffer,int * ans,bool pipe){
  int i=pipeCheck(fd,WRITE);
  int j=0;
  if(i==-1){
    if(pipe)
    *ans=i;
    return;
  }

  char * write=files[i].write;
  char * read=files[i].read;
  int count=0;
  bool flag=false;
  while(buffer[j]!=0){
    flag=false;
      SpinLock();
      if(read==write && *write!=0){
        int pid=getpid();
        files[i].processesBlocked=pid;
        block(&pid);
        flag=true;
      }

      SpinUnlock();

      if(flag){
        __ForceTimerTick__();
        read=files[i].read;
      }
      if(write<(files[i].buffer+BUFFER)){
        *write=buffer[j++];
        write++;
        count++;
      }
      else
        write=files[i].buffer;
}  
    files[i].write=write;
    if(files[i].processesBlocked!=0){
      block(&files[i].processesBlocked);
      files[i].processesBlocked=0;
    }
    if(pipe)
      *ans=count;
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
      printf("Proceso Bloqueado:");
      if(files[i].processesBlocked!=0)
      printf(" %d",files[i].processesBlocked);
      printf("\n");
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