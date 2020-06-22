// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "Challenge10.h"

#include <stdio.h>
#include <unistd.h>
#include <string.h>

const char * challenge10_GetHint(){
    return "hola?\n";
}

const char * challenge10_GetAnswer(){
    return "nj213kjh23kh311jh2h3k1";
}

void challenge10_Run(){
    int pipes[2];
    
    if(pipe(pipes) == -1){
        perror("Could't open pipe\n");
    }

    const char * ttt = challenge10_GetAnswer();
    write(pipes[0],ttt,strlen(ttt));

    close(pipes[0]);
    close(pipes[1]);
}