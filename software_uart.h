#ifndef XC_HEADER_TEMPLATE_H_SOFTWARE_UART
#define	XC_HEADER_TEMPLATE_H_SOFTWARE_UART


                             #include "pins.h"
#define SOFTWARE_UART1_INIT  PIN_INIT_INPUT(55)
#define SOFTWARE_UART1_READ  PIN_GET_BIT(55)
#define SOFTWARE_UART1_BUFF  100      //Allocated bytes in a heap for every recieved message
#define SOFTWARE_UART1_WAIT  2000ULL  //Miliseconds (integer))

#define SOFTWARE_UART2_INIT  
#define SOFTWARE_UART2_READ 
#define SOFTWARE_UART2_BUFF  256      //Allocated bytes in a heap for every recieved message
#define SOFTWARE_UART2_WAIT  20000ULL //Miliseconds (integer))



typedef enum {
    uart1 = 1, 
    uart2 = 2
    //, invalidFirst = 0, first = uart1, last = uart2
} 
uartPort_e;


typedef struct {
    unsigned short length; 
    char* pointer;     
}
str_t;


typedef struct {
  //void     (*Send)    (char*);
  str_t    (*Recieve) (void);
  void     (*Clear)   (void);  
} 
software_uart_t;


software_uart_t Software_UART(const uartPort_e port,
                              const unsigned long baudRate, 
                              const unsigned long long fcy);


#endif