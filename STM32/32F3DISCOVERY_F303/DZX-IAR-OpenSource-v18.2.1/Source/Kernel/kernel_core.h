/*******************************************************************************************************************************************

    DZX | KERNEL | CORE                                                                                                   VERSION 18.2.1
    ------------------------------------------------------------------------------------------------------------------------------------

    This file provides an interface for the internal functionality for the real-time kernel. This interface is to be used by internal 
    kernel components and is not intended to be referenced by applications.

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
#ifndef KERNEL_CORE_H__
#define KERNEL_CORE_H__

#include "kernel_list.h"
#include "kernel_thread.h"
#include "kernel_signal.h"
#include "kernel_stat.h"
#include "kernel_mutex.h"

/*******************************************************************************************************************************************
    DEFINITIONS
*******************************************************************************************************************************************/
#define KERNEL_MAJORVERSION        18
#define KERNEL_MINORVERSION        2
#define KERNEL_REVISION            1

#define PRIO_MAX                    (PRIO_HIGHER_7 + 1)
#define FLAG_THREADABORTED          (UINT32)1

/*******************************************************************************************************************************************
    CORE TYPES
*******************************************************************************************************************************************/
/*******************************************************************************************************************************************

    Internal kernel information.
    @module     internal

*******************************************************************************************************************************************/
typedef struct KERNEL {
    THREAD*         thread;                     /* A pointer to the current executing thread */
    THREAD*         next;                       /* A pointer to the next thread to be executing when performing a context switch */
    LIST            threads;                    /* A list of all the threads within the kernel */
    LIST            ready[PRIO_MAX];            /* An array of lists of the threads that are ready (not-blocked) to run */
    LIST            pending;                    /* A list of threads blocked pending to be sorted by expiry time */
    LIST            blocked[CFG_BLOCKLISTS];    /* An array of lists that hold the threads that are currently blocked (wheel) */
    UINT32          prio;                       /* The priority of the current executing thread */
    SIGNALSET       signals;                    /* Signals for the kernel */
    volatile UINT32 ticks;                      /* The current system time, in kernel ticks */
    THREAD          idle;                       /* The idle thread for the kernel */
    THREAD          main;                       /* The main thread for the application */
    THREAD          tick;                       /* The thread for processing the kernel tick */
    THREADLOCK      lock;                       /* A lock for disabling preemption */
    MUTEX           mutex;                      /* A mutex to lock internal thread lists */
    const KERNELINFO* info;                     /* A pointer to information about the kernel */
} KERNEL;

/*******************************************************************************************************************************************
    CORE VARIABLES
*******************************************************************************************************************************************/
extern KERNEL kernel;

/*******************************************************************************************************************************************
    CORE FUNCTIONS
*******************************************************************************************************************************************/
/*******************************************************************************************************************************************

    Signals the kernel to process the next time tick.

    @return     None
    @module     internal

*******************************************************************************************************************************************/
extern void KERNEL_SignalTick(void);

/***************************************************************************************************************************************//**

    Handler for a callback that occurs upon each context switch within the kernel.

    @param[in]  prev        A pointer to the thread that was previously executing.
    @param[in]  next        A pointer to the thread that is next to execute.

    @return     None.
    @module     internal

*******************************************************************************************************************************************/
extern void KERNEL_OnContextSwitch(void);

/*******************************************************************************************************************************************

    A handler called upon when a thread completes execution and returns from its process function. This handler terminates the thread to
    ensure clean-up of the thread.

    @return     None
    @remark     NOT to be called directly from code.
    @module     internal

*******************************************************************************************************************************************/
extern void KERNEL_OnThreadExit(void);

/*******************************************************************************************************************************************

    Places a thread into the specified state.

    @param[in]  thread      A pointer to the thread to change state.
    @param[in]  state       The new state for the given thread.

    @return     None
    @remark     Not thread or interrupt safe, must be called within active interrupt lock.
    @module     internal

*******************************************************************************************************************************************/
extern void KERNEL_SetState(THREAD* thread, THREADSTATE state);

/*******************************************************************************************************************************************

    Invokes a context switch by performing a search for the highest priority or next ready to run thread that should be executing. If a
    thread is found that is different than the current, a context switch is performed.

    @return     None
    @module     internal

*******************************************************************************************************************************************/
extern void KERNEL_ContextSwitch(void);

/***************************************************************************************************************************************//**

    Removes and releases the first thread from a list of blocked threads.

    @param[in]  waiters     A pointer to the list of waiters.
    @param[in]  result      The result code to be given to the released thread.

    @return     A pointer to the thread that has been released, if any, or NULL if no thread was released.
    @remark     Not thread safe. Must be called within a critical section.
    @module     internal

*******************************************************************************************************************************************/
extern THREAD* KERNEL_ReleaseOne(LIST* waiters, STATUS result);

/***************************************************************************************************************************************//**

    Removes and releases all threads from a specified list of blocked threads.

    @param[in]  threads     A pointer to the list of blocked threads.
    @param[in]  result      The result code to be given to each of the released threads.

    @return     None.
    @remark     Not thread safe. Must be called within a critical section.
    @module     internal

*******************************************************************************************************************************************/
extern void KERNEL_ReleaseAll(LIST* waiters, STATUS result);

/***************************************************************************************************************************************//**

    Blocks the calling thread upon a specified object.

    @param[in]  obj         A pointer to the object that the thread is blocking upon.
    @param[in]  list        A pointer to a list of blocked threads that the calling thread will be added in.
    @param[in]  timeout     The maximum amount of time, in kernel ticks, that the calling thread should be blocked. Must not be zero. Use 
                            INFINITE to block indefinitely without a timeout.

    @return     None.
    @remark     Not thread safe. Must be called within an interrupt lock.
    @module     internal

*******************************************************************************************************************************************/
extern STATUS KERNEL_Block(void* obj, LIST* list, UINT32 timeout);

