#ifndef PIPE_H
#define PIPE_H

#include "Sem.h"

#define BUFFER 1024
#define MAX_NAME 100
#define STDIN 0
#define STDOUT 1

typedef enum{READ,WRITE} actions;
typedef struct t_pipe
{
  int state;
  char name[MAX_NAME];
  int fd[2];
  char buffer[BUFFER];
  SemData_t * sem;
  char * read;
  char * write;
  int processesBlocked;
}t_pipe;


void openPipe(char * name,actions action,int * fd);

void read(char * buffer,int bufferSize);

//devuelve si pudo leer por el bufferSize, -1 error sino cantidad de caracteres
void readPipe(int fd,char * buffer,int * bufferSize);

void write(char * buffer,int * ans);
//devuelve si pudo escribir por la respuesta, -1 error sino cantidad de caracteres
void writePipe(int fd,char * buffer,int * ans);

void pipes();

void closePipes(int * fd);
#endif