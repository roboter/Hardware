//*****************************************************************************
//
// wdt_a.c - Driver for the WDT_A Module for MSP430G2xx family.
//
//*****************************************************************************

#include <msp430g2553.h>
#include "wdt_a.h"

//*****************************************************************************
//
//! Holds the WDT.
//!
//! This function holds the WDT.
//!
//! \return None
//
//*****************************************************************************
void WDT_A_holdTimer(void)
{
    // Stop watchdog timer using inline assembly
    __asm(" MOV.W #0x5A80, &0x0120 ");
}