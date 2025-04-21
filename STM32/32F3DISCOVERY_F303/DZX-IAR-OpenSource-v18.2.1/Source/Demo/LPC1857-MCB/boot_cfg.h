/*******************************************************************************************************************************************

    DZX | BOOTLOADER | CONFIGURATION                                                                                      VERSION 18.2.1
    ------------------------------------------------------------------------------------------------------------------------------------

    This provides configuration settings for the bootloader and is used by both boot.c/.h and boot_runtime.c/.h.

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
#ifndef BOOT_CFG_H__
#define BOOT_CFG_H__

/*******************************************************************************************************************************************

    RUNTIME ADDRESS                 The starting address of the runtime application.

*******************************************************************************************************************************************/
#define CFG_RUNTIMEADDRESS          0x1A008000

/*******************************************************************************************************************************************

    SIGNATURE ADDRESS               The address of a signature used to request the bootloader to execute.

*******************************************************************************************************************************************/
#define CFG_BOOTSIGADDRESS          0x10007E00

/*******************************************************************************************************************************************

    SIGNATURE VALUE                 The signature value that indicates the bootloader should execute.

*******************************************************************************************************************************************/
#define CFG_BOOTSIGNATURE           0xAA55BB55

#endif
