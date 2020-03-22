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
#define MAX 2
#define BLOCK 20

typedef struct 
{
    int fd;
    int cant;
    pid_t pid;
}ChildProcess_t;

pid_t waitV();
void createSlaves(ChildProcess_t  processes[][SLAVES],char * path);
int readline(int fd, char * buffer);

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
    
    char * fifoP="./ff";
    if (mkfifo(fifoP,0666) == -1){  //rw-rw-rw-
                perror("Pipe not established");
                exit(-1);
    }
    int fifo=open(fifoP, O_RDONLY);
    
    createSlaves(&processes,fifoP);
    
    int resultados=open("resultados", O_WRONLY | O_TRUNC | O_CREAT);
    int i,j;
    for(i=1;i<argc;i++){
        for(j=0;(processes[j].cant)==2 && j<SLAVES;j++);
        if(j==SLAVES){
            //... hay que esperar porque todos llenos
            //una vez que le dicen que uno terminó
            char * ans=NULL;
            size_t x;
            int k;
            int pid;
            while((x=readline(fifo,ans))>0){
                sscanf(ans,"%*s %d",&pid);
                for(k=0;processes[k].pid!=pid && k<SLAVES;k++);
                processes[k].cant--;
                
                write(resultados,ans,sizeof(ans));                
                if(v_pid!=0){
                    //mandar ans al buffer si esta vista
                }
            }
            j=k;
        }
        write(processes[j].fd,argv[i],sizeof(argv[i]));
        processes[j].cant++;
    }
    system("rm ./ff >/dev/null 2>&1");
    
}


pid_t waitV(){
        
        char buffer[BUF];
        system("ps | grep vista > rta"); //look for Vista process
        FILE * file=fopen("./rta","r");
        fscanf(file,"%s",buffer);
        system("rm ./rta");
        
        return atoi(buffer);
}

void createSlaves(ChildProcess_t  processes[][SLAVES],char * path){
    int i;
    for(i = 0 ; i < SLAVES ; i++){
        int fd[2];
        if(pipe(fd)==-1){
            perror("Pipe error:");
            exit(-1);}
        pid_t pid = fork();
        switch (pid)
        {
        case -1:{
            perror("Error creating child Process:");
            exit(-1);
            break;}
        case 0:{
            close(fd[1]);
            dup2(fd[0],0);
            char * c[4]={"./slave",path,NULL};
            if(execvp("./slave",c)==-1)
                perror("Execvp error:");
            break;
            }
        default:
            // Guardo el FD a donde voy a leer y cierro el que escribe.
            
            close(fd[0]);
            (*processes)[i].fd=fd[1];
            (*processes)[i].pid = pid;
            break;
        }
    }
}
int readline(int fd, char * buffer) {
    char c;
    int counter = 0;
    int x;
    while ((x=read(fd, &c, 1)) != 0) {
        if (c == '\n') {
            break;
        }
        
        if(buffer==NULL||strlen(buffer)==counter)
            buffer=realloc(buffer,counter+BLOCK);
        
        buffer[counter++] = c;
    }
    return x==0 ? x:counter;
}