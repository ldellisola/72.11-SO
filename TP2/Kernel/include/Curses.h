#ifndef CURSES_API_H
#define CURSES_API_H

#include <stdarg.h>

#define DEBUG(mod,val) printfColor("KERNEL - DEBUG - "#mod,0xFF3300,0,val); putCharColor('\n',0xFF3300,0);



void printf(const char * format,...);

void printfColor(const char * format,int fontColor, int backgroundColor,...);

void putChar(char ch);

void putCharColor(char ch, int fontColor, int backgroundColor);





#endif


