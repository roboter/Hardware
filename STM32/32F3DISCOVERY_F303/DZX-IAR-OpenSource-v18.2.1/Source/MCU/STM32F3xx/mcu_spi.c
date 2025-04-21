/*******************************************************************************************************************************************

    DZX | STM32F3xx | SPI                                                                                                 VERSION 18.2.1
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
#include "mcu_irq.h"
#include "mcu_cfg.h"
#include "mcu_rcc.h"
#include "mcu_kernel.h"

/*******************************************************************************************************************************************
    PRIVATE VARIABLES
*******************************************************************************************************************************************/
static SPI* mcu_spi[3];

/*******************************************************************************************************************************************
    PRIVATE FUNCTIONS
*******************************************************************************************************************************************/
static void SPI_ApplyClock(SPI* port, UINT32 baud);
static void SPI_IRQ(IRQ irq);

/***************************************************************************************************************************************//**

    Opens an SPI port for communications.

    The port is opened by powering the peripheral and configuring it's clock for the specified baud rate. Interrupts for the port are
    enabled within the NVIC.

    @param[in]  port        A caller allocated SPI port to be initialized.
    @param[in]  number      The number of the port to be opened (valid values are 1-3).
    @param[in]  clkHz       The target clock rate, in hertz, for the port.
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

    @remark     The peripheral only supports power-of-two clock divisors, therefore the actual clock frequency will be set at or below
                the requested frequency.
    @module     spi-stm32f3xx

*******************************************************************************************************************************************/
STATUS SPI_Open(SPI* port, UINT32 number, UINT32 clkHz, UINT32 mode)
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

    switch (number) {
        case 1:
            port->REG = REG_SPI1;
            
            ACQUIREINTERRUPTLOCK();
            REGBITS_RCCAPB2ENR.SPI1EN = 1;
            RELEASEINTERRUPTLOCK();
            
            IRQ_RegisterHandler(IRQ_SPI1, SPI_IRQ);
            IRQ_Enable(IRQ_SPI1);
            break;
        case 2:
            port->REG = REG_SPI2;
            
            ACQUIREINTERRUPTLOCK();
            REGBITS_RCCAPB1ENR.SPI2EN = 1;
            RELEASEINTERRUPTLOCK();
            
            IRQ_RegisterHandler(IRQ_SPI2, SPI_IRQ);
            IRQ_Enable(IRQ_SPI2);
            break;
        case 3:
            port->REG = REG_SPI3;
            
            ACQUIREINTERRUPTLOCK();
            REGBITS_RCCAPB1ENR.SPI3EN = 1;
            RELEASEINTERRUPTLOCK();
            
            IRQ_RegisterHandler(IRQ_SPI3, SPI_IRQ);
            IRQ_Enable(IRQ_SPI3);
            break;
        default:
            return ERR_NOTSUPPORTED;
    }

    port->number = number - 1;
   
    status = MUTEX_Create(&port->mutex, "SPI", FALSE);          /* Create an underlying mutex */
    if (status != SUCCESS) {
        return status;
    }
    
    SIGNAL_Init(&port->signals);
    
    port->REG->CR1.BITS.MSTR = 1;                               /* Select master mode */
    port->REG->CR1.BITS.CPHA = (mode & 0x1);                    /* Clock phase */
    port->REG->CR1.BITS.CPOL = ((mode >> 1) & 0x1);             /* Clock polarity */
    
    port->REG->CR1.BITS.BIDIMODE = 0;                           /* 2-wire mode */
    port->REG->CR1.BITS.BIDIOE = 1;
    port->REG->CR1.BITS.DFF = 0;                                /* 8-bit data transfers */
    port->REG->CR1.BITS.LSBFIRST = 0;
    
    port->REG->CR1.BITS.RXONLY = 0;                             /* Full duplex */
    port->REG->CR1.BITS.SSM = 0;                                /* Disable software slave management */
    
    port->REG->CR2.BITS.DS = 7;                                 /* 8-bit data transfers */
    port->REG->CR2.BITS.FRXTH = 1;
    
    SPI_ApplyClock(port, clkHz);                                /* Set the clock rate */
    
    port->REG->CR2.BITS.SSOE = 1;   
    port->REG->CR1.BITS.SPE = 1;                                /* Enable SPI */

    mcu_spi[number - 1] = port;                                 /* Keep a local reference of the opened port */
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
    @module     spi-stm32f3xx

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
    
    port->REG->CR1.BITS.SPE = 0;
    
    switch (port->number) {                                 /* Find by port number */
        case 1:
            IRQ_Disable(IRQ_SPI1);                          /* Disable possible interrupts */
            break;
        case 2:
            IRQ_Disable(IRQ_SPI2);                          /* Disable possible interrupts */
            break;
        case 3:
            IRQ_Disable(IRQ_SPI3);                          /* Disable possible interrupts */
            break;
        default:
            RELEASEINTERRUPTLOCK();
            return ERR_INVALIDOPERATION;                    /* Unsupported port number */
    }

    mcu_spi[port->number] = NULL;                           /* Release the port */
    
    RELEASEINTERRUPTLOCK();
    return SUCCESS;
}

