// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "include/Speaker.h"
#include "include/Syscalls.h"

/***************************************************************/
/*                 Functiones Publicas                         */
/***************************************************************/

void playSound(uint64_t frecuency){

    _write(FD_SPEAKER,(void *)frecuency,0,0,0);

}


void stopSound(){
    delete(FD_SPEAKER,0,NULL,NULL,NULL);
}