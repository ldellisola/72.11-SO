#include "include/Time.h"
#include <stdint.h>
#include "include/Syscalls.h"
enum{
SECONDS, MINUTES, HOURS, DAYOFWEEK, DAYOFMONTH, MONTH, YEAR
};



int getTime(uint64_t id);

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


int getTime(uint64_t id){
    int time = 0;

    _read(FD_TIME,(void *)id,&time,0,0);

    return time;
}


uint64_t getTicks(){
    uint64_t ticks = 0;

    _read(FD_TIMER,&ticks,0,0,0);
    return ticks;

}