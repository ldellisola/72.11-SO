#include "FDTest.h"

#include <stdio.h>
#include <unistd.h>

void runClosedFDTest(){
    int pipes[2];
    
    if(pipe(pipes) == -1){
        perror("Could't open pipe\n");
    }

    write(pipes[0],"nj213kjh23kh311jh2h3k1",24);

    close(pipes[0]);
    close(pipes[1]);
}
