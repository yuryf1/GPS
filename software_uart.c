#include "software_uart.h"

//Temporary
#include <xc.h>

#include <stdbool.h>            // true/false

#include "timer.h"

#define BYTE_LENGHT 8


char * buffer_g;
short bufferLenght_g;

void PutBit(short bit)
{
    static short stringCounter = 0;
    static short byteCounter = 0;
    static bool startBit = false;
    static bool previosBitIsHigh = false;

    if (startBit)
    {
        if (byteCounter < BYTE_LENGHT)
        {
            buffer_g[stringCounter] |= (bit << byteCounter++);
        }
        else
        {
            if(bit == 1)                             //if stop bit
            {
                if(buffer_g[stringCounter] == 0xa)   //if end of the string
                {
                    bufferLenght_g = stringCounter;
                    T1CONbits.TON = 0;               // Stop Timer
                }
                
                startBit = false;
                previosBitIsHigh = false;
                stringCounter++;                     // Next symbol please
            }
            byteCounter = 0;
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

//void PutBit(short bit)
//{
//    static short stream[120];
//    static short counter = 0;
//    static bool startBit = false;
//    static bool previosBitIsHigh = false;
//
//    if (startBit)
//    {
//        if (counter < 120)
//        {
//            stream[counter++] = bit;
//        }
//        else
//        {
//
//        }
//    }
//    else
//    {
//        if(bit == 0)
//        {
//            startBit = previosBitIsHigh? true : false;
//        }
//        else
//        {
//            previosBitIsHigh = true;
//        }
//    }
//}

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