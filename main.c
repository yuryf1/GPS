#include "configuration.h"
#include "system.h"               // EnablePLL(FINPUT,FOSC);
#include "perephereal_methods.h"  // EnablePerephereal();EnableModuleGPS();EnableModuleGSM();
#include "pins.h"
#include "registers.h"

#include <libpic30.h>           // delay32() and others
#include <stdbool.h>            // true/false
#include <stdio.h>
#include <string.h>

//Temporary
#include <xc.h>


int main(void) {
    
    EnablePLL(FINPUT,FOSC);
    EnablePerepherealPower();
    //EnableModuleGPS();
    EnableModuleGSM();
        
    PIN_INIT_OUTPUT(3);
    PIN_TURN_HIGH(3);
    __delay_ms(2000);
         
    BITS_INTERRUPT_CPU_PRIORITY      = 0; //lowest
    BIT_INTERRUPT_NESTING_DISABLE    = 0;
    BIT_INTERRUPT_PIN55_ENABLE       = 1;
    BITS_INTERRUPT_PIN55_PRIORITY    = 7; //highest
    BIT_INTERRUPT_PIN55_STATUS       = 0;
    
    T1CONbits.TON = 0; // Disable Timer
    T1CONbits.TCS = 0; // Select internal instruction cycle clock
    T1CONbits.TGATE = 0; // Disable Gated Timer mode
    T1CONbits.TCKPS = 0b00; // Select 1:1 Prescaler
    TMR1 = 0x00; // Clear timer register
    PR1 = 64000; // Load the period value
    IPC0bits.T1IP = 0x01; // Set Timer1 Interrupt Priority Level
    IFS0bits.T1IF = 0; // Clear Timer1 Interrupt Flag
    IEC0bits.T1IE = 1; // Enable Timer1 interrupt
    T1CONbits.TON = 1; // Start Timer

    while(true)
    {
        Nop();
    }
       
    return 0;
}


void __attribute__((interrupt)) _INT0Interrupt( void )               
{
    //Maybe we must write 1 and turn on timer for 0
    
    BIT_INTERRUPT_PIN55_STATUS       = 0;
}


//Lets create a timer
void __attribute__((__interrupt__, no_auto_psv)) _T1Interrupt(void)
{
    //Maybe we must write 0 
    PIN_TURN_LOW(3);
    __delay_ms(500);
    PIN_TURN_HIGH(3);
    
    
    IFS0bits.T1IF = 0; 
}