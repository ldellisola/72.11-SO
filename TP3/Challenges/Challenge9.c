// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "Challenge9.h"
#include <stdio.h>

void GDB_Me();
int CalculateOtherNumber(int num);

const char * challenge9_GetHint(){
    return "GDB_Me\n";
}

const char * challenge9_GetAnswer(){
    return "Harry Potter is dead";
}

void challenge9_Run(){
    int magicNumber = 1;
    int otherNumber = CalculateOtherNumber(magicNumber);

    GDB_Me();

    if(magicNumber == otherNumber){
        printf("Igual que el anterior\n");
    }
}

int CalculateOtherNumber(int num){
    return num + 1;
}

void GDB_Me(){

}