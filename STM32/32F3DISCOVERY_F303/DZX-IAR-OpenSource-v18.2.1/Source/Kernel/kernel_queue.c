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
#include "kernel_queue.h"
#include "kernel_core.h"

/*******************************************************************************************************************************************
    PRIVATE VARIABLES
*******************************************************************************************************************************************/
static LIST kernel_queues;

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
STATUS QUEUE_Create(QUEUE* queue, const CHAR* name, QUEUESLOT* slots, UINT32 capacity)
{
    INTERRUPTLOCK lock;
    
    
#if (CFG_CONTEXTCHECKING)
    if (KERNEL_IsISR()) {
        return ERR_INVALIDCONTEXT;
    }
#endif
    
#if (CFG_NULLCHECKING)
    if (queue == NULL) {
        return ERR_NULLREFERENCE;
    }

    if (slots == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif
    
    if (capacity == 0) {
        return ERR_INVALIDARGUMENT;                             /* Must have a capacity larger than zero */
    }

    ACQUIREINTERRUPTLOCK();
    
    if (queue->node.list == &kernel_queues) {                   /* Has the queue already been initialized? */
        RELEASEINTERRUPTLOCK();
        return ERR_ALREADYINITIALIZED;
    }
    
    RELEASEINTERRUPTLOCK();
    
    queue->name = name;                                         /* Initialize the queue */
    queue->slots = slots;
    queue->rdx = 0;
    queue->wrx = 0;
    queue->capacity = capacity;

    LIST_Clear(&queue->writers);                                /* Initialize the list of threads blocked waiting to read the queue */
    LIST_Clear(&queue->readers);                                /* Initialize the list of threads blocked waiting to write the queue */
    
    
#if (CFG_STATISTICS)
    queue->stats.total = 0;                                     /* Initialize run-time statistics */
    queue->stats.maxcount = 0;
#endif

    ACQUIREINTERRUPTLOCK();
    
    LIST_AddLast(&kernel_queues, &queue->node, queue);          /* Register the queue within the kernel */
    
    RELEASEINTERRUPTLOCK();
    return SUCCESS;
}

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
STATUS QUEUE_Destroy(QUEUE* queue)
{
    INTERRUPTLOCK lock;

    
#if (CFG_CONTEXTCHECKING)
    if (KERNEL_IsISR()) {
        return ERR_INVALIDCONTEXT;
    }
#endif
    
#if (CFG_NULLCHECKING)
    if (queue == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif

    ACQUIREINTERRUPTLOCK();
    
    if (queue->node.list != &kernel_queues) {                   /* Has the queue been initialized? */
        RELEASEINTERRUPTLOCK();
        return ERR_NOTINITIALIZED;
    }
    
    LIST_Remove(&kernel_queues, &queue->node);                  /* Remove the queue from the kernel */
    RELEASEINTERRUPTLOCK();
    
    KERNEL_ReleaseAll(&queue->readers, ERR_DESTROYED);          /* Release any threads blocked waiting to read from the queue */
    KERNEL_ReleaseAll(&queue->writers, ERR_DESTROYED);          /* Release any threads blocked waiting to write to the queue */
    
    KERNEL_ContextSwitch();                                     /* Possibly switch threads */
    return SUCCESS;
}

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
STATUS QUEUE_Enqueue(QUEUE* queue, void* obj, UINT32 timeout)
{
  	INTERRUPTLOCK lock;
    THREAD* reader;


#if (CFG_NULLCHECKING)
    if (queue == NULL) {
        return ERR_NULLREFERENCE;
    }

    if (obj == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif

    ACQUIREINTERRUPTLOCK();
    
    if (queue->node.list != &kernel_queues) {                   /* Has the specified queue been initialized? */
        RELEASEINTERRUPTLOCK();
        return ERR_NOTINITIALIZED;
    }

    if (queue->cnt >= queue->capacity) {                        /* Is the queue full? */

        if (timeout == 0) {                                     /* Is requested to not block and return immediately? */
            RELEASEINTERRUPTLOCK();
            return ERR_TIMEOUT;                                 /* Return timeout without blocking */
        }
        
        if (KERNEL_IsISR()) {                                   /* Is the caller an ISR? */
            RELEASEINTERRUPTLOCK();
            return ERR_TIMEOUT;                                 /* Would block, but the caller is not a thread */
        }
        
        kernel.thread->args[0] = obj;                           /* Keep a reference to the object to be inserted */
        KERNEL_Block(queue, &queue->writers, timeout);          /* Put the calling thread into the blocked state */
        
        RELEASEINTERRUPTLOCK();
        KERNEL_ContextSwitch();                                 /* Blocked the caller, switch threads */
        return kernel.thread->status;                           /* Return the result of the block */
    }

    if (queue->readers.first) {                                 /* Is there a thread waiting to read the queue? */
        
        reader = KERNEL_ReleaseOne(&queue->readers, SUCCESS);   /* Release the next thread waiting to read the queue */
        reader->args[0] = (void*)obj;                           /* Write the object directly to the waiting thread */
        
#if (CFG_STATISTICS)
        queue->stats.total++;                                   /* Keep a count of total objects passed through the queue */
#endif
    
        RELEASEINTERRUPTLOCK();
        KERNEL_ContextSwitch();                                 /* Possibly switch threads */
        return SUCCESS;
    }

    queue->slots[queue->wrx] = obj;                             /* Insert the object into the queue */
    queue->wrx = (queue->wrx + 1) % queue->capacity;            /* Move to the next slot */
    queue->cnt++;                                               /* Update the queue's object count */

#if (CFG_STATISTICS)
    queue->stats.total++;                                       /* Keep a count of total objects passed through the queue */
    
    if (queue->cnt > queue->stats.maxcount) {                   /* Is this the most objects that have ever been in the queue? */
        queue->stats.maxcount = queue->cnt;                     /* Yes, capture this number */
    }
#endif

    RELEASEINTERRUPTLOCK();
    return SUCCESS;
}

/***************************************************************************************************************************************//**

    Removes and returns an object from a queue.

    @param[in]  queue       A pointer to the queue that contains the object to be removed.
    @param[in]  timeout     The maximum amount of time, in kernel ticks, to block and wait for an object to arrive if the queue happens to
                            be empty. Use '0' to return immediately without blocking. Use 'INFINITE' to block indefinitely.

    @return     A pointer to the object that has been removed from the queue, if any; otherwise NULL.
    @remark     Can be called from ISR, but cannot block if the queue is empty (timeout is ignored).
    @module     kernel-queue

*******************************************************************************************************************************************/
void* QUEUE_Dequeue(QUEUE* queue, UINT32 timeout)
{
  	INTERRUPTLOCK lock;
    THREAD* writer;
    void* obj;


#if (CFG_NULLCHECKING)
    if (queue == NULL) {
        return NULL;
    }
#endif

    ACQUIREINTERRUPTLOCK();
    
    if (queue->node.list != &kernel_queues) {                   /* Has the queue been initialized? */
        RELEASEINTERRUPTLOCK();
        return NULL;
    }

    if (queue->cnt == 0) {                                      /* Is the queue empty? */

        if (timeout == 0) {                                     /* Is requested to not block and return immediately? */
            RELEASEINTERRUPTLOCK();
            return NULL;                                        /* Return timeout without blocking */
        }
        
        if (KERNEL_IsISR()) {                                   /* Is the caller an ISR? */
            RELEASEINTERRUPTLOCK();
            return NULL;                                        /* Would block, but caller is not a thread */
        }
        
        kernel.thread->args[0] = NULL;                          /* Initialize thread local storage */
        kernel.thread->args[1] = 0;
        KERNEL_Block(queue, &queue->readers, timeout);          /* Block the calling thread */
        
        RELEASEINTERRUPTLOCK();
        KERNEL_ContextSwitch();                                 /* Blocked the caller, switch threads */
        return kernel.thread->args[0];                          /* Return the reference to the object */             
    }

    obj = queue->slots[queue->rdx];                             /* Read the next object from the queue */
    queue->rdx = (queue->rdx + 1) % queue->capacity;            /* Remove the object from the queue */

    if (queue->writers.first) {                                 /* Is there a thread waiting to write the queue? */
        writer = KERNEL_ReleaseOne(&queue->writers, SUCCESS);   /* Release the waiting thread */
        queue->slots[queue->wrx] = writer->args[0];             /* Insert the object into the queue */
        queue->wrx = (queue->wrx + 1) % queue->capacity;        /* Move to the next slot */
        
#if (CFG_STATISTICS)
        queue->stats.total++;                                   /* Keep a count of total objects passed through the queue */
#endif
        
        RELEASEINTERRUPTLOCK();
        KERNEL_ContextSwitch();
        return obj;
    }

    queue->cnt--;                                               /* Update the count of objects */
    
    RELEASEINTERRUPTLOCK();
    return obj;
}

/***************************************************************************************************************************************//**

    Reads and returns an object from a queue without removing the object from the queue.

    @param[in]  queue       A pointer to the queue that contains the object to be returned.
    @param[in]  idx         The zero based index of the object to be returned.

    @return     A pointer to the object at the specified index, if any; otherwise NULL.
    @module     kernel-queue

*******************************************************************************************************************************************/
void* QUEUE_Peek(QUEUE* queue, UINT32 idx)
{
  	INTERRUPTLOCK lock;
    void* obj;
    UINT32 i;


#if (CFG_NULLCHECKING)
    if (queue == NULL) {
        return NULL;
    }
#endif

    ACQUIREINTERRUPTLOCK();
    
    if (queue->node.list != &kernel_queues) {                   /* Has the queue been initialized? */
        RELEASEINTERRUPTLOCK();
        return NULL;
    }

    if (idx >= queue->cnt) {                                    /* Does the index reference an object within the queue? */
        RELEASEINTERRUPTLOCK();
        return NULL;
    }

    i = (queue->rdx + idx) % queue->capacity;                   /* Calculate the read index for the zero-based index */
    obj = queue->slots[i];                                      /* Read the object from the queue */
    
    RELEASEINTERRUPTLOCK();
    return obj;
}

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
STATUS QUEUE_Clear(QUEUE* queue)
{
    INTERRUPTLOCK lock;
    THREAD* writer;


#if (CFG_NULLCHECKING)
    if (queue == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif

    ACQUIREINTERRUPTLOCK();
    
    if (queue->node.list != &kernel_queues) {                   /* Has the queue been initialized? */
        RELEASEINTERRUPTLOCK();
        return ERR_NOTINITIALIZED;
    }

    queue->rdx = 0;                                             /* Empty the queue */
    queue->wrx = 0;
    queue->cnt = 0;

    while (queue->writers.first) {                              /* Any threads waiting to write the queue? */
        writer = KERNEL_ReleaseOne(&queue->writers, SUCCESS);   /* Get the first thread waiting to write the queue */

        queue->slots[queue->wrx] = writer->args[0];             /* Write the queue as requested by the blocked thread */
        queue->wrx = (queue->wrx + 1) % queue->capacity;        /* Move to the next slot */
        queue->cnt++;                                           /* Keep count of objects within the queue */

        RELEASEINTERRUPTLOCK();
        KERNEL_ContextSwitch();                                 /* Possibly switch threads */
        
        ACQUIREINTERRUPTLOCK();
        
        if (queue->cnt >= queue->capacity) {                    /* Is there any free space remaining within the queue? */
            RELEASEINTERRUPTLOCK();                             /* Out of free space, done releasing blocked threads */
            return SUCCESS;
        }
    }

    RELEASEINTERRUPTLOCK();
    return SUCCESS;
}

/***************************************************************************************************************************************//**

    Returns the number of objects currently contained within a queue.

    @param[in]  queue       A pointer to the target queue.

    @return     The total number of objects currently within the given queue.
    @module     kernel-queue

*******************************************************************************************************************************************/
UINT32 QUEUE_Count(QUEUE* queue)
{
    INTERRUPTLOCK lock;
    UINT32 cnt = 0;


#if (CFG_NULLCHECKING)
    if (queue == NULL) {
        return 0;
    }
#endif

    ACQUIREINTERRUPTLOCK();
    
    if (queue->node.list != &kernel_queues) {                   /* Has the queue been initialized? */
        RELEASEINTERRUPTLOCK();
        return 0;
    }
    
    cnt = queue->cnt;                                           /* Capture the current count in within a thread and ISR safe lock */
    
    RELEASEINTERRUPTLOCK();
    return cnt;
}
