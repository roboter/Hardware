//*****************************************************************************
//
// pmm.h - Driver for the Power Management Module.
//
//*****************************************************************************

//*****************************************************************************
//
// pmm.h - Driver for the Power Management Module for MSP430G2xx family.
//
//*****************************************************************************

#ifndef __MSP430WARE_PMM_H__
#define __MSP430WARE_PMM_H__

#include "inc/hw_memmap.h"

#ifdef __MSP430_HAS_PMM__

#ifdef __cplusplus
extern "C"
{
#endif

//*****************************************************************************
//
// Prototypes for the APIs.
//
//*****************************************************************************

extern void PMM_enterLPM0(void);
extern void PMM_enterLPM1(void);
extern void PMM_enterLPM2(void);
extern void PMM_enterLPM3(void);
extern void PMM_enterLPM4(void);
extern void PMM_exitLPM(void);

#ifdef __cplusplus
}
#endif

#endif // __MSP430_HAS_PMM__

#endif // __MSP430WARE_PMM_H__