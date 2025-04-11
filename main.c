#include "configuration.h"
#include "system.h"               // EnablePLL(FINPUT,FOSC);
#include "perephereal_methods.h"  // EnablePerephereal();EnableModuleGPS();EnableModuleGSM();

#include <libpic30.h>           // delay32() and others
#include <stdbool.h>            // true/false
#include <stdio.h>
#include <string.h>

#include "software_uart.h"

char response[BUFFERLENGTH];
char response2[BUFFERLENGTH];
char response3[BUFFERLENGTH];
char response4[BUFFERLENGTH];
char response5[BUFFERLENGTH];
#define DELAY 
//#define DELAY __delay_ms(1500)
int main(void) {
   
    EnablePLL(FINPUT,FOSC);
    EnablePerepherealPower();
    EnableModuleGPS();
    //EnableModuleGSM();
       
    PIN_INIT_OUTPUT(3);
    PIN_TURN_HIGH(3);
    __delay_ms(9000);
    PIN_TURN_LOW(3);
        
    software_uart_t gps = Software_UART(uart1, GPS_BAUDRATE, FCY);
    
    str_t gpsString = gps.Recieve();
    strncpy(response, gpsString.pointer, gpsString.length);
    gps.Clear(&gpsString);

    DELAY; 
    
    str_t gpsString2 = gps.Recieve();
    strncpy(response2, gpsString2.pointer, gpsString2.length);
    gps.Clear(&gpsString);
    
    DELAY; 
    
    str_t gpsString3 = gps.Recieve();
    strncpy(response3, gpsString3.pointer, gpsString3.length);
    gps.Clear(&gpsString);
    
    DELAY; 
    
    str_t gpsString4 = gps.Recieve();
    strncpy(response4, gpsString4.pointer, gpsString4.length);
    gps.Clear(&gpsString);
    
    DELAY; 
    
    str_t gpsString5 = gps.Recieve();
    strncpy(response5, gpsString5.pointer, gpsString5.length);
    gps.Clear(&gpsString);
    
    Nop();
    Nop();
    Nop();
    Nop();

    while(true)
    {
        //Nop();
    }
    

    
       
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