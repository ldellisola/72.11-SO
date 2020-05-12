#include "include/SpinLock.h"

extern void __SpinLock__();
extern void __SpinUnlock__();

void SpinLock(){
    __SpinLock__();
}

void SpinUnlock(){
    __SpinUnlock__();
}