#ifndef KEYBOARD_API_H
#define KEYBOARD_API_H

#include <Sem.h>



void readKey();
int returnKey();

void initializeKeyboard();
SemData_t * getKeyboardSem();


#endif
