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

#define MAX 200
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
        FILE * fp;
        int status;
        char inst[MAX];
        snprintf(inst,MAX,"minisat %s |grep -e variables -e clauses: -e CPU -e SAT| \\tr -d \"|\" | tr -s \" \" | tr -d \\\\n",file);
  		
  		fp = popen(inst, "r");
        if (fp == NULL){
            perror("Popen error:");
            exit(-1);
        }

        char * ans=NULL;
        size_t n=0;
        ssize_t ansSize;
        
        ansSize=getline(&ans,&n,fp);  
        if(ansSize==-1){
            perror("getLine error:");
            exit(-1);
        }

        char * info=NULL;
        info=realloc(info,MAX+strlen(ans));
        snprintf(info,MAX,"PID: %d. File: %s. %s \n",getpid(),argv[1],ans);
        write(fifo,ans,sizeof(ans));
        
        free(info);
        free(ans);
        status=fclose(fp);
        
        if(status==-1){
            perror("Fclose error:");
            exit(-1);
        }
    }    
    return 0;
}
