/*******************************************************************************************************************************************

    DZX | BOOTLOADER | BOOT RUNTIME                                                                                       VERSION 18.2.1
    ------------------------------------------------------------------------------------------------------------------------------------

    This provides support for creating a runtime application that can request a bootloader to execute via a shared RAM key. Use  header 
    file 'boot_cfg.h' for configuration settings.

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
#ifndef BOOT_RUNTIME_H__
#define BOOT_RUNTIME_H__

#include "Kernel/kernel.h"
#include "boot_cfg.h"

/*******************************************************************************************************************************************
    PUBLIC FUNCTIONS
*******************************************************************************************************************************************/
/***************************************************************************************************************************************//**

    Swithes execution to the bootloader application.

    @return     Does not return.
    @module     boot-runtime

*******************************************************************************************************************************************/
extern void BOOT_ExecuteBootloader(void);

#endif
