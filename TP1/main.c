#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>

typedef struct 
{
    int readFD;
    pid_t pid;
    bool open;
}ChildProcess_t;



int main(int  argc, char ** argv){  



    ChildProcess_t processes[5];

    bool end=false;

    


    do{

        for(int i = 0 ; i < 5 ; i++){
            
            int fd[2];
            if (pipe(fd) == -1)
            {
                perror("Pipe not established");
                return -1;
            }
            pid_t pid = fork();


            switch (pid)
            {
            case -1:
                perror("Error creating child Process");
                return -1;
                break;
            case 0:

                

                srand(time(0)+ getpid());

                int ownPID = (int) getpid();

                close(fd[0]);
                
                int rnd =  rand() % 500;

                

                printf("Process %d talsk to father.\t Token: %d\n",ownPID, rnd);
                char str[100];
                int sleepTime = 3 + rand() % 10;
                sleep(sleepTime);

                int n = sprintf(str,"Slept for %d seconds. Secret token: %d",sleepTime, rnd);

                str[n] = 0;

                write(fd[1],str,n);

                exit(EXIT_SUCCESS);

                break;
            default:
                // Guardo el FD a donde voy a leer y cierro el que escribe.
                processes[i].readFD = fd[0];
                processes[i].pid = pid;
                processes[i].open = true;
                close(fd[1]);
                break;
            }
        }

            bool leave = false;

        do{
            int status;

            printf("Waiting for childs\n");
            pid_t ChildPID =  wait(&status);

            leave = true;

            if(ChildPID == -1){
                perror("Wait Failed");
                return -1;
            }
            
            int selected = -1;
            for(int i = 0 ; i < 5 ; i++){
                if(processes[i].pid == ChildPID)
                    selected = i;
            }

            processes[selected].open = false;
            char str[300];

            read(processes[selected].readFD,str,300);

            printf("PARENT:\n\t\tChild process: %d sent the following message:\n\t\t\t %s \n",(int)ChildPID,str);
            

            for(int i = 0 ; i < 5 ; i++){
                if(processes[i].open)
                    leave = false;
            }
            

        }while(!leave);


    }while(!end);


}