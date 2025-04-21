/*******************************************************************************************************************************************

    DZX | LPC18xx | IAP                                                                                                   VERSION 18.2.1
    ------------------------------------------------------------------------------------------------------------------------------------

    This is part of the MCU peripheral drivers and provides support for the In-Application Programming (IAP) interface.

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
#ifndef MCU_IAP_H__
#define MCU_IAP_H__

#include "Kernel/kernel.h"

/***************************************************************************************************************************************//**

    A serial number that is received via the In-Application Programming (IAP) interface.
    @module     iap-lpc18xx

*******************************************************************************************************************************************/
typedef struct LPC18XX_IAPSERIALNUMBER {
	BYTE values[16];            /**< The individual values of the serial number */
} IAPSERIALNUMBER;

/*******************************************************************************************************************************************
    PUBLIC FUNCTIONS
*******************************************************************************************************************************************/
/***************************************************************************************************************************************//**

    Initializes the In-Application Programming interface.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The part identification number was successfully read and returned.
     ERR_DRIVER             | The IAP interface has returned an error.

    @module     iap-lpc18xx

*******************************************************************************************************************************************/
extern STATUS IAP_Initialize(void);

/***************************************************************************************************************************************//**

    Reads and returns the part identification numbers.

    @param[out] id1         A pointer to a caller allocated variable to receive the first part identification number.
    @param[out] id2         A pointer to a caller allocated variable to receive the second part identification number.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The part identification numbers were read and returned.
     ERR_NULLREFERENCE      | The argument 'id1' or 'id2' was found to be NULL.
     ERR_DRIVER             | The IAP interface has returned an error.

    @module     iap-lpc18xx

*******************************************************************************************************************************************/
extern STATUS IAP_ReadPartID(UINT32* id1, UINT32* id2);

/***************************************************************************************************************************************//**

    Reads and returns the version number for the In-Application Programming (IAP) interface.

    @param[out] major       A pointer to a caller allocated value to receive major ASCII encoded version number.
    @param[out] minor       A pointer to a caller allocated value to receive minor ASCII encoded version number.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The version number was successfully read and returned.
     ERR_NULLREFERENCE      | The argument 'major' or 'minor' was found to be NULL.
     ERR_DRIVER             | The IAP interface has returned an error.

    @module     iap-lpc18xx

*******************************************************************************************************************************************/
extern STATUS IAP_ReadBootCodeVersion(CHAR* major, CHAR* minor);

/***************************************************************************************************************************************//**

    Reads a unique serial number from the In-Application Programming (IAP) interface.

    @param[out] sn          A pointer to a caller allocated value to receive the serial number.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The serial number was successfully read and returned.
     ERR_DRIVER             | The IAP interface has returned an error.

    @module     iap-lpc18xx

*******************************************************************************************************************************************/
extern STATUS IAP_ReadSerialNumber(IAPSERIALNUMBER* sn);

/***************************************************************************************************************************************//**

    Prepares internal flash sectors to be erased or programmed.

    @param[in] startSector  The starting sector to be prepared.
    @param[in] endSector    The ending sector to be prepared. Set equal to startSector to prepare a single sector.
    @param[in] bank         The flash bank (0 = bank A, 1 = bank B).

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The sectors were successfully prepared.
     ERR_DRIVER             | The IAP interface has returned an error.

    @module     iap-lpc18xx

*******************************************************************************************************************************************/
extern STATUS IAP_PrepareSector(UINT32 startSector, UINT32 endSector, UINT32 bank);

/***************************************************************************************************************************************//**

    Erases internal flash sectors.

    @param[in] startSector  The starting sector to be erased.
    @param[in] endSector    The ending sector to be erased. Set equal to startSector to erased a single sector.
    @param[in] bank         The flash bank (0 = bank A, 1 = bank B).

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The sectors were successfully erased.
     ERR_DRIVER             | The IAP interface has returned an error.

    @module     iap-lpc18xx

*******************************************************************************************************************************************/
extern STATUS IAP_EraseSector(UINT32 startSector, UINT32 endSector, UINT32 bank);

/***************************************************************************************************************************************//**

    Programs the internal flash memory.

    @param[in]  destAddr    The destination flash address to be programmed. This address must be on a 256-byte boundry.
    @param[in]  srcAddr     The source RAM address of the data to be programmed. This address must be on a word boundry.
    @param[in]  nbytes      The total number of bytes to be programmed. Must be 256, 512, 1024, or 4096.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The flash memory was successfully programmed.
     ERR_DRIVER             | The IAP interface has returned an error.

    @module     iap-lpc18xx

*******************************************************************************************************************************************/
extern STATUS IAP_CopyRamToFlash(UINT32 destAddr, UINT32 srcAddr, UINT32 nbytes);

#endif /* MCU_IAP_H__ */
