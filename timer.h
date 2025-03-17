#ifndef TIMER_H
#define	TIMER_H

#include "timer_methods.h"

typedef enum {
    timer1 = 1, 
    timer2 = 2, 
    timer3 = 3, 
    timer4 = 4, 
    timer5 = 5, 
    timer6 = 6, 
    timer7 = 7, 
    timer8 = 8, 
    timer9 = 9,
    invalidFirst = 0, first = timer1, last = timer9
} 
timers_e;


typedef struct
{
  void  (*Start)      (void);
  void  (*Stop)       (void);
  void  (*Terminate)  (void);
} timer_t;

timer_t TimerInitialize(const timers_e number,
                        const size_t baudrate,
                        const unsigned long long fcy,
                        void (*Action)(short),
                        short object);



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

