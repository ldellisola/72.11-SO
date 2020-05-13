#ifndef EXEC_H
#define EXEC_H

typedef struct function_t{
    int (* function)(int, char **);
    int argc;
    char ** args;
    int read;
    int write;
}function_t;


int exec(char * name, int status, int (* func)(int, char **),int read,int write,int argc,char ** argv);
#endif