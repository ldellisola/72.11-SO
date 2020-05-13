#ifndef PIPES_H
#define PIPES_H
#include "../Include/Sem.h"
typedef enum{READ,WRITE} actions;


int openPipe(char * name,actions action);

int readPipe(int pipe,char * buffer,int bufferSize);

int writePipe(int pipe,char * buffer);

void pipe();

int closePipes(int pipe);

#endif