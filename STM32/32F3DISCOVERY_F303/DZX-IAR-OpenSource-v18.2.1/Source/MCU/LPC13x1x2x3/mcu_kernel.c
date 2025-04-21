/*******************************************************************************************************************************************

    DZX | LPC13x1x2x3 | KERNEL                                                                                            VERSION 18.2.1
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
#include "Kernel/kernel.h"
#include "mcu_kernel.h"
#include "mcu_cfg.h"
#include "mcu_irq.h"
#include "mcu_pin.h"

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
    MCU_InitClock();                                            /* Initialize system clock */
    
    REGBITS_SYSAHBCLKCTRL.IOCON = 1;
}

/***************************************************************************************************************************************//**

    Returns the frequency, in hertz, of the core CPU clock.

    @return     None.
    @module     kernel-lpc13x1x2x3

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
    REG_SYSOSCCTRL = 0;                                         /* External oscillator range */
    
    REGBITS_PDRUNCFG.IRCPD = 0;                                 /* Power up internal oscillator */
    REGBITS_PDRUNCFG.SYSOSCPD = 0;                              /* Power up external oscillator */
    
    REG_MAINCLKUEN = 0;                                         /* Select the internal oscillator for clock source */
    REG_MAINCLKSEL = 0;
    REG_MAINCLKSEL = 1;
    
    REG_SYSPLLCLKUEN = 0;
    REG_SYSPLLCLKSEL = 1;                                       /* Select the external oscillator as source for PLL */
    REG_SYSPLLCLKUEN = 1;
    
    REGBITS_SYSPLLCTRL.MSEL = CFG_SYSPLLMSEL;                   /* Assign PLL multiplier and divider */
    REGBITS_SYSPLLCTRL.PSEL = CFG_SYSPLLPSEL;
    
    REGBITS_PDRUNCFG.SYSPLLPD = 0;                              /* Power up the PLL */
    
    while (REGBITS_SYSPLLSTAT.LOCK == 0);                       /* Wait for the PLL to lock */
    
    REG_MAINCLKUEN = 0;                                         /* Select the PLL as the main clock source */
    REG_MAINCLKSEL = 3;
    REG_MAINCLKUEN = 1;
}

/***************************************************************************************************************************************//**

    Performs initialization of the MCU peripheral drivers.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The MCU was successfully initialized.

    @module     internal
    @remark     Not to be called directly from application code.

*******************************************************************************************************************************************/
STATUS MCU_Initialize(void)
{
    STATUS status;
    
    
    status = IRQ_Initialize();
    if (status != SUCCESS) {
        return status;
    }
    
    return SUCCESS;
}

/***************************************************************************************************************************************//**

    Requests a full-system reset of the MCU.

    @return     Does not return as the system is reset.
    @module     kernel-lpc13x1x2x3

*******************************************************************************************************************************************/
void MCU_Reset(void)
{
    REG_AIRCR = 0x05FA0004;                                     /* Issue a reset */
}
