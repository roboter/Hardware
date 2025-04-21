/*******************************************************************************************************************************************

    DZX | KERNEL | STATISTICS                                                                                             VERSION 18.2.1
    ------------------------------------------------------------------------------------------------------------------------------------

    This file is part of the kernel and provides support for keeping runtime statistics. Runtime statistics can be kept for each of the 
    kernel threads, interrupts and interrupt lock sections. 

    Use CFG_STATISTICS within kernel_cfg.h to enable/disable all of the statistics.

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
#ifndef KERNEL_STAT_H__
#define KERNEL_STAT_H__

#include "Kernel/kernel_types.h"
#include "kernel_cfg.h"

#if (CFG_ISRSTATISTICS)
/*******************************************************************************************************************************************

    Represents run-time statistics for interrupt service routines.
    @module     internal

*******************************************************************************************************************************************/
typedef struct ISRSTATS {
	UINT32 count;
    UINT32 prevcnt;
    UINT32 nesting;
    UINT32 cntpersec;
} ISRSTATS;
#endif /* CFG_ISRSTATISTICS */

#if (CFG_LOCKSTATISTICS)
/*******************************************************************************************************************************************

    Represents run-time statistics for a synchronization lock.
    @module     internal

*******************************************************************************************************************************************/
typedef struct LOCKSTATITEM {
	STOPWATCH   watch;                  /**< A stopwatch for measuring the length of time the lock was active */
	UINT32      nesting;                /**< Level for keeping track of nested lock calls */
	UINT32      max;                    /**< The maximum captured time the lock was active */
} LOCKSTATITEM;

/*******************************************************************************************************************************************

    Represents run-time statistics for both interrupt and thread synchronization locks.
    @module     internal

*******************************************************************************************************************************************/
typedef struct LOCKSTATS {
    LOCKSTATITEM isr;                   /* Interrupt lock stats */
    LOCKSTATITEM thread;                /* Thread lock stats */
} LOCKSTATS;
#endif /* CFG_LOCKSTATISTICS */

#if (CFG_STATISTICS)
/*******************************************************************************************************************************************

    Represents run-time statistics for the kernel.
    @module     internal

*******************************************************************************************************************************************/
typedef struct KERNELSTATS {
    UINT32      ctxcnt;                 /* A count of total number of thread context switches */
    UINT32      prevctxcnt;             /* A count of thread context switches used for calculating switches per second */
    UINT32      ctxpersec;              /* A count of number of thread context switches per second */
    UINT32      cpu;                    /* The current CPU utilization, in units of hundredths of percent */
    STOPWATCH   watch;                  /* A stopwatch used to calculate runtime statistics */
    THREAD      thread;                 /* A thread for periodically calculating statistics */
} KERNELSTATS;
#endif /* CFG_STATISTICS */

/*******************************************************************************************************************************************
    PRIVATE VARIABLES
*******************************************************************************************************************************************/
#if (CFG_ISRSTATISTICS)
extern ISRSTATS isr_stats;              /* Interrupt service routine statistics */
#endif

#if (CFG_LOCKSTATISTICS)
extern LOCKSTATS lock_stats;            /* Lock statistics */
#endif
    
#if (CFG_STATISTICS)
extern KERNELSTATS kernel_stats;
#endif

/*******************************************************************************************************************************************
    PUBLIC FUNCTIONS
*******************************************************************************************************************************************/
/***************************************************************************************************************************************//**

    Gets the current percentage of CPU utilization, in hundreths of percent (i.e. 10000 = 100.00%).

    @return     The CPU utilization percentage.
    @module     kernel-stat

*******************************************************************************************************************************************/
extern UINT32 KERNEL_Utilization(void);

#if (CFG_LOCKSTATISTICS)
/***************************************************************************************************************************************//**

    Gets the maximum amount of time, in timestamp ticks, that an interrupt lock has been held. Use CFG_TSTICKSPERSECOND to convert units.

    @return     The maximum amount of time an interrupt lock has been held.
    @module     kernel-stat

*******************************************************************************************************************************************/
extern UINT32 KERNEL_MaxIsrLock(void);

/***************************************************************************************************************************************//**

    Gets the maximum amount of time, in timestamp ticks, that a thread lock has been held. Use CFG_TSTICKSPERSECOND to convert units.

    @return     The maximum amount of time a thread lock has been held.
    @module     kernel-stat

*******************************************************************************************************************************************/
extern UINT32 KERNEL_MaxThreadLock(void);
#endif /* CFG_LOCKSTATISTICS */

#endif /* KERNEL_STAT_H__ */
