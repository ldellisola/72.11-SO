#ifndef KEYBOARD_API_H
#define KEYBOARD_API_H

#include <stdbool.h>


//  tries to read a key from the keyboard (hardware)
void readKey();

// Reads a key from the keyboard Buffer. This key may be an ASCII character or a 
// custom character such as EOF (-20). If no new key wa detected, it will return -1.
// Unmapped keys will return 0.
int returnKey();

// Binds a function to a key. When CTRL + key is pressed, it will execute said function.
// Some keys are already mapped to functions, such as CTRL + D will cause EOF.
void SetKeyboardShortcut(void (* func ) (), int key);

// checks if there was new input on STDIN.
bool isThereInputInSTDIN();

// Initializes the keyboard driver.
void initializeKeyboard();


#endif
