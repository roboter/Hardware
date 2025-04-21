/*******************************************************************************************************************************************

    DZX | KERNEL | BUFFER                                                                                                 VERSION 18.2.1
    ------------------------------------------------------------------------------------------------------------------------------------

    This file is part of the kernel and provides support for circular buffers. A circular buffer is a byte-wide copy-in/copy-out 
    first-in first-out (FIFO) storage of generic data. A buffer provides the ability to block threads that are attempting to read data 
    from or write data to the buffer. Data can be written to and read from the buffer from any context, including either a thread or an 
    interrupt service routine (ISR).

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
#include "kernel_buffer.h"
#include "kernel_core.h"
#include <string.h>

/*******************************************************************************************************************************************
    PRIVATE VARIABLES
*******************************************************************************************************************************************/
static LIST kernel_buffers;

/***************************************************************************************************************************************//**

    Creates and initializes a circular buffer.

    @param[in]  b           A pointer to a caller allocated buffer instance to be initialized.
    @param[in]  name        A pointer to a NULL terminated string that represents the name for the buffer.
    @param[in]  mem         A pointer to a caller allocated array of memory that will hold the contents of the buffer.
    @param[in]  capacity    The maximum amount of data, in bytes, that the buffer can contain. Should be the same size as the provided
                            array of memory.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The buffer was created and initialized.
     ERR_NULLREFERENCE      | The argument 'b' or 'mem' was found to be NULL.
     ERR_INVALIDCONTEXT     | The operation is not supported from the context of an interrupt service routine (ISR).
     ERR_ALREADYINITIALIZED | The specified buffer has already been created and initialized.

    @module     kernel-buffer

*******************************************************************************************************************************************/
STATUS BUFFER_Create(BUFFER* b, const CHAR* name, void* mem, UINT32 capacity)
{
    INTERRUPTLOCK lock;
    
    
#if (CFG_CONTEXTCHECKING)
    if (KERNEL_IsISR()) {
        return ERR_INVALIDCONTEXT;
    }
#endif
    
#if (CFG_NULLCHECKING)
    if (b == NULL) {
        return ERR_NULLREFERENCE;
    }

    if (mem == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif

    ACQUIREINTERRUPTLOCK();
    
    if (b->node.list == &kernel_buffers) {                      /* Has the buffer already been initialized? */
        RELEASEINTERRUPTLOCK();
        return ERR_ALREADYINITIALIZED;
    }
    
    RELEASEINTERRUPTLOCK();
    
    b->name = name;                                             /* Initialize the buffer */
    b->rdx = 0;
    b->wrx = 0;
    b->count = 0;
    b->mem = mem;
    b->capacity = capacity;
    
    b->reader = NULL;
    b->writer = NULL;
    
    LIST_Init(&b->readers);                                     /* Initialize the lists of threads blocked upon the buffer */
    LIST_Init(&b->writers);
    
    ACQUIREINTERRUPTLOCK();
    
    LIST_AddLast(&kernel_buffers, &b->node, b);                 /* Register the buffer with the kernel */
    
    RELEASEINTERRUPTLOCK();
    return SUCCESS;
}

/***************************************************************************************************************************************//**

    Destroys and removes a buffer from the kernel. Any threads that happen to be blocked waiting to write or read from the buffer will be 
    released with the ERR_DESTROYED status code.

    @param[in]  b       A pointer to a buffer to be destroyed.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The buffer was destroyed and removed from the kernel.
     ERR_NULLREFERENCE      | The argument 'b' was found to be NULL.
     ERR_INVALIDCONTEXT     | This operation is not supported from the context of an interrupt service routine (ISR).
     ERR_NOTINITIALIZED     | The specified buffer has not been created or initialized.

    @module     kernel-buffer

*******************************************************************************************************************************************/
STATUS BUFFER_Destroy(BUFFER* b)
{
    INTERRUPTLOCK lock;


#if (CFG_CONTEXTCHECKING)
    if (KERNEL_IsISR()) {
        return ERR_INVALIDCONTEXT;
    }
#endif
    
#if (CFG_NULLCHECKING)
    if (b == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif

    ACQUIREINTERRUPTLOCK();
        
    if (b->node.list != &kernel_buffers) {                      /* Has the buffer been initialized? */
        RELEASEINTERRUPTLOCK();
        return ERR_NOTINITIALIZED;
    }
    
    LIST_Remove(&kernel_buffers, &b->node);                     /* Remove the buffer from the kernel */
    RELEASEINTERRUPTLOCK();
    
    KERNEL_ReleaseAll(&b->readers, ERR_DESTROYED);              /* Release any blocked thread waiting to read from the buffer */
    KERNEL_ReleaseAll(&b->writers, ERR_DESTROYED);              /* Release any blocked thread waiting to write to the buffer */
    return SUCCESS;
}

/***************************************************************************************************************************************//**

    Clears and removes all contents of a buffer.

    @param[in]  b           A pointer to the buffer to be cleared.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The buffer has been cleared.
     ERR_NULLREFERENCE      | The argument 'b' was found to be NULL.
     ERR_NOTINITIALIZED     | The specified buffer has not been created or initialized.

    @module     kernel-buffer

*******************************************************************************************************************************************/
STATUS BUFFER_Clear(BUFFER* b)
{
    INTERRUPTLOCK lock;
    THREAD* writer;


#if (CFG_NULLCHECKING)
    if (b == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif

    ACQUIREINTERRUPTLOCK();
    
    if (b->node.list != &kernel_buffers) {                              /* Has the buffer been initialized? */
        RELEASEINTERRUPTLOCK();
        return ERR_NOTINITIALIZED;
    }
    
    if (b->reader) {                                                    /* Is there a thread concurrently reading this buffer? */
        RELEASEINTERRUPTLOCK();
        return ERR_ACCESSDENIED;
    }
    
    if (b->writer) {                                                    /* Is there a thread concurrently writing to this buffer? */
        RELEASEINTERRUPTLOCK();
        return ERR_ACCESSDENIED;
    }

    b->wrx = 0;                                                         /* Reset the indexes and current count */
    b->rdx = 0;
    b->count = 0;

    if (b->writers.first) {                                             /* Is there a thread waiting to write the buffer? */
        writer = b->writers.first->value;                               /* Get the first thread waiting to write the buffer */                                                    
        if ((b->capacity - b->count) >= (UINT32)(writer->args[0])) {    /* Is the blocked thread's request now fulfilled? */
            KERNEL_ReleaseOne(&b->writers, SUCCESS);                    /* Yes, release the waiting thread */
            
            RELEASEINTERRUPTLOCK();
            KERNEL_ContextSwitch();                                     /* Possibly switch threads */
            return SUCCESS;
        }
    }
    
    RELEASEINTERRUPTLOCK();
    return SUCCESS;
}

/***************************************************************************************************************************************//**

    Returns the capacity, in bytes, for a buffer.

    @param[in]  b           A pointer to the target buffer.

    @return     The specified buffer's capacity, in bytes.
    @module     kernel-buffer

*******************************************************************************************************************************************/
UINT32 BUFFER_Capacity(BUFFER* b)
{
#if (CFG_NULLCHECKING)
    if (b == NULL) {
        return 0;
    }
#endif
    
    return b->capacity;
}

/***************************************************************************************************************************************//**

    Returns the number of bytes currently contained within a buffer.

    @param[in]  b           A pointer to the target buffer.

    @return     The total number of bytes contained within the buffer.
    @module     kernel-buffer

*******************************************************************************************************************************************/
UINT32 BUFFER_Count(BUFFER* b)
{
    INTERRUPTLOCK lock;
    UINT32 count;


#if (CFG_NULLCHECKING)
    if (b == NULL) {
        return 0;
    }
#endif
    
    ACQUIREINTERRUPTLOCK();

    count = b->count;                                           /* Capture the current count of the buffer within the lock */
    
    RELEASEINTERRUPTLOCK();
    return count;
}

/***************************************************************************************************************************************//**

    Writes data to a circular buffer.

    @param[in]  b           A pointer to the buffer to receive the data.
    @param[in]  data        A pointer to the beginning of the data to be written into the buffer.
    @param[in]  nbytes      The total number of data bytes to be written into the buffer.
    @param[out] actual      A pointer to a caller allocated value used to determine the actual number of bytes that have been written to
                            the buffer. Use 'NULL' to force either all or none of the data to be written.
    @param[in]  timeout     The maximum amount of time, in kernel ticks, to block and wait for sufficient space to fulfill the request.
                            Use 0 to return immediately without blocking and use INFINITE to wait indefinitely.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The data has been written to the buffer. Use 'actual' to determine the number of bytes actually written.
     ERR_NULLREFERENCE      | The argument 'b' or 'data' was found to be NULL.
     ERR_ACCESSDENIED       | The request is from an interrupt and the buffer was already being written by a thread.
     ERR_TIMEOUT            | The specified amount of time has elapsed before there was sufficient space within the buffer.

    @module     kernel-buffer

*******************************************************************************************************************************************/
STATUS BUFFER_Write(BUFFER* b, const void* data, UINT32 nbytes, UINT32* actual, UINT32 timeout)
{
    INTERRUPTLOCK lock;
    THREAD* thread;
    UINT32 wrap;
    UINT32 count;
    
    
#if (CFG_NULLCHECKING)
    if (b == NULL) { 
        return ERR_NULLREFERENCE;
    }
    
    if (data == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif
    
    if (actual) {
        *actual = 0;
    }

    if (KERNEL_IsISR()) {                                               /* Is the caller an interrupt service routine? */
        
        if (b->node.list != &kernel_buffers) {                          /* Has the buffer been initialized? */
            return ERR_NOTINITIALIZED;
        }
        
        if (b->writer) {                                                /* Is there a thread in-progress writing the buffer? */
            return ERR_ACCESSDENIED;
        }
        
        count = nbytes;                                                 /* Capture the amount of data to be written */
        if (count > (b->capacity - b->count)) {                         /* Can the requested data fit into the buffer? */
            
            if (actual == NULL) {
                return ERR_TIMEOUT;                                     /* Cannot fit, and cannot perform partial write */
            }
            
            count = b->capacity - b->count;                             /* Limit the data to the space available */
            
            if (count == 0) {
                return SUCCESS;                                         /* Partial writes allowed, but no space */
            }
        }
    
        if ((b->wrx + count) > b->capacity) {                           /* Will the write wrap? */
            wrap = b->capacity - b->wrx;                                /* Calculate the wrap point */
            memcpy(&((BYTE*)b->mem)[b->wrx], data, wrap);               /* Write data up to the wrap point */
            memcpy(b->mem, &((BYTE*)data)[wrap], count - wrap);         /* Complete the write after the wrap */
        } else {
            memcpy(&((BYTE*)b->mem)[b->wrx], data, count);              /* No wrap, write the data in a single operation */
        }
        
        b->wrx = (b->wrx + count) % b->capacity;                        /* Move to the next location to be written in the buffer */
        b->count += count;                                              /* Update the amount of contained data */
        
#if (CFG_STATISTICS)
        b->stats.total += count;                                        /* Keep record of total amount of data passed through */
        
        if (b->count > b->stats.maxcount) {                             
            b->stats.maxcount = b->count;                               /* Keep record of maximum amount of contained data */
        }
#endif
        
        if (b->reader == NULL) {
            if (b->readers.first) {
                thread = b->readers.first->value;                       /* Yes, get the blocked thread */
                
                if (b->count >= (UINT32)thread->args[0]) {              /* Is the requesting thread's data now available? */
                    b->reader = KERNEL_ReleaseOne(&b->readers, SUCCESS);    /* Yes, release the blocked thread */
                }
            }
        }
        
        return SUCCESS;
    }
    
    ACQUIREINTERRUPTLOCK();
    
    if (b->node.list != &kernel_buffers) {                              /* Has the buffer been initialized? */
        RELEASEINTERRUPTLOCK();
        return ERR_NOTINITIALIZED;
    }
    
    if (timeout > 0) {
        
        if (b->writer || b->writers.first ||                            /* Is there a concurrent access or not enough space available? */
            (b->count + nbytes) > b->capacity) {

            kernel.thread->args[0] = (void*)nbytes;                     /* No, store the amount of space required for this write request */
            KERNEL_Block(b, &b->writers, timeout);                      /* Put the caller into the blocked state */
            
            RELEASEINTERRUPTLOCK();
            KERNEL_ContextSwitch();                                     /* Blocked the calling thread; switch threads */
            
            if (actual == NULL) {
                if (kernel.thread->status != SUCCESS) {                 /* Was there an error while blocked? */
                    return kernel.thread->status;                       /* Yes, return the error code */
                }
            }
            
            ACQUIREINTERRUPTLOCK();
        }
    }
    
    b->writer = kernel.thread;
    
    count = nbytes;                                                     /* Capture the amount of data to be written */
    if (count > (b->capacity - b->count)) {                             /* Can the requested data fit into the buffer? */
      
        count = b->capacity - b->count;                                 /* Limit the data to the space available */
        if (count == 0) {
            b->writer = NULL;
            RELEASEINTERRUPTLOCK();
            return SUCCESS;                                             /* Partial writes allowed, but no space */
        }
    }

    RELEASEINTERRUPTLOCK();
            
    if ((b->wrx + count) > b->capacity) {                               /* Will the write wrap? */
        wrap = b->capacity - b->wrx;                                    /* Yes, calculate the wrap point */
        memcpy(&((BYTE*)b->mem)[b->wrx], data, wrap);                   /* Write data up to the wrap point */
        memcpy(b->mem, &((BYTE*)data)[wrap], count - wrap);             /* Complete the write after the wrap */
    } else {
        memcpy(&((BYTE*)b->mem)[b->wrx], data, count);                  /* No wrap, write the data in a single operation */
    }
    
    if (actual) {
        *actual = count;
    }
            
    ACQUIREINTERRUPTLOCK();
    
    b->wrx = (b->wrx + count) % b->capacity;                            /* Update the writing index location */
    b->count += count;                                                  /* Update the amount of data contained within the buffer */
    b->writer = NULL;                                                   /* Release the reference to the thread writing this buffer */
    
    
#if (CFG_STATISTICS)
    b->stats.total += count;                                            /* Keep record of total amount of data passed through */
    
    if (b->count > b->stats.maxcount) {                             
        b->stats.maxcount = b->count;                                   /* Keep record of maximum amount of contained data */
    }
#endif
    
    if (b->writers.first) {                                             /* Is there another thread blocked waiting to write the buffer? */
        thread = b->writers.first->value;                               /* Yes, get the blocked thread */
        
        if ((b->capacity - b->count) >= (UINT32)thread->args[0]) {      /* Is there space for the thread's data? */
            b->writer = KERNEL_ReleaseOne(&b->writers, SUCCESS);        /* Yes, release the blocked thread */
        }
    }
    
    RELEASEINTERRUPTLOCK();

    ACQUIREINTERRUPTLOCK();
    
    if (b->reader == NULL) {
        if (b->readers.first) {
            thread = b->readers.first->value;                           /* Yes, get the blocked thread */
            
            if (b->count >= (UINT32)thread->args[0]) {                  /* Is the requesting thread's data now available? */
                b->reader = KERNEL_ReleaseOne(&b->readers, SUCCESS);    /* Yes, release the blocked thread */
            }
        }
    }
    
    RELEASEINTERRUPTLOCK(); 
    KERNEL_ContextSwitch();                                             /* Possibly switch threads */
    return SUCCESS;
}

/***************************************************************************************************************************************//**

    Reads and removes data from a circular buffer.

    @param[in]  b           A pointer to the buffer object that contains the data to be removed.
    @param[out] buf         A pointer to a caller allocated buffer to receive the data read and removed from the buffer.
    @param[in]  nbytes      The total number of bytes to be read and removed from the buffer.
    @param[out] actual      A pointer to a caller allocated value used to determine the actual number of bytes that have been returned.
                            Use 'NULL' to only return either all or none of the requested amount.
    @param[in]  timeout     The maximum amount of time, in kernel ticks, to block and wait for the data to be received. Use '0' to
                            return immediately without blocking and use 'INFINITE' wait indefinitely.

    @return

      Status Code           | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The operation completed successfully. Use argument 'actual' to determine the number of bytes returned.
     ERR_NULLREFERENCE      | The argument 'b' or 'buf' was found to be NULL.
     ERR_ACCESSDENIED       | The request is from an interrupt and the buffer was already being written by a thread.
     ERR_NOTINITIALIZED     | The specified buffer has not been created or initialized.
     ERR_TIMEOUT            | The specified amount of time has elapsed before the requested amount of data arrived within the buffer.

    @remark     Thread and interrupt safe against a call to BUFFER_Write().
    @module     kernel-buffer

*******************************************************************************************************************************************/
STATUS BUFFER_Read(BUFFER* b, void* buf, UINT32 nbytes, UINT32* actual, UINT32 timeout)
{
    INTERRUPTLOCK lock;
    THREAD* thread;
    UINT32 wrap;
    UINT32 count;
    
    
#if (CFG_NULLCHECKING)
    if (b == NULL) {
        return ERR_NULLREFERENCE;
    }

    if (buf == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif
    
    if (actual) {
        *actual = 0;
    }

    if (KERNEL_IsISR()) {                                           /* Is the caller an interrupt service routine? */
        
        if (b->node.list != &kernel_buffers) {                      /* Has the buffer been initialized? */
            return ERR_NOTINITIALIZED;
        }
        
        if (b->reader) {                                            /* Is there a thread in-progress reading the buffer? */
            return ERR_ACCESSDENIED;
        }

        count = nbytes;                                             /* Capture the amount of data to return */
        if (count > b->count) {                                     /* Does the buffer contain the requested amount? */
            
            if (actual == NULL) {                                   /* Can a partial amount be returned? */
                return ERR_TIMEOUT;                                 /* Cannot return a partial amount */
            }
            
            count = b->count;                                       /* Capture amount that can actually be returned */
            
            if (count == 0) {                                       /* Any data to return? */
                return SUCCESS;                                     /* Buffer is empty */
            }
        }
        
        if ((b->rdx + count) > b->capacity) {                       /* Copy the data into the caller's buffer */
            wrap = b->capacity - b->rdx;
            memcpy(buf, &((BYTE*)b->mem)[b->rdx], wrap);
            memcpy(&((BYTE*)buf)[wrap], b->mem, count - wrap);
        } else {
            memcpy(buf, &((BYTE*)b->mem)[b->rdx], count);
        }
       
        *actual = count;                                            /* Report how much data has been returned */
        
        b->rdx = (b->rdx + count) % b->capacity;
        b->count -= count;

        if (b->writer == NULL) {
            if (b->writers.first) {
                thread = b->writers.first->value;
                
                if ((b->capacity - b->count) >= (UINT32)(thread->args[0])) {
                    b->writer = KERNEL_ReleaseOne(&b->writers, SUCCESS);
                }
            }
        }
    
        
        return SUCCESS;
    }
    
    ACQUIREINTERRUPTLOCK();
    
    if (b->node.list != &kernel_buffers) {                      /* Has the buffer been initialized? */
        RELEASEINTERRUPTLOCK();
        return ERR_NOTINITIALIZED;
    }
    
    if (timeout > 0) {
        
        if (b->reader || b->readers.first || nbytes > b->count) {

            kernel.thread->args[0] = (void*)nbytes;
            KERNEL_Block(b, &b->readers, timeout);
            
            RELEASEINTERRUPTLOCK();
            KERNEL_ContextSwitch();
            
            if (actual == NULL) {
                if (kernel.thread->status != SUCCESS) {
                    return kernel.thread->status;
                }
            }
            
            ACQUIREINTERRUPTLOCK();
        }
    }
    
    b->reader = kernel.thread;

    count = nbytes;
    if (count > b->count) {
        count = b->count;
        
        if (count == 0) {
            b->reader = NULL;
            RELEASEINTERRUPTLOCK();
            return SUCCESS;
        }
    }
    
    RELEASEINTERRUPTLOCK();
    
    if ((b->rdx + count) > b->capacity) {
        wrap = b->capacity - b->rdx;
        memcpy(buf, &((BYTE*)b->mem)[b->rdx], wrap);
        memcpy(&((BYTE*)buf)[wrap], b->mem, count - wrap);
    } else {
        memcpy(buf, &((BYTE*)b->mem)[b->rdx], count);
    }
    
    if (actual) {
        *actual = count;
    }
    
    ACQUIREINTERRUPTLOCK();

    b->rdx = (b->rdx + count) % b->capacity;
    b->count -= count;
    b->reader = NULL;
    
    if (b->readers.first) {
        thread = b->readers.first->value;
        
        if (b->count >= (UINT32)thread->args[0]) {
            b->reader = KERNEL_ReleaseOne(&b->readers, SUCCESS);
        }
    }
    
    RELEASEINTERRUPTLOCK();

    ACQUIREINTERRUPTLOCK();
    
    if (b->writer == NULL) {
        if (b->writers.first) {
            thread = b->writers.first->value;
            
            if ((b->capacity - b->count) >= (UINT32)(thread->args[0])) {
                b->writer = KERNEL_ReleaseOne(&b->writers, SUCCESS);
            }
        }
    }
    
    RELEASEINTERRUPTLOCK();
    KERNEL_ContextSwitch();                                     /* Possibly switch threads */
    return SUCCESS;
}
