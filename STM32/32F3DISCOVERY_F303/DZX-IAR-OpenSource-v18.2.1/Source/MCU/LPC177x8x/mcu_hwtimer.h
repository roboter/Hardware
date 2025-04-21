/*******************************************************************************************************************************************

    DZX | LPC177x8x | HARDWARE TIMER                                                                                      VERSION 18.2.1
    ------------------------------------------------------------------------------------------------------------------------------------

    This is part of the MCU peripheral drivers and provides support for peripheral timers.

    ------------------------------------------------------------------------------------------------------------------------------------

    GNU GENERAL PUBLIC LICENSE VERSION 3 (GPLv3)

    This file is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published 
    by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

    This file is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of 
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along with this distribution (license.txt). Please review the 
    following information to ensure all requirements of the license will be met:  
    <https://dzxdesigns.com/licensing/open.aspx> and <http://www.gnu.org/licenses/gpl-3.0.html> for more information.

    ------------------------------------------------------------------------------------------------------------------------------------
    COPYRIGHT (C) 2018 DZX DESIGNS 

*******************************************************************************************************************************************/
#ifndef MCU_HWTIMER_H__
#define MCU_HWTIMER_H__

#include "Kernel/kernel.h"
#include "mcu_pin.h"

/*******************************************************************************************************************************************
    REGISTER DEFINITIONS
*******************************************************************************************************************************************/
#define REG_TIMER0      ((TIMERREGISTERS*)0x40004000)
#define REG_TIMER1      ((TIMERREGISTERS*)0x40008000)
#define REG_TIMER2      ((TIMERREGISTERS*)0x40090000)
#define REG_TIMER3      ((TIMERREGISTERS*)0x40094000)

typedef struct T0IRBITFIELD {
    UINT32 MR0INT                  :1;
    UINT32 MR1INT                  :1;
    UINT32 MR2INT                  :1;
    UINT32 MR3INT                  :1;
    UINT32 CR0INT                  :1;
    UINT32 CR1INT                  :1;
    UINT32 CR2INT                  :1;
    UINT32 CR3INT                  :1;
    UINT32                         :24;
} T0IRBITFIELD;

typedef struct T0TCRBITFIELD {
    UINT32 CE                      :1;
    UINT32 CR                      :1;
    UINT32                         :30;
} T0TCRBITFIELD;

typedef struct T0MCRBITFIELD {
    UINT32 MR0I                    :1;
    UINT32 MR0R                    :1;
    UINT32 MR0S                    :1;
    UINT32 MR1I                    :1;
    UINT32 MR1R                    :1;
    UINT32 MR1S                    :1;
    UINT32 MR2I                    :1;
    UINT32 MR2R                    :1;
    UINT32 MR2S                    :1;
    UINT32 MR3I                    :1;
    UINT32 MR3R                    :1;
    UINT32 MR3S                    :1;
    UINT32                         :20;
} T0MCRBITFIELD;


typedef struct T0CCRBITFIELD {
    UINT32 CAP0RE                  :1;
    UINT32 CAP0FE                  :1;
    UINT32 CAP0I                   :1;
    UINT32 CAP1RE                  :1;
    UINT32 CAP1FE                  :1;
    UINT32 CAP1I                   :1;
    UINT32 CAP2RE                  :1;
    UINT32 CAP2FE                  :1;
    UINT32 CAP2I                   :1;
    UINT32 CAP3RE                  :1;
    UINT32 CAP3FE                  :1;
    UINT32 CAP3I                   :1;
    UINT32                         :20;
} T0CCRBITFIELD;

typedef struct T0EMRBITFIELD {
    UINT32 EM0                     :1;
    UINT32 EM1                     :1;
    UINT32 EM2                     :1;
    UINT32 EM3                     :1;
    UINT32 EMC0                    :2;
    UINT32 EMC1                    :2;
    UINT32 EMC2                    :2;
    UINT32 EMC3                    :2;
    UINT32                         :20;
} T0EMRBITFIELD;

typedef struct T0CTCRBITFIELD {
    UINT32 CTM                     :2;
    UINT32 CIS                     :2;
    UINT32                         :28;
} T0CTCRBITFIELD;

typedef struct REG_TIMER {
	PREG_BITS32(IR, T0IRBITFIELD);
	PREG_BITS32(TCR, T0TCRBITFIELD);
	PREG_32(TC);
	PREG_32(PR);
	PREG_32(PC);
	PREG_BITS32(MCR, T0MCRBITFIELD);
	PREG_32(MR0);
	PREG_32(MR1);
	PREG_32(MR2);
	PREG_32(MR3);
	PREG_BITS32(CCR, T0CCRBITFIELD);
	PREG_32(CR0);
	PREG_32(CR1);
	PREG_32(CR2);
	PREG_32(CR3);
	PREG_BITS32(EMR, T0EMRBITFIELD);
	volatile UINT32 reserved[12];
	PREG_BITS32(CTCR, T0CTCRBITFIELD);
} TIMERREGISTERS;


