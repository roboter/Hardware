//*****************************************************************************
//
// pmm.h - Driver for the Power Management Module for MSP430G2xx family.
//
//*****************************************************************************

#ifndef __MSP430WARE_PMM_H__
#define __MSP430WARE_PMM_H__

#include "inc/hw_memmap.h"

#ifdef __MSP430_HAS_PMM__

#ifdef __cplusplus
extern "C"
{
#endif

//*****************************************************************************
//
// Voltage monitor levels (if available)
//
//*****************************************************************************
#define PMM_VMON_LEVEL_1_8V                             (0x0000)    // 1.8V voltage monitor level
#define PMM_VMON_LEVEL_2_2V                             (0x0001)    // 2.2V voltage monitor level
#define PMM_VMON_LEVEL_2_7V                             (0x0002)    // 2.7V voltage monitor level
#define PMM_VMON_LEVEL_3_0V                             (0x0003)    // 3.0V voltage monitor level

//*****************************************************************************
//
// Brown-out reset levels
//
//*****************************************************************************
#define PMM_BOR_LEVEL_1_8V                              (0x0000)    // 1.8V brown-out reset level
#define PMM_BOR_LEVEL_2_2V                              (0x0004)    // 2.2V brown-out reset level
#define PMM_BOR_LEVEL_2_7V                              (0x0008)    // 2.7V brown-out reset level
#define PMM_BOR_LEVEL_3_0V                              (0x000C)    // 3.0V brown-out reset level

//*****************************************************************************
//
// Low power reset enable/disable
//
//*****************************************************************************
#define PMM_LPR_DISABLE                                 (0x0000)    // Low power reset disabled
#define PMM_LPR_ENABLE                                  (0x0010)    // Low power reset enabled

//*****************************************************************************
//
// Prototypes for the APIs.
//
//*****************************************************************************

extern void PMM_enterLPM0(void);
extern void PMM_enterLPM1(void);
extern void PMM_enterLPM2(void);
extern void PMM_enterLPM3(void);
extern void PMM_enterLPM4(void);
extern void PMM_exitLPM(void);
extern void PMM_setVoltageMonitorLevel(uint8_t level);
extern void PMM_enableVoltageMonitor(void);
extern void PMM_disableVoltageMonitor(void);
extern void PMM_enableBrownOutReset(void);
extern void PMM_disableBrownOutReset(void);
extern void PMM_enableLowPowerReset(void);
extern void PMM_disableLowPowerReset(void);
extern uint8_t PMM_getInterruptStatus(uint8_t mask);
extern void PMM_clearInterrupt(uint8_t mask);
extern void PMM_enableInterrupt(uint8_t mask);
extern void PMM_disableInterrupt(uint8_t mask);

#ifdef __cplusplus
}
#endif

#endif // __MSP430_HAS_PMM__

#endif // __MSP430WARE_PMM_H__
