//*****************************************************************************
//
// bcs.h - Driver for the Basic Clock System Module.
//
//*****************************************************************************

#ifndef __MSP430WARE_BCS_H__
#define __MSP430WARE_BCS_H__

#include <msp430g2553.h>

// Define standard integer types if not already defined
#ifndef uint8_t
typedef unsigned char uint8_t;
#endif
#ifndef uint16_t
typedef unsigned int uint16_t;
#endif

// BCS constants
#define BCS_DCO_RSEL_0                                (0x0000)    // DCO frequency range select 0 (~100kHz)
#define BCS_DCO_RSEL_1                                (0x0001)    // DCO frequency range select 1 (~150kHz)
#define BCS_DCO_RSEL_2                                (0x0002)    // DCO frequency range select 2 (~200kHz)
#define BCS_DCO_RSEL_3                                (0x0003)    // DCO frequency range select 3 (~300kHz)
#define BCS_DCO_RSEL_4                                (0x0004)    // DCO frequency range select 4 (~400kHz)
#define BCS_DCO_RSEL_5                                (0x0005)    // DCO frequency range select 5 (~600kHz)
#define BCS_DCO_RSEL_6                                (0x0006)    // DCO frequency range select 6 (~800kHz)
#define BCS_DCO_RSEL_7                                (0x0007)    // DCO frequency range select 7 (~1.2MHz)
#define BCS_DCO_RSEL_8                                (0x0008)    // DCO frequency range select 8 (~1.6MHz)
#define BCS_DCO_RSEL_9                                (0x0009)    // DCO frequency range select 9 (~2.0MHz)
#define BCS_DCO_RSEL_10                               (0x000A)    // DCO frequency range select 10 (~3.0MHz)
#define BCS_DCO_RSEL_11                               (0x000B)    // DCO frequency range select 11 (~4.0MHz)
#define BCS_DCO_RSEL_12                               (0x000C)    // DCO frequency range select 12 (~6.0MHz)
#define BCS_DCO_RSEL_13                               (0x000D)    // DCO frequency range select 13 (~8.0MHz)
#define BCS_DCO_RSEL_14                               (0x000E)    // DCO frequency range select 14 (~12.0MHz)
#define BCS_DCO_RSEL_15                               (0x000F)    // DCO frequency range select 15 (~16.0MHz)

#define BCS_DCO_MODULATION_DISABLE                    (0x0000)    // DCO modulation disabled
#define BCS_DCO_MODULATION_ENABLE                     (0x0010)    // DCO modulation enabled

#define BCS_MCLK_DIVIDER_1                            (0x0000)    // MCLK divider /1
#define BCS_MCLK_DIVIDER_2                            (0x0010)    // MCLK divider /2
#define BCS_MCLK_DIVIDER_4                            (0x0020)    // MCLK divider /4
#define BCS_MCLK_DIVIDER_8                            (0x0030)    // MCLK divider /8

#define BCS_SMCLK_DIVIDER_1                           (0x0000)    // SMCLK divider /1
#define BCS_SMCLK_DIVIDER_2                           (0x0004)    // SMCLK divider /2
#define BCS_SMCLK_DIVIDER_4                           (0x0008)    // SMCLK divider /4
#define BCS_SMCLK_DIVIDER_8                           (0x000C)    // SMCLK divider /8

// Function prototypes
extern void BCS_setupDCO(uint8_t dcoRange, uint8_t modulation);
extern void BCS_setMCLKDivider(uint8_t divider);
extern void BCS_setSMCLKDivider(uint8_t divider);
extern uint32_t BCS_getMCLKFrequency(void);
extern uint32_t BCS_getSMCLKFrequency(void);
extern uint32_t BCS_getACLKFrequency(void);

#endif // __MSP430WARE_BCS_H__