#include "software_uart.h"

//Temporary
#include <xc.h>

#include <stdbool.h>            // true/false
#include <stdlib.h>             // calloc
#include <string.h>   


str_t Recieve(void)
{
    
}

void Clear()
{
    
}

software_uart_t Software_UART_Initialize(uartPort_e           port,
                                         unsigned long        baudRate,
                                         unsigned long long   fcy)
{
    SOFTWARE_UART1_INIT;

    T1CONbits.TON = 0; // Disable Timer
    T1CONbits.TCS = 0; // Select internal instruction cycle clock
    T1CONbits.TGATE = 0; // Disable Gated Timer mode
    T1CONbits.TCKPS = 0b01;//0b00; // Select 1:1 Prescaler
    TMR1 = 0x00; // Clear timer register
    PR1 = 625;//5000; // Load the period value
    IPC0bits.T1IP = 0x01; // Set Timer1 Interrupt Priority Level
    IFS0bits.T1IF = 0; // Clear Timer1 Interrupt Flag
    IEC0bits.T1IE = 1; // Enable Timer1 interrupt
    T1CONbits.TON = 1; // Start Timer

    software_uart_t client;
    return client;
}


#define BYTE_LENGHT 8

void PutBit(short bit)
{
    static char data[160];
    static short stringCounter = 0;
    static short byteCounter = 0;
    static bool startBit = false;
    static bool previosBitIsHigh = false;

    if(stringCounter == 159)
    {
        Nop();
        Nop();
        Nop();
        Nop();
    }
    
    if (startBit)
    {
        if (byteCounter < BYTE_LENGHT)
        {
            data[stringCounter] |= (bit << byteCounter++);
        }
        else
        {
            if(bit == 1) //Stop bit
            {
                startBit = false;
                previosBitIsHigh = false;
                stringCounter++;
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

void __attribute__((__interrupt__, no_auto_psv)) _T1Interrupt(void)
{
    PutBit(SOFTWARE_UART1_READ);
    IFS0bits.T1IF = 0;
}
