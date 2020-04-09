#ifndef CURSES_API_H
#define CURSES_API_H

#include <stdarg.h>




void printf(const char * format,...);

void printfColor(const char * format,int fontColor, int backgroundColor,...);

void putChar(char ch);

void putCharColor(char ch, int fontColor, int backgroundColor);






#endif


