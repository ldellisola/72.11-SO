#include <stdio.h>
#include "include/Exec.h"
#include "../Include/Syscalls.h"






int exec(char * name, int status, int ** func,int argc,...){
    int bridge=status;
     char * args[argc];

    if(argc!=0){
    va_list valist;
    int i;
    va_start(valist, argc);
    for (i = 0; i < argc; i++) {
        args[i]=va_arg(valist,char*);
    }
    va_end(valist);}

    function * function;
    function->args=args;
    function->function=func;
    function->argc=argc;
    create_process(name,&bridge,function);
    
    if(bridge==-1)
        return -1;
    return 0;
        
}