/*******************************************************************************************************************************************

    DZX | LPC175x6x | IRQ                                                                                                 VERSION 18.2.1
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
typedef enum LPC175X6X_IRQ IRQ;

/***************************************************************************************************************************************//**

    Represents an individual interrupt source that is managed by the NVIC.
    @module     irq-lpc175x6x

*******************************************************************************************************************************************/
enum LPC175X6X_IRQ {
	IRQ_WDT = 0,    /**< Watchdog interrupt */
	IRQ_TIMER0,     /**< Timer 0 interrupt */
	IRQ_TIMER1,     /**< Timer 1 interrupt */
	IRQ_TIMER2,     /**< Timer 2 interrupt */
	IRQ_TIMER3,     /**< Timer 3 interrupt */
	IRQ_UART0,      /**< Uart 0 interrupt */
	IRQ_UART1,      /**< Uart 1 interrupt */
	IRQ_UART2,      /**< Uart 2 interrupt */

	IRQ_UART3,      /**< Uart 3 interrupt */
	IRQ_PWM1,       /**< PWM 1 interrupt */
	IRQ_I2C0,       /**< I2C 0 interrupt */
	IRQ_I2C1,       /**< I2C 1 interrupt */
	IRQ_I2C2,       /**< I2C 2 interrupt */
	IRQ_SPI,        /**< SPI interrupt */
	IRQ_SSP0,       /**< SSP 0 interrupt */
	IRQ_SSP1,       /**< SSP 1 interrupt */

	IRQ_PLL0,       /**< PLL 0 interrupt */
	IRQ_RTC,        /**< Real time clock (RTC) interrupt */
	IRQ_EINT0,      /**< External interrupt 0 */
	IRQ_EINT1,      /**< External interrupt 1 */
	IRQ_EINT2,      /**< External interrupt 2 */
	IRQ_EINT3,      /**< External interrupt 3 */
	IRQ_ADC,        /**< Analog-to-digital converter interrupt */
	IRQ_BOD,        /**< Brown out detect interrupt */

	IRQ_USB,        /**< USB interrupt */
	IRQ_CAN,        /**< CAN controller interrupt */
	IRQ_GPDMA,      /**< General purpose DMA interrupt */
	IRQ_I2S,        /**< I2S interrupt */
	IRQ_ETHERNET,   /**< Ethernet interrupt */
	IRQ_RITIRQ,     /**< Repetitive interrupt timer */
	IRQ_MCPWM,      /**< Motor control PWM interrupt */
	IRQ_QE,         /**< Quadrature encoder interrupt */

	IRQ_PLL1,       /**< PLL 1 interrupt */
	IRQ_USBACT,     /**< USB activity interrupt */
	IRQ_CANACT,     /**< CAN activity interrupt */

	IRQ_MAX,
};

/***************************************************************************************************************************************//**

    An application-defined function that handles an interrupt request.

    @param[in]  irq         The interrupt request that has occurred.

    @return     None.
    @module     irq-lpc175x6x

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
    @module     irq-lpc175x6x

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

    @module     irq-lpc175x6x

*******************************************************************************************************************************************/
extern STATUS IRQ_RegisterHandler(IRQ irq, IRQHANDLER handler);

/***************************************************************************************************************************************//**

    Enables an interrupt within the nested vectored interrupt controller (NVIC).

    @param[in]  irq         The interrupt to be enabled.

    @return     None.
    @module     irq-lpc175x6x

*******************************************************************************************************************************************/
extern void IRQ_Enable(IRQ irq);

/***************************************************************************************************************************************//**

    Disables an interrupt within the nested vectored interrupt controller (NVIC).

    @param[in]  irq         The interrupt source to be disabled.

    @return     None.
    @module     irq-lpc175x6x

*******************************************************************************************************************************************/
extern void IRQ_Disable(IRQ irq);

/***************************************************************************************************************************************//**

    Returns an indication of whether an interrupt is currently enabled.

    @param[in]  irq         The interrupt source to be checked.

    @return     TRUE if the specified interrupt is enabled; otherwise FALSE.
    @module     irq-lpc175x6x

*******************************************************************************************************************************************/
extern BOOLEAN IRQ_IsEnabled(IRQ irq);

/***************************************************************************************************************************************//**

    Returns the priority for an interrupt within the NVIC.

    @param[in]  irq         The target interrupt source.

    @return     The current priority for the given interrupt source.
    @module     irq-lpc175x6x

*******************************************************************************************************************************************/
extern BYTE IRQ_Priority(IRQ irq);

/***************************************************************************************************************************************//**

    Sets the priority for an interrupt within the NVIC.

    @param[in]  irq         The target interrupt source to receive the new priority value.
    @param[in]  priority    The new priority for the specified interrupt. Value should be between 0 and 31. A lower value indicates a 
                            higher priority.

    @return     None
    @module     irq-lpc175x6x

*******************************************************************************************************************************************/
extern void IRQ_SetPriority(IRQ irq, BYTE priority);

#if (CFG_HOOKUNHANDLEDIRQ)
/***************************************************************************************************************************************//**

    An application-defined hook function that is called when an unhandled interrupt occurs.

    @param[in]  irq         The interrupt that has occurred and is unhandled.

    @return     None.
    @module     irq-lpc175x6x

*******************************************************************************************************************************************/
extern void HOOK_UnhandledIRQ(IRQ irq);
#endif

#endif /* MCU_IRQ_H__ */
