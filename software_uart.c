#include "software_uart.h"

//Temporary
#include <xc.h>

#include <stdbool.h>            // true/false

//size_t __CalculatePR()
//{
//    
//}


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


bool previosBitIsHigh   = false;
bool startBit           = false;
bool receiving          = false;
//#define DATA_LENGHT       8
//short bitNumber         = DATA_LENGHT;
//short buffer[DATA_LENGHT];
char data[120];
short counter = 0;


//void BuildSymbol(short bit)
//{
//    buffer[number] = bit;
//    
//    if(number == 0)
//    {
//        data = buffer;
//    }
//}

void PutBit(short bit)
{
    if(bit == 0)
    {
        startBit = previosBitIsHigh? true : false;
    }
    else
    {
        previosBitIsHigh = true;
    }
    
    if (counter < 100 && startBit)
    {
        data[counter++] = bit;
//        if(bitNumber == DATA_LENGHT)
//        {
//            //Do nothing,
//            //because this is start bit
//        }
//        else
//        {
//            BuildSymbol(bit, bitNumber);
//        }
//              
//        bitNumber--;     
    }
}

void __attribute__((__interrupt__, no_auto_psv)) _T1Interrupt(void)
{
    PutBit(SOFTWARE_UART1_READ);
    IFS0bits.T1IF = 0; 
}
