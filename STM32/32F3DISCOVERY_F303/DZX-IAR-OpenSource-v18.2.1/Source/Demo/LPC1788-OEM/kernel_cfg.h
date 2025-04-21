/*******************************************************************************************************************************************

    DZX | KERNEL | CONFIGURATION                                                                                          VERSION 18.2.1
    ------------------------------------------------------------------------------------------------------------------------------------

    This provides configuration settings for the kernel.

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
#ifndef KERNEL_CFG_H__
#define KERNEL_CFG_H__


/*******************************************************************************************************************************************
    CORE CONFIGURATION
*******************************************************************************************************************************************/
/*******************************************************************************************************************************************

    KERNEL TICKS PER SECOND         Indicates the number of kernel ticks that occur within a 1 second time interval.

*******************************************************************************************************************************************/
#define CFG_TICKSPERSECOND          1000

/*******************************************************************************************************************************************

    TIMESTAMP TICKS PER SECOND      Indicates the number of timestamp ticks that occur within a 1 second time interval.

*******************************************************************************************************************************************/
#define CFG_TSTICKSPERSECOND        100000000

/*******************************************************************************************************************************************

    DEFAULT TIME SLICE              The initial time slice value, in kernel ticks, for each thread created within the kernel.

*******************************************************************************************************************************************/
#define CFG_DEFAULTTIMESLICE        5

/*******************************************************************************************************************************************

    NUMBER OF BLOCK LISTS           The number of lists used to track the expiry of blocked threads. These lists create a wheel to
                                    reduce searching time of the lists at the expense of memory.

*******************************************************************************************************************************************/
#define CFG_BLOCKLISTS              8

/*******************************************************************************************************************************************

    TICK THREAD PRIORITY            The priority level for the thread that processes the kernel time tick.

*******************************************************************************************************************************************/
#define CFG_TICKPRIORITY            PRIO_HIGHER_7

/*******************************************************************************************************************************************

    TICK THREAD SIGNAL              The signal that is used to signal the kernel tick thread.

*******************************************************************************************************************************************/
#define CFG_TICKSIGNAL              SIGNAL_31

/*******************************************************************************************************************************************

    CALLER CONTEXT CHECKING         Determines whether to include code for checking the context of the caller for functions that do not
                                    support being called from the context of an interrupt service routine (ISR).

*******************************************************************************************************************************************/
#define CFG_CONTEXTCHECKING         TRUE

/*******************************************************************************************************************************************

    NULL REFERENCE CHECKING         Determines whether to include code for checking required function arguments for NULL values.

*******************************************************************************************************************************************/
#define CFG_NULLCHECKING            TRUE

/*******************************************************************************************************************************************

    INLINING                        Determines whether to include inline attributes on the specified functions (requires compiler C99).

*******************************************************************************************************************************************/
#define CFG_INLINING                FALSE





/*******************************************************************************************************************************************
    STACK MEMORY CONFIGURATION
*******************************************************************************************************************************************/
/*******************************************************************************************************************************************

    MAIN THREAD STACK SIZE          The size, in bytes, of the stack memory used by the main application thread.

*******************************************************************************************************************************************/
#define CFG_MAINSTACKSIZE           512

/*******************************************************************************************************************************************

    TICK THREAD STACK SIZE          The size, in bytes, of the stack memory used by the kernel tick thread.

*******************************************************************************************************************************************/
#define CFG_TICKSTACKSIZE           256

/*******************************************************************************************************************************************

    IDLE THREAD STACK SIZE          The size, in bytes, of the stack memory used by the idle thread within the kernel.

*******************************************************************************************************************************************/
#define CFG_IDLESTACKSIZE           192

/*******************************************************************************************************************************************

    ISR STACK SIZE                  The size, in bytes, of the stack memory used by all of the interrupt service routines.

*******************************************************************************************************************************************/
#define CFG_ISRSTACKSIZE            512
    
/*******************************************************************************************************************************************

    STACK FILLING                   Determines whether to include code for initializing stack memory to a known fill-value for the 
                                    purposes of determining a high water mark.
                                    
*******************************************************************************************************************************************/
#define CFG_STACKFILLING            TRUE

