#include "include/Phylo.h"
#include "include/Exec.h"
#include "../Include/Sem.h"
#include "../Include/Curses.h"
#include "../Include/String.h"
#include "../Include/Syscalls.h"

#define MAX 20

enum State {ASLEEP = 0, EATING};
enum State state[MAX];
int pids[MAX];
int phils[MAX];
int amount;
char * S[] = {"s1", "s2", "s3", "s4", "s5", "s6", "s7", "s8", "s9", "s10"
    "s11", "s12", "s13", "s14", "s15", "s16", "s17", "s18", "s19", "s20"};
char * phylos_names[] = {"f1", "f2", "f3", "f4", "f5", "f6", "f7", "f8", "f9", "f10"
    "f11", "f12", "f13", "f14", "f15", "f16", "f17", "f18", "f19", "f20"};

void philosopher_process(int num);


void phylo() {
    int initial_number = 5;
    int mutex = semopen("phmutex",1);
    amount = initial_number;
    
    for(int i = 0; i < amount; i++) {
        state[i] = ASLEEP;
        phils[i] = i;
        // aux1 = philo_p_name(i);
        // aux2 = philo_sem_name(i);
        // printf("Phylo process name is %s \n", aux1);
        // printf("Phylo sem name is %s \n", aux2);
        semopen(S[i],0);
        pids[i] = exec(phylos_names[i], 1, philosopher_process,-1,-1,1,&phils[i]);
    }

    // char c;
    // int aux = 0;
    while(1) {
        // if (aux++ == 1000) {
        // printf("Press 'a' to Add philo, 'r' to Remove philo, any key to continue\n");
        // c = getchar();
        // switch(c) {
        //     case 'a':
        //         if (amount < MAX) {
        //             create_philosopher(amount);
        //         }
        //         aux=0;
        //         break;
        //     case 'r':
        //         if (amount > 1) {
        //             /* redefine this */
        //             kill_philosopher(amount);
        //         }
        //         aux=0;
        //         break;
        //     default:
        //         aux=0;
        //         break;
        // }
        // }

        for (int i = 0; i < amount; i++) {
            printf("%c", (state[i] == ASLEEP) ? '.' : 'E');
        }
        printf("\n");
    }
}

void take_fork(int phnum) {
    semwait("phmutex");
    test(phnum);
    sempost("phmutex");
    semwait(S[phnum]);
}

void put_fork(int phnum) {
    semwait("phmutex");
    state[phnum] = ASLEEP;
    test(left(phnum));
    test(right(phnum));
    sempost("phmutex");
}

void test(int phnum) {
    if ((state[left(phnum)] != EATING) && (state[right(phnum)] != EATING)) {
        printf("El philo nro %d entro a comer\n", phnum);
        state[phnum] = EATING;
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

void philosopher_process(int num) {
    int *i = &num;
    while (1) {
       take_fork(*i);
       put_fork(*i);
    }
}

void kill_philosopher(int i) {
    semclose(S[i]);
    kill_process(&pids[i]);
    state[i] = ASLEEP;
    amount--;
}

void create_philosopher(int i) {
    semopen(S[i], 0);
    pids[i] = exec(S[i], 1, philosopher_process,-1,-1,1,&phils[i]);
    state[i] = ASLEEP;
    amount++;
}