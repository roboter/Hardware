/*******************************************************************************************************************************************

    DZX | KERNEL | SEMAPHORE                                                                                              VERSION 18.2.1
    ------------------------------------------------------------------------------------------------------------------------------------

    This file is part of the kernel and provides support for counting semaphores. A semaphore is a synchronization object that limits 
    the number of threads that can concurrently access a resource. 
    
    Anytime that a thread successfully acquires the semaphore using SEMAPHORE_Acquire(), its count is decremented by one. If the 
    semaphore's count is zero when a thread attempts to acquire the semaphore, the calling thread will be blocked until the semaphore's 
    count is incremented using SEMAPHORE_Release() or until the specified timeout interval elapses.

    Unlike the mutex, a semaphore does not have the notion of an owner thread. Without an owner, any thread can release a semaphore, 
    even if it is different than the thread that originally acquired the semaphore.

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
#include "kernel_semaphore.h"
#include "kernel_core.h"

/*******************************************************************************************************************************************
    PRIVATE VARIABLES
*******************************************************************************************************************************************/
static LIST kernel_semaphores;

/***************************************************************************************************************************************//**

    Creates and initializes a counting semaphore with the specified initial and maximum count value.

    @param[in]  sem         A pointer to a caller allocated semaphore instance to be initialized.
    @param[in]  name        A pointer to a NULL terminated string that represents the name for the semaphore.
    @param[in]  initcnt     The intial count value for the semaphore. Must be greater than or equal to zero, and must be
                            less than or equal to 'maxcnt'.
    @param[in]  maxcnt      The maximum count value for the semaphore. Must be greater than zero.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The semaphore has been created and initialized.
     ERR_NULLREFERENCE      | The argument 'sem' was found to be NULL.
     ERR_INVALIDCONTEXT     | The operation is not supported from the context of an interrupt service routine (ISR).
     ERR_INVALIDARGUMENT    | The argument 'initcnt' or 'maxcnt' was invalid.
     ERR_ALREADYINITIALIZED | The specified semaphore has already been created and initialized.

    @module     kernel-semaphore

*******************************************************************************************************************************************/
STATUS SEMAPHORE_Create(SEMAPHORE* sem, const CHAR* name, UINT32 initcnt, UINT32 maxcnt)
{
    INTERRUPTLOCK lock;


#if (CFG_CONTEXTCHECKING)
    if (KERNEL_IsISR()) {
        return ERR_INVALIDCONTEXT;
    }
#endif
    
#if (CFG_NULLCHECKING)
    if (sem == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif

    if (maxcnt == 0) {
        return ERR_INVALIDARGUMENT;
    }

    if (initcnt > maxcnt) {
        return ERR_INVALIDARGUMENT;
    }
    
    ACQUIREINTERRUPTLOCK();
    
    if (sem->node.list == &kernel_semaphores) {                 /* Has the semaphore already been initialized? */
        RELEASEINTERRUPTLOCK();
        return ERR_ALREADYINITIALIZED;
    }
    
    RELEASEINTERRUPTLOCK();
    
    sem->name = name;                                           /* Initialize the semaphore */
    sem->count = initcnt;                                       /* Assign initial count values */
    sem->maxcount = maxcnt;
    
    ACQUIREINTERRUPTLOCK();
    
    LIST_AddLast(&kernel_semaphores, &sem->node, sem);          /* Register the semaphore with the kernel */
    
    RELEASEINTERRUPTLOCK();
    return SUCCESS;
}

/***************************************************************************************************************************************//**

    Destroys and removes a semaphore from the kernel. Any threads that happen to be waiting to acquire the semaphore will be released 
    with the ERR_DESTROYED status code.

    @param[in]  sem         A pointer to the semaphore to be destroyed.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The semaphore has been destroyed and removed from the kernel.
     ERR_NULLREFERENCE      | The argument 'sem' was found to be NULL.
     ERR_INVALIDCONTEXT     | The operation is not supported from the context of an interrupt service routine (ISR).
     ERR_NOTINITIALIZED     | The specified semaphore has not been created and initialized.

    @module     kernel-semaphore

*******************************************************************************************************************************************/
STATUS SEMAPHORE_Destroy(SEMAPHORE* sem)
{
    INTERRUPTLOCK lock;


#if (CFG_CONTEXTCHECKING)
    if (KERNEL_IsISR()) {
        return ERR_INVALIDCONTEXT;
    }
#endif
    
#if (CFG_NULLCHECKING)
    if (sem == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif
    
    ACQUIREINTERRUPTLOCK();
    
    if (sem->node.list != &kernel_semaphores) {                 /* Has the specified semaphore been initialized? */
        RELEASEINTERRUPTLOCK();
        return ERR_NOTINITIALIZED;
    }
    
    LIST_Remove(&kernel_semaphores, &sem->node);                /* Remove the semaphore from the kernel */
    RELEASEINTERRUPTLOCK();
    
    KERNEL_ReleaseAll(&sem->threads, ERR_DESTROYED);            /* Release any and all blocked threads upon this semaphore */
    KERNEL_ContextSwitch();                                     /* Possibly switch threads */
    return SUCCESS;
}

/***************************************************************************************************************************************//**

    Acquires a semaphore. If the semaphore's count is non-zero, the semaphore's count is decremented and the call returns without
    blocking. If the semaphore's count is zero, this call will block until the semaphore's count is incremented or until the specified 
    timeout interval elapses.

    @param[in]  sem         A pointer to the semaphore to wait upon to be signaled.
    @param[in]  timeout     A maximum amount of time, in kernel ticks, to block and wait for the semaphore to become signaled. Use '0' to 
                            return immediately without blocking. Use 'INFINITE' to block indefinitely.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The semaphore has been acquired.
     ERR_NULLREFERENCE      | The argument 'sem' was found to be NULL.
     ERR_INVALIDCONTEXT     | The operation is not supported from the context of an interrupt service routine (ISR).
     ERR_NOTINITIALIZED     | The specified semaphore has not been created and initialized.
     ERR_TIMEOUT            | The timeout period has elapsed prior to the semaphore becoming signaled.

    @module     kernel-semaphore

*******************************************************************************************************************************************/
STATUS SEMAPHORE_Acquire(SEMAPHORE* sem, UINT32 timeout)
{
    INTERRUPTLOCK lock;


#if (CFG_CONTEXTCHECKING)
    if (KERNEL_IsISR()) {                                         /* Is the caller an ISR? */
        return ERR_INVALIDCONTEXT;
    }
#endif
    
#if (CFG_NULLCHECKING)
    if (sem == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif

    ACQUIREINTERRUPTLOCK();

    if (sem->node.list != &kernel_semaphores) {                 /* Has the specified semaphore been initialized? */
        RELEASEINTERRUPTLOCK();
        return ERR_NOTINITIALIZED;
    }
    
    if (sem->count) {                                           /* Is the semaphore's count zero? */
        sem->count--;                                           /* It's positive, no need to block the caller */
        RELEASEINTERRUPTLOCK();
        return SUCCESS;
    }
    
    if (timeout == 0) {                                         /* Is requested to not block and return immediately? */
        RELEASEINTERRUPTLOCK();
        return ERR_TIMEOUT;                                     /* Return timeout without blocking */
    }

    KERNEL_Block(sem, &sem->threads, timeout);                  /* Count is zero, block the caller */
    
    RELEASEINTERRUPTLOCK();
    KERNEL_ContextSwitch();                                     /* Caller blocked, switch threads */
    return kernel.thread->status;                               /* Caller released, return result */
}

/***************************************************************************************************************************************//**

    Releases a semaphore and increments the semaphore's count by the specified amount. If there are any threads blocked on the semaphore, 
    each increment in the count can release one of the blocked threads.

    @param[in]  sem         A pointer to the semaphore to be released.
    @param[in]  count       The amount in which the specified semaphore's count should be increased. Must be greater than zero.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The semaphore has been released and its count has been updated.
     ERR_NULLREFERENCE      | The argument 'sem' was found to be NULL.
     ERR_INVALIDARGUMENT    | The argument 'count' was invalid. Must be greater than zero.
     ERR_NOTINITIALIZED     | The specified semaphore has not been created and initialized.

    @module     kernel-semaphore

*******************************************************************************************************************************************/
STATUS SEMAPHORE_Release(SEMAPHORE* sem, UINT32 count)
{
    INTERRUPTLOCK lock;
    THREAD* thread;
    UINT32 num;
    UINT32 idx;


#if (CFG_NULLCHECKING)
    if (sem == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif
    
    if (count == 0) {
        return ERR_INVALIDARGUMENT;
    }

    num = count;

    ACQUIREINTERRUPTLOCK();
    
    if (sem->node.list != &kernel_semaphores) {                 /* Has the specified semaphore been initialized? */
        RELEASEINTERRUPTLOCK();
        return ERR_NOTINITIALIZED;
    }

    if (num > (sem->maxcount - sem->count)) {                   /* Bound the requested count to the maximum allowable */
        num = (sem->maxcount - sem->count);
    }
    
    for (idx = 0; idx < num; idx++) {                           /* Release the specified count */
        thread = KERNEL_ReleaseOne(&sem->threads, SUCCESS);       /* Attempt to release a waiting thread */
        if (thread == NULL) {                                   /* Was a thread released? */
            sem->count += (num - idx);                          /* No thread released, increment the semaphore's count */
            break;
        }                                      
    }

    RELEASEINTERRUPTLOCK();
    KERNEL_ContextSwitch();                                     /* Possibly switch threads */
    return SUCCESS;
}

/***************************************************************************************************************************************//**

    Returns the current count for a semaphore.

    @param[in]  sem         A pointer to the target semaphore.

    @return     The current count for the specified semaphore.
    @module     kernel-semaphore

*******************************************************************************************************************************************/
UINT32 SEMAPHORE_Count(SEMAPHORE* sem)
{
    INTERRUPTLOCK lock;
    UINT32 count;
    
    
#if (CFG_NULLCHECKING)
    if (sem == NULL) {
        return 0;
    }
#endif
    
    ACQUIREINTERRUPTLOCK(); 
    
    if (sem->node.list != &kernel_semaphores) {                 /* Has the specified semaphore been initialized? */
        RELEASEINTERRUPTLOCK();
        return 0;
    }
    
    count = sem->count;                                         /* Capture the current count for the semaphore */
    
    RELEASEINTERRUPTLOCK();
    return count;
}
