#include "timer.h"
#include <stddef.h>
#include <stdbool.h>

//for 4800 baudrate , period is 625 and 1:8 prescaler or period is 5000 and 1:1 prescaler

timer_prescaler_t prescalers[] = 
{
            {1, 0b00},   //00 = 1:1
            {8, 0b01},   //01 = 1:8 
            {64, 0b10},  //10 = 1:64
            {256, 0b11}  //11 = 1:256
        };

void (*Timer1Action)(short);
short * timer1Object;
//void __attribute__((__interrupt__, no_auto_psv)) _T1Interrupt(void)
//{
//    Timer1Action(timer1Object);
//    Timer1_InterruptFlag_Clear(); 
//}

void    __Timer1_Start(void) { Timer1_Enable(); }
void    __Timer1_Stop(void)  { Timer1_Disable();}

timer_t __Timer1_Init(size_t period, 
                      unsigned short prescaler, 
                      void (*Action)(short),
                      short * object)
{ 
    Timer1_ExternalClock_Disable();
    Timer1_MeasureMode_Disable();
    Timer1_Prescaler_Set(prescaler);
    Timer1_MeasureMode_Counter_Set(0); 
    Timer1_Period_Set(period); 
    Timer1_PriorityFrom0to7_Set(1); 
    Timer1_InterruptFlag_Clear();
    Timer1_Interrupt_Enable();
    
    Timer1Action = Action;
    timer1Object = object;
    
    timer_t client = {&__Timer1_Start, &__Timer1_Stop};
    return client;
}


void (*Timer2Action)(short);
short * timer2Object;
void __attribute__((__interrupt__, no_auto_psv)) _T2Interrupt(void)
{
    Timer2Action(timer2Object);
    Timer2_InterruptFlag_Clear(); 
}

void    __Timer2_Start(void) { Timer2_Enable(); }
void    __Timer2_Stop(void)  { Timer2_Disable();}

timer_t __Timer2_Init(size_t period, 
                      unsigned short prescaler, 
                      void (*Action)(short),
                      short * object)
{
    Timer2_ExternalClock_Disable();
    Timer2_MeasureMode_Disable();
    Timer2_Prescaler_Set(prescaler);
    Timer2_MeasureMode_Counter_Set(0); 
    Timer2_Period_Set(period);
    Timer2_PriorityFrom0to7_Set(1);
    Timer2_InterruptFlag_Clear();
    Timer2_Interrupt_Enable();
    
    Timer1Action = Action;
    timer1Object = object;
    
    timer_t client = {&__Timer2_Start, &__Timer2_Stop};
    return client;
}



size_t __CalculateBaudrate(const unsigned long long fcy,
                           const unsigned short prescaler,
                           const size_t period)
{
    return  (fcy / prescaler) / period;
}

size_t __CalculatePeriod(const unsigned long long fcy,
                         const unsigned short prescaler,
                         const size_t baudrate)
{
    return (fcy / prescaler) / baudrate;
}

unsigned long __AbsoluteDifference (unsigned long value1, unsigned long value2)
{
    return (value1 < value2)? (value2 - value1) : (value1 - value2);
}

size_t __CalculateError(const unsigned long long fcy,
                        const unsigned short prescaler,
                        const size_t baudrate,
                        const size_t period)
{
    size_t calcBaudrate = __CalculateBaudrate(fcy, prescaler, period);
    return __AbsoluteDifference(calcBaudrate, baudrate);
}


timer_prescaler_t __ChosePrescaler(const unsigned long long fcy, 
                                          const size_t baudrate,
                                          const timer_prescaler_t * prescalers,
                                          const unsigned short prescalersLenght)
{
    size_t period;
    size_t error = baudrate;
    size_t calcError = 0;
    unsigned short prescalerNumber;
    
    for (unsigned short i = 0; i < prescalersLenght; i++)
    {
        period    = __CalculatePeriod(fcy, prescalers[i].scale, baudrate);
        calcError = __CalculateError (fcy, prescalers[i].scale, baudrate, period);
 
        if (calcError < error)
        {
            error = calcError;
            prescalerNumber = i;
        }   
    }
    return prescalers[prescalerNumber];
}


timer_t Timer(const timers_e number,
              const size_t baudrate,
              const unsigned long long fcy,
              void (*Action)(short),
              short * object)
{
    timer_prescaler_t prescaler = __ChosePrescaler(fcy, baudrate, prescalers, 
                                  sizeof(prescalers) / sizeof(prescalers[0]));
    size_t pr = __CalculatePeriod(fcy, prescaler.scale, baudrate);
    
    timer_t timer;
    switch(number)
    {
        case timer1: 
             timer = __Timer1_Init(pr, prescaler.bitsValue, Action, object);
        break;   
        
        case timer2: 
             timer = __Timer2_Init(pr, prescaler.bitsValue, Action, object);
        break; 
        
        default:
            printf("No such Timer for this device");
    }
    
    return timer;
}