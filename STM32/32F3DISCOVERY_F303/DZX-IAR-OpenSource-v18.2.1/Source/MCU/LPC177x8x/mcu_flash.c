/*******************************************************************************************************************************************

    DZX | LPC177x8x | FLASH                                                                                               VERSION 18.2.1
    ------------------------------------------------------------------------------------------------------------------------------------

    This is part of the MCU peripheral drivers and provides support for programming the on-chip flash memory.

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
#include "mcu_flash.h"
#include "mcu_iap.h"
#include <string.h>

/***************************************************************************************************************************************//**

    Returns a zero based sector number for the specified address.

    @param[in]  address     The physical address to be converted into a sector number.

    @return     The positive zero-based sector number.
    @module     flash-lpc177x8x

*******************************************************************************************************************************************/
UINT32 FLASH_GetSector(UINT32 address)
{
    if (address < 0x10000) {                                    /* Is the address within the area of 4KB sectors? */
        return (address / 0x1000);                              /* Yes, return one of the 4KB sectors */
    }
    
    return (address / 0x8000) + 14;                             /* No, the address is within the area of 32KB sectors */
}

/***************************************************************************************************************************************//**

    Returns an indication of whether the specified address is the start of a sector.

    @param[in]  address     The target address.

    @return     TRUE if the specified address is the start of a sector; otherwise FALSE.
    @module     FLASH-LPC177X8X

*******************************************************************************************************************************************/
BOOLEAN FLASH_IsSectorStart(UINT32 address)
{
    if (address < 0x10000) {                                    /* Is the address within the area of 4KB sectors? */
        if ((address % 0x1000) == 0) {                          /* Is the address aligned to a 4KB sector? */
            return TRUE;                                        /* Yes, address is the start of a 4KB sector */
        }
    }
    
    if ((address % 0x8000) == 0) {                              /* Is the address aligned to a 32KB sector? */
        return TRUE;                                            /* Yes, address is the start of a 32KB sector */
    }
    
    return FALSE;
}

/***************************************************************************************************************************************//**

    Erases a single sector of on-chip flash memory.

    @param[in]  sector      The zero-based number of the sector to be erased.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The specified sector was successfully erased.
     ERRDRIVER              | An occurred within the underlying flash programming driver (IAP).

    @remark     Interrupts are locked for the duration of the operation.
    @module     flash-lpc177x8x

*******************************************************************************************************************************************/
STATUS FLASH_EraseSector(UINT32 sector)
{
    INTERRUPTLOCK lock;
    STATUS status;


    ACQUIREINTERRUPTLOCK();

    status = IAP_PrepareSector(sector, sector);                 /* Prepare the sector to be erased */
    if (status == SUCCESS) {
        status = IAP_EraseSector(sector, sector);               /* Erase the sector */
    }

    RELEASEINTERRUPTLOCK();
    return status;
}

/***************************************************************************************************************************************//**

    Reads and returns data from the on-chip flash memory.

    @param[in]  addr        The starting address to be read.
    @param[out] buf         A pointer to a caller allocated buffer to receive the memory data.
    @param[in]  nbytes      The total number of bytes of memory to be read.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The flash memory was successfully read and returned.
     ERR_NULLREFERENCE      | The argument 'buf' was found to be NULL.
     ERR_OUTOFRANGE         | The read was outside the range of the flash memory.

    @module     flash-lpc177x8x

*******************************************************************************************************************************************/
STATUS FLASH_Read(UINT32 addr, void* buf, UINT32 nbytes)
{
#if (CFG_NULLCHECKING)
    if (buf == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif
    
    memcpy(buf, (void*)addr, nbytes);       /* Read the memory */
    return SUCCESS;
}

/***************************************************************************************************************************************//**

    Returns an indication of whether a block of flash data is blank.

    @param[in]  data        A pointer to the start of the data that is to be checked for blank.
    @param[in]  nbytes      The size, in bytes, of the data block.

    @return     TRUE if the specified block is blank; otherwise FALSE.
    @module     internal

*******************************************************************************************************************************************/
static BOOLEAN FLASH_IsBlank(const void* data, UINT32 nbytes)
{
    UINT32 i;
    
    
    for (i = 0; i < nbytes / sizeof(UINT32); i++) {
        if (((UINT32*)data)[i] != 0xFFFFFFFF) {
            return FALSE;
        }
    }
    
    return TRUE;
}

/***************************************************************************************************************************************//**

    Programs data directly to the internal on-chip flash memory.

    @param[in]  addr        The target flash memory address to be written. Must be on a 256 byte boundry.
    @param[in]  data        A pointer to the data to be written. Must be word (32-bit) aligned.
    @param[in]  nbytes      The total number of bytes to be written. Must be either 256, 512, 1024, or 4096.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The specified data was successfully programmed within the flash memory.
     ERR_NULLREFERENCE      | The argument 'data' was found to be NULL.
     ERR_ALIGNMENT          | The argument 'addr' or 'data' has an invalid alignment.
     ERR_NOTSUPPORTED       | The specified number of bytes is not supported.
     ERRNOTFOUND            | The sector for the specified address was not found.
     ERRDRIVER              | An occurred within the underlying flash programming driver (IAP).

    @remark     Interrupts are disabled for the duration of this operation.
    @module     flash-lpc177x8x

*******************************************************************************************************************************************/
STATUS FLASH_Write(UINT32 addr, const void* data, UINT32 nbytes)
{
    INTERRUPTLOCK lock;
    STATUS status;
    UINT32 sector;


#if (CFG_NULLCHECKING)
    if (data == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif

    if (((UINT32)data % sizeof(void*)) != 0) {
        return ERR_ALIGNMENT;
    }

    if ((addr % 256) != 0) {
        return ERR_ALIGNMENT;
    }

    if (nbytes != 256 && nbytes != 512 &&
        nbytes != 1024 && nbytes != 4096) {
        return ERR_NOTSUPPORTED;
    }
    
    if (FLASH_IsBlank(data, nbytes)) {
        return SUCCESS;
    }

    sector = FLASH_GetSector(addr);                                         /* Lookup the target sector number */

    ACQUIREINTERRUPTLOCK();

    status = IAP_PrepareSector(sector, sector);                             /* Prepare the sector */
    if (status == SUCCESS) {
        status = IAP_CopyRamToFlash(addr, (UINT32)data, nbytes);
    }

    RELEASEINTERRUPTLOCK();
    return status;
}
