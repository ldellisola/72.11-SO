#ifndef EXEC_H
#define EXEC_H
#include <stdarg.h>
typedef struct function_t{
    int (*function)();
    int argc;
    char ** args;
}function_t;

int exec(char * name, int status, int ** func,int args,...);

#endif