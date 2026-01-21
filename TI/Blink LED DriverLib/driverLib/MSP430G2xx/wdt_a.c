//*****************************************************************************
//
// wdt_a.c - Driver for the WDT_A Module for MSP430G2xx family.
//
//*****************************************************************************

#include "inc/hw_memmap.h"
#include "wdt_a.h"

#ifdef __MSP430_HAS_WDT__

#include <assert.h>

void WDT_A_holdTimer(void)
{
    WDTCTL = WDTPW | WDTHOLD;
}

void WDT_A_startTimer(void)
{
    WDTCTL = WDTPW;
}

void WDT_A_clearTimer(void)
{
    WDTCTL |= WDTPW | WDTCNTCL;
}

#endif // __MSP430_HAS_WDT__