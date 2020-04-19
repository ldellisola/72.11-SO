#ifndef EXEC_H
#define EXEC_H
#include <stdarg.h>
typedef struct function{
    int (*function)();
    int argc;
    char ** args;
}function;

int exec(char * name, int state, int ** func,int args,...);

#endif