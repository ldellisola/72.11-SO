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

#define MAX 150
int main(int argc,char ** argv){
    
    if(argc!=2){
        printf("Error, not file found");
    }
    
    char * fifoP=argv[1];
    int fifo=open(fifoP, O_WRONLY);
    
    char *file = NULL;
    size_t linecap = 0;
    ssize_t linelen;

    while ((linelen = getline(&file, &linecap, stdin)) > 0) {
        FILE *fp;
        int status;
        char * ans=NULL;
        size_t n=0;
        ssize_t ansSize;
char inst[MAX]="minisat ";
        strcat(inst,argv[1]);

        //strcat(inst," | grep -o -e \"Number of [a-z]+: [0-9]+\" -e \"CPU time.*\" -e\".*SATISFIABLE\"");
  		
  		fp = popen(inst, "r");
        if (fp == NULL){
            perror("Popen error:");
            exit(-1);
        }
       
       while((ansSize=getline(&ans,&n,fp))>0)
            write(fifo,ans,ansSize);
        
        status=fclose(fp);
        if(status==-1){
            perror("Fclose error:");
            exit(-1);
        }
    }    
    return 0;
}