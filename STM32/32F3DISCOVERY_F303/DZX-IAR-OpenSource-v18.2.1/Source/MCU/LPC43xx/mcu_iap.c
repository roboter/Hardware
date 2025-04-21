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
#include "mcu_iap.h"
#include "mcu_cfg.h"
#include <string.h>

/*******************************************************************************************************************************************
    PRIVATE DEFINITIONS
*******************************************************************************************************************************************/
#define IAPLOCATION                     *(volatile UINT32 *)(0x10400100)  /**< The location of the entry point for the IAP driver */
#define IAPCMDINITIALIZE                49          /**< The IAP Initialize command number */
#define IAPCMDPREPARESECTOR             50          /**< The IAP Prepare Sector command number */
#define IAPCMDCOPYRAMTOFLASH            51          /**< The IAP Copy RAM To FLASH command number */
#define IAPCMDERASESECTOR               52          /**< The IAP Erase Sector command number */
#define IAPCMDBLANKCHECKSECTOR          53          /**< The IAP Blank Check Sector command number */
#define IAPCMDREADPARTID                54          /**< The IAP Read Part ID command number */
#define IAPCMDREADBOOTCODEVERSION       55          /**< The IAP Read Boot Code Version command number */
#define IAPCMDREADDEVICESERIALNUMBER    58          /**< The IAP Read Device Serial Number command number */

/*******************************************************************************************************************************************
    PRIVATE 
*******************************************************************************************************************************************/
static void IAP_Command(UINT32* cmd, UINT32* result);

/***************************************************************************************************************************************//**

    Represents the command function for the IAP interface.
    @module     internal

*******************************************************************************************************************************************/
typedef void (*IAPFUNCTION)(UINT32* cmd, UINT32* result);

/***************************************************************************************************************************************//**

    Executes a command by calling into the In-Application Programming interface.

    @param[in]  cmd         A pointer to the command to be executed.
    @param[out] result      A caller allocated buffer to receive the results of the command.

    @return     None
    @remark     Executes the command within a critical section.
    @module     iap-lpc43xx

*******************************************************************************************************************************************/
static void IAP_Command(UINT32* cmd, UINT32* result)
{
    INTERRUPTLOCK lock;
     
    
    ACQUIREINTERRUPTLOCK();
    ((IAPFUNCTION)IAPLOCATION)(cmd, result);
    RELEASEINTERRUPTLOCK();
}

/***************************************************************************************************************************************//**

    Initializes the In-Application Programming interface.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The part identification number was successfully read and returned.
     ERR_DRIVER             | The IAP interface has returned an error.

    @module     iap-lpc43xx

*******************************************************************************************************************************************/
STATUS IAP_Initialize(void)
{
    UINT32 results[4];
    UINT32 cmds[6];
    
    
    cmds[0] = IAPCMDINITIALIZE;
    
    IAP_Command(cmds, results);                             /* Execute the command */
    return (STATUS)(ERR_DRIVER + results[0]);
}

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

    @module     iap-lpc43xx

*******************************************************************************************************************************************/
STATUS IAP_ReadPartID(UINT32* id1, UINT32* id2)
{
    UINT32 results[3];
    UINT32 command = IAPCMDREADPARTID;


#if (CFG_NULLCHECKING)
    if (id1 == NULL) {
        return ERR_NULLREFERENCE;
    }
    
    if (id2 == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif
    
    IAP_Command(&command, &results[0]);                  /* Execute the command */

    if (results[0] == 0) {                               /* Completed successfully? */
        *id1 = results[1];
        *id2 = results[2];
        return SUCCESS;
    }

    return (STATUS)(ERR_DRIVER + results[0]);
}

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

    @module     iap-lpc43xx

*******************************************************************************************************************************************/
STATUS IAP_ReadBootCodeVersion(CHAR* major, CHAR* minor)
{
    UINT32 results[2];
    UINT32 cmd = IAPCMDREADBOOTCODEVERSION;
    
    
#if (CFG_NULLCHECKING)
    if (major == NULL) {
        return ERR_NULLREFERENCE;
    }
    
    if (minor == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif

    IAP_Command(&cmd, &results[0]);                      /* Execute the command */

    if (results[0] == 0) {                               /* Assign the versions if the command was successful */
        *minor = results[1] & 0x000000FF;
        *major = (results[1] & 0x0000FF00) >> 8;
        return SUCCESS;
    }

    return (STATUS)(ERR_DRIVER + results[0]);
}

/***************************************************************************************************************************************//**

    Reads a unique serial number from the In-Application Programming (IAP) interface.

    @param[out] sn          A pointer to a caller allocated value to receive the serial number.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The serial number was successfully read and returned.
     ERR_DRIVER             | The IAP interface has returned an error.

    @module     iap-lpc43xx

*******************************************************************************************************************************************/
STATUS IAP_ReadSerialNumber(IAPSERIALNUMBER* sn)
{
    UINT32 results[5];
    UINT32 cmd = IAPCMDREADDEVICESERIALNUMBER;


    IAP_Command(&cmd, &results[0]);

    if (results[0] == 0) {
        memcpy(sn, &results[1], sizeof(IAPSERIALNUMBER));
        return SUCCESS;
    }

    return (STATUS)(ERR_DRIVER + results[0]);
}

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

    @module     iap-lpc43xx

*******************************************************************************************************************************************/
STATUS IAP_PrepareSector(UINT32 startSector, UINT32 endSector, UINT32 bank)
{
    UINT32 result;
    UINT32 cmds[4];


    cmds[0] = IAPCMDPREPARESECTOR;
    cmds[1] = startSector;
    cmds[2] = endSector;
    cmds[3] = bank;
    
    IAP_Command(&cmds[0], &result);    /* Execute the command */

    if (result == 0) {
        return SUCCESS;
    }

    return (STATUS)(ERR_DRIVER + result);
}

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

    @module     iap-lpc43xx

*******************************************************************************************************************************************/
STATUS IAP_EraseSector(UINT32 startSector, UINT32 endSector, UINT32 bank)
{
    UINT32 result;
    UINT32 cmds[5];

    cmds[0] = IAPCMDERASESECTOR;
    cmds[1] = startSector;
    cmds[2] = endSector;
    cmds[3] = (CFG_CPUCLOCKHZ / 1000);
    cmds[4] = bank;

    IAP_Command(&cmds[0], &result);  /* Execute the command */

    if (result == 0) {
        return SUCCESS;
    }

    return (STATUS)(ERR_DRIVER + result);
}

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

    @module     iap-lpc43xx

*******************************************************************************************************************************************/
STATUS IAP_CopyRamToFlash(UINT32 destAddr, UINT32 srcAddr, UINT32 nbytes)
{
    UINT32 result;
    UINT32 cmds[5];


    cmds[0] = IAPCMDCOPYRAMTOFLASH;
    cmds[1] = destAddr;
    cmds[2] = srcAddr;
    cmds[3] = nbytes;
    cmds[4] = (CFG_CPUCLOCKHZ / 1000);

    IAP_Command(&cmds[0], &result);

    if (result == 0) {
        return SUCCESS;
    }

    return (STATUS)(ERR_DRIVER + result);
}
