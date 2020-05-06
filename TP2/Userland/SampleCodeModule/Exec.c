#include "include/Exec.h"
#include "../Include/Syscalls.h"
#include "../Include/Curses.h"





/*

    - name: name of the process
    - status: foreground / background?
    - func: Puntero a la funciona ejectuar
    - argc: cantidad de argumentos
    - ... argumentos

*/
int exec(char * name, int status, int (* func)(),int argc,...){
    int bridge=status;
    char * args[argc];

    //DEBUG("%s","Entrando en exec")

    if(argc!=0){

        //DEBUG("Tengo %d argumentos",argc)
        va_list valist;
        int i;
        va_start(valist, argc);
        for (i = 0; i < argc; i++) {
            args[i]=va_arg(valist,char*);
        }
        va_end(valist);
    }


    function_t  function;
    function.args=args;
    function.function=func;
    function.argc=argc;

    //DEBUG("%s","Llamando a syscall")    

    create_process(name,&bridge,&function);
//    ps();
    return bridge;
        
}