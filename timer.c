#include "timer.h"


void __Timer1_Init()
{
    Timer1_Disable();
    Timer1_SetInternalClockFromFCY();
    T1CONbits.TGATE = 0; // Disable Gated Timer mode
    T1CONbits.TCKPS = 0b01;//0b00; // Select 1:1 Prescaler
    TMR1 = 0x00; // Clear timer register
    PR1 = 625;//5000; // Load the period value
    IPC0bits.T1IP = 0x01; // Set Timer1 Interrupt Priority Level
    IFS0bits.T1IF = 0; // Clear Timer1 Interrupt Flag
    IEC0bits.T1IE = 1; // Enable Timer1 interrupt
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
        
        break;      
        case timer2: 
         
        break; 
        case timer3: 
        
        break;      
        case timer4: 
         
        break;  
        case timer5: 
        
        break;      
        case timer6: 
         
        break;
        case timer7: 
         
        break;  
        case timer8: 
        
        break;      
        case timer9: 
         
        break; 
        default:
            printf("No such UART port for this device");
    }
    
    
    timer_t client;
    return client;
}