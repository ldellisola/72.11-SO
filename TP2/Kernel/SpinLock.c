// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
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