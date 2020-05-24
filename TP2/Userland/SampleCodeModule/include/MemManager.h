#ifndef MEM_MANAGER_H
#define MEM_MANAGER_H
#include <stdlib.h>

/***************************************************************/
/*                 Functiones Publicas                         */
/***************************************************************/

//  Allocates memory dinamically
void *malloc(size_t size);

//  frees allocated memory
void free(void * ptr);


#endif