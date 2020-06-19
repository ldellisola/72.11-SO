// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "GDBTest.h"

#include <stdio.h>

void GDB_Me();
int CalculateOtherNumber(int num);

void runGDBTest(){
    
    int magicNumber = 1;

    GDB_Me();

    int otherNumber = CalculateOtherNumber(magicNumber);

    if(magicNumber == otherNumber){
        printf("Igual que el anterior");
    }
}

int CalculateOtherNumber(int num){
    return num + 1;
}

void GDB_Me(){

}