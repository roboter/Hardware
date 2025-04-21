/*******************************************************************************************************************************************

    DZX | FILE SYSTEM | DISK                                                                                              VERSION 18.2.1
    ------------------------------------------------------------------------------------------------------------------------------------

    This provides an abstract interface for using a disk driver to access a media disk.

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
#ifndef DISK_H__
#define DISK_H__

#include "Kernel/kernel.h"

/*******************************************************************************************************************************************
    TYPE DEFINITIONS
*******************************************************************************************************************************************/
typedef struct DISK DISK;

/***************************************************************************************************************************************//**

    Represents a function that handles an operation upon a disk.
    @module     fs-disk

*******************************************************************************************************************************************/
typedef STATUS (*DISKHANDLER)(DISK* disk);

/***************************************************************************************************************************************//**

    Represents a function that handles a read sector operation upon a disk.
    @module     fs-disk

*******************************************************************************************************************************************/
typedef STATUS (*DISKREADHANDLER)(DISK* disk, UINT32 lba, void* buf, UINT32 num);

/***************************************************************************************************************************************//**

    Represents a function that handles a write sector operation upon a disk.
    @module     fs-disk

*******************************************************************************************************************************************/
typedef STATUS (*DISKWRITEHANDLER)(DISK* disk, UINT32 lba, const void* data, UINT32 num);

/***************************************************************************************************************************************//**

    Represents a function that handles an erase sector operation upon a disk.
    @module     fs-disk

*******************************************************************************************************************************************/
typedef STATUS (*DISKERASEHANDLER)(DISK* disk, UINT32 lba);

/***************************************************************************************************************************************//**

    Represents a function that handles a media presence check operation upon a disk.
    @module     fs-disk

*******************************************************************************************************************************************/
typedef BOOLEAN (*DISKMEDIAPRESHANDLER)(DISK* disk);

/***************************************************************************************************************************************//**

    Represents a function that handles a write protection check operation upon a disk.
    @module     fs-disk

*******************************************************************************************************************************************/
typedef BOOLEAN (*DISKWRITEPROTECTHANDLER)(DISK* disk);

/***************************************************************************************************************************************//**

    Represents an abstract media disk.
    @module     fs-disk

*******************************************************************************************************************************************/
struct DISK {
    UINT32 blksize;                 /**< The size, in bytes, of each block within the disk */
    UINT32 blkcnt;                  /**< The number of blocks contained within the disk */
    DISKHANDLER mount;              /**< A handler that mounts the disk */
    DISKHANDLER unmount;            /**< A handler that unmounts the disk */
    DISKREADHANDLER read;           /**< A handler that reads sectors from the disk */
    DISKWRITEHANDLER write;         /**< A handler that writes sectors on the disk */
    DISKERASEHANDLER erase;         /**< A handler that erases sectors on the disk */
    DISKHANDLER flush;              /**< A handler that flushes any cache for the disk */
    DISKMEDIAPRESHANDLER mediapres; /**< A handler that checks if for the media presence */
    DISKWRITEPROTECTHANDLER wp;     /**< A handler that check if the disk is write protected */
    BOOLEAN mounted;                /**< An indication of whether the disk has been mounted */
};

/*******************************************************************************************************************************************
    PUBLIC FUNCTIONS
*******************************************************************************************************************************************/
/***************************************************************************************************************************************//**

    Mounts a disk and prepares for I/O operations.

    @param[in]  disk        A pointer to the disk to be mounted.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The disk has been mounted.
     ERR_NULLREFERENCE      | The argument 'disk' was found to be NULL.
     ERR_NOMEDIA            | The media is not present for the disk.
     ERR_NOTSUPPORTED       | The specified disk does not support being mounted.

    @remark     If the disk fails to mount, it is unmounted to leave the disk in a known state.
    @module     fs-disk

*******************************************************************************************************************************************/
extern STATUS DISK_Mount(DISK* disk);

/***************************************************************************************************************************************//**

    Unmounts a disk.

    @param[in]  disk        A pointer to the disk to be unmounted.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The disk has been unmounted.
     ERR_NULLREFERENCE      | The argument 'disk' was found to be NULL.
     ERR_NOTSUPPORTED       | The specified disk does not support being unmounted.

    @module     fs-disk

*******************************************************************************************************************************************/
extern STATUS DISK_Unmount(DISK* disk);

/***************************************************************************************************************************************//**

    Returns an indication of whether a disk has been mounted.

    @param[in]  disk        A pointer to the disk to be checked for being mounted.

    @return     TRUE if the disk has been mounted; otherwise FALSE.
    @module     fs-disk

*******************************************************************************************************************************************/
extern BOOLEAN DISK_Mounted(DISK* disk);

