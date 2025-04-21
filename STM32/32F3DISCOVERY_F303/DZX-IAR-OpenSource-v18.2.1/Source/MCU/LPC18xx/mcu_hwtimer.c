/*******************************************************************************************************************************************

    DZX | LPC18xx | HARDWARE TIMER                                                                                        VERSION 18.2.1
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
#include "mcu_hwtimer.h"
#include "mcu_irq.h"

/*******************************************************************************************************************************************
    PRIVATE VARIABLES
*******************************************************************************************************************************************/
static HWTIMER* mcu_timer[4];       /* Pointers to each of the hardware timers */

/*******************************************************************************************************************************************
    PRIVATE FUNCTIONS
*******************************************************************************************************************************************/
static void HWTIMER_ISR(IRQ irq);

/***************************************************************************************************************************************//**

    Enables a hardware timer.

    @param[in]  timer       A pointer to a caller allocated timer to be initialized.
    @param[in]  number      The number of the timer to be enabled (0-3).

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The timer was successfully initialized and configured.
     ERR_NULLREFERENCE      | The argument 'timer' was found to be NULL.
     ERR_NOTSUPPORTED       | The timer number is not supported.

    @module     hwtimer-lpc18xx

*******************************************************************************************************************************************/
STATUS HWTIMER_Enable(HWTIMER* timer, UINT32 number)
{
    INTERRUPTLOCK lock;


#if (CFG_NULLCHECKING)
    if (timer == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif

    switch (number) {                                       /* Find the timer by number */
        case 0:
            timer->REG = REG_TIMER0;
            break;
        case 1:
            timer->REG = REG_TIMER1;
            break;
        case 2:
            timer->REG = REG_TIMER2;
            break;
        case 3:
            timer->REG = REG_TIMER3;
            break;
        default:
            return ERR_NOTSUPPORTED;
    }

    timer->number = number;

    timer->REG->TCR.VALUE = 2;                          /* Stop and reset the timer */
    timer->REG->TCR.VALUE = 1;                          /* Release the timer */

    switch (number) {                                   /* Enable interrupts for the timer */
        case 0:
            IRQ_RegisterHandler(IRQ_TIMER0, HWTIMER_ISR);
            IRQ_Enable(IRQ_TIMER0);
            break;
        case 1:
            IRQ_RegisterHandler(IRQ_TIMER1, HWTIMER_ISR);
            IRQ_Enable(IRQ_TIMER1);
            break;
        case 2:
            IRQ_RegisterHandler(IRQ_TIMER2, HWTIMER_ISR);
            IRQ_Enable(IRQ_TIMER2);
            break;
        case 3:
            IRQ_RegisterHandler(IRQ_TIMER3, HWTIMER_ISR);
            IRQ_Enable(IRQ_TIMER3);
            break;
    }

    ACQUIREINTERRUPTLOCK();

    mcu_timer[number] = timer;                          /* Keep a reference of the enabled timer */

    RELEASEINTERRUPTLOCK();
    return SUCCESS;
}

/***************************************************************************************************************************************//**

    Disables a hardware timer.

    @param[in]  timer       A pointer to the timer to be disabled.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The timer has been disabled.
     ERR_NULLREFERENCE      | The argument 'timer' was found to be NULL.

    @module     hwtimer-lpc18xx

*******************************************************************************************************************************************/
STATUS HWTIMER_Disable(HWTIMER* timer)
{
    INTERRUPTLOCK lock;


#if (CFG_NULLCHECKING)
    if (timer == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif

    ACQUIREINTERRUPTLOCK();

    if (timer != mcu_timer[timer->number]) {
        RELEASEINTERRUPTLOCK();
        return ERR_NOTINITIALIZED;
    }

    switch (timer->number) {                        /* Disable interrupts for the timer */
        case 0:
            IRQ_Disable(IRQ_TIMER0);
            break;
        case 1:
            IRQ_Disable(IRQ_TIMER1);
            break;
        case 2:
            IRQ_Disable(IRQ_TIMER2);
            break;
        case 3:
            IRQ_Disable(IRQ_TIMER3);
            break;
        default:
            return ERR_NULLREFERENCE;
    }

    mcu_timer[timer->number] = NULL;

    RELEASEINTERRUPTLOCK();
    return SUCCESS;
}

/***************************************************************************************************************************************//**

    Reads and returns a hardware timer's current counter value.

    @param[in]  timer       A pointer to the hardware timer to be read.

    @return     The current counter value for the given timer.
    @module     hwtimer-lpc18xx

*******************************************************************************************************************************************/
UINT32 HWTIMER_Counter(HWTIMER* timer)
{
#if (CFG_NULLCHECKING)
    if (timer == NULL) {
        return 0;
    }
#endif

    return timer->REG->TC;
}

/***************************************************************************************************************************************//**

    Reads and returns the capture value for a hardware timer channel.

    @param[in]  timer       A pointer to the hardware timer to be read.
    @param[in]  channel     The timer channel to be read.

    @return     The capture value for the given timer.
    @module     hwtimer-lpc18xx

*******************************************************************************************************************************************/
UINT32 HWTIMER_Capture(HWTIMER* timer, UINT32 channel)
{
#if (CFG_NULLCHECKING)
    if (timer == NULL) {
        return 0;
    }
#endif

    switch (channel) {
        case 0:
            return timer->REG->CR0;
        case 1:
            return timer->REG->CR1;
    }

    return 0;
}

/***************************************************************************************************************************************//**

    Reads and returns the match value for a hardware timer channel.

    @param[in]  timer       A pointer to the hardware timer to be read.
    @param[in]  channel     The timer channel to be read.

    @return     The match value for the given timer.
    @module     hwtimer-lpc18xx

*******************************************************************************************************************************************/
UINT32 HWTIMER_Match(HWTIMER* timer, UINT32 channel)
{
#if (CFG_NULLCHECKING)
    if (timer == NULL) {
        return 0;
    }
#endif

    switch (channel) {
        case 0:
            return timer->REG->MR0;
        case 1:
            return timer->REG->MR1;
        case 2:
            return timer->REG->MR2;
        case 3:
            return timer->REG->MR3;
    }

    return 0;
}

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
    @module     hwtimer-lpc18xx

*******************************************************************************************************************************************/
STATUS HWTIMER_CreateCapture(HWTIMER* timer, UINT32 channel, EDGE edge, HWTIMERCALLBACK callback, void* state)
{
    INTERRUPTLOCK lock;


#if (CFG_NULLCHECKING)
    if (timer == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif
    
    if (timer != mcu_timer[timer->number]) {
        return ERR_NOTINITIALIZED;
    }

    ACQUIREINTERRUPTLOCK();

    switch (channel) {
        case 0:
            timer->args[TIMERCAPTURE0] = state;
            timer->callbacks[TIMERCAPTURE0] = callback;
            timer->REG->CCR.BITS.CAP0FE = (edge & EDGE_FALLING) ? 1 : 0;
            timer->REG->CCR.BITS.CAP0RE = (edge & EDGE_RISING) ? 1 : 0;
            timer->REG->CCR.BITS.CAP0I = 1;
            break;
        case 1:
            timer->args[TIMERCAPTURE1] = state;
            timer->callbacks[TIMERCAPTURE1] = callback;
            timer->REG->CCR.BITS.CAP1FE = (edge & EDGE_FALLING) ? 1 : 0;
            timer->REG->CCR.BITS.CAP1RE = (edge & EDGE_RISING) ? 1 : 0;
            timer->REG->CCR.BITS.CAP1I = 1;
            break;
         default:
            RELEASEINTERRUPTLOCK();
            return ERR_NOTSUPPORTED;
    }

    RELEASEINTERRUPTLOCK();
    return SUCCESS;
}

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

    @module     hwtimer-lpc18xx

*******************************************************************************************************************************************/
STATUS HWTIMER_CancelCapture(HWTIMER* timer, UINT32 channel)
{
    INTERRUPTLOCK lock;


#if (CFG_NULLCHECKING)
    if (timer == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif
    

    ACQUIREINTERRUPTLOCK();

    switch (channel) {
        case 0:
            timer->REG->CCR.BITS.CAP0I = 0;
            break;
        case 1:
            timer->REG->CCR.BITS.CAP1I = 0;
            break;
        default:
            RELEASEINTERRUPTLOCK();
            return ERR_NOTSUPPORTED;
    }

    RELEASEINTERRUPTLOCK();
    return SUCCESS;
}

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
     
    @module     hwtimer-lpc18xx

*******************************************************************************************************************************************/
STATUS HWTIMER_CreateMatch(HWTIMER* timer, UINT32 channel, UINT32 value, HWTIMERCALLBACK callback, void* arg, UINT32 opt)
{
    INTERRUPTLOCK lock;


#if (CFG_NULLCHECKING)
    if (timer == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif

    if (timer != mcu_timer[timer->number]) {
        return ERR_NOTINITIALIZED;
    }
    
    
    ACQUIREINTERRUPTLOCK();

    switch (channel) {
        case 0:
            timer->args[TIMERMATCH0] = arg;
            timer->callbacks[TIMERMATCH0] = callback;
            timer->REG->MR0 = value;
            timer->REG->MCR.BITS.MR0I = 1;
            timer->REG->MCR.BITS.MR0R = (opt & OPT_MATCHRESET) ? 1 : 0;
            timer->REG->MCR.BITS.MR0S = (opt & OPT_MATCHSTOP) ? 1 : 0;
            break;
        case 1:
            timer->args[TIMERMATCH1] = arg;
            timer->callbacks[TIMERMATCH1] = callback;
            timer->REG->MR1 = value;
            timer->REG->MCR.BITS.MR1I = 1;
            timer->REG->MCR.BITS.MR1R = (opt & OPT_MATCHRESET) ? 1 : 0;
            timer->REG->MCR.BITS.MR1S = (opt & OPT_MATCHSTOP) ? 1 : 0;
            break;
        case 2:
            timer->args[TIMERMATCH2] = arg;
            timer->callbacks[TIMERMATCH2] = callback;
            timer->REG->MR2 = value;
            timer->REG->MCR.BITS.MR2I = 1;
            timer->REG->MCR.BITS.MR2R = (opt & OPT_MATCHRESET) ? 1 : 0;
            timer->REG->MCR.BITS.MR2S = (opt & OPT_MATCHSTOP) ? 1 : 0;
            break;
        case 3:
            timer->args[TIMERMATCH3] = arg;
            timer->callbacks[TIMERMATCH3] = callback;
            timer->REG->MR3 = value;
            timer->REG->MCR.BITS.MR3I = 1;
            timer->REG->MCR.BITS.MR3R = (opt & OPT_MATCHRESET) ? 1 : 0;
            timer->REG->MCR.BITS.MR3S = (opt & OPT_MATCHSTOP) ? 1 : 0;
            break;
        default:
            RELEASEINTERRUPTLOCK();
            return ERR_NOTSUPPORTED;
    }

    RELEASEINTERRUPTLOCK();
    return SUCCESS;
}

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
     
    @module     hwtimer-lpc18xx

*******************************************************************************************************************************************/
STATUS HWTIMER_ResetMatch(HWTIMER* timer, UINT32 channel, UINT32 value)
{
    INTERRUPTLOCK lock;
    
    
#if (CFG_NULLCHECKING)
    if (timer == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif

    if (timer != mcu_timer[timer->number]) {
        return ERR_NOTINITIALIZED;
    }    
    
    ACQUIREINTERRUPTLOCK();

    switch (channel) {
        case 0:
            timer->REG->MR0 = value;
            timer->REG->MCR.BITS.MR0I = 1;
            break;
        case 1:
            timer->REG->MR1 = value;
            timer->REG->MCR.BITS.MR1I = 1;
            break;
        case 2:
            timer->REG->MR2 = value;
            timer->REG->MCR.BITS.MR2I = 1;
            break;
        case 3:
            timer->REG->MR3 = value;
            timer->REG->MCR.BITS.MR3I = 1;
            break;
        default:
            RELEASEINTERRUPTLOCK();
            return ERR_NOTSUPPORTED;
    }

    RELEASEINTERRUPTLOCK();
    return SUCCESS;
}

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

    @module     hwtimer-lpc18xx

*******************************************************************************************************************************************/
STATUS HWTIMER_CancelMatch(HWTIMER* timer, UINT32 channel)
{
    INTERRUPTLOCK lock;


#if (CFG_NULLCHECKING)
    if (timer == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif

    ACQUIREINTERRUPTLOCK();

    switch (channel) {
        case 0:
            timer->REG->MCR.BITS.MR0I = 0;
            break;
        case 1:
            timer->REG->MCR.BITS.MR1I = 0;
            break;
        case 2:
            timer->REG->MCR.BITS.MR2I = 0;
            break;
        case 3:
            timer->REG->MCR.BITS.MR3I = 0;
            break;
        default:
            RELEASEINTERRUPTLOCK();
            return ERR_NOTSUPPORTED;
    }

    RELEASEINTERRUPTLOCK();
    return SUCCESS;
}

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

    @module     hwtimer-lpc18xx

*******************************************************************************************************************************************/
STATUS HWTIMER_ConfigureExtMatch(HWTIMER* timer, UINT32 channel, UINT32 opt)
{
    INTERRUPTLOCK lock;


#if (CFG_NULLCHECKING)
    if (timer == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif

    ACQUIREINTERRUPTLOCK();

    switch (channel) {
        case 0:
            timer->REG->EMR.BITS.EMC0 = opt;
            break;
        case 1:
            timer->REG->EMR.BITS.EMC1 = opt;
            break;
        case 2:
            timer->REG->EMR.BITS.EMC2 = opt;
            break;
        case 3:
            timer->REG->EMR.BITS.EMC3 = opt;
            break;
        default:
            RELEASEINTERRUPTLOCK();
            return ERR_NOTSUPPORTED;
    }

    RELEASEINTERRUPTLOCK();
    return SUCCESS;
}

/***************************************************************************************************************************************//**

    The handler for processing a hardware timer interrupt request.

    @param[in]  irq         The interrupt request to be handled.

    @return     None.
    @module     internal

*******************************************************************************************************************************************/
static void HWTIMER_ISR(IRQ irq)
{
    TIMEREVENT event;
    UINT32 value;
    HWTIMER* timer;
    
    
    timer = mcu_timer[irq - IRQ_TIMER0];                            /* Get the timer for the interrupt request */
    
    for (event = TIMERMATCH0; event < TIMEREVENTMAX; event++) {     /* Check for all possible events */
        if (timer->REG->IR.VALUE & BIT(event)) {                    /* Check for active interrupt */
            switch (event) {
                default:
                case TIMERCAPTURE0:
                    value = timer->REG->CR0;
                    break;
                case TIMERCAPTURE1:
                    value = timer->REG->CR1;
                    break;
                case TIMERMATCH0:
                    timer->REG->MCR.BITS.MR0I = 0;
                    value = timer->REG->MR0;
                    break;
                case TIMERMATCH1:
                    timer->REG->MCR.BITS.MR1I = 0;
                    value = timer->REG->MR1;
                    break;
                case TIMERMATCH2:
                    timer->REG->MCR.BITS.MR2I = 0;
                    value = timer->REG->MR2;
                    break;
                case TIMERMATCH3:
                    timer->REG->MCR.BITS.MR3I = 0;
                    value = timer->REG->MR3;
                    break;
            }
            
            if (timer->callbacks[event]) {                      /* Call the callback */
                timer->callbacks[event](timer,
                                        (UINT32)(event % 4),
                                        timer->args[event],
                                        value);
            }

            timer->REG->IR.VALUE = (1 << event);                                 /* Clear interrupt */
        }
    }
}
