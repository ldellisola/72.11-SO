#include <stdarg.h>
#include "../Include/Syscalls.h"
#include "include/Terminal.h"
#include "../Include/Curses.h"
#include "include/Commands.h"
#include "../Include/String.h"
#include <stdlib.h>
#include <stdbool.h>
#include "include/Exec.h"
#include "include/Process.h"
#include "../Include/Sem.h"

/***************************************************************/
/*                        Constantes                           */
/***************************************************************/

#define MAXBUFFER (600)

/***************************************************************/
/*                         Estructuras                         */
/***************************************************************/

typedef struct
{
    bool isBackground;
    int argc;
    char *argv[20];
    char *process;
    unsigned long hash;

} ParsedCommand_t;

typedef void (*processFunction)(int, char **);

typedef struct
{
    processFunction function;
    const char *name;
    bool isProcess;
    unsigned long hash;
    const char *description;

} Command_t;

/***************************************************************/
/*                         Variables                           */
/***************************************************************/

static char TerminalType[MAXBUFFER];
static unsigned int TypeIndex = 0;

Command_t commands[] = {
    {.function = loop, .name = "loop", .isProcess = true, .description = "It shows the current date and time."},
    {.function = test_mm, .name = "testMem", .isProcess = true, .description = "Process that tests our memory manager implementation."},
    {.function = test_processes, .name = "testProcess", .isProcess = true, .description = "Process that tests our process implementation."},

    {.function = help, .name = "help", .isProcess = false, .description = "It enumerates all the commands available on this shell\nIf there's an argument, it will tell you the funcition of that command."},
    {.function = time, .name = "time", .isProcess = false, .description = "It shows the current date and time."},
    {.function = infoReg, .name = "infoReg", .isProcess = false, .description = "It prints on screen the actual value of the registers."},
    {.function = invalidOpcode, .name = "invalidOpcode", .isProcess = false, .description = "It is a test to validate the INVALID OPCODE exception."},
    {.function = clearConsole, .name = "clear", .isProcess = false, .description = "It clears the screen."},
    {.function = quotient, .name = "quotient", .isProcess = false, .description = "It calculates the quotient of the division of [Argument_1] by [Argument_2]. This can be used to test the DIVISION BY ZERO exception."},
    {.function = malloc_test, .name = "malloctest", .isProcess = false, .description = "Our very own memory manager test."},
    {.function = printMemoryState, .name = "mem", .isProcess = false, .description = "It prints on screen the first 32 bytes of memory from any given memory position."},
    {.function = killProcess, .name = "kill", .isProcess = false, .description = "It kills any process by its PID. It won't kill the terminal."},
    {.function = niceProcess, .name = "nice", .isProcess = false, .description = "It changes the priority of a process, with 1 beign more priority and 3 less priority."},
    {.function = blockProcess, .name = "block", .isProcess = false, .description = "It blocks a process by its PID. It won't block the terminal."},
    {.function = ProcessState, .name = "ps", .isProcess = false, .description = "It prints in the terminal information about all the processes that are currently running."},
    {.function = semInfo, .name = "sem", .isProcess = false, .description = "It prints in the terminal information about all the current semaphores that currently exists."},
    {.function = testSem, .name = "testSem", .isProcess = false, .description = "Our very own function that tests our semaphores implementation."},

    {.function = NULL, .name = NULL, .isProcess = false, .description = NULL}};

/***************************************************************/
/*                         Declaraciones                       */
/***************************************************************/

void clearArray(char *arr, int size);
void overwriteArray(char *src, char *dest);
void printTerminal();
int interpretCommand();
void overwriteArrayUpTo(char *src, char *dest, char c);
void InitializeTerminal();
unsigned long sdbm(char *str);

/***************************************************************/
/*                      Funciones Publicas                     */
/***************************************************************/

