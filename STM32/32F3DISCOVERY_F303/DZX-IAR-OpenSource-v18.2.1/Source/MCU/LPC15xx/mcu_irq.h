/*******************************************************************************************************************************************

    DZX | LPC15xx | IRQ                                                                                                   VERSION 18.2.1
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
    @module     irq-lpc15xx

*******************************************************************************************************************************************/
typedef enum LPC15XX_IRQ {
	IRQ_WDT = 0,    /**< Watchdog interrupt */
    IRQ_BOD,
    IRQ_FLASH,
    IRQ_EE,
    IRQ_DMA,
    IRQ_GINT0,
    IRQ_GINT1,
    IRQ_PININT0,
    IRQ_PININT1,
    IRQ_PININT2,
    IRQ_PININT3,
    IRQ_PININT4,
    IRQ_PININT5,
    IRQ_PININT6,
    IRQ_PININT7,
    IRQ_RIT,
    IRQ_SCT0,
    IRQ_SCT1,
    IRQ_SCT2,
    IRQ_SCT3,
    IRQ_MRT,
    IRQ_UART0,
    IRQ_UART1,
    IRQ_UART2,
    IRQ_I2C0,
    IRQ_SPI0,
    IRQ_SPI1,
    IRQ_CCAN0,
    IRQ_USB,
    IRQ_USBFIQ,
    IRQ_USBWAKEUP,
    IRQ_ADC0SEQA,
    IRQ_ADC0SEQB,
    IRQ_ADC0THCMP,
    IRQ_ADC0OVR,
    IRQ_ADC1SEQA,
    IRQ_ADC1SEQB,
    IRQ_ADC1THCMP,
    IRQ_ADC1OVR,
    IRQ_DAC,
    IRQ_CMP0,
    IRQ_CMP1,
    IRQ_CMP2,
    IRQ_CMP3,
    IRQ_QEI,
    IRQ_RTCALARM,
    IRQ_RTCWAKE,
	IRQ_MAX,
} IRQ;

/***************************************************************************************************************************************//**

    An application-defined function that handles an interrupt request.

    @param[in]  irq         The interrupt request that has occurred.

    @return     None.
    @module     irq-lpc15xx

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
    @module     irq-lpc15xx

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

    @module     irq-lpc15xx

*******************************************************************************************************************************************/
extern STATUS IRQ_RegisterHandler(IRQ irq, IRQHANDLER handler);

/***************************************************************************************************************************************//**

    Enables an interrupt within the nested vectored interrupt controller (NVIC).

    @param[in]  irq         The interrupt to be enabled.

    @return     None.
    @module     irq-lpc15xx

*******************************************************************************************************************************************/
extern void IRQ_Enable(IRQ irq);

/***************************************************************************************************************************************//**

    Disables an interrupt within the nested vectored interrupt controller (NVIC).

    @param[in]  irq         The interrupt source to be disabled.

    @return     None.
    @module     irq-lpc15xx

*******************************************************************************************************************************************/
extern void IRQ_Disable(IRQ irq);

/***************************************************************************************************************************************//**

    Returns an indication of whether an interrupt is currently enabled.

    @param[in]  irq         The interrupt source to be checked.

    @return     TRUE if the specified interrupt is enabled; otherwise FALSE.
    @module     irq-lpc15xx

*******************************************************************************************************************************************/
extern BOOLEAN IRQ_IsEnabled(IRQ irq);

/***************************************************************************************************************************************//**

    Returns the priority for an interrupt within the NVIC.

    @param[in]  irq         The target interrupt source.

    @return     The current priority for the given interrupt source.
    @module     irq-lpc15xx

*******************************************************************************************************************************************/
extern BYTE IRQ_Priority(IRQ irq);

/***************************************************************************************************************************************//**

    Sets the priority for an interrupt within the NVIC.

    @param[in]  irq         The target interrupt source to receive the new priority value.
    @param[in]  priority    The new priority for the specified interrupt. Value should be between 0 and 31. A lower value indicates a 
                            higher priority.

    @return     None
    @module     irq-lpc15xx

*******************************************************************************************************************************************/
extern void IRQ_SetPriority(IRQ irq, BYTE priority);

#if (CFG_HOOKUNHANDLEDIRQ)
/***************************************************************************************************************************************//**

    An application-defined hook function that is called when an unhandled interrupt occurs.

    @param[in]  irq         The interrupt that has occurred and is unhandled.

    @return     None.
    @module     irq-lpc15xx

*******************************************************************************************************************************************/
extern void HOOK_UnhandledIRQ(IRQ irq);
#endif

#endif /* MCU_IRQ_H__ */
