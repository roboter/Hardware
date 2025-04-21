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
#ifndef MCU_WDT_H__
#define MCU_WDT_H__

#include "Kernel/kernel.h"

/*******************************************************************************************************************************************
    REGISTER DEFINITIONS
*******************************************************************************************************************************************/
typedef struct WDCLKSELBITFIELD {
    UINT32 WDSEL                    :2;
    UINT32                          :29;
    UINT32 WDLOCK                   :1;
} WDCLKSELBITFIELD;

typedef struct WDMODBITFIELD {
    UINT32 WDEN                     :1;
    UINT32 WDRESET                  :1;
    UINT32 WDTOF                    :1;
    UINT32 WDINT                    :1;
    UINT32                          :28;
} WDMODBITFIELD;

#define REG_WDCLKSEL                REG_32(0x40000010)
#define REGBITS_WDCLKSEL            REGBITS_32(0x40000010, WDCLKSELBITFIELD)
#define REG_WDFEED                  REG_32(0x40000008)
#define REG_WDMOD                   REG_32(0x40000000)
#define REGBITS_WDMOD               REGBITS_32(0x40000000, WDMODBITFIELD)
#define REG_WDTC                    REG_32(0x40000004)
#define REG_WDTV                    REG_32(0x4000000C)

/*******************************************************************************************************************************************
    PUBLIC FUNCTIONS
*******************************************************************************************************************************************/
/***************************************************************************************************************************************//**

    Initializes the watchdog timer for a specified timeout interval.

    @param[in]  ticks       The amount of time in ticks for the watchdog timer interval.

    @return     None.
    @module     wdt-lpc175x6x

*******************************************************************************************************************************************/
extern void WDT_Init(UINT32 ticks);

/***************************************************************************************************************************************//**

    Performs a feed sequence that prevents the watchdog timer from timing out.

    @return     None.
    @module     wdt-lpc175x6x

*******************************************************************************************************************************************/
extern void WDT_Feed(void);

#endif /* MCU_WDT_H__ */
