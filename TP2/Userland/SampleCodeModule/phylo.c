#include "include/phylo.h"
#include "include/Exec.h"
#include "include/Process.h"
#include "../Include/Sem.h"
#include "../Include/Curses.h"
#include "../Include/String.h"
#include "include/Process.h"
#include "../Include/Syscalls.h"

#define MAX 15

enum State state[MAX];
int phils[MAX];
int amount;
char table[MAX] = {0};
int g_var;
int pids[MAX];
char * mutex = "phmutex";
char * S[] = {"s0", "s1", "s2", "s3", "s4", "s5", "s6", "s7", "s8", "s9", "s10"
    "s11", "s12", "s13", "s14"};
char * phylos_names[] = {"f0","f1", "f2", "f3", "f4", "f5", "f6", "f7", "f8", "f9", "f10",
    "f11", "f12", "f13", "f14"};

int phylo(int argc,char ** argv) {
    int initial_number = 5;
    semopen(mutex,1);
    amount = initial_number;
    g_var = 0;
    
    semwait(mutex);
    for(int i = 0; i < amount; i++) {
        state[i] = ASLEEP;
        table[i] = '.';
        semopen(S[i], 0);
        exec(phylos_names[i], 1, philosopher_process,-1,-1,0,NULL);
    }
    sempost(mutex);

    char c;
    while(1) {
        // c = readKey();
        // switch(c) {
        //     case 'A':
        //     case 'a':
        //         if (amount < MAX) {
        //             create_philosopher();
        //         }
        //         break;
        //     case 'R':
        //     case 'r':
        //         if (amount > 1) {
        //             kill_philosopher();
        //         }
        //         break;
        //     case 'I':
        //     case 'i':
        //         semwait(mutex);
        //         printf("INFO \n");
        //         for (int j = 0; j < amount; j++) {
        //             printf ("Phylo %d, PID: %d \n", j, pids[j]);
        //         }
        //         sempost(mutex);
        //     default:
        //         break;
        // }

        semwait(mutex);
        table[amount] = '\0';
        printf("%s\n",table);
        sempost(mutex);
    }
 return 0;   
}

void take_fork(int phnum) {
    semwait(mutex);
    test(phnum);
    sempost(mutex);
    semwait(S[phnum]);
}

void put_fork(int phnum) {
    semwait(mutex);
    state[phnum] = ASLEEP;
    table[phnum] = '.';
    test(left(phnum));
    test(right(phnum));
    sempost(mutex);
}

void test(int phnum) {
    if ((state[left(phnum)] != EATING) && (state[right(phnum)] != EATING)) {
        state[phnum] = EATING;
        table[phnum] = 'E';
        sempost(S[phnum]);
    }
}

int left (int phnum) { return (phnum + amount - 1) % amount;}

int right (int phnum) { return (phnum + 1) % amount;}

int philosopher_process(int num,char ** argv) {
    int i = g_var++;
    pids[i] = getpid();
    while (1) {
       take_fork(i);
       put_fork(i);
    }
   return 0; 
}

void kill_philosopher() {
    semwait(mutex);
    amount--;
    semclose(S[amount]);
    int aux = pids[amount];
    kill_process(&aux);
    state[amount] = ASLEEP;
    table[amount] = '.';
    sempost(mutex);
}

void create_philosopher() {
    semopen(S[amount], 0);
    state[amount] = ASLEEP;
    table[amount] = '.';
    semwait(mutex);
    exec(phylos_names[amount++], 1, philosopher_process,-1,-1,0,NULL);
    sempost(mutex);
}