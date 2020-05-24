#include "include/deviceInfo.h"
#include "include/Syscalls.h"

/***************************************************************/
/*                         Estructuras                          */
/***************************************************************/

typedef struct{
    unsigned int bbp;
    unsigned int charHeight;
    unsigned int charWidht;
    unsigned int screenHeight;
    unsigned int screenWidth;
}DeviceInfo;

/***************************************************************/
/*                   Funciones Publicas                        */
/***************************************************************/

void readMem(uint64_t position, char * buff, uint64_t size){

    _read(FD_MEMORY,(void *)position,buff,(void *)size,0);

}

void getBpp(unsigned int * bpp){

    DeviceInfo temp;

    _read(FD_DEVICE_INFO,(void *)&temp,0,0,0);

    *bpp = temp.bbp;

}

void setSize(uint64_t bpp){
    _write(FD_DEVICE_INFO,(void *)bpp,0,0,0);
}

void getCharHeight(unsigned int * c){
     DeviceInfo temp;

    _read(FD_DEVICE_INFO,(void *)&temp,0,0,0);

    *c = temp.charHeight;
}

void getCharWidth(unsigned int * c){
     DeviceInfo temp;

    _read(FD_DEVICE_INFO,(void *)&temp,0,0,0);

    *c = temp.charWidht;
}

void getScreenWidth(unsigned int * s){

         DeviceInfo temp;

    _read(FD_DEVICE_INFO,(void *)&temp,0,0,0);

    *s = temp.screenWidth;
    
}

void getScreenHeight(unsigned int * s){

         DeviceInfo temp;

    _read(FD_DEVICE_INFO,(void *)&temp,0,0,0);

    *s = temp.screenHeight;

}