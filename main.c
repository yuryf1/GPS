#define FINPUT 10000000ULL      // 10 MHz oscillator
#define FOSC 80000000ULL        // x8 and x6 PLL devides work good
#define FCY FOSC/2              // device instruction clock for delay_ms() and more

#include <xc.h>                 // mcu registers

#include <libpic30.h>           // delay32() and others
#include <stdbool.h>            // true/false
#include <string.h>
#include "system.h"
#include "pins.h"
#include "registers.h"
#include <stdlib.h>             // calloc   

void __attribute__((interrupt)) _INT0Interrupt( void )               
{
    PORTEbits.RE5              = 1;
    Nop();
    
    IFS0bits.INT0IF            = 0;
}


int main(void) {
      
    //Disable watchdog
    RCONbits.SWDTEN            = 0;
    
    //Set CPU prioritets to 0        
    SRbits.IPL                 = 0;
    //Enable prioritets for interrupts
    INTCON1bits.NSTDIS         = 0;
    //Turn on INT0 Interrupt
    IEC0bits.INT0IE            = 1;
    //Set highest prioritet for INT0        
    IPC0bits.INT0IP = 7;
    //Clear the flag (I dont kwoun why)))
    IFS0bits.INT0IF            = 0;

      
    TRISEbits.TRISE5           = 0; 
    TRISFbits.TRISF6           = 1;  
    PORTEbits.RE5              = 0;
    PORTFbits.RF6              = 0;
       
    
    while(1)
    {
        Nop();
    }
    
      
    return 0;
}

