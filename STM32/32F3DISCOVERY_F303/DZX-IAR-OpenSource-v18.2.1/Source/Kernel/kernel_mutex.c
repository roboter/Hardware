/*******************************************************************************************************************************************

    DZX | KERNEL | MUTEX                                                                                                  VERSION 18.2.1
    ------------------------------------------------------------------------------------------------------------------------------------

    This file is part of the kernel and provides support for mutexes. A mutex is a synchronization object that provides a mutually 
    exclusive access to a resource. For example, to prevent two threads from writing to shared memory at the same time, each thread 
    acquires ownership of a mutex before executing the code that accesses the memory. After writing to the shared memory, the thread 
    releases the mutex.

    After a thread obtains ownership of a mutex, it can specify the same mutex within subsequent calls to acquire ownership of the mutex 
    without being blocked, but the thread must release the mutex once for each time the mutex was acquired.

    A mutex supports priority inheritance so that if a thread with higher priority is blocked while waiting to acquire ownership of 
    a mutex, the kernel will temporarily give the owner of that mutex the same priority of the blocked thread. Once the mutex has been 
    released, the original owning thread will return back to it's original priority.

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
#include "kernel_mutex.h"
#include "kernel_core.h"

/*******************************************************************************************************************************************
    PRIVATE VARIABLES
*******************************************************************************************************************************************/
static LIST kernel_mutexes;

