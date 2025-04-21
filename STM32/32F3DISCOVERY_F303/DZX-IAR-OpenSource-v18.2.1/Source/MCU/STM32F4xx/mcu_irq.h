/*******************************************************************************************************************************************

    DZX | STM32F4xx | IRQ                                                                                                 VERSION 18.2.1
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
typedef enum STM32F411_IRQ IRQ;

/***************************************************************************************************************************************//**

    Represents an individual interrupt source that is managed by the NVIC.
    @module     irq-stm32f4xx

*******************************************************************************************************************************************/
enum STM32F411_IRQ {
	IRQ_WWDG = 0,               /**< Watchdog interrupt */
	IRQ_EXTI16,                 /**< EXTI Line 16 / PVD through EXTI line interrupt */
	IRQ_EXTI21,                 /**< EXTI Line 21 / Tamper and TimeStamp through EXTI line interrupt */
	IRQ_EXTI22,                 /**< EXTI Line 22 / RTC Wakeup through EXTI line interrupt */
	IRQ_FLASH,                  /**< Flash global interrupt */
	IRQ_RCC,                    /**< RCC global interrupt */
	IRQ_EXTI0,                  /**< EXTI Line 0 interrupt */
    IRQ_EXTI1,                  /**< EXTI Line 1 interrupt */
    IRQ_EXTI2,                  /**< EXTI Line 2 interrupt */
    IRQ_EXTI3,                  /**< EXTI Line 3 interrupt */
    IRQ_EXTI4,                  /**< EXTI Line 4 interrupt */
    IRQ_DMA1_STREAM0,           /**< DMA1 Stream 0 global interrupt */
    IRQ_DMA1_STREAM1,           /**< DMA1 Stream 1 global interrupt */
    IRQ_DMA1_STREAM2,           /**< DMA1 Stream 2 global interrupt */
    IRQ_DMA1_STREAM3,           /**< DMA1 Stream 3 global interrupt */
    IRQ_DMA1_STREAM4,           /**< DMA1 Stream 4 global interrupt */
    
    IRQ_DMA1_STREAM5,           /**< DMA1 Stream 5 global interrupt */
    IRQ_DMA1_STREAM6,           /**< DMA1 Stream 6 global interrupt */
    IRQ_ADC,                    /**< ADC1 global interrupts */
    IRQ_CAN1_TX,                /**< CAN1 TX interrupt */
    IRQ_CAN1_RX0,               /**< CAN1 RX0 interrupt */
    IRQ_CAN1_RX1,               /**< CAN1 RX1 interrupt */
    IRQ_CAN1_SCE,               /**< CAN1 SCE interrupt */
    IRQ_EXTI9_5,                /**< EXTI Line [9:5] interrupts */
    IRQ_TIM1_BRK_TIM9,          /**< TIM1 Break interrupt and TIM9 global interrupt */
    IRQ_TIM1_UP_TIM10,          /**< TIM1 Update interrupt and TIM10 global interrupt */
	IRQ_TIM1_TRG_COM_TIM11,     /**< TIM1 Trigger and Commutation interrupts and TIM11 global interrupt */
    IRQ_TIM1_CC,                /**< TIM1 Capture Compare interrupt */
    IRQ_TIM2,                   /**< TIM2 global interrupt */
    IRQ_TIM3,                   /**< TIM3 global interrupt */
    IRQ_TIM4,                   /**< TIM4 global interrupt */
    IRQ_I2C1_EV,                /**< I2C1 event interrupt */
    
    IRQ_I2C1_ER,                /**< I2C1 error interrupt */
    IRQ_I2C2_EV,                /**< I2C2 event interrupt */
    IRQ_I2C2_ER,                /**< I2C2 error interrupt */
    IRQ_SPI1,                   /**< SPI1 global interrupt */
    IRQ_SPI2,                   /**< SPI2 global interrupt */
    IRQ_USART1,                 /**< USART1 global interrupt */
    IRQ_USART2,                 /**< USART2 global interrupt */
    IRQ_USART3,                 /**< USART3 global interrupt */
    IRQ_EXTI15_10,              /**< EXTI Line[15:10] interrupts */
    IRQ_EXTI18,                 /**< EXTI Line 18 interrupt and USB OTG FS Wakeup through EXTI line interrupt */
    IRQ_DMA1_STREAM7,           /**< DMA1 Stream 7 global interrupt */
    IRQ_SDIO,                   /**< SDIO global interrupt */
    IRQ_TIM5,                   /**< TIM5 global interrupt */
    IRQ_SPI3,                   /**< SPI3 global interrupt */
    IRQ_DMA2_STREAM0,           /**< DMA2 Stream 0 global interrupt */
    IRQ_DMA2_STREAM1,           /**< DMA2 Stream 1 global interrupt */
    IRQ_DMA2_STREAM2,           /**< DMA2 Stream 2 global interrupt */
    IRQ_DMA2_STREAM3,           /**< DMA2 Stream 3 global interrupt */
    IRQ_DMA2_STREAM4,           /**< DMA2 Stream 4 global interrupt */
    IRQ_ETHERNET,
    IRQ_ETHERNET_WAKEUP,
    IRQ_CAN2_TX,
    
