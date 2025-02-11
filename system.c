#include "system.h"

#include "system_methods_pll.h"


double CalculateError(double multiply, 
                      unsigned short M, 
                      unsigned short N1,
                      unsigned short N2)
{
    double realMultiply =  ((double)M) / (  ((double)N1) * ((double)N2) );
    double error = realMultiply - multiply;
    
    //to absolute...
    return (error > 0)? error : -error;
}

void EnablePLL(unsigned long long freqIn, unsigned long long freqOut)
{ 
    double multiplier = ((double)freqOut) / ((double)freqIn);
    
    unsigned short calculatedM, calculatedN1, calculatedN2;
    
    double currentError = 88.8;
    double calculatedError = 99.9;
    
    for (unsigned short m = Mmin; m <= Mmax; m++)
    {
        for (unsigned short n1 = N1min; n1 <= N1max; n1++)
        {
            for (unsigned short iN2 = 0; iN2 < ( sizeof(N2all) / sizeof(N2all[0]) ); iN2++)
            {
                calculatedError = CalculateError(multiplier, m, n1, N2all[iN2]);
                
                if(calculatedError < currentError)
                {
                    currentError = calculatedError;
                    
                    calculatedM  = m;
                    calculatedN1 = n1;
                    calculatedN2 = N2all[iN2];
                }
                else
                {
                    //Do nothing
                }
            }
        }
    }
    
    
    // N1 = 2  => 10 MHz / 2 = 5 MHz
    __SetPLLPRE(calculatedN1 - 2);
    //__SetPLLPRE(0);
    
    // M  = 32 => 5 MHz * 32 = 160 MHz
    __SetPLLDIV(calculatedM - 2);
    //__SetPLLDIV(0x1E);
    
    // N2 = 2  => 160 MHz / 2 = 80 MHz (40 MIPS)
    __SetPLLPOST(calculatedN2 - 2);
    //__SetPLLPOST(0);
   
    //Migrate to other method
    __DisableWatchdog();
    
    while(__IsPllReady() == false) {};      
}



void EnablePerepherial()
{    
    //For manage M1 (main power supply) transistor 
    PIN_INIT_OUTPUT(87);  
    PIN_TURN_LOW(87);       
    
     //For manage M12 (GSM module power supply) transistor
    PIN_INIT_OUTPUT(1);
    PIN_TURN_LOW(1); 
    
    //For turn on GSM module
    PIN_INIT_OUTPUT(14);   
    PIN_TURN_HIGH(14);     
    __delay_ms(1000);
    PIN_TURN_LOW(14);
    
    //For manage M13 (GPS module power supply) transistor
    PIN_INIT_OUTPUT(53);
    PIN_TURN_LOW(53); 
      
//    Nop();
//    //M2 transistor
//    _TRISF1 = 0;
//    _RF1 = 0; 
//    
//    Nop();
//    //M3 transistor
//    //Configure RG0(pin90) to digital output
//    _TRISG0 = 0;
//    //pin90 close M3 transistor
//    _RG0 = 0;     
}