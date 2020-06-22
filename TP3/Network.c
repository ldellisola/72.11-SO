// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "Network.h"

#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <asm-generic/socket.h>
#include <stdio.h>
#include <stdlib.h>

#define DEFAULT_PORT 8080

struct in_addr getHostInfo(char * host);
struct sockaddr_in prepareSocket(int port, char * host);

int selectPort(bool useCustomPort, char * customPort){
  int port = DEFAULT_PORT;

  if (useCustomPort)
  {
    port = atoi(customPort);

    if (port == 0)
    {
      printf("Invalid port. Switching to default %d\n", DEFAULT_PORT);
      port = DEFAULT_PORT;
    }
  }
  return port;
}

struct sockaddr_in prepareSocket(int port, char * host){
  struct sockaddr_in addr;
  addr.sin_family = PF_INET;
  addr.sin_port = htons(port);
  addr.sin_addr = getHostInfo(host);

  /* zero the rest of the struct */
  memset(&(addr.sin_zero), '\0', 8);

  return addr;
}

int startServer(int port, int socket){

    struct sockaddr_in my_addr = prepareSocket(port,"0.0.0.0");

    // Links a socket to a file descriptor
    if (bind(socket, (struct sockaddr *)&my_addr, sizeof(struct sockaddr)) == -1)
    {
        perror("Server-bind() error lol!");
        exit(1);
    }

    if (listen(socket, 5) == -1)
    {
        perror("On Listen");
        exit(-1);
    }

    unsigned int addr_len = 16;

    int communicationFD = accept(socket, (struct sockaddr *)&my_addr, &addr_len);

    if (communicationFD == -1)
    {
        perror("On Accept");
        exit(-1);
    }

    // Hago bloqueante la lectura del socket
    int mode = 0;
    ioctl(communicationFD, FIONBIO, &mode);

    return communicationFD;
}

int openSocket(){
  int sockfd = socket(PF_INET, SOCK_STREAM, IPPROTO_IP);
  if (sockfd == -1)
  {
    perror("Server-socket() sockfd error lol!");
    exit(1);
  }

  int on=1;
  if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEPORT, &on, sizeof(on)) == -1)
  {
    perror("On SetSockOpt");
    exit(-1);
  }

  return sockfd;
}

void closeSocket(int socket){
  if (close(socket) != 0)
    perror("On socket close\n");
  else
    printf("Server-sockfd successfully closed!\n");
}

struct in_addr getHostInfo(char * host){

    struct in_addr inAddr = {inet_addr(host)};
    return inAddr;
}

int startClient(char * host, int port, int socket){
    struct sockaddr_in their_addr = prepareSocket(port,host);

    if (connect(socket, (struct sockaddr *)&their_addr, sizeof(struct sockaddr)) == -1)
    {
        perror("connect()");
        exit(1);
    }
    else
        printf("Client-The connect() is OK...\n");

    return socket;
}