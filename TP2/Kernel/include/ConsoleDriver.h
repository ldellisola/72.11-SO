#ifndef CONSOLE_DRIVER_API_H
#define CONSOLE_DRIVER_API_H

#include <stdarg.h>

typedef struct{
    char ch;
    int fontColor;
    int backgroundColor;
    int x;
    int y;
}ColorChar;

void initializeConsoleDriver(int charHeight_,int charWidth_, int screenHeight_, int screenWidth_);

void printLine(char * string);

void printLineColor(ColorChar * string);

void printLineColorAt(ColorChar * string);

void printChar(char ch);

void printCharColor(ColorChar ch);

void clearConsole();

void removeLastChar();



#endif