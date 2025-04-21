/*******************************************************************************************************************************************

    DZX | KERNEL | TIMER                                                                                                  VERSION 18.2.1
    ------------------------------------------------------------------------------------------------------------------------------------

    This file is part of the kernel and provides support for timers. A timer provides the ability to execute an application-defined 
    function upon expiration of a time interval. A timer can be reset, started, stopped, or restarted at any time from any code context, 
    including from an interrupt service routine (ISR).

    Use CFG_TIMERLISTS to configure the number of running lists are maintained for sorting the timers. More lists will reduce the time
    it takes to sort the timers at the expense of memory.

    Use CFG_TIMERTHREADS to configure the number of dedicated threads that are used for calling the expiry functions. Note that if only 
    a single thread is used (CFG_TIMERTHREADS = 1) and the expiry function makes a blocking call, it is also blocking all the other 
    timer's expiry functions. Use more than one thread if making blocking calls within expiry functions.

    A timer has the resolution of the kernel tick rate. When specifying a time interval, the accuracy is +1/-0 kernel ticks as the tick 
    time is not synchronized with the starting time of a timer.

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
#ifndef KERNEL_TIMER_H__
#define KERNEL_TIMER_H__

#include "Kernel/kernel_list.h"
#include "Kernel/kernel_thread.h"
#include "Kernel/kernel_stopwatch.h"

/*******************************************************************************************************************************************
    TYPE DEFINITIONS
*******************************************************************************************************************************************/
typedef struct TIMER TIMER;

/***************************************************************************************************************************************//**

    An application-defined function that will be called upon the expiration of a kernel timer.

    @param[in]  timer       A pointer to the timer that has expired.
    @param[in]  state       A pointer to an application-defined argument that was provided when the timer was created.

    @return     None.
    @module     kernel-timer

*******************************************************************************************************************************************/
typedef void (*TIMERCALLBACK)(TIMER* timer, void* state);

/***************************************************************************************************************************************//**

    A kernel timer.
    @module     kernel-timer

*******************************************************************************************************************************************/
struct TIMER {
	NODE            node;           /**< A node to reference the timer within the created timers list */
    const CHAR*     name;           /**< A name for the timer */
    NODE            pendnode;       /**< A node to reference the timer within a pending to run list */
    NODE            runnode;        /**< A node to reference the timer within the running timers list */
    NODE            expnode;        /**< A node to reference the timer within the expired timers list */
    THREAD*         thread;         /**< A pointer to the thread that is executing a callback for the timer */
	UINT32          interval;       /**< The timing interval, in kernel ticks, for the timer */
    UINT32          remainder;      /**< An incremental amount of time remaining for the timer when it has been stopped. */
	UINT32          exptime;        /**< The time value of when the timer will be expired */
	TIMERCALLBACK   callback;       /**< An application-defined function to receive a callback upon expiration of the timer */
	void*           arg;            /**< An optional argument that is passed to the timer callback function */
	UINT32          opt;            /**< Additional options for the timer */
    BOOLEAN         running;        /**< Indication of whether the timer is running */  
#if (CFG_STATISTICS)
    UINT32          expcnt;         /**< Total number of times the timer has expired */
    STOPWATCH       watch;          /**< A stopwatch for measuring callback latency */
    UINT32          latency;        /**< The latency, in timestamp ticks, of the most recent expiration callback */
    UINT32          maxlatency;     /**< The maximum captured latency, in timestamp ticks, of the expiration callback */
#endif
};

/*******************************************************************************************************************************************
    PUBLIC FUNCTIONS
*******************************************************************************************************************************************/
/***************************************************************************************************************************************//**

    Creates and initializes a timer.

    @param[in]  timer       A pointer to a caller allocated timer instance to be initialized.
    @param[in]  name        A pointer to a NULL terminated string that represents the name for the timer.
    @param[in]  callback    A function that will receive a callback when the timer has expired.
    @param[in]  arg         (optional) A user defined argument object that is passed as the callback function argument. Can be NULL.
    @param[in]  interval    The amount of time, in kernel ticks, between the timer's expiration events.
    @param[in]  opt         Additional options to be applied to the timer.
     
     opt                    | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     OPT_NONE               | No options. Create without starting and one-shot mode.
     OPT_START              | Use to have the timer started.
     OPT_AUTORESET          | Use to have the timer automatically reset after each expiration.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The timer has been created and initialized.
     ERR_NULLREFERENCE      | The argument 'timer' or 'callback' was found to be NULL.
     ERR_INVALIDCONTEXT     | The operation is not supported from the context of an interrupt service routine (ISR).
     ERR_INVALIDARGUMENT    | The specified interval must be larger than zero.
     ERR_ALREADYINITIALIZED | The specified timer has already been created and initialized.

    @module     kernel-timer

*******************************************************************************************************************************************/
extern STATUS TIMER_Create(TIMER* timer, const CHAR* name, TIMERCALLBACK callback, void* arg, UINT32 interval, UINT32 opt);

