#include "software_uart.h"

//Temporary
#include <xc.h>

#include <stdbool.h>            // true/false
#include <stdlib.h>             // calloc
#include <string.h>   


bool * inProgress;
char response[BUFFERLENGTH];
short bufferLenght_g;
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
     
    software_uart_t client;
    return client;
}






//#define BYTE_LENGHT       8
//#define LINE_FEED         0xa // \n
//#define CARRIAGE_RETURN   0xd // \r
//
//void PutBit(short bit)
//{
//    static short stringCounter         = 0;
//    static short byteCounter           = 0;
//    static bool startBit               = false;
//    static bool stopBit                = false;
//    static bool previosBitIsHigh       = false;
//    static bool endOfString            = false;
//    
//    //templorary, trying to create best algorithm
//    static bool dataBit                = false;
//
//    if (startBit)
//    {
//        buffer_g[stringCounter] |= (bit << byteCounter);
//        
//        dataBit = byteCounter < BYTE_LENGHT;
//        byteCounter = dataBit? (byteCounter + 1) : (0);
//        stopBit = (bit == 1 && !dataBit)? true : false;
//        
//        if(stopBit)                             
//        {
//            endOfString = buffer_g[stringCounter-1] == CARRIAGE_RETURN 
//                             && 
//                          buffer_g[stringCounter]   == LINE_FEED;
//                
//            if(endOfString) 
//            {
//                bufferLenght_g = stringCounter;
//                inProgress = false;
//            }
//                
//            startBit = false;
//            stringCounter++;                     // Next symbol please
//        }     
//    }
//    else
//    {
//        if(bit == 0)
//        {
//            startBit = previosBitIsHigh? true : false;
//            previosBitIsHigh = false;    //Clear flag
//                     
//        }
//        else
//        {
//            previosBitIsHigh = true;  
//        }
//    }
//}






void PutBit(short bit)
{
    static const short byteLenght            = 8;
    static const char lineFeedSymbol         = 0xa;
    static const char carriageReturnSymbol   = 0xd;
    
    static short stringCounter               = 0;
    static short byteCounter                 = 0;
    static bool startBit                     = false;
    static bool stopBit                      = false;
    static bool previosBitIsHigh             = false;
    static bool endOfString                  = false;
    static bool dataBit                      = false;
    
    if (startBit)
    {
        dataBit = byteCounter < byteLenght;
        if(dataBit)
        {
            buffer_g[stringCounter] |= (bit << byteCounter++);
        }
        else
        {
            byteCounter = 0;
            stopBit = (bit == 1 && !dataBit)? true : false;
            if(stopBit)                             
            {
                endOfString = buffer_g[stringCounter-1] == carriageReturnSymbol 
                                && 
                              buffer_g[stringCounter]   == lineFeedSymbol;
                if(endOfString) 
                {
                    bufferLenght_g = stringCounter;
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
