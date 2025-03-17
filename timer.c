#include "timer.h"
#include <stddef.h>

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

timer_t TimerInitialize(const timers_e number,
                        const size_t baudrate,
                        void (*Action)(short),
                        short object)
{
    timer_t client;
    
    switch(number)
    {
        case timer1: 
        __Timer1_Init();
        break;   
        
        case timer2: 
         
        break; 
        
        default:
            printf("No such UART port for this device");
    }
    
    return client;
}