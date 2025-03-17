#include "timer.h"
#include <stddef.h>
#include <stdbool.h>


void __Timer1_Init()
{
    Timer1_Disable();
    Timer1_ExternalClock_Disable();
    Timer1_MeasureMode_Disable();
    Timer1_Prescaler_Set(prescalers[1].bitsValue);
    Timer1_MeasureMode_Counter_Set(0); //
    Timer1_Period_Set(625); //5000 for FCY == 40000000
    Timer1_PriorityFrom0to7_Set(1);
    Timer1_InterruptFlag_Clear();
    Timer1_Interrupt_Enable();
    Timer1_Enable();
}

void __Timer2_Init()
{
    Timer2_Disable();
    Timer2_ExternalClock_Disable();
    Timer2_MeasureMode_Disable();
    Timer2_Prescaler_Set(prescalers[1].bitsValue);
    Timer2_MeasureMode_Counter_Set(0); //
    Timer2_Period_Set(625); //5000 for FCY == 40000000
    Timer2_PriorityFrom0to7_Set(1);
    Timer2_InterruptFlag_Clear();
    Timer2_Interrupt_Enable();
    Timer2_Enable();
}

unsigned long __AbsoluteDifference (unsigned long value1, unsigned long value2)
{
    return (value1 < value2)? (value2 - value1) : (value1 - value2);
}

size_t __CalculateError(const unsigned long long fcy,
                        const size_t baudrate,
                        const size_t pr, 
                        const unsigned short prescaler)
{
    size_t calcBaudrate = (fcy / prescaler) / pr;
    return __AbsoluteDifference(calcBaudrate, baudrate);
}

size_t __GetPeriod()
{
    size_t period;
    
    return period;
}

size_t __CalculatePeriod(const unsigned long long fcy, 
                         const size_t baudrate,
                         const timer_prescaler_t * prescalers,
                         const unsigned short prescalersLenght)
{
    unsigned long long periodWithoutPrescaler = fcy / baudrate;
    
    size_t pr;
    size_t error = baudrate;
    size_t calcError;
    unsigned short scaler;
    unsigned short scalerNumber;
    for (unsigned short i = 0; i < prescalersLenght; i++)
    {
        scaler = prescalers[i].scale;
        pr = periodWithoutPrescaler / scaler;
        calcError = __CalculateError(fcy, baudrate, pr, scaler);
 
        if (calcError < error)
        {
            error = calcError;
            scalerNumber = i;
        }   
    }
       
    return pr;
}

timer_t TimerInitialize(const timers_e number,
                        const size_t baudrate,
                        const unsigned long long fcy,
                        void (*Action)(short),
                        short object)
{
    timer_t client;
    
    size_t period = __CalculatePeriod(fcy, baudrate, prescalers, 
                                      sizeof(prescalers) / sizeof(prescalers[0]));
    
    switch(number)
    {
        case timer1: 
        __Timer1_Init();
        break;   
        
        case timer2: 
        __Timer2_Init(); 
        break; 
        
        default:
            printf("No such UART port for this device");
    }
    
    return client;
}