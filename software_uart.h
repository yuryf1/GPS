#ifndef XC_HEADER_TEMPLATE_H_SOFTWARE_UART
#define	XC_HEADER_TEMPLATE_H_SOFTWARE_UART

#include "pins.h"
#define SOFTWARE_UART1_INIT  PIN_INIT_INPUT(55)
#define SOFTWARE_UART1_READ  PIN_GET_BIT(55)
#define SOFTWARE_UART1_WAIT  2 //seconds (integer))
#define SOFTWARE_UART2_INIT  
#define SOFTWARE_UART2_READ 
#define SOFTWARE_UART2_WAIT  //seconds (integer))

//Allocated bytes in a heap for every recieved message
#define BUFFERLENGTH 100  

typedef enum {
    uart1 = 1, 
    uart2 = 2
    //, invalidFirst = 0, first = uart1, last = uart2
} 
uartPort_e;


typedef struct {
    const unsigned short length; 
    const char* pointer;     
}
str_t;


typedef struct {
  //void     (*Send)    (char*);
  str_t    (*Recieve) (void);
  void     (*Clear)   (str_t*);  
} 
software_uart_t;


software_uart_t Software_UART(uartPort_e port,
                              unsigned long baudRate, 
                              unsigned long long fcy);


#endif