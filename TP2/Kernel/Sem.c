#include "include/Sem.h"
#include "include/Mutex.h"
#include "include/Curses.h"
#include "include/String.h"

SemData_t sems[MAX];

int lookSem(int id);

SemData_t * semopen(char * name){
    int id=lookSem(0);
    
    if(id==MAX)
        return -1;

    sems[id].id=id+1;
    sems[id].lock=0;
    CopyString(name, sems[id].name, strlen(name));
    

}

void semwait(SemData_t * sem);

int sempost(SemData_t * sem);

int semclose(SemData_t * sem){
    
}
int lookSem(int id){
    int i;
    for(i=0;i<MAX && sems[i].id!=id;i++);
    return i;
}