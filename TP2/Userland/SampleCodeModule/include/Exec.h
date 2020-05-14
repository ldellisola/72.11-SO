#ifndef EXEC_H
#define EXEC_H

typedef  int (* process_Function_t)(int, char **);

typedef struct function_t{
    process_Function_t function;
    int argc;
    char ** args;
}function_t;

int exec(char * name, int status, int (* func)(int, char **),int argc,char ** argv);
#endif