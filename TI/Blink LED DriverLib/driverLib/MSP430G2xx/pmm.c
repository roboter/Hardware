//*****************************************************************************
//
// pmm.c - Driver for the Power Management Module for MSP430G2xx family.
//
//*****************************************************************************

#include "inc/hw_memmap.h"
#include "pmm.h"

#ifdef __MSP430_HAS_PMM__

#include <assert.h>

// Low power mode defines for MSP430G2xx
#define LPM0_BITS    (CPUOFF)
#define LPM1_BITS    (CPUOFF | SCG0)
#define LPM2_BITS    (CPUOFF | SCG1)
#define LPM3_BITS    (CPUOFF | SCG1 | SCG0)
#define LPM4_BITS    (CPUOFF | SCG1 | SCG0 | OSCOFF)

void PMM_enterLPM0(void)
{
    __bis_SR_register(LPM0_BITS | GIE);
}

void PMM_enterLPM1(void)
{
    __bis_SR_register(LPM1_BITS | GIE);
}

void PMM_enterLPM2(void)
{
    __bis_SR_register(LPM2_BITS | GIE);
}

void PMM_enterLPM3(void)
{
    __bis_SR_register(LPM3_BITS | GIE);
}

void PMM_enterLPM4(void)
{
    __bis_SR_register(LPM4_BITS | GIE);
}

void PMM_exitLPM(void)
{
    __bic_SR_register_on_exit(LPM4_BITS);
}

#endif // __MSP430_HAS_PMM__