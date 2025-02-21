#include "perephereal_methods.h"

#include "configuration.h"            //for delay
#include <libpic30.h> 


void EnablePerepherealPower()
{     
    SET_PIN_POWER_SUPPLY_OUTPUT;     //PIN_INIT_OUTPUT(87); 
    SET_PIN_POWER_SUPPLY_LOW;        //PIN_TURN_LOW(87); 
}

void DisablePerepherealPower()
{
    SET_PIN_POWER_SUPPLY_HIGH;
    SET_PIN_POWER_SUPPLY_INPUT;
}


void EnableModuleGPS()
{
    SET_PIN_GPS_SUPPLY_OUTPUT;       //PIN_INIT_OUTPUT(53);
    SET_PIN_GPS_SUPPLY_LOW;          //PIN_TURN_LOW(53);   
}

void DisableModuleGPS()
{
    SET_PIN_GPS_SUPPLY_HIGH; 
    SET_PIN_GPS_SUPPLY_INPUT;                  
}


void EnableModuleGSM()
{
    SET_PIN_GSM_SUPPLY_OUTPUT;       //PIN_INIT_OUTPUT(1); 
    SET_PIN_GSM_SUPPLY_LOW;          //PIN_TURN_LOW(1);  

    SET_PIN_GSM_BUTTON_OUTPUT;       //PIN_INIT_OUTPUT(14);     
    SET_PIN_GSM_BUTTON_HIGH;         //PIN_TURN_HIGH (14);
    __delay_ms(1000);
    SET_PIN_GSM_BUTTON_LOW;          //PIN_TURN_LOW(14);
}

void DisableModuleGSM()
{
    SET_PIN_GSM_SUPPLY_HIGH; 
    SET_PIN_GSM_SUPPLY_INPUT;       
              
}





