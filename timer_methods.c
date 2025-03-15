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


void Timer1_Period_Set(size_t pr)
{
    BITS_TIMER1_PERIOD = pr;
}

size_t Timer1_Period_Get(void)
{
    return BITS_TIMER1_PERIOD;
}


void Timer1_PriorityFrom0to7_Set(unsigned short priority)
{
    BITS_TIMER1_PRIORITY = priority;
}

unsigned short Timer1_PriorityFrom0to7_Get(void)
{
    return BITS_TIMER1_PRIORITY;
}


void Timer1_InterruptFlag_Clear(void)
{
    BIT_TIMER1_INTERRUPT_FLAG = 0;
}

void Timer1_InterruptFlag_Fill(void)
{
    BIT_TIMER1_INTERRUPT_FLAG = 1;
}


void Timer1_Interrupt_Enable(void)
{
    BIT_TIMER1_INTERRUPT_ENABLE = 1;
}

void Timer_Interrupt_Disable(void)
{
    BIT_TIMER1_INTERRUPT_ENABLE = 0;
}