/*******************************************************************************************************************************************

    STACK FILL VALUE                Determines the value that is written to stack memory upon initialization for the purposes of 
                                    determining a high water mark.
                                    
*******************************************************************************************************************************************/
#define CFG_STACKFILLVALUE          0xAAAAAAAA




/*******************************************************************************************************************************************
    TIMER CONFIGURATION
*******************************************************************************************************************************************/
/*******************************************************************************************************************************************

    NUMBER OF TIMER LISTS           The number of lists used for tracking running timers. These lists create a wheel to reduce searching
                                    time at the expense of memory.

*******************************************************************************************************************************************/
#define CFG_TIMERLISTS              8

/*******************************************************************************************************************************************

    NUMBER OF TIMER THREADS         The number of threads used by the kernel to call the application-defined timer expiration functions. 
                                    Must be at least one. Use more than one to allow the expiry functions make blocking calls without 
                                    blocking the other timers.

*******************************************************************************************************************************************/
#define CFG_TIMERTHREADS            2

/*******************************************************************************************************************************************

    TIMER THREAD STACK SIZE         The size, in bytes, of the stack memory used by the threads within the kernel that are used to call
                                    the application-defined timer expiration functions.

*******************************************************************************************************************************************/
#define CFG_TIMERSTACKSIZE          512

/*******************************************************************************************************************************************

    TIMER THREAD PRIORITY           The priority for the the threads within the kernel that are used to call the application-defined 
                                    timer expiration functions.

*******************************************************************************************************************************************/
#define CFG_TIMERPRIORITY           PRIO_HIGHER_5

/*******************************************************************************************************************************************

    TIMER THREAD SIGNAL             The signal that is used to signal the threads that call expiration callback handler functions.

*******************************************************************************************************************************************/
#define CFG_TIMERSIGNAL             SIGNAL_31




/*******************************************************************************************************************************************
    STATISTICS CONFIGURATION
*******************************************************************************************************************************************/
/*******************************************************************************************************************************************

    STATISTICS                      Determines whether to include code for keeping runtime statistics on the kernel.

*******************************************************************************************************************************************/
#define CFG_STATISTICS              TRUE

/*******************************************************************************************************************************************

    STATISTICS PRIORITY             The priority level for the statistics thread.

*******************************************************************************************************************************************/
#define CFG_STATPRIORITY            PRIO_NORMAL

/*******************************************************************************************************************************************

    STAT THREAD STACK SIZE          The size, in bytes, of the stack memory used by the statistics thread within the kernel.

*******************************************************************************************************************************************/
#define CFG_STATSTACKSIZE           256

/*******************************************************************************************************************************************

    LOCK STATISTICS                 Determines whether to include code for keeping runtime statistics on interrupt locks.

*******************************************************************************************************************************************/
#define CFG_LOCKSTATISTICS          TRUE

/*******************************************************************************************************************************************

    INTERRUPT STATISTICS            Determines whether to include code for keeping runtime statistics on interrupt service routines.

*******************************************************************************************************************************************/
#define CFG_ISRSTATISTICS           TRUE





/*******************************************************************************************************************************************
    HOOK FUNCTIONS
*******************************************************************************************************************************************/
/*******************************************************************************************************************************************

    HOOK BOOT                       Determines whether to call function 'HOOK_Boot' upon boot entry. This hook function will be called
                                    before any memory initialization and therefore should not depend upon any initial values.

*******************************************************************************************************************************************/
#define CFG_HOOKBOOT                FALSE

/*******************************************************************************************************************************************

    HOOK IDLE                       Determines whether to call function 'HOOK_Idle' upon each idle loop iteration. Since this is called
                                    from within the idle thread, the hook function should not make any blocking calls.

*******************************************************************************************************************************************/
#define CFG_HOOKIDLE                FALSE

/*******************************************************************************************************************************************

    HOOK CONTEXT SWITCH             Determines whether to call function 'HOOK_ContextSwitch' upon each context switch. This funcion is
                                    called from the context switch interrupt.

*******************************************************************************************************************************************/
#define CFG_HOOKCONTEXTSWITCH       FALSE


#endif /* KERNEL_CFG_H__ */
