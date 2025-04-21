/*******************************************************************************************************************************************

    DZX | STM32F3xx | KERNEL                                                                                              VERSION 18.2.1
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
    
    REGBITS_RCCAHBENR.IOPAEN = 1;                               /* Enable the GPIO clocks */
    REGBITS_RCCAHBENR.IOPBEN = 1;
    REGBITS_RCCAHBENR.IOPCEN = 1;
    REGBITS_RCCAHBENR.IOPDEN = 1;
    REGBITS_RCCAHBENR.IOPEEN = 1;
    REGBITS_RCCAHBENR.IOPFEN = 1;
}

/***************************************************************************************************************************************//**

    Returns the frequency, in hertz, of the core CPU clock.

    @return     None.
    @module     kernel-stm32f3xx

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


//DEEPSEEK
void MCU_InitClock(void)
{
    /* 1. Define registers using your architecture */
    #define RCC_CR        REG_32(0x40021000)
    #define RCC_CFGR      REG_32(0x40021004)
    #define RCC_APB1ENR   REG_32(0x4002101C)
    #define FLASH_ACR     REG_32(0x40022000)
    #define RCC_APB2ENR   REG_32(0x40021018)
    
    /* 2. Bit definitions matching HAL configuration */
    #define RCC_CR_HSEON     (1 << 16)
    #define RCC_CR_HSEBYP    (1 << 18)
    #define RCC_CR_HSERDY    (1 << 17)
    #define RCC_CR_HSION     (1 << 0)
    #define RCC_CR_HSIRDY    (1 << 1)
    #define RCC_CR_PLLON     (1 << 24)
    #define RCC_CR_PLLRDY    (1 << 25)
    
    /* PLL configuration (matches RCC_PLL_MUL6) */
    #define PLL_MUL_6        (0x4 << 18)  /* 6x multiplier */
    #define PLL_SRC_HSE      (1 << 16)
    
    /* Clock control */
    #define SW_PLL           (0x2 << 0)
    #define SWS_PLL          (0x2 << 2)
    
    /* 3. Enable HSE in bypass mode (8MHz from ST-LINK) */
    RCC_CR |= RCC_CR_HSEBYP;  /* Bypass oscillator */
    RCC_CR |= RCC_CR_HSEON;   /* Enable HSE */
    volatile uint32_t timeout = 1000000;
    while ((RCC_CR & RCC_CR_HSERDY) == 0 && timeout--);
    
    /* 4. Configure PLL (HSE 8MHz * 6 = 48MHz) */
    RCC_CFGR &= ~(0xF << 18);  /* Clear PLLMUL */
    RCC_CFGR |= PLL_MUL_6;     /* 6x multiplier */
    RCC_CFGR |= PLL_SRC_HSE;   /* HSE as PLL source */
    
    /* 5. Enable PLL */
    RCC_CR |= RCC_CR_PLLON;
    timeout = 1000000;
    while ((RCC_CR & RCC_CR_PLLRDY) == 0 && timeout--);
    
    /* 6. Configure Flash (1 wait state for 48MHz) */
    FLASH_ACR &= ~(0x7 << 0);  /* Clear latency */
    FLASH_ACR |= (1 << 0);     /* LATENCY_1 */
    FLASH_ACR |= (1 << 4);     /* PRFTBE */
    
    /* 7. Configure clock dividers */
    RCC_CFGR &= ~(0xF << 4);   /* AHB = SYSCLK/1 */
    RCC_CFGR |= (0x4 << 8);    /* APB1 = HCLK/2 (24MHz) */
    RCC_CFGR &= ~(0x7 << 11);  /* APB2 = HCLK/1 (48MHz) */
    
    /* 8. Switch to PLL */
    RCC_CFGR &= ~(0x3 << 0);   /* Clear SW */
    RCC_CFGR |= SW_PLL;        /* Select PLL */
    while ((RCC_CFGR & (0x3 << 2)) != SWS_PLL); /* Wait for switch */
    
    /* 9. USB Clock (48MHz from PLL) - Requires PLL multiplier of 6/8/12 */
    /* No additional config needed as PLL is already configured for 48MHz */
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
    @module     kernel-stm32f3xx

*******************************************************************************************************************************************/
void MCU_Reset(void)
{
    /* Not supported */
}
