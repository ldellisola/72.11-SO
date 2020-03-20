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
    char fifo[6];
    pid_t pid;
}ChildProcess_t;

pid_t waitV();
void createSlaves(ChildProcess_t  processes[][SLAVES]);
void rmFifo();

int main(int  argc, char ** argv){  

    if(argc<2){
        printf("Please, send files\n");
        exit(1);
    }    

    sleep(2);
    
    pid_t v_pid = waitV(); //if ==0 no esta, else es el pid
    
    
    if(v_pid!=0){
        char buffer[BUF];
	    printf("%d\n",v_pid);
    }else
        printf("No hay vista \n");
    
    ChildProcess_t processes[SLAVES];
    createSlaves(&processes);
    
    int resultados=open("resultados", O_WRONLY | O_TRUNC | O_CREAT);
    int i;
    rmFifo();
    for(i=1;i<argc;i++){
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

void createSlaves(ChildProcess_t  processes[][SLAVES]){
    char fifoP[6]={'.','/','f','f','n',0};
   
    int i;
    for(i = 0 ; i < SLAVES ; i++){
        fifoP[4]=i+'0';
        if (mkfifo(fifoP,0666) == -1)  //rw-rw-rw-
        {
            perror("Pipe not established\n");
            exit(-1);
        }
        pid_t pid = fork();

        switch (pid)
        {
        case -1:{
            perror("Error creating child Process\n");
            exit(-1);
            break;}
        case 0:{
            int ownPID = (int) getpid();
            execvp("./slave",(char **)&fifoP);
            break;
            }
        default:
            // Guardo el FD a donde voy a leer y cierro el que escribe.
            strcpy((*processes)[i].fifo,fifoP);
            (*processes)[i].pid = pid;
            break;
        }
    }
}
void rmFifo(){
    char fifoP[6]={'.','/','f','f','n',0};
    int i;
    for(i = 0 ; i < SLAVES ; i++){
        fifoP[4]=i+'0';
        char rm[40]="rm ";
        strcat(rm,fifoP);
        strcat(rm," >/dev/null 2>&1");
        system(rm);
    }    
}