#define OPT_ABSVALUE                (1 <<  8)
#define OPT_RELCOUNTER              (1 <<  9)
#define OPT_RELMATCH                (1 << 10)
#define OPT_MATCHRESET              (1 << 11)
#define OPT_MATCHSTOP               (1 << 12)

#define OPT_MATCHNONE               0
#define OPT_MATCHLOW                1
#define OPT_MATCHHIGH               2
#define OPT_MATCHTOGGLE             3

/*******************************************************************************************************************************************
    TYPE DEFINITIONS
*******************************************************************************************************************************************/
typedef struct LPC177X8X_HWTIMER HWTIMER;
typedef enum LPC177X8X_TIMEREVENT TIMEREVENT;

/***************************************************************************************************************************************//**

    Represents a function that will receive a callback upon a hardware timer event.
    @module     internal

*******************************************************************************************************************************************/
enum LPC177X8X_TIMEREVENT {
	TIMERMATCH0 = 0,
	TIMERMATCH1,
	TIMERMATCH2,
	TIMERMATCH3,
	TIMERCAPTURE0,
	TIMERCAPTURE1,
	TIMEREVENTMAX,
};

/***************************************************************************************************************************************//**

    An application-defined function that is called upon a hardware timer event.

    @param[in]  timer       A pointer to the timer that received the event.
    @param[in]  channel     The channel that received the event.
    @param[in]  arg         A pointer to an optional application-defined argument that was provided when the event was created.
    @param[in]  value       The value for the event, either capture or match time in ticks.

    @return     None.
    @module     hwtimer-lpc177x8x

*******************************************************************************************************************************************/
typedef void (*HWTIMERCALLBACK)(HWTIMER* timer, UINT32 channel, void* arg, UINT32 value);

/***************************************************************************************************************************************//**

    An MCU internal hardware timer.
    @module     hwtimer-lpc177x8x

*******************************************************************************************************************************************/
struct LPC177X8X_HWTIMER {
    BYTE                number;                         /**< The timer number (0-3) */
    TIMERREGISTERS*     REG;                            /**< A pointer to the peripheral registers for the timer */
    void*               args[TIMEREVENTMAX];            /**< Application defined arguments for timer events */
    HWTIMERCALLBACK     callbacks[TIMEREVENTMAX];       /**< Application defined callback functions for timer events */
};

/*******************************************************************************************************************************************
    PUBLIC FUNCTIONS
*******************************************************************************************************************************************/
/***************************************************************************************************************************************//**

    Enables a hardware timer.

    @param[in]  timer       A pointer to a caller allocated timer to be initialized.
    @param[in]  number      The number of the timer to be enabled (0-3).

    @return     A status code the indicates the result.

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The timer was successfully intialized and configured.
     ERR_NULLREFERENCE      | The argument 'timer' was found to be NULL.
     ERR_NOTSUPPORTED       | The timer number is not supported.

    @module     hwtimer-lpc177x8x

*******************************************************************************************************************************************/
extern STATUS HWTIMER_Enable(HWTIMER* timer, UINT32 channel);

/***************************************************************************************************************************************//**

    Disables a hardware timer.

    @param[in]  timer       A pointer to the timer to be disabled.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The timer has been disabled.
     ERR_NULLREFERENCE      | The argument 'timer' was found to be NULL.

    @module     hwtimer-lpc177x8x

*******************************************************************************************************************************************/
extern STATUS HWTIMER_Disable(HWTIMER* timer);

/***************************************************************************************************************************************//**

    Reads and returns a hardware timer's current counter value.

    @param[in]  timer       A pointer to the hardware timer to be read.

    @return     The current counter value for the given timer.
    @module     hwtimer-lpc177x8x

*******************************************************************************************************************************************/
extern UINT32 HWTIMER_Counter(HWTIMER* timer);

/***************************************************************************************************************************************//**

    Reads and returns the capture value for a hardware timer channel.

    @param[in]  timer       A pointer to the hardware timer to be read.
    @param[in]  channel     The timer channel to be read.

    @return     The capture value for the given timer.
    @module     hwtimer-lpc177x8x

*******************************************************************************************************************************************/
extern UINT32 HWTIMER_Capture(HWTIMER* timer, UINT32 channel);

/***************************************************************************************************************************************//**

    Reads and returns the match value for a hardware timer channel.

    @param[in]  timer       A pointer to the hardware timer to be read.
    @param[in]  channel     The timer channel to be read.

    @return     The match value for the given timer.
    @module     hwtimer-lpc177x8x

*******************************************************************************************************************************************/
extern UINT32 HWTIMER_Match(HWTIMER* timer, UINT32 channel);

