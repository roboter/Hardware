/*******************************************************************************************************************************************

    DZX | KERNEL | STOPWATCH                                                                                              VERSION 18.2.1
    ------------------------------------------------------------------------------------------------------------------------------------

    This file is part of the kernel and provides support for stopwatches. A stopwatch provides the ability to measure a time interval 
    using a high resolution timestamp counter. A stopwatch uses the KERNEL_Timestamp() call to acquire a timestamp whenever the watch is 
    started or stopped. The accuracy and maximum interval that a stopwatch can measure depends upon the implementation of the 
    KERNEL_Timestamp() functionality. 

    Use CFG_TSTICKSPERSECOND in kernel_cfg.h to determine the resolution and maximum measurable interval for a stopwatch. For example, if 
    CFG_TSTICKSPERSECOND is set to 100,000,000 (100Mhz); the stopwatch would have a resolution of 0.010 microseconds, and if stored as
    a 32-bit counter, it would be limited to measuring intervals less than ~42.949 seconds (2^32 / 100Mhz).

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
#include "kernel_stopwatch.h"

/***************************************************************************************************************************************//**

    Creates and initializes a stopwatch.

    @param[in]  sw          A pointer to a caller allocated stopwatch instance to be initialized.
    @param[in]  opt         Additional options applied when the stopwatch is being created.

     opt                    | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     OPT_NONE               | No additional options.
     OPT_START              | Indicates to start the stopwatch after creation.

    @return     None.
    @remark     Not thread safe.
    @module     kernel-stopwatch

*******************************************************************************************************************************************/
void STOPWATCH_Create(STOPWATCH* sw, UINT32 opt)
{
    sw->elapsed = 0;                                            /* Initialize */

    if (opt & OPT_START) {                                      /* Start the stopwatch? */
        sw->running = TRUE;                                     /* Yes, start it */
        sw->ts = KERNEL_Timestamp();                            /* Get the initial time */
    } else {
        sw->running = FALSE;                                        /* Don't start */
        sw->ts = 0;
    }
}

/***************************************************************************************************************************************//**

    Starts a stopwatch.

    @param[in]  sw          A pointer to the stopwatch to be started.

    @return     None
    @module     kernel-stopwatch

*******************************************************************************************************************************************/
INLINE void STOPWATCH_Start(STOPWATCH* sw)
{
    if (sw->running == FALSE) {                                 /* Only start if not already running */
        sw->ts = KERNEL_Timestamp();                            /* Capture the start time */
        sw->running = TRUE;
    }
}

/***************************************************************************************************************************************//**

    Stops a stopwatch.

    @param[in]  sw          A pointer to the stopwatch to be stopped.

    @return     None
    @module     kernel-stopwatch

*******************************************************************************************************************************************/
INLINE void STOPWATCH_Stop(STOPWATCH* sw)
{
    if (sw->running) {                                          /* Only stop if already running */
        sw->elapsed += (KERNEL_Timestamp() - sw->ts);           /* Accumulate the elapsed time */
        sw->running = FALSE;
    }
}

/***************************************************************************************************************************************//**

    Returns an indication of whether a stopwatch is currently running.

    @param[in]  sw          A pointer to the target stopwatch.

    @return     TRUE if the stopwatch is currently running; otherwise FALSE.
    @module     kernel-stopwatch

*******************************************************************************************************************************************/
INLINE BOOLEAN STOPWATCH_IsRunning(const STOPWATCH* sw)
{
    return sw->running;
}

/***************************************************************************************************************************************//**

    Resets a stopwatch.

    @param[in]  sw          A pointer to the stopwatch to be reset.

    @return     None
    @module     kernel-stopwatch

*******************************************************************************************************************************************/
INLINE void STOPWATCH_Reset(STOPWATCH* sw)
{
    sw->elapsed = 0;
    sw->ts = KERNEL_Timestamp();
}

/***************************************************************************************************************************************//**

    Resets and starts a stopwatch.

    @param[in]  sw          A pointer to the stopwatch to be restarted.

    @return     None
    @module     kernel-stopwatch

*******************************************************************************************************************************************/
INLINE void STOPWATCH_Restart(STOPWATCH* sw)
{
    sw->elapsed = 0;
    sw->ts = KERNEL_Timestamp();
    sw->running = TRUE;
}

/***************************************************************************************************************************************//**

    Calculates and returns the amount of time in timestamp ticks that has elapsed while the stopwatch has been running.

    @param[in]  sw          A pointer to the target stopwatch.

    @return     The total number of timestamp ticks that have elapsed while the stopwatch has been running.
    @module     kernel-stopwatch

*******************************************************************************************************************************************/
INLINE UINT32 STOPWATCH_Elapsed(const STOPWATCH* sw)
{
    if (sw->running) {
        return (UINT32)(sw->elapsed + (KERNEL_Timestamp() - sw->ts));
    }
    
    return sw->elapsed;
}
