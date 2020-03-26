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

#define MAX 1024

// Parametros
//      Programa
//      FILES...
int main(int argc,char ** argv){

    char ** initialFiles;

    setvbuf(stdout, NULL, _IONBF, 0);


    if(argc <= 1){
        fprintf(stderr,"Invalid Arguments.\n");
        return -1;
    }

    initialFiles = argv;


    // Me quedo solo con los archivos en este arreglo de strings.
    for(int i = 1; i < argc ;i++ )
        initialFiles[i-1] = initialFiles[i];
        
    initialFiles[argc-1] = NULL;


    srand(time(NULL));

    int id = getpid();
    

    bool exit = false;
    int initialIndex = 0;
    do{
        char file[200];

        if(initialFiles[initialIndex] != NULL)
            strncpy(file,initialFiles[initialIndex++],200);
        else
        {
            // Leo del pipe
            int final = read(STDIN_FILENO,file,200);
            file[final] = 0;
        }

        int sleepTime = 3 + rand()%5;

        sleep(sleepTime);

        char str[1000];

        int a = sprintf(str,"%d: Proceso el archivo: %s",id,file);
        write(STDOUT_FILENO,str,a);


            
        

    }while(!exit);
    

    
    // char *file = NULL;
    // size_t linecap = 0;
    // ssize_t linelen;

    // while ((linelen = getline(&file, &linecap, stdin)) > 0) {
    //     FILE * fp;
    //     int status;
    //     char inst[MAX];
    //     snprintf(inst,MAX,"minisat %s |grep -e variables -e clauses: -e CPU -e SAT| \\tr -d \"|\" | tr -s \" \" | tr -d \\\\n",file);
  		
  	// 	fp = popen(inst, "r");
    //     if (fp == NULL){
    //         perror("Popen error:");
    //         exit(-1);
    //     }

    //     char * ans=NULL;
    //     size_t n=0;
    //     ssize_t ansSize;
        
    //     ansSize=getline(&ans,&n,fp);  
    //     if(ansSize==-1){
    //         perror("getLine error:");
    //         exit(-1);
    //     }

    //     char * info=NULL;
    //     info=realloc(info,MAX+strlen(ans));
    //     snprintf(info,MAX,"PID: %d. File: %s. %s \n",getpid(),argv[1],ans);
    //     write(fifo,ans,sizeof(ans));
        
    //     free(info);
    //     free(ans);
    //     status=fclose(fp);
        
    //     if(status==-1){
    //         perror("Fclose error:");
    //         exit(-1);
    //     }
    // }    
    return 0;
}
