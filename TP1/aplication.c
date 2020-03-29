#define _GNU_SOURCE   

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


#include <errno.h>
#include <sys/wait.h>
#include <sys/select.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "semaphoreHelper.h"
#include "shmHelper.h"

#include <poll.h>

#define SLAVES 5
#define BUF 100
#define MAX 1000
#define BLOCK 20

#define SLAVE_EXEC "./SatSlave"

typedef struct 
{
    int writeFD;
    int readFD;
    int cant;
    pid_t pid;
}ChildProcess_t;




pid_t waitV();
void createSlaves(ChildProcess_t  processes[SLAVES],char * filesToSend[SLAVES * 2]);
// int readline(int fd, char * buffer);


int main(int  argc, char ** argv){  

    if(argc<2){
        printf("Please, send files\n");
        exit(1);
    }    

    printf("Connect to display with code: %d\n",argc);

    sleep(2);

    // Inicializo el semaforo
    char semName[50];
    sprintf(semName,"SEM_%d",argc);
    SemData_t semData = semaphoreSetUp(semName,true);

    // Creo el archivo de memoria compartida y uso como nombre la cantidad de archivos que recibi
    char shmName[50];
    sprintf(shmName,"SHM_%d",argc);
    SHMData_t shmData = shmCreate(shmName,50 * MAX);
    


    int fileIndex = 1; 
    
    ChildProcess_t processes[SLAVES];

    char * initialFiles[SLAVES * 2];

    // Preparo los archivos iniciales que le voy a mandar a los hijos, si tengo menos archivos que el doble de los esclavos, 
    // les mando NULL para que no los reconozcan los esclavos y se queden esperando a que el padre les mande archivos.
    for(int i = 0 ; i < SLAVES * 2 ; i++){
        if(i + 1 < argc){
            initialFiles[i] = argv[i+1];
        }else{
            initialFiles[i] = NULL;
        }

        fileIndex++;
    }
    
    createSlaves(processes,initialFiles);

    bool exitCondition = false;

    int maxFDPlusOne = SLAVES + 1;

    setvbuf(stdout, NULL, _IONBF, 0);


    char response[MAX];

    do{

        
        // struct pollfd polls[SLAVES];

        // for(int i = 0 ; i < SLAVES ; i++){
        //     polls[i].fd = processes[i].readFD;
        //     polls[i].events = POLLIN;
        // }

        // Seteo el arreglo de FDs que el select va a estar escuchando. Esto se tiene que hacer siempre que se va a llamar select
        fd_set listeningFDs;
        FD_ZERO(&listeningFDs);

        for(int i = 0 ; i < SLAVES ; i++){
            FD_SET(processes[i].readFD,&listeningFDs);
        }

        for(int j = 0 ; j < SLAVES ; j++){
            if(FD_ISSET(processes[j].readFD,&listeningFDs))
                printf("AsignandoFD: %d\n",processes[j].readFD);
        }
        
        printf("Esperando a slave\n");
        int retVal = select(maxFDPlusOne,&listeningFDs,NULL,NULL,NULL);
        // int retVal = poll(polls,(nfds_t)6,-1);
        printf("Respondieron %d slaves \n",retVal);
        if(retVal == -1){
            perror("Master waiting for slave to speak");
            exit(-1);
        }

        // Hay que ver si podemos obtener el FD que queremos a partir de la lista de fd_set que nos queda despues de select.
        for(int i = 0 ; i < SLAVES ; i++){

            if(!FD_ISSET(processes[i].readFD,&listeningFDs))
                break;
            // if( (polls[i].revents & POLLIN) != POLLIN)
            //     break;
            
            

            int activeFD = processes[i].readFD;

            printf("FD: %d \n",activeFD);
            int size = read(activeFD,response,MAX);
            if(size == -1){
                perror("Reading from Slave");
                exit(-1);
            }

            
            response[size] = 0;
            printf("Respondio PID: %d Mensaje: %s\n",processes[i].pid,response);
            // Lo guardo en memoria compartida

            SemaphoreWait(&semData);
            
            shmWrite(response,size,&shmData);
            
            SemaphorePost(&semData);


            // Le asigno el proximo archivo al slave
            // Veo si en la proxima ronda va a terminar. Si no va a terminar le mando otro archivo.
            exitCondition = ++fileIndex > argc;
            if(!exitCondition){
                int writeFD = processes[i].writeFD;

                printf("Contactandome con slave: %d\n",processes[i].pid);
                int strSize = strlen(argv[fileIndex]);

                if(write(writeFD,argv[fileIndex],strSize) == -1){
                    perror("Writing to Slave");
                    exit(-1);
                }
            }
            FD_CLR(processes[i].readFD,&listeningFDs);
        }

    }while(!exitCondition);


    // Mato a los esclavos

    // Guardo el archivo de memoria compartida en un archivo real

    FILE * outputFile = fopen("output.txt", "w+");
    if(outputFile == NULL){
        perror("Creating output file");
        exit(-1);
    }

    int outputFileFD = fileno(outputFile);
    if(outputFileFD == -1){
        perror("Converting File to File Descriptor");
        exit(-1);
    }



    if( write(outputFileFD,shmData.map,shmData.writeIndex) == -1){
        perror("Writting to output file");
        exit(-1);
    }

    // Borro al semaforo

    semaphoreDestroy(&semData);

    // Borro memoria compartida

    shmDestroy(&shmData);


    
    // int resultados=open("resultados", O_WRONLY | O_TRUNC | O_CREAT);
    // int i,j;
    // for(i=1;i<argc;i++){
    //     for(j=0;(processes[j].cant)==2 && j<SLAVES;j++);
    //     if(j==SLAVES){
    //         //... hay que esperar porque todos llenos
    //         //una vez que le dicen que uno terminó
    //         char * ans=NULL;
    //         size_t x;
    //         int k;
    //         int pid;
    //         while((x=readline(fifo,ans))>0){
    //             sscanf(ans,"%*s %d",&pid);
    //             for(k=0;processes[k].pid!=pid && k<SLAVES;k++);
    //             processes[k].cant--;
                
    //             write(resultados,ans,sizeof(ans));                
    //             if(v_pid!=0){
    //                 //mandar ans al buffer si esta vista
    //             }
    //         }
    //         j=k;
    //     }
    //     write(processes[j].writeFD,argv[i],sizeof(argv[i]));
    //     processes[j].cant++;
    // }
    // system("rm ./ff >/dev/null 2>&1");
    
}


