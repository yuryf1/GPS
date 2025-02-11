#include "system_methods_pll.h"

#include "registers.h"
#include <stdbool.h>            // true/false



void __SetPLLPRE(unsigned short pre)
{
    BITS_SYSTEM_PLLPRE  = pre;
}

void __SetPLLDIV(unsigned short div)
{
    BITS_SYSTEM_PLLDIV = div;
}

void __SetPLLPOST(unsigned short post)
{
    BITS_SYSTEM_PLLPOST = post;
}

void __EnableWatchdog()
{
    BIT_SYSTEM_WATCHDOG = 1;
}

void __DisableWatchdog()
{
    BIT_SYSTEM_WATCHDOG = 0;
}

bool __IsPllReady()
{
    return (BIT_SYSTEM_PLL_READY == 1)? true : false;
}





