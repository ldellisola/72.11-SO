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

#include "GDBTest.h"
#include "FDTest.h"
#include "AudioTest.h"

/* the port users will be connecting to */
#define MYPORT 8080
#define MAXBUFLEN 500

void challenges(int fd);
void mixedFds();
void logo();
void los_simuladores();

extern void _dum1(){};
extern void _dum2(){};
extern void _dum3(){};


char *dummystring = "era%yo";
int main(int argc, char *argv[])
{
  int sockfd;
  /* my address information */
  struct sockaddr_in my_addr;

  unsigned int addr_len = 16;

  sockfd = socket(PF_INET, SOCK_STREAM, IPPROTO_IP);
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

  /* host byte order */
  my_addr.sin_family = AF_INET;

  /* short, network byte order */

  int port = MYPORT;

  if (argc == 2)
  {
    port = atoi(argv[1]);

    if (port == 0)
    {
      printf("Invalid port. Switching to default %d\n", MYPORT);
      port = MYPORT;
    }
  }

  my_addr.sin_port = htons(port);

  /* automatically fill with my IP */
  //my_addr.sin_addr.s_addr = INADDR_ANY;
  struct in_addr inAddr = {inet_addr("0.0.0.0")};
  my_addr.sin_addr = inAddr;

  /* zero the rest of the struct */
  memset(&(my_addr.sin_zero), '\0', 8);

  if (bind(sockfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr)) == -1)
  {
    perror("Server-bind() error lol!");
    exit(1);
  }

  if (listen(sockfd, 5) == -1)
  {
    perror("On Listen");
    exit(-1);
  }

  int communicationFD = accept(sockfd, (struct sockaddr *)&my_addr, &addr_len);

  if (communicationFD == -1)
  {
    perror("On Accept");
    exit(-1);
  }

  // Hago bloqueante la lectura del socket
  int mode = 0;
  ioctl(communicationFD, FIONBIO, &mode);

  printf("Bienvenido! A continuacion debera superar un par de IMPOSIBLES desafios. Que la fuerza te acompañe\n");
  challenges(communicationFD);

  if (close(sockfd) != 0)
    printf("Server-sockfd closing failed!\n");
  else
    printf("Server-sockfd successfully closed!\n");

  return 0;
}

void challenges(int fd)
{
  int challenge = 0;
  char *message[] = {
      "Para asegurarnos que haya entendido, escriba \"grupo 4 es el mejor\\n\"\n",
      "Mixed fds\n",
      "Logo\n",
      "TANGO HOTEL INDIA SIERRA INDIA SIERRA NOVEMBER OSCAR TANGO FOXTROT UNIFORM NOVEMBER NOVEMBER YANKEE \n",
      "NOx+ (4+7x2+2x9)/3 (/)SI \n",
      ".data .comment ? \n",
      "strings: 50 \n",
      "Busca un archivo que no deberia estar en el repositorio, reproducilo y resolve la prueba\n",
      "GDB era clave para el TP2\n",
      "hola?\n",
      "Los Simuladores\n"
  };
  char *ans[] = {
      "grupo 4 es el mejor",
      "a_non_y_mous",
      "bojack horseman",
      "this is not funny",
      "(36)/3",
      ".RUN_ME",
      "era%yo",
      "Harry Potter is dead",
      "Harry Potter is dead",
      "nj213kjh23kh311jh2h3k1",
      "TORTUGA MARITIMA"
  };
  char buffer[MAXBUFLEN];
  while (1)
  {
    if (challenge < 11) {
      printf("\n--- DESAFIO %d ---\n\n", challenge + 1);
      printf("%s", *(message + challenge));
    }
    switch (challenge)
    {
      //va a cambiar al que corresponda el de 2FDS
    case 0:
      // Grupo 4 es el mejor
      break;
    case 1:
      mixedFds();
      break;
    case 2:
      logo();
      break;
    case 3:
      // Militar
      break;
    case 4:
      // Matematica
      break;
    case 5:
      // Tags ASM?
      break;
    case 6:
      // strings
      break;
    case 7:
      runAudioTest();
      break;
    case 8:
      runGDBTest();
      break;
    case 9:
      runClosedFDTest();
      break;
    case 10:
      los_simuladores();
      break;
    default:
      // Termina
      return;
      break;
    }
    int c = read(fd, buffer, MAXBUFLEN);
    if (c == -1)
    {
      perror("On Read");
    }
    else if (c == 0)
    {
      printf("Se cerro el cliente, chau.\n");
      exit(0);
    }
    buffer[c - 1] = 0;

    if (strcmp(*(ans + challenge), buffer) == 0)
    {
      printf("*tin tin tin* CORRECTO!\n");
      challenge++;
    }
    else
    {
      printf("Respuesta incorrecta: %s\n\n", buffer);
    }
  }
}

