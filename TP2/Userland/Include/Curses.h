#ifndef CURSES
#define CURSES

#include <stdarg.h>



void clearConsole();

void RemoveLastCharFromDisplay();

void printf(const char * format, ...);

void printfError(const char * format,...);

void putChar(char ch);

int readKey();

void printfColorAt(int fontColor, int backgroundColor,int x,int y,const char * format,...);

#endif


