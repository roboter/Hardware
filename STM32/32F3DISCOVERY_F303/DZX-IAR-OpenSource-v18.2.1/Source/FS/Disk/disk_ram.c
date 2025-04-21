/*******************************************************************************************************************************************

    DZX | FILE SYSTEM | RAM DISK                                                                                          VERSION 18.2.1
    ------------------------------------------------------------------------------------------------------------------------------------

    This provides a driver for accessing a media disk that uses RAM memory for storage. Once the disk driver has been created, use the 
    generic DISK functions for mounting or reading/writing the disk.

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
#include "disk_ram.h"
#include <string.h>

/*******************************************************************************************************************************************
    PRIVATE FUNCTIONS
*******************************************************************************************************************************************/
static STATUS RAMDISK_Mount(DISK* disk);
static STATUS RAMDISK_Unmount(DISK* disk);
static STATUS RAMDISK_Read(DISK* disk, UINT32 lba, void* buf, UINT32 num);
static STATUS RAMDISK_Write(DISK* disk, UINT32 lba, const void* data, UINT32 num);
static STATUS RAMDISK_Flush(DISK* disk);


/***************************************************************************************************************************************//**

    Creates and initializes a disk driver that uses RAM memory for data storage.

    @param[in]  disk        A pointer to a caller allocated RAM disk driver instance to be initialized.
    @param[in]  mem         A pointer to the RAM memory that represents the disk image. The specified memory area must be at least
                            (sectorSize * sectorCount) in size.
    @param[in]  blksize     The size, in bytes, of each of the blocks within the disk.
    @param[in]  blkcnt      The total number of blocks contained within the disk.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The disk has been initialized.
     ERR_NULLREFERENCE      | The argument 'disk' or 'mem' was found to be NULL.

    @module     fs-ramdisk

*******************************************************************************************************************************************/
STATUS RAMDISK_Create(RAMDISK* disk, void* mem, UINT32 blksize, UINT32 blkcnt)
{
#if (CFG_NULLCHECKING)
    if (disk == NULL) {
        return ERR_NULLREFERENCE;
    }
    
    if (mem == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif

    disk->base.blksize = blksize;                               /* Cache block information */
    disk->base.blkcnt = blkcnt;
    
    disk->base.mount = RAMDISK_Mount;                           /* Assign specific handler functions */
    disk->base.unmount = RAMDISK_Unmount;
    disk->base.read = RAMDISK_Read;         
    disk->base.write = RAMDISK_Write;
    disk->base.flush = RAMDISK_Flush;
    
    disk->mem = mem;
    return SUCCESS;
}

/***************************************************************************************************************************************//**

    A disk handler function that mounts a RAM disk.

    @param[in]  disk        A pointer to the disk to be mounted.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The disk has been mounted.

    @module     internal

*******************************************************************************************************************************************/
static STATUS RAMDISK_Mount(DISK* disk)
{
    return SUCCESS;         /* Nothing to do for a RAM disk */
}

/***************************************************************************************************************************************//**

    A disk handler function that unmounts a RAM disk.

    @param[in]  disk        A pointer to the disk to be unmounted.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The disk has been unmounted.

    @module     internal

*******************************************************************************************************************************************/
static STATUS RAMDISK_Unmount(DISK* disk)
{
    return SUCCESS;         /* Nothing to do for a RAM disk */
}

/***************************************************************************************************************************************//**

    A disk handler function that reads data from a RAM disk.

    @param[in]  disk        A pointer to the disk to be read.
    @param[in]  lba         The logical block address to be read.
    @param[out] buf         A pointer to a caller allocated buffer to receive the data from the disk.
    @param[in]  num         The number of sectors to be read and returned.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The data has been read and returned from the disk.

    @module     internal

*******************************************************************************************************************************************/
static STATUS RAMDISK_Read(DISK* disk, UINT32 lba, void* buf, UINT32 num)
{
    RAMDISK* rdisk;
    
    
    rdisk = (RAMDISK*)disk;
    memcpy(buf, &((BYTE*)rdisk->mem)[lba * disk->blksize], num * disk->blksize);
    
    return SUCCESS;
}

/***************************************************************************************************************************************//**

    A disk handler function that writes data to a RAM disk.

    @param[in]  disk        A pointer to the disk to be written.
    @param[in]  lba         The logical block address to be written.
    @param[in]  data        A pointer to the data to be written to the disk.
    @param[in]  num         The number of sectors to be written.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The data has been written to the disk.

    @module     internal

*******************************************************************************************************************************************/
static STATUS RAMDISK_Write(DISK* disk, UINT32 lba, const void* data, UINT32 nblks)
{
    RAMDISK* rdisk;
    
    
    rdisk = (RAMDISK*)disk;
    memcpy(&((BYTE*)rdisk->mem)[lba * disk->blksize], data, nblks * disk->blksize);
    
    return SUCCESS;
} 

/***************************************************************************************************************************************//**

    A disk handler function that flushes any cached data for the disk. 

    @param[in]  disk        A pointer to the disk to be flushed.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The disk cache has been flushed.

    @module     internal

*******************************************************************************************************************************************/
static STATUS RAMDISK_Flush(DISK* disk)
{
    return SUCCESS;             /* Nothing to do for a RAM disk */
}
