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
#ifndef KERNEL_MUTEX_H__
#define KERNEL_MUTEX_H__

#include "Kernel/kernel_thread.h"

/*******************************************************************************************************************************************
    TYPE DEFINITIONS
*******************************************************************************************************************************************/
typedef struct MUTEX MUTEX;

/***************************************************************************************************************************************//**

    A mutually exclusive lock mechanism that is used for thread synchronization purposes.
    @module     kernel-mutex

*******************************************************************************************************************************************/
struct MUTEX {
    NODE        node;               /**< A node for registering the mutex within the kernel */
    const CHAR* name;               /**< A name for the mutex */
	LIST        threads;            /**< A list of blocked threads waiting to acquire the mutex */
    THREAD*     owner;              /**< A pointer to the thread that owns the mutex */
	UINT32      nesting;            /**< A count used for supporting nested acquire/release calls on the mutex */
};

/*******************************************************************************************************************************************
    PUBLIC FUNCTIONS
*******************************************************************************************************************************************/
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
extern STATUS MUTEX_Create(MUTEX* mutex, const CHAR* name, BOOLEAN owner);

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
extern STATUS MUTEX_Destroy(MUTEX* mutex);

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
extern STATUS MUTEX_Acquire(MUTEX* mutex, UINT32 timeout);

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
extern STATUS MUTEX_Release(MUTEX* mutex);

#endif /* KERNEL_MUTEX_H__ */
