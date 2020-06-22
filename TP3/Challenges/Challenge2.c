#include "Challenge2.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

const char * challenge2_GetHint(){
    return "Mixed fds\n";
}

const char * challenge2_GetAnswer(){
    return "a_non_y_mous";
}

void challenge2_Run(){
    char *ans = "a_non_y_mous";
    char *trash = "asda213123s[*]*[$dasd23436*12}+{+{dasd234asd43as}-}31}+asd43as}{+{+-**-+dsfd\\¿'¿ASDA213123S[*]*[$Dasd234asd43as}{+{+-**-+dsfd\\¿'¿''dasd5636*12}+{+{-}31}+{3123sdfsadf23''daasdasdasdasdfgsdsd5636*12}+{+{daasd43as}{+{+-**-+dsfd\\¿'¿''dasd5636*12}+{sd234asd43as}-}31}+{3123s5461685as65das5df4ur890'34rhebwidsklmkñaiofpsu8g9hibnjreklm4,3lwqe'pdsñ{.dfsadf23a";
    int x = (strlen(trash) / strlen(ans));
    size_t rsp;
    int tr, i;
    tr = rsp = i = 0;
    printf("\n\n");
    while (rsp != strlen(ans))
    {
        if (i % 2 == 1)
        {
            write(1, (ans + rsp++), 1);
        }
        else
        {
            write(2, trash + tr, x);
            tr += x;
        }
        i++;
    }

    write(2, trash, x / 2);
    printf("\n");
}