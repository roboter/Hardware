/*******************************************************************************************************************************************

    DZX | LPC175x6x | WDT                                                                                                 VERSION 18.2.1
    ------------------------------------------------------------------------------------------------------------------------------------

    This is part of the MCU peripheral drivers and provides support for the watch-dog timer (WDT).

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
#include "mcu_wdt.h"

/***************************************************************************************************************************************//**

    Initializes the watchdog timer for a specified timeout interval.

    @param[in]  ticks       The amount of time in ticks for the watchdog timer interval.

    @return     None.
    @module     wdt-lpc175x6x

*******************************************************************************************************************************************/
void WDT_Init(UINT32 ticks)
{
    REG_WDTC = ticks;       /* Assign the timeout value */
    REG_WDMOD = 0x3;        /* Enable and configure for reset upon timeout */

    WDT_Feed();             /* Accept the changes */
}

/***************************************************************************************************************************************//**

    Performs a feed sequence that prevents the watchdog timer from timing out.

    @return     None.
    @module     wdt-lpc175x6x

*******************************************************************************************************************************************/
INLINE void WDT_Feed(void)
{
    REG_WDFEED = 0xAA;
    REG_WDFEED = 0x55;
}
