#ifndef CURSES
#define CURSES

#include <stdarg.h>
#include <stdint.h>



int clearConsole(int argc, char **argv);

void RemoveLastCharFromDisplay();

void printf(const char * format, ...);

void printfError(const char * format,...);

void putChar(char ch);

int readKey();

void printfColorAt(int fontColor, int backgroundColor,int x,int y,const char * format,...);

void * memset(void * destiation, int32_t c, uint64_t length);

#define DEBUG(mod,val) printfError("USER - DEBUG - "#mod,val); putChar('\n');

// #undef DEBUG(mod,val)

// #define DEBUG(mod,val) ;

#endif


