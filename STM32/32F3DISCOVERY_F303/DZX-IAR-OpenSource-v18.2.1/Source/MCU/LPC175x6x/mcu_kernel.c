/*******************************************************************************************************************************************

    DZX | LPC175x6x | KERNEL                                                                                              VERSION 18.2.1
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
#include "Kernel/kernel.h"
#include "mcu_kernel.h"
#include "mcu_cfg.h"
#include "mcu_irq.h"
#include "mcu_pin.h"
#include "mcu_scu.h"

/*******************************************************************************************************************************************
    PRIVATE VARIABLES
*******************************************************************************************************************************************/

/*******************************************************************************************************************************************
    PRIVATE FUNCTIONS
*******************************************************************************************************************************************/
static void MCU_InitClock(void);
static INLINE void MCU_FeedPLL(void);

/***************************************************************************************************************************************//**

    Called by the kernel immediately upon boot-up (before memory initialization).

    @return     None.
    @module     internal
    @remark     Not to be called directly from application code.

*******************************************************************************************************************************************/
void MCU_Boot(void)
{
    MCU_InitClock();                                            /* Initialize system clock */
}

/***************************************************************************************************************************************//**

    Returns the frequency, in hertz, of the core CPU clock.

    @return     None.
    @module     kernel-lpc175x6x

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
    REGBITS_SCS.OSCRANGE = 0;                       /* Set the oscillator range to 1-20MHz */
    REGBITS_SCS.OSCEN = 1;                          /* Enable the external crystal oscillator */

    while (REGBITS_SCS.OSCSTAT == 0);               /* Wait for the external oscillator to become valid */

    if (REGBITS_PLL0STAT.PLLC) {                    /* Check if the PLL is currently connected and should be disconnected */
        REGBITS_PLL0CON.PLLC = 0;                   /* Set command to disconnect the PLL */
        MCU_FeedPLL();                              /* Perform feed sequence to execute the previous disconnect command */
    }

    if (REGBITS_PLL0STAT.PLLE) {                    /* Check if the PLL is currently enabled and should be disabled */
        REGBITS_PLL0CON.PLLE = 0;                   /* Command the PLL to be disabled */
        MCU_FeedPLL();                              /* Perform feed sequence to execute the previous disable command */
    }

    REG_CLKSRCSEL = 0x01;                           /* Select the main oscillator for the system clock */

    REGBITS_PLL0CFG.MSEL = CFG_CLKPLL0MSEL;         /* Assign the configured multiplier and pre-divider values */
    REGBITS_PLL0CFG.NSEL = CFG_CLKPLL0NSEL;
    MCU_FeedPLL();

    REGBITS_PLL0CON.PLLE = 1;                       /* Enable the PLL */
    MCU_FeedPLL();

    while (REGBITS_PLL0STAT.PLOCK == 0);            /* Wait for the pll to lock */

    REG_CCLKCFG = CFG_CLKCCLKCFG;                   /* Set the system clock divisor */

    REGBITS_PLL0CON.PLLC = 1;                       /* Connect the PLL */
    MCU_FeedPLL();

    REGBITS_FLASHCFG.FLASHTIM = 0x4;                /* Set the flash accelerator */
}

/***************************************************************************************************************************************//**

    Performs a feed sequence on PLL 0 for setting up the CPU clock.

    @return     None
    @module     internal

*******************************************************************************************************************************************/
static INLINE void MCU_FeedPLL(void)
{
    REG_PLL0FEED = 0xAA;
    REG_PLL0FEED = 0x55;
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
    @module     kernel-lpc175x6x

*******************************************************************************************************************************************/
void MCU_Reset(void)
{
    REG_AIRCR = 0x05FA0004;                                     /* Issue a reset */
}
