#include <time.h>

extern int __GetTime__(int code);

enum{
SECONDS, MINUTES, HOURS, DAYOFWEEK, DAYOFMONTH, MONTH, YEAR
};


int GetSeconds();
int GetMinutes();
int GetHours();
int GetDayOfWeek();
int GetDayOfMonth();
int GetMonth();
int GetYear();


int handleTimeRequest(int id){

    switch (id)
    {
        case SECONDS:   return GetSeconds();
        case MINUTES:   return GetMinutes();
        case HOURS:     return GetHours();
        case DAYOFWEEK: return GetDayOfWeek();
        case DAYOFMONTH:return GetDayOfMonth();
        case MONTH:     return GetMonth();
        case YEAR:      return GetYear();
    }
}


int GetSeconds(){
    int ss1 = __GetTime__(0)/16;
    int ss2 = __GetTime__(0) - ss1*16;
    return ss1*10 + ss2;
}

int GetMinutes(){
    int mm1 = __GetTime__(2)/16;
    int mm2 = __GetTime__(2) - mm1*16;
    return mm1*10 + mm2;
}

int GetHours(){
    int hh1 = __GetTime__(4)/16;
    int hh2 = __GetTime__(4) - hh1*16;
    return hh1*10 + hh2;
}

int GetDayOfWeek(){
    return __GetTime__(6)/16;
}
int GetDayOfMonth(){
    int mm1 = __GetTime__(7)/16;
    int mm2 = __GetTime__(7) - mm1*16;
    return mm1*10 + mm2;
    }

int GetMonth(){
    int mm1 = __GetTime__(8)/16;
    int mm2 = __GetTime__(8) - mm1*16;
    return mm1*10 + mm2;
}

#include <Curses.h>

int GetYear(){
    int aa1 = __GetTime__(9)/16;
    int aa2 = __GetTime__(9) - aa1*16 ;
    int a = aa1 * 10 + aa2;

    return a  ;
}