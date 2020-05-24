#ifndef CURSES
#define CURSES

#include <stdarg.h>
#include <stdint.h>

/***************************************************************/
/*                 Functiones Publicas                         */
/***************************************************************/

//  Clears the console
int clearConsole(int argc, char **argv);

//  Removes the last character printed
void RemoveLastCharFromDisplay();

//  prints formated text to the console
void printf(const char * format, ...);

//  printf formated error to the console
void printfError(const char * format,...);

//  prints char to the console
void putChar(char ch);

//  reads key from the input FD
int readKey();

//  prits formated text in a given color
void printfColorAt(int fontColor, int backgroundColor,int x,int y,const char * format,...);

//  sets a string with a given char
void * memset(void * destiation, int32_t c, uint64_t length);

//  reads from keyboard without blocking the process
int readKeyNoBlock();


#define DEBUG(mod,val) printfError("USER - DEBUG - "#mod,val); putChar('\n');


#endif


