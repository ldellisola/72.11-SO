#ifndef STRINGH
#define STRINGH

#include <stdarg.h>
#include <stdint.h>

/***************************************************************/
/*                 Functiones Publicas                         */
/***************************************************************/

//  Counts the lenght of a string
int strlen(char * str);

//  Separates the string in smaller string using tokens
char * strtok(char **str,  char delim);

//  Converts int to string
void IntToString(char * buff, int buffSize, int64_t num);

//  converts string to hexa num
int stringToHexa(char *buff);

//  converts hex num to string
void HexToString(char * buff, int buffSize, int64_t num);

//  adds string to begining of another string
void preppend(char * src, char * dest, unsigned size);

//  adds strign to the end of another string
void append(char * src, char * dest, unsigned size);

//  formats string to another buffer
void snprintf(char * string, int size, char * format, va_list args);

//  formats string into another buffer
void formatString(char * string, int size,char * format,...);

//  returns 1 if the strings are the same, 0 else
int strcmp(char * s1,char * s2);

//  converts string to int
int stringToInt(char * buff);

//  same 
void HexToStringSPECIAL(char * buffer, int buffSize, uint64_t num);




#endif