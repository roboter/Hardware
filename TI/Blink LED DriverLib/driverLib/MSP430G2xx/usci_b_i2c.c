//*****************************************************************************
//
// usci_b_i2c.c - Driver for the USCI_B I2C Module.
//
//*****************************************************************************

#include <msp430g2553.h>
#include "usci_b_i2c.h"

// HWREG16 macro definition
#ifndef HWREG16
#define HWREG16(x)     (*((volatile uint16_t *)(x)))
#endif
#ifndef HWREG8
#define HWREG8(x)      (*((volatile uint8_t *)(x)))
#endif

void USCI_B_I2C_init(uint16_t baseAddress, uint8_t selectClockSource,
                    uint16_t clockSourceFrequency, uint16_t dataRate) {
    HWREG16(baseAddress + 0x00) |= 0x0080; // Set UCSWRST
    // Configure UCBxCTL0
    HWREG8(baseAddress + 0x01) = 0x0F; // I2C mode
    // Configure UCBxCTL1
    HWREG8(baseAddress + 0x00) = selectClockSource | 0x80; // Master mode
    // Set baud rate (simplified)
    HWREG16(baseAddress + 0x06) = (uint16_t)(clockSourceFrequency / 100000); // 100kHz default
    HWREG16(baseAddress + 0x00) &= ~0x0080; // Clear UCSWRST
}

void USCI_B_I2C_enable(uint16_t baseAddress) {
    HWREG16(baseAddress + 0x00) &= ~0x0080; // Clear UCSWRST
}

void USCI_B_I2C_disable(uint16_t baseAddress) {
    HWREG16(baseAddress + 0x00) |= 0x0080; // Set UCSWRST
}

void USCI_B_I2C_setSlaveAddress(uint16_t baseAddress, uint8_t slaveAddress) {
    HWREG16(baseAddress + 0x10) = slaveAddress; // UCBxI2CSA
}

uint8_t USCI_B_I2C_getInterruptStatus(uint16_t baseAddress, uint8_t mask) {
    return HWREG8(baseAddress + 0x1C) & mask; // UCBxIFG
}