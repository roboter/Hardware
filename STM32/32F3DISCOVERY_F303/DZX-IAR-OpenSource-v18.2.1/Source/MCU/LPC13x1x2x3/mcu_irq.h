/*******************************************************************************************************************************************

    DZX | LPC13x1x2x3 | IRQ                                                                                               VERSION 18.2.1
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
typedef enum LPC13X1X2X3_IRQ IRQ;

/***************************************************************************************************************************************//**

    Represents an individual interrupt source that is managed by the NVIC.
    @module     irq-lpc13x1x2x3

*******************************************************************************************************************************************/
enum LPC13X1X2X3_IRQ {
    IRQ_WAKEUP0 = 0,
    IRQ_WAKEUP1,
    IRQ_WAKEUP2,
    IRQ_WAKEUP3,
    IRQ_WAKEUP4,
    IRQ_WAKEUP5,
    IRQ_WAKEUP6,
    IRQ_WAKEUP7,
    IRQ_WAKEUP8,
    IRQ_WAKEUP9,
    IRQ_WAKEUP10,
    IRQ_WAKEUP11,
    IRQ_WAKEUP12,
    IRQ_WAKEUP13,
    IRQ_WAKEUP14,
    IRQ_WAKEUP15,
    IRQ_WAKEUP16,
    IRQ_WAKEUP17,
    IRQ_WAKEUP18,
    IRQ_WAKEUP19,
    IRQ_WAKEUP20,
    IRQ_WAKEUP21,
    IRQ_WAKEUP22,
    IRQ_WAKEUP23,
    IRQ_WAKEUP24,
    IRQ_WAKEUP25,
    IRQ_WAKEUP26,
    IRQ_WAKEUP27,
    IRQ_WAKEUP28,
    IRQ_WAKEUP29,
    IRQ_WAKEUP30,
    IRQ_WAKEUP31,
    IRQ_WAKEUP32,
    IRQ_WAKEUP33,
    IRQ_WAKEUP34,
    IRQ_WAKEUP35,
    IRQ_WAKEUP36,
    IRQ_WAKEUP37,
    IRQ_WAKEUP38,
    IRQ_WAKEUP39,
    
    IRQ_I2C0,
    IRQ_CT16B0,
    IRQ_CT16B1,
    IRQ_CT32B0,
    IRQ_CT32B1,
    IRQ_SSP0,
    IRQ_UART,
    
    IRQ_USBIRQ,
    IRQ_USBFIQ,
    IRQ_ADC,
    IRQ_WDT,
    IRQ_BOD,
    
    IRQ_PIO3 = 53,
    IRQ_PIO2,
    IRQ_PIO1,
    IRQ_PIO0,
    
    IRQ_SSP1,

	IRQ_MAX,
};

/***************************************************************************************************************************************//**

    An application-defined function that handles an interrupt request.
    @module     irq-lpc13x1x2x3

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
    @module     INTERNAL

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

    @module     irq-lpc13x1x2x3

*******************************************************************************************************************************************/
extern STATUS IRQ_RegisterHandler(IRQ irq, IRQHANDLER handler);

/***************************************************************************************************************************************//**

    Enables an interrupt within the nested vectored interrupt controller (NVIC).

    @param[in]  irq         The interrupt to be enabled.

    @return     None.
    @module     irq-lpc13x1x2x3

*******************************************************************************************************************************************/
extern void IRQ_Enable(IRQ irq);

/***************************************************************************************************************************************//**

    Disables an interrupt within the nested vectored interrupt controller (NVIC).

    @param[in]  irq         The interrupt source to be disabled.

    @return     None.
    @module     irq-lpc13x1x2x3

*******************************************************************************************************************************************/
extern void IRQ_Disable(IRQ irq);

/***************************************************************************************************************************************//**

    Returns an indication of whether an interrupt is currently enabled.

    @param[in]  irq         The interrupt source to be checked.

    @return     TRUE if the specified interrupt is enabled; otherwise FALSE.
    @module     irq-lpc13x1x2x3

*******************************************************************************************************************************************/
extern BOOLEAN IRQ_IsEnabled(IRQ irq);

/***************************************************************************************************************************************//**

    Returns the priority for an interrupt within the NVIC.

    @param[in]  irq         The target interrupt source.

    @return     The current priority for the given interrupt source.
    @module     irq-lpc13x1x2x3

*******************************************************************************************************************************************/
extern BYTE IRQ_Priority(IRQ irq);

/***************************************************************************************************************************************//**

    Sets the priority for an interrupt within the NVIC.

    @param[in]  irq         The target interrupt source to receive the new priority value.
    @param[in]  priority    The new priority for the specified interrupt. Value should be between 0 and 31. A lower value indicates a 
                            higher priority.

    @return     None
    @module     irq-lpc13x1x2x3

*******************************************************************************************************************************************/
extern void IRQ_SetPriority(IRQ irq, BYTE priority);


#if (CFG_HOOKUNHANDLEDIRQ)
/***************************************************************************************************************************************//**

    An application-defined hook function that is called when an unhandled interrupt occurs.

    @param[in]  irq         The interrupt that has occurred and is unhandled.

    @return     None.
    @module     irq-lpc13x1x2x3

*******************************************************************************************************************************************/
extern void HOOK_UnhandledIRQ(IRQ irq);
#endif

#endif /* MCU_IRQ_H__ */
