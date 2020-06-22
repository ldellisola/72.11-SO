// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "Network.h"

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


#define MAXBUFLEN 500

// This function will run through the challenges and interact with the client
// via the specified File Descriptor
void runChallenges(int fd);

// Reads input from the client
void readFromClient(int fd, char * buffer, int bufferSize);

int main(int argc, char *argv[])
{
  int socket = openSocket();
  int port = selectPort(argc == 2, argv[1]);
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