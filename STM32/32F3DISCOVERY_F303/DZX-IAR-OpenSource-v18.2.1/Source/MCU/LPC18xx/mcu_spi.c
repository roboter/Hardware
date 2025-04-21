/*******************************************************************************************************************************************

    DZX | LPC18xx | SPI                                                                                                   VERSION 18.2.1
    ------------------------------------------------------------------------------------------------------------------------------------

    This is part of the MCU peripheral drivers and provides support for the SPI ports. This driver only provides master mode
    transfers.

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
#include "mcu_spi.h"
#include "mcu_cfg.h"
#include "mcu_irq.h"
#include "mcu_cgu.h"

/*******************************************************************************************************************************************
    PRIVATE VARIABLES
*******************************************************************************************************************************************/
static SPI* mcu_spi[2];         /* Pointers to each of the open SPI ports */

/*******************************************************************************************************************************************
    PRIVATE FUNCTIONS
*******************************************************************************************************************************************/
static void SPI_ApplyClock(SPI* port, UINT32 baud);
static void SSP_IRQ(IRQ irq);

/***************************************************************************************************************************************//**

    Opens an SPI port for communications.

    The port is opened by powering the peripheral and configuring it's clock for the specified baud rate. Interrupts for the port are
    enabled within the NVIC.

    @param[in]  port        A caller allocated SPI port to be initialized.
    @param[in]  number      The number of the port to be opened.

     Number                 | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     0                      | Use for SSP port 0.
     1                      | Use for SSP port 1.

    @param[in]  clkHz       The target clock rate in hertz for the port.
    @param[in]  mode        The mode of control clock phase and polarity. Bitwise OR to specify multiple options.
        
     mode                   | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SPI_DEFAULT            | Use default options (CPHA = 0 and CPOL = 1)
     SPI_CPHA0              | Use to sample data on the leading (first) clock edge (CPHA = 0).
     SPI_CPHA1              | Use to sample data on the trailing (second) clock edge (CPHA = 1).
     SPI_CPOL0              | Use for active high clock (CPOL = 0).
     SPI_CPOL1              | Use for active low clock (CPOL = 1).
       
    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The port was successfully configured and is open for communications.
     ERR_NULLREFERENCE      | The argument 'port' was found to be NULL.
     ERR_INVALIDCONTEXT     | This operation is not supported from the context of an interrupt service routine (ISR).
     ERR_NOTSUPPORTED       | The specified port number is not supported.

    @remark     Not thread safe.
    @module     spi-lpc18xx

*******************************************************************************************************************************************/
STATUS SPI_Open(SPI* port, UINT32 number, UINT32 clkHz, UINT32 mode)
{
    STATUS status;

    
#if (CFG_CONTEXTCHECKING)
    if (KERNEL_IsISR()) {
        return ERR_INVALIDCONTEXT;
    }
#endif
#if (CFG_NULLCHECKING)
    if (port == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif

    switch (number) {
        case 0:
            port->REG = REG_SSP0;
            REGBITS_CGUBASESSP0CLK.CLKSEL = 9;
            REGBITS_CGUBASESSP0CLK.AUTOBLOCK = 1;
            REGBITS_CGUBASESSP0CLK.PD = 0;
            IRQ_RegisterHandler(IRQ_SSP0, SSP_IRQ);
            IRQ_Enable(IRQ_SSP0);
            break;
        case 1:
            port->REG = REG_SSP1;
            REGBITS_CGUBASESSP1CLK.CLKSEL = 9;
            REGBITS_CGUBASESSP1CLK.AUTOBLOCK = 1;
            REGBITS_CGUBASESSP1CLK.PD = 0;
            IRQ_RegisterHandler(IRQ_SSP1, SSP_IRQ);
            IRQ_Enable(IRQ_SSP1);
            break;
        default:
            return ERR_NOTSUPPORTED;
    }

    port->number = number;
    SPI_ApplyClock(port, clkHz);                                /* Set the clock rate */

    status = MUTEX_Create(&port->mutex, "SPI", FALSE);          /* Create an underlying mutex */
    if (status != SUCCESS) {
        return status;
    }
   
    SIGNAL_Init(&port->signals);

    port->REG->CR0.BITS.FRF = 0;                                /* Configure as SPI */
    port->REG->CR0.BITS.DSS = 7;                                /* Configure as 8-bit transfers */
    
    if (mode & SPI_CPHA1) {
        port->REG->CR0.BITS.CPHA = 1;
    } else {
        port->REG->CR0.BITS.CPHA = 0;
    }
    
    if (mode & SPI_CPOL1) {
        port->REG->CR0.BITS.CPOL = 1;
    } else {
        port->REG->CR0.BITS.CPOL = 0;
    }
    
    port->REG->CR1.BITS.MS = 0;                                 /* Configure as master */
    port->REG->CR1.BITS.SSE = 1;                                /* Enable the controller */

    mcu_spi[number] = port;                                     /* Keep a local reference of the opened port */
    return SUCCESS;
}

/***************************************************************************************************************************************//**

    Closes and releases all resources used by an SPI port.

    The port is closed by powering the peripheral down and disabling it's interrupt within the NVIC.

    @param[in]  port        A pointer to the port to be closed.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The port was successfully closed.
     ERR_NULLREFERENCE      | The argument 'port' was found to be NULL.
     ERR_INVALIDCONTEXT     | This operation is not supported from the context of an interrupt service routine (ISR).
     ERR_NOTINITIALIZED     | The specified port has not been initialized (opened).

    @remark     Not thread safe.     
    @module     spi-lpc18xx

*******************************************************************************************************************************************/
STATUS SPI_Close(SPI* port)
{
    INTERRUPTLOCK lock;
    STATUS status;
    
 
#if (CFG_CONTEXTCHECKING)
    if (KERNEL_IsISR()) {
        return ERR_INVALIDCONTEXT;
    }
#endif
#if (CFG_NULLCHECKING)
    if (port == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif
    
    if (mcu_spi[port->number] != port) {                    /* Is the port open? */
        return ERR_NOTINITIALIZED;
    }
    
    status = MUTEX_Destroy(&port->mutex);
    if (status != SUCCESS) {
        return status;
    }
    
    ACQUIREINTERRUPTLOCK();
    
    switch (port->number) {                                     /* Find by port number */
        case 0:
            IRQ_Disable(IRQ_SSP0);                             /* Disable possible interrupts */
            break;
        case 1:
            IRQ_Disable(IRQ_SSP1);                             /* Disable possible interrupts */
            break;
        default:
            RELEASEINTERRUPTLOCK();
            return ERR_INVALIDOPERATION;                        /* Unsupported port number */
    }

    mcu_spi[port->number] = NULL;                               /* Release the port */
    
    RELEASEINTERRUPTLOCK();
    return SUCCESS;
}

/***************************************************************************************************************************************//**

    Gets an indication of whether an SPI port is currently open for communications.

    @param[in]  port        A pointer to the target SPI port.

    @return     TRUE if the SPI port is currently open; otherwise FALSE.
    @module     spi-lpc18xx

*******************************************************************************************************************************************/
BOOLEAN SPI_IsOpen(SPI* port)
{
    INTERRUPTLOCK lock;
    
    
#if (CFG_NULLCHECKING)
    if (port == NULL) {
        return FALSE;
    }
#endif

    ACQUIREINTERRUPTLOCK();
    
    if (mcu_spi[port->number] == port) {
        RELEASEINTERRUPTLOCK();
        return TRUE;
    }

    RELEASEINTERRUPTLOCK();
    return FALSE;
}

/***************************************************************************************************************************************//**

    Configures the baud rate for an SPI port.

    @param[in]  port        A pointer to the port to be configured.
    @param[in]  baud        The new baud rate for the port.

    @return     None.
    @module     internal

*******************************************************************************************************************************************/
static void SPI_ApplyClock(SPI* port, UINT32 baud)
{
    UINT32 divisor;
    UINT32 prescalar;


    prescalar = 2;
    divisor = (CFG_CPUCLOCKHZ / (baud * prescalar)) - 1;
    if (divisor > 255) {                                        /* Bound the divisor */
        divisor = 255;
    }

    port->REG->CR0.BITS.SCR = divisor;                          /* Assign divisor and prescaler */
    port->REG->CPSR.BITS.CPSDVSR = prescalar;
}

/***************************************************************************************************************************************//**

    Writes and transmits data over an SPI port.

    @param[in]  port        A pointer to the port to transmit the data.
    @param[in]  data        A pointer to the data to be written.
    @param[in]  nbytes      The total number of bytes to be written.
    @param[in]  timeout     The maximum amount of time, in kernel ticks, to block and wait for the transfer to complete. Must not be zero
                            and must be large enough to allow the transfer to complete; based upon clock rate and amount of data being
                            transferred. Use INFINITE to wait indefinitely.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The transfer completed successfully.
     ERR_NULLREFERENCE      | The argument 'port' or 'data' was found to be NULL.
     ERR_INVALIDCONTEXT     | This operation is not supported from the context of an interrupt service routine (ISR).
     ERR_TIMEOUT            | The specified amount of time has elapsed before the transfer was complete.

    @module     spi-lpc18xx

*******************************************************************************************************************************************/
STATUS SPI_Write(SPI* port, const void* data, UINT32 nbytes, UINT32 timeout)
{
    STATUS status;
    UINT32 k;
    
    
#if (CFG_CONTEXTCHECKING)
    if (KERNEL_IsISR()) {
        return ERR_INVALIDCONTEXT;
    }
#endif
#if (CFG_NULLCHECKING)
    if (port == NULL) {
        return ERR_NULLREFERENCE;
    }

    if (data == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif
    
    status = MUTEX_Acquire(&port->mutex, timeout);
    if (status != SUCCESS) {
        return status;
    }

    port->data = (void*)data;
    port->buf = NULL;
	port->nbytes = nbytes;
	port->idx = 0;
    
    SIGNAL_Clear(&port->signals, SIGNAL_0);
    
    k = 0;                                                      
    while ((k < 4) && (k < port->nbytes)) {                     /* Load the local SPI FIFO */   
        port->REG->DR.VALUE = ((BYTE*)port->data)[k++];         /* Load the specified data bytes */
    }
    port->REG->IMSC.BITS.RTIM = 1;                              /* Enable the interrupts to complete the transfer */
    port->REG->IMSC.BITS.RXIM = 1;
    
    status = SIGNAL_WaitOne(&port->signals, SIGNAL_0, timeout); /* Block and wait for the transfer to complete */
    
    port->REG->IMSC.BITS.RTIM = 0;                              /* Disable further interrupts */
    port->REG->IMSC.BITS.RXIM = 0;
            
    if (status == SUCCESS) {
        MUTEX_Release(&port->mutex);
        return port->result;
    }
    
    MUTEX_Release(&port->mutex);
    return status;
}

/***************************************************************************************************************************************//**

    Reads and returns the data received from an SPI port.

    @param[in]  port        A pointer to the port to receive the data.
    @param[out] buf         A pointer to a caller allocated buffer to receive the read data.
    @param[in]  nbytes      The total number of bytes to be read and returned.
    @param[in]  timeout     The maximum amount of time, in kernel ticks, to block and wait for the transfer to complete. Must not be zero
                            and must be large enough to allow the transfer to complete; based upon clock rate and amount of data being
                            transferred. Use INFINITE to wait indefinitely.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The transfer completed successfully and the requested data has been returned.
     ERR_NULLREFERENCE      | The argument 'port' or 'buf' was found to be NULL.
     ERR_INVALIDCONTEXT     | This operation is not supported from the context of an interrupt service routine (ISR).
     ERR_TIMEOUT            | The specified amount of time has elapsed before the transfer was complete.

    @module     spi-lpc18xx

*******************************************************************************************************************************************/
STATUS SPI_Read(SPI* port, void* buf, UINT32 nbytes, UINT32 timeout)
{
    STATUS status;
    UINT32 k;
    
    
#if (CFG_CONTEXTCHECKING)
    if (KERNEL_IsISR()) {
        return ERR_INVALIDCONTEXT;
    }
#endif
#if (CFG_NULLCHECKING)
    if (port == NULL) {
        return ERR_NULLREFERENCE;
    }

    if (buf == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif
    
    status = MUTEX_Acquire(&port->mutex, timeout);
    if (status != SUCCESS) {
        return status;
    }
    
    SIGNAL_Clear(&port->signals, SIGNAL_0);
    
    port->data = NULL;
    port->buf = buf;
	port->nbytes = nbytes;
	port->idx = 0;
   
    k = 0;                                                      
    while ((k < 4) && (k < port->nbytes)) {                     /* Load the local SPI FIFO */   
        port->REG->DR.VALUE = 0;
        k++;
    }
    
    port->REG->IMSC.BITS.RTIM = 1;                              /* Enable the interrupts to complete the transfer */
    port->REG->IMSC.BITS.RXIM = 1;

    
    status = SIGNAL_WaitOne(&port->signals, SIGNAL_0, timeout);
    
    port->REG->IMSC.BITS.RTIM = 0;                              /* Disable further interrupts */
    port->REG->IMSC.BITS.RXIM = 0;

    if (status == SUCCESS) {                                    /* Did the blocking operation receive a signal from the interrupt? */
        MUTEX_Release(&port->mutex);
        return port->result;                                    /* Yes, then return the result from the interrupt */
    }
    
    MUTEX_Release(&port->mutex);
    return status;                                              /* Return the error code */
}

/***************************************************************************************************************************************//**

    Selects an SPI port by acquiring exclusive access to the port and activating the chip-select signal.

    @param[in]  port        A pointer to the target port.
    @param[in]  cs          The pin to be used as the chip-select signal.
    @param[in]  timeout     The maximum amount of time, in kernel ticks, to block and wait to acquire exclusive access to the port. Use
                            '0' to return immediately without blocking and use 'INFINITE' to block and wait indefinitely.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The port has been selected.
     ERR_NULLREFERENCE      | The argument 'port' was found to be NULL.
     ERR_INVALIDCONTEXT     | This operation is not supported from the context of an interrupt service routine (ISR).
     ERR_NOTINITIALIZED     | The specified port has not been initialized (opened).
     ERR_TIMEOUT            | The specified amount of time has elapsed before a claim was acquired upon the port.

    @module     spi-lpc18xx

*******************************************************************************************************************************************/
STATUS SPI_Select(SPI* port, PIN cs, UINT32 timeout)
{
    STATUS status;
    
    
#if (CFG_NULLCHECKING)
    if (port == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif
    
    if (mcu_spi[port->number] != port) {
        return ERR_NOTINITIALIZED;
    }
    
    status = MUTEX_Acquire(&port->mutex, timeout);              /* Claim exclusive access to the bus */
    if (status != SUCCESS) {
        return status;                                          /* Failed, bubble up error */
    }
    
    if (cs != PIN_INVALID) {
        PIN_Write(cs, FALSE);                                   /* Activate the chip-select signal */
    }
    
    return SUCCESS;
}

/***************************************************************************************************************************************//**

    Deselects a port by deactivating the chip-select signal and releasing exclusive access to an SPI port.

    @param[in]  port        A pointer to the target port.
    @param[in]  cs          The pin to be used as the chip-select signal.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The port has been deselected.
     ERR_NULLREFERENCE      | The argument 'port' was found to be NULL.
     ERR_INVALIDCONTEXT     | This operation is not supported from the context of an interrupt service routine (ISR).
     ERR_NOTINITIALIZED     | The specified port has not been initialized (opened).

    @module     spi-lpc18xx

*******************************************************************************************************************************************/
STATUS SPI_Deselect(SPI* port, PIN cs)
{ 
#if (CFG_NULLCHECKING)
    if (port == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif
    
    if (mcu_spi[port->number] != port) {
        return ERR_NOTINITIALIZED;
    }
    
    if (cs != PIN_INVALID) {
        PIN_Write(cs, TRUE);                                    /* Deactivate the chip-select signal */
    }
    
    return MUTEX_Release(&port->mutex);                         /* Release the exclusive access claim on the bus */
}

/***************************************************************************************************************************************//**

    Interrupt request handler for an SSP peripheral.

    @param[in]  port        A pointer to the port that has a pending interrupt request.

    @return     None
    @module     internal

*******************************************************************************************************************************************/
static void SSP_IRQ(IRQ irq)
{
    volatile BYTE dummy;
    SPI* port;
    UINT32 idx;
    
    
    (void)dummy;
    
    switch (irq) {
        case IRQ_SSP0:
            port = mcu_spi[0];
            break;
        case IRQ_SSP1:
            port = mcu_spi[1];
            break;
        default:
            return;
    }

    while (port->REG->SR.BITS.RNE) {                                        /* While the receive queue is not empty... */
        if (port->buf) {                                                    /* Is the driver is receiving? */
            ((BYTE*)port->buf)[port->idx++] = port->REG->DR.VALUE;          /* Read the received byte */
        } else {
            dummy = port->REG->DR.VALUE;                                    /* Not receiving, don't care dummy read */
            port->idx++;
        }
    }

    if (port->idx >= port->nbytes) {                                        /* Is the transfer completed? */
        port->result = SUCCESS;
        SIGNAL_Set(&port->signals, SIGNAL_0);
        return;
    }

    idx = 0;

    if (port->data) {
        if (port->idx >= port->nbytes) {
            port->result = SUCCESS;
            SIGNAL_Set(&port->signals, SIGNAL_0);
            return;
        }

        while ((idx < 4) && (port->idx + idx < port->nbytes)) {
            port->REG->DR.VALUE = ((BYTE*)port->data)[port->idx + idx];
            idx++;
        }
    } else {
        while ((idx < 4) && (port->idx + idx < port->nbytes)) {
            port->REG->DR.VALUE = 0;
            idx++;
        }
    }
}
