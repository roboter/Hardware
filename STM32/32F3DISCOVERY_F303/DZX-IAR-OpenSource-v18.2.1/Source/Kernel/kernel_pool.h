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
#ifndef KERNEL_POOL_H__
#define KERNEL_POOL_H__

#include "Kernel/kernel.h"
#include "Kernel/kernel_list.h"

/*******************************************************************************************************************************************
    TYPE DEFINITIONS
*******************************************************************************************************************************************/
typedef struct POOL POOL;
typedef struct POOLBLK POOLBLK;

/***************************************************************************************************************************************//**

    Represents a fixed sized block of memory within a memory pool.
    @module     kernel-pool

*******************************************************************************************************************************************/
struct POOLBLK {
	POOLBLK*    next;           /**< A pointer to the next block within a linked list of blocks */
};

/***************************************************************************************************************************************//**

    Represents a memory pool used for dynamic allocation of fixed sized memory blocks.
    @module     kernel-pool

*******************************************************************************************************************************************/
struct POOL {       
    NODE        node;           /**< A node used to place the pool into a list */
    const CHAR* name;           /**< A name for the memory pool */
    LIST        threads;        /**< A list of blocked threads waiting upon the memory pool */
	void*       mem;            /**< A pointer to the memory managed by the pool */
	POOLBLK*    blks;           /**< A pointer to the available blocks within the pool */
	UINT32      nfree;          /**< Represents the total number of free blocks remaining within the pool */
	UINT32      nblks;          /**< Represents the total number of blocks contained within the pool */
	UINT32      blksize;        /**< Represents the size in bytes for each block within the pool */
};

/*******************************************************************************************************************************************
    PUBLIC FUNCTIONS
*******************************************************************************************************************************************/
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
extern STATUS POOL_Create(POOL* pool, const CHAR* name, void* mem, UINT32 blksize, UINT32 nblks);

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
extern STATUS POOL_Destroy(POOL* pool);

/***************************************************************************************************************************************//**

    Allocates and returns a block of memory from a memory pool.

    @param[in]  pool        A pointer to the memory pool in which to allocate and return a block of memory.
    @param[in]  timeout     The maximum amount of time, in kernel ticks, to wait for a block to become available if the pool is
                            currently empty. Use '0' to return immediately without waiting. Use INFINITE to wait indefinitely.

    @return     A non-zero pointer to the block of memory that has been allocated from the given pool upon success; otherwise NULL on
                any error.
    @module     kernel-pool

*******************************************************************************************************************************************/
extern void* POOL_Alloc(POOL* pool, UINT32 timeout);

/***************************************************************************************************************************************//**

    Allocates and returns a block of memory from a memory pool that has been cleared (zero initialized).

    @param[in]  pool        A pointer to the memory pool in which to allocate and return a block of memory.
    @param[in]  timeout     The maximum amount of time, in kernel ticks, to wait for a block to become available if the pool is
                            currently empty. Use '0' to return immediately without waiting. Use INFINITE to wait indefinitely.

    @return     A non-zero pointer to the block of memory that has been allocated from the given pool upon success; otherwise NULL on
                any error.
    @module     kernel-pool

*******************************************************************************************************************************************/
extern void* POOL_Calloc(POOL* pool, UINT32 timeout);

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
extern STATUS POOL_Free(POOL* pool, void* blk);

/***************************************************************************************************************************************//**

    Returns the current number of available unallocated blocks remaining within a memory pool.

    @param[in]  pool        A pointer to the target memory pool in which to return a available block count.

    @return     The number of available blocks remaining in the specified memory pool.
    @module     kernel-pool

*******************************************************************************************************************************************/
extern UINT32 POOL_FreeCount(POOL* pool);

/***************************************************************************************************************************************//**

    Returns the size in bytes for each block within a memory pool.

    @param[in]  pool        A pointer to the target memory pool in which to return the block size.

    @return     The size in bytes of each block within the specified pool.
    @module     kernel-pool

*******************************************************************************************************************************************/
extern UINT32 POOL_BlockSize(POOL* pool);

#endif /* KERNEL_POOL_H__ */
