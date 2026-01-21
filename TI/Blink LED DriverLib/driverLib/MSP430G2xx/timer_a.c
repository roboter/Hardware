//*****************************************************************************
//
// timer_a.c - Driver for the Timer_A Module.
//
//*****************************************************************************

#include <msp430g2553.h>
#include "timer_a.h"

// HWREG16 macro definition
#ifndef HWREG16
#define HWREG16(x)     (*((volatile uint16_t *)(x)))
#endif

void Timer_A_startCounter(uint16_t baseAddress, uint16_t timerMode) {
    HWREG16(baseAddress + 0x00) |= timerMode; // TACTL
}

void Timer_A_stopTimer(uint16_t baseAddress) {
    HWREG16(baseAddress + 0x00) &= ~(0x0030); // Clear MC bits in TACTL
}

void Timer_A_clearTimerInterrupt(uint16_t baseAddress) {
    HWREG16(baseAddress + 0x02) &= ~0x0001; // Clear TAIFG in TAIV
}

uint16_t Timer_A_getInterruptStatus(uint16_t baseAddress) {
    return HWREG16(baseAddress + 0x02) & 0x000F; // Return TAIV
}

void Timer_A_enableInterrupt(uint16_t baseAddress) {
    HWREG16(baseAddress + 0x00) |= 0x0002; // Set TAIE in TACTL
}

void Timer_A_disableInterrupt(uint16_t baseAddress) {
    HWREG16(baseAddress + 0x00) &= ~0x0002; // Clear TAIE in TACTL
}