#ifndef PIPES_H
#define PIPES_H
#include "Sem.h"

/***************************************************************/
/*                          Enums                              */
/***************************************************************/

typedef enum{READ,WRITE} actions;

/***************************************************************/
/*                 Functiones Publicas                         */
/***************************************************************/

//  Opens pipe
int openPipe(char * name,actions action);

//  Reads from pipe
int readPipe(int pipe,char * buffer,int bufferSize);

//  Writes to pipe
int writePipe(int pipe,char * buffer);

//  prints pipes details
int pipe(int argc, char **argv);

//  Closes pipe
int closePipes(int pipe);

#endif