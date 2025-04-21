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
#include "mcu_irq.h"
#include "Kernel/kernel_core.h"
        
/*******************************************************************************************************************************************
    PRIVATE VARIABLES
*******************************************************************************************************************************************/
static IRQHANDLER mcu_irqs[IRQ_MAX];

/*******************************************************************************************************************************************
    PRIVATE FUNCTIONS
*******************************************************************************************************************************************/
static void IRQ_Unhandled(IRQ irq);

/***************************************************************************************************************************************//**

    Initializes interrupt handlers.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The interrupt handlers have been initialized.

    @remark     Not to be called directly from user code.
    @module     internal

*******************************************************************************************************************************************/
STATUS IRQ_Initialize(void)
{
    UINT32 k;
    
    
    for (k = 0; k < IRQ_MAX; k++) {
        mcu_irqs[k] = IRQ_Unhandled;                            /* Default the interrupt handlers */
    }
    
    return SUCCESS;
}

/***************************************************************************************************************************************//**

    A global interrupt handler.

    @return     None.
    @remark     Not to be called directly from user code.
    @module     internal

*******************************************************************************************************************************************/
void IRQ_Handler(void)
{ 
    UINT32 irq_num;
#if (CFG_ISRSTATISTICS)
    INTERRUPTLOCK lock;
#endif
    
    
#if (CFG_ISRSTATISTICS)
    ACQUIREINTERRUPTLOCK();
    isr_stats.nesting++;                                        /* Keep a nesting depth indicator */
    RELEASEINTERRUPTLOCK();
#endif
    
    irq_num = REGBITS_ICSR.VECTACTIVE - 16;                     /* Get active interrupt number */
    mcu_irqs[irq_num]((IRQ)irq_num);                            /* Call the application-defined interrupt handler */
                    
#if (CFG_ISRSTATISTICS) 
    ACQUIREINTERRUPTLOCK();
    isr_stats.nesting--;                                        /* Update the nesting depth */
    isr_stats.count++;                                          /* Keep a total count of interrupts */
    RELEASEINTERRUPTLOCK();
#endif
}

/***************************************************************************************************************************************//**

    A default handler for an unhandled interrupt request.

    @param[in]  irq         The interrupt request that was unhandled.

    @return     None.
    @remark     Not to be called directly from user code.
    @module     internal

*******************************************************************************************************************************************/
static void IRQ_Unhandled(IRQ irq)
{
#if (CFG_HOOKUNHANDLEDIRQ)
    HOOK_UnhandledIRQ(irq);                                     /* Call hook function if configured */
#endif
}

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
STATUS IRQ_RegisterHandler(IRQ irq, IRQHANDLER handler)
{
    mcu_irqs[irq] = handler;
    return SUCCESS;
}

/***************************************************************************************************************************************//**

    Enables an interrupt within the nested vectored interrupt controller (NVIC).

    @param[in]  irq         The interrupt to be enabled.

    @return     None.
    @module     irq-lpc13x1x2x3

*******************************************************************************************************************************************/
void IRQ_Enable(IRQ irq)
{
    INTERRUPTLOCK lock;
    volatile UINT32* reg;

    
    reg = (volatile UINT32*)(BASE_ISER + ((irq >> 5) * sizeof(UINT32)));    /* Get the appropriate ISER register for the given IRQ */

    ACQUIREINTERRUPTLOCK();
    *reg = (1 << (irq % 32));                                               /* Enable the interrupt */
    RELEASEINTERRUPTLOCK();
}

/***************************************************************************************************************************************//**

    Disables an interrupt within the nested vectored interrupt controller (NVIC).

    @param[in]  irq         The interrupt source to be disabled.

    @return     None.
    @module     irq-lpc13x1x2x3

*******************************************************************************************************************************************/
void IRQ_Disable(IRQ irq)
{
    INTERRUPTLOCK lock;
    volatile UINT32* reg;

    
    reg = (volatile UINT32*)(BASE_ICER + ((irq >> 5) * sizeof(UINT32)));    /* Get the appropriate ICER register for the given IRQ */
    
    ACQUIREINTERRUPTLOCK();
    *reg = (1 << (irq % 32));                                               /* Disable the interrupt */
    RELEASEINTERRUPTLOCK();
}

/***************************************************************************************************************************************//**

    Returns an indication of whether an interrupt is currently enabled.

    @param[in]  irq         The interrupt source to be checked.

    @return     TRUE if the specified interrupt is enabled; otherwise FALSE.
    @module     irq-lpc13x1x2x3

*******************************************************************************************************************************************/
BOOLEAN IRQ_IsEnabled(IRQ irq)
{
    INTERRUPTLOCK lock;
    volatile UINT32* reg;
    
    
    reg = (volatile UINT32*)(BASE_ISER + ((irq >> 5) * sizeof(UINT32)));    /* Get the appropriate ISER register for the given IRQ */
    

    ACQUIREINTERRUPTLOCK();
    
    if (*reg & (1 << (irq % 32))) {                                         /* Is the interrupt enabled? */
        RELEASEINTERRUPTLOCK(); 
        return TRUE;                                                        /* Yes, currently enabled */
    }

    RELEASEINTERRUPTLOCK(); 
    return FALSE;                                                           /* No, currently disabled */
}

/***************************************************************************************************************************************//**

    Returns the priority for an interrupt within the NVIC.

    @param[in]  irq         The target interrupt source.

    @return     The current priority for the given interrupt source.
    @module     irq-lpc13x1x2x3

*******************************************************************************************************************************************/
BYTE IRQ_Priority(IRQ irq)
{
    INTERRUPTLOCK lock;
    UINT32* reg;
    UINT32 offset;
    BYTE prio;


    reg = (UINT32*)(BASE_IPR + (((UINT32)irq / 4) * 4));        /* Get the priority register for the specified interrupt source */
    offset = ((UINT32)irq % 4) * 8;                             /* Calculate the bit placement within the register */

    ACQUIREINTERRUPTLOCK();
    
    prio = (((*reg) >> offset) >> 3);                           /* Get the priority bits */
    
    RELEASEINTERRUPTLOCK();
    return prio;
}

/***************************************************************************************************************************************//**

    Sets the priority for an interrupt within the NVIC.

    @param[in]  irq         The target interrupt source to receive the new priority value.
    @param[in]  priority    The new priority for the specified interrupt. Value should be between 0 and 31. A lower value indicates a 
                            higher priority.

    @return     None
    @module     irq-lpc13x1x2x3

*******************************************************************************************************************************************/
void IRQ_SetPriority(IRQ irq, BYTE priority)
{
    INTERRUPTLOCK lock;
    UINT32* reg;
    UINT32 offset;


    reg = (UINT32*)(BASE_IPR + (((UINT32)irq / 4) * 4));        /* Get the priority register for the specified interrupt source */
    offset = ((UINT32)irq % 4) * 8;                             /* Calculate the bit placement within the register */

    ACQUIREINTERRUPTLOCK();

    *reg &= ~(0xFF << offset);                                  /* Clear then set the priority bits */
    *reg |= ((priority << 3) << offset);

    RELEASEINTERRUPTLOCK();
}
