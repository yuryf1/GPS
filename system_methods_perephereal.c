#include "system_methods_perephereal.h"

#include "registers.h"
#include "configuration.h"      //for delay
#include <libpic30.h> 





void __EnablePower()
{     
    SET_PIN_POWER_SUPPLY_OUTPUT;
    SET_PIN_POWER_SUPPLY_LOW;
//    PIN_INIT_OUTPUT(87);  
//    PIN_TURN_LOW(87);   
}


void __EnableModuleGPS()
{
    SET_PIN_GPS_SUPPLY_OUTPUT;
    SET_PIN_GPS_SUPPLY_LOW;   
//    PIN_INIT_OUTPUT(53);
//    PIN_TURN_LOW(53); 
}


void __EnableModuleGSM()
{
    SET_PIN_GSM_SUPPLY_OUTPUT;
    SET_PIN_GSM_SUPPLY_LOW; 
//    PIN_INIT_OUTPUT(1);  
//    PIN_TURN_LOW   (1);  

    SET_PIN_GSM_BUTTON_OUTPUT;
    //PIN_INIT_OUTPUT(14);     
    SET_PIN_GSM_BUTTON_HIGH;  
    //PIN_TURN_HIGH  (14);
    __delay_ms(1000);
    SET_PIN_GSM_BUTTON_LOW;
    //PIN_TURN_LOW(14);
}





