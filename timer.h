#ifndef TIMER_H
#define	TIMER_H

#include "timer_methods.h"
#include <stdbool.h>

#include "configuration.h"       //advanced for TIMER_PRESCALERS


typedef enum {
    timer1 = 1, 
    timer2 = 2, 
    invalidFirst = 0, first = timer1, last = timer2
} 
timers_e;


typedef struct
{
  void  (*Start)      (void);
  void  (*Stop)       (void);
} timer_t;


timer_t Timer(const timers_e number,
              const size_t baudrate,
              const unsigned long long fcy,
              bool (*Action)(void*),
              bool * isRunning,
              void * object);



//ADVANCED OPTION (PRESCALER - frequency devide)
//For 4800 baudrate , period is 625  and 1:8 prescaler
//                 or period is 5000 and 1:1 prescaler
typedef struct {
    const unsigned short scale; 
    const unsigned short bitsValue;     
}
timer_prescaler_t;






#endif	/* TIMER_H */

