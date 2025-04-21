/*******************************************************************************************************************************************

    DZX | KERNEL | POOL                                                                                                   VERSION 18.2.1
    ------------------------------------------------------------------------------------------------------------------------------------

    This file is part of the kernel and provides support for memory pools. A memory pool is a collection of fixed-sized memory blocks 
    that support dynamic allocation. Since the blocks within a memory pool are fixed in size, memory pools do not suffer from any sort 
    of fragmentation. Allocation and deallocation of blocks are fast and deterministic which provides the ability to use pools from all 
    execution contexts including interrupt service routines (ISR).

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
#include "kernel_pool.h"
#include "kernel_core.h"
#include <string.h>

/*******************************************************************************************************************************************
    PRIVATE VARIABLES
*******************************************************************************************************************************************/
static LIST kernel_pools;

/***************************************************************************************************************************************//**

    Creates and initializes a fixed-sized block memory pool.

    @param[in]  pool        A pointer to the caller allocated memory pool instance to be initialized.
    @param[in]  name        A pointer to a NULL terminated string that represents the name for the pool.
    @param[in]  mem         A pointer to a caller allocated block of memory to be managed by the pool.
    @param[in]  blksize     The size in bytes for each block contained within the memory pool. Must be at least the size of an address
                            field within the target MCU. (i.e. 4 bytes for a 32-bit MCU)
    @param[in]  nblks       The total number of blocks for the memory pool. (Must be at least one)

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The memory pool was created and initialized.
     ERR_NULLREFERENCE      | The argument 'pool' or 'mem' was found to be NULL.
     ERR_INVALIDCONTEXT     | This operation is not supported from the context of an interrupt service routine (ISR).
     ERR_INVALIDARGUMENT    | The argument 'blksize' or 'nblks' was invalid.
     ERR_ALREADYINITIALIZED | The specified pool has already been initialized (created).

    @remark     The buffer memory must be aligned on an pointer sized word boundry (i.e. 4 bytes for 32-bit)
    @remark     Ensure that blksize is at least as large as sizeof(void*) (i.e. 4 bytes for 32-bit)
    @module     kernel-pool

*******************************************************************************************************************************************/
STATUS POOL_Create(POOL* pool, const CHAR* name, void* mem, UINT32 blksize, UINT32 nblks)
{
    INTERRUPTLOCK lock;
    UINT32 i;
    POOLBLK* blk;


#if (CFG_CONTEXTCHECKING)
    if (KERNEL_IsISR()) {
        return ERR_INVALIDCONTEXT;
    }
#endif  
    
#if (CFG_NULLCHECKING)
    if (pool == NULL) {
        return ERR_NULLREFERENCE;
    }

    if (mem == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif

    if (blksize < sizeof(POOLBLK*)) {                               /* Each block must be at least the size of an address field */
        return ERR_INVALIDARGUMENT;
    }

    if (nblks == 0) {                                               /* Validate the number of blocks */
        return ERR_INVALIDARGUMENT;
    }
    
    ACQUIREINTERRUPTLOCK();
    
    if (pool->node.list == &kernel_pools) {                         /* Has the pool already been initialized? */
        RELEASEINTERRUPTLOCK();
        return ERR_ALREADYINITIALIZED;
    }
    
    RELEASEINTERRUPTLOCK();
    
    pool->name = name;                                              /* Initialize the pool */
    pool->mem = mem;
    pool->blksize = blksize;
    pool->nblks = nblks;
    pool->nfree = nblks;
    pool->blks = (POOLBLK*)mem;

    blk = pool->blks;                                               /* Initialize the list of available blocks */
    for (i = 0; i < nblks - 1; i++) {
        blk->next = (POOLBLK*)((UINT32)mem + ((i + 1) * blksize));  /* Assign the address of the next available block */
        blk = blk->next;                                            /* Move to the next block */
    }

    blk->next = NULL;                                               /* Terminate the list of available blocks */
    LIST_Init(&pool->threads);                                      /* Initialize the list of threads block upon the pool */
    
    ACQUIREINTERRUPTLOCK();
    
    LIST_AddLast(&kernel_pools, &pool->node, pool);                 /* Register the pool within the kernel */
    
    RELEASEINTERRUPTLOCK();
    return SUCCESS;
}

/***************************************************************************************************************************************//**

    Destroys and removes a memory pool from the kernel. Any threads that are waiting upon the memory pool will be released with the 
    ERR_DESTROYED status code.

    @param[in]  pool        A pointer to the memory pool to be destroyed.

    @return

     Status Code            | Description
    ----------------------- | -----------------------------------------------------------------------------------------
     SUCCESS                | The memory pool was destroyed and removed from the kernel.
     ERR_NULLREFERENCE      | The argument 'pool' was found to be NULL.
     ERR_INVALIDCONTEXT     | This operation is not supported from the context of an interrupt service routine (ISR).
     ERR_NOTINITIALIZED     | The specified pool has not been initialized (created).

    @module     kernel-pool

*******************************************************************************************************************************************/
STATUS POOL_Destroy(POOL* pool)
{
    INTERRUPTLOCK lock;
    
    
#if (CFG_CONTEXTCHECKING)
    if (KERNEL_IsISR()) {
        return ERR_INVALIDCONTEXT;
    }
#endif
    
#if (CFG_NULLCHECKING)
    if (pool == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif
    
    ACQUIREINTERRUPTLOCK();
    
    if (pool->node.list != &kernel_pools) {                     /* Has the specified pool been initialized? */
        RELEASEINTERRUPTLOCK();
        return ERR_NOTINITIALIZED;
    }

    LIST_Remove(&kernel_pools, &pool->node);                    /* Remove the pool from the kernel */
    RELEASEINTERRUPTLOCK();
    
    KERNEL_ReleaseAll(&pool->threads, ERR_DESTROYED);           /* Release any threads waiting upon the pool */
    return SUCCESS;
}

/***************************************************************************************************************************************//**

    Allocates and returns a block of memory from a memory pool.

    @param[in]  pool        A pointer to the memory pool in which to allocate and return a block of memory.
    @param[in]  timeout     The maximum amount of time, in kernel ticks, to wait for a block to become available if the pool is
                            currently empty. Use '0' to return immediately without waiting. Use INFINITE to wait indefinitely.

    @return     A non-zero pointer to the block of memory that has been allocated from the given pool upon success; otherwise NULL on
                any error.
    @module     kernel-pool

*******************************************************************************************************************************************/
void* POOL_Alloc(POOL* pool, UINT32 timeout)
{
    INTERRUPTLOCK lock;
    POOLBLK* blk;


 #if (CFG_NULLCHECKING)
    if (pool == NULL) {
        return NULL;
    }
#endif

    ACQUIREINTERRUPTLOCK();
    
    if (pool->node.list != &kernel_pools) {                     /* Has the specified pool been initialized? */
        RELEASEINTERRUPTLOCK();
        return NULL;
    }

    if (pool->blks) {                                           /* Any available blocks? */
        blk = pool->blks;                                       /* Take the first available block */
        pool->blks = blk->next;                                 /* Remove the block from the available list */
        pool->nfree--;                                          /* Update the available count for the pool */

        RELEASEINTERRUPTLOCK();
        return blk;                                             /* Return the captured block */
    }
    
    if (KERNEL_IsISR()) {                                       /* Is the caller an ISR? */
        RELEASEINTERRUPTLOCK();
        return NULL;                                            /* Would block, but caller is an ISR */
    }
    
    if (timeout == 0) {                                         /* Requested to not block and return immediately? */
        RELEASEINTERRUPTLOCK();
        return NULL;                                            /* Return timeout without blocking */
    }

    KERNEL_Block(pool, &pool->threads, timeout);                /* Attempt to block the caller */
    kernel.thread->args[0] = NULL;                              /* Initialize the return value for the blocking */
    
    RELEASEINTERRUPTLOCK();
    KERNEL_ContextSwitch();                                     /* Caller blocked, switch threads */
    return kernel.thread->args[0];                              /* Caller released, return the result */
}

/***************************************************************************************************************************************//**

    Allocates and returns a block of memory from a memory pool that has been cleared (zero initialized).

    @param[in]  pool        A pointer to the memory pool in which to allocate and return a block of memory.
    @param[in]  timeout     The maximum amount of time, in kernel ticks, to wait for a block to become available if the pool is
                            currently empty. Use '0' to return immediately without waiting. Use INFINITE to wait indefinitely.

    @return     A non-zero pointer to the block of memory that has been allocated from the given pool upon success; otherwise NULL on
                any error.
    @module     kernel-pool

*******************************************************************************************************************************************/
void* POOL_Calloc(POOL* pool, UINT32 timeout)
{
    void* p;
    
    
    p = POOL_Alloc(pool, timeout);                              /* Attempt to allocate the requested block of memory */
    
    if (p) {                                                    /* Allocation was successful? */
        memset(p, 0, pool->blksize);                            /* Clear (zero initialize) the block of memory */
    }
    
    return p;
}

/***************************************************************************************************************************************//**

    Returns a previously allocated block of memory back to a memory pool.

    @param[in]  pool        A pointer to the memory pool to receive the block.
    @param[in]  blk         A pointer to the block of memory to be returned to the specified pool.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The block was returned to the specified memory pool.
     ERR_NULLREFERENCE      | The argument 'pool' or 'blk' was found to be NULL.
     ERR_NOTINITIALIZED     | The specified pool has not been created or initialized.

    @remark     Ensure the block was allocated from the specified pool and not to free the same block multiple times as there are no 
                guards for these scenarios for the sake of efficiency.
    @module     kernel-pool

*******************************************************************************************************************************************/
STATUS POOL_Free(POOL* pool, void* blk)
{
    INTERRUPTLOCK lock;
    THREAD* thread;


#if (CFG_NULLCHECKING)
    if (pool == NULL) {
        return ERR_NULLREFERENCE;
    }

    if (blk == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif

    ACQUIREINTERRUPTLOCK();

    if (pool->node.list != &kernel_pools) {                     /* Has the specified pool been initialized? */
        RELEASEINTERRUPTLOCK();
        return ERR_NOTINITIALIZED;
    }

    thread = KERNEL_ReleaseOne(&pool->threads, SUCCESS);        /* Attempt to release a blocked thread*/
    if (thread) {                                               /* Was a thread released? */
        thread->args[0] = blk;                                  /* Give the memory block directly to the released thread */
        
        RELEASEINTERRUPTLOCK();
        KERNEL_ContextSwitch();                                 /* Possibly switch threads */
        return SUCCESS;
    } 
        
    ((POOLBLK*)blk)->next = pool->blks;                         /* Return the block to the available list */
    pool->blks = (POOLBLK*)blk;
    pool->nfree++;                                              /* Update the available block count for the pool */
                                                                    
    RELEASEINTERRUPTLOCK();
    return SUCCESS;
}

/***************************************************************************************************************************************//**

    Returns the current number of available unallocated blocks remaining within a memory pool.

    @param[in]  pool        A pointer to the target memory pool in which to return a available block count.

    @return     The number of available blocks remaining in the specified memory pool.
    @module     kernel-pool

*******************************************************************************************************************************************/
UINT32 POOL_FreeCount(POOL* pool)
{
    INTERRUPTLOCK lock;
    UINT32 num;

    
    ACQUIREINTERRUPTLOCK();

    if (pool->node.list != &kernel_pools) {                     /* Has the specified pool been initialized? */
        RELEASEINTERRUPTLOCK();
        return 0;
    }

    num = pool->nfree;                                          /* Capture the number of free blocks in thread and ISR safe lock */
    
    RELEASEINTERRUPTLOCK();
    return num;
}

/***************************************************************************************************************************************//**

    Returns the size in bytes for each block within a memory pool.

    @param[in]  pool        A pointer to the target memory pool in which to return the block size.

    @return     The size in bytes of each block within the specified pool.
    @module     kernel-pool

*******************************************************************************************************************************************/
UINT32 POOL_BlockSize(POOL* pool)
{
    INTERRUPTLOCK lock;
    UINT32 size;

    
    ACQUIREINTERRUPTLOCK();

    if (pool->node.list != &kernel_pools) {                     /* Has the specified pool been initialized? */
        RELEASEINTERRUPTLOCK();
        return 0;                                               /* The pool is not valid */
    }

    size = pool->blksize;                                       /* Capture the size of the blocks in thread and ISR safe lock */

    RELEASEINTERRUPTLOCK();
    return size;
}
