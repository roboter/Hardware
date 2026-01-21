/**
 * @file wdt_a_example.c
 * @brief WDT_A (Watchdog Timer) peripheral example for MSP430G2xx
 *
 * This example demonstrates watchdog timer operations:
 * - Configure watchdog timer intervals
 * - Feed the watchdog to prevent reset
 * - Demonstrate watchdog timeout reset
 */

#include <msp430g2553.h>
#include "driverlib.h"

// Watchdog interrupt service routine
#pragma vector=WDT_VECTOR
__interrupt void WDT_ISR(void)
{
    // Toggle LED to show watchdog interrupt
    GPIO_toggleOutputOnPin(GPIO_PORT_P1, GPIO_PIN6);
}

void main(void)
{
    uint8_t mode = 0;
    uint32_t delayCount = 0;

    // Initially hold watchdog timer
    WDT_A_holdTimer();

    // Configure LEDs
    GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN0); // Mode indicator
    GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN6); // Watchdog activity

    // Configure P1.3 as input (button to change modes)
    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P1, GPIO_PIN3);

    while(1)
    {
        switch(mode)
        {
            case 0:
                // Mode 0: Watchdog disabled (hold timer)
                GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0);
                WDT_A_holdTimer();

                // Check for button press to change mode
                if(GPIO_getInputPinValue(GPIO_PORT_P1, GPIO_PIN3) == 0)
                {
                    mode = 1;
                    __delay_cycles(10000); // Debounce
                }
                break;

            case 1:
                // Mode 1: Watchdog enabled with feeding
                GPIO_setOutputHighOnPin(GPIO_PORT_P1, GPIO_PIN0);
                WDT_A_startTimer();

                // Feed the watchdog regularly to prevent reset
                delayCount = 0;
                while(delayCount < 100000)
                {
                    if(delayCount % 10000 == 0)
                    {
                        WDT_A_clearTimer(); // Feed watchdog
                        GPIO_toggleOutputOnPin(GPIO_PORT_P1, GPIO_PIN6);
                    }
                    delayCount++;
                    __delay_cycles(1);
                }

                // Check for button press to change mode
                if(GPIO_getInputPinValue(GPIO_PORT_P1, GPIO_PIN3) == 0)
                {
                    mode = 2;
                    WDT_A_holdTimer(); // Hold timer before changing mode
                    __delay_cycles(10000); // Debounce
                }
                break;

            case 2:
                // Mode 2: Watchdog enabled without feeding (will reset)
                GPIO_setOutputHighOnPin(GPIO_PORT_P1, GPIO_PIN0);
                GPIO_setOutputHighOnPin(GPIO_PORT_P1, GPIO_PIN6); // Solid on

                WDT_A_startTimer();

                // Don't feed the watchdog - it will timeout and reset the device
                // The device will reset before reaching this point
                __delay_cycles(2000000); // Long delay - watchdog will timeout

                // This code should never be reached
                mode = 0;
                break;

            default:
                mode = 0;
                break;
        }

        __delay_cycles(10000); // Small delay between iterations
    }
}