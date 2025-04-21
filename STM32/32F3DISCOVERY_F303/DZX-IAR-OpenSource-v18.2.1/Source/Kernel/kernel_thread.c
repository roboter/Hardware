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
#include "kernel_thread.h"
#include "kernel_core.h"

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
STATUS THREAD_Create(THREAD* thread, const CHAR* name, void* stk, UINT32 stksize, PRIORITY prio)
{
    INTERRUPTLOCK lock;
    STATUS status;
    

#if (CFG_CONTEXTCHECKING)
    if (KERNEL_IsISR()) {
        return ERR_INVALIDCONTEXT;
    }
#endif
    
#if (CFG_NULLCHECKING)
    if (thread == NULL) {
        return ERR_NULLREFERENCE;
    }

    if (stk == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif

    thread->name = name;
    thread->bobj = NULL;
    thread->prio = prio;                                        /* Assign priorities */
    thread->baseprio = prio;
    thread->slice = CFG_DEFAULTTIMESLICE;                       /* Begin with the global default time slice */
    thread->time = 0;
    thread->state = STATE_STOPPED;
    thread->flags = 0;

    status = THREAD_AssignStack(thread, stk, stksize);          /* Assign the stack memory for the thread */
    if (status != SUCCESS) {                                    /* Error with the stack memory? */
        return status;                                          /* Bubble up the error */
    }
    
    LIST_Init(&thread->joined);
    
    LIST_InitNode(&thread->snode);                              /* Initialize the state node */
    LIST_InitNode(&thread->pnode);
    LIST_InitNode(&thread->bnode);                              /* Initialize the blocking node */
    
#if (CFG_STATISTICS)
    thread->stats.exetime = 0;                                  /* Initialize runtime statistics */
    thread->stats.usage = 0;
    
    STOPWATCH_Create(&thread->stats.watch, OPT_NONE);
    STOPWATCH_Create(&thread->stats.runsw, OPT_NONE);
    STOPWATCH_Create(&thread->stats.statsw, OPT_START);
#endif
    
    KERNEL_AcquireLock();

    ACQUIREINTERRUPTLOCK();
    
    LIST_AddLast(&kernel.threads, &thread->node, thread);       /* Keep a reference to the created thread */ 
    
    RELEASEINTERRUPTLOCK();
    KERNEL_ReleaseLock();
    return SUCCESS;
}

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
STATUS THREAD_Destroy(THREAD* thread)
{
    INTERRUPTLOCK lock;
    STATUS status;
    
    
#if (CFG_CONTEXTCHECKING)
    if (KERNEL_IsISR()) {
        return ERR_INVALIDCONTEXT;
    }
#endif
    
#if (CFG_NULLCHECKING)
    if (thread == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif
    
    ACQUIREINTERRUPTLOCK();

    if (thread->node.list != &kernel.threads) {                     /* Has the thread been initialized? */
        RELEASEINTERRUPTLOCK();
        return ERR_NOTINITIALIZED;
    }

    if (thread->snode.list) {                                       /* Is the thread alive? */
        RELEASEINTERRUPTLOCK();
        
        status = THREAD_Terminate(thread);                          /* Terminate the thread (forced stop) */
        if (status != SUCCESS) {
            return status;                                          /* Failed to terminate. Bubble up the error. */
        }
        
    } else {
        RELEASEINTERRUPTLOCK();
    }

    KERNEL_AcquireLock();                   
    ACQUIREINTERRUPTLOCK();
    
    thread->stk = NULL;                                             /* Remove references to the stack memory */
    thread->stksize = 0;

    LIST_Remove(&kernel.threads, &thread->node);                    /* Remove the thread from the kernel */

    RELEASEINTERRUPTLOCK();
    KERNEL_ReleaseLock();
    KERNEL_ContextSwitch();
    return SUCCESS;
}

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
STATUS THREAD_Start(THREAD* thread, THREADSTART proc, void* arg)
{
    INTERRUPTLOCK lock;
    STATUS status;
    
    
#if (CFG_CONTEXTCHECKING)
    if (KERNEL_IsISR()) {
        return ERR_INVALIDCONTEXT;
    }
#endif
    
#if (CFG_NULLCHECKING)
    if (thread == NULL) {
        return ERR_NULLREFERENCE;
    }
    
    if (proc == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif
    
    ACQUIREINTERRUPTLOCK();

    if (thread->node.list != &kernel.threads) {                 /* Has the thread been initialized? */
        RELEASEINTERRUPTLOCK();
        return ERR_NOTINITIALIZED;
    }
    
    if (thread->snode.list) {                                   /* Is the thread already alive? */
        RELEASEINTERRUPTLOCK();
        return ERR_INVALIDOPERATION;                            /* Cannot start a live thread */
    }
    
    thread->flags &= ~FLAG_THREADABORTED;
     
    RELEASEINTERRUPTLOCK();
   
    status = THREAD_InitContext(thread,                         /* Initialize the hardware context for the thread */
                                proc,                           /* The process function for the thread */
                                arg);                           /* An optional argument for the process function */
    
    if (status != SUCCESS) {                                    /* Any errors? */
        return status;                                          /* Bubble up the error */
    }
    
    ACQUIREINTERRUPTLOCK();
    
    thread->time = kernel.ticks + thread->slice;                /* Establish the system time for the resumed thread */
    KERNEL_SetState(thread, STATE_READY);                       /* Schedule the thread to execute */

    RELEASEINTERRUPTLOCK(); 
    KERNEL_ContextSwitch();                                     /* Possibly switch threads */
    return SUCCESS;
}
    
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
STATUS THREAD_Abort(THREAD* thread)
{
    INTERRUPTLOCK lock;
    
   
#if (CFG_NULLCHECKING)
    if (thread == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif
    
    ACQUIREINTERRUPTLOCK();

    if (thread->node.list != &kernel.threads) {                 /* Has the thread been initialized? */
        RELEASEINTERRUPTLOCK();
        return ERR_NOTINITIALIZED;
    }
        
    thread->flags |= FLAG_THREADABORTED;                        /* Mark as aborted */
    
    if (thread->bobj == NULL) {                                 /* Is the specified thread already blocked? */                       
        RELEASEINTERRUPTLOCK();
        return SUCCESS;                                         /* No, exit */
    }
    
    if (thread->bnode.list) {
        LIST_Remove(thread->bnode.list, &thread->bnode);        /* Remove the thread from the block list */
    }
    
    KERNEL_SetState(thread, STATE_READY);                       /* Make the removed thread ready to execute */

    thread->bobj = NULL;                                        /* Clear the object the thread is blocked upon */
    thread->status = ERR_ABORTED;                               /* Provide the blocking result code */
    
    RELEASEINTERRUPTLOCK();
    KERNEL_ContextSwitch();                                     /* Possibly switch threads */
    return SUCCESS;
}

/***************************************************************************************************************************************//**

    Returns an indication of whether the calling thread has been aborted.

    @return     TRUE if the calling thread has been aborted and should exit; otherwise FALSE.
    @module     kernel-thread

*******************************************************************************************************************************************/
BOOLEAN THREAD_Aborted(void)
{
    INTERRUPTLOCK lock;
    
    
    ACQUIREINTERRUPTLOCK();
    if (kernel.thread->flags & FLAG_THREADABORTED) {
        RELEASEINTERRUPTLOCK();
        return TRUE;
    }
    
    RELEASEINTERRUPTLOCK();
    return FALSE;
}

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
STATUS THREAD_Terminate(THREAD* thread)
{
    INTERRUPTLOCK lock;
    
    
#if (CFG_CONTEXTCHECKING)
    if (KERNEL_IsISR()) {
        return ERR_INVALIDCONTEXT;
    }
#endif
    
#if (CFG_NULLCHECKING)
    if (thread == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif
   
    KERNEL_AcquireLock();
    if (thread->pnode.list) {
        LIST_Remove(thread->pnode.list, &thread->pnode);
    }
    KERNEL_ReleaseLock();
    
    thread->bobj = NULL;                                            /* Clear the reference to the blocked object */
    thread->state = STATE_STOPPED;                                  /* Update the thread's state */
    
    ACQUIREINTERRUPTLOCK();

    if (thread->node.list != &kernel.threads) {                     /* Has the thread been initialized? */
        RELEASEINTERRUPTLOCK();
        return ERR_NOTINITIALIZED;
    }
    
    if (thread->bnode.list) {
        LIST_Remove(thread->bnode.list, &thread->bnode);            /* Remove the thread from the block list */
    }
    
    KERNEL_SetState(thread, STATE_STOPPED);

    RELEASEINTERRUPTLOCK();
    KERNEL_ReleaseAll(&thread->joined, SUCCESS);                    /* Release any thread waiting to join */
    KERNEL_ContextSwitch();                                         /* Possibly switch threads */
    return SUCCESS;   
}

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
STATUS THREAD_Join(THREAD* thread, UINT32 timeout)
{
    INTERRUPTLOCK lock;


#if (CFG_CONTEXTCHECKING)
    if (KERNEL_IsISR()) {
        return ERR_INVALIDCONTEXT;
    }
#endif

#if (CFG_NULLCHECKING)
    if (thread == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif
    
    ACQUIREINTERRUPTLOCK();

    if (thread->node.list != &kernel.threads) {                 /* Has the thread been initialized? */
        RELEASEINTERRUPTLOCK();
        return ERR_NOTINITIALIZED;
    }

    if (thread->state == STATE_STOPPED) {                       /* Is the thread alive? */
        RELEASEINTERRUPTLOCK();
        return SUCCESS;                                         /* Thread is not alive */
    }
    
    if (timeout == 0) {                                         /* Is requested to return immediately? */
        RELEASEINTERRUPTLOCK();
        return ERR_TIMEOUT;                                     /* Return immediate timeout without blocking */
    }
    
    KERNEL_Block(thread, &thread->joined, timeout);             /* Block the caller */
    
    RELEASEINTERRUPTLOCK();
    KERNEL_ContextSwitch();                                     /* Caller blocked, switch threads */
    return kernel.thread->status;                               /* Caller released, return result */
}

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
STATUS THREAD_SetPriority(THREAD* thread, PRIORITY prio)
{
    INTERRUPTLOCK lock;

    
#if (CFG_CONTEXTCHECKING)
    if (KERNEL_IsISR()) {
        return ERR_INVALIDCONTEXT;   
    }
#endif
    
#if (CFG_NULLCHECKING)
    if (thread == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif
    
    ACQUIREINTERRUPTLOCK();

    if (thread->node.list != &kernel.threads) {                 /* Has the thread been initialized? */
        RELEASEINTERRUPTLOCK();
        return ERR_NOTINITIALIZED;
    }

    if (thread->prio == thread->baseprio) {                     /* Is the target thread's priority temporarily elevated? */
        thread->prio = prio;                                    /* Not elevated, update the current priority */
        KERNEL_SetState(thread, thread->state);                 /* Reschedule the thread with it's new priority level */                
    }
    
    thread->baseprio = prio;                                    /* Update the base priority for the thread */

    RELEASEINTERRUPTLOCK();
    KERNEL_ContextSwitch();                                     /* Possibly switch threads */
    return SUCCESS;
}

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
STATUS THREAD_SetSlice(THREAD* thread, UINT32 slice)
{
    INTERRUPTLOCK lock;


#if (CFG_NULLCHECKING)
    if (thread == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif

    if (slice == 0) {
        return ERR_OUTOFRANGE;
    }
    
    ACQUIREINTERRUPTLOCK();

    if (thread->node.list != &kernel.threads) {                 /* Has the thread been initialized? */
        RELEASEINTERRUPTLOCK();
        return ERR_NOTINITIALIZED;
    }

    thread->slice = slice;

    RELEASEINTERRUPTLOCK();
    return SUCCESS;
}

/***************************************************************************************************************************************//**

    Returns the thread that is currently excecuting. If called from an ISR, returns the thread that has been interrupted.

    @return     A pointer to the thread that is currently executing. NULL if the kernel is not executing.
    @module     kernel-thread

*******************************************************************************************************************************************/
THREAD* THREAD_Current(void)
{
    return kernel.thread;
}

/***************************************************************************************************************************************//**

    Returns a pointer to the main thread for the application.

    @return     A pointer to the main thread for the application.
    @module     kernel-thread

*******************************************************************************************************************************************/
THREAD* THREAD_Main(void)
{
    return &kernel.main;
}

/***************************************************************************************************************************************//**

    Returns a pointer to the idle thread for the kernel.

    @return     A pointer to the idle thread for the kernel.
    @module     kernel-thread

*******************************************************************************************************************************************/
THREAD* THREAD_Idle(void)
{
    return &kernel.idle;
}

/***************************************************************************************************************************************//**

    Returns an indication of whether a thread is alive. A thread is considered to be alive if it has been started and it has not exited or
    has been terminated.

    @param[in]  thread      A pointer to the target thread to be checked for being alive.

    @return     TRUE if the thread has been started and has not been stopped or terminated; otherwise FALSE.
    @module     kernel-thread

*******************************************************************************************************************************************/
BOOLEAN THREAD_IsAlive(THREAD* thread)
{
    INTERRUPTLOCK lock;
    

#if (CFG_NULLCHECKING)
    if (thread == NULL) {
        return FALSE;
    }
#endif
    
    ACQUIREINTERRUPTLOCK();
    
    if (thread->node.list != &kernel.threads) {                 /* Has the thread been initialized? */
        RELEASEINTERRUPTLOCK();
        return ERR_NOTINITIALIZED;
    }
    
    if (thread->state != STATE_STOPPED) {
        RELEASEINTERRUPTLOCK();
        return TRUE;                                            /* The thread isn't stopped; considered alive */
    }
    
    RELEASEINTERRUPTLOCK();
    return FALSE;
}

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
STATUS THREAD_Sleep(UINT32 timeout)
{
    INTERRUPTLOCK lock;
    
 
#if (CFG_CONTEXTCHECKING)
    if (KERNEL_IsISR()) {                                       /* Cannot sleep ISR */
        return ERR_INVALIDCONTEXT;
    }
#endif
    
    ACQUIREINTERRUPTLOCK();
    
    if (timeout > 0) {                                          /* Actually suspend the calling thread? */
        kernel.thread->time = timeout;                          /* Set the wake-up time for the thread */
        KERNEL_SetState(kernel.thread, STATE_SLEEPING);         /* Place the thread into the sleeping state */
    } else {
        KERNEL_SetState(kernel.thread, STATE_READY);            /* Reschedule without suspending */     
    }
    
    RELEASEINTERRUPTLOCK();
    KERNEL_ContextSwitch();                                     /* Possibly switch threads */
    return SUCCESS;
}

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
STATUS THREAD_AcquireLock(void)
{
    INTERRUPTLOCK lock;
    
 
#if (CFG_CONTEXTCHECKING)
    if (KERNEL_IsISR()) {
        return ERR_INVALIDCONTEXT;
    }
#endif
    
    ACQUIREINTERRUPTLOCK();
    kernel.lock++;
    
#if (CFG_LOCKSTATISTICS)
    if (kernel.lock == 1) {
        STOPWATCH_Restart(&lock_stats.thread.watch);
    }
#endif
    RELEASEINTERRUPTLOCK();
    
    return SUCCESS;
}

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
STATUS THREAD_ReleaseLock(void)
{
    INTERRUPTLOCK lock;
#if (CFG_LOCKSTATISTICS)
    UINT32 elapsed;
#endif

    
#if (CFG_CONTEXTCHECKING)
    if (KERNEL_IsISR()) {
        return ERR_INVALIDCONTEXT;
    }
#endif
    
    ACQUIREINTERRUPTLOCK();
    
    if (kernel.lock == 0) {
        RELEASEINTERRUPTLOCK();
        return ERR_INVALIDOPERATION;
    }
    
    --kernel.lock;

    if (kernel.lock == 0) {
#if (CFG_LOCKSTATISTICS)
        elapsed = STOPWATCH_Elapsed(&lock_stats.thread.watch);
        if (elapsed > lock_stats.thread.max) {
            lock_stats.thread.max = elapsed;
        }
#endif
        RELEASEINTERRUPTLOCK();
        KERNEL_ContextSwitch();
        return SUCCESS;
    }
    
    RELEASEINTERRUPTLOCK();
    return SUCCESS;   
}
