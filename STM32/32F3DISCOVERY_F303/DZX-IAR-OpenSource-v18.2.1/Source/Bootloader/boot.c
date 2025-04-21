/*******************************************************************************************************************************************

    DZX | BOOTLOADER | BOOT                                                                                               VERSION 18.2.1
    ------------------------------------------------------------------------------------------------------------------------------------

    This provides support for creating a bootloader that can switch execution with a runtime application via a shared RAM key. Use 
    header file 'boot_cfg.h' for configuration settings.

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
#include "boot.h"
#include "mcu_kernel.h"

/*******************************************************************************************************************************************
    PRIVATE FUNCTIONS
*******************************************************************************************************************************************/
static UINT32 BOOT_GetSignature(void);
static void BOOT_SetSignature(UINT32 value);

/***************************************************************************************************************************************//**

    Returns the current value of the signature field.

    @return     The current signature value.
    @module     internal

*******************************************************************************************************************************************/
static UINT32 BOOT_GetSignature(void)
{
    return (*(UINT32*)CFG_BOOTSIGADDRESS);                      /* Return the value stored at the signature address */
}

/***************************************************************************************************************************************//**

    Writes a value to a special signature field used to request a bootloader.

    @param[in]  value       The value to be written to teh signature field. Use 'CFG_BOOTSIGNATURE' to request bootloader.

    @return     None.
    @module     internal

*******************************************************************************************************************************************/
static void BOOT_SetSignature(UINT32 value)
{
    (*(UINT32*)CFG_BOOTSIGADDRESS) = value;                     /* Write the value at the signature address */
}

/***************************************************************************************************************************************//**

    Swithes execution to the bootloader application.

    @return     Does not return.
    @module     boot

*******************************************************************************************************************************************/
void BOOT_ExecuteBootloader(void)
{
    BOOT_SetSignature(CFG_BOOTSIGNATURE);                       /* Set the signature to request bootloader */
    MCU_Reset();                                                /* Perform reset and bootloader will catch on the signature */
}

/***************************************************************************************************************************************//**

    Swithes execution to the runtime application.

    @return     Does not return.
    @module     boot

*******************************************************************************************************************************************/
void BOOT_ExecuteRuntime(void)
{
    BOOT_SetSignature(0);                                       /* Clear any pre-existing signature */
    MCU_Reset();                                                /* Perform a reset */
}

/***************************************************************************************************************************************//**

    Returns an indication of whether the current boot signature is valid (matches CFG_BOOTSIGNATURE in sdk_cfg.h).

    @return     TRUE if the signature is valid; otherwise FALSE.
    @module     boot

*******************************************************************************************************************************************/
BOOLEAN BOOT_IsSignatureValid(void)
{
    if (BOOT_GetSignature() != CFG_BOOTSIGNATURE) {             /* Compare the signature value */
        return FALSE;
    }
    
    return TRUE;
}