pid_t waitV(){
        
        char buffer[BUF];
        system("ps | grep vista > rta"); //look for Vista process
        FILE * file=fopen("./rta","r");
        fscanf(file,"%s",buffer);
        system("rm ./rta");
        
        return atoi(buffer);
}

#define READ 0
#define WRITE 1

void createSlaves(ChildProcess_t  processes[SLAVES],char * filesToSend[SLAVES * 2]){
    int i;
    for(i = 0 ; i < SLAVES ; i++){
        int MasterToSlave[2], SlaveToMaster[2];

        if(pipe(MasterToSlave) == -1){
            perror("Error creating pipe Master to Slave:");
            exit(-1);
        }

        if(pipe(SlaveToMaster) == -1){
            perror("Error creating pipe Slave to Master:");
            exit(-1);
        }
        pid_t pid = fork();
        switch (pid)
        {
        case -1:{
            perror("Error creating child Process:");
            exit(-1);
            break;}
        case 0:{

            // Configuro el pipe Master To Slave
            if(close(MasterToSlave[WRITE]) == -1){
                perror("Forbiding Slave to WRITE to Master on MasterToSlave pipe");
                exit(-1);
            }
            int dupnum = 0;
            if(( dupnum = dup2(MasterToSlave[READ],STDIN_FILENO)) == -1){
                perror("Converting MasterToSlave into STDIN");
                exit(-1);
            }

            // Configuro el pipe Slave To Master
            if(close(SlaveToMaster[READ]) == -1){
                perror("Forbiding Slave to READ from Master on SlaveToMaster pipe");
                exit(-1);
            }
            if((dupnum = dup2(SlaveToMaster[WRITE],STDOUT_FILENO)) == -1){
                perror("Converting SlaveToMaster into STDOUT");
                exit(-1);
            }

            char * c[4]={SLAVE_EXEC,filesToSend[2*i],filesToSend[2*i+1],NULL};
            if(execvp(SLAVE_EXEC,c)==-1)
                perror("Execvp error:");
            break;
            }
        default:

            // Configuro el pipe Master To Slave
            if(close(MasterToSlave[READ]) == -1){
                perror("Forbiding Master to READ from Slave on MasterToSlave pipe");
                exit(-1);
            }

            // Configuro el pipe Slave To Master
            if(close(SlaveToMaster[WRITE]) == -1){
                perror("Forbiding Master to WRITE from Slave on SlaveToMaster pipe");
                exit(-1);
            }

            processes[i].readFD = SlaveToMaster[READ];
            processes[i].writeFD = MasterToSlave[WRITE];
            processes[i].pid = pid;
            break;
        }
    }
}
// int readline(int fd, char * buffer) {
//     // char c;
//     // int counter = 0;
//     // int x;
//     // // while ((x=read(fd, &c, 1)) != 0) {
//     // //     if (c == '\n') {
//     // //         break;
//     // //     }
        
//     // //     if(buffer==NULL||strlen(buffer)==counter)
//     // //         buffer=realloc(buffer,counter+BLOCK);
        
//     // //     buffer[counter++] = c;
//     // // }
//     // return x==0 ? x:counter;

//     return 0;
// }