/**
 * @file timer_a_example.c
 * @brief Timer_A peripheral example for MSP430G2xx
 *
 * This example demonstrates Timer_A operations:
 * - Configure timer in up mode
 * - Generate periodic interrupts
 * - Toggle LED in interrupt service routine
 */

#include <msp430g2553.h>
#include "driverlib.h"

// Timer_A interrupt service routine
#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A_ISR(void)
{
    // Toggle P1.0 LED
    GPIO_toggleOutputOnPin(GPIO_PORT_P1, GPIO_PIN0);
}

void main(void)
{
    // Stop watchdog timer
    WDT_A_holdTimer();

    // Configure P1.0 as output (LED)
    GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN0);

    // Configure Timer_A in up mode for ~1Hz blinking
    // Clock source: ACLK (32768Hz), Divider: 1, Period: 32768 (1 second)
    Timer_A_initUpModeParam timerParam = {
        TIMER_A_CLOCKSOURCE_ACLK,           // Clock source
        TIMER_A_CLOCKSOURCE_DIVIDER_1,      // Divider
        32768,                             // Period (1 second at 32.768kHz)
        TIMER_A_TAIE_INTERRUPT_DISABLE,     // Timer interrupt disable
        TIMER_A_CCIE_CCR0_INTERRUPT_ENABLE, // CCR0 interrupt enable
        true                               // Start timer
    };

    Timer_A_initUpMode(TIMER_A0_BASE, &timerParam);

    // Enable global interrupts
    __bis_SR_register(GIE);

    // Enter low power mode 3 (CPU off, ACLK on for timer)
    PMM_enterLPM3();

    // Code never reaches here due to LPM3
    while(1);
}