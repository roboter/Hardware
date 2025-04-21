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
#include "kernel_heap.h"
#include "kernel_core.h"
#include <string.h>

/*******************************************************************************************************************************************
    PRIVATE VARIABLES
*******************************************************************************************************************************************/
static LIST kernel_heaps;

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
STATUS HEAP_Create(HEAP* heap, const CHAR* name, void* mem, UINT32 size)
{
    INTERRUPTLOCK lock;
    HEAPBLK* blk;
    

#if (CFG_CONTEXTCHECKING)
    if (KERNEL_IsISR()) {
        return ERR_INVALIDCONTEXT;
    }
#endif
#if (CFG_NULLCHECKING)
    if (heap == NULL) {
        return ERR_NULLREFERENCE;
    }
    
    if (mem == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif
  
    if (size < sizeof(HEAPBLK)) {
        return ERR_INVALIDARGUMENT;
    }
    
    ACQUIREINTERRUPTLOCK();

    if (heap->node.list == &kernel_heaps) {                     /* Has the specified heap already been initialized? */
        RELEASEINTERRUPTLOCK();
        return ERR_ALREADYINITIALIZED;
    }
    
    RELEASEINTERRUPTLOCK();
    
    heap->name = name;                                          /* Initialize the memory heap */
    heap->mem = mem;
    heap->size = size;
    
    heap->blks = 1;                                             /* Begin the heap with a single large free block */
    heap->freeblks = 1;
    heap->freebytes = size;
    
    blk = (HEAPBLK*)heap->mem;                                  /* Initialize the single free block within the heap */
    blk->ctrl.used = 0;
    blk->ctrl.size = size;
    blk->next = NULL;
    blk->prev = NULL;
    
    heap->first = blk;                                          /* Initialize the list with the single free block */
    heap->last = blk;
    
    ACQUIREINTERRUPTLOCK();
    
    LIST_AddLast(&kernel_heaps, &heap->node, heap);             /* Register the heap within the kernel */

    RELEASEINTERRUPTLOCK();
    return SUCCESS;
}
    
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
STATUS HEAP_Destroy(HEAP* heap)
{
    INTERRUPTLOCK lock;
    
    
#if (CFG_CONTEXTCHECKING)
    if (KERNEL_IsISR()) {
        return ERR_INVALIDCONTEXT;
    }
#endif
#if (CFG_NULLCHECKING)
    if (heap == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif
    
    ACQUIREINTERRUPTLOCK();

    if (heap->node.list != &kernel_heaps) {                     /* Is the heap registered within the kernel? */
        RELEASEINTERRUPTLOCK();
        return ERR_NOTINITIALIZED;
    }
   
    LIST_Remove(&kernel_heaps, &heap->node);                    /* Release the kernel reference to the heap */

    RELEASEINTERRUPTLOCK();
    return SUCCESS;
}

/***************************************************************************************************************************************//**

    Returns the total number of available free bytes remaining within a memory heap.

    @param[in]  heap        A pointer to the target memory heap.

    @return     The total number of available free bytes remaining within the heap. 
    @remark     The returned value does not indicate the total number of bytes that could be allocated as the heap could be fragmented.
    @remark     Not thread safe.
    @module     kernel-heap

*******************************************************************************************************************************************/
UINT32 HEAP_FreeBytes(HEAP* heap)
{
#if (CFG_NULLCHECKING)
    if (heap == NULL) {
        return 0;
    }
#endif
    
    return heap->freebytes;
}

/***************************************************************************************************************************************//**

    Allocates and returns memory from a heap.

    @param[in]  heap        A pointer to the heap in which to allocate memory.
    @param[in]  size        The size, in bytes, of the memory to be allocated and returned.

    @return     A pointer to the memory that has been allocated upon success; otherwise NULL on any error.
    @remark     This performs a linear search and therefore is an O(n) operation where n is the number of free blocks within the heap.
    @remark     Not thread safe.
    @module     kernel-heap

*******************************************************************************************************************************************/
void* HEAP_Alloc(HEAP* heap, UINT32 size)
{
    HEAPBLK* blk;
    HEAPBLK* newblk;
    
   
#if (CFG_NULLCHECKING)
    if (heap == NULL) {
        return NULL;
    }
#endif
    
    if (size == 0) {
        return NULL;
    }
    
    if (heap->node.list != &kernel_heaps) {                             /* Has the specified heap been initialized? */
        return NULL;
    }

    size += sizeof(HEAPBLK);                                            /* Apply the management overhead to the request */

    if (size % HEAPBLKALIGNMENT) {                                      /* Does the size comply with the desired alignment? */
        size += (HEAPBLKALIGNMENT - (size % HEAPBLKALIGNMENT));         /* Increase the requested size to maintain alignment */
    }
    
    for (blk = heap->last; blk != NULL; blk = blk->prev) {              /* Search for a free block (last-to-first) */
        if (blk->ctrl.used == 0) {                                      /* Is the block free? */
            if (blk->ctrl.size >= size) {                               /* Is the block large enough for the request? */
                if (blk->ctrl.size > (size + sizeof(HEAPBLK))) {        /* Can the block be split? */
                    newblk = (HEAPBLK*)((UINT32)blk + size);            /* Create a new block to remain free within the heap */
                    newblk->ctrl.used = 0;
                    newblk->ctrl.size = blk->ctrl.size - size;          /* The new block size is what's left after the allocation */
                    newblk->prev = blk;                                 /* Insert the new block after the block being allocated */
                    newblk->next = blk->next;
                    
                    if (blk->next) {
                        blk->next->prev = newblk;
                    }
                    
                    blk->next = newblk;
                    blk->ctrl.size = size;
                    
                    if (heap->last == blk) {                            /* Update tail pointer if necessary */
                        heap->last = newblk;
                    }
                    
                    heap->blks++;                                       /* After the split there's one more block within the heap */
                } else {
                    heap->freeblks--;                                   /* Unable to split, one less free block */
                }
                    
                blk->ctrl.used = 1;                                     /* Mark this block as used */
                heap->freebytes -= blk->ctrl.size;                      /* Update the count of total free bytes left in the heap */
                return (void*)((UINT32)blk + sizeof(HEAPBLK));          /* Return the allocated memory */
            }
        }
    }
    
    return NULL;                                                        /* Unable to fulfill the request */
}

/***************************************************************************************************************************************//**

    Allocates and returns memory from a heap that has been cleared (zero initialized).

    @param[in]  heap        A pointer to the heap in which to allocate memory.
    @param[in]  size        The size in bytes of memory to be allocated and returned.

    @return     A pointer to the memory that has been allocated and cleared upon success; otherwise NULL on any error.
    @remark     This performs a linear search and therefore is an O(n) operation where n is the number of free blocks within the heap.
    @remark     Not thread safe.
    @module     kernel-heap

*******************************************************************************************************************************************/
void* HEAP_Calloc(HEAP* heap, UINT32 size)
{
    void* p;
    
    
    p = HEAP_Alloc(heap, size);                                 /* Attempt to allocate the requested memory */ 
    if (p) {                                                    /* Was the allocation successful? */
        memset(p, 0, size);                                     /* Clear (zero initialize) the memory */
    }
    
    return p;
}

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
STATUS HEAP_Free(HEAP* heap, void* mem)
{
    HEAPBLK* blk;
    
    
    
#if (CFG_NULLCHECKING)
    if (heap == NULL) {
        return ERR_NULLREFERENCE;
    }
    
    if (mem == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif
    

    if (heap->node.list != &kernel_heaps) {                     /* Has the specified heap been initialized? */
        return ERR_NOTINITIALIZED;
    }
   
    blk = (HEAPBLK*)((UINT32)mem - sizeof(HEAPBLK));            /* Get the block that is being returned to the heap */
    
    if (blk->ctrl.used == 0) {                                  /* Is the block currently marked as used (not free)? */
        return ERR_INVALIDOPERATION;                             /* The block is not marked as used */
    }
                           
    blk->ctrl.used = 0;                                         /* Mark the block as free */
    
    heap->freebytes += blk->ctrl.size;                          /* Update the total count of free bytes in the heap */
    heap->freeblks++;                                           /* Update the total count of free blocks in the heap */
    
    if (blk->next) {                                            /* Is there a block next to this returned block? */
        if (blk->next->ctrl.used == 0) {                        /* Is the next block free too? */
            
            blk->ctrl.size += blk->next->ctrl.size;             /* Merge these two blocks together into a single block */
            if (heap->last == blk->next) {                      /* Update the heap block pointers if necessary */
                heap->last = blk;
            }  
            
            blk->next = blk->next->next;                        /* Adjust pointers to skip the merged block */
            if (blk->next) {
                blk->next->prev = blk;
            }
            
            heap->blks--;                                       /* One less block in the heap after the merge */
            heap->freeblks--;                                   /* One less free block in the heap after the merge */
        }
    }
    
    if (blk->prev) {                                            /* Is there a block before this returned block */
        if (blk->prev->ctrl.used == 0) {                        /* Is the previous block free too? */
            
            blk->prev->ctrl.size += blk->ctrl.size;             /* Merge these two blocks together into a single block */
            
            blk->prev->next = blk->next;                        /* Adjust pointers to skip the merged block */
            if (blk->prev->next) {
                blk->prev->next->prev = blk->prev;
            }
            
            if (heap->last == blk) {                            /* Update the heap block pointers if necessary */
                heap->last = blk->prev;
            }
            
            heap->blks--;                                       /* One less block in the heap after the merge */
            heap->freeblks--;                                   /* One less free block in the heap after the merge */
        }
    }
 
    return SUCCESS;                                             /* Successfully returned to the heap */
}

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
STATUS HEAP_Verify(HEAP* heap)
{
    HEAPBLK* blk;
    UINT32 addr;
    
    
#if (CFG_NULLCHECKING)
    if (heap == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif
    
    if (heap->node.list != &kernel_heaps) {                                     /* Has the specified heap been initialized? */
        return ERR_NOTINITIALIZED;
    }
    
    addr = 0;
    
    for (blk = heap->first; blk != NULL; blk = blk->next) {                     /* Go through each block within the heap */
        
        if ((UINT32)blk > addr) {                                               /* Ensure each block is in ascending order by address */
            addr = (UINT32)blk;     
        } else {
            return ERR_CORRUPTED;                                               /* Failed, blocks not in order */
        }
        
        if (blk->next) {
            if (((UINT32)blk + blk->ctrl.size) != (UINT32)blk->next) {          /* Ensure the next block is up tight  */
                return ERR_CORRUPTED;                                           /* Failed, there is a reported gap between blocks */
            }
        }
        
        if (blk->prev) {
            if (((UINT32)blk->prev + blk->prev->ctrl.size) != (UINT32)blk) {    /* Ensure the previous block is up tight */
                return ERR_CORRUPTED;                                           /* Failed, there is a reported gap between blocks */
            }
        }
    }
    
    return SUCCESS;
}
