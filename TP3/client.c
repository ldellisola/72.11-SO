// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

#include "Network.h"

#define MAX_BUFFER (500)

int main(int argc, char *argv[])
{
    // if the arguments are not what the client was expecting
    if (argc != 3 && argc != 2)
    {
        fprintf(stderr, "Client-Usage: %s HOST [optional PORT]\n", argv[0]);
        exit(-1);
    }

    int socket = openSocket();
    int port = selectPort(argc == 3,argv[2]);

    printf("Connecting to server %s:%d on socket %d\n", argv[1], port,socket);

    startClient(argv[1],port,socket);

    bool exitLoop = false;
    while (!exitLoop)
    {
        char st[MAX_BUFFER];
       	int c = read(STDIN_FILENO, st, MAX_BUFFER);

        if(c == -1){
            perror("on Read");
            return -1;
        }   
        else if (c == 0){
            printf("Server is closed. Shutting client down.\n");
            exitLoop = true;
        }

        if (write(socket, st, c) == -1)
        {
            perror("on Write");
            return -1;
        }
    }

    closeSocket(socket);
    return 0;
}
