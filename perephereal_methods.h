#ifndef XC_HEADER_TEMPLATE_H_SYSTEM_METHODS_PEREPHEREAL
#define	XC_HEADER_TEMPLATE_H_SYSTEM_METHODS_PEREPHEREAL
 

#include "registers.h"

#define SET_PIN_POWER_SUPPLY_OUTPUT          BIT_PIN_87_IO = 0 
#define SET_PIN_POWER_SUPPLY_INPUT           BIT_PIN_87_IO = 1 
#define SET_PIN_POWER_SUPPLY_LOW             BIT_PIN_87_SWITCH = 0
#define SET_PIN_POWER_SUPPLY_HIGH            BIT_PIN_87_SWITCH = 1

#define SET_PIN_GPS_SUPPLY_OUTPUT            BIT_PIN_53_IO = 0
#define SET_PIN_GPS_SUPPLY_INPUT             BIT_PIN_53_IO = 1
#define SET_PIN_GPS_SUPPLY_LOW               BIT_PIN_53_SWITCH = 0
#define SET_PIN_GPS_SUPPLY_HIGH              BIT_PIN_53_SWITCH = 1

#define SET_PIN_GSM_SUPPLY_OUTPUT            BIT_PIN_1_IO = 0
#define SET_PIN_GSM_SUPPLY_INPUT             BIT_PIN_1_IO = 1
#define SET_PIN_GSM_SUPPLY_LOW               BIT_PIN_1_SWITCH = 0
#define SET_PIN_GSM_SUPPLY_HIGH              BIT_PIN_1_SWITCH = 1

#define SET_PIN_GSM_BUTTON_OUTPUT            BIT_PIN_14_IO = 0
#define SET_PIN_GSM_BUTTON_INPUT             BIT_PIN_14_IO = 1
#define SET_PIN_GSM_BUTTON_LOW               BIT_PIN_14_SWITCH = 0
#define SET_PIN_GSM_BUTTON_HIGH              BIT_PIN_14_SWITCH = 1


void EnablePerepherealPower();
void DisablePerepherealPower();

void EnableModuleGPS();
void DisableModuleGPS();

void EnableModuleGSM();
void DisableModuleGSM();





//    //M2 transistor
//    _TRISF1 = 0;
//    _RF1 = 0; 
//    

//    //M3 transistor
//    //Configure RG0(pin90) to digital output
//    _TRISG0 = 0;
//    //pin90 close M3 transistor
//    _RG0 = 0; 



#endif	/* XC_HEADER_TEMPLATE_H */

