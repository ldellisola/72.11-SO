#include "include/SpinLock.h"

/***************************************************************/
/*                     Functiones ASM                          */
/***************************************************************/

extern void __SpinLock__();
extern void __SpinUnlock__();

/***************************************************************/
/*                 Functiones Publicas                         */
/***************************************************************/

void SpinLock(){
    __SpinLock__();
}

void SpinUnlock(){
    __SpinUnlock__();
}