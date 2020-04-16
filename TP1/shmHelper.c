// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "shmHelper.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/stat.h>

SHMData_t shmCreate(const char *shmName, size_t shmSize)
{

    SHMData_t data;

    strcpy(data.name, shmName);
    data.size = shmSize;

    for (int i = 0; data.name[i] != 0; i++)
        if (data.name[i] == '\n')
            data.name[i] = 0;

    data.fd = shm_open(data.name, O_CREAT | O_RDWR | O_TRUNC, S_IRUSR | S_IWUSR | S_IROTH | S_IWOTH);

    if (data.fd == -1)
    {
        perror("Creating Shared Memory");
        exit(-1);
    }

    if (ftruncate(data.fd, shmSize) == -1)
    {
        perror("Truncating Shared Memory");
        exit(-1);
    }

    data.map = (char *)mmap(NULL, shmSize, PROT_READ | PROT_WRITE, MAP_SHARED, data.fd, 0);
    if (data.map == (void *)-1)
    {
        perror("Mapping Shared memory to virtual memory");
        exit(-1);
    }

    // Indice para escribir y leer a memoria compartida
    data.readIndex = 0;
    data.writeIndex = 0;

    return data;
}

SHMData_t shmOpen(const char *shmName, size_t shmSize)
{

    SHMData_t data;

    strcpy(data.name, shmName);
    data.size = shmSize;

    for (int i = 0; data.name[i] != 0; i++)
        if (data.name[i] == '\n')
            data.name[i] = 0;

    data.fd = shm_open(data.name, O_RDWR, S_IRUSR | S_IWUSR | S_IROTH | S_IWOTH);

    if (data.fd == -1)
    {
        perror("Creating Shared Memory");
        exit(-1);
    }

    data.map = (char *)mmap(NULL, shmSize, PROT_READ | PROT_WRITE, MAP_SHARED, data.fd, 0);
    if (data.map == (void *)-1)
    {
        perror("Mapping Shared memory to virtual memory");
        exit(-1);
    }

    // Indice para escribir y leer a memoria compartida
    data.readIndex = 0;
    data.writeIndex = 0;

    return data;
}

void shmDestroy(SHMData_t *data)
{

    if (munmap((*data).map, (*data).size) == -1)
    {
        perror("Deleting Mapped Memory");
    }

    if (shm_unlink((*data).name) == -1)
    {
        perror("Unlinking Shared Memory");
    }

    if (close((*data).fd) == -1)
    {
        perror("Closing Shared Memory File Descriptor");
    }
}

void shmClose(SHMData_t *data)
{

    if (munmap((*data).map, (*data).size) == -1)
    {
        perror("Deleting Mapped Memory");
    }

    if (close((*data).fd) == -1)
    {
        perror("Closing Shared Memory File Descriptor");
    }
}

void shmWrite(char *buffer, int bSize, SHMData_t *data)
{
    for (int i = 0; i < bSize; i++)
    {
        data->map[data->writeIndex++] = buffer[i];
    }
    data->map[data->writeIndex] = 0;
}

int shmRead(char *buffer, int bSize, SHMData_t *data)
{
    int i;

    for (i = 0; i < bSize && data->map[data->readIndex] != 0; i++)
    {
        buffer[i] = data->map[data->readIndex++];
    }
    buffer[i] = 0;

    return i;
}
