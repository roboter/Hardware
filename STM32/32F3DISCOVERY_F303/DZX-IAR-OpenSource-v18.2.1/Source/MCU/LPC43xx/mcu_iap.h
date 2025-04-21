/*******************************************************************************************************************************************

    DZX | LPC43xx | IAP                                                                                                   VERSION 18.2.1
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
    @module     iap-lpc43xx

*******************************************************************************************************************************************/
typedef struct LPC43XX_IAPSERIALNUMBER {
	BYTE values[16];            /**< The individual values of the serial number */
} IAPSERIALNUMBER;

/*******************************************************************************************************************************************
    PUBLIC FUNCTIONS
*******************************************************************************************************************************************/
extern STATUS IAP_Initialize(void);
extern STATUS IAP_ReadPartID(UINT32* id1, UINT32* id2);
extern STATUS IAP_ReadBootCodeVersion(CHAR* major, CHAR* minor);
extern STATUS IAP_ReadSerialNumber(IAPSERIALNUMBER* sn);
extern STATUS IAP_PrepareSector(UINT32 startSector, UINT32 endSector, UINT32 bank);
extern STATUS IAP_EraseSector(UINT32 startSector, UINT32 endSector, UINT32 bank);
extern STATUS IAP_CopyRamToFlash(UINT32 destAddr, UINT32 srcAddr, UINT32 nbytes);

#endif /* MCU_IAP_H__ */
