// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/********************************************************************************
*                               Constantes                                      *
*********************************************************************************/

// Define el tama;o de los strings que vamos a utilizar por defecto.
#define MAX 1024

/********************************************************************************
*                          Funciones Auxiliares                                 *
*********************************************************************************/

// Ejecuta el comando minisat en la consola y luego parsea el texto para formar el string que se va
// a enviar a master
//
//      - file: Path al archivo a procesar
//      - info: String al cual se va a guardar la informacion procesada de minisat
int runMinisat(char *file, char *info);

// Recorre un arreglo de string y elimina el primer argumento del programa
//
//      - argc:         Cantidad de argumentos que se le enviaron al programa
//      - initialFiles: Arreglo de strings que se enviaron como argumentos
void getFirstFiles(int argc, char **initialFiles);

int main(int argc, char **argv)
{
    char **initialFiles;

    setvbuf(stdout, NULL, _IONBF, 0);

    initialFiles = argv;

    // Me quedo solo con los archivos en este arreglo de strings.
    getFirstFiles(argc, initialFiles);

    bool exitCondition = false;
    int initialIndex = 0;
    char file[MAX];

    do
    {
        if (initialFiles[initialIndex] != NULL)
            strncpy(file, initialFiles[initialIndex++], MAX);
        else
        {
            // Leo del pipe
            int final = read(STDIN_FILENO, file, MAX);
            if (final == -1)
            {
                perror("Reading file from master");
                exit(-1);
            }

            exitCondition = (final == 0);
            file[final] = 0;
        }

        if (!exitCondition)
        {

            char info[2 * MAX];
            int n = runMinisat(file, info);
            write(STDOUT_FILENO, info, n);
        }

    } while (!exitCondition);

    return 0;
}

void getFirstFiles(int argc, char **initialFiles)
{
    for (int i = 1; i < argc; i++)
        initialFiles[i - 1] = initialFiles[i];

    initialFiles[argc - 1] = NULL;
}

int runMinisat(char *file, char *info)
{
    char inst[MAX];
    snprintf(inst, MAX, "minisat %s |grep -o -e 'Number of.*[0-9]\\+' -e 'CPU time.*' -e '.*SATISFIABLE' | grep -o -e '[0-9|.]*' -o -e '.*SATISFIABLE' | xargs", file);
    FILE *fp = popen(inst, "r");
    if (fp == NULL)
    {
        perror("Popen error:");
        exit(-1);
    }

    char ans[MAX];
    size_t n = 0;
    ssize_t ansSize;

    ansSize = read(fileno(fp), ans, MAX);
    if (ansSize == -1)
    {
        perror("getLine error:");
        exit(-1);
    }
    ans[ansSize] = 0;

    int v = -1, c = -1;
    float t = -1.0;
    char s[15];
    s[0] = 0;
    sscanf(ans, "%d %d %f %s", &v, &c, &t, s);

    n = snprintf(info, MAX, "PID: %d. File: %s. Number of Variables: %d. Number of Clauses: %d CPU TIME: %f %s \n", getpid(), file, v, c, t, s);
    int status = fclose(fp);

    if (status == -1)
    {
        perror("Fclose error:");
        exit(-1);
    }
    return n;
}
