#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
/* the port users will be connecting to */
#define MYPORT 8080
#define MAXBUFLEN 500

void challenges();

int main(int argc, char *argv[]){
int sockfd;
/* my address information */
struct sockaddr_in my_addr;
/* connector’s address information */
struct sockaddr_in their_addr;

int addr_len = 16, numbytes;
char buf[MAXBUFLEN];

if((sockfd = socket(PF_INET, SOCK_STREAM, IPPROTO_IP)) == -1){
    perror("Server-socket() sockfd error lol!");
    exit(1);
}
else
    printf("Server-socket() sockfd %d is OK...\n",sockfd);
setsockopt(sockfd,SOL_SOCKET,SO_REUSEPORT,NULL,4);

/* host byte order */
my_addr.sin_family = AF_INET;

/* short, network byte order */
my_addr.sin_port = htons(MYPORT);

/* automatically fill with my IP */
//my_addr.sin_addr.s_addr = INADDR_ANY;
struct in_addr inAddr= {inet_addr("0.0.0.0")};
my_addr.sin_addr = inAddr;

/* zero the rest of the struct */

memset(&(my_addr.sin_zero), '\0', 8);

 

if(bind(sockfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr)) == -1){
    perror("Server-bind() error lol!");
    exit(1);
}
else
    printf("Server-bind() is OK...\n");

 
listen(sockfd,5);
accept(sockfd,(struct sockaddr *)&my_addr,&addr_len);
printf("Bienvenido! A continuacion debera superar un par de IMPOSIBLES desafios. Que la fuerza te acompañe\n");
challenges();

if(close(sockfd) != 0)

    printf("Server-sockfd closing failed!\n");

else

    printf("Server-sockfd successfully closed!\n");

return 0;

}

void challenges (){
int challenge = 0;
char * message[] = {"Para asegurarnos que haya entendido, escriba \"grupo 4 es el mejor\\n\"\n"};
char * ans[] = {"grupo 4 es el mejor\n"};
char buffer[MAXBUFLEN];
while(challenge!=11){
  printf("\n--- DESAFIO %d ---\n\n",challenge+1);
  printf("%s",*(message+challenge));
  int c=read(4,buffer,MAXBUFLEN);
  buffer[c-1]=0;
  if(strcmp(*(ans+challenge),buffer)){
    printf("Bien!\n");
    challenge++;
  }
  else
  {
    printf("Respuesta incorrecta: %s",buffer);
  }
  
} 

}