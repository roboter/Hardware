//*****************************************************************************
//
// timer_a.h - Driver for the TIMER_A Module for MSP430G2xx family.
//
//*****************************************************************************

#ifndef __MSP430WARE_TIMER_A_H__
#define __MSP430WARE_TIMER_A_H__

#include "inc/hw_memmap.h"

#ifdef __MSP430_HAS_TxA__

#ifdef __cplusplus
extern "C"
{
#endif

//*****************************************************************************
//
// Timer modes
//
//*****************************************************************************
#define TIMER_A_STOP_MODE                                              MC_0
#define TIMER_A_UP_MODE                                                MC_1
#define TIMER_A_CONTINUOUS_MODE                                        MC_2
#define TIMER_A_UPDOWN_MODE                                            MC_3

//*****************************************************************************
//
// Clock sources
//
//*****************************************************************************
#define TIMER_A_CLOCKSOURCE_TACLK                              TASSEL_0
#define TIMER_A_CLOCKSOURCE_ACLK                               TASSEL_1
#define TIMER_A_CLOCKSOURCE_SMCLK                              TASSEL_2
#define TIMER_A_CLOCKSOURCE_INVERTED_EXTERNAL_TXCLK            TASSEL_3

//*****************************************************************************
//
// Clock dividers
//
//*****************************************************************************
#define TIMER_A_CLOCKSOURCE_DIVIDER_1                              ID_0
#define TIMER_A_CLOCKSOURCE_DIVIDER_2                              ID_1
#define TIMER_A_CLOCKSOURCE_DIVIDER_4                              ID_2
#define TIMER_A_CLOCKSOURCE_DIVIDER_8                              ID_3

//*****************************************************************************
//
// Interrupt enables
//
//*****************************************************************************
#define TIMER_A_TAIE_INTERRUPT_DISABLE                                0x0000
#define TIMER_A_TAIE_INTERRUPT_ENABLE                                 TAIE
#define TIMER_A_CCIE_CCR0_INTERRUPT_DISABLE                           0x0000
#define TIMER_A_CCIE_CCR0_INTERRUPT_ENABLE                           CCIE

//*****************************************************************************
//
//! \brief Used in the Timer_A_initContinuousMode() function as the param
//! parameter.
//
//*****************************************************************************
typedef struct Timer_A_initContinuousModeParam {
    uint16_t clockSource;
    uint16_t clockSourceDivider;
    uint16_t timerInterruptEnable_TAIE;
    bool startTimer;
} Timer_A_initContinuousModeParam;

//*****************************************************************************
//
//! \brief Used in the Timer_A_initUpMode() function as the param parameter.
//
//*****************************************************************************
typedef struct Timer_A_initUpModeParam {
    uint16_t clockSource;
    uint16_t clockSourceDivider;
    uint16_t timerPeriod;
    uint16_t timerInterruptEnable_TAIE;
    uint16_t captureCompareInterruptEnable_CCR0_CCIE;
    bool startTimer;
} Timer_A_initUpModeParam;

//*****************************************************************************
//
// Prototypes for the APIs.
//
//*****************************************************************************

//*****************************************************************************
//
//! \brief Starts the Timer_A counter
//!
//! This function starts the Timer_A counter based on the mode selected.
//!
//! \param baseAddress is the base address of the Timer_A module.
//! \param timerMode mode to start the timer in.
//!        Valid values are:
//!        - \b TIMER_A_STOP_MODE
//!        - \b TIMER_A_UP_MODE
//!        - \b TIMER_A_CONTINUOUS_MODE
//!        - \b TIMER_A_UPDOWN_MODE
//!
//! \return None
//
//*****************************************************************************
extern void Timer_A_startCounter(uint16_t baseAddress, uint16_t timerMode);

//*****************************************************************************
//
//! \brief Stops the Timer_A counter
//!
//! This function stops the Timer_A counter from running.
//!
//! \param baseAddress is the base address of the Timer_A module.
//!
//! \return None
//
//*****************************************************************************
extern void Timer_A_stopCounter(uint16_t baseAddress);

//*****************************************************************************
//
//! \brief Initializes Timer_A in continuous mode
//!
//! This function initializes Timer_A in continuous mode.
//!
//! \param baseAddress is the base address of the Timer_A module.
//! \param param is the pointer to the initialization parameters.
//!
//! \return None
//
//*****************************************************************************
extern void Timer_A_initContinuousMode(uint16_t baseAddress,
                                        Timer_A_initContinuousModeParam *param);

//*****************************************************************************
//
//! \brief Initializes Timer_A in up mode
//!
//! This function initializes Timer_A in up mode.
//!
//! \param baseAddress is the base address of the Timer_A module.
//! \param param is the pointer to the initialization parameters.
//!
//! \return None
//
//*****************************************************************************
extern void Timer_A_initUpMode(uint16_t baseAddress,
                                Timer_A_initUpModeParam *param);

//*****************************************************************************
//
//! \brief Sets the compare value of Timer_A
//!
//! This function sets the compare value of the Timer_A capture/compare register.
//!
//! \param baseAddress is the base address of the Timer_A module.
//! \param compareRegister selects the compare register.
//! \param compareValue is the value to be written.
//!
//! \return None
//
//*****************************************************************************
extern void Timer_A_setCompareValue(uint16_t baseAddress,
                                     uint8_t compareRegister,
                                     uint16_t compareValue);

//*****************************************************************************
//
//! \brief Gets the current counter value of Timer_A
//!
//! This function gets the current counter value of Timer_A.
//!
//! \param baseAddress is the base address of the Timer_A module.
//!
//! \return Current counter value
//
//*****************************************************************************
extern uint16_t Timer_A_getCounterValue(uint16_t baseAddress);

//*****************************************************************************
//
//! \brief Clears the counter value of Timer_A
//!
//! This function clears the counter value of Timer_A.
//!
//! \param baseAddress is the base address of the Timer_A module.
//!
//! \return None
//
//*****************************************************************************
extern void Timer_A_clearCounter(uint16_t baseAddress);

#ifdef __cplusplus
}
#endif

#endif // __MSP430_HAS_TxA__

#endif // __MSP430WARE_TIMER_A_H__