/***************************************************************************************************************************************//**

    Acquires a lock that is used to guard the thread lists.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The lock has been acquired.
     ERR_INVALIDCONTEXT     | This operation is not supported from the context of an interrupt service routine (ISR).   
     ERR_NOTINITIALIZED     | The specified mutex has not been initialized (created). 
     ERR_TIMEOUT            | The specified amount of time has elapsed prior to acquiring lock.
     ERR_DESTROYED          | The operation failed because the mutex has been destroyed.
     ERR_ABORTED            | The caller is unable to block because it has been aborted.

    @module     internal

*******************************************************************************************************************************************/
extern STATUS KERNEL_AcquireLock(void);

/***************************************************************************************************************************************//**

    Releases a previously acquired lock on the thread lists.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The lock has been released.
     ERR_INVALIDCONTEXT     | This operation is not supported from the context of an interrupt service routine (ISR).   
     ERR_NOTINITIALIZED     | The specified mutex has not been initialized (created).
     ERR_NOTOWNER           | The caller is not the owner, but only the owner is allowed to release the mutex.

    @module     internal

*******************************************************************************************************************************************/
extern STATUS KERNEL_ReleaseLock(void);

/*******************************************************************************************************************************************

    Initializes runtime statistics for the kernel.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The statistics have been successfully initialized.

    @remark     Called by KERNEL_Execute() and not to be called by user code.
    @module     internal

*******************************************************************************************************************************************/
extern STATUS KERNEL_InitializeStats(void);


/*******************************************************************************************************************************************
    KERNEL PORTS
*******************************************************************************************************************************************/
/***************************************************************************************************************************************//**

    Performs low-level initialization required for boot-up of the kernel. This is called before static memory initialization and therefore 
    should not depend upon any initial values.

    Optionally calls an application-defined hook function if configured using 'CFG_HOOKBOOT'.

    @return     None.
    @remark     Not to be called from user code.
    @module     internal

*******************************************************************************************************************************************/
extern void KERNEL_Boot(void);

/***************************************************************************************************************************************//**

    Starts execution of the kernel by launching the first thread process.

    @param[in]  proc        The process function for the first thread to be executed.
    @param[in]  arg         An optional argument to be passed to the process function. Can be NULL.

    @return     None.
    @remark     Not to be called from user code.
    @module     internal

*******************************************************************************************************************************************/
extern void KERNEL_ExecutePort(THREADSTART proc, void* arg);

/***************************************************************************************************************************************//**

    Assigns stack memory for a new thread within the kernel.

    @param[in]  thread      A pointer to the new thread to receive the specified stack memory.
    @param[in]  stk         A pointer to the stack memory to be assigned to the given thread.
    @param[in]  stksize     The size in bytes of the specified stack memory.

    @return

    Status Code             | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The stack memory was successfully assigned and initialized.

    @remark     Not to be called directly from user code.
    @module     internal

*******************************************************************************************************************************************/
extern STATUS THREAD_AssignStack(THREAD* thread, void* stk, UINT32 stksize);

/***************************************************************************************************************************************//**

    Creates and initializes the platform specific context for a thread.

    @param[in]  thread      A pointer to the thread to be initialized.
    @param[in]  proc        The process function for the thread.
    @param[in]  arg         An optional argument to be passed to the process function. Can be NULL.

    @return

    Status Code             | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The thread's context was successfully initialized.

    @remark     Not to be called directly from user code.
    @module     internal

*******************************************************************************************************************************************/
extern STATUS THREAD_InitContext(THREAD* thread, THREADSTART proc, void* arg);

/***************************************************************************************************************************************//**

    Executes a thread by invoking the context switch using the PendSV exception.

    @param[in]  thread      A pointer to the thread to begin execution.

    @return     None
    @remark     Not to be called direct from user code.
    @remark     Must be called from within a critical section.
    @module     internal

*******************************************************************************************************************************************/
extern void THREAD_Execute(THREAD* thread);


/*******************************************************************************************************************************************
    MCU SPECIFIC SUPPORT
*******************************************************************************************************************************************/
/***************************************************************************************************************************************//**

    Called by the kernel immediately upon boot-up (before memory initialization).

    @return     None.
    @remark     Not to be called directly from application code.
    @module     internal
    
*******************************************************************************************************************************************/
extern void MCU_Boot(void);

/***************************************************************************************************************************************//**

    Called by the kernel upon initialization and performs initialization of the MCU peripheral drivers.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The MCU was successfully initialized.

    @remark     Not to be called directly from application code.
    @module     internal

*******************************************************************************************************************************************/
extern STATUS MCU_Initialize(void);


/*******************************************************************************************************************************************
    TIMERS
*******************************************************************************************************************************************/
/***************************************************************************************************************************************//**

    Initializes support for kernel timers.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The timers have been successfully initialized.

    @remark     Not to be called directly from user code.
    @module     internal

*******************************************************************************************************************************************/
extern STATUS TIMER_Initialize(void);

/***************************************************************************************************************************************//**

    Performs the processing for all timers for a new system time tick.

    @return     None
    @remarks    Not to be called by user code. Called from kernel on a new system tick.
    @module     internal

*******************************************************************************************************************************************/
extern void TIMER_Process(void);

/*******************************************************************************************************************************************
    CONFIGURATION VALIDATION
*******************************************************************************************************************************************/
#if CFG_DEFAULTTIMESLICE < 2
#error "The default thread time slice must be greater than or equal to 2"
#endif

#endif /* KERNEL_CORE_H__ */

