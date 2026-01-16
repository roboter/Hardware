//*****************************************************************************
//
// bcs.h - Driver for the Basic Clock System Module for MSP430G2xx family.
//
//*****************************************************************************

#ifndef __MSP430WARE_BCS_H__
#define __MSP430WARE_BCS_H__

#include "inc/hw_memmap.h"

#ifdef __MSP430_HAS_BASIC_CLOCK__

#ifdef __cplusplus
extern "C"
{
#endif

//*****************************************************************************
//
// DCO frequency range settings
//
//*****************************************************************************
#define BCS_DCO_RSEL_0                                  (0x0000)    // DCO frequency range select 0
#define BCS_DCO_RSEL_1                                  (0x0001)    // DCO frequency range select 1
#define BCS_DCO_RSEL_2                                  (0x0002)    // DCO frequency range select 2
#define BCS_DCO_RSEL_3                                  (0x0003)    // DCO frequency range select 3
#define BCS_DCO_RSEL_4                                  (0x0004)    // DCO frequency range select 4
#define BCS_DCO_RSEL_5                                  (0x0005)    // DCO frequency range select 5
#define BCS_DCO_RSEL_6                                  (0x0006)    // DCO frequency range select 6
#define BCS_DCO_RSEL_7                                  (0x0007)    // DCO frequency range select 7
#define BCS_DCO_RSEL_8                                  (0x0008)    // DCO frequency range select 8
#define BCS_DCO_RSEL_9                                  (0x0009)    // DCO frequency range select 9
#define BCS_DCO_RSEL_10                                 (0x000A)    // DCO frequency range select 10
#define BCS_DCO_RSEL_11                                 (0x000B)    // DCO frequency range select 11
#define BCS_DCO_RSEL_12                                 (0x000C)    // DCO frequency range select 12
#define BCS_DCO_RSEL_13                                 (0x000D)    // DCO frequency range select 13
#define BCS_DCO_RSEL_14                                 (0x000E)    // DCO frequency range select 14
#define BCS_DCO_RSEL_15                                 (0x000F)    // DCO frequency range select 15

//*****************************************************************************
//
// DCO modulation settings
//
//*****************************************************************************
#define BCS_DCO_MODULATION_DISABLE                      (0x0000)    // DCO modulation disabled
#define BCS_DCO_MODULATION_ENABLE                       (0x0010)    // DCO modulation enabled

//*****************************************************************************
//
// Clock source selections for MCLK, SMCLK
//
//*****************************************************************************
#define BCS_CLOCKSOURCE_ACLK                            (0x0000)    // ACLK as clock source
#define BCS_CLOCKSOURCE_MCLK                            (0x0001)    // MCLK as clock source
#define BCS_CLOCKSOURCE_SMCLK                           (0x0002)    // SMCLK as clock source
#define BCS_CLOCKSOURCE_DCOCLK                          (0x0003)    // DCOCLK as clock source

//*****************************************************************************
//
// ACLK divider settings
//
//*****************************************************************************
#define BCS_ACLK_DIVIDER_1                              (0x0000)    // ACLK divider /1
#define BCS_ACLK_DIVIDER_2                              (0x0004)    // ACLK divider /2
#define BCS_ACLK_DIVIDER_4                              (0x0008)    // ACLK divider /4
#define BCS_ACLK_DIVIDER_8                              (0x000C)    // ACLK divider /8

//*****************************************************************************
//
// MCLK divider settings
//
//*****************************************************************************
#define BCS_MCLK_DIVIDER_1                              (0x0000)    // MCLK divider /1
#define BCS_MCLK_DIVIDER_2                              (0x0010)    // MCLK divider /2
#define BCS_MCLK_DIVIDER_4                              (0x0020)    // MCLK divider /4
#define BCS_MCLK_DIVIDER_8                              (0x0030)    // MCLK divider /8

//*****************************************************************************
//
// LFXT1 crystal frequency settings
//
//*****************************************************************************
#define BCS_LFXT1_CRYSTAL_FREQUENCY_32768               (0x0000)    // 32768 Hz crystal
#define BCS_LFXT1_CRYSTAL_FREQUENCY_1000K               (0x0001)    // 1 MHz crystal
#define BCS_LFXT1_CRYSTAL_FREQUENCY_3000K               (0x0002)    // 3 MHz crystal
#define BCS_LFXT1_CRYSTAL_FREQUENCY_4000K               (0x0003)    // 4 MHz crystal

//*****************************************************************************
//
// XT2 state settings
//
//*****************************************************************************
#define BCS_XT2_OFF                                     (0x0000)    // XT2 off
#define BCS_XT2_ON                                      (0x0001)    // XT2 on

//*****************************************************************************
//
// Prototypes for the APIs.
//
//*****************************************************************************

extern void BCS_setupDCO(uint8_t dcoRange, uint8_t modulation);
extern void BCS_setDCO(uint8_t dcoRange);
extern void BCS_setACLKDivider(uint8_t divider);
extern void BCS_setMCLKDivider(uint8_t divider);
extern void BCS_setSMCLKDivider(uint8_t divider);
extern void BCS_setupLFXT1(uint8_t lfxFrequency, uint8_t xt2State);
extern uint32_t BCS_getMCLKFrequency(void);
extern uint32_t BCS_getSMCLKFrequency(void);
extern uint32_t BCS_getACLKFrequency(void);
extern void BCS_enableXT2(void);
extern void BCS_disableXT2(void);
extern void BCS_enableLFXT1(void);
extern void BCS_disableLFXT1(void);

#ifdef __cplusplus
}
#endif

#endif // __MSP430_HAS_BASIC_CLOCK__

#endif // __MSP430WARE_BCS_H__
