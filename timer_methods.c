#include "timer_methods.h"

void Timer1_Enable(void)
{
    BIT_TIMER1_SWITCH = 1;
}

void Timer1_Disable(void)
{
    BIT_TIMER1_SWITCH = 0;
}

void Timer1_SetInternalClockFromFCY(void)
{
    BIT_TIMER1_EXTERNAL_CLOCK_SOURSE = 0;
}

void Timer1_SetExternalClockFromT1CK(void)
{
    BIT_TIMER1_EXTERNAL_CLOCK_SOURSE = 1;
}