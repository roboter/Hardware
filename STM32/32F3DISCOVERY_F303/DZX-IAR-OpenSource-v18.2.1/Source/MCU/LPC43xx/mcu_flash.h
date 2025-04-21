/*******************************************************************************************************************************************

    DZX | LPC43xx | FLASH                                                                                                 VERSION 18.2.1
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
#ifndef MCU_FLASH_H__
#define MCU_FLASH_H__

#include "Kernel/kernel.h"

/*******************************************************************************************************************************************
    PUBLIC FUNCTIONS
*******************************************************************************************************************************************/
/***************************************************************************************************************************************//**

    Returns a zero based sector number for the specified address.

    @param[in]  address     The physical address to be converted into a sector number.

    @return     The positive zero-based sector number.
    @module     flash-lpc43xx

*******************************************************************************************************************************************/
extern UINT32 FLASH_GetSector(UINT32 address);

/***************************************************************************************************************************************//**

    Returns a zero based bank number for the specified address.

    @param[in]  address     The physical address to be converted into a flash bank number.

    @return     The positive zero-based flash bank number.
    @module     flash-lpc43xx

*******************************************************************************************************************************************/
extern UINT32 FLASH_GetBank(UINT32 address);

/***************************************************************************************************************************************//**

    Returns an indication of whether the specified address is the start of a sector.

    @param[in]  address     The target address.

    @return     TRUE if the specified address is the start of a sector; otherwise FALSE.
    @module     flash-lpc43xx

*******************************************************************************************************************************************/
extern BOOLEAN FLASH_IsSectorStart(UINT32 address);

/***************************************************************************************************************************************//**

    Erases a single sector of on-chip flash memory.

    @param[in]  sector      The zero-based number of the sector to be erased.
    @param[in]  bank        The bank that contains the sector to be erased (0 = bank A, 1 = bank B).

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The specified sector was successfully erased.
     ERRDRIVER              | An occurred within the underlying flash programming driver (IAP).

    @remark     Interrupts are locked for the duration of the operation.
    @module     flash-lpc43xx

*******************************************************************************************************************************************/
extern STATUS FLASH_EraseSector(UINT32 sector, UINT32 bank);

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

    @module     flash-lpc43xx

*******************************************************************************************************************************************/
extern STATUS FLASH_Read(UINT32 address, void* buf, UINT32 nbytes);

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

    @remark     This call disables interrupts throughout the duration of the operation.
    @module     flash-lpc43xx

*******************************************************************************************************************************************/
extern STATUS FLASH_Write(UINT32 address, const void* data, UINT32 nbytes);

#endif /* MCU_FLASH_H__ */
