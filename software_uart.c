#include "software_uart.h"

//Temporary
#include <xc.h>

#include <stdbool.h>            // true/false
#include <stdlib.h>             // calloc
#include <string.h>   

bool receiving = true;
bool * inProgress;
char response[BUFFERLENGTH];
unsigned short bufferLenght_g;
char * buffer_g;


//str_t Recieve(void)
//{
//    str_t message = {bufferLenght_g, buffer_g};
//    return message;
//}

void Clear()
{
    
}

software_uart_t Software_UART_Initialize(uartPort_e           port,
                                         unsigned long        baudRate,
                                         unsigned long long   fcy)
{
    SOFTWARE_UART1_INIT;
    buffer_g = (char*)calloc(sizeof(char), BUFFERLENGTH);
    inProgress = (bool*)calloc(sizeof(bool), 1);
    inProgress = true;
    
    T1CONbits.TON = 0; // Disable Timer
    T1CONbits.TCS = 0; // Select internal instruction cycle clock
    T1CONbits.TGATE = 0; // Disable Gated Timer mode
    T1CONbits.TCKPS = 0b00; ///0b01;// Select 1:1 Prescaler
    TMR1 = 0x00; // Clear timer register
    PR1 = 5000; //625;// Load the period value
    IPC0bits.T1IP = 0x01; // Set Timer1 Interrupt Priority Level
    IFS0bits.T1IF = 0; // Clear Timer1 Interrupt Flag
    IEC0bits.T1IE = 1; // Enable Timer1 interrupt
    T1CONbits.TON = 1; // Start Timer
     
    //buffer_g = buffer;
    software_uart_t client;
    return client;
}


#define BYTE_LENGHT       8
#define LINE_FEED         0xa // \n
#define CARRIAGE_RETURN   0xd // \r

void PutBit(short bit)
{
    static short stringCounter         = 0;
    static short byteCounter           = 0;
    static bool startBit               = false;
    static bool previosBitIsHigh       = false;

    if (startBit)
    {
        if (byteCounter < BYTE_LENGHT)
        {
            buffer_g[stringCounter] |= (bit << byteCounter++);
        }
        else
        {
            byteCounter = 0;
            
            if(bit == 1)                             //if stop bit
            {
                if(buffer_g[stringCounter-1] == CARRIAGE_RETURN 
                      && 
                   buffer_g[stringCounter]   == LINE_FEED) //if end of the string
                {
                    bufferLenght_g = stringCounter;
                    //receiving = false;
                    inProgress = false;
                }
                
                startBit = false;
                stringCounter++;                     // Next symbol please
            }     
        }
    }
    else
    {
        if(bit == 0)
        {
            startBit = previosBitIsHigh? true : false;
            previosBitIsHigh = false;    //Clear flag
                     
        }
        else
        {
            previosBitIsHigh = true;  
        }
    }
}

void __attribute__((__interrupt__, no_auto_psv)) _T1Interrupt(void)
{ 
    //if(receiving)
    if(inProgress)
    {
        PutBit(SOFTWARE_UART1_READ);
    }
    else
    {
        strncpy(response, buffer_g, bufferLenght_g);
        Nop();
        Nop();
        Nop();
        Nop();
        
        T1CONbits.TON = 0;
        IEC0bits.T1IE = 0;
    }
    
    IFS0bits.T1IF = 0;
}
