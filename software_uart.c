#include "software_uart.h"

//Temporary
#include <xc.h>

#include <stdbool.h>            // true/false

#include "timer.h"


void PutBit(short bit)
{
    static short stream[120];
    static short counter = 0;
    static bool startBit = false;
    static bool previosBitIsHigh = false;

    if (startBit)
    {
        if (counter < 120)
        {
            stream[counter++] = bit;
        }
        else
        {
            Nop();
            Nop();
            Nop();
            Nop();
            Nop();
        }
    }
    else
    {
        if(bit == 0)
        {
            startBit = previosBitIsHigh? true : false;
        }
        else
        {
            previosBitIsHigh = true;
        }
    }
}

str_t Recieve (void)
{
    
}


software_uart_t Software_UART_Initialize(uartPort_e           port,
                                         unsigned long        baudRate, 
                                         unsigned long long   fcy)
{
    SOFTWARE_UART1_INIT;
    //uartPort_t to timers_e nedded
    timer_t timer = Timer(timer1, baudRate, fcy, PutBit, SOFTWARE_UART1_READ);
    timer.Start();
    
    
    

     
    software_uart_t client;
    return client;
}




//void __attribute__((__interrupt__, no_auto_psv)) _T1Interrupt(void)
//{
//    PutBit(SOFTWARE_UART1_READ);
//    IFS0bits.T1IF = 0; 
//}