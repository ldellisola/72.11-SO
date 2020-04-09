#include "../Include/Time.h"
#include <stdint.h>
#include "../Include/Syscalls.h"
enum{
SECONDS, MINUTES, HOURS, DAYOFWEEK, DAYOFMONTH, MONTH, YEAR
};



int getTime(int id);

int GetSeconds(){
    int ret = getTime(SECONDS);
    return ret;
}

int GetMinutes(){
    int ret = getTime(MINUTES);
    return ret;
}

int GetHours(){
    return getTime(HOURS);
}

int GetDayOfWeek(){
    return getTime(DAYOFWEEK);
}

int GetDayOfMonth(){
    return getTime(DAYOFMONTH);
}

int GetMonth(){
    return getTime(MONTH);
}

int GetYear(){
    int ret = getTime(YEAR);
    return ret;
}


int getTime(int id){
    int time = 0;

    read(FD_TIME,id,&time,0,0);

    return time;
}


uint64_t getTicks(){
    uint64_t ticks = 0;

    read(FD_TIMER,&ticks,0,0,0);
    return ticks;

}