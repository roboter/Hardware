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
#include "disk.h"

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
STATUS DISK_Mount(DISK* disk)
{
    STATUS status;
    
    
#if (CFG_NULLCHECKING)
    if (disk == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif
    
    if (!DISK_MediaPresent(disk)) {                             /* Confirm media presence */
        return ERR_NOMEDIA;                                     /* Media not present, cannot mount */
    }
    
    if (disk->mount == NULL) {
        return ERR_NOTSUPPORTED;                                /* No mount handler */
    }
    
    status = disk->mount(disk);                                 /* Mount the disk */
    if (status != SUCCESS) {
        if (disk->unmount) {
            disk->unmount(disk);                                /* Mount failed, cleanup with unmount */
        }
        return status;
    }
    
    disk->mounted = TRUE;                                       /* Indicate the disk is mounted */
    return SUCCESS;
}

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
STATUS DISK_Unmount(DISK* disk)
{
    STATUS status;
    
    
#if (CFG_NULLCHECKING)
    if (disk == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif
    
    if (disk->unmount == NULL) {
        return ERR_NOTSUPPORTED;
    }
    
    status = disk->unmount(disk);                               /* Unmount the disk */
    disk->mounted = FALSE;                                      /* Indicate the disk is no longer mounted */
    return status;
}

/***************************************************************************************************************************************//**

    Returns an indication of whether a disk has been mounted.

    @param[in]  disk        A pointer to the disk to be checked for being mounted.

    @return     TRUE if the disk has been mounted; otherwise FALSE.
    @module     fs-disk

*******************************************************************************************************************************************/
BOOLEAN DISK_Mounted(DISK* disk)
{
#if (CFG_NULLCHECKING)
    if (disk == NULL) {
        return FALSE;
    }
#endif
    
    return disk->mounted;
}

/***************************************************************************************************************************************//**

    Returns an indication of whether the media is present for a disk.

    @param[in]  disk        A pointer to the disk to be checked for media presence.

    @return     TRUE if the disk's media is present; otherwise FALSE.
    @module     fs-disk

*******************************************************************************************************************************************/
BOOLEAN DISK_MediaPresent(DISK* disk)
{
#if (CFG_NULLCHECKING)
    if (disk == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif
    
    if (disk->mediapres == NULL) {
        return TRUE;                                            /* Assume present if not implemented by driver */
    }
    
    return disk->mediapres(disk);
}

/***************************************************************************************************************************************//**

    Returns an indication of whether the media is write protected for a disk.

    @param[in]  disk        A pointer to the disk to be checked for write protection.

    @return     TRUE if the disk's media is write protected; otherwise FALSE.
    @module     fs-disk

*******************************************************************************************************************************************/
BOOLEAN DISK_WriteProtect(DISK* disk)
{
#if (CFG_NULLCHECKING)
    if (disk == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif
    
    if (disk->wp == NULL) {
        return FALSE;                                           /* Assume NOT write protected if not implemented by driver */
    }
    
    return disk->wp(disk);
}

/***************************************************************************************************************************************//**

    Returns the size of each block within a disk.

    @param[in]  disk        A pointer to the target disk.

    @return     The size, in bytes, of each block within the specified disk.
    @remark     Depending upon the type of disk, may only be valid after the disk has been mounted.
    @module     fs-disk

*******************************************************************************************************************************************/
UINT32 DISK_BlockSize(DISK* disk)
{
#if (CFG_NULLCHECKING)
    if (disk == NULL) {
        return 0;
    }
#endif
    
    return disk->blksize;
}

/***************************************************************************************************************************************//**

    Returns the number of blocks within a disk.

    @param[in]  disk        A pointer to the target disk.

    @return     The total number of blocks contained within the specified disk.
    @remark     Depending upon the type of disk, may only be valid after the disk has been mounted.
    @module     fs-disk

*******************************************************************************************************************************************/
UINT32 DISK_BlockCount(DISK* disk)
{
    #if (CFG_NULLCHECKING)
    if (disk == NULL) {
        return 0;
    }
#endif
    
    return disk->blkcnt;
}

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
STATUS DISK_Read(DISK* disk, UINT32 lba, void* buf, UINT32 nblks)
{
#if (CFG_NULLCHECKING)
    if (disk == NULL) {
        return ERR_NULLREFERENCE;
    }
    
    if (buf == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif
    
    if (disk->read == NULL) {
        return ERR_NOTSUPPORTED;
    }
    
    return disk->read(disk, lba, buf, nblks);
}

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
STATUS DISK_Write(DISK* disk, UINT32 lba, const void* data, UINT32 nblks)
{
#if (CFG_NULLCHECKING)
    if (disk == NULL) {
        return ERR_NULLREFERENCE;
    }
    
    if (data == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif
    
    if (disk->write == NULL) {
        return ERR_NOTSUPPORTED;
    }
    
    return disk->write(disk, lba, data, nblks);
}

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
STATUS DISK_Erase(DISK* disk, UINT32 lba)
{
#if (CFG_NULLCHECKING)
    if (disk == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif
    
    if (disk->erase == NULL) {
        return ERR_NOTSUPPORTED;
    }
    
    return disk->erase(disk, lba);    
}
 
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
STATUS DISK_Flush(DISK* disk)
{
#if (CFG_NULLCHECKING)
    if (disk == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif
    
    if (disk->flush == NULL) {
        return ERR_NOTSUPPORTED;
    }
    
    return disk->flush(disk);
}

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
STATUS DISK_SetMediaPresentHandler(DISK* disk, DISKMEDIAPRESHANDLER handler)
{
#if (CFG_NULLCHECKING)
    if (disk == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif
    
    disk->mediapres = handler;
    return SUCCESS;
}

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
STATUS DISK_SetWriteProtectHandler(DISK* disk, DISKWRITEPROTECTHANDLER handler)
{
#if (CFG_NULLCHECKING)
    if (disk == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif

    disk->wp = handler;
    return SUCCESS;
}
