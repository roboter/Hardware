//*****************************************************************************
//
// flashctl.c - Driver for the Flash Controller Module.
//
//*****************************************************************************

#include <msp430g2553.h>
#include "flashctl.h"

// HWREG16 macro definition
#ifndef HWREG16
#define HWREG16(x)     (*((volatile uint16_t *)(x)))
#endif
#ifndef HWREG8
#define HWREG8(x)      (*((volatile uint8_t *)(x)))
#endif

void FlashCtl_eraseSegment(uint16_t *flashAddress) {
    HWREG16(0x0128) = 0xA500 | 0x0002; // FCTL1 - ERASE + MERAS
    *flashAddress = 0x0000; // Dummy write to start erase
    while (HWREG16(0x012A) & 0x8000); // Wait for erase completion
}

void FlashCtl_writeByte(uint16_t *flashAddress, uint8_t data) {
    HWREG16(0x0128) = 0xA500 | 0x0001; // FCTL1 - WRT
    *flashAddress = data;
    while (HWREG16(0x012A) & 0x8000); // Wait for write completion
}

void FlashCtl_writeWord(uint16_t *flashAddress, uint16_t data) {
    HWREG16(0x0128) = 0xA500 | 0x0001; // FCTL1 - WRT
    *flashAddress = data;
    while (HWREG16(0x012A) & 0x8000); // Wait for write completion
}

uint8_t FlashCtl_getStatus(void) {
    return HWREG16(0x012A) & 0x0003; // FCTL3 status bits
}