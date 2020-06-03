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
void mixedFds();


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
char * message[] = {
  "Para asegurarnos que haya entendido, escriba \"grupo 4 es el mejor\\n\"\n",
  "Mixed fds\n"
};
char * ans[] = {
  "grupo 4 es el mejor",
  "a_non_y_mous"
};
char buffer[MAXBUFLEN];
while(1){
  printf("\n--- DESAFIO %d ---\n\n",challenge+1);
  printf("%s",*(message+challenge));
  switch (challenge)
  {
  //va a cambiar al que corresponda el de 2FDS  
  case 1:
    mixedFds();
    break;
  default: break;
  }
  int c=read(4,buffer,MAXBUFLEN);
  buffer[c-1]=0;
  printf("\nbuffer : %s and ans: %s\n",buffer,*(ans+challenge));
  if(strcmp(*(ans+challenge),buffer) == 0){
    printf("tin tin tin CORRECTO!\n");
    challenge++;
  }
  else
  {
    printf("Respuesta incorrecta: %s\n\n",buffer);
  }
  
} 

}

void mixedFds(){
  char * ans = "a_non_y_mous";
  char * trash = "asda213123s[*]*[$dasd23436*12}+{+{dasd234asd43as}-}31}+asd43as}{+{+-**-+dsfd\\¿'¿ASDA213123S[*]*[$Dasd234asd43as}{+{+-**-+dsfd\\¿'¿''dasd5636*12}+{+{-}31}+{3123sdfsadf23''daasdasdasdasdfgsdsd5636*12}+{+{daasd43as}{+{+-**-+dsfd\\¿'¿''dasd5636*12}+{sd234asd43as}-}31}+{3123s5461685as65das5df4ur890'34rhebwidsklmkñaiofpsu8g9hibnjreklm4,3lwqe'pdsñ{.dfsadf23a";
  int x = (strlen(trash)/strlen(ans));
  int tr,rsp,i;
  tr = rsp = i = 0;
  printf("\n\n");
  while(rsp!=strlen(ans)){
    if( i%2 == 1){
      write(1,(ans+rsp++),1);
    }
    else {
      write(2,trash+tr,x);
      tr+=x;
    }
    i++;
  }
    write(2,trash,x/2);
  printf("\n");
}