/***************************************************************************************************************************************//**

    Gets an indication of whether an SPI port is currently open for communications.

    @param[in]  port        A pointer to the target SPI port.

    @return     TRUE if the SPI port is currently open; otherwise FALSE.
    @module     spi-stm32f3xx

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
    UINT32 input;
    static UINT32 div;
    UINT32 brc;
    
    
    switch (port->number + 1) {
        case 1:
            input = MCU_APB2ClockHz();
            break;
            
        case 2:
        case 3:
            input = MCU_APB1ClockHz();
            break;
    }
    
    div = input / baud;
    
    for (brc = 0; brc < 8; brc++) {
        if ((1 << (brc + 1)) >= div) {
            port->REG->CR1.BITS.BR = brc;
            return;
        }
    }
    
    port->REG->CR1.BITS.BR = 7;
}

/***************************************************************************************************************************************//**

    Writes data to an SPI port.

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

    @module     spi-stm32f3xx

*******************************************************************************************************************************************/
STATUS SPI_Write(SPI* port, const void* data, UINT32 nbytes, UINT32 timeout)
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
    
    port->REG->CR2.BITS.RXNEIE = 1;                                     /* Enable interrupt on transmit buffer empty */
    *((BYTE*)&port->REG->DR) = ((BYTE*)port->data)[0];                  /* Initiate the first transfer */
   
    status = SIGNAL_WaitOne(&port->signals, SIGNAL_0, timeout);         /* Block and wait for the transfer to complete */
    
    port->REG->CR2.BITS.TXEIE = 0;                                      /* Disable further interrupts */
    port->REG->CR2.BITS.RXNEIE = 0;
    
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

    @module     spi-stm32f3xx

*******************************************************************************************************************************************/
STATUS SPI_Read(SPI* port, void* buf, UINT32 nbytes, UINT32 timeout)
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
    
    
    port->REG->CR2.BITS.RXNEIE = 1;                                         /* Enable receive interrupt */
    *((BYTE*)&port->REG->DR) = 0;                                                      /* Initiate a transfer */
    
    status = SIGNAL_WaitOne(&port->signals, SIGNAL_0, timeout);
    
    port->REG->CR2.BITS.RXNEIE = 0;
    
    if (status == SUCCESS) {                                            /* Did the blocking operation receive a signal from the interrupt? */
        MUTEX_Release(&port->mutex);
        return port->result;                                            /* Yes, then return the result from the interrupt */
    }
    
    MUTEX_Release(&port->mutex);
    return status;                                                      /* Return the error code */
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

    @module     spi-stm32f3xx

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

    @module     spi-stm32f3xx

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

    Interrupt request handler for the SPI peripheral.

    @param[in]  irq         The interrupt request to be handled.

    @return     None
    @module     internal

*******************************************************************************************************************************************/
static void SPI_IRQ(IRQ irq)
{
    SPI* port;
    volatile BYTE dummy;
    
    
    (void)dummy;
    
    switch (irq) {
        case IRQ_SPI1:
            port = mcu_spi[0];
            break;
        case IRQ_SPI2:
            port = mcu_spi[1];
            break;
        case IRQ_SPI3:
            port = mcu_spi[2];
            break;
    }
    
    if (port->buf) {
        ((BYTE*)port->buf)[port->idx] = *((BYTE*)&port->REG->DR);   /* Read the received data byte */
    } else {
       dummy = *((BYTE*)&port->REG->DR);                            /* Read a dummy byte */
    }
    
    port->idx++;                                                    /* Account for the completed data byte */
    
    if (port->idx >= port->nbytes) {                                /* Is the transfer complete? */
        port->REG->CR2.BITS.TXEIE = 0;
        port->REG->CR2.BITS.RXNEIE = 0;
        port->result = SUCCESS;
        SIGNAL_Set(&port->signals, SIGNAL_0);                       /* Signal any waiting thread */
        return;
    }
    
    if (port->data) {
        *((BYTE*)&port->REG->DR) = ((BYTE*)port->data)[port->idx];
    } else {
        *((BYTE*)&port->REG->DR) = (BYTE)0;
    }
}