int runTerminal()
{
    InitializeTerminal();
    clearArray(TerminalType, MAXBUFFER);
    TypeIndex = 0;
    printf(">>>>  ");
    int exit = 0;
    do
    {
        int key = readKey();
        if (key > 0)
        {
            if (key == 8)
            {
                if (TypeIndex > 0)
                {
                    TerminalType[--TypeIndex] = 0;
                    RemoveLastCharFromDisplay();
                }
            }
            else
            {
                TerminalType[TypeIndex++] = key;
                printTerminal();

                if (key == '\n')
                {
                    exit = interpretCommand();
                    clearArray(TerminalType, MAXBUFFER);
                    TypeIndex = 0;
                    printf(">>>>  ");
                }
            }
        }
    } while (!exit);

    return exit;
}

/***************************************************************/
/*                      Funciones Privadas                     */
/***************************************************************/

unsigned long sdbm(char *str)
{
    unsigned long hash = 0;
    int c;
    while (c = *str++)
        hash = c + (hash << 6) + (hash << 16) - hash;

    return hash;
}

void InitializeTerminal()
{

    for (int i = 0; commands[i].function != NULL; i++)
    {
        commands[i].hash = sdbm(commands[i].name);
    }
}

void help(int argc, char **argv)
{
    if (argc == 0)
    {
        int i = 0;

        while (commands[i].name != NULL)
        {
            printf("%s    |%s\n", commands[i].isProcess ? "Proceso" : "Comando", commands[i].name);
            i++;
        }
    }
    else
    {
        unsigned long hash = sdbm(argv[0]);
        for (int i = 0; commands[i].name != NULL; i++)
        {
            if (hash == commands[i].hash)
            {
                printf("%s      | %s\n", commands[i].isProcess ? "Proceso" : "Comando", commands[i].name);
                printf("           %s\n", commands[i].description);
                return;
            }
        }
    }
}

void ProcessCommandString(char *command, ParsedCommand_t *cmd)
{
    char *currentPart;
    int index = 0;
    cmd->isBackground = false;
    cmd->process = NULL;

    if (command[strlen(command) - 1] == '\n')
        command[strlen(command) - 1] = 0;

    while ((currentPart = strtok(&command, ' ')) != NULL && index < 20)
    {
        if (cmd->process == NULL)
        {
            cmd->process = currentPart;
            continue;
        }

        if (currentPart[0] == '&')
        {
            cmd->isBackground = true;
            break;
        }
        cmd->argv[index++] = currentPart;
    }

    cmd->argc = index;
    cmd->hash = sdbm(cmd->process);
}

int interpretCommand()
{
    ParsedCommand_t parsedCommand;
    ProcessCommandString(TerminalType, &parsedCommand);

    int i;
    for (i = 0; commands[i].name != NULL; i++)
    {
        if (commands[i].hash == parsedCommand.hash)
        {

            if (commands[i].isProcess)
            {
                exec(commands[i].name, parsedCommand.isBackground, commands[i].function, parsedCommand.argc, parsedCommand.argv);
            }
            else
            {
                commands[i].function(parsedCommand.argc, parsedCommand.argv);
            }
            break;
        }
    }

    if (commands[i].name == NULL)
    {
        printfError("%s: command not found with arguments: \n", parsedCommand.process);
        for (int i = 0; i < parsedCommand.argc; i++)
            printfError(" %s ", parsedCommand.argv[i]);
    }

    return 0;
}

void printTerminal()
{

    if (TerminalType[0])
        putChar(TerminalType[TypeIndex - 1]);
}

void clearArray(char *arr, int size)
{

    for (int i = 0; i < size; i++)
        arr[i] = 0;
}

void overwriteArray(char *src, char *dest)
{
    overwriteArrayUpTo(src, dest, 0);
}

void overwriteArrayUpTo(char *src, char *dest, char c)
{
    clearArray(dest, MAXBUFFER);
    int i;
    for (i = 0; src[i] != 0 && src[i] != '\n' && i < MAXBUFFER && src[i] != c; i++)
        dest[i] = src[i];
    if (i != MAXBUFFER)
    {
        dest[i] = 0;
    }
}
