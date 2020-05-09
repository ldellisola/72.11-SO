#ifndef EXEC_H
#define EXEC_H

typedef struct function_t{
    int (* function)(int, char **);
    int argc;
    char ** args;
}function_t;

int exec(char * name, int status, int (* func)(int, char **),int argc,char ** argv);
#endif