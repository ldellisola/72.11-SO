#ifndef SEM_H
#define SEM_H
//typedef void * sem_t;
#include <stdarg.h>
#include <stdint.h>

/***************************************************************/
/*                 Functiones Publicas                         */
/***************************************************************/

// opens sem
uint64_t semopen(char * name,uint64_t initValue);

// waits sem
uint64_t semwait(char * semp);

// post sem
uint64_t sempost(char * semp);

// closes sem
uint64_t semclose(char * semp);

//  prints infor about sems
int semInfo(int argc, char ** argv);

#endif