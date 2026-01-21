//*****************************************************************************
//
// usci_a_spi.c - Driver for the USCI_A SPI Module.
//
//*****************************************************************************

#include <msp430g2553.h>
#include "usci_a_spi.h"

// HWREG16 macro definition
#ifndef HWREG16
#define HWREG16(x)     (*((volatile uint16_t *)(x)))
#endif
#ifndef HWREG8
#define HWREG8(x)      (*((volatile uint8_t *)(x)))
#endif

void USCI_A_SPI_init(uint16_t baseAddress, uint8_t selectClockSource,
                    uint16_t clockSourceFrequency, uint16_t desiredSpiClock,
                    uint8_t msbFirst, uint8_t clockPhase, uint8_t clockPolarity) {
    HWREG16(baseAddress + 0x00) |= 0x0080; // Set UCSWRST
    // Configure UCAxCTL0
    HWREG8(baseAddress + 0x01) = msbFirst | clockPhase | clockPolarity;
    // Configure UCAxCTL1
    HWREG8(baseAddress + 0x00) = selectClockSource;
    // Set baud rate (simplified)
    HWREG16(baseAddress + 0x06) = (uint16_t)(clockSourceFrequency / desiredSpiClock);
    HWREG16(baseAddress + 0x00) &= ~0x0080; // Clear UCSWRST
}

void USCI_A_SPI_enable(uint16_t baseAddress) {
    HWREG16(baseAddress + 0x00) &= ~0x0080; // Clear UCSWRST
}

void USCI_A_SPI_disable(uint16_t baseAddress) {
    HWREG16(baseAddress + 0x00) |= 0x0080; // Set UCSWRST
}

uint8_t USCI_A_SPI_queryStatusFlags(uint16_t baseAddress, uint8_t mask) {
    return HWREG8(baseAddress + 0x02) & mask; // UCAxSTAT
}