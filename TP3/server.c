// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>

#include "Challenges/Challenge1.h"
#include "Challenges/Challenge2.h"
#include "Challenges/Challenge3.h"
#include "Challenges/Challenge4.h"
#include "Challenges/Challenge5.h"
#include "Challenges/Challenge6.h"
#include "Challenges/Challenge7.h"
#include "Challenges/Challenge8.h"
#include "Challenges/Challenge9.h"
#include "Challenges/Challenge10.h"
#include "Challenges/Challenge11.h"

typedef const char *(*function_returns_string_t)();
typedef void (*function_t)();

typedef struct 
{
  function_returns_string_t getHint;
  function_returns_string_t getAnswer;
  function_t run;
} Challenge_t;

/* the port users will be connecting to */
#define DEFAULT_PORT 8080
#define MAXBUFLEN 500

// This function will run through the challenges and interact with the client
// via the specified File Descriptor
void runChallenges(int fd);

// Reads input from the client
void readFromClient(int fd, char * buffer, int bufferSize);

// Opens socket for the server
int openSocket();

// Closes socket for the server
void closeSocket(int socket);

// Selects wheter the server will use the default port or a prot provided by 
// the user
int selectPort(int argc, char ** argv);

// Starts the server and waits for a client to connect
int startServer(int port, int socket);


int main(int argc, char *argv[])
{
  int socket = openSocket();
  int port = selectPort(argc, argv);
  int fd = startServer(port,socket);

  printf("Bienvenido! A continuacion debera superar un par de IMPOSIBLES desafios. Que la fuerza te acompañe\n");
  runChallenges(fd);

  closeSocket(socket);

  return 0;
}

void runChallenges(int fd)
{
  int challengeIndex = 0;
  char buffer[MAXBUFLEN];

  Challenge_t  challenges[] = {
    { challenge1_GetHint, challenge1_GetAnswer, challenge1_Run },
    { challenge2_GetHint, challenge2_GetAnswer, challenge2_Run },
    { challenge3_GetHint, challenge3_GetAnswer, challenge3_Run },
    { challenge4_GetHint, challenge4_GetAnswer, challenge4_Run },
    { challenge5_GetHint, challenge5_GetAnswer, challenge5_Run },
    { challenge6_GetHint, challenge6_GetAnswer, challenge6_Run },
    { challenge7_GetHint, challenge7_GetAnswer, challenge7_Run },
    { challenge8_GetHint, challenge8_GetAnswer, challenge8_Run },
    { challenge9_GetHint, challenge9_GetAnswer, challenge9_Run },
    { challenge10_GetHint, challenge10_GetAnswer, challenge10_Run },
    { challenge11_GetHint, challenge11_GetAnswer, challenge11_Run },
    { NULL, NULL, NULL }
  };
  
  while (challenges[challengeIndex].getHint != NULL)
  {
    Challenge_t challenge = challenges[challengeIndex];

    printf("\n--- DESAFIO %d ---\n\n", challengeIndex + 1);
    printf("%s", challenge.getHint());

    challenge.run();
    
    readFromClient(fd,buffer,MAXBUFLEN);
    
    if (strcmp(challenge.getAnswer(), buffer) == 0)
    {
      printf("*tin tin tin* CORRECTO!\n");
      challengeIndex++;
    }
    else
    {
      printf("Respuesta incorrecta: %s\n\n", buffer);
    }
  }

  printf("Resolvieron todos los Desafios!\n");
}

void readFromClient(int fd, char * buffer, int bufferSize) { 

  int c = read(fd, buffer, bufferSize);
  if (c == -1) {
    perror("On Read");
  }
  else if (c == 0) {
    printf("Se cerro el cliente, chau.\n");
    exit(0);
  }
  else {
    buffer[c - 1] = 0;
  }
}

int startServer(int port, int socket){

  struct sockaddr_in my_addr;
  my_addr.sin_family = AF_INET;
  my_addr.sin_port = htons(port);
  struct in_addr inAddr = {inet_addr("0.0.0.0")};
  my_addr.sin_addr = inAddr;

  /* zero the rest of the struct */
  memset(&(my_addr.sin_zero), '\0', 8);

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

int selectPort(int argc, char ** argv){
  int port = DEFAULT_PORT;

  if (argc == 2)
  {
    port = atoi(argv[1]);

    if (port == 0)
    {
      printf("Invalid port. Switching to default %d\n", DEFAULT_PORT);
      port = DEFAULT_PORT;
    }
  }
  return port;
}