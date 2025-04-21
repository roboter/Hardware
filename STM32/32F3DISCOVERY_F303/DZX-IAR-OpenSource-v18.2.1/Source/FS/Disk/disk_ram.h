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
#ifndef DISK_RAM_H__
#define DISK_RAM_H__

#include "disk.h"

/*******************************************************************************************************************************************
    TYPE DEFINITIONS
*******************************************************************************************************************************************/
typedef struct RAMDISK RAMDISK;

/***************************************************************************************************************************************//**

    Represents a media disk that is implemented upon RAM memory.
    @module     fs-ramdisk

*******************************************************************************************************************************************/
struct RAMDISK {
    DISK base;              /**< Provides an implementation for the base DISK */
    void* mem;              /**< A pointer to the memory that represents the disk image */
};

/*******************************************************************************************************************************************
    PUBLIC FUNCTIONS
*******************************************************************************************************************************************/
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
extern STATUS RAMDISK_Create(RAMDISK* disk, void* mem, UINT32 blksize, UINT32 blkcnt);

#endif /* DISK_RAM_H__ */
