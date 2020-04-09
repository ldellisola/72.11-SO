#include "./include/gamePrinter.h"
#include "../Include/Syscalls.h"

void printOnScreen(int *pos,int lenght,int height,int color){

				//  printf("FD: %d. PAR1 %d. PAR2 %d. PAR3 %d. PAR4 %d.",5,pos[0],pos[1],lenght,height,color);

   write(5,pos,lenght,height,color);
   

}

