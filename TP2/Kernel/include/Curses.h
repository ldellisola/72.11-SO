#ifndef CURSES_API_H
#define CURSES_API_H

#include <stdarg.h>


//  Macro to make the debbuging process faster
#define DEBUG(mod,val) printfColor(0xFF3300,0,"KERNEL - DEBUG - "#mod,val); putCharColor('\n',0xFF3300,0);

#define ERROR(mod,val) printfColor(0xFF0000,0xFFFFFF,"KERNEL - ERROR - "#mod,val); putCharColor('\n',0xFF0000,0xFFFFFF);

#define WARNING(mod,val) printfColor(0xEEC200,0xDDDDDD,"KERNEL - WARNING - "#mod,val); putCharColor('\n',0xEEC200,0xDDDDDD);

//  Prints a formated string on the console
void printf(const char * format,...);

//  Prints a formated string with a given color on the console
void printfColor(int fontColor, int backgroundColor,const char * format,...);

//  Prints a character on the console
void putChar(char ch);

//  Prints a character with a given color on the console
void putCharColor(char ch, int fontColor, int backgroundColor);





#endif


