#include "timer.h"
#include <stddef.h>                 //size_t


timer_prescaler_t prescalers[] = 
{
    #ifdef TIMER_PRESCALERS
        TIMER_PRESCALERS
    #else
        {1,   0b00}    //00 = 1:1
    #endif
};

bool (*Timer1Action)(void*);
bool * timer1Running;
void * timer1Object;
void __attribute__((__interrupt__, auto_psv)) _T1Interrupt(void)
{
    *timer1Running = Timer1Action(timer1Object);
    Timer1_InterruptFlag_Clear(); 
}

void    __Timer1_Start(void) { Timer1_Enable();  }
void    __Timer1_Stop(void)  { Timer1_Disable(); }
timer_t __Timer1_Init(size_t period, 
                      unsigned short prescaler, 
                      bool (*Action)(void*),
                      bool * isRunning,
                      void * object)
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
    timer1Running = isRunning;
    timer1Object = object;

    timer_t client = {&__Timer1_Start, &__Timer1_Stop};
    return client;
}


bool (*Timer2Action)(void*);
bool * timer2Running;
void * timer2Object;
void __attribute__((__interrupt__, auto_psv)) _T2Interrupt(void)
{
    *timer2Running = Timer2Action(timer2Object);
    Timer2_InterruptFlag_Clear(); 
}

void    __Timer2_Start(void) { Timer2_Enable(); }
void    __Timer2_Stop(void)  { Timer2_Disable();}

timer_t __Timer2_Init(size_t period, 
                      unsigned short prescaler, 
                      bool (*Action)(void*),
                      bool * isRunning,
                      void * object)
{
    Timer2_ExternalClock_Disable();
    Timer2_MeasureMode_Disable();
    Timer2_Prescaler_Set(prescaler);
    Timer2_MeasureMode_Counter_Set(0); 
    Timer2_Period_Set(period);
    Timer2_PriorityFrom0to7_Set(1);
    Timer2_InterruptFlag_Clear();
    Timer2_Interrupt_Enable();
    
    Timer2Action  = Action;
    timer2Running = isRunning;
    timer2Object  = object;
    
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
              bool (*Action)(void*),
              bool * isRunning,
              void * object)
{
    timer_prescaler_t prescaler = __ChosePrescaler(fcy, baudrate, prescalers, 
                                  sizeof(prescalers) / sizeof(prescalers[0]));
    size_t pr = __CalculatePeriod(fcy, prescaler.scale, baudrate);
    
    timer_t timer;
    switch(number)
    {
        case timer1: 
             timer = __Timer1_Init(pr, prescaler.bitsValue, Action, isRunning, object);
        break;   
        
        case timer2: 
             timer = __Timer2_Init(pr, prescaler.bitsValue, Action, isRunning, object);
        break; 
        
        default:
            printf("No such Timer for this device");
    }
    
    return timer;
}


//    T1CONbits.TON = 0; // Disable Timer
//    T1CONbits.TCS = 0; // Select internal instruction cycle clock
//    T1CONbits.TGATE = 0; // Disable Gated Timer mode
//    T1CONbits.TCKPS = 0b00; ///0b01;// Select 1:1 Prescaler
//    TMR1 = 0x00; // Clear timer register
//    PR1 = 5000; //625;// Load the period value
//    IPC0bits.T1IP = 0x01; // Set Timer1 Interrupt Priority Level
//    IFS0bits.T1IF = 0; // Clear Timer1 Interrupt Flag
//    IEC0bits.T1IE = 1; // Enable Timer1 interrupt
//    T1CONbits.TON = 1; // Start Timer