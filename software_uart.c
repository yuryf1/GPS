#include "software_uart.h"

#include "configuration.h"
#include "timer.h"
//Temporary
//#include <xc.h>

#include <stdbool.h>            // true/false
#include <stdlib.h>             // calloc
#include <string.h>   


#define INPUT
#define OUTPUT
bool SymbolIsComming(void * outputCharacter)
{
    INPUT  short bit                         = SOFTWARE_UART1_READ;
    OUTPUT char * symbol                     = outputCharacter;

    static const short byteLenght            = 8;

    static short byteCounter                 = 0;
    static bool startBit                     = false;
    static bool dataBit                      = false;
    static bool stopBit                      = false;
    static bool previosBitIsHigh             = false;
    
    if (startBit)
    {
        dataBit = byteCounter < byteLenght;
        if(dataBit)
        {
            *symbol |= (bit << byteCounter++);
        }
        else
        { 
            byteCounter                      = 0;  
            startBit                         = false;
            previosBitIsHigh                 = false; 
            
            stopBit = (bit == 1)? true : false;
            if(stopBit)                             
            {
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



//char currentSymbol_g1 = 0;
//char currentSymbol_g2 = 0;
//char currentSymbol_g3 = 0;
//char currentSymbol_g4 = 0;
//char currentSymbol_g5 = 0;

char currentSymbol_g  = 0;
char data[BUFFERLENGTH];
short dataCounter     = 0;
bool running_g;
software_uart_t Software_UART_Initialize(uartPort_e           port,
                                         unsigned long        baudRate,
                                         unsigned long long   fcy)
{
    SOFTWARE_UART1_INIT;

    running_g = false;
    
    timer_t timer = Timer(timer1, 4800, FCY, SymbolIsComming, &running_g, &currentSymbol_g);
    
          running_g = true;
    timer.Start(); 
          while(running_g) {};
    timer.Stop();
    data[dataCounter++] = currentSymbol_g; 
    currentSymbol_g = 0;
    
              running_g = true;
    timer.Start(); 
          while(running_g) {};
    timer.Stop();
    data[dataCounter++] = currentSymbol_g; 
    currentSymbol_g = 0;
    
              running_g = true;
    timer.Start(); 
          while(running_g) {};
    timer.Stop();
    data[dataCounter++] = currentSymbol_g; 
    currentSymbol_g = 0;
    
              running_g = true;
    timer.Start(); 
          while(running_g) {};
    timer.Stop();
    data[dataCounter++] = currentSymbol_g; 
    currentSymbol_g = 0;
    
    
//    timer = Timer(timer1, 4800, FCY, SymbolIsComming, &running_g, &currentSymbol_g2);
//          running_g = true;
//    timer.Start(); 
//          while(running_g) {};
//    timer.Stop();
//    
//    timer = Timer(timer1, 4800, FCY, SymbolIsComming, &running_g, &currentSymbol_g3);
//          running_g = true;
//    timer.Start(); 
//          while(running_g) {};
//    timer.Stop();
//    
//    timer = Timer(timer1, 4800, FCY, SymbolIsComming, &running_g, &currentSymbol_g4);
//          running_g = true;
//    timer.Start(); 
//          while(running_g) {};
//    timer.Stop();
//    
//    timer = Timer(timer1, 4800, FCY, SymbolIsComming, &running_g, &currentSymbol_g5);
//          running_g = true;
//    timer.Start(); 
//          while(running_g) {};
//    timer.Stop();
 
    Nop();
    Nop();
    Nop();
    
    
    software_uart_t client;
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
