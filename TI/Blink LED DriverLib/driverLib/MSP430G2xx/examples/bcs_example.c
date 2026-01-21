/**
 * @file bcs_example.c
 * @brief BCS (Basic Clock System) peripheral example for MSP430G2xx
 *
 * This example demonstrates clock system configuration:
 * - Configure DCO for different frequencies
 * - Set up clock dividers for MCLK and SMCLK
 * - Demonstrate frequency changes
 */

#include <msp430g2553.h>
#include "driverlib.h"

#define DCO_RANGES 8
const uint8_t dcoRanges[DCO_RANGES] = {
    BCS_DCO_RSEL_7,   // ~1.2MHz
    BCS_DCO_RSEL_13,  // ~8MHz
    BCS_DCO_RSEL_14,  // ~12MHz
    BCS_DCO_RSEL_15,  // ~16MHz
    BCS_DCO_RSEL_15,  // ~16MHz (with divider)
    BCS_DCO_RSEL_14,  // ~12MHz
    BCS_DCO_RSEL_13,  // ~8MHz
    BCS_DCO_RSEL_7    // ~1.2MHz
};

const uint8_t mclkDividers[DCO_RANGES] = {
    BCS_MCLK_DIVIDER_1,  // /1
    BCS_MCLK_DIVIDER_1,  // /1
    BCS_MCLK_DIVIDER_1,  // /1
    BCS_MCLK_DIVIDER_1,  // /1
    BCS_MCLK_DIVIDER_2,  // /2 (8MHz)
    BCS_MCLK_DIVIDER_1,  // /1
    BCS_MCLK_DIVIDER_1,  // /1
    BCS_MCLK_DIVIDER_1   // /1
};

void main(void)
{
    uint8_t rangeIndex = 0;

    // Stop watchdog timer
    WDT_A_holdTimer();

    // Configure P1.0 as output (activity indicator)
    GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN0);

    // Configure P1.6 as output (frequency indicator)
    GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN6);

    while(1)
    {
        // Indicate start of frequency change
        GPIO_setOutputHighOnPin(GPIO_PORT_P1, GPIO_PIN0);

        // Configure DCO frequency range
        BCS_setupDCO(dcoRanges[rangeIndex], BCS_DCO_MODULATION_DISABLE);

        // Configure MCLK divider
        BCS_setMCLKDivider(mclkDividers[rangeIndex]);

        // Configure SMCLK divider (fixed at /8 for consistent timing)
        BCS_setSMCLKDivider(BCS_SMCLK_DIVIDER_8);

        // Indicate frequency change complete
        GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0);

        // Blink LED at different rates based on frequency
        // Higher frequency = faster blinking
        GPIO_toggleOutputOnPin(GPIO_PORT_P1, GPIO_PIN6);

        // Delay proportional to frequency (higher frequency = shorter delay)
        // This creates a visual indication of the frequency changes
        uint32_t delay = 50000; // Base delay
        if(rangeIndex < 4) {
            delay = delay >> rangeIndex; // Shorter delay for higher frequencies
        } else {
            delay = delay >> (7 - rangeIndex); // Longer delay for lower frequencies
        }
        __delay_cycles(delay);

        // Move to next frequency range
        rangeIndex = (rangeIndex + 1) % DCO_RANGES;
    }
}