#include "system_methods_perephereal.h"

#include "pins.h"
#include "configuration.h"
#include <libpic30.h> 
#include <stdbool.h>            // true/false


void __EnablePower()
{    
    PinInitOutput(PIN_POWER_SUPPLY);
    
    PIN_INIT_OUTPUT(87);  
    PIN_TURN_LOW(87);   
}


void __EnableModuleGPS()
{
    PIN_INIT_OUTPUT(53);
    PIN_TURN_LOW(53); 
}


void __EnableModuleGSM()
{
    PIN_INIT_OUTPUT(1);  
    PIN_TURN_LOW   (1);  

    PIN_INIT_OUTPUT(14);   
    PIN_TURN_HIGH  (14);     
    __delay_ms(1000);
    PIN_TURN_LOW(14);
}





