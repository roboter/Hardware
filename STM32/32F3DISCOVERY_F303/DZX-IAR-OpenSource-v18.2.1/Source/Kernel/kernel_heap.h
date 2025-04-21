/*******************************************************************************************************************************************

    DZX | KERNEL | HEAP                                                                                                   VERSION 18.2.1
    ------------------------------------------------------------------------------------------------------------------------------------

    This file is part of the kernel and provides support for memory heaps. A memory heap provides variable-sized dynamic allocation from 
    a contiguous block of memory. The allocator uses a first-fit algorithm when searching for a free block to satisfy a request. Since a 
    heap supports allocations of any size, it can suffer from fragmentation. 

    The allocator may have to perform a search to find a free block that is large enough to satisfy the request and therefore the time 
    to complete an allocation is not deterministic and thus a heap is not to be used from within an ISR. 

    Allocating a block from the heap is not thread safe and it is the responsibility of the caller to ensure synchronized access to each
    memory heap.

    When an allocated block of memory from a heap is no longer needed, it can be returned to the heap using HEAP_Free(). When the block
    is returned, the heap will merge the returned block into any other free neighboring blocks thus defragmenting the heap.

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
#ifndef KERNEL_HEAP_H__
#define KERNEL_HEAP_H__

#include "Kernel/kernel.h"
#include "Kernel/kernel_list.h"

/*******************************************************************************************************************************************
    TYPE DEFINITIONS
*******************************************************************************************************************************************/
typedef struct HEAP HEAP;
typedef struct HEAPCTRL HEAPCTRL;
typedef struct HEAPBLK HEAPBLK;

/***************************************************************************************************************************************//**

    A control header that begins each block within a memory heap.
    @module     kernel-heap

*******************************************************************************************************************************************/
struct HEAPCTRL {
    UINT32 used : 1;            /**< A control bit used to mark the block as free or used */
    UINT32 size : 31;           /**< The size in bytes of the block (including overhead) */
};

/***************************************************************************************************************************************//**

    A block of memory contained within a heap.
    @module     kernel-heap

*******************************************************************************************************************************************/
struct HEAPBLK {
    HEAPCTRL ctrl;              /**< Control information about the block */
    HEAPBLK* next;              /**< A pointer to the next block within heap */
    HEAPBLK* prev;              /**< A pointer to the previous block within heap */
};

/***************************************************************************************************************************************//**

    A memory heap that supports dynamic allocation.
    @module     kernel-heap

*******************************************************************************************************************************************/
struct HEAP {
    NODE        node;           /**< A node used to place the heap into a list */
    const CHAR* name;           /**< A name for the heap */
    void*       mem;            /**< A pointer to the memory managed by the heap */
    UINT32      size;           /**< The size in bytes of the memory managed by the heap */
    HEAPBLK*    first;          /**< A pointer to the first block within the heap */
    HEAPBLK*    last;           /**< A pointer to the last block within the heap */  
    UINT32      blks;           /**< The total number of blocks contained within the heap */
    UINT32      freebytes;      /**< The total number of free available bytes within the heap */
    UINT32      freeblks;       /**< The total number of free blocks within the heap */
};

/*******************************************************************************************************************************************
    PUBLIC FUNCTIONS
*******************************************************************************************************************************************/
/***************************************************************************************************************************************//**

    Creates and initializes a memory heap from a contiguous region of memory.

    @param[in]  heap        A pointer to a caller allocated memory heap instance to be initialized.
    @param[in]  name        A pointer to a NULL terminated string that represents the name for the heap.
    @param[in]  mem         A pointer to a caller allocated region of memory to be managed by the heap.
    @param[in]  size        The size, in bytes, of the given region of memory.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The memory heap was created and initialized.
     ERR_NULLREFERENCE      | The argument 'heap' or 'mem' was found to be NULL.
     ERR_INVALIDCONTEXT     | This operation is not supported from the context of an interrupt service routine (ISR).
     ERR_INVALIDARGUMENT    | The specified 'size' was invalid. Must be larger than a single heap block, sizeof(HEAPBLK).
     ERR_ALREADYINITIALIZED | The specified heap has already been created and initialized.

    @module     kernel-heap

*******************************************************************************************************************************************/
extern STATUS HEAP_Create(HEAP* heap, const CHAR* name, void* mem, UINT32 size);

/***************************************************************************************************************************************//**

    Destroys and removes a memory heap from the kernel.

    @param[in]  heap        A pointer to a caller allocated memory heap to be destroyed.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The memory heap was successfully destroyed and removed from the kernel.
     ERR_NULLREFERENCE      | The argument 'heap' was found to be NULL.
     ERR_INVALIDCONTEXT     | The operation is not supported from the context of an interrupt service routine (ISR).
     ERR_NOTINITIALIZED     | The specified heap has not been created and initialized.

    @module     kernel-heap

*******************************************************************************************************************************************/
extern STATUS HEAP_Destroy(HEAP* heap);

/***************************************************************************************************************************************//**

    Allocates and returns memory from a heap.

    @param[in]  heap        A pointer to the heap in which to allocate memory.
    @param[in]  size        The size, in bytes, of the memory to be allocated and returned.

    @return     A pointer to the memory that has been allocated upon success; otherwise NULL on any error.
    @remark     This performs a linear search and therefore is an O(n) operation where n is the number of free blocks within the heap.
    @remark     Not thread safe.
    @module     kernel-heap

*******************************************************************************************************************************************/
extern void* HEAP_Alloc(HEAP* heap, UINT32 size);

/***************************************************************************************************************************************//**

    Allocates and returns memory from a heap that has been cleared (zero initialized).

    @param[in]  heap        A pointer to the heap in which to allocate memory.
    @param[in]  size        The size in bytes of memory to be allocated and returned.

    @return     A pointer to the memory that has been allocated and cleared upon success; otherwise NULL on any error.
    @remark     This performs a linear search and therefore is an O(n) operation where n is the number of free blocks within the heap.
    @remark     Not thread safe.
    @module     kernel-heap

*******************************************************************************************************************************************/
extern void* HEAP_Calloc(HEAP* heap, UINT32 size);

/***************************************************************************************************************************************//**

    Releases and returns memory back to a memory heap.

    @param[in]  heap        A pointer to the heap to receive the memory.
    @param[in]  mem         A pointer to the memory to be returned to the heap.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The memory was returned to the heap.
     ERR_NULLREFERENCE      | The argument 'heap' or 'mem' was found to be NULL.
     ERR_NOTINITIALIZED     | The specified heap has not been created and initialized.
     ERR_INVALIDOPERATION   | The memory was not used from the heap and could not be returned.

    @remark     This is an O(1) operation.
    @remark     Not thread safe.
    @module     kernel-heap

*******************************************************************************************************************************************/
extern STATUS HEAP_Free(HEAP* heap, void* mem);

/***************************************************************************************************************************************//**

    Returns the total number of available free bytes remaining within a memory heap.

    @param[in]  heap        A pointer to the target memory heap.

    @return     The total number of available free bytes remaining within the heap. 
    @remark     The returned value does not indicate the total number of bytes that could be allocated as the heap could be fragmented.
    @remark     Not thread safe.
    @module     kernel-heap

*******************************************************************************************************************************************/
extern UINT32 HEAP_FreeBytes(HEAP* heap);

/***************************************************************************************************************************************//**

    Verifies a memory heap against any corruption.

    @param[in]  heap        A pointer to the heap to be verified.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The memory heap has no detectable corruption.
     ERR_NULLREFERENCE      | The argument 'heap' was found to be NULL.
     ERR_NOTINITIALIZED     | The specified heap has not been created and initialized.
     ERR_CORRUPTED          | The memory heap has been corrupted.

    @remark     Not thread safe.
    @module     kernel-heap

*******************************************************************************************************************************************/
extern STATUS HEAP_Verify(HEAP* heap);

#endif /* KERNEL_HEAP_H__ */
