#ifndef XC_HEADER_TEMPLATE_H_PINS
#define	XC_HEADER_TEMPLATE_H_PINS

#include "registers.h"


#define PIN_POWER_SUPPLY      87
#define PIN_GPS_SUPPLY        53
#define PIN_GSM_SUPPLY        1
#define PIN_GSM_STARTUP       14
#define GSM_PRESS_TIME_MS     1000


#define PIN_INIT_INPUT(NUMBER)  BIT_PIN_ ## NUMBER ## _IO = 1
#define PIN_INIT_OUTPUT(NUMBER) BIT_PIN_ ## NUMBER ## _IO = 0
#define PIN_TURN_HIGH(NUMBER)   BIT_PIN_ ## NUMBER ## _SWITCH = 1 
#define PIN_TURN_LOW(NUMBER)    BIT_PIN_ ## NUMBER ## _SWITCH = 0 
#define PIN_GET_BIT(NUMBER)     BIT_PIN_ ## NUMBER ## _SWITCH


#define MY_INSTRUCTION(COMMAND) COMMAND ## = 0


void PinInitOutput(unsigned short pinNumber);



#endif	/* XC_HEADER_TEMPLATE_H */

