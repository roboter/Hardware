/*******************************************************************************************************************************************

    DZX | KERNEL | THREAD                                                                                                 VERSION 18.2.1
    ------------------------------------------------------------------------------------------------------------------------------------

    This file is part of the kernel and provides support for threads. A thread is a sequence of programmed instructions that can be 
    scheduled and executed independently by the kernel. The threads provide an abstraction for concurrent execution that ultimately 
    provides a method for multitasking. The kernel provides the ability to have multiple threads that can be coded independent of each 
    other, can be assigned unique or equal priorities and have the ability to only execute when certain events have occurred.

    Once a thread has been created, it can be executed using THREAD_Start(). The thread will receive time upon the CPU depending upon
    it's configured priority.

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
#ifndef KERNEL_THREAD_H__
#define KERNEL_THREAD_H__

#include "Kernel/kernel_toolchain.h"
#include "Kernel/kernel_list.h"
#include "Kernel/kernel_stopwatch.h"

/*******************************************************************************************************************************************
    DEFINITIONS
*******************************************************************************************************************************************/


/*******************************************************************************************************************************************
    TYPE DEFINITIONS
*******************************************************************************************************************************************/
typedef struct THREAD THREAD;
typedef enum THREADSTATE THREADSTATE;
typedef enum PRIORITY PRIORITY;

/***************************************************************************************************************************************//**

    A state of a thread within the kernel.
    @module     kernel-thread

*******************************************************************************************************************************************/
enum THREADSTATE {
    STATE_STOPPED = 0,          /**< Indicates the thread is stopped. */
    STATE_READY,                /**< Indicates the thread is ready to be executed */
    STATE_SLEEPING,             /**< Indicates the thread is sleeping */
    STATE_BLOCKED,              /**< Indicates the thread is blocked waiting upon an object */
    STATE_BLOCKEDINDEFINITE,    /**< Indicates the thread is blocked waiting indefinitely upon an object */
    STATE_MAX                   /**< Represents the total number of possible thread states */
};

/***************************************************************************************************************************************//**

    A priority level for a thread.
    @module     kernel-thread

*******************************************************************************************************************************************/
enum PRIORITY {
    PRIO_IDLE = 0,              /**< The idle thread priority level (lowest possible) */
    PRIO_LOWER_7,               /**< A lower priority that is 7-levels below normal */
    PRIO_LOWER_6,               /**< A lower priority that is 6-levels below normal */
    PRIO_LOWER_5,               /**< A lower priority that is 5-levels below normal */
    PRIO_LOWER_4,               /**< A lower priority that is 4-levels below normal */
    PRIO_LOWER_3,               /**< A lower priority that is 3-levels below normal */
    PRIO_LOWER_2,               /**< A lower priority that is 2-levels below normal */
    PRIO_LOWER_1,               /**< A lower priority that is 1-level below normal */
    PRIO_NORMAL,                /**< A normal priority level */
    PRIO_HIGHER_1,              /**< A higher priority that is 1-level above normal */
    PRIO_HIGHER_2,              /**< A higher priority that is 2-levels above normal */
    PRIO_HIGHER_3,              /**< A higher priority that is 3-levels above normal */
    PRIO_HIGHER_4,              /**< A higher priority that is 4-levels above normal */
    PRIO_HIGHER_5,              /**< A higher priority that is 5-levels above normal */
    PRIO_HIGHER_6,              /**< A higher priority that is 6-levels above normal */
    PRIO_HIGHER_7,              /**< A higher priority that is 7-levels above normal */
};

/*******************************************************************************************************************************************

    Represents run-time statistics for a thread.
    @module     INTERNAL

*******************************************************************************************************************************************/
typedef struct THREADSTATS {
    STOPWATCH   watch;
    STOPWATCH   runsw;
    STOPWATCH   statsw;
    UINT32      usage;
    UINT64      exetime;
} THREADSTATS;

