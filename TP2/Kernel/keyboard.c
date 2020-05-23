#include <keyboard.h>
#include <stdlib.h>

/***************************************************************************\
 *                              Estructuras                                 *
 \***************************************************************************/

typedef struct
{
    int (*func)();
    int key
} KeyboardShortCut_t;

/***************************************************************************\
 *                              Dependencias ASM                            *
 \***************************************************************************/

extern int __ReadKey__();

/***************************************************************************\
 *                          Defines y Enums                                  *
 \***************************************************************************/

#define F(x) (CapsLock - x)
#define BUFFER_SIZE 256
#define EOF -20
#define MAX_SHORTCUTS 30

enum Commands
{
    Escape = -1,
    Control = -2,
    LShift = -3,
    Rshift = -4,
    PrintScreen = -5,
    Alt = -6,
    CapsLock = -7,
    NumLock = -8,
    ScrollLock = -9,
    Home = -10,
    ArrowUp = -11,
    ArrowDown = -12,
    ArrowLeft = -13,
    ArrowRight = -14,
    End = -15,
    PageUp = -16,
    Delete = -17
};

/***************************************************************************\
 *                          Variables estaticas                              *
 \***************************************************************************/

static char keyboardBuffer[BUFFER_SIZE];
static unsigned int bufferIndex = 0;
static unsigned int returnIndex = 0;

static bool Mayusc = false;
static bool Shift = false;
static bool control = false;

KeyboardShortCut_t shortcuts[MAX_SHORTCUTS];

static const int KeyMap[] = {
    //1
    Escape, 27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', 8,
    //16
    9, 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', Control,
    //32
    'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', LShift, '\\',
    //46
    'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', Rshift, PrintScreen, CapsLock,
    //59
    ' ', CapsLock, F(1), F(2), F(3), F(4), F(5), F(6), F(7), F(8), F(9), F(10),
    //71
    NumLock, ScrollLock, Home, ArrowUp, PageUp, 0, 0, 0, 0, 0, 0, 0, 0, 0, Delete,
    //86
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, F(11), F(12), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

static const int ShiftKeyMap[] = {
    //0
    0, 0, 0, 0, 0, 0, 0, 0, 8, 0, '\n', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    //32
    ' ', '!', '\"', '#', '&', '%', '\"', '(', ')', '*', '+', '<', '_', '>', '?', ')',
    '!', '@', '#', '$', '%', '^', '&', '*', '(', ':', ':', '<', '+', '>', '?',
    '@', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
    'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '{', '|', '}',
    '^', '_', '~', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L',
    'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '{',
    '|', '}', '~', 0};

static const int ControlKeyMap[] = {
    //0
    0, 0, 0, 0, 0, 0, 0, 0, 8, 0, '\n', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    //32
    ' ', '!', '\"', '#', '&', '%', '\"', '(', ')', '*', '+', '<', '_', '>', '?', ')',
    '!', '@', '#', '$', '%', '^', '&', '*', '(', ':', ':', '<', '+', '>', '?',
    '@', 'a', 'b', 'c', EOF, 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
    'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '{', '|', '}',
    '^', '_', '~', 'A', 'B', 'C', EOF, 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L',
    'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '{',
    '\\', '}', '~', 0};

/***************************************************************************\
  *                  Declaracion de Funciones Privadas                      *
 \***************************************************************************/

void handleBreaks(int input);
int handleASCII(int PressedKey);
void handleCommands(int PressedKey);
int processKeyboardInput(int input);
bool tryToRunShortcuts(int key);

/***************************************************************************\
  *                Implementacion de Funciones Publicas                      *
 \***************************************************************************/

void initializeKeyboard()
{
    for (int i = 0; i < MAX_SHORTCUTS; i++)
    {
        shortcuts[i].func = NULL;
        shortcuts[i].key = -1;
    }
}

void SetKeyboardShortcut(int (*func)(), int key)
{

    int i = -1;
    while (shortcuts[++i].func != NULL)
        ;

    shortcuts[i].func = func;
    shortcuts[i].key = key;
}

void readKey()
{
    if (bufferIndex + 1 == returnIndex)
        returnIndex++;

    int temp = processKeyboardInput(__ReadKey__());

    if (temp != -1)
        keyboardBuffer[bufferIndex++ % BUFFER_SIZE] = temp;
}

bool isThereInputInSTDIN()
{
    return returnIndex != bufferIndex;
}

int returnKey()
{
    if (returnIndex == bufferIndex)
        return -1;

    return keyboardBuffer[returnIndex++ % BUFFER_SIZE];
}

/***************************************************************************\
  *               Implementacion de Funciones Privadas                      *
 \***************************************************************************/

void handleBreaks(int input)
{
    input = input - 0x80;

    if (input > 0)
    {
        int ReleasedKey = KeyMap[input];

        switch (ReleasedKey)
        {
        case LShift:
        case Rshift:
            Shift = false;
            break;
        case Control:
            control = false;
            break;
        }
    }
}

int handleASCII(int PressedKey)
{

    if ('a' <= PressedKey && PressedKey <= 'z')
    {
        if (Mayusc)
            PressedKey += 'A' - 'a';
        if (Shift)
            PressedKey = ShiftKeyMap[PressedKey];
        if (control)
        {

            if (tryToRunShortcuts(PressedKey))
                PressedKey = -1;
            else
                PressedKey = ControlKeyMap[PressedKey];
        }
        return PressedKey;
    }
    else if ((' ' <= PressedKey && PressedKey <= '?') || ('Z' < PressedKey && PressedKey < 'a') || (PressedKey == '\n') || (PressedKey == 8))
    {
        if (Shift)
            return ShiftKeyMap[PressedKey];
        else
            return PressedKey;
    }

    return -1;
}

void handleCommands(int PressedKey)
{
    switch (PressedKey)
    {
    case CapsLock:
        Mayusc = !Mayusc;
        break;
    case LShift:
    case Rshift:
        Shift = true;
        break;
    case Control:
        control = true;
        break;

    default:
        break;
    }
    if (PressedKey == CapsLock)
    {
        if (Mayusc)
        {
            Mayusc = false;
        }
        else
        {
            Mayusc = true;
        }
    }
    else if (PressedKey == LShift || PressedKey == Rshift)
    {
        Shift = true;
    }
}

int processKeyboardInput(int input)
{

    handleBreaks(input);

    if (input <= 0 || input > 86)
        return -1;

    int PressedKey = KeyMap[input];

    if (PressedKey > 0)
    {
        int asciiValue = handleASCII(PressedKey);

        if (asciiValue > 0 || asciiValue == EOF)
            return asciiValue;
    }

    handleCommands(PressedKey);

    return -1;
}

bool tryToRunShortcuts(int key)
{

    int i = -1;

    while (shortcuts[++i].func != NULL)
    {
        if (shortcuts[i].key == key)
        {
            shortcuts[i].func();
            return true;
        }
    }

    return false;
}