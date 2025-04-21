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
#include "kernel_core.h"
#include "kernel_stat.h"


/*******************************************************************************************************************************************
    PRIVATE VARIABLES
*******************************************************************************************************************************************/
#if (CFG_ISRSTATISTICS)
ISRSTATS isr_stats;              /* Interrupt service routine statistics */
#endif

#if (CFG_LOCKSTATISTICS)
LOCKSTATS lock_stats;            /* Lock statistics */
#endif

#if (CFG_STATISTICS)
KERNELSTATS kernel_stats;        /* Information for keeping run-time statistics */
#endif


#if (CFG_STATISTICS)
/*******************************************************************************************************************************************
    PRIVATE FUNCTIONS
*******************************************************************************************************************************************/
static void STAT_Process(void* arg);
static void STAT_ProcessCounters(void);
static THREAD* STAT_NextThread(void);

/*******************************************************************************************************************************************

    Initializes runtime statistics for the kernel.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The statistics have been successfully initialized.

    @remark     Called by KERNEL_Execute() and not to be called by user code.
    @module     kernel-core

*******************************************************************************************************************************************/
STATUS KERNEL_InitializeStats(void)
{
    ALIGNED(8) static BYTE kernel_stats_stk[CFG_STATSTACKSIZE];
    STATUS status;

    
    kernel_stats.ctxcnt = 0;
    kernel_stats.prevctxcnt = 0;
    kernel_stats.ctxpersec = 0;
    
    STOPWATCH_Create(&kernel_stats.watch, OPT_START);
    
#if (CFG_LOCKSTATISTICS)
    lock_stats.isr.nesting = 0;
    lock_stats.isr.max = 0;
    STOPWATCH_Create(&lock_stats.isr.watch, OPT_NONE);
    
    lock_stats.thread.nesting = 0;
    lock_stats.thread.max = 0;
    STOPWATCH_Create(&lock_stats.thread.watch, OPT_NONE);
#endif
    
    status = THREAD_Create(&kernel_stats.thread,
                           "Kernel Stat",
                           kernel_stats_stk,
                           CFG_STATSTACKSIZE,
                           CFG_STATPRIORITY);
    
    if (status != SUCCESS) {
        return status;
    }
                           
    status = THREAD_Start(&kernel_stats.thread,
                          STAT_Process,
                          NULL);
    
    if (status != SUCCESS) {
        return status;
    }
    
    return SUCCESS;
}

/***************************************************************************************************************************************//**

    Gets the current percentage of CPU utilization, in hundreths of percent (i.e. 10000 = 100.00%).

    @return     The CPU utilization percentage.
    @module     kernel-stat

*******************************************************************************************************************************************/
UINT32 KERNEL_Utilization(void)
{
    return kernel_stats.cpu;
}

#if (CFG_LOCKSTATISTICS)
/***************************************************************************************************************************************//**

    Gets the maximum amount of time, in timestamp ticks, that an interrupt lock has been held. Use CFG_TSTICKSPERSECOND to convert units.

    @return     The maximum amount of time an interrupt lock has been held.
    @module     kernel-stat

*******************************************************************************************************************************************/
UINT32 KERNEL_MaxIsrLock(void)
{
    return lock_stats.isr.max;
}

/***************************************************************************************************************************************//**

    Gets the maximum amount of time, in timestamp ticks, that a thread lock has been held. Use CFG_TSTICKSPERSECOND to convert units.

    @return     The maximum amount of time a thread lock has been held.
    @module     kernel-stat

*******************************************************************************************************************************************/
UINT32 KERNEL_MaxThreadLock(void)
{
    return lock_stats.thread.max;
}
#endif

