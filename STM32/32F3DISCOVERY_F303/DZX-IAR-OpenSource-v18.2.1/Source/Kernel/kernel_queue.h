/*******************************************************************************************************************************************

    DZX | KERNEL | QUEUE                                                                                                  VERSION 18.2.1
    ------------------------------------------------------------------------------------------------------------------------------------

    This file is part of the kernel and provides support for object queues. A queue is a first-in first-out (FIFO) collection of 
    objects. Queues store objects by keeping references (pointers) to the objects they contain. Insertion and removal of objects from 
    queues are fast and deterministic which provides the ability to use them from either the context of threads or interrupt service 
    routines (ISR). 

    A queue only keeps a reference (pointer) to the objects it contains; therefore, it is required that the object remains valid during 
    the entire time it is contained within a queue (i.e. it is not created on stack memory that is lost on breaking scope).

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
#ifndef KERNEL_QUEUE_H__
#define KERNEL_QUEUE_H__

#include "Kernel/kernel_list.h"

#if (CFG_STATISTICS)
/*******************************************************************************************************************************************

    Represents run-time statistics for a queue.
    @module     internal

*******************************************************************************************************************************************/
typedef struct QUEUESTATS {
    UINT32 total;                       /**< The total number of objects that have gone through the queue */
    UINT32 maxcount;                    /**< The maximum number of objects that have ever been contained within the queue */
} QUEUESTATS;
#endif

/*******************************************************************************************************************************************
    TYPE DEFINITIONS
*******************************************************************************************************************************************/
typedef struct QUEUE QUEUE;

/***************************************************************************************************************************************//**

    Represents a slot that points to an object within a queue.
    @module     kernel-queue

*******************************************************************************************************************************************/
typedef void* QUEUESLOT;

/***************************************************************************************************************************************//**

    A circular first-in first-out queue.
    @module     kernel-queue

*******************************************************************************************************************************************/
struct QUEUE {
    NODE        node;                   /**< Allocation of a node to place the queue into a list */
    const CHAR* name;                   /**< A name for the queue */
    QUEUESLOT*  slots;                  /**< A pointer to the creator allocated slots */
    UINT32      rdx;                    /**< The current zero-based reading index position */
    UINT32      wrx;                    /**< The current zero-based writing index position */
    UINT32      cnt;                    /**< The total number of items currently within the queue */
    UINT32      capacity;               /**< The maximum number of items to be contained within the queue */
    LIST        writers;                /**< A list of threads blocked waiting to write the queue */
    LIST        readers;                /**< A list of threads blocked waiting to read the queue */

#if (CFG_STATISTICS)
    QUEUESTATS  stats;                  /**< Runtime statistics for the queue */
#endif
};

/*******************************************************************************************************************************************
    PUBLIC FUNCTIONS
*******************************************************************************************************************************************/
/***************************************************************************************************************************************//**

    Creates and initializes a queue.

    @param[in]  queue       A pointer to a caller allocated queue instance to be intialized.
    @param[in]  name        A pointer to a NULL terminated string that represents the name for the queue.
    @param[in]  slots       A pointer to a caller allocated array of slots used to reference the objects contained within the queue.
    @param[in]  capacity    The maximum number of objects that can be contained within the queue. Must be larger than zero.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The queue has been created and initialized.
     ERR_NULLREFERENCE      | The argument 'q' or 'slots' was found to be NULL.
     ERR_INVALIDCONTEXT     | The operation is not supported from the context of an interrupt service routine (ISR).
     ERR_INVALIDARGUMENT    | The argument 'capacity' was invalid. Must be larger than zero.
     ERR_ALREADYINITIALIZED | The specified queue has already been created and initialized.

    @remark     The caller allocated array of slots must be able to contain the maximum capacity for the queue.
    @module     kernel-queue

*******************************************************************************************************************************************/
extern STATUS QUEUE_Create(QUEUE* queue, const CHAR* name, QUEUESLOT* slots, UINT32 capacity);

/***************************************************************************************************************************************//**

    Destroys and removes a queue from the kernel. Any threads that are currently blocked waiting to read or write the queue will be 
    released with the ERR_DESTROYED status code.

    @param[in]  queue       A pointer to a queue to be destroyed.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The queue was destroyed and removed from the kernel.
     ERR_NULLREFERENCE      | The argument 'queue' was found to be NULL.
     ERR_INVALIDCONTEXT     | The operation is not supported from the context of an interrupt service routine (ISR).
     ERR_NOTINITIALIZED     | The specified queue has not been created and initialized.

    @module     kernel-queue

*******************************************************************************************************************************************/
extern STATUS QUEUE_Destroy(QUEUE* queue);

/***************************************************************************************************************************************//**

    Inserts an object into a queue.

    @param[in]  queue       A pointer to the target queue to receive the object.
    @param[in]  obj         A pointer to the object to be placed into the queue.
    @param[in]  timeout     The maximum amount of time, in kernel ticks, to block and wait for the object to be inserted if the queue 
                            happens to be full. Use '0' to return immediately without blocking. Use 'INFINITE' to block indefinitely.
    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The object was successfully inserted into the queue.
     ERR_NULLREFERENCE      | The argument 'queue' or 'obj' was found to be NULL.
     ERR_NOTINITIALIZED     | The specified queue has not been created and initialized.
     ERR_TIMEOUT            | The timeout interval elapsed before the queue acquired an available slot for the object.

    @remark     Can be called from ISR, but cannot block if the queue is full (timeout is ignored).
    @module     kernel-queue

*******************************************************************************************************************************************/
extern STATUS QUEUE_Enqueue(QUEUE* queue, void* obj, UINT32 timeout);

/***************************************************************************************************************************************//**

    Removes and returns an object from a queue.

    @param[in]  queue       A pointer to the queue that contains the object to be removed.
    @param[in]  timeout     The maximum amount of time, in kernel ticks, to block and wait for an object to arrive if the queue happens to
                            be empty. Use '0' to return immediately without blocking. Use 'INFINITE' to block indefinitely.

    @return     A pointer to the object that has been removed from the queue, if any; otherwise NULL.
    @remark     Can be called from ISR, but cannot block if the queue is empty (timeout is ignored).
    @module     kernel-queue

*******************************************************************************************************************************************/
extern void* QUEUE_Dequeue(QUEUE* queue, UINT32 timeout);

/***************************************************************************************************************************************//**

    Reads and returns an object from a queue without removing the object from the queue.

    @param[in]  queue       A pointer to the queue that contains the object to be returned.
    @param[in]  idx         The zero based index of the object to be returned.

    @return     A pointer to the object at the specified index, if any; otherwise NULL.
    @module     kernel-queue

*******************************************************************************************************************************************/
extern void* QUEUE_Peek(QUEUE* queue, UINT32 idx);

/***************************************************************************************************************************************//**

    Clears and removes all objects from a queue.

    @param[in]  queue       A pointer to the queue to be cleared.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The queue has been cleared.
     ERR_NULLREFERENCE      | The argument 'queue' was found to be NULL.
     ERR_NOTINITIALIZED     | The specified queue has not been created and initialized.

    @module     kernel-queue

*******************************************************************************************************************************************/
extern STATUS QUEUE_Clear(QUEUE* queue);

/***************************************************************************************************************************************//**

    Returns the number of objects currently contained within a queue.

    @param[in]  queue       A pointer to the target queue.

    @return     The total number of objects currently within the given queue.
    @module     kernel-queue

*******************************************************************************************************************************************/
extern UINT32 QUEUE_Count(QUEUE* queue);

#endif /* KERNEL_QUEUE_H__ */
