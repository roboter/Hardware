/*******************************************************************************************************************************************

    DZX | STM32F3xx | RCC                                                                                                 VERSION 18.2.1
    ------------------------------------------------------------------------------------------------------------------------------------

    This is part of the MCU peripheral drivers and provides support for reset and clock control.

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
#include "mcu_rcc.h"
#include "mcu_kernel.h"

UINT32 MCU_AHBClockHz(void)
{
    if (REGBITS_RCCCFGR.HPRE < 8) {
        return MCU_ClockHz();                                   /* Divider is 1 */
    }
    
    return MCU_ClockHz() / (1UL << (REGBITS_RCCCFGR.HPRE - 7));
}

UINT32 MCU_APB1ClockHz(void)
{
    if (REGBITS_RCCCFGR.PPRE1 < 4) {
        return MCU_AHBClockHz();
    }
    
    return MCU_AHBClockHz() / (1UL << (REGBITS_RCCCFGR.PPRE1 - 3));
}

UINT32 MCU_APB2ClockHz(void)
{
    if (REGBITS_RCCCFGR.PPRE2 < 4) {
        return MCU_AHBClockHz();
    }
    
    return MCU_AHBClockHz() / (1UL << (REGBITS_RCCCFGR.PPRE2 - 3));
}
