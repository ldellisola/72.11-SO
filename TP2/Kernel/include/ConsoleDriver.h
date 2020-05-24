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

//  Initializes the console
void initializeConsoleDriver(int charHeight_,int charWidth_, int screenHeight_, int screenWidth_);

//  Prints line in default color on the screen
void printLine(char * string);

//  Prints line in the color of each char
void printLineColor(ColorChar * string);

//  Prints a single character in screen
void printChar(char ch);

//  Print a single character in screen with a given color
void printCharColor(ColorChar ch);

//  Removes all characters from the screen
void clearConsole();

// Removes the last added character from the screen
void removeLastChar();



#endif