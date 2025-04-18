#include "configuration.h"
#include "system.h"               // EnablePLL(FINPUT,FOSC);
#include "perephereal_methods.h"  // EnablePerephereal();EnableModuleGPS();EnableModuleGSM();

#include <libpic30.h>           // delay32() and others
#include <stdbool.h>            // true/false
#include <stdio.h>
#include <string.h>

#include "software_uart.h"


// 1)
// 10.2. +CGACT Command: PDP Context Activate or Deactivate


char message[SOFTWARE_UART1_BUFF];

int main(void) {
   
    EnablePLL(FINPUT,FOSC);
    EnablePerepherealPower();
    EnableModuleGPS();
    //EnableModuleGSM();
       
    __delay_ms(8000);
    
    software_uart_t gps = Software_UART(uart1, GPS_BAUDRATE, FCY);
    
    const char ggaProtocolHeader[] = "$GPRMC";
    str_t location;
    char * match = NULL;
    
    
    for(unsigned short i = 0; i < 10;)
    {
        location = gps.Recieve();
        match = strstr(location.pointer, ggaProtocolHeader);
        
        if(match)
        {
            strcpy(message, location.pointer);
            i++;
        }
        
        gps.Clear();
    }
    
    Nop();
    Nop();
    Nop();
    Nop();
     
    return 0;
}


// External interrupt working code
//    BITS_INTERRUPT_CPU_PRIORITY      = 0; //lowest
//    BIT_INTERRUPT_NESTING_DISABLE    = 0;
//    BIT_INTERRUPT_PIN55_ENABLE       = 1;
//    BITS_INTERRUPT_PIN55_PRIORITY    = 7; //highest
//    BIT_INTERRUPT_PIN55_STATUS       = 0;
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