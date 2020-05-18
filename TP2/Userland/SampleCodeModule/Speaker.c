#include "include/Speaker.h"
#include "../Include/Syscalls.h"


void playSound(int frecuency){

    _write(FD_SPEAKER,frecuency,0,0,0);

}


void stopSound(){
    delete(FD_SPEAKER,NULL,NULL,NULL,NULL);
}