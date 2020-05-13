#ifndef EXEC_H
#define EXEC_H

typedef struct function_t{
    int (* function)(int, char **);
    int argc;
    char ** args;
    int fd[2];
}function_t;
typedef enum{READ,WRITE} actions;


int exec(char * name, int status, int (* func)(int, char **),int read,int write,int argc,char ** argv);
#endif