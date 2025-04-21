/*******************************************************************************************************************************************

    DZX | LPC15xx | KERNEL                                                                                                VERSION 18.2.1
    ------------------------------------------------------------------------------------------------------------------------------------

    This is part of the MCU peripheral drivers and provides the support that is required by the real-time kernel. This configures
    the system clock and performs any required intialization for the peripheral drivers.

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
#ifndef MCU_KERNEL_H__
#define MCU_KERNEL_H__

#include "Kernel/kernel_types.h"

/*******************************************************************************************************************************************
    PUBLIC FUNCTIONS
*******************************************************************************************************************************************/
/***************************************************************************************************************************************//**

    Resets the MCU.

    @return     None.
    @module     kernel-lpc15xx

*******************************************************************************************************************************************/
extern void MCU_Reset(void);

/***************************************************************************************************************************************//**

    Returns the frequency, in hertz, of the core CPU clock.

    @return     None.
    @module     kernel-lpc15xx

*******************************************************************************************************************************************/
extern UINT32 MCU_ClockHz(void);

#endif /* MCU_KERNEL_H__ */
