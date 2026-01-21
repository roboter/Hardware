/**
 * @file adc10_a_example.c
 * @brief ADC10_A peripheral example for MSP430G2xx
 *
 * This example demonstrates ADC10 operations:
 * - Configure ADC for single conversion
 * - Read analog input from P1.0
 * - Use result to control LED brightness via PWM
 */

#include <msp430g2553.h>
#include "driverlib.h"

// ADC conversion result
volatile uint16_t adcResult;

void main(void)
{
    // Stop watchdog timer
    WDT_A_holdTimer();

    // Configure P1.0 as ADC input (A0)
    GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P1, GPIO_PIN0);

    // Configure P1.6 as PWM output (TA0.1)
    GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P1, GPIO_PIN6);

    // Configure ADC parameters
    ADC10_A_initParam adcParam = {
        ADC10_A_CLOCKSOURCE_ADC10OSC,      // Clock source
        ADC10_A_CLOCKSOURCE_DIVIDER_1,     // Clock divider
        ADC10_A_CLOCKSOURCE_PRESCALER_1,   // Prescaler
        ADC10_A_INTERNAL_CHANNEL_MAP_NONE  // No internal channel mapping
    };

    // Initialize ADC
    ADC10_A_init(ADC10_BASE, &adcParam);
    ADC10_A_enable(ADC10_BASE);

    // Configure ADC for single conversion on A0
    ADC10_A_setReferenceVoltage(ADC10_BASE, ADC10_A_VREFPOS_AVCC_VREFNEG_VSS);
    ADC10_A_setSampleHoldTime(ADC10_BASE, ADC10_A_SAMPLEHOLDSOURCE_16);

    // Configure Timer_A for PWM output on P1.6
    Timer_A_initUpModeParam timerParam = {
        TIMER_A_CLOCKSOURCE_SMCLK,         // Clock source
        TIMER_A_CLOCKSOURCE_DIVIDER_1,     // Divider
        1023,                             // Period (10-bit resolution)
        TIMER_A_TAIE_INTERRUPT_DISABLE,    // Timer interrupt disable
        TIMER_A_CCIE_CCR0_INTERRUPT_DISABLE, // CCR0 interrupt disable
        true                              // Start timer
    };

    Timer_A_initUpMode(TIMER_A0_BASE, &timerParam);
    Timer_A_setCompareValue(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_1, 512);

    while(1)
    {
        // Start ADC conversion
        ADC10_A_startConversion(ADC10_BASE, ADC10_A_INPUT_A0);

        // Wait for conversion to complete
        while(ADC10_A_getInterruptStatus(ADC10_BASE) == 0);

        // Read conversion result
        adcResult = ADC10_A_getResults(ADC10_BASE);

        // Clear interrupt flag
        ADC10_A_clearInterrupt(ADC10_BASE);

        // Update PWM duty cycle based on ADC result
        // ADC result ranges from 0-1023, perfect for our PWM period
        Timer_A_setCompareValue(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_1, adcResult);

        // Delay before next conversion
        __delay_cycles(10000); // ~10ms at 1MHz
    }
}