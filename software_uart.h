// that contents of this file are not included more than once.  
#ifndef XC_HEADER_TEMPLATE_H_SOFTWARE_UART
#define	XC_HEADER_TEMPLATE_H_SOFTWARE_UART

#include "pins.h"
#define INIT_GPS_RECIEVE  PIN_INIT_INPUT(55)
#define RX_GPS            PIN_GET_BIT(55)

typedef struct 
{
    const unsigned short length; 
    const char* pointer;     
} str_t;


typedef struct
{
  void     (*Send)    (char*);
  str_t (*Recieve) (void);
  void     (*Clear)   (str_t);  
} software_uart_t;


software_uart_t UART_Initialize( unsigned long baudRate, 
                                 unsigned long long fcy);


//Allocated bytes in a heap for every recieved message
#define BUFFERLENGTH 256    




#endif