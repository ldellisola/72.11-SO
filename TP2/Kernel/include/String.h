#ifndef STRING_API_H
#define STRING_API_H
#include <stdint.h>

int strlen(char * str);

void IntToString(char * buff, int buffSize, uint64_t num);

void HexToString(char * buff, int buffSize, uint64_t num);

void CopyString(char * src, char * dest, int bufferSize);

int countRepetitionsOf(char * string, char el);

void preppend(char * src, char * dest, unsigned size);

void append(char * src, char * dest, unsigned size);

void formatString(char * string, int size,char * format,...);



#endif