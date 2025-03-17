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

void Timer1_Interrupt_Disable(void)
{
    BIT_TIMER1_INTERRUPT_ENABLE = 0;
}






void Timer2_Enable(void)
{
    BIT_TIMER2_SWITCH = 1;
}

void Timer2_Disable(void)
{
    BIT_TIMER2_SWITCH = 0;
}


void Timer2_ExternalClock_Enable(void)
{
    BIT_TIMER2_EXTERNAL_CLOCK = 1;
}

void Timer2_ExternalClock_Disable(void)
{
    BIT_TIMER2_EXTERNAL_CLOCK = 0;
}


void Timer2_MeasureMode_Enable(void)
{
    BIT_TIMER2_GATEMODE = 1;
}

void Timer2_MeasureMode_Disable(void)
{
    BIT_TIMER2_GATEMODE = 0;
}


size_t Timer2_MeasureMode_Counter_Get(void)
{
    return BITS_TIMER2_COUNTER;
}

void Timer2_MeasureMode_Counter_Set(size_t counter)
{
    BITS_TIMER2_COUNTER = counter;
}


unsigned short Timer2_Prescaler_Get(void)
{
    return BITS_TIMER2_PRESCALER;
}

void Timer2_Prescaler_Set(unsigned short prescalerInBitsValue)
{
    BITS_TIMER2_PRESCALER = prescalerInBitsValue;
}


void Timer2_Period_Set(size_t pr)
{
    BITS_TIMER2_PERIOD = pr;
}

size_t Timer2_Period_Get(void)
{
    return BITS_TIMER1_PERIOD;
}


void Timer2_PriorityFrom0to7_Set(unsigned short priority)
{
    BITS_TIMER2_PRIORITY = priority;
}

unsigned short Timer2_PriorityFrom0to7_Get(void)
{
    return BITS_TIMER2_PRIORITY;
}


void Timer2_InterruptFlag_Clear(void)
{
    BIT_TIMER2_INTERRUPT_FLAG = 0;
}

void Timer2_InterruptFlag_Fill(void)
{
    BIT_TIMER2_INTERRUPT_FLAG = 1;
}


void Timer2_Interrupt_Enable(void)
{
    BIT_TIMER2_INTERRUPT_ENABLE = 1;
}

void Timer2_Interrupt_Disable(void)
{
    BIT_TIMER2_INTERRUPT_ENABLE = 0;
}