//*****************************************************************************
//
// flashctl.h - Driver for the Flash Controller Module for MSP430G2xx family.
//
//*****************************************************************************

#ifndef __MSP430WARE_FLASHCTL_H__
#define __MSP430WARE_FLASHCTL_H__

#include "inc/hw_memmap.h"

#ifdef __MSP430_HAS_FLASH__

#ifdef __cplusplus
extern "C"
{
#endif

//*****************************************************************************
//
// Flash timing generator settings
//
//*****************************************************************************
#define FLASHCTL_CLOCK_DIVIDER_1                         (0x0000)    // Flash clock divider /1
#define FLASHCTL_CLOCK_DIVIDER_2                         (0x0001)    // Flash clock divider /2
#define FLASHCTL_CLOCK_DIVIDER_3                         (0x0002)    // Flash clock divider /3
#define FLASHCTL_CLOCK_DIVIDER_4                         (0x0003)    // Flash clock divider /4
#define FLASHCTL_CLOCK_DIVIDER_5                         (0x0004)    // Flash clock divider /5
#define FLASHCTL_CLOCK_DIVIDER_6                         (0x0005)    // Flash clock divider /6
#define FLASHCTL_CLOCK_DIVIDER_7                         (0x0006)    // Flash clock divider /7
#define FLASHCTL_CLOCK_DIVIDER_8                         (0x0007)    // Flash clock divider /8
#define FLASHCTL_CLOCK_DIVIDER_9                         (0x0008)    // Flash clock divider /9
#define FLASHCTL_CLOCK_DIVIDER_10                        (0x0009)    // Flash clock divider /10
#define FLASHCTL_CLOCK_DIVIDER_11                        (0x000A)    // Flash clock divider /11
#define FLASHCTL_CLOCK_DIVIDER_12                        (0x000B)    // Flash clock divider /12
#define FLASHCTL_CLOCK_DIVIDER_13                        (0x000C)    // Flash clock divider /13
#define FLASHCTL_CLOCK_DIVIDER_14                        (0x000D)    // Flash clock divider /14
#define FLASHCTL_CLOCK_DIVIDER_15                        (0x000E)    // Flash clock divider /15
#define FLASHCTL_CLOCK_DIVIDER_16                        (0x000F)    // Flash clock divider /16

//*****************************************************************************
//
// Flash status flags
//
//*****************************************************************************
#define FLASHCTL_READY                                   (0x0001)    // Flash ready
#define FLASHCTL_ACCESS_VIOLATION                        (0x0002)    // Flash access violation
#define FLASHCTL_PASSWORD_WRONG                          (0x0004)    // Wrong password
#define FLASHCTL_BUSY                                    (0x0008)    // Flash busy

//*****************************************************************************
//
// Prototypes for the APIs.
//
//*****************************************************************************

extern void FlashCtl_eraseSegment(uint8_t *flash_ptr);
extern void FlashCtl_performMassErase(uint8_t *flash_ptr);
extern bool FlashCtl_performEraseCheck(uint8_t *flash_ptr, uint16_t numberOfBytes);
extern void FlashCtl_write8(uint8_t *data_ptr, uint8_t *flash_ptr, uint16_t count);
extern void FlashCtl_write16(uint16_t *data_ptr, uint16_t *flash_ptr, uint16_t count);
extern void FlashCtl_write32(uint32_t *data_ptr, uint32_t *flash_ptr, uint16_t count);
extern void FlashCtl_fillMemory32(uint32_t value, uint32_t *flash_ptr, uint16_t count);
extern uint8_t FlashCtl_getStatus(uint8_t mask);
extern void FlashCtl_lockInfo(void);
extern void FlashCtl_unlockInfo(void);
extern uint8_t FlashCtl_setupClock(uint32_t clockTargetFreq, uint32_t clockSourceFreq, uint16_t clockSource);

#ifdef __cplusplus
}
#endif

#endif // __MSP430_HAS_FLASH__

#endif // __MSP430WARE_FLASHCTL_H__
