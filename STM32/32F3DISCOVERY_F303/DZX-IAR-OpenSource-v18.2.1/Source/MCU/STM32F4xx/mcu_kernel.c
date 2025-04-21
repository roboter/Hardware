/*******************************************************************************************************************************************

    DZX | STM32F4xx | KERNEL                                                                                              VERSION 18.2.1
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
#include "mcu_cfg.h"
#include "mcu_pin.h"
#include "mcu_rcc.h"
#include "mcu_pwr.h"
#include "mcu_irq.h"
#include "mcu_flash.h"

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
    
    REGBITS_RCCAHB1ENR.GPIOAEN = 1;                             /* Enable GPIO clocks */
    REGBITS_RCCAHB1ENR.GPIOBEN = 1;
    REGBITS_RCCAHB1ENR.GPIOCEN = 1;
    REGBITS_RCCAHB1ENR.GPIODEN = 1;
    REGBITS_RCCAHB1ENR.GPIOEEN = 1;
    REGBITS_RCCAHB1ENR.GPIOHEN = 1;
}

/***************************************************************************************************************************************//**

    Returns the frequency, in hertz, of the core CPU clock.

    @return     None.
    @module     kernel-stm32f4xx

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
    REGBITS_RCCCR.HSION = 1;                        /* Turn on the internal oscillator */
    REG_RCCCFGR = 0;                                /* Reset clock configuration */
    
    REGBITS_RCCCR.HSEON = 0;                        /* Turn off high speed external oscillator */
    REGBITS_RCCCR.CSSON = 0;                        /* Turn off clock security system */
    REGBITS_RCCCR.PLLON = 0;                        /* Turn off PLL */
    REGBITS_RCCCR.HSEBYP = 0;                       /* Turn off high speed external oscillator bypass */
    
    REG_RCCPLLCFGR = 0x24003010;                    /* Reset PLL configuration register to default value */
    REG_RCCCIR = 0x00000000;                        /* Disable all interrupts */
    
    REGBITS_RCCCR.HSEON = 1;                        /* Enable the HSE oscillator */
    while (REGBITS_RCCCR.HSERDY == 0);              /* Wait for the oscillator ready */
    
    REGBITS_RCCAPB1ENR.PWREN = 1;
    REGBITS_PWRCR.VOS = 1;
    
    REGBITS_RCCCFGR.HPRE = CFG_HPRE;                /* Assign AHB prescalar */
    REGBITS_RCCCFGR.PPRE1 = CFG_PRE1;               /* Assign APB1 (low speed) prescalar */
    REGBITS_RCCCFGR.PPRE2 = CFG_PRE2;               /* Assign APB2 (high speed) prescalar */
    
    REGBITS_RCCPLLCFGR.PLLM = CFG_PLLM;             /* Assign PLL factors */
    REGBITS_RCCPLLCFGR.PLLN = CFG_PLLN;
    REGBITS_RCCPLLCFGR.PLLP = CFG_PLLP;
    REGBITS_RCCPLLCFGR.PLLQ = CFG_PLLQ;
    
    REGBITS_RCCPLLCFGR.PLLSRC = 1;                  /* Select external oscillator as PLL source */
    
    REGBITS_RCCCR.PLLON = 1;                        /* Turn ON the PLL */
    while (REGBITS_RCCCR.PLLRDY == 0);              /* Wait for the PLL to lock */
    
    REGBITS_FLASHACR.LATENCY = CFG_FLASHLATENCY;    /* Configure flash cache and latency */
    REGBITS_FLASHACR.PRFTEN = 1;
    REGBITS_FLASHACR.ICEN = 1;
    REGBITS_FLASHACR.DCEN = 1;
    
    REGBITS_RCCCFGR.SW = 2;                         /* Select PLL as source clock */
    while (REGBITS_RCCCFGR.SWS != 2);               /* Wait for the PLL to become the source */
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
    IRQ_Initialize();                                           /* Initialize interrupt handlers */
    return SUCCESS;
}

/***************************************************************************************************************************************//**

    Requests a full-system reset of the MCU.

    @return     Does not return as the system is reset.
    @module     kernel-stm32f4xx

*******************************************************************************************************************************************/
void MCU_Reset(void)
{
    /* Not supported */
}
