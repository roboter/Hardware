//*****************************************************************************
//
// flashctl.h - Driver for the Flash Controller Module.
//
//*****************************************************************************

#ifndef __MSP430WARE_FLASHCTL_H__
#define __MSP430WARE_FLASHCTL_H__

#include <msp430g2553.h>

// Define standard integer types if not already defined
#ifndef uint8_t
typedef unsigned char uint8_t;
#endif
#ifndef uint16_t
typedef unsigned int uint16_t;
#endif

// Flash Controller constants
#define FLASHCTL_ERASE_SEGMENT                        (0x02)
#define FLASHCTL_ERASE_MAIN                           (0x04)
#define FLASHCTL_WRITE_BYTE                           (0x01)
#define FLASHCTL_WRITE_WORD                           (0x02)

// Function prototypes
extern void FlashCtl_eraseSegment(uint16_t *flashAddress);
extern void FlashCtl_writeByte(uint16_t *flashAddress, uint8_t data);
extern void FlashCtl_writeWord(uint16_t *flashAddress, uint16_t data);
extern uint8_t FlashCtl_getStatus(void);

#endif // __MSP430WARE_FLASHCTL_H__