/***************************************************************************************************************************************//**

    Destroys and removes a timer from the kernel.

    @param[in]  timer       A pointer to the timer to be destroyed and removed.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The timer has been destroyed and removed from the kernel.
     ERR_NULLREFERENCE      | The argument 'timer' was found to be NULL.
     ERR_INVALIDCONTEXT     | The operation is not supported from the context of an interrupt service routine (ISR).
     ERR_NOTINITIALIZED     | The specified timer has not been created and initialized.
     ERR_ACCESSDENIED       | The specified timer is currently executing it's callback function.

    @module     kernel-timer

*******************************************************************************************************************************************/
extern STATUS TIMER_Destroy(TIMER* timer);

/***************************************************************************************************************************************//**

    Starts a timer.

    @param[in]  timer       A pointer to the timer to be started.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The timer has been started.
     ERR_NULLREFERENCE      | The argument 'timer' was found to be NULL.
     ERR_NOTINITIALIZED     | The specified timer has not been created and initialized.

    @remark     If the timer is not expired, it will resume where it has last been stopped. Use TIMER_Restart() if starting the timer
                over with a fresh complete timing period is the desired operation.
    @module     kernel-timer

*******************************************************************************************************************************************/
extern STATUS TIMER_Start(TIMER* timer);

/***************************************************************************************************************************************//**

    Stops a timer.

    @param[in]  timer       A pointer to the timer to be stopped.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The timer has been stopped.
     ERR_NULLREFERENCE      | The argument 'timer' was found to be NULL.
     ERR_NOTINITIALIZED     | The specified timer has not been created and initialized.

    @remark     The timer's remaining time interval is left unchanged.
    @module     kernel-timer

*******************************************************************************************************************************************/
extern STATUS TIMER_Stop(TIMER* timer);

/***************************************************************************************************************************************//**

    Resets a timer by giving the timer a new full time interval. This will leave the timer in it's current state.

    @param[in]  timer       A pointer to the timer to be reset.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The timer was reset with a full interval.
     ERR_NULLREFERENCE      | The argument 'timer' was found to be NULL.
     ERR_NOTINITIALIZED     | The specified timer has not been created and initialized.

    @module     kernel-timer

*******************************************************************************************************************************************/
extern STATUS TIMER_Reset(TIMER* timer);

/***************************************************************************************************************************************//**

    Resets and starts a timer.

    @param[in]  timer       A pointer to the timer to be restarted.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The timer has been reset with a full interval and started.
     ERR_NULLREFERENCE      | The argument 'timer' was found to be NULL.
     ERR_NOTINITIALIZED     | The specified timer has not been created and initialized.

    @module     kernel-timer

*******************************************************************************************************************************************/
extern STATUS TIMER_Restart(TIMER* timer);

/***************************************************************************************************************************************//**

    Sets a new timing interval, in kernel ticks, for a timer.

    @param[in]  timer           A pointer to the timer to receive the new interval value.
    @param[in]  interval        The new interval value for the timer. Must be greater than zero.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The timer has been updated with the new interval value.
     ERR_NULLREFERENCE      | The argument 'timer' was found to be NULL.
     ERR_INVALIDARGUMENT    | The argument 'interval' was invalid. Must be greater than zero.
     ERR_NOTINITIALIZED     | The specified timer has not been created and initialized.

    @module     kernel-timer

*******************************************************************************************************************************************/
extern STATUS TIMER_SetInterval(TIMER* timer, UINT32 interval);

/***************************************************************************************************************************************//**

    Returns an indication of whether a timer is currently running.

    @param[in]  timer       A pointer to the timer to be checked for running status.

    @return     TRUE if the timer is currently running; otherwise FALSE.
    @module     kernel-timer

*******************************************************************************************************************************************/
extern BOOLEAN TIMER_IsRunning(TIMER* timer);

#endif /* KERNEL_TIMER_H__ */
