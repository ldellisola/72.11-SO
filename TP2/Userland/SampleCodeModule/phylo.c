#include "include/phylo.h"
#include "include/Exec.h"
#include "include/Process.h"
#include "../Include/Sem.h"
#include "../Include/Curses.h"
#include "../Include/String.h"
#include "../Include/Syscalls.h"

#define MAX 20

enum State state[MAX];
// int pids[MAX];
int phils[MAX];
int amount;
char table[MAX] = {0};
int g_var;
int pids[MAX];
char * mutex = "phmutex";
char * S[] = {"s0", "s1", "s2", "s3", "s4", "s5", "s6", "s7", "s8", "s9", "s10"
    "s11", "s12", "s13", "s14", "s15", "s16", "s17", "s18", "s19"};
char * phylos_names[] = {"f0","f1", "f2", "f3", "f4", "f5", "f6", "f7", "f8", "f9", "f10"
    "f11", "f12", "f13", "f14", "f15", "f16", "f17", "f18", "f19"};



void phylo() {
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
    bool trying;
    while(1) {
        c = readKey();
        switch(c) {
            case 'a':
                if (amount < MAX) {
                    trying = true;
                    while(trying) {
                        if ((state[0] != EATING) && (state[amount-1] != EATING)) {
                            create_philosopher();
                            trying = false;
                        }
                    }
                }
                break;
            case 'r':
                if (amount > 1) {
                    kill_philosopher();
                }
                break;
            default:
                break;
        }

        semwait(mutex);
        // for (int i = 0; i < amount; i++) {
        //     putChar((state[i] == ASLEEP) ? '.' : 'E');
        // }
        // printf("\n");
        table[amount] = '\0';
        printf("%s\n",table);
        sempost(mutex);
    }
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

// char * philo_p_name (int phnum) {
//     char pname[6] = "ph";
//     char r[3];
//     IntToString(r,3,phnum);
//     pname[3] = r[0];
//     pname[4] = r[1];
    
//     if (phnum >= 10) {
//         pname[5] = '\0';
//     }
//     return pname;
// }

// char * philo_sem_name(int phnum) {
//     char pname[6] = "sm";
//     char r[3];
//     IntToString(r,3,phnum);
//     pname[3] = r[0];
//     pname[4] = r[1];
    
//     if (phnum >= 10) {
//         pname[5] = '\0';
//     }
//     return pname;
// }

void philosopher_process() {
    int i = g_var++;
    pids[i] = getpid();
    while (1) {
       take_fork(i);
       put_fork(i);
    }
}

void kill_philosopher() {
    semwait(mutex);
    amount--;
    kill_process(&pids[amount]);
    semclose(S[amount]);
    state[amount] = ASLEEP;
    table[amount] = '.';
    sempost(mutex);
    return;
}

void create_philosopher() {
    semwait(mutex);
    semopen(S[amount], 0);
    state[amount] = ASLEEP;
    table[amount] = '.';
    exec(phylos_names[amount], 1, philosopher_process,-1,-1,0,NULL);
    amount++;
    sempost(mutex);
    return;
}