    IRQ_CAN2_RX0,
    IRQ_CAN2_RX1,
    IRQ_CAN2_SCE,
    IRQ_OTG_FS,                 /**< USB on-the-go FS global interrupt */
    IRQ_DMA2_STREAM5,           /**< DMA2 Stream 5 global interrupt */
    IRQ_DMA2_STREAM6,           /**< DMA2 Stream 6 global interrupt */
    IRQ_DMA2_STREAM7,           /**< DMA2 Stream 7 global interrupt */
    IRQ_USART6,                 /**< USART6 global interrupt */
    IRQ_I2C3_EV,                /**< I2C3 event interrupt */
    IRQ_I2C3_ER,                /**< I2C3 error interrupt */
    
    IRQ_OTG_HS_EP1_OUT,
    IRQ_OTG_HS_EP1_IN,
    IRQ_OTG_HS_WAKEUP,
    IRQ_OTG_HS,
    IRQ_DCMI,
    IRQ_CRYP,
    IRQ_HASH_RNG,
    IRQ_FPU,                    /**< FPU global interrupt */
    IRQ_UART7,                  /**< UART 7 interrupt */
    IRQ_UART8,                  /**< UART 8 interrupt */
    IRQ_SPI4,                   /**< SPI 4 global interrupt */
    IRQ_SPI5,                   /**< SPI 5 global interrupt */
    IRQ_SPI6,                   /**< SPI 6 global interrupt */
    IRQ_SAI1,                   /**< SAI 1 global interrupt */
    IRQ_LTDC,
    IRQ_LTDC_ERROR,
    IRQ_DMA2D,
    
	IRQ_MAX,
};

/***************************************************************************************************************************************//**

    An application-defined function that handles an interrupt request.

    @param[in]  irq         The interrupt request that has occurred.

    @return     None.
    @module     irq-stm32f4xx

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
    @module     irq-stm32f4xx

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

    @module     irq-stm32f4xx

*******************************************************************************************************************************************/
extern STATUS IRQ_RegisterHandler(IRQ irq, IRQHANDLER handler);

/***************************************************************************************************************************************//**

    Enables an interrupt within the nested vectored interrupt controller (NVIC).

    @param[in]  irq         The interrupt to be enabled.

    @return     None.
    @module     irq-stm32f4xx

*******************************************************************************************************************************************/
extern void IRQ_Enable(IRQ irq);

/***************************************************************************************************************************************//**

    Disables an interrupt within the nested vectored interrupt controller (NVIC).

    @param[in]  irq         The interrupt source to be disabled.

    @return     None.
    @module     irq-stm32f4xx

*******************************************************************************************************************************************/
extern void IRQ_Disable(IRQ irq);

/***************************************************************************************************************************************//**

    Returns an indication of whether an interrupt is currently enabled.

    @param[in]  irq         The interrupt source to be checked.

    @return     TRUE if the specified interrupt is enabled; otherwise FALSE.
    @module     irq-stm32f4xx

*******************************************************************************************************************************************/
extern BOOLEAN IRQ_IsEnabled(IRQ irq);

/***************************************************************************************************************************************//**

    Returns the priority for an interrupt within the NVIC.

    @param[in]  irq         The target interrupt source.

    @return     The current priority for the given interrupt source.
    @module     irq-stm32f4xx

*******************************************************************************************************************************************/
extern BYTE IRQ_Priority(IRQ irq);

/***************************************************************************************************************************************//**

    Sets the priority for an interrupt within the NVIC.

    @param[in]  irq         The target interrupt source to receive the new priority value.
    @param[in]  priority    The new priority for the specified interrupt. Value should be between 0 and 31. A lower value indicates a 
                            higher priority.

    @return     None
    @module     irq-stm32f4xx

*******************************************************************************************************************************************/
extern void IRQ_SetPriority(IRQ irq, BYTE priority);

#if (CFG_HOOKUNHANDLEDIRQ)
/***************************************************************************************************************************************//**

    An application-defined hook function that is called when an unhandled interrupt occurs.

    @param[in]  irq         The interrupt that has occurred and is unhandled.

    @return     None.
    @module     irq-stm32f4xx

*******************************************************************************************************************************************/
extern void HOOK_UnhandledIRQ(IRQ irq);
#endif

#endif /* MCU_IRQ_H__ */