/***************************************************************************************************************************************//**

    Configures a timer to generate a capture event for the specified signal edge(s). Once a capture is configured for a particular
    channel, it will remain configured and will continue to call the given callback function for each capture event until the capture
    is explicitly cancelled.

    @param[in]  timer       A pointer to the target timer.
    @param[in]  channel     The channel to receive the capture event.
    @param[in]  edge        The signal edge(s) that will generate a capture event.

     edge                   | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     EDGE_RISING            | Generate a capture event upon rising edges only.
     EDGE_FALLING           | Generate a capture event upon falling edges only.
     EDGE_BOTH              | Generate a capture event upon both rising and falling edges.

    @param[in]  callback    A function to receive a callback upon the capture event.
    @param[in]  state       An optional object to be passed to the callback upon the capture event. Can be NULL.

    @return     A status code the indicates the result.

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The capture event has been successfully configured.
     ERR_NULLREFERENCE      | The argument 'timer' was found to be NULL.
     ERR_NOTINITIALIZED     | The specified timer has not been initialized (enabled).
     ERR_NOTSUPPORTED       | The specified timer channel is not supported.

    @remark     Only a single callback function can be configured at a time per timer channel.
    @module     hwtimer-lpc177x8x

*******************************************************************************************************************************************/
extern STATUS HWTIMER_CreateCapture(HWTIMER* timer, UINT32 channel, EDGE edge, HWTIMERCALLBACK callback, void* arg);

/***************************************************************************************************************************************//**

    Cancels a pending timer capture event.

    @param[in]  timer       A pointer to the target timer.
    @param[in]  channel     The timer channel to be cancelled.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The timer capture was successfully cancelled.\
     ERR_NULLREFERENCE      | The argument 'timer' was found to be NULL.
     ERR_NOTSUPPORTED       | The specified timer channel is not supported.

    @module     hwtimer-lpc177x8x

*******************************************************************************************************************************************/
extern STATUS HWTIMER_CancelCapture(HWTIMER* timer, UINT32 channel);

/***************************************************************************************************************************************//**

    Configures a timer to generate a match event.

    @param[in]  timer       A pointer to the target timer.
    @param[in]  channel     The timer channel to receive the match event.
    @param[in]  value       The absolute counter value that will generate a match event.
    @param[in]  callback    A function to receive a callback upon the match event.
    @param[in]  state       An optional object to be passed to the callback upon the match event. Can be NULL.
    @param[in]  opt         Additional options for the match event.
     
     opt                    | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     OPT_NONE               | No options. Create as a one-shot match event.
     OPT_MATCHRESET         | The timer counter should be reset upon the match event.
     OPT_MATCHSTOP          | The timer counter should be stopped upon the match event.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The match event was successfully configured.
     ERR_NULLREFERENCE      | The argument 'timer' was found to be NULL.
     ERR_NOTINITIALIZED     | The specified timer has not been initialized (enabled).
     ERR_NOTSUPPORTED       | The specified timer channel is not supported.
     
    @module     hwtimer-lpc177x8x

*******************************************************************************************************************************************/
extern STATUS HWTIMER_CreateMatch(HWTIMER* timer, UINT32 channel, UINT32 value, HWTIMERCALLBACK callback, void* arg, UINT32 opt);

/***************************************************************************************************************************************//**

    Resets the configuration of a timer to generate another match event.

    @param[in]  timer       A pointer to the target timer.
    @param[in]  channel     The timer channel to receive the match event.
    @param[in]  value       The absolute counter value that will generate a match event.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The match event was successfully configured.
     ERR_NULLREFERENCE      | The argument 'timer' was found to be NULL.
     ERR_NOTINITIALIZED     | The specified timer has not been initialized (enabled).
     ERR_NOTSUPPORTED       | The specified timer channel is not supported.
     
    @module     hwtimer-lpc177x8x

*******************************************************************************************************************************************/
extern STATUS HWTIMER_ResetMatch(HWTIMER* timer, UINT32 channel, UINT32 value);

/***************************************************************************************************************************************//**

    Cancels a pending timer match event.

    @param[in]  timer         A pointer to the target timer.
    @param[in]  channel          The timer channel to be cancelled.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The timer match was successfully cancelled.
     ERR_NULLREFERENCE      | The argument 'timer' was found to be NULL.
     ERR_NOTSUPPORTED       | The specified timer channel is not supported.
     ERR_INVALIDOPERATION   | The timer has not been enabled.

    @module     hwtimer-lpc177x8x

*******************************************************************************************************************************************/
extern STATUS HWTIMER_CancelMatch(HWTIMER* timer, UINT32 channel);

/***************************************************************************************************************************************//**

    Configures the external pin response for a timer match event.

    @param[in]  timer       A pointer to the target timer.
    @param[in]  channel     The timer channel to be configured.
    @param[in]  opt         The external match option.

     opt                    | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     OPT_MATCHNONE          | Timer pin will do nothing on a match event.
     OPT_MATCHLOW           | Timer pin will clear and go low on a match event.
     OPT_MATCHHIGH          | Timer pin will set and go high on a match event.
     OPT_MATCHTOGGLE        | Timer pin will toggle on a match event.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The externel pin response has been successfully configured.
     ERR_NULLREFERENCE      | The argument 'timer' was found to be NULL.
     ERR_NOTSUPPORTED       | The specified timer channel is not supported.

    @module     hwtimer-lpc177x8x

*******************************************************************************************************************************************/
extern STATUS HWTIMER_ConfigureExtMatch(HWTIMER* timer, UINT32 channel, UINT32 opt);

#endif /* MCU_HWTIMER_H__ */
