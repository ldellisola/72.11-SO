#ifndef EXEC_H
#define EXEC_H

typedef  int (* process_Function_t)(int, char **);


typedef struct function_t{
    process_Function_t function;
    int argc;
    char ** args;
    int read;
    int write;
}function_t;


int exec(char * name, int status, int (* func)(int, char **),int read,int write,int argc,char ** argv);
#endif