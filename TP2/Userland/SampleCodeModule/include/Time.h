#ifndef TIMEH
#define TIMEH
#include <stdint.h>

/***************************************************************/
/*                 Functiones Publicas                         */
/***************************************************************/

int GetSeconds();

int GetMinutes();

int GetHours();

int GetDayOfWeek();

int GetDayOfMonth();

int GetMonth();

int GetYear();

uint64_t getTicks();


#endif
