#include "system.h"

#include "system_methods.h"


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


//void EnablePLL()
//{ 
//    //10MHz to 80MHz scaling
//    
//    // N1 = 2  => 10 MHz / 2 = 5 MHz
//    __SetPLLPRE(0);
//    
//    // M  = 32 => 5 MHz * 32 = 160 MHz
//    __SetPLLDIV(0x1E);
//    
//    // N2 = 2  => 160 MHz / 2 = 80 MHz (40 MIPS)
//    __SetPLLPOST(0);
//   
//    //Migrate to other method
//    __DisableWatchdog();
//    
//    while(__IsPllReady() == false) {};      
//}