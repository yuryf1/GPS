#include "software_uart.h"

#include "timer.h"

#include <stdbool.h>            // true/false
#include <stdlib.h>             // calloc


unsigned long long softwareUART1_maxTicks_g;           //Setup by initialization

#define INPUT
#define OUTPUT
bool SymbolIsComming(OUTPUT void * character)
{
    INPUT  unsigned long long maxWaitTicks   = softwareUART1_maxTicks_g;
    INPUT  unsigned short bit                = SOFTWARE_UART1_READ;
    OUTPUT char * symbol                     = character;

    static const unsigned short byteLenght   = 8;
    
    static unsigned short byteCounter        = 0;
    static unsigned short waitingTicks       = 0;
    static bool startBit                     = false;
    static bool dataBit                      = false;
    static bool stopBit                      = false;
    
    bool overTime                            = false;
    
    if (startBit)
    {
        dataBit = byteCounter < byteLenght;
        if(dataBit)
        {
            *symbol |= (bit << byteCounter++);
        }
        else
        { 
            byteCounter = 0;  
            startBit = false;

            stopBit = (bit == 1)? true : false;
            if(stopBit)                             
            {
                return false;
            }
        }
        
        waitingTicks = 0;
    }
    else
    {
        waitingTicks++;
        startBit = (bit == 0)? true : false;
    }
    
    overTime = waitingTicks > maxWaitTicks;
    if (overTime)
    {
        waitingTicks = 0;
        return false;
    }
    else
    {
        return true;
    }
}


void __Software_UART_Clear(str_t * str)
{
   if(str)
   {
       if(str->pointer)
       {
           free(str->pointer);
           str->pointer = NULL;
       }
   }
}


timer_t softwareUART1_Timer_g;
bool    softwareUART1_RunningFlag_g;
char    softwareUART1_CurrentSymbol_g; 
str_t   softwareUART1_CurrentString_g;

str_t __Software_UART1_Recieve(void)
{
    static const char lineFeedSymbol               = 0xa;
    //static const char carriageReturnSymbol         = 0xd;
    
    char * message = (char*)calloc(sizeof(char), SOFTWARE_UART1_BUFF);
    unsigned short messageCounter                  = 0;
    bool endOfString                               = false;
    
    while((messageCounter < SOFTWARE_UART1_BUFF) && (!endOfString))
    {
        softwareUART1_RunningFlag_g = true;     
        softwareUART1_Timer_g.Start(); 
        while(softwareUART1_RunningFlag_g) {};  
        softwareUART1_Timer_g.Stop();
        
        message[messageCounter++] = softwareUART1_CurrentSymbol_g; 
        endOfString = softwareUART1_CurrentSymbol_g == lineFeedSymbol;
        softwareUART1_CurrentSymbol_g = 0b00000000;     
    }
    
    softwareUART1_CurrentString_g.length  = messageCounter;
    softwareUART1_CurrentString_g.pointer = message;
    
    return softwareUART1_CurrentString_g;
}



void __Software_UART1_Clear(void)
{
  __Software_UART_Clear(&softwareUART1_CurrentString_g);
}



software_uart_t Software_UART(const uartPort_e           port,
                              const unsigned long        baudRate,
                              const unsigned long long   fcy)
{
    software_uart_t client;
            
    switch(port)
    {
        case uart1:
            SOFTWARE_UART1_INIT;
            softwareUART1_maxTicks_g = baudRate * (SOFTWARE_UART1_WAIT / 1000ULL);
            softwareUART1_Timer_g = Timer(timer1, baudRate, fcy, 
                                            SymbolIsComming, 
                                            &softwareUART1_RunningFlag_g, 
                                            &softwareUART1_CurrentSymbol_g);
            client.Recieve = __Software_UART1_Recieve;
            client.Clear   = __Software_UART1_Clear;
        break;
        
        case uart2:
            SOFTWARE_UART2_INIT;
        break;
        
        default:
            printf("No such UART port in software uart.");
    }

    return client;
}






//void __attribute__((__interrupt__, no_auto_psv)) _T1Interrupt(void)
//{
//    running_g = SymbolIsComming(&currentSymbol_g);
//
//    IFS0bits.T1IF = 0;//Flag
//}


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
