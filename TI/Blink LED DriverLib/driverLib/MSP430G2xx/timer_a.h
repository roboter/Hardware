//*****************************************************************************
//
// timer_a.h - Driver for the Timer_A Module.
//
//*****************************************************************************

#ifndef __MSP430WARE_TIMER_A_H__
#define __MSP430WARE_TIMER_A_H__

#include <msp430g2553.h>

// Define standard integer types if not already defined
#ifndef uint8_t
typedef unsigned char uint8_t;
#endif
#ifndef uint16_t
typedef unsigned int uint16_t;
#endif

// Timer_A constants (simplified for MSP430G2553)
#define TIMER_A_CLOCKSOURCE_SMCLK                    (0x0200)
#define TIMER_A_CLOCKSOURCE_ACLK                     (0x0100)
#define TIMER_A_CLOCKSOURCE_EXTERNAL_TXCLK           (0x0200)
#define TIMER_A_CLOCKSOURCE_INVERTED_EXTERNAL_TXCLK  (0x0300)

#define TIMER_A_CLOCKSOURCE_DIVIDER_1                (0x0000)
#define TIMER_A_CLOCKSOURCE_DIVIDER_2                (0x0040)
#define TIMER_A_CLOCKSOURCE_DIVIDER_4                (0x0080)
#define TIMER_A_CLOCKSOURCE_DIVIDER_8                (0x00C0)

#define TIMER_A_TAIE_INTERRUPT_ENABLE                (0x0002)
#define TIMER_A_TAIE_INTERRUPT_DISABLE               (0x0000)

#define TIMER_A_CCIE_CCR0_INTERRUPT_ENABLE           (0x0010)
#define TIMER_A_CCIE_CCR0_INTERRUPT_DISABLE          (0x0000)

#define TIMER_A_CAPTURECOMPARE_REGISTER_0            (0x0000)
#define TIMER_A_CAPTURECOMPARE_REGISTER_1            (0x0002)
#define TIMER_A_CAPTURECOMPARE_REGISTER_2            (0x0004)

// Function prototypes
extern void Timer_A_startCounter(uint16_t baseAddress, uint16_t timerMode);
extern void Timer_A_stopTimer(uint16_t baseAddress);
extern void Timer_A_clearTimerInterrupt(uint16_t baseAddress);
extern uint16_t Timer_A_getInterruptStatus(uint16_t baseAddress);
extern void Timer_A_enableInterrupt(uint16_t baseAddress);
extern void Timer_A_disableInterrupt(uint16_t baseAddress);

#endif // __MSP430WARE_TIMER_A_H__