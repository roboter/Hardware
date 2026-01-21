/**
 * @file gpio_example.c
 * @brief GPIO peripheral example for MSP430G2xx
 *
 * This example demonstrates basic GPIO operations:
 * - Configure pins as input/output
 * - Set/clear pin states
 * - Toggle pins
 * - Read input pin values
 */

#include <msp430g2553.h>
#include "driverlib.h"

void main(void)
{
    // Stop watchdog timer
    WDT_A_holdTimer();

    // Configure P1.0 as output (LED)
    GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN0);

    // Configure P1.3 as input with pull-up resistor (Button)
    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P1, GPIO_PIN3);

    while(1)
    {
        // Read button state (active low)
        uint8_t buttonState = GPIO_getInputPinValue(GPIO_PORT_P1, GPIO_PIN3);

        if(buttonState == 0) // Button pressed
        {
            // Turn on LED
            GPIO_setOutputHighOnPin(GPIO_PORT_P1, GPIO_PIN0);

            // Simple debounce delay
            __delay_cycles(10000);
        }
        else
        {
            // Turn off LED
            GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0);
        }

        // Toggle LED every second for visual feedback
        GPIO_toggleOutputOnPin(GPIO_PORT_P1, GPIO_PIN0);
        __delay_cycles(1000000); // ~1 second at 1MHz
    }
}