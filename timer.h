#ifndef TIMER_H
#define	TIMER_H

#include "timer_methods.h"
#include <stdbool.h>

//Temporary for SOFTWARE_UART1_READ dependency ?
//#include "pins.h"

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



//OPTIONS
//If your devise has not prescaller leave only {1, 0b00}
typedef struct {
    const unsigned short scale; 
    const unsigned short bitsValue;     
}
timer_prescaler_t;



#endif	/* TIMER_H */

