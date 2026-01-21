//*****************************************************************************
//
// adc10_a.c - Driver for the ADC10 Module for MSP430G2xx family.
//
//*****************************************************************************

#include "inc/hw_memmap.h"
#include "adc10_a.h"

#ifdef __MSP430_HAS_ADC10__

#include <assert.h>

void ADC10_A_init(uint16_t baseAddress, uint8_t sampleHoldSignalSourceSelect,
                  uint8_t clockSourceSelect, uint8_t clockSourceDivider)
{
    // Disable ADC10
    ADC10CTL0 = 0;

    // Configure clock source and divider
    ADC10CTL1 = clockSourceSelect | clockSourceDivider | sampleHoldSignalSourceSelect;
}

void ADC10_A_enable(uint16_t baseAddress)
{
    ADC10CTL0 |= ADC10ON;
}

void ADC10_A_disable(uint16_t baseAddress)
{
    ADC10CTL0 &= ~ADC10ON;
}

void ADC10_A_setReferenceVoltage(uint16_t baseAddress, uint16_t refVoltage)
{
    ADC10CTL0 &= ~SREF_3;
    ADC10CTL0 |= refVoltage;
}

void ADC10_A_setSampleHoldTime(uint16_t baseAddress, uint8_t sampleHoldTime)
{
    ADC10CTL0 &= ~ADC10SHT_15;
    ADC10CTL0 |= sampleHoldTime;
}

void ADC10_A_enableInterrupt(uint16_t baseAddress)
{
    ADC10IE |= ADC10IE0;
}

void ADC10_A_disableInterrupt(uint16_t baseAddress)
{
    ADC10IE &= ~ADC10IE0;
}

void ADC10_A_clearInterrupt(uint16_t baseAddress)
{
    ADC10IFG &= ~ADC10IFG0;
}

uint8_t ADC10_A_getInterruptStatus(uint16_t baseAddress)
{
    return (ADC10IFG & ADC10IFG0);
}

void ADC10_A_startConversion(uint16_t baseAddress, uint8_t inputChannelSelect)
{
    // Configure input channel
    ADC10CTL1 &= ~INCH_15;
    ADC10CTL1 |= inputChannelSelect;

    // Start conversion
    ADC10CTL0 |= (ADC10SC | ENC);
}

uint16_t ADC10_A_getResults(uint16_t baseAddress)
{
    return ADC10MEM;
}

#endif // __MSP430_HAS_ADC10__