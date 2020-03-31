#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <sys/select.h>

#define MAX 1024

void runMinisat(char *file);

// Parametros
//      Programa
//      FILES...
int main(int argc, char **argv)
{

    char **initialFiles;

    setvbuf(stdout, NULL, _IONBF, 0);

    // if(argc <= 1){
    //     fprintf(stderr,"Invalid Arguments.\n");
    //     return -1;
    // }

    initialFiles = argv;

    // Me quedo solo con los archivos en este arreglo de strings.
    for (int i = 1; i < argc; i++)
        initialFiles[i - 1] = initialFiles[i];

    initialFiles[argc - 1] = NULL;

    srand(time(NULL));

    int id = getpid();

    fprintf(stderr, "SLAVE: %d -- REcieved Files: %s - %s\n", id, initialFiles[0], initialFiles[1]);

    bool exitCondition = false;
    int initialIndex = 0;
    char file[MAX];
    do
    {
        if (initialFiles[initialIndex] != NULL)
        {
            strncpy(file, initialFiles[initialIndex++], MAX);
            fprintf(stderr, "SLAVE: %d -- Loading Initial File: %s\n", id, file);
        }
        else
        {
            //fprintf(stderr, "SLAVE: %d -- Waiting for file from master\n", id);
            // Leo del pipe
            int final = read(STDIN_FILENO, file, MAX);

            if (final == -1)
            {
                perror("Reading file from master");
                exit(-1);
            }

            exitCondition = (final == 0);

            file[final] = 0;
            //fprintf(stderr, "SLAVE: %d -- Loading recieved File: %s\n", id, file);
        }

        if (!exitCondition)
            runMinisat(file);


            

    } while (!exitCondition);

    return 0;
}

void runMinisat(char *file)
{
    char inst[MAX];
    snprintf(inst, MAX, "minisat %s |grep -o -e 'Number of.*[0-9]\\+' -e 'CPU time.*' -e '.*SATISFIABLE' | grep -o -e '[0-9|.]*' -o -e '.*SATISFIABLE' | xargs", file);
    FILE * fp = popen(inst, "r");
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

    int v=-1, c=-1;
    float t=-1.0;
    char s[15];
    s[0]=0;
    sscanf(ans, "%d %d %f %s", &v, &c, &t, s);
    char info[MAX * 2];
    n = snprintf(info, MAX, "PID: %d. File: %s. Number of Variables: %d. Number of Clauses: %d CPU TIME: %f %s \n", getpid(), file, v, c, t, s);
    // printf(info);
    //if(s[0]!=0)
    write(STDOUT_FILENO, info, n);
    int status = fclose(fp);

    if (status == -1)
    {
        perror("Fclose error:");
        exit(-1);
    }
}
