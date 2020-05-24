#ifndef STRING_API_H
#define STRING_API_H
#include <stdint.h>
#include <stdarg.h>

/***************************************************************/
/*                 Functiones Publicas                         */
/***************************************************************/

//  Formats a string and stores it in a buffer
void snprintf(char * string, int size, char * format, va_list args);

//  Calculates the lenght of a string
int strlen(char * str);

//  Converts an number into to a string formating it as decimal
void IntToString(char * buff, int buffSize, uint64_t num);

//  Converts a num into a string formatting it as hexadecimal
void HexToString(char * buff, int buffSize, uint64_t num);

//  It Copies a string to a buffer
void CopyString(char * src, char * dest, int bufferSize);

//  It counts the times a char is repeated in a string
int countRepetitionsOf(char * string, char el);

//  It adds a string to the begining of another string
void preppend(char * src, char * dest, unsigned size);

//  It adds a string to the end of another string
void append(char * src, char * dest, unsigned size);

//  It formats a string and stores it in a buffer
void formatString(char * string, int size,char * format,...);

//  It compares two strings and returns 1 if are equal.
int strcmp(char * s1,char * s2);




#endif