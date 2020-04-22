#include "../Include/Curses.h"
#include "../Include/Syscalls.h"
#include "../Include/Time.h"
#include "include/Process.h"

#define LOOP_TIME 5 //1seg

void loop()
{
    int t1 = GetSeconds();
    int t2 = 0;
    do
    {
        // if(++t2 %2000000 == 0)
        // {
        //     printf("HOLA\n");
        // }
        // if (t2 == -1 || t2 - t1 >= LOOP_TIME)
         //   printf("Hey, im %d. See you in %d s", getpid(), LOOP_TIME);
    } while (1);
}