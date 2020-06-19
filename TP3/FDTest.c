// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "FDTest.h"

#include <stdio.h>
#include <unistd.h>
#include <string.h>

void runClosedFDTest(){
    int pipes[2];
    
    if(pipe(pipes) == -1){
        perror("Could't open pipe\n");
    }

    char * ttt = "nj213kjh23kh311jh2h3k1";


    write(pipes[0],ttt,strlen(ttt));

    close(pipes[0]);
    close(pipes[1]);
}
