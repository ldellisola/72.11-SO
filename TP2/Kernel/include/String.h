#ifndef STRING_API_H
#define STRING_API_H
#include <stdint.h>
#include <stdarg.h>


void snprintf(char * string, int size, char * format, va_list args);

int strlen(char * str);

void IntToString(char * buff, int buffSize, uint64_t num);

void HexToString(char * buff, int buffSize, uint64_t num);

void CopyString(char * src, char * dest, int bufferSize);

int countRepetitionsOf(char * string, char el);

void preppend(char * src, char * dest, unsigned size);

void append(char * src, char * dest, unsigned size);

void formatString(char * string, int size,char * format,...);

int strcmp(char * s1,char * s2);




#endif