void mixedFds()
{
  char *ans = "a_non_y_mous";
  char *trash = "asda213123s[*]*[$dasd23436*12}+{+{dasd234asd43as}-}31}+asd43as}{+{+-**-+dsfd\\¿'¿ASDA213123S[*]*[$Dasd234asd43as}{+{+-**-+dsfd\\¿'¿''dasd5636*12}+{+{-}31}+{3123sdfsadf23''daasdasdasdasdfgsdsd5636*12}+{+{daasd43as}{+{+-**-+dsfd\\¿'¿''dasd5636*12}+{sd234asd43as}-}31}+{3123s5461685as65das5df4ur890'34rhebwidsklmkñaiofpsu8g9hibnjreklm4,3lwqe'pdsñ{.dfsadf23a";
  int x = (strlen(trash) / strlen(ans));
  int tr, rsp, i;
  tr = rsp = i = 0;
  printf("\n\n");
  while (rsp != strlen(ans))
  {
    if (i % 2 == 1)
    {
      write(1, (ans + rsp++), 1);
    }
    else
    {
      write(2, trash + tr, x);
      tr += x;
    }
    i++;
  }
  write(2, trash, x / 2);
  printf("\n");
}

void logo()
{
  printf("                           `-+/`                      `-`                                    \n");
  printf("                           `/o+-`                    `+o/`                                   \n");
  printf("                           .++++.                   `:oo+.                                   \n");
  printf("                          `:++++:`     `        `` `-++oo:`                                  \n");
  printf("                         `--++++/`   `     ```   ``-++:+o/`                                  \n");
  printf("                         `::+-``                 `:++:/+++`                                  \n");
  printf("                        `--++:.`                `/++/:++++`                                  \n");
  printf("                        `/--``                 `/+++-+oo+:`                                  \n");
  printf("                       ``.                     :+++:/ooo+.`                                  \n");
  printf("                       `                       ++++-+o++:`                                   \n");
  printf("                      `                      ..++++-+++/` `                                  \n");
  printf("                      ``                 ` `:+-+o++:+o+`   `                                 \n");
  printf("                      `          `:`    --./++/+++++++.     `                                \n");
  printf("                     ` `--      `//     +++++++++++++/-     `                                \n");
  printf("                     `.++. ``  .+o:  : -+++++++++++++++`       `                             \n");
  printf("                     `:oo/:+-.:/:o: :+:+++++++++++++++o/`                                    \n");
  printf("                     -ooooooo+/s++/:+++++++++++++++++oo+/`      `                            \n");
  printf("                    -+oooooo+/hMd:+++++++++++ooo++++oooo+:      `                            \n");
  printf("                  `-+o+oooo++mMMM/+++++++++++++++ooooooo++.     `                            \n");
  printf("                 `:++/++oo/+NMMMMd:++++++++++++++ooooooo++-                                  \n");
  printf("               ``---::+++/+MMMMMMM/+++++//+++++ooo++ooo+++/`    `  `                         \n");
  printf("               `ohhho:+++//MMMMMMh:+++++/::::::/++++o+++++++.      `                         \n");
  printf("               -omMMMy/+++-NMMMmo/++++++/+syso/:-/++++++++/+:                                \n");
  printf("               ``/ddy/++++:yMNy:+o+++++/+mNMMMN///++++++++-/:                                \n");
  printf("               `-//++++++++/m//oooo+++++. `mMNh://++++++++/-+.     `                         \n");
  printf("               `-//++o+++++-:+oooo+++++/+/:++////++++++++++-+/`    `                         \n");
  printf("         `      .++++++++++oooooo++++++/::::::::+++++++++++-+:     `                         \n");
  printf("                .++++++++++oooooo++++++++++++///++++++++++o-+/       `                       \n");
  printf("                .+++++oo/-/oooooo+++++++++++++++++++++++++o-++-      `                       \n");
  printf("               `-++++oo/oh:++ooooo++++++++++++++++o++++oo++-++/`     `                       \n");
  printf("               `:+++oo:yMh:ooooo++++o++++o+++++++ooo+oo+++:/+++:                             \n");
  printf("               `++ooo:hMMh:oooooooooo+++o++++++++ooooo++++-++++/`   `                        \n");
  printf("               .ooo+/hMMMy/+oooooo+++++++++++++oooooo++oo:/+++++`    `                       \n");
  printf("              `/oo+/dMMMMy:+++o+++++++++++++++++++++++oo/:++++++-    ``                      \n");
  printf("              `+oo:hMMMMMh:++++++++++++++++++++++++++++::+++++++.    `                       \n");
  printf("             `-oo/yMMMMMMh:+++++++++++++++/+++++++++++:/++++++++/    `                       \n");
  printf("             `/o/sMMMMMMMd:+++++++++++++++-+++++++++/:/++++++++++-   `                       \n");
  printf("            `.o/oMMMMMMMMm:+++++++++++++++/-+++///::/++/:/+++++++:   `                       \n");
  printf("            `/++NMMMMMMMMm:+++++++++++++++/-///+++++//:/+++++++++:   `                       \n");
  printf("            .+/NMMMMMMMMMm-++++++++++++++/-/++++/////+++++++++++++.  `                       \n");
  printf("           `-:ymNNNmdNMNmd-+++:+++++++++:://++++++oooo++++++++++++/` `                       \n");
  printf("             `yoddddddshdy``.//-++++++/-:++++++++++++++++++++++++++:`                        \n");
  printf("           `  ooyddddsody`   -+-+++:/::++++++++++oo+++++++++++++++++`                        \n");
  printf("              yoydddd/dd-   `/+/++++::oo+++++ooooooooooo++++++++++++..`                      \n");
  printf("           `.+dyddddd:dh`   .+++++/++-ooooooooooooooo++++///++++++++-//-``                   \n");
  printf("           -dddddddddoyd+. `:o+/:/++::oooooo+ooooooooo+++///++++++++--//+/-.`                \n");
  printf("           `hddddddddddddh:/o+:/+++-:ooooooo+ooooooooo++++++++++++++:`::://+/-`              \n");
  printf("           `/ddddddddddddds:+-+++o+-oooooooooooooooooo++++++++++++++/`:::::://..`            \n");
  printf("            `/hddddddddddhy-/++oo/:+ooooooooooooooooooo++ooo++++++++/`::::::::.::-``         \n");
  printf("       `:```.-:/yhddddhs+//++:++:/ooooooooooooooooooooooooo++++++++//.::::::::.::::-.`       \n");
  printf("       `--:::::`://++//+oo+:.::/+ooooooooo++++ooooooooooo+++++++++++--:::::::.-:::::::.`     \n");
  printf("    ``.::::::::.:-::///:////+ooooooooooooo+++++++++++++++++++++++++/.::::::::.::::::::::.`   \n");
  printf("  `.-::::::::::.:::::::.+o++++ooooooooooooo+++++++++++++++++++++++/.::::::::.::::::::::::``  \n");
}

void los_simuladores() {
  FILE * pf;
  char * fn = "milazzo.txt";
  //char buffer [24];
  //const char * r = "el pavo esta en el saco";

  printf("...\n");

  if ((pf = fopen(fn, "r")) == NULL) {
    printf("Error, Vanegas no pudo encontrar a: %s ¿Estuviste un año en la selva, solo, hablandole a una camara de television apagada? KJJJJJJ \n", fn);
    return;
  }

  printf("Fase 1 completa, Santos \n");
  printf("...\n");
  printf("https://youtu.be/rHs_DBLJIwk 18:44\n");
  printf("...\n");

  if (!feof(pf)) {
    char buffer [24];
    const char * r = "el pavo esta en el saco";
    fgets(buffer, 24, pf);
    if (strcmp(buffer, r) == 0) {
      printf("La respuesta es TORTUGA MARITIMA\n");
    }
  }
  else {printf("Lamponne, tenemos un problema... \n");}
  fclose(pf);
  return;
}
