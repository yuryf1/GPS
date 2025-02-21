  
#ifndef XC_HEADER_TEMPLATE_H_SYSTEM_METHODS_PLL
#define	XC_HEADER_TEMPLATE_H_SYSTEM_METHODS_PLL
  
#include <stdbool.h>                       // true/false


//PLLPRE<4:0>: PLL Phase Detector Input Divider bits 
//(also denoted as ?N1?, PLL prescaler)
//00000 = Input/2 (default)
//00001 = Input/3
//11111 = Input/33
void __SetPLLPRE(unsigned short pre);

//PLLDIV<8:0>: PLL Feedback Divisor bits (also denoted as ?M?, PLL multiplier)
//000000000 = 2
//000000001 = 3
//000000010 = 4
//000110000 = 50 (default)
//111111111 = 513
void __SetPLLDIV(unsigned short div);

//PLLPOST<1:0>: PLL VCO Output Divider Select bits 
//(also denoted as ?N2?, PLL postscaler)
//00 = Output/2 
//01 = Output/4 (default) 
//10 = Reserved
//11 = Output/8 
void __SetPLLPOST(unsigned short post);

//SWDTEN: Software Enable/Disable of WDT bit
void __EnableWatchdog();
void __DisableWatchdog();

// LOCK: PLL Lock Status bit (read-only) 
bool __IsPllReady();




#endif	/* XC_HEADER_TEMPLATE_H */

