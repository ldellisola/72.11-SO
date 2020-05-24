#ifndef PIPE_H
#define PIPE_H

#include "Sem.h"

/***************************************************************/
/*                         Constantes                          */
/***************************************************************/

#define BUFFER 1024
#define MAX_NAM 100
#define STDIN 0
#define STDOUT 1

/***************************************************************/
/*                  Estructuras y Enums                        */
/***************************************************************/

typedef enum
{
  READ,
  WRITE
} actions;

typedef struct t_pipe
{
  int state;
  char name[MAX_NAM];
  int fd[2];
  char buffer[BUFFER];
  char *read;
  char *write;
  int processesBlocked;
  char sem[15];
} t_pipe;

/***************************************************************/
/*                      Declaraciones                          */
/***************************************************************/

//  It creates a new pipe of it doesn't exists. If it exists, it will return it.
void openPipe(char *name, actions action, int *fd);

//  It reads input either from STDINT or from a pipe.
//  In both cases, this function will block the process until new input arrives
void read(char *buffer, int bufferSize, int *ans);

//  It reads from a pipe. If there's no itnput it will block the process.
//  In case of error, -1 will be returnes, if everything went ok, it will return 
//  the amount of characters read.
void readPipe(int fd, char *buffer, int bufferSize, int *ans);

//  It writes input either to STDOUT or from a pipe.
void write(char *buffer, int *ans);

//  It writes to a pipe. It will block the process until it writes the info
//  In case of error, -1 will be returnes, if everything went ok, it will return 
//  the amount of characters read.void writePipe(int fd, char *buffer, int *ans);
void writePipe(int fd,char * buffer,int * ans);

//  It prints in terminal information about the pipes
void pipes();

//  It closes a pipe's end, wheter is the read or write end of the pipe. If the pipe
//  is still in use, it won't close it, we only close the pipe when no one is done with it
void closePipes(int *fd);

void readNoBlock(char * buffer,int bufferSize,int * lenght);
#endif