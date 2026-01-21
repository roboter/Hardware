//*****************************************************************************
//
// wdt_a.h - Driver for the WDT_A Module for MSP430G2xx family.
//
//*****************************************************************************

#ifndef __MSP430WARE_WDT_A_H__
#define __MSP430WARE_WDT_A_H__

#include "inc/hw_memmap.h"

#ifdef __MSP430_HAS_WDT__

#ifdef __cplusplus
extern "C"
{
#endif

//*****************************************************************************
//
// Prototypes for the APIs.
//
//*****************************************************************************

extern void WDT_A_holdTimer(void);
extern void WDT_A_startTimer(void);
extern void WDT_A_clearTimer(void);

#ifdef __cplusplus
}
#endif

#endif // __MSP430_HAS_WDT__

#endif // __MSP430WARE_WDT_A_H__