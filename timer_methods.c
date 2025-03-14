#include "timer_methods.h"


void Timer1_Enable(void)
{
    BIT_TIMER1_SWITCH = 1;
}

void Timer1_Disable(void)
{
    BIT_TIMER1_SWITCH = 0;
}

void Timer1_ExternalClock_Enable(void)
{
    BIT_TIMER1_EXTERNAL_CLOCK = 1;
}

void Timer1_ExternalClock_Disable(void)
{
    BIT_TIMER1_EXTERNAL_CLOCK = 0;
}

void Timer1_MeasureMode_Enable(void)
{
    BIT_TIMER1_GATEMODE = 1;
}

void Timer1_MeasureMode_Disable(void)
{
    BIT_TIMER1_GATEMODE = 0;
}

size_t Timer1_MeasureMode_Counter_Get(void)
{
    return BITS_TIMER1_COUNTER;
}

void Timer1_MeasureMode_Counter_Set(size_t counter)
{
    BITS_TIMER1_COUNTER = counter;
}

unsigned short Timer1_Prescaler_Get(void)
{
    return BITS_TIMER1_PRESCALER;
}

void Timer1_Prescaler_Set(unsigned short prescalerInBitsValue)
{
    BITS_TIMER1_PRESCALER = prescalerInBitsValue;
}