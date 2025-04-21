/*******************************************************************************************************************************************

    DZX | LPC18xx | KERNEL                                                                                                VERSION 18.2.1
    ------------------------------------------------------------------------------------------------------------------------------------

    This is part of the MCU peripheral drivers and provides the support that is required by the real-time kernel. This configures
    the system clock and performs any required initialization for the peripheral drivers.

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
#include "mcu_kernel.h"
#include "mcu_irq.h"
#include "mcu_cfg.h"
#include "mcu_pin.h"
#include "mcu_cgu.h"
#include "mcu_creg.h"
#include "mcu_scu.h"

/*******************************************************************************************************************************************
    PRIVATE VARIABLES
*******************************************************************************************************************************************/

/*******************************************************************************************************************************************
    PRIVATE FUNCTIONS
*******************************************************************************************************************************************/
static void MCU_InitClock(void);

/***************************************************************************************************************************************//**

    Called by the kernel immediately upon boot-up (before memory initialization).

    @return     None.
    @remark     Not to be called directly from application code.
    @module     kernel-lpc18xx
    
*******************************************************************************************************************************************/
void MCU_Boot(void)
{
    MCU_InitClock();                                            /* Initialize the system clock */
    
    REG_SFSCLK0 = 0xF0;
    REG_SFSCLK1 = 0xF0;
    REG_SFSCLK2 = 0xF0;
    REG_SFSCLK3 = 0xF0;
}

/***************************************************************************************************************************************//**

    Returns the frequency, in hertz, of the core CPU clock.

    @return     None.
    @module     kernel-lpc18xx

*******************************************************************************************************************************************/
UINT32 MCU_ClockHz(void)
{
    return CFG_CPUCLOCKHZ;
}

/*******************************************************************************************************************************************

    Initializes the core CPU clock using PLL 0.

    @return     None.
    @remark     Not to be called from user code.
    @module     internal

*******************************************************************************************************************************************/
static void MCU_InitClock(void)
{
    volatile UINT32 k;
    
    
    REGBITS_CGUBASEM3CLK.CLKSEL = 0xE;
    REGBITS_CGUBASEAPB1CLK.CLKSEL = 0xE;
    REGBITS_CGUBASEAPB3CLK.CLKSEL = 0xE;

    REGBITS_CGUXTALOSCCTRL.HF = 0;                              /* Select 1 to 20Mhz oscillator range */
    REGBITS_CGUXTALOSCCTRL.BYPASS = 0;                          /* Disable bypass */
    REGBITS_CGUXTALOSCCTRL.ENABLE = 0;                          /* Enable the oscillator */
    
    for (k = 0; k < 12000; k++);                                /* Wait for the oscillator to stabilize (100uS user manual) */
    
    REGBITS_CGUBASEM3CLK.AUTOBLOCK = 1;
    REGBITS_CGUBASEM3CLK.CLKSEL = 6;
    REGBITS_CGUBASEAPB1CLK.AUTOBLOCK = 1;
    REGBITS_CGUBASEAPB1CLK.CLKSEL = 6;
    REGBITS_CGUBASEAPB3CLK.AUTOBLOCK = 1;
    REGBITS_CGUBASEAPB3CLK.CLKSEL = 6;
    
    REGBITS_CGUPLL1CTRL.PD = 1;                                 /* Power down the PLL */
    
    REGBITS_CGUPLL1CTRL.AUTOBLOCK = 1;
    REGBITS_CGUPLL1CTRL.CLKSEL = 6;
    REGBITS_CGUPLL1CTRL.DIRECT = CFG_PLL1DIRECT;
    
    REGBITS_CGUPLL1CTRL.MSEL = CFG_PLL1MSEL;
    REGBITS_CGUPLL1CTRL.NSEL = CFG_PLL1NSEL;
    REGBITS_CGUPLL1CTRL.PSEL = CFG_PLL1PSEL;
    
    REGBITS_CGUPLL1CTRL.BYPASS = 0;
    REGBITS_CGUPLL1CTRL.PD = 0;
    
    while (REGBITS_CGUPLL1STAT.LOCK == 0);
    
    REGBITS_CGUBASEM3CLK.CLKSEL = 9;
    REGBITS_CGUBASEAPB1CLK.CLKSEL = 9;
    REGBITS_CGUBASEAPB3CLK.CLKSEL = 9;
    
    
    REGBITS_FLASHCFGA.FLASHTIM = 0x8;
    REGBITS_FLASHCFGB.FLASHTIM = 0x8;
}

/***************************************************************************************************************************************//**

    Called by the kernel upon initialization and performs initialization of the MCU peripheral drivers.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The MCU was successfully initialized.

    @remark     Not to be called directly from application code.
    @module     kernel-lpc18xx

*******************************************************************************************************************************************/
STATUS MCU_Initialize(void)
{
    IRQ_Initialize();                                           /* Initialize interrupt handlers */
    return SUCCESS;
}

/***************************************************************************************************************************************//**

    Resets the MCU.

    @return     None.
    @module     kernel-lpc18xx

*******************************************************************************************************************************************/
void MCU_Reset(void)
{
    REG_AIRCR = 0x05FA0004;                                     /* Issue a reset */
}
