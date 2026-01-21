/**
 * @file pmm_example.c
 * @brief PMM (Power Management Module) peripheral example for MSP430G2xx
 *
 * This example demonstrates low power mode operations:
 * - Configure GPIO interrupt for wake-up
 * - Enter different low power modes
 * - Demonstrate wake-up from interrupt
 */

#include <msp430g2553.h>
#include "driverlib.h"

// Port 1 interrupt service routine
#pragma vector=PORT1_VECTOR
__interrupt void Port1_ISR(void)
{
    // Clear interrupt flag
    GPIO_clearInterrupt(GPIO_PORT_P1, GPIO_PIN3);

    // Toggle LED to show wake-up
    GPIO_toggleOutputOnPin(GPIO_PORT_P1, GPIO_PIN0);
}

void main(void)
{
    uint8_t lpmMode = 0;

    // Stop watchdog timer
    WDT_A_holdTimer();

    // Configure P1.0 as output (LED indicator)
    GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN0);

    // Configure P1.3 as input with pull-up and interrupt (Button)
    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P1, GPIO_PIN3);
    GPIO_selectInterruptEdge(GPIO_PORT_P1, GPIO_PIN3, GPIO_HIGH_TO_LOW_TRANSITION);
    GPIO_enableInterrupt(GPIO_PORT_P1, GPIO_PIN3);

    // Enable global interrupts
    __bis_SR_register(GIE);

    while(1)
    {
        // Indicate current LPM mode with LED pattern
        GPIO_setOutputHighOnPin(GPIO_PORT_P1, GPIO_PIN0);
        __delay_cycles(100000); // Short flash
        GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0);

        // Wait for button press to change modes
        __delay_cycles(500000); // ~0.5 second delay

        // Cycle through different low power modes
        switch(lpmMode)
        {
            case 0:
                // Enter LPM0: CPU off, all clocks on
                PMM_enterLPM0();
                break;

            case 1:
                // Enter LPM1: CPU off, MCLK off, SMCLK on, ACLK on
                PMM_enterLPM1();
                break;

            case 2:
                // Enter LPM2: CPU off, MCLK off, SMCLK off, ACLK on
                PMM_enterLPM2();
                break;

            case 3:
                // Enter LPM3: CPU off, MCLK off, SMCLK off, ACLK on (32kHz)
                PMM_enterLPM3();
                break;

            default:
                lpmMode = 0;
                continue;
        }

        // Code execution resumes here after wake-up from interrupt

        // Exit LPM (restore clocks and CPU)
        PMM_exitLPM();

        // Move to next LPM mode
        lpmMode = (lpmMode + 1) % 4;

        // Brief delay before next iteration
        __delay_cycles(100000);
    }
}