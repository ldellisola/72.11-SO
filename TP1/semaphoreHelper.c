// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "semaphoreHelper.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

SemData_t semaphoreSetUp(const char *name)
{
    SemData_t data;
    strncpy(data.name, name, 1024);

    for (int i = 0; data.name[i] != 0; i++)
        if (data.name[i] == '\n')
            data.name[i] = 0;

    char path[1024];

    sprintf(path, "/dev/shm%s", data.name);

    sem_unlink(name);
    data.id = sem_open(data.name, O_CREAT | O_RDWR, 0777, 0);

    if (data.id == SEM_FAILED)
    {
        perror("Creating Semaphore");

        if (access(path, F_OK) != -1)
            printf("File: %s Doesnt exist\n", path);
        else
            printf("File: %s Exist!\n", path);

        exit(-1);
    }

    return data;
}

SemData_t semaphoreOpen(const char *name)
{
    SemData_t data;
    strncpy(data.name, name, 1024);

    for (int i = 0; data.name[i] != 0; i++)
        if (data.name[i] == '\n')
            data.name[i] = 0;

    char path[1024];

    sprintf(path, "/dev/shm%s", data.name);

    data.id = sem_open(data.name, O_RDWR, 0777, 0);

    if (data.id == SEM_FAILED)
    {
        perror("Creating Semaphore");

        if (access(path, F_OK) != -1)
            printf("File: %s Doesnt exist\n", path);
        else
            printf("File: %s Exist!\n", path);

        exit(-1);
    }

    return data;
}

void semaphoreDestroy(SemData_t *data)
{
    if (sem_close(data->id) != 0)
    {
        perror("Closing Semaphore");
        exit(-1);
    }

    if (sem_unlink(data->name) < 0)
    {
        perror("Unlinking Semaphore");
        exit(-1);
    }
}

void semaphoreClose(SemData_t *data)
{
    if (sem_close(data->id) != 0)
    {
        perror("Closing Semaphore");
        exit(-1);
    }
}

void semaphoreWait(SemData_t *data)
{
    sem_wait(data->id);
}

void semaphorePost(SemData_t *data)
{
    sem_post(data->id);
}