/*******************************************************************************************************************************************

    A process for keeping runtime statistics for the system.

    @return     None.
    @remark     Called from the idle loop and not to be called from user code.
    @module     internal

*******************************************************************************************************************************************/
static void STAT_Process(void* arg)
{
    INTERRUPTLOCK lock;
    THREAD* thread;
    UINT64 interval;
    UINT64 t1;
    UINT32 usage;
    
    
    
    for (;;) {
        
        STAT_ProcessCounters();    
                                  
        KERNEL_AcquireLock();                                       /* Lock the threads while searching */

        thread = STAT_NextThread();                                 /* Find a thread to calc stats upon */
        while (thread) {
            
            ACQUIREINTERRUPTLOCK();
            interval = STOPWATCH_Elapsed(&thread->stats.statsw);    /* Capture the time elapsed since last measurement for the thread */
            STOPWATCH_Restart(&thread->stats.statsw);               /* Yes, reset the elapsed time */
            
            t1 = STOPWATCH_Elapsed(&thread->stats.runsw);           /* Capture the total amount of time the thread has executed */
            RELEASEINTERRUPTLOCK();
            
            t1 += (interval / 20000);                               /* Round up (in units of hundredths of percent) */
            t1 *= 10000;                                            /* Scale up for precision */

            usage = (UINT32)((UINT64)(t1 / (UINT64)interval));      /* Calculate as a percentage */
            if (usage > 10000) {                                    /* Bound to 100.00% */
                usage = 10000;
            }
            
            ACQUIREINTERRUPTLOCK();
            
            thread->stats.exetime += thread->stats.runsw.elapsed;   /* Accumulate total time the thread has executed */
            STOPWATCH_Reset(&thread->stats.runsw);                  /* Reset the watch for measuring execution time */
            
            thread->stats.usage = usage;                            /* Store the usage for query */
            
            RELEASEINTERRUPTLOCK();
            
            if (thread == &kernel.idle) {
                ACQUIREINTERRUPTLOCK();
                kernel_stats.cpu = 10000 - kernel.idle.stats.usage; /* CPU utilization is the time NOT at idle (100.00% - idle usage) */
                RELEASEINTERRUPTLOCK();
            }
            
            KERNEL_ReleaseLock();
            KERNEL_AcquireLock(); 
            
            thread = STAT_NextThread();
        } 
        
        KERNEL_ReleaseLock();
        THREAD_Sleep(MILLISECOND_TICKS(250));                        /* No threads to process, wait a bit */
    }
}

/*******************************************************************************************************************************************

    Finds and returns the next thread to calculate statistics upon.

    @return     A pointer to a thread that needs a statistics update, if any; otherwise NULL.
    @module     internal

*******************************************************************************************************************************************/
static THREAD* STAT_NextThread(void)
{
    INTERRUPTLOCK lock;
    UINT32 interval;
    THREAD* thread;
    NODE* node;
    
    
    LIST_Foreach(node, &kernel.threads) {
        thread = node->value;
           
        ACQUIREINTERRUPTLOCK();
        
        interval = STOPWATCH_Elapsed(&thread->stats.statsw);
        if (interval > (CFG_TSTICKSPERSECOND / 50)) {
            RELEASEINTERRUPTLOCK();
            return thread;
        }
        
        RELEASEINTERRUPTLOCK();
    }
    
    return NULL;
}

/*******************************************************************************************************************************************

    A process for calculating context switches and interrupts per second.

    @return     None.
    @module     internal

*******************************************************************************************************************************************/
static void STAT_ProcessCounters(void)
{
    INTERRUPTLOCK lock;
    UINT32 num;
    UINT32 interval;

    
    ACQUIREINTERRUPTLOCK();
    
    interval = STOPWATCH_Elapsed(&kernel_stats.watch);
    
    if (interval < (CFG_TSTICKSPERSECOND / 50)) {
        RELEASEINTERRUPTLOCK();
        return;
    }
    
    if (interval == 0) {
        RELEASEINTERRUPTLOCK();
        return;
    }
    
    STOPWATCH_Restart(&kernel_stats.watch);
    
    num = kernel_stats.ctxcnt - kernel_stats.prevctxcnt;
    kernel_stats.ctxpersec = num * (CFG_TSTICKSPERSECOND / interval);
    kernel_stats.prevctxcnt = kernel_stats.ctxcnt;
    
    RELEASEINTERRUPTLOCK();
    
#if (CFG_ISRSTATISTICS)
    ACQUIREINTERRUPTLOCK();
    
    num = isr_stats.count - isr_stats.prevcnt;
    isr_stats.cntpersec = num * (CFG_TSTICKSPERSECOND / interval);
    isr_stats.prevcnt = isr_stats.count;
    
    RELEASEINTERRUPTLOCK();
#endif
}
#endif /* CFG_STATISTICS */
