#ifndef NETWORK_H
#define NETWORK_H

#include <stdbool.h>

// Selects wheter the system will use the default port or a port provided by 
// the user
int selectPort(bool useCustomPort, char * customPort);

// Starts the server and waits for a client to connect
int startServer(int port, int socket);

// Starts the clients and connects to the server based on port and host.
// The function will return the file descriptor linked to the socket.
int startClient(char * host, int port, int socket);

// it opens a file descriptor for the socket. The client or the server will then
// link this file descriptor to the socket
int openSocket();

// Closes file descriptor that's linked to the socket
void closeSocket(int socket);





#endif