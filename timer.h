#ifndef TIMER_H
#define	TIMER_H

#include "timer_methods.h"

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
              void (*Action)(short),
              short * object);



//OPTIONS
//If your devise has not prescaller leave only {1, 0b00}
typedef struct {
    const unsigned short scale; 
    const unsigned short bitsValue;     
}
timer_prescaler_t;

timer_prescaler_t prescalers[] = 
{
            {1, 0b00},   //00 = 1:1
            {8, 0b01},   //01 = 1:8 
            {64, 0b10},  //10 = 1:64
            {256, 0b11}  //11 = 1:256
        };

#endif	/* TIMER_H */

