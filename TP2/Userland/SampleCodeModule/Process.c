#include "../Include/Curses.h"
#include "../Include/Syscalls.h"
#include "../Include/Time.h"
#include "include/Process.h"
#include <stdbool.h>

#define LOOP_TIME 5 // N secs

void loop()
{
    bool flag = true;
    unsigned int startSeconds = GetSeconds();
    unsigned int t1 = 0;
    unsigned int t2 = t1;
    int pid = getpid();
    unsigned int elapsed = 0;
    do
    {
        if ((GetSeconds() - startSeconds) >= 59) { // because when more than 1 minute has elapsed timer explodes
            t1 -= startSeconds;                    // keep the timer upon update
            t2 -= startSeconds;
            startSeconds = GetSeconds();
        }
        else
        {
            t2 = GetSeconds() - startSeconds;
        }

        if (((elapsed % LOOP_TIME) == 0 ) && flag) {
            printf("Loop says: My PID is %d. BRB in %d secs\n", pid, LOOP_TIME);
            flag = false;                           //avoid more than 1 call per second
        }
        
        if (t2 != t1) {                             // != and not > because of the first if
            flag = true;
            t1 = t2;
            // printf("Elapsed: %d\n", elapsed);
            elapsed++;
        }
        
    } while (1);
}