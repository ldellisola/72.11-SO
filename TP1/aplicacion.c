#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>



#define SLAVES 5
#define BUF 100

typedef struct 
{
    char * fifo;
    pid_t pid;
}ChildProcess_t;

pid_t waitV();
void createSlaves(ChildProcess_t ** processes);

int main(int  argc, char ** argv){  
    sleep(2);
    
    pid_t v_pid = waitV(); //if ==0 no esta, else es el pid
    
    if(argc<2){
        printf("Please, send files");
        exit(1);
    }    
    
    if(v_pid!=0){
        char buffer[BUF];
	    printf("%d\n",v_pid);
    }else
        printf("No hay vista \n");
    
    if(argc==1){
        printf("Please send files");
        exit(1);
    }

    ChildProcess_t processes[SLAVES];
    createSlaves(&processes);
    

    int resultados=open("resultados", O_WRONLY | O_TRUNC | O_CREAT);
    for(int i=1;i<argc;i++){
        //...
    }
    
}


pid_t waitV(){
    char buffer[BUF];

        system("ps | grep vista > rta"); //look for Vista process
        FILE * file=fopen("./rta","r");
        fscanf(file,"%s",buffer);
        system("rm ./rta");
        
        return atoi(buffer);
}

void createSlaves(ChildProcess_t ** processes){
    char fifo[6]={'.','/','f','f','n',0};
   

    for(int i = 0 ; i < SLAVES ; i++){
        fifo[4]=i;
        if (mkfifo(fifo,0666) == -1)  //rw-rw-rw-
        {
            perror("Pipe not established");
            return -1;
        }
        pid_t pid = fork();


        switch (pid)
        {
        case -1:{
            perror("Error creating child Process");
            return -1;
            break;}
        case 0:{
            int ownPID = (int) getpid();
            char * sPath="./slave";
            char ** args={sPath,fifo};
            execvp(sPath,args);
            break;
            }
        default:
            // Guardo el FD a donde voy a leer y cierro el que escribe.
            (*processes)[i].fifo = fifo;
            (*processes)[i].pid = pid;
            break;
        }
    }
    
}