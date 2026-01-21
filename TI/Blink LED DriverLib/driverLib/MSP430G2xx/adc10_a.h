//*****************************************************************************
//
// adc10_a.h - Driver for the ADC10 Module for MSP430G2xx family.
//
//*****************************************************************************

#ifndef __MSP430WARE_ADC10_A_H__
#define __MSP430WARE_ADC10_A_H__

#include "inc/hw_memmap.h"

#ifdef __MSP430_HAS_ADC10__

#ifdef __cplusplus
extern "C"
{
#endif

//*****************************************************************************
//
// Clock sources
//
//*****************************************************************************
#define ADC10_A_CLOCKSOURCE_ADC10OSC                               ADC10SSEL_0
#define ADC10_A_CLOCKSOURCE_ACLK                                   ADC10SSEL_1
#define ADC10_A_CLOCKSOURCE_MCLK                                   ADC10SSEL_2
#define ADC10_A_CLOCKSOURCE_SMCLK                                  ADC10SSEL_3

//*****************************************************************************
//
// Clock dividers
//
//*****************************************************************************
#define ADC10_A_CLOCKDIVIDER_1                                     ADC10DIV_0
#define ADC10_A_CLOCKDIVIDER_2                                     ADC10DIV_1
#define ADC10_A_CLOCKDIVIDER_3                                     ADC10DIV_2
#define ADC10_A_CLOCKDIVIDER_4                                     ADC10DIV_3
#define ADC10_A_CLOCKDIVIDER_5                                     ADC10DIV_4
#define ADC10_A_CLOCKDIVIDER_6                                     ADC10DIV_5
#define ADC10_A_CLOCKDIVIDER_7                                     ADC10DIV_6
#define ADC10_A_CLOCKDIVIDER_8                                     ADC10DIV_7

//*****************************************************************************
//
// Input channels
//
//*****************************************************************************
#define ADC10_A_INPUT_A0                                           INCH_0
#define ADC10_A_INPUT_A1                                           INCH_1
#define ADC10_A_INPUT_A2                                           INCH_2
#define ADC10_A_INPUT_A3                                           INCH_3
#define ADC10_A_INPUT_A4                                           INCH_4
#define ADC10_A_INPUT_A5                                           INCH_5
#define ADC10_A_INPUT_A6                                           INCH_6
#define ADC10_A_INPUT_A7                                           INCH_7
#define ADC10_A_INPUT_TEMPERATURE_SENSOR                           INCH_10
#define ADC10_A_INPUT_VCC_2                                         INCH_11

//*****************************************************************************
//
// Reference voltages
//
//*****************************************************************************
#define ADC10_A_VREFPOS_AVCC_VREFNEG_VSS                          SREF_0
#define ADC10_A_VREFPOS_EXTPOS_VREFNEG_VSS                        SREF_1
#define ADC10_A_VREFPOS_AVCC_VREFNEG_EXTNEG                        SREF_2
#define ADC10_A_VREFPOS_EXTPOS_VREFNEG_EXTNEG                      SREF_3

//*****************************************************************************
//
// Sample and hold time
//
//*****************************************************************************
#define ADC10_A_SAMPLEHOLDSOURCE_SC                                ADC10SHT_0
#define ADC10_A_SAMPLEHOLDSOURCE_1                                 ADC10SHT_1
#define ADC10_A_SAMPLEHOLDSOURCE_2                                 ADC10SHT_2
#define ADC10_A_SAMPLEHOLDSOURCE_3                                 ADC10SHT_3
#define ADC10_A_SAMPLEHOLDSOURCE_4                                 ADC10SHT_4
#define ADC10_A_SAMPLEHOLDSOURCE_5                                 ADC10SHT_5
#define ADC10_A_SAMPLEHOLDSOURCE_6                                 ADC10SHT_6
#define ADC10_A_SAMPLEHOLDSOURCE_7                                 ADC10SHT_7
#define ADC10_A_SAMPLEHOLDSOURCE_8                                 ADC10SHT_8
#define ADC10_A_SAMPLEHOLDSOURCE_9                                 ADC10SHT_9
#define ADC10_A_SAMPLEHOLDSOURCE_10                                ADC10SHT_10
#define ADC10_A_SAMPLEHOLDSOURCE_11                                ADC10SHT_11
#define ADC10_A_SAMPLEHOLDSOURCE_12                                ADC10SHT_12
#define ADC10_A_SAMPLEHOLDSOURCE_13                                ADC10SHT_13
#define ADC10_A_SAMPLEHOLDSOURCE_14                                ADC10SHT_14
#define ADC10_A_SAMPLEHOLDSOURCE_15                                ADC10SHT_15
#define ADC10_A_SAMPLEHOLDSOURCE_16                                ADC10SHT_4  // 16 cycles

//*****************************************************************************
//
// Conversion sequence mode select
//
//*****************************************************************************
#define ADC10_A_SINGLE_CHANNEL_SINGLE_CONVERSION                   CONSEQ_0
#define ADC10_A_SEQUENCE_OF_CHANNELS                               CONSEQ_1
#define ADC10_A_REPEATED_SINGLE_CHANNEL                            CONSEQ_2
#define ADC10_A_REPEATED_SEQUENCE_OF_CHANNELS                      CONSEQ_3

//*****************************************************************************
//
// Prototypes for the APIs.
//
//*****************************************************************************

extern void ADC10_A_init(uint16_t baseAddress, uint8_t sampleHoldSignalSourceSelect,
                        uint8_t clockSourceSelect, uint8_t clockSourceDivider);
extern void ADC10_A_enable(uint16_t baseAddress);
extern void ADC10_A_disable(uint16_t baseAddress);
extern void ADC10_A_setReferenceVoltage(uint16_t baseAddress, uint16_t refVoltage);
extern void ADC10_A_setSampleHoldTime(uint16_t baseAddress, uint8_t sampleHoldTime);
extern void ADC10_A_enableInterrupt(uint16_t baseAddress);
extern void ADC10_A_disableInterrupt(uint16_t baseAddress);
extern void ADC10_A_clearInterrupt(uint16_t baseAddress);
extern uint8_t ADC10_A_getInterruptStatus(uint16_t baseAddress);
extern void ADC10_A_startConversion(uint16_t baseAddress, uint8_t inputChannelSelect);
extern uint16_t ADC10_A_getResults(uint16_t baseAddress);

#ifdef __cplusplus
}
#endif

#endif // __MSP430_HAS_ADC10__

#endif // __MSP430WARE_ADC10_A_H__