/***************************************************************************************************************************************//**

    Returns an indication of whether the media is present for a disk.

    @param[in]  disk        A pointer to the disk to be checked for media presence.

    @return     TRUE if the disk's media is present; otherwise FALSE.
    @module     fs-disk

*******************************************************************************************************************************************/
extern BOOLEAN DISK_MediaPresent(DISK* disk);

/***************************************************************************************************************************************//**

    Returns an indication of whether the media is write protected for a disk.

    @param[in]  disk        A pointer to the disk to be checked for write protection.

    @return     TRUE if the disk's media is write protected; otherwise FALSE.
    @module     fs-disk

*******************************************************************************************************************************************/
extern BOOLEAN DISK_WriteProtect(DISK* disk);

/***************************************************************************************************************************************//**

    Returns the size of each block within a disk.

    @param[in]  disk        A pointer to the target disk.

    @return     The size, in bytes, of each block within the specified disk.
    @remark     Depending upon the type of disk, may only be valid after the disk has been mounted.
    @module     fs-disk

*******************************************************************************************************************************************/
extern UINT32 DISK_BlockSize(DISK* disk);

/***************************************************************************************************************************************//**

    Returns the number of blocks within a disk.

    @param[in]  disk        A pointer to the target disk.

    @return     The total number of blocks contained within the specified disk.
    @remark     Depending upon the type of disk, may only be valid after the disk has been mounted.
    @module     fs-disk

*******************************************************************************************************************************************/
extern UINT32 DISK_BlockCount(DISK* disk);

/***************************************************************************************************************************************//**

    Reads and returns data from a disk.

    @param[in]  disk        A pointer to the disk to be read.
    @param[in]  lba         The logical block address to be read.
    @param[out] buf         A pointer to caller allocated buffer to receive the data read from the disk.
    @param[in]  nblks       The total number of blocks to be read.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The data has been read and returned from the disk.
     ERR_NULLREFERENCE      | The argument 'disk' or 'buf' was found to be NULL.
     ERR_NOTSUPPORTED       | The specified disk does not support being read.

    @module     fs-disk

*******************************************************************************************************************************************/
extern STATUS DISK_Read(DISK* disk, UINT32 lba, void* buf, UINT32 nblks);

/***************************************************************************************************************************************//**

    Writes data to a disk.

    @param[in]  disk        A pointer to the disk to be written.
    @param[in]  lba         The logical block address to be written.
    @param[in]  data        A pointer to the data to be written to the disk.
    @param[in]  nblks       The total number of blocks to be written.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The data has been written to the disk.
     ERR_NULLREFERENCE      | The argument 'disk' or 'data' was found to be NULL.
     ERR_NOTSUPPORTED       | The specified disk does not support being written.

    @module     fs-disk

*******************************************************************************************************************************************/
extern STATUS DISK_Write(DISK* disk, UINT32 lba, const void* data, UINT32 nblks);

/***************************************************************************************************************************************//**

    Erases a sector within a disk.

    @param[in]  disk        A pointer to the disk that contains the sector to be erased.
    @param[in]  lba         The logical block address to be erased.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The specified sector has been erased.
     ERR_NULLREFERENCE      | The argument 'disk' was found to be NULL.
     ERR_NOTSUPPORTED       | The specified disk does not support erasing sectors.

    @module     fs-disk

*******************************************************************************************************************************************/
extern STATUS DISK_Erase(DISK* disk, UINT32 lba);

/***************************************************************************************************************************************//**

    Flushes any cached data to a disk.

    @param[in]  disk        A pointer to the disk that contains cached data to be flushed.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The disk has been flushed.
     ERR_NULLREFERENCE      | The argument 'disk' was found to be NULL.
     ERR_NOTSUPPORTED       | The specified disk does not support being flushed.

    @module     fs-disk

*******************************************************************************************************************************************/
extern STATUS DISK_Flush(DISK* disk);

/***************************************************************************************************************************************//**

    Assigns a custom application-defined handler function for checking if the disk's media is present.

    @param[in]  disk        A pointer to the disk to receive the handler.
    @param[in]  handler     The function that will handle the checking for the presence of the disk's media.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The specified handler function has been set.
     ERR_NULLREFERENCE      | The argument 'disk' was found to be NULL.

    @module     fs-disk

*******************************************************************************************************************************************/
extern STATUS DISK_SetMediaPresentHandler(DISK* disk, DISKMEDIAPRESHANDLER handler);

/***************************************************************************************************************************************//**

    Assigns a custom application-defined handler function for checking if the disk's media is write protected.

    @param[in]  disk        A pointer to the disk to receive the handler.
    @param[in]  handler     The function that will handle the checking if the disk's media is write protected.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The specified handler function has been set.
     ERR_NULLREFERENCE      | The argument 'disk' was found to be NULL.

    @module     fs-disk

*******************************************************************************************************************************************/
extern STATUS DISK_SetWriteProtectHandler(DISK* disk, DISKWRITEPROTECTHANDLER handler);

#endif /* DISK_H__ */
