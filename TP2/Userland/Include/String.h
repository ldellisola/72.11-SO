#ifndef STRINGH
#define STRINGH
#include <stdarg.h>

#include <stdint.h>


int strlen(char * str);

void IntToString(char * buff, int buffSize, uint64_t num);

int stringToHexa(char *buff);

void HexToString(char * buff, int buffSize, uint64_t num);

void preppend(char * src, char * dest, unsigned size);

void append(char * src, char * dest, unsigned size);

void snprintf(char * string, int size, char * format, va_list args);

void handleFormat(char type,int * k,char * string,int size,va_list args);

void formatString(char * string, int size,char format,...);

int strcmp(char * s1,char * s2);

int stringToInt(char * buff);

void HexToStringSPECIAL(char * buffer, int buffSize, uint64_t num);




#endif