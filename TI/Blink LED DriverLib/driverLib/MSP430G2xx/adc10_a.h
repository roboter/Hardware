//*****************************************************************************
//
// adc10_a.h - Driver for the ADC10_A Module for MSP430G2xx family.
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
//! \brief Used in the ADC10_A_init() function as the param parameter.
//
//*****************************************************************************
typedef struct ADC10_A_initParam {
    uint8_t clockSource;
    uint8_t sampleHoldSignalSourceSelect;
    uint8_t clockSourceDivider;
    uint8_t clockSourcePredivider;
    uint8_t internalChannelMap;
} ADC10_A_initParam;

//*****************************************************************************
//
// Clock sources
//
//*****************************************************************************
#define ADC10_A_CLOCKSOURCE_ADC10OSC                                 ADC10OSC
#define ADC10_A_CLOCKSOURCE_ACLK                                      ADC10SSEL_0
#define ADC10_A_CLOCKSOURCE_MCLK                                      ADC10SSEL_1
#define ADC10_A_CLOCKSOURCE_SMCLK                                     ADC10SSEL_2
//#define ADC10_A_CLOCKSOURCE_SMCLK                                     ADC10SSEL_3

//*****************************************************************************
//
// Input channels
//
//*****************************************************************************
#define ADC10_A_INPUT_A0                                              INCH_0
#define ADC10_A_INPUT_A1                                              INCH_1
#define ADC10_A_INPUT_A2                                              INCH_2
#define ADC10_A_INPUT_A3                                              INCH_3
#define ADC10_A_INPUT_A4                                              INCH_4
#define ADC10_A_INPUT_A5                                              INCH_5
#define ADC10_A_INPUT_A6                                              INCH_6
#define ADC10_A_INPUT_A7                                              INCH_7
#define ADC10_A_INPUT_TEMPERATURE_SENSOR                              INCH_10
#define ADC10_A_INPUT_VCC_2                                            INCH_11

//*****************************************************************************
//
// Reference voltages
//
//*****************************************************************************
#define ADC10_A_VREFPOS_AVCC_VREFNEG_VSS                             0x0000
#define ADC10_A_VREFPOS_EXTPOS_VREFNEG_VSS                           SREF_1
#define ADC10_A_VREFPOS_AVCC_VREFNEG_EXTNEG                           SREF_2
#define ADC10_A_VREFPOS_EXTPOS_VREFNEG_EXTNEG                         SREF_3
#define ADC10_A_VREFPOS_INT_1_5V_VREFNEG_VSS                          SREF_4
#define ADC10_A_VREFPOS_INT_1_5V_VREFNEG_EXTNEG                       SREF_5
#define ADC10_A_VREFPOS_INT_2_5V_VREFNEG_VSS                          SREF_6
#define ADC10_A_VREFPOS_INT_2_5V_VREFNEG_EXTNEG                       SREF_7

//*****************************************************************************
//
// Prototypes for the APIs.
//
//*****************************************************************************

extern void ADC10_A_init(uint16_t baseAddress, ADC10_A_initParam *param);
extern void ADC10_A_enable(uint16_t baseAddress);
extern void ADC10_A_disable(uint16_t baseAddress);
extern void ADC10_A_setResolution(uint16_t baseAddress, uint8_t resolution);
extern void ADC10_A_setDataReadBackFormat(uint16_t baseAddress, uint8_t format);
extern void ADC10_A_setReferenceVoltage(uint16_t baseAddress, uint16_t refVoltage);
extern void ADC10_A_setSampleHoldTime(uint16_t baseAddress,
                                      uint8_t clockCycles,
                                      uint8_t multiSample);
extern void ADC10_A_setWindowComp(uint16_t baseAddress,
                                  uint16_t highThreshold,
                                  uint16_t lowThreshold);
extern void ADC10_A_enableInterrupt(uint16_t baseAddress, uint16_t mask);
extern void ADC10_A_disableInterrupt(uint16_t baseAddress, uint16_t mask);
extern void ADC10_A_clearInterrupt(uint16_t baseAddress, uint16_t mask);
extern uint16_t ADC10_A_getInterruptStatus(uint16_t baseAddress);
extern void ADC10_A_startConversion(uint16_t baseAddress, uint8_t inputChannelSelect);
extern uint16_t ADC10_A_getResults(uint16_t baseAddress);

#ifdef __cplusplus
}
#endif

#endif // __MSP430_HAS_ADC10__

#endif // __MSP430WARE_ADC10_A_H__
