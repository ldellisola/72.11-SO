#include <stdarg.h>
#include <stdbool.h>
#include "../Include/String.h"
#include <stdarg.h>

int strlen(char * str){
    int i = 0;
    while(str[i]!=0)
        i++;
    return i;
}


void IntToString(char * buffer, int buffSize, uint64_t num){

	char *p = buffer;
	char *p1, *p2;
	uint32_t digits = 0;

	//Calculate characters for each digit
	do
	{
		uint32_t remainder = num % 10;
		*p++ = (remainder < 10) ? remainder + '0' : remainder + 'A' - 10;
		digits++;
	}
	while (num /= 10);

	// Terminate string in buffer.
	*p = 0;

	//Reverse string in buffer.
	p1 = buffer;
	p2 = p - 1;
	while (p1 < p2)
	{
		char tmp = *p1;
		*p1 = *p2;
		*p2 = tmp;
		p1++;
		p2--;
	}
}

int stringToInt(char * buff){
	int aux=0;
	for(int i=0;*(buff+i)!=0;i++){
		aux=aux*10+(*(buff+i)-'0');
	}
	return aux;
}

int power(int x,int y){
	if(y == 0)
		return 1;
	else
		return x * power(x,y-1);
}



void HexToStringSPECIAL(char * buffer, int buffSize, uint64_t num){

	for(int i = 0 ; i < buffSize ; i++)
		buffer[i] = '0';

	buffer[buffSize-1]= 0;

	    uint64_t temp = num;
	int i = 0;

	while(temp!= 0 && i < buffSize){

		uint64_t stVal = temp;
		uint64_t numToSave = temp - 16*(stVal/16);

		if(numToSave <10 ){
			buffer[i++] = '0' + numToSave;
		}
		else{
			buffer[i++] = 'A' + numToSave-10;
		}
		
		temp = temp/16;
	}
    i = buffSize-2;

	for(int a = 0 ; a <= (buffSize-2)/2 ; a++){
		char temp = buffer[a];
		buffer[a] = buffer[i-a];
		buffer[i-a] = temp;
	}
}


// Taken from the base project
void HexToString(char * buffer, int buffSize, uint64_t num){

	char *p = buffer;
	char *p1, *p2;
	uint32_t digits = 0;

	//Calculate characters for each digit
	do
	{
		uint32_t remainder = num % 16;
		*p++ = (remainder < 10) ? remainder + '0' : remainder + 'A' - 10;
		digits++;
	}
	while (num /= 16);

	// Terminate string in buffer.
	*p = 0;

	p1 = buffer;
	p2 = p - 1;
	while (p1 < p2)
	{
		char tmp = *p1;
		*p1 = *p2;
		*p2 = tmp;
		p1++;
		p2--;
	}

	return digits;
	
}

void append(char * src, char * dest, unsigned size){
	int base = strlen(dest);

	for(int i = 0 ; i < size && src[i] != 0 ; i++){
		dest[base + i] = src[i];
	}

}

void preppend(char * src, char * dest, unsigned size){
	int srcLenght = strlen(src);
	int destLenght = strlen(dest);

	for(int i = destLenght ; i >=0  ; i--){
		dest[i + srcLenght ] = dest[i];
	}

	for(int i = 0 ; i < srcLenght-1 ; i++)
		dest[i] = src[i];

}

int strcmp(char * s1,char * s2){
    int i;
    for(i=0;*(s1+i)!=0 && *(s2+i)!=0 && *(s1+i)==*(s2+i);i++);

    if(*(s1+i)==0 && *(s2+i)==0)
     return 1;
    return 0; 
}

void formatString(char * string, int size,char format,...){
	va_list args;
	va_start(args,format);
	snprintf(string,size,format,args);
	va_end(args);
}

void snprintf(char * string, int size, char * format, va_list args){
	int i=0,k=0;
	char c;
	while(((c=(*(format+i)))!=0)&& k<size){
		if(c=='%'){
			i++;
			handleFormat(*(format+i),&k,string,size,args);
		}
		else{
			*(string+k)=*(format+i);	
			k++;
		}
		i++;
	}
	*(string+k)=0;
}

void handleFormat(char type,int * k,char * string,int size,va_list args){
	switch(type){
		case 'c':{
			char aux=va_arg(args,int);
			*(string+(*k))=aux;
			break;
		}
		case 'd':
		case 'i':
		{	int aux1=va_arg(args,int);
			IntToString(string+(*k),size-1-(*k),aux1);
			break;}
		case 's':
			{char * aux2 =va_arg(args,char *);
			append(aux2,string+(*k),size-1-(*k));	
			break;}	
		case 'x':
		case 'X':
		{	
			HexToString(string+(*k),size-1-(*k),va_arg(args,int));
			break;
		}
		default: 
			{	*(string+(*k))='%';
				*(string+(*k+1))=type;}
	}
			*k=strlen(string);	

}
int stringToHexa(char *buff){
	int aux=0;
	for(int i=0;*(buff+i)!=0;i++){
		int c;
		switch(*(buff+i)){
			case('A'):{
				c=10;
				break;
			}
			case('B'):{
				c=11;
				break;
			}
			case('C'):{
				c=12;
				break;
			}
			case('D'):{
				c=13;
				break;
			}
			case('E'):{
				c=14;
				break;
			}
			case('F'):{
				c=15;
				break;
			}
			case('0'):
			case('1'):
			case('2'):
			case('3'):
			case('4'):
			case('5'):
			case('6'):
			case('7'):
			case('8'):
			case('9'):{
				c=(*(buff+i)-'0');
				break;}
			default:
				return -1;	
		}
		aux=aux*16+c;
	}
	return aux;
}