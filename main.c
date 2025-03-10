#include "configuration.h"
#include "system.h"               // EnablePLL(FINPUT,FOSC);
#include "perephereal_methods.h"  // EnablePerephereal();EnableModuleGPS();EnableModuleGSM();
#include "registers.h"

#include <libpic30.h>           // delay32() and others
#include <stdbool.h>            // true/false
#include <stdio.h>
#include <string.h>

//Temporary
#include <xc.h>

#include "pins.h"
#define INIT_GPS_RECIEVE  PIN_INIT_INPUT(55)
#define RX_GPS            PIN_GET_BIT(55)


int main(void) {
    
    EnablePLL(FINPUT,FOSC);
    EnablePerepherealPower();
    EnableModuleGPS();
    //EnableModuleGSM();
       
    INIT_GPS_RECIEVE;
    
    PIN_INIT_OUTPUT(3);
    PIN_TURN_HIGH(3);
    __delay_ms(1000);
    PIN_TURN_LOW(3);
      
    BITS_INTERRUPT_CPU_PRIORITY      = 0; //lowest
    BIT_INTERRUPT_NESTING_DISABLE    = 0;
//    BIT_INTERRUPT_PIN55_ENABLE       = 1;
//    BITS_INTERRUPT_PIN55_PRIORITY    = 7; //highest
//    BIT_INTERRUPT_PIN55_STATUS       = 0;
    
    T1CONbits.TON = 0; // Disable Timer
    T1CONbits.TCS = 0; // Select internal instruction cycle clock
    T1CONbits.TGATE = 0; // Disable Gated Timer mode
    T1CONbits.TCKPS = 0b00; // Select 1:1 Prescaler
    TMR1 = 0x00; // Clear timer register
    PR1 = 5000; // Load the period value
    IPC0bits.T1IP = 0x01; // Set Timer1 Interrupt Priority Level
    IFS0bits.T1IF = 0; // Clear Timer1 Interrupt Flag
    IEC0bits.T1IE = 1; // Enable Timer1 interrupt
    T1CONbits.TON = 1; // Start Timer
    
    while(true)
    {
        //Nop();
    }
       
    return 0;
}


bool previosBitIsHigh   = false;
bool startBit           = false;
bool receiving          = false;
#define DATA_LENGHT       8
short bitNumber         = DATA_LENGHT;
short buffer[DATA_LENGHT];
char data[0];



void BuildSymbol(short bit, short number)
{
    buffer[number] = bit;
    
    if(number == 0)
    {
        data[] = buffer;
    }
}

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
    
    if (startBit)
    {
        if(bitNumber == DATA_LENGHT)
        {
            //Do nothing,
            //because this is start bit
        }
        else
        {
            BuildSymbol(bit, bitNumber);
        }
              
        bitNumber--;     
    }
}


void __attribute__((__interrupt__, no_auto_psv)) _T1Interrupt(void)
{
    PutBit(RX_GPS);
    IFS0bits.T1IF = 0; 
}


//void __attribute__((interrupt)) _INT0Interrupt( void )               
//{    
//    BIT_INTERRUPT_PIN55_STATUS       = 0;
//}


//Waiting for:
//$GPGGA,101714.421,,,,,0,00,,,M,0.0,M,,000053
//$GPGSA,A,1,,,,,,,,,,,,,,,1E
//$GPRMC,101714.421,V,,,,,,,011124,,,N4F
//$GPGGA,101715.421,,,,,0,00,,,M,0.0,M,,000052
//$GPGSA,A,1,,,,,,,,,,,,,,,\*1E
//$GPGSV,3,1,12,30,65,060,24,11,64,239,29,20,62,347,,13,40,277,\*7B
//$GPGSV,3,2,12,06,37,176,,05,32,324,,07,32,043,,14,19,133,\*75
//$GPGSV,3,3,12,22,11,154,,09,06,061,,19,00,183,,29,-1,299,\*6