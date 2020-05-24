// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "include/Sem.h"
#include "include/Syscalls.h"
#include "include/Curses.h"
#include <stdbool.h>

/***************************************************************/
/*                        Variables                            */
/***************************************************************/

int var = 0;

/***************************************************************/
/*                 Functiones Publicas                         */
/***************************************************************/

uint64_t semopen(char *name,uint64_t initValue)
{
    uint64_t aux=initValue;
    sem(0, (void *)name, &aux);
    return aux;
}

uint64_t semwait(char * semp)
{
    uint64_t aux;
    sem(1, (void *)semp, &aux);
    return aux;
    
}

uint64_t sempost(char * semp)
{
    uint64_t aux;
    sem(2, (void *)semp, &aux);
    return aux;
}

uint64_t semclose(char *semp)
{
    uint64_t aux;
    sem(3, (void *)semp, &aux);
    return aux;
}

int semInfo(int argc, char ** argv)
{
    sem(4, NULL, NULL);
    return 0;
}