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
#ifndef KERNEL_BUFFER_H__
#define KERNEL_BUFFER_H__

#include "Kernel/kernel_list.h"
#include "Kernel/kernel_thread.h"

/*******************************************************************************************************************************************
    TYPE DEFINITIONS
*******************************************************************************************************************************************/
typedef struct BUFFER BUFFER;

#if (CFG_STATISTICS)
/*******************************************************************************************************************************************

    Represents run-time statistics for a buffer.
    @module     INTERNAL

*******************************************************************************************************************************************/
typedef struct BUFFERSTATS {
    UINT32      maxcount;           /**< The maximum number of bytes the buffer has ever contained */
	UINT32      total;              /**< The total number of data bytes that have transferred through the buffer */
} BUFFERSTATS;
#endif

/***************************************************************************************************************************************//**

    A circular byte wide copy-in/copy-out buffer.
    @module     kernel-buffer

*******************************************************************************************************************************************/
struct BUFFER {
    NODE        node;               /**< A node for registering the buffer within the kernel */
    const CHAR* name;               /**< A name for the buffer */
    void*       mem;                /**< A pointer to the memory managed by the buffer */ 
    UINT32      rdx;                /**< An index used for reading data from the buffer */
    UINT32      wrx;                /**< An index used for writing data to the buffer */
    UINT32      count;              /**< The total number of bytes contained within the buffer */
    UINT32      capacity;           /**< The capacity in bytes that the buffer can contain */   
    THREAD*     reader;             /**< A pointer to the thread in-progress reading the buffer */
    THREAD*     writer;             /**< A pointer to the thread in-progress writing the buffer */
    LIST        readers;            /**< A list of threads blocked waiting to read from the buffer */
    LIST        writers;            /**< A list of threads blocked waiting to write to the buffer */
     
#if (CFG_STATISTICS)
	BUFFERSTATS stats;              /**< Runtime statistics for the buffer */
#endif
};

/*******************************************************************************************************************************************
    PUBLIC FUNCTIONS
*******************************************************************************************************************************************/
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
extern STATUS BUFFER_Create(BUFFER* b, const CHAR* name, void* mem, UINT32 capacity);

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
extern STATUS BUFFER_Destroy(BUFFER* b);

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
extern STATUS BUFFER_Clear(BUFFER* b);

/***************************************************************************************************************************************//**

    Returns the capacity, in bytes, for a buffer.

    @param[in]  b           A pointer to the target buffer.

    @return     The specified buffer's capacity, in bytes.
    @module     kernel-buffer

*******************************************************************************************************************************************/
extern UINT32 BUFFER_Capacity(BUFFER* b);

/***************************************************************************************************************************************//**

    Returns the number of bytes currently contained within a buffer.

    @param[in]  b           A pointer to the target buffer.

    @return     The total number of bytes contained within the buffer.
    @module     kernel-buffer

*******************************************************************************************************************************************/
extern UINT32 BUFFER_Count(BUFFER* b);

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
extern STATUS BUFFER_Write(BUFFER* b, const void* data, UINT32 nbytes, UINT32* actual, UINT32 timeout);

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
extern STATUS BUFFER_Read(BUFFER* b, void* buf, UINT32 nbytes, UINT32* actual, UINT32 timeout);

#endif /* KERNEL_BUFFER_H__ */
