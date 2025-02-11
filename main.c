#define FINPUT 10000000ULL      // 10 MHz oscillator
#define FOSC   80000000ULL      // x8 and x6 PLL devides work good
#define FCY    FOSC/2           // device instruction clock for delay_ms()


#include "system.h"
#include "pins.h"
#include "registers.h"

#include <libpic30.h>           // delay32() and others
#include <stdbool.h>            // true/false





int main(void) {
      
    EnablePLL(FINPUT,FOSC);
    EnablePerepherial();
    
    PIN_INIT_OUTPUT(3);  
       
    
    BITS_INTERRUPT_CPU_PRIORITY      = 0; //lowest
    BIT_INTERRUPT_NESTING_DISABLE    = 0;
    BIT_INTERRUPT_PIN55_ENABLE       = 1;
    BITS_INTERRUPT_PIN55_PRIORITY    = 7; //highest
    BIT_INTERRUPT_PIN55_STATUS       = 0;

       
    
    while(true)
    {
        Nop();
    }
    
      
    return 0;
}


void __attribute__((interrupt)) _INT0Interrupt( void )               
{
    PIN_TURN_HIGH(3);
    __delay_ms(500);
    PIN_TURN_LOW(3); 
    
    BIT_INTERRUPT_PIN55_STATUS       = 0;
}

//Lets create a timer
void __attribute__((interrupt)) _NULLInterrupt( void )               
{
    //TO DO
}