/***************************************************************************************************************************************//**

    Represents a thread of execution within the kernel.
    @module     kernel-thread

*******************************************************************************************************************************************/
struct THREAD {
	THREADCONTEXT   ctx;        /**< The hardware platform specific context information for the thread */
    NODE            node;       /**< A node to place the thread in a general list within the kernel */
    const CHAR*     name;       /**< A name for the thread */
    NODE            snode;      /**< A node to place the thread into a state-specific list */
    NODE            pnode;      /**< A node to place the thread into a pending block state list */
	NODE            bnode;      /**< A node to place the thread into an object's block list */
    void*           bobj;       /**< A pointer to the object that the thread is currently blocked upon */
    void*           args[2];    /**< Generic thread local storage used by kernel functions */
	void*           stk;        /**< A pointer to the memory of the stack for the thread */
	UINT32          stksize;    /**< Represents the size of the stack in bytes for the thread */
    UINT32          slice;      /**< The amount of time slice allocated for the thread */
    UINT32          timeout;    /**< The time value in kernel ticks when the thread will timeout from a blocking call */
    UINT32          time;       /**< A time counter for tracking the current slice usage for the thread */
    STATUS          status;     /**< The current status for the blocked thread */
    PRIORITY        prio;       /**< The current effective priority for the thread */
    PRIORITY        baseprio;   /**< The configured base priority for the thread */
	THREADSTATE     state;      /**< The current state of the thread */
    UINT32          flags;      /**< Status flags for the thread */
    LIST            joined;     /**< A list of threads blocked waiting to join this thread */ 
#if (CFG_STATISTICS)
	THREADSTATS     stats;      /**< Runtime statistics for the thread */
#endif
};

/*******************************************************************************************************************************************
    PUBLIC FUNCTIONS
*******************************************************************************************************************************************/
/***************************************************************************************************************************************//**

    Creates a thread with the specified parameters.

    @param[in]  thread      A pointer to a caller allocated thread instance to be created and initialized.
    @param[in]  name        A pointer to a NULL terminated string that represents the name for the thread.
    @param[in]  stk         A pointer to the start of the memory to be used for the thread stack.
    @param[in]  stksize     The size in bytes for the thread's stack memory.
    @param[in]  prio        A priority level for the thread. There are 15-available values and must be one of the following.

     Priority               | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     PRIO_HIGHER_7          | A priority 7 levels above normal.
     PRIO_HIGHER_6          | A priority 6 levels above normal.
     PRIO_HIGHER_5          | A priority 5 levels above normal.
     PRIO_HIGHER_4          | A priority 4 levels above normal.
     PRIO_HIGHER_3          | A priority 3 levels above normal.
     PRIO_HIGHER_2          | A priority 2 levels above normal.
     PRIO_HIGHER_1          | A priority 1 level above normal.
     PRIO_NORMAL            | A normal priority level.
     PRIO_LOWER_1           | A priority 1 level below normal.
     PRIO_LOWER_2           | A priority 2 levels below normal.
     PRIO_LOWER_3           | A priority 3 levels below normal.
     PRIO_LOWER_4           | A priority 4 levels below normal.
     PRIO_LOWER_5           | A priority 5 levels below normal.
     PRIO_LOWER_6           | A priority 6 levels below normal.
     PRIO_LOWER_7           | A priority 7 levels below normal.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The thread has been created.
     ERR_NULLREFERENCE      | The argument 'thread' or 'stk' was found to be NULL.
     ERR_INVALIDCONTEXT     | The operation is not supported from the context of an interrupt service routine (ISR).

    @module     kernel-thread

*******************************************************************************************************************************************/
extern STATUS THREAD_Create(THREAD* thread, const CHAR* name, void* stk, UINT32 stksize, PRIORITY prio);

/***************************************************************************************************************************************//**

    Destroys and removes a thread from the kernel. If the thread is alive, the thread will be terminated.

    @param[in]  thread      A pointer to the thread to be destroyed and removed from the kernel.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The thread has been removed from the kernel.
     ERR_NULLREFERENCE      | The argument 'thread' was found to be NULL.
     ERR_INVALIDCONTEXT     | This operation is not supported from the context of an interrupt service routine (ISR).
     ERR_NOTINITIALIZED     | The specified thread does not exist within the kernel.

    @module     kernel-thread

*******************************************************************************************************************************************/
extern STATUS THREAD_Destroy(THREAD* thread);

/***************************************************************************************************************************************//**

    Starts execution of a thread at the given entry function.

    @param[in]  thread      A pointer to the thread to be started.
    @param[in]  proc        An application-defined process function that represents the entry point for the thread.
    @param[in]  arg         (optional) A caller argument to be passed to the given thread function. Can be NULL.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The thread has been started.
     ERR_NULLREFERENCE      | The argument 'thread' or 'proc' was found to be NULL.
     ERR_INVALIDCONTEXT     | The operation is not supported from the context of an interrupt service routine (ISR).
     ERR_INVALIDOPERATION   | The thread is already alive and executing a function.
     ERR_NOTINITIALIZED     | The specified thread does not exist within the kernel.

    @module     kernel-thread

*******************************************************************************************************************************************/
extern STATUS THREAD_Start(THREAD* thread, THREADSTART func, void* arg);

/***************************************************************************************************************************************//**

    Aborts a thread. Once a thread has been aborted, all blocking calls made by the thread will fail with the ERR_ABORTED status code
    and any calls to THREAD_Aborted() will return as TRUE.

    @param[in]  thread      A pointer to the thread to be aborted.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The thread has been aborted.
     ERR_NULLREFERENCE      | The argument 'thread' was found to be NULL.
     ERR_NOTINITIALIZED     | The specified thread does not exist within the kernel.

    @module     kernel-thread

*******************************************************************************************************************************************/
extern STATUS THREAD_Abort(THREAD* thread);

/***************************************************************************************************************************************//**

    Returns an indication of whether the calling thread has been aborted.

    @return     TRUE if the calling thread has been aborted and should exit; otherwise FALSE.
    @module     kernel-thread

*******************************************************************************************************************************************/
extern BOOLEAN THREAD_Aborted(void);

/***************************************************************************************************************************************//**

    Terminates execution of a thread immediately.

    @param[in]  thread      A pointer to the thread to be terminated.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The thread has been terminated.
     ERR_NULLREFERENCE      | The argument 'thread' was found to be NULL.
     ERR_NOTINITIALIZED     | The specified thread does not exist within the kernel.

    @module     kernel-thread

*******************************************************************************************************************************************/
extern STATUS THREAD_Terminate(THREAD* thread);

/***************************************************************************************************************************************//**

    Blocks the calling thread until a thread terminates.

    @param[in]  thread      A pointer to the thread to wait for termination.
    @param[in]  timeout     The maximum amount of time, in kernel ticks, to wait for the thread to terminate. Use 0 to return immediately
                            without blocking or use INFINITE to wait indefinitely.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The specified thread has terminated.
     ERR_NULLREFERENCE      | The argument 'thread' was found to be NULL.
     ERR_INVALIDCONTEXT     | The operation is not supported from the context of an interrupt service routine (ISR).
     ERR_NOTINITIALIZED     | The specified thread does not exist within the kernel.
     ERR_TIMEOUT            | The specified maximum amount of time has elapsed prior to the thread terminating.
     
    @module     kernel-thread

*******************************************************************************************************************************************/
extern STATUS THREAD_Join(THREAD* thread, UINT32 timeout);

/***************************************************************************************************************************************//**

    Returns an indication of whether a thread is alive. A thread is considered to be alive if it has been started and it has not exited or
    has been terminated.

    @param[in]  thread      A pointer to the target thread to be checked for being alive.

    @return     TRUE if the thread has been started and has not been stopped or terminated; otherwise FALSE.
    @module     kernel-thread

*******************************************************************************************************************************************/
extern BOOLEAN THREAD_IsAlive(THREAD* thread);

/***************************************************************************************************************************************//**

    Assigns a new priority level to a thread.

    @param[in]  thread      A pointer to the thread to receive the new priority value.
    @param[in]  prio        A priority level for the thread. There are 15-available values and must be one of the following.

     Priority               | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     PRIO_HIGHER_7          | A priority 7 levels above normal.
     PRIO_HIGHER_6          | A priority 6 levels above normal.
     PRIO_HIGHER_5          | A priority 5 levels above normal.
     PRIO_HIGHER_4          | A priority 4 levels above normal.
     PRIO_HIGHER_3          | A priority 3 levels above normal.
     PRIO_HIGHER_2          | A priority 2 levels above normal.
     PRIO_HIGHER_1          | A priority 1 level above normal.
     PRIO_NORMAL            | A normal priority level.
     PRIO_LOWER_1           | A priority 1 level below normal.
     PRIO_LOWER_2           | A priority 2 levels below normal.
     PRIO_LOWER_3           | A priority 3 levels below normal.
     PRIO_LOWER_4           | A priority 4 levels below normal.
     PRIO_LOWER_5           | A priority 5 levels below normal.
     PRIO_LOWER_6           | A priority 6 levels below normal.
     PRIO_LOWER_7           | A priority 7 levels below normal.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The thread has been given the new priority level.
     ERR_NULLREFERENCE      | The argument 'thread' was found to be NULL.
     ERR_INVALIDCONTEXT     | The operation is not supported from the context of an interrupt service routine (ISR).
     ERR_NOTINITIALIZED     | The specified thread does not exist within the kernel.

    @module     kernel-thread

*******************************************************************************************************************************************/
extern STATUS THREAD_SetPriority(THREAD* thread, PRIORITY prio);

/***************************************************************************************************************************************//**

    Assigns a new time slice value to a thread.

    The time slice is the maximum amount of time, in kernel ticks, that the thread is allowed to continuously execute before switching
    execution to another similar priority thread. The thread's time slice has no effect if there are no other threads of similar priority.

    @param[in]  thread      A pointer to the thread to receive the new time slice value.
    @param[in]  slice       The new time slice value for the thread. Must be greater than zero.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The thread has been given the new time slice.
     ERR_NULLREFERENCE      | The argument 'thread' was found to be NULL.
     ERR_OUTOFRANGE         | The specified slice value was out of range (must be greater than zero).
     ERR_NOTINITIALIZED     | The specified thread does not exist within the kernel.

    @module     kernel-thread

*******************************************************************************************************************************************/
extern STATUS THREAD_SetSlice(THREAD* thread, UINT32 slice);

/***************************************************************************************************************************************//**

    Suspends and blocks the calling thread for the specified amount of time.

    @param[in]  timeout     The total amount of time, in kernel ticks, to suspend the calling thread. Use '0' to yield the remainder of 
                            the calling thread's time slice without actually suspending or blocking the thread.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The thread was suspended.
     ERR_INVALIDCONTEXT     | This operation is not supported from the context of an interrupt service routine (ISR).

    @remark     Cannot be called from an ISR.
    @module     kernel-thread

*******************************************************************************************************************************************/
extern STATUS THREAD_Sleep(UINT32 timeout);

/***************************************************************************************************************************************//**

    Returns the thread that is currently excecuting. If called from an ISR, returns the thread that has been interrupted.

    @return     A pointer to the thread that is currently executing. NULL if the kernel is not executing.
    @module     kernel-thread

*******************************************************************************************************************************************/
extern THREAD* THREAD_Current(void);

/***************************************************************************************************************************************//**

    Returns a pointer to the idle thread for the kernel.

    @return     A pointer to the idle thread for the kernel.
    @module     kernel-thread

*******************************************************************************************************************************************/
extern THREAD* THREAD_Idle(void);

/***************************************************************************************************************************************//**

    Returns a pointer to the main thread for the application.

    @return     A pointer to the main thread for the application.
    @module     kernel-thread

*******************************************************************************************************************************************/
extern THREAD* THREAD_Main(void);

/***************************************************************************************************************************************//**

    Acquires a lock upon the calling thread by suspending further context switches until this lock is released.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The thread has been locked.
     ERR_INVALIDCONTEXT     | The operation is not supported from the context of an interrupt service routine (ISR).

    @remark     The lock can be acquired multiple times, but the lock will need to be released the same number of times before context
                switches will resume.
    @module     KERNEL-LOCK

*******************************************************************************************************************************************/
extern STATUS THREAD_AcquireLock(void);

/***************************************************************************************************************************************//**

    Releases a previously acquired lock upon the current thread and resumes normal scheduling of threads.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The thread lock has been released.
     ERR_INVALIDCONTEXT     | The operation is not supported from the context of an interrupt service routine (ISR).
     ERR_INVALIDOPERATION   | The calling thread is not locked.

    @module     KERNEL-LOCK

*******************************************************************************************************************************************/
extern STATUS THREAD_ReleaseLock(void);

#if (CFG_STACKFILLING)
/***************************************************************************************************************************************//**

    Returns the maximum amount of space, in bytes, that has been used within the stack memory of a thread.

    @param[in]  thread      A pointer to the target thread.

    @return     The maximum number of bytes of stack memory that has been used by the given thread.
    @module     kernel-thread

*******************************************************************************************************************************************/
extern UINT32 THREAD_StackUsage(THREAD* thread);

/***************************************************************************************************************************************//**

    Returns an indication of whether a thread has overflowed its stack memory.

    @param[in]  thread      A pointer to the target thread.

    @return     TRUE if the thread has accessed beyond its configured stack memory; otherwise FALSE.
    @module     kernel-thread

*******************************************************************************************************************************************/
extern BOOLEAN THREAD_StackOverflow(THREAD* thread);
#endif /* CFG_STACKFILLING */

#endif /* KERNEL_THREAD_H__ */
