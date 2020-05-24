// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "include/Exec.h"
#include "include/Syscalls.h"
#include "include/Curses.h"

/***************************************************************/
/*                 Functiones Publicas                         */
/***************************************************************/

int exec(char * name, int status, int (* func)(),int read,int write,int argc,char ** argv){

    int bridge=status;
    function_t  function;
    function.args=argv;
    function.function=func;
    function.argc=argc;
    function.read=read;
    function.write=write;

    process_manager(0,(void *)name,(void *)&bridge,(void *)&function);
    return bridge;
        
}