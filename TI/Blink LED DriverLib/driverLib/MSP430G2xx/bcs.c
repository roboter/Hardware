//*****************************************************************************
//
// bcs.c - Driver for the Basic Clock System Module for MSP430G2xx family.
//
//*****************************************************************************

#include "inc/hw_memmap.h"
#include "bcs.h"

#ifdef __MSP430_HAS_BC2__

#include <assert.h>

// Default DCO frequencies for range select values (approximate)
static const uint32_t DCO_FREQUENCIES[] = {
    100000,   // RSEL_0
    150000,   // RSEL_1
    200000,   // RSEL_2
    300000,   // RSEL_3
    400000,   // RSEL_4
    600000,   // RSEL_5
    800000,   // RSEL_6
    1200000,  // RSEL_7
    1600000,  // RSEL_8
    2000000,  // RSEL_9
    3000000,  // RSEL_10
    4000000,  // RSEL_11
    6000000,  // RSEL_12
    8000000,  // RSEL_13
    12000000, // RSEL_14
    16000000  // RSEL_15
};

void BCS_setupDCO(uint8_t dcoRange, uint8_t modulation)
{
    // Set DCO range in DCOCTL
    DCOCTL &= ~(DCO2 | DCO1 | DCO0);
    DCOCTL |= dcoRange & 0x07;  // Lower 3 bits for DCO range

    // Set modulation in BCSCTL1
    if(modulation == BCS_DCO_MODULATION_ENABLE) {
        BCSCTL1 |= DIVA_3;  // Enable modulation
    } else {
        BCSCTL1 &= ~DIVA_3;
    }
}

void BCS_setMCLKDivider(uint8_t divider)
{
    BCSCTL1 &= ~(DIVM0 | DIVM1);
    BCSCTL1 |= divider;
}

void BCS_setSMCLKDivider(uint8_t divider)
{
    BCSCTL1 &= ~(DIVS0 | DIVS1);
    BCSCTL1 |= (divider << 4);  // DIVS bits are in upper nibble
}

uint32_t BCS_getMCLKFrequency(void)
{
    uint8_t dcoRange = DCOCTL & (DCO2 | DCO1 | DCO0);
    uint8_t divider = (BCSCTL1 & (DIVM0 | DIVM1)) >> 4;

    uint32_t baseFreq = DCO_FREQUENCIES[dcoRange];
    return baseFreq >> divider;
}

uint32_t BCS_getSMCLKFrequency(void)
{
    uint8_t dcoRange = DCOCTL & (DCO2 | DCO1 | DCO0);
    uint8_t divider = (BCSCTL1 & (DIVS0 | DIVS1)) >> 4;

    uint32_t baseFreq = DCO_FREQUENCIES[dcoRange];
    return baseFreq >> divider;
}

uint32_t BCS_getACLKFrequency(void)
{
    // ACLK typically runs at 32.768 kHz from LFXT1
    return 32768;
}

#endif // __MSP430_HAS_BC2__