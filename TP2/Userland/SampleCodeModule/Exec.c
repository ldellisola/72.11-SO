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

int exec(char * name, int status, int (* func)(),int read,int write,int argc,char ** argv){
    int bridge=status;


    function_t  function;
    function.args=argv;
    function.function=func;
    function.argc=argc;
    function.fd[READ]=read;
    function.fd[WRITE]=write;
    //DEBUG("%s","Llamando a syscall")    

    create_process(name,&bridge,&function);
    return bridge;
        
}