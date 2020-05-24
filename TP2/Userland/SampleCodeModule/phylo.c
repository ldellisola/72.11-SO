#include "include/phylo.h"
#include "include/Exec.h"
#include "include/Process.h"
#include "include/Sem.h"
#include "include/Curses.h"
#include "include/String.h"
#include "include/Process.h"
#include "include/Syscalls.h"
#include "include/Time.h"

#define MAX 15
#define ALIVE 1
#define DEAD 0

enum State state[MAX];
int phils[MAX];
int amount;
char table[MAX];
int g_var;
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

    for(int i = 0; i < amount; i++) {
        state[i] = ASLEEP;
        phils[i] = DEAD;
        table[i] = '.';
    }
    
    semwait(mutex);
    for(int i = 0; i < amount; i++) {
        state[i] = ASLEEP;
        table[i] = '.';
        phils[i] = ALIVE;
        semopen(S[i], 0);
        exec(phylos_names[i], 1, philosopher_process,-1,-1,0,NULL);
    }
    sempost(mutex);

    printf("Welcome to phylo. Press (a) to add. (r) to remove. (q) to exit\n");
    sleep();
    sleep();

    char c;
    while(1) {
        c = readKeyNoBlock();
        switch(c) {
            case 'A':
            case 'a':
                if (amount < MAX) {
                    semwait(mutex);
                    create_philosopher();
                    sempost(mutex);
                }
                break;
            case 'R':
            case 'r':
                if (amount > 1) {
                    semwait(mutex);
                    phils[amount-1] = DEAD;
                    sempost(mutex);
                }
                break;
            case 'Q':
            case 'q':
                semwait(mutex);
                printf("Killing phylos... \n");
                for (int aux = 0; aux < amount; aux++) {
                    phils[aux] = DEAD;
                }
                sempost(mutex);
                sleep();
                sleep();
                semclose(mutex);
                exit_process();
                break;
            default:
                break;
        }

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
    semwait(mutex);
    int i = g_var++;
    sempost(mutex);

    while (1) {
       if (phils[i] == DEAD) {
           kill_philosopher();
           exit_process();
       } 
       take_fork(i);
       put_fork(i);
    }
   return 0; 
}

void kill_philosopher() {
    semwait(mutex);
    amount--;
    g_var--;
    state[amount] = ASLEEP;
    table[amount] = '.';
    semclose(S[amount]);
    sempost(mutex);
    return;
}

void create_philosopher() {
    semopen(S[amount], 0);
    state[amount] = ASLEEP;
    table[amount] = '.';
    phils[amount] = ALIVE;
    exec(phylos_names[amount++], 1, philosopher_process,-1,-1,0,NULL);
}

void sleep() {
    int i = GetSeconds();
    while((i - GetSeconds()) == 0);
    return;
}