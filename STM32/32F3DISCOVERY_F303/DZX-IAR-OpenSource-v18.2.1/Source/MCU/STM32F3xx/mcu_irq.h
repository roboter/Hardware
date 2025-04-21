/*******************************************************************************************************************************************

    DZX | STM32F3xx | IRQ                                                                                                 VERSION 18.2.1
    ------------------------------------------------------------------------------------------------------------------------------------

    This is part of the MCU peripheral drivers and provides support for the MCU specific interrupts.

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
#ifndef MCU_IRQ_H__
#define MCU_IRQ_H__

#include "Kernel/kernel.h"

/*******************************************************************************************************************************************
    TYPE DEFINITIONS
*******************************************************************************************************************************************/
/***************************************************************************************************************************************//**

    Represents an individual interrupt source that is managed by the NVIC.
    @module     irq-stm32f3xx

*******************************************************************************************************************************************/
typedef enum STM32F3XX_IRQ {
	IRQ_WWDG = 0,               /**< Watchdog interrupt */
    IRQ_PVD,
    IRQ_TIMESTAMP,
    IRQ_RTCWAKEUP,
    IRQ_FLASH,
    IRQ_RCC,
    IRQ_EXTI0,
    IRQ_EXTI1,
    IRQ_EXTI2,
    IRQ_EXTI3,
    IRQ_EXTI4,
    IRQ_DMA1CH1,
    IRQ_DMA1CH2,
    IRQ_DMA1CH3,
    IRQ_DMA1CH4,
    IRQ_DMA1CH5,
    IRQ_DMA1CH6,
    IRQ_DMA1CH7,
    IRQ_ADC1_2,
    IRQ_CANTX,
    IRQ_CANRX0,
    IRQ_CANRX1,
    IRQ_CANSCE,
    IRQ_EXTI9_5,
    IRQ_TIM1BRK_TIM9,
    IRQ_TIM1UP_TIM16,
    IRQ_TIM1TRGCOM_TIM17,
    IRQ_TIM1CC,
    IRQ_TIM2,
    IRQ_TIM3,
    IRQ_TIM4,
    IRQ_I2C1EV_EXTI23,
    IRQ_I2C1ER,
    IRQ_I2C2EV_EXTI24,
    IRQ_I2C2ER,
    IRQ_SPI1,
    IRQ_SPI2,
    IRQ_USART1_EXTI25,
    IRQ_USART2_EXTI26,
    IRQ_USART3_EXTI28,
    IRQ_EXTI15_10,
    IRQ_RTCALARM,
    IRQ_USBWKUP,
    IRQ_TIM8BRK,
    IRQ_TIM8UP,
    IRQ_TIM8TRGCOM,
    IRQ_TIM8CC,
    IRQ_ADC3,
    IRQ_SPI3 = 51,
    IRQ_UART4_EXTI34,
    IRQ_UART5_EXTI35,
    IRQ_TIM6_DACUNDER,
    IRQ_DMA2CH1,
    IRQ_DMA2CH2,
    IRQ_DMA2CH3,
    IRQ_DMA2CH4,
    IRQ_DMA2CH5,
    IRQ_ADC4,
    IRQ_COMP123 = 64,
    IRQ_COMP456,
    IRQ_COMP7,
    IRQ_USBHP = 74,
    IRQ_USBLP,
    IRQ_USBWKUP2,
    IRQ_FPU = 81,
	IRQ_MAX,
} IRQ;

/***************************************************************************************************************************************//**

    An application-defined function that handles an interrupt request.

    @param[in]  irq         The interrupt request that has occurred.

    @return     None.
    @module     irq-stm32f3xx

*******************************************************************************************************************************************/
typedef void (*IRQHANDLER)(IRQ irq);

/*******************************************************************************************************************************************
    INTERNAL FUNCTIONS
*******************************************************************************************************************************************/
/***************************************************************************************************************************************//**

    Initializes interrupt handlers.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The interrupt handlers have been initialized.

    @remark     Not to be called directly from user code.
    @module     irq-stm32f3xx

*******************************************************************************************************************************************/
extern STATUS IRQ_Initialize(void);


/*******************************************************************************************************************************************
    PUBLIC FUNCTIONS
*******************************************************************************************************************************************/
/***************************************************************************************************************************************//**

    Registers an application-defined handler for an interrupt request.

    @param[in]  irq         The target interrupt request to be handled.
    @param[in]  handler     The application-defined function to be called to handle the request.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The handler was registered.

    @module     irq-stm32f3xx

*******************************************************************************************************************************************/
extern STATUS IRQ_RegisterHandler(IRQ irq, IRQHANDLER handler);

/***************************************************************************************************************************************//**

    Enables an interrupt within the nested vectored interrupt controller (NVIC).

    @param[in]  irq         The interrupt to be enabled.

    @return     None.
    @module     irq-stm32f3xx

*******************************************************************************************************************************************/
extern void IRQ_Enable(IRQ irq);

/***************************************************************************************************************************************//**

    Disables an interrupt within the nested vectored interrupt controller (NVIC).

    @param[in]  irq         The interrupt source to be disabled.

    @return     None.
    @module     irq-stm32f3xx

*******************************************************************************************************************************************/
extern void IRQ_Disable(IRQ irq);

/***************************************************************************************************************************************//**

    Returns an indication of whether an interrupt is currently enabled.

    @param[in]  irq         The interrupt source to be checked.

    @return     TRUE if the specified interrupt is enabled; otherwise FALSE.
    @module     irq-stm32f3xx

*******************************************************************************************************************************************/
extern BOOLEAN IRQ_IsEnabled(IRQ irq);

/***************************************************************************************************************************************//**

    Returns the priority for an interrupt within the NVIC.

    @param[in]  irq         The target interrupt source.

    @return     The current priority for the given interrupt source.
    @module     irq-stm32f3xx

*******************************************************************************************************************************************/
extern BYTE IRQ_Priority(IRQ irq);

/***************************************************************************************************************************************//**

    Sets the priority for an interrupt within the NVIC.

    @param[in]  irq         The target interrupt source to receive the new priority value.
    @param[in]  priority    The new priority for the specified interrupt. Value should be between 0 and 31. A lower value indicates a 
                            higher priority.

    @return     None
    @module     irq-stm32f3xx

*******************************************************************************************************************************************/
extern void IRQ_SetPriority(IRQ irq, BYTE priority);

#if (CFG_HOOKUNHANDLEDIRQ)
/***************************************************************************************************************************************//**

    An application-defined hook function that is called when an unhandled interrupt occurs.

    @param[in]  irq         The interrupt that has occurred and is unhandled.

    @return     None.
    @module     irq-stm32f3xx

*******************************************************************************************************************************************/
extern void HOOK_UnhandledIRQ(IRQ irq);
#endif

#endif /* MCU_IRQ_H__ */
