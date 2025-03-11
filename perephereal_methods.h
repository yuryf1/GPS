#ifndef XC_HEADER_TEMPLATE_H_SYSTEM_METHODS_PEREPHEREAL
#define	XC_HEADER_TEMPLATE_H_SYSTEM_METHODS_PEREPHEREAL
 
#include "pins.h"


#define SET_PIN_POWER_SUPPLY_OUTPUT          PIN_INIT_OUTPUT(87)
#define SET_PIN_POWER_SUPPLY_INPUT           PIN_INIT_INPUT(87) 
#define SET_PIN_POWER_SUPPLY_LOW             PIN_TURN_LOW(87)
#define SET_PIN_POWER_SUPPLY_HIGH            PIN_TURN_HIGH(87)

#define SET_PIN_GPS_SUPPLY_OUTPUT            PIN_INIT_OUTPUT(53)
#define SET_PIN_GPS_SUPPLY_INPUT             PIN_INIT_INPUT(53)
#define SET_PIN_GPS_SUPPLY_LOW               PIN_TURN_LOW(53)
#define SET_PIN_GPS_SUPPLY_HIGH              PIN_TURN_HIGH(53)

#define SET_PIN_GSM_SUPPLY_OUTPUT            PIN_INIT_OUTPUT(1)
#define SET_PIN_GSM_SUPPLY_INPUT             PIN_INIT_INPUT(1)
#define SET_PIN_GSM_SUPPLY_LOW               PIN_TURN_LOW(1)
#define SET_PIN_GSM_SUPPLY_HIGH              PIN_TURN_HIGH(1)

#define SET_PIN_GSM_BUTTON_OUTPUT            PIN_INIT_OUTPUT(14)
#define SET_PIN_GSM_BUTTON_INPUT             PIN_INIT_INPUT(14)
#define SET_PIN_GSM_BUTTON_LOW               PIN_TURN_LOW(14)
#define SET_PIN_GSM_BUTTON_HIGH              PIN_TURN_HIGH(14)


//#include "registers.h"

//#define SET_PIN_POWER_SUPPLY_OUTPUT          BIT_PIN_87_IO = 0 
//#define SET_PIN_POWER_SUPPLY_INPUT           BIT_PIN_87_IO = 1 
//#define SET_PIN_POWER_SUPPLY_LOW             BIT_PIN_87_SWITCH = 0
//#define SET_PIN_POWER_SUPPLY_HIGH            BIT_PIN_87_SWITCH = 1
//
//#define SET_PIN_GPS_SUPPLY_OUTPUT            BIT_PIN_53_IO = 0
//#define SET_PIN_GPS_SUPPLY_INPUT             BIT_PIN_53_IO = 1
//#define SET_PIN_GPS_SUPPLY_LOW               BIT_PIN_53_SWITCH = 0
//#define SET_PIN_GPS_SUPPLY_HIGH              BIT_PIN_53_SWITCH = 1
//
//#define SET_PIN_GSM_SUPPLY_OUTPUT            BIT_PIN_1_IO = 0
//#define SET_PIN_GSM_SUPPLY_INPUT             BIT_PIN_1_IO = 1
//#define SET_PIN_GSM_SUPPLY_LOW               BIT_PIN_1_SWITCH = 0
//#define SET_PIN_GSM_SUPPLY_HIGH              BIT_PIN_1_SWITCH = 1
//
//#define SET_PIN_GSM_BUTTON_OUTPUT            BIT_PIN_14_IO = 0
//#define SET_PIN_GSM_BUTTON_INPUT             BIT_PIN_14_IO = 1
//#define SET_PIN_GSM_BUTTON_LOW               BIT_PIN_14_SWITCH = 0
//#define SET_PIN_GSM_BUTTON_HIGH              BIT_PIN_14_SWITCH = 1


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

