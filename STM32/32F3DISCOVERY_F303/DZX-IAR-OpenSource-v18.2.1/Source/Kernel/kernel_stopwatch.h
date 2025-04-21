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
#ifndef KERNEL_STOPWATCH_H__
#define KERNEL_STOPWATCH_H__

#include "Kernel/kernel.h"

/*******************************************************************************************************************************************
    TYPE DEFINITIONS
*******************************************************************************************************************************************/
typedef struct STOPWATCH STOPWATCH;

/***************************************************************************************************************************************//**

    A stopwatch to be used to accurately measure time intervals using a high resolution counter.
    @module     kernel-stopwatch

*******************************************************************************************************************************************/
struct STOPWATCH {
	UINT32      ts;             /**< The tick value the stopwatch has been started when running. */
    UINT32      elapsed;        /**< Represents an incremental amount of elapsed time while the stopwatch is stopped. */
    BOOLEAN     running;        /**< An indication of whether the stopwatch is currently running. */
};

/*******************************************************************************************************************************************
    PUBLIC FUNCTIONS
*******************************************************************************************************************************************/
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
extern void STOPWATCH_Create(STOPWATCH* sw, UINT32 opt);

/***************************************************************************************************************************************//**

    Starts a stopwatch.

    @param[in]  sw          A pointer to the stopwatch to be started.

    @return     None
    @module     kernel-stopwatch

*******************************************************************************************************************************************/
extern void STOPWATCH_Start(STOPWATCH* sw);

/***************************************************************************************************************************************//**

    Stops a stopwatch.

    @param[in]  sw          A pointer to the stopwatch to be stopped.

    @return     None
    @module     kernel-stopwatch

*******************************************************************************************************************************************/
extern void STOPWATCH_Stop(STOPWATCH* sw);

/***************************************************************************************************************************************//**

    Resets a stopwatch.

    @param[in]  sw          A pointer to the stopwatch to be reset.

    @return     None
    @module     kernel-stopwatch

*******************************************************************************************************************************************/
extern void STOPWATCH_Reset(STOPWATCH* sw);

/***************************************************************************************************************************************//**

    Resets and starts a stopwatch.

    @param[in]  sw          A pointer to the stopwatch to be restarted.

    @return     None
    @module     kernel-stopwatch

*******************************************************************************************************************************************/
extern void STOPWATCH_Restart(STOPWATCH* sw);

/***************************************************************************************************************************************//**

    Returns an indication of whether a stopwatch is currently running.

    @param[in]  sw          A pointer to the target stopwatch.

    @return     TRUE if the stopwatch is currently running; otherwise FALSE.
    @module     kernel-stopwatch

*******************************************************************************************************************************************/
extern BOOLEAN STOPWATCH_IsRunning(const STOPWATCH* sw);

/***************************************************************************************************************************************//**

    Calculates and returns the amount of time in timestamp ticks that has elapsed while the stopwatch has been running.

    @param[in]  sw          A pointer to the target stopwatch.

    @return     The total number of timestamp ticks that have elapsed while the stopwatch has been running.
    @module     kernel-stopwatch

*******************************************************************************************************************************************/
extern UINT32 STOPWATCH_Elapsed(const STOPWATCH* sw);

#endif /* KERNEL_STOPWATCH_H__ */