/***************************************************************************************************************************************//**

    Creates and initializes a mutex.

    @param[in]  mutex       A pointer to a caller allocated mutex instance to be initialized.
    @param[in]  name        A pointer to a NULL terminated string that represents the name for the mutex.
    @param[in]  owner       Use TRUE to have the caller initially be the owner of the mutex (already acquired).

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The mutex has been created and initialized.
     ERR_NULLREFERENCE      | The argument 'mutex' was found to be NULL.
     ERR_INVALIDCONTEXT     | The operation is not supported from the context of an interrupt service routine (ISR).
     ERR_ALREADYINITIALIZED | The specified mutex has already been created and initialized.

    @module     kernel-mutex

*******************************************************************************************************************************************/
STATUS MUTEX_Create(MUTEX* mutex, const CHAR* name, BOOLEAN owner)
{
    INTERRUPTLOCK lock;
    
    
#if (CFG_CONTEXTCHECKING)
    if (KERNEL_IsISR()) {
        return ERR_INVALIDCONTEXT;
    }
#endif
    
#if (CFG_NULLCHECKING)
    if (mutex == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif
    
    ACQUIREINTERRUPTLOCK();
    
    if (mutex->node.list == &kernel_mutexes) {                  /* Has the mutex already been initialized? */
        RELEASEINTERRUPTLOCK();
        return ERR_ALREADYINITIALIZED;
    }
    
    RELEASEINTERRUPTLOCK();
    
    mutex->name = name;                                         /* Initialize the mutex */
    mutex->nesting = 0;
    mutex->owner = NULL;
    LIST_Init(&mutex->threads);                                 /* Initialize the list of threads waiting to acquire the mutex */

    ACQUIREINTERRUPTLOCK();
    
    if (owner) {                                                /* Begin with the caller as the owner? */
        mutex->owner = kernel.thread;                           /* Assign the caller as the initial owner */
    }
    
    LIST_AddLast(&kernel_mutexes,                               /* Register the mutex within the kernel */
                 &mutex->node, 
                 mutex);
   
    RELEASEINTERRUPTLOCK();
    return SUCCESS;
}

/***************************************************************************************************************************************//**

    Destroys and removes a mutex from the kernel. Any threads that happen to be waiting to acquire the mutex will be released with the 
    ERR_DESTROYED status code.

    @param[in]  mutex       A pointer to a mutex to be destroyed.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The mutex has been destroyed and removed from the kernel.
     ERR_NULLREFERENCE      | The argument 'mutex' was found to be NULL.
     ERR_INVALIDCONTEXT     | The operation is not supported from the context of an interrupt service routine (ISR).
     ERR_NOTINITIALIZED     | The specified mutex has not been created and initialized.
     
    @module     kernel-mutex

*******************************************************************************************************************************************/
STATUS MUTEX_Destroy(MUTEX* mutex)
{
    INTERRUPTLOCK lock;
    
    
#if (CFG_CONTEXTCHECKING)
    if (KERNEL_IsISR()) {
        return ERR_INVALIDCONTEXT;
    }
#endif
    
#if (CFG_NULLCHECKING)
    if (mutex == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif

    ACQUIREINTERRUPTLOCK();

    if (mutex->node.list != &kernel_mutexes) {                  /* Has the mutex been initialized? */
        RELEASEINTERRUPTLOCK();
        return ERR_NOTINITIALIZED;
    }

    LIST_Remove(&kernel_mutexes, &mutex->node);                 /* Remove the mutex from the kernel */
    RELEASEINTERRUPTLOCK();
    
    KERNEL_ReleaseAll(&mutex->threads, ERR_DESTROYED);          /* Release any threads waiting to acquire the mutex */
    return SUCCESS;                                     
}

/***************************************************************************************************************************************//**

    Acquires ownership of a mutex.

    @param[in]  mutex       A pointer to the mutex to be acquired.
    @param[in]  timeout     The maximum amount of time, in kernel ticks, to block and wait to acquire ownership of the mutex. Use '0' to 
                            return immediately without blocking or use 'INFINITE' to block indefinitely.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The calling thread has acquired ownership of the mutex.
     ERR_NULLREFERENCE      | The argument 'mutex' was found to be NULL.
     ERR_INVALIDCONTEXT     | The operation is not supported from the context of an interrupt service routine (ISR).   
     ERR_NOTINITIALIZED     | The specified mutex has not been created and initialized. 
     ERR_TIMEOUT            | The specified amount of time has elapsed while waiting to acquire ownership of the mutex.
     ERR_DESTROYED          | The operation failed because the mutex has been destroyed.
     ERR_ABORTED            | The caller is unable to block because it has been aborted.

    @remark     Only causes a context switch to occur if the mutex happens to be owned by a different thread.
    @remark     MUTEX_Acquire() can be called multiple times, but the mutex will require the same number of MUTEX_Release() calls to
                completely release ownership.
    @module     kernel-mutex

*******************************************************************************************************************************************/
STATUS MUTEX_Acquire(MUTEX* mutex, UINT32 timeout)
{
    INTERRUPTLOCK lock;
    STATUS status;
    

#if (CFG_CONTEXTCHECKING)
    if (KERNEL_IsISR()) {                                         /* Is the caller an ISR? */
        return ERR_INVALIDCONTEXT;
    }
#endif
    
#if (CFG_NULLCHECKING)
    if (mutex == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif

    ACQUIREINTERRUPTLOCK();
    
    if (mutex->node.list != &kernel_mutexes) {                  /* Has the specified mutex been initialized? */
        RELEASEINTERRUPTLOCK();
        return ERR_NOTINITIALIZED;
    }

    if (kernel.thread == mutex->owner) {                        /* Is the caller already the owner of the mutex? */
        mutex->nesting++;                                       /* Keep count of nested acquisitions */
        RELEASEINTERRUPTLOCK();
        return SUCCESS;
    }
    
    if (mutex->owner == NULL) {                                 /* Is the mutex current owned by a different thread? */
        mutex->owner = kernel.thread;                           /* Mutex is not owned, take ownership */
        
        RELEASEINTERRUPTLOCK();
        return SUCCESS;
    }
    
    if (timeout == 0) {                                         /* Requested to not block and return immediately? */
        RELEASEINTERRUPTLOCK();
        return ERR_TIMEOUT;                                     /* Return timeout without blocking */
    }

    status = KERNEL_Block(mutex, &mutex->threads, timeout);     /* Attempt to block the caller */
    if (status == SUCCESS) {                                    /* Was the caller blocked? */
        
        if (kernel.thread->prio > mutex->owner->prio) {         /* Yes, now is the requesting thread higher priority than the owner? */
            mutex->owner->prio = kernel.thread->prio;           /* Temporarily give owner the caller's priority */
            KERNEL_SetState(mutex->owner, mutex->owner->state); /* Reschedule the owner with it's new priority */
        }
    }

    RELEASEINTERRUPTLOCK();
    KERNEL_ContextSwitch();
    return kernel.thread->status;                               /* Return the result after blocking */
}

/***************************************************************************************************************************************//**

    Releases ownership of a mutex.

    @param[in]  mutex       A pointer to the mutex to have ownership released.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The mutex has been released.
     ERR_NULLREFERENCE      | The argument 'mutex' was found to be NULL.
     ERR_INVALIDCONTEXT     | The operation is not supported from the context of an interrupt service routine (ISR).   
     ERR_NOTINITIALIZED     | The specified mutex has not been created and initialized.
     ERR_NOTOWNER           | The calling thread is not the owner, but only the owner is allowed to release the mutex.

   @remark      If there were multiple calls to MUTEX_Acquire() by the owning thread, the mutex will not be released until the same number 
                of MUTEX_Release() calls have been made.
   @module      kernel-mutex

*******************************************************************************************************************************************/
STATUS MUTEX_Release(MUTEX* mutex)
{
    INTERRUPTLOCK lock;
    
    
#if (CFG_CONTEXTCHECKING)
    if (KERNEL_IsISR()) {                                         /* Is the caller an ISR? */
        return ERR_INVALIDCONTEXT;
    }
#endif
    
#if (CFG_NULLCHECKING)
    if (mutex == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif

    ACQUIREINTERRUPTLOCK();
    
    if (mutex->node.list != &kernel_mutexes) {                  /* Has the specified mutex been initialized? */
        RELEASEINTERRUPTLOCK();
        return ERR_NOTINITIALIZED;
    }

    if (mutex->owner != kernel.thread) {                        /* Does the caller own the mutex? */
        RELEASEINTERRUPTLOCK();
        return ERR_NOTOWNER;                                    /* Caller not the owner and only the owner can release it */
    }

    if (mutex->nesting) {                                       /* Were there multiple acquisitions? */
        mutex->nesting--;                                       /* Release a single acquisition */
        RELEASEINTERRUPTLOCK();
        return SUCCESS;
    }

    if (kernel.thread->prio != kernel.thread->baseprio) {       /* Was the caller's priority temporarily elevated? */
        kernel.thread->prio = kernel.thread->baseprio;          /* Restore caller to their base priority */
        KERNEL_SetState(kernel.thread, kernel.thread->state);   /* Reschedule the caller with their new priority */
    }
    
    mutex->owner = KERNEL_ReleaseOne(&mutex->threads, SUCCESS); /* Release to the next potential owner */
    
    RELEASEINTERRUPTLOCK();
    KERNEL_ContextSwitch();
    return SUCCESS;
}
