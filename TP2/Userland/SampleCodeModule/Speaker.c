#include "include/Speaker.h"
#include "include/Syscalls.h"


void playSound(uint64_t frecuency){

    _write(FD_SPEAKER,(void *)frecuency,0,0,0);

}


void stopSound(){
    delete(FD_SPEAKER,NULL,NULL,NULL,NULL);
}