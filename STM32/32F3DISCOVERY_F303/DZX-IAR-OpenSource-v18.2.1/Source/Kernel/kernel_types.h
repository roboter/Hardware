/*******************************************************************************************************************************************

    DZX | KERNEL | DATA TYPES                                                                                             VERSION 18.2.1
    ------------------------------------------------------------------------------------------------------------------------------------

    This file is part of the kernel and provides definitions for basic data types.

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
#ifndef KERNEL_TYPES_H__
#define KERNEL_TYPES_H__

#include <stdint.h>

/*******************************************************************************************************************************************
    DATA TYPES
*******************************************************************************************************************************************/
typedef int             INT;        /**< Native system size signed integer */
typedef unsigned int    UINT;       /**< Native system size unsigned integer */

typedef char            CHAR;       /**< Signed 8-bit character */
typedef unsigned char   UCHAR;      /**< Unsigned byte 8-bit character */
typedef uint16_t        WCHAR;      /**< Wide 16-bit character */

typedef uint8_t         BYTE;       /**< Unsigned 8-bit integer */
typedef int8_t          SBYTE;      /**< Signed 8-bit integer */
typedef uint8_t         UINT8;      /**< Unsigned 8-bit integer */
typedef int8_t          INT8;       /**< Signed 8-bit integer */

typedef uint16_t        WORD;       /**< Unsigned word (16-bit) */
typedef uint16_t        USHORT;     /**< Unsigned 16-bit integer */
typedef int16_t         SHORT;      /**< Signed 16-bit integer */
typedef uint16_t        UINT16;     /**< Unsigned 16-bit integer */
typedef int16_t         INT16;      /**< Signed 16-bit integer */

typedef uint32_t        DWORD;      /**< Unsigned double word (32-bit) */
typedef uint32_t        ULONG;      /**< Unsigned 32-bit integer */
typedef int32_t         LONG;       /**< Signed 32-bit integer */
typedef uint32_t        UINT32;     /**< Unsigned 32-bit integer */
typedef int32_t         INT32;      /**< Signed 32-bit integer */
typedef float           FLOAT;      /**< Floating precision point 32-bit variable */

typedef uint64_t        QWORD;      /**< Unsigned quad word (64-bit) */
typedef uint64_t        UINT64;     /**< Unsigned 64-bit integer */
typedef int64_t         INT64;      /**< Signed 64-bit integer */
typedef double          DOUBLE;     /**< Floating precision point 64-bit variable */

typedef uint32_t        BOOLEAN;    /**< Boolean variable */

/*******************************************************************************************************************************************
    STANDARD VALUES
*******************************************************************************************************************************************/
#ifndef FALSE
	#define FALSE       (0 == 1)    /**< A false boolean value */
#endif

#ifndef TRUE
	#define TRUE        (!FALSE)    /**< A true boolean value */
#endif

#ifndef NULL
#define NULL            0
#endif

/***************************************************************************************************************************************//**

    A common status code that indicates a result of an operation.
    @module     kernel-core

*******************************************************************************************************************************************/
typedef enum STATUS {
    SUCCESS = 0,                /**< The operation completed without any errors */
    
    ERR_TIMEOUT,                /**< The specified timeout interval has elapsed prior to completion of the operation */
    ERR_INVALIDCONTEXT,         /**< The operation has been called from an unsupported context (i.e. cannot be called from an ISR) */
    ERR_NULLREFERENCE,          /**< Indicates a required argument was found to be NULL */     
    ERR_INVALIDOPERATION,       /**< Indicates the operation was an invalid request due to the current state */
    ERR_INVALIDARGUMENT,        /**< A required argument was found to be invalid */
    ERR_NOTINITIALIZED,         /**< A specified object has not been initialized */
    ERR_ALREADYINITIALIZED,     /**< The specified object has already been initialized */
    ERR_KERNELFAILED,           /**< Indicates the kernel has failed to execute */
    ERR_BLOCKFAILED,            /**< Indicates that a thread has failed to block */
    ERR_ABORTED,                /**< An operation or thread has been aborted */
    ERR_DESTROYED,              /**< An operation failed due to an object being destroyed */
    ERR_THREADLOCK,             /**< The operation cannot complete due to an acquired interrupt lock */    
    ERR_OUTOFRANGE,             /**< Indicates that a parameter was out-of-range */
    ERR_ALIGNMENT,              /**< The operation failed due to an unsupported alignment for the target value */
    ERR_ACCESSDENIED,           /**< A request to access a resource has been denied */
    ERR_NOTSUPPORTED,           /**< A requested operation is not supported */
    ERR_NOTOWNER,               /**< Indicates an operation failed because the caller is not the owner of the target object */
    ERR_DEVICENAK,              /**< A device has returned a NAK */
    ERR_INCOMPLETE,             /**< Indicates a failure occured that caused the operation to end incomplete */
    ERR_NOTFOUND,               /**< Indicates that an item was not found */
    ERR_CORRUPTED,              /**< Indicates that corruption has been detected */
    ERR_NORESPONSE,             /**< Indicates no response */
    ERR_NOMEDIA,                /**< Indicates a disk media is not present */
    ERR_NOFILESYSTEM,           /**< Indicates a disk media does not contain a file system */
    ERR_PROTECTED,              /**< An operation failed because the target was protected */
    ERR_OVERFLOW,               /**< Indicates an operation exceeded a limitation */
    
    ERR_DRIVER = 0x0100,        /**< Start of a range of driver-specific error codes */
    ERR_DRIVER_001,             /**< Driver error code # 001 */ 
    ERR_DRIVER_002,             /**< Driver error code # 002 */ 
    ERR_DRIVER_003,             /**< Driver error code # 003 */ 
    ERR_DRIVER_004,             /**< Driver error code # 004 */ 
    ERR_DRIVER_005,             /**< Driver error code # 005 */ 
    ERR_DRIVER_006,             /**< Driver error code # 006 */ 
    ERR_DRIVER_007,             /**< Driver error code # 007 */ 
    ERR_DRIVER_008,             /**< Driver error code # 008 */ 
    ERR_DRIVER_009,             /**< Driver error code # 009 */ 
    ERR_DRIVER_010,             /**< Driver error code # 010 */ 
    ERR_DRIVER_011,             /**< Driver error code # 011 */ 
    ERR_DRIVER_012,             /**< Driver error code # 012 */ 
    ERR_DRIVER_013,             /**< Driver error code # 013 */ 
    ERR_DRIVER_014,             /**< Driver error code # 014 */ 
    ERR_DRIVER_015,             /**< Driver error code # 015 */ 
    ERR_DRIVER_016,             /**< Driver error code # 016 */ 
    ERR_DRIVER_017,             /**< Driver error code # 017 */ 
    ERR_DRIVER_018,             /**< Driver error code # 018 */     
    ERR_DRIVER_019,             /**< Driver error code # 019 */ 
    
    ERR_MAX = 0x7FFFFFFF        /**< The maximum allowable status code */
} STATUS;

/***************************************************************************************************************************************//**

    Gets the bit-field representation for the specified bit number.

    @param[in]  x           The bit number (0-31).

    @return     The bitfield with the specified bit set.

*******************************************************************************************************************************************/
#define BIT(x)              (1 << x)

/***************************************************************************************************************************************//**

    Returns the greater value between x and y.

    @param[in]  x           The first variable to be compared.
    @param[in]  y           The second variable to be compared.

    @return     The larger value between x and y.

*******************************************************************************************************************************************/
#define MAX(x, y)           (((x) > (y)) ? (x) : (y))

/***************************************************************************************************************************************//**

    Returns the lesser value between x and y.

    @param[in]  x           The first variable to be compared.
    @param[in]  y           The second variable to be compared.

    @return     The lesser value between x and y.

*******************************************************************************************************************************************/
#define MIN(x, y)           (((x) < (y)) ? (x) : (y))

#endif /* KERNEL_TYPES_H__ */
