#include "software_uart.h"

//Temporary
#include <xc.h>

#include <stdbool.h>            // true/false
#include <stdlib.h>             // calloc
#include <string.h>   


char currentSymbol_g;

char data_g[3];
short dataLenght_g;
bool running_g;


software_uart_t Software_UART_Initialize(uartPort_e           port,
                                         unsigned long        baudRate,
                                         unsigned long long   fcy)
{
    SOFTWARE_UART1_INIT;
    
    //data_g = (char*)calloc(sizeof(char), BUFFERLENGTH); 
    dataLenght_g = 0;
    
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
    
    running_g = true;
    while(running_g) {};
    IEC0bits.T1IE = 0; // Disable Timer1 interrupt
    T1CONbits.TON = 0; // Stop Timer
    //TMR1 = 0x00;
    data_g[dataLenght_g++] = currentSymbol_g;
    
    IEC0bits.T1IE = 1; // Timer1 interrupt
    T1CONbits.TON = 1; //Timer
    running_g = true;
    while(running_g) {};
    IEC0bits.T1IE = 0; // Disable Timer1 interrupt
    T1CONbits.TON = 0; // Stop Timer
    //TMR1 = 0x00;
    data_g[dataLenght_g++] = currentSymbol_g;
    
    Nop();
    Nop();
    Nop();
    Nop();
    
    
    software_uart_t client;
    return client;
}


#define INPUT
#define OUTPUT
bool SymbolIsComming(void * outputCharacter)
{
    INPUT  short bit                         = SOFTWARE_UART1_READ;
    OUTPUT char * symbol                     = outputCharacter;

    static const short byteLenght            = 8;

    static short byteCounter                 = 0;
    static bool startBit                     = false;
    static bool stopBit                      = false;
    static bool previosBitIsHigh             = false;
    
    if (startBit)
    {
        if(byteCounter < byteLenght)
        {
            *symbol |= (bit << byteCounter++);
        }
        else
        {
            stopBit = (bit == 1)? true : false;
            if(stopBit)                             
            {
                byteCounter            = 0;
                startBit               = false;
                return false;
            }     
        }
    }
    else
    {
        if(bit == 0)
        {
            startBit = previosBitIsHigh? true : false;
            previosBitIsHigh = false;                
                     
        }
        else
        {
            previosBitIsHigh = true;  
        }
    }
    
    return true;
}



void __attribute__((__interrupt__, no_auto_psv)) _T1Interrupt(void)
{
    running_g = SymbolIsComming(&currentSymbol_g);

    IFS0bits.T1IF = 0;//Flag
}




//
//#define INPUT
//#define OUTPUT
//bool StringIsComming(void * outputString)
//{
//    INPUT  short bit                         = SOFTWARE_UART1_READ;
//    OUTPUT char * buffer                     = outputString;
//    
//    static const short byteLenght            = 8;
//    static const char lineFeedSymbol         = 0xa;
//    static const char carriageReturnSymbol   = 0xd;
//    
//    static short stringCounter               = 0;
//    static short byteCounter                 = 0;
//    static bool startBit                     = false;
//    static bool dataBit                      = false;
//    static bool stopBit                      = false;
//    static bool endOfString                  = false;
//    static bool previosBitIsHigh             = false;
//    
//    
//    if (startBit)
//    {
//        dataBit = byteCounter < byteLenght;
//        if(dataBit)
//        {
//            buffer[stringCounter] |= (bit << byteCounter++);
//        }
//        else
//        {
//            byteCounter = 0;
//            stopBit = (bit == 1)? true : false;
//            if(stopBit)                             
//            {
//                endOfString = buffer[stringCounter-1] == carriageReturnSymbol 
//                                && 
//                              buffer[stringCounter]   == lineFeedSymbol;
//                if(endOfString) 
//                {
//                    bufferLenght_g = stringCounter;
//                    return false;
//                } 
//                startBit = false;
//                stringCounter++;                     // Next symbol please
//            }     
//        }
//    }
//    else
//    {
//        if(bit == 0)
//        {
//            startBit = previosBitIsHigh? true : false;
//            previosBitIsHigh = false;                //Clear flag
//                     
//        }
//        else
//        {
//            previosBitIsHigh = true;  
//        }
//    }
//    
//    return true;
//}
//
//
//void __attribute__((__interrupt__, no_auto_psv)) _T1Interrupt(void)
//{ 
//    if(StringIsComming(buffer_g))
//    {
//
//    }
//    else
//    {
//        //str_t uartString = {bufferLenght_g, buffer_g};
//        strncpy(response, buffer_g, bufferLenght_g);
//        Nop();
//        Nop();
//        Nop();
//        Nop();
//        
//        //T1CONbits.TON = 0;
//        IEC0bits.T1IE = 0;
//    }
//    
//    IFS0bits.T1IF = 0;
//}
