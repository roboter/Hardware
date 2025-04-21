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
#include "mcu_kernel.h"
#include "mcu_cfg.h"
#include "mcu_irq.h"
#include "mcu_syscon.h"

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
    @module     internal
    @remark     Not to be called directly from application code.

*******************************************************************************************************************************************/
void MCU_Boot(void)
{
    MCU_InitClock();                                            /* Initialize the system clock */
    
    REGBITS_SYSAHBCLKCTRL0.GPIO0 = 1;
    REGBITS_SYSAHBCLKCTRL0.GPIO1 = 1;
    REGBITS_SYSAHBCLKCTRL0.GPIO2 = 1;
    REGBITS_SYSAHBCLKCTRL0.PMUX = 1;
    REGBITS_SYSAHBCLKCTRL0.SWM = 1;
    REGBITS_SYSAHBCLKCTRL0.IOCON = 1;
}

/***************************************************************************************************************************************//**

    Returns the frequency, in hertz, of the core CPU clock.

    @return     None.
    @module     kernel-lpc15xx

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
    volatile UINT32 dly;
    
    
    REG_MAINCLKSELB = 0;                                        /* Select oscillator as main clock */ 
    
    REGBITS_SYSOSCCTRL.FREQRANGE = 0;                           /* Select the 1-20 MHz oscillator range */

    REGBITS_PDRUNCFG.SYSOSC_PD = 0;                             /* Power up the oscillator */
    for (dly = 0; dly < 200; dly++);
    
    REG_SYSPLLCLKSEL = 1;                                       /* Select the oscillator as the system PLL source */
    
    REGBITS_PDRUNCFG.SYSPLL_PD = 1;                             /* Power down system PLL before configuring */
    
    REGBITS_SYSPLLCTRL.MSEL = CFG_SYSPLLMSEL;                   /* Configure dividers */
    REGBITS_SYSPLLCTRL.PSEL = CFG_SYSPLLPSEL;
    
    REGBITS_PDRUNCFG.SYSPLL_PD = 0;                             /* Power up the PLL */
    while (REGBITS_SYSPLLSTAT.LOCK == 0);                       /* Wait for the PLL to lock */
  
    REG_SYSAHBCLKDIV = 1;                                       /* Set system clock divider */
    REGBITS_FLASHCFG.FLASHTIM = CFG_FLASHTIM;                   /* Set the flash access time */
    
    REG_MAINCLKSELB = 2;                                        /* Select the PLL as main clock source */
}

/***************************************************************************************************************************************//**

    Called by the kernel upon initialization and performs initialization of the on-chip peripheral drivers.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The MCU was successfully initialized.

    @module     internal
    @remark     Not to be called directly from application code.

*******************************************************************************************************************************************/
STATUS MCU_Initialize(void)
{
    IRQ_Initialize();                                           /* Initialize interrupt handlers */
    return SUCCESS;
}

/***************************************************************************************************************************************//**

    Resets the MCU.

    @return     None.
    @module     kernel-lpc15xx

*******************************************************************************************************************************************/
void MCU_Reset(void)
{
    REG_AIRCR = 0x05FA0004;                                     /* Issue a reset */
}
