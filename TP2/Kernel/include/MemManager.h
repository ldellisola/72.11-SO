#ifndef MEM_MANAGER_H
#define MEM_MANAGER_H

#include <stdlib.h>

/***************************************************************/
/*                        CONSTANTES                           */
/***************************************************************/

// It defines if we are compiling the Budddy memory manager or our implementation
//#define ENABLE_BUDDY

/***************************************************************/
/*                      Declaraciones                          */
/***************************************************************/

//  It allocates a given ammount of memory that must be freed
void *malloc(size_t size);

//  It frees memory allocated by malloc
void free(void *ptr);

#endif