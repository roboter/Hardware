/*******************************************************************************************************************************************

    DZX | LPC43xx | I2C                                                                                                   VERSION 18.2.1
    ------------------------------------------------------------------------------------------------------------------------------------

    This is part of the MCU peripheral drivers and provides support for I2C ports.

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
#include "mcu_i2c.h"
#include "mcu_cfg.h"
#include "mcu_irq.h"
#include "mcu_scu.h"

/*******************************************************************************************************************************************
    PRIVATE VARIABLES
*******************************************************************************************************************************************/
static I2C* mcu_i2c[2];             /* Pointers to each of the open I2C ports */

/*******************************************************************************************************************************************
    PRIVATE FUNCTIONS
*******************************************************************************************************************************************/
static void I2C_IRQ(IRQ irq);

/***************************************************************************************************************************************//**

    Opens an I2C port for communications.

    @param[in]  port        A pointer to a caller allocated I2C port to be opened.
    @param[in]  number      The port number for the port to be opened.
    @param[in]  clk         The clock frequency, in hertz, for the port.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The port has been opened.
     ERR_INVALIDCONTEXT     | The operation is not supported from the context of an interrupt service routine (ISR).
     ERR_NULLREFERENCE      | The argument 'port' was found to be NULL.
     ERR_NOTSUPPORTED       | An unsupported port number was specified.

    @module     i2c-lpc43xx

*******************************************************************************************************************************************/
STATUS I2C_Open(I2C* port, BYTE number, UINT32 clk)
{
    INTERRUPTLOCK lock;
    STATUS status;
    UINT32 ticks;


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
    
    status = MUTEX_Create(&port->mutex,                     /* Create an underlying mutex to support claiming exclusive access */
                          "I2C",
                          FALSE);             
    
    if (status != SUCCESS) {                                /* Was there an error? */
        return status;                                      /* Yes, bubble up the error */
    }
    
    SIGNAL_Init(&port->signals);

    switch (number) {                                       /* By port number, power-on, select clock and enable NVIC interrupt */
        case 0:
            port->REG = REG_I2C0;
            
            ACQUIREINTERRUPTLOCK();
            
            REGBITS_SFSI2C0.SCLEZI = 1;
            REGBITS_SFSI2C0.SDAEZI = 1;
            
            IRQ_RegisterHandler(IRQ_I2C0, I2C_IRQ);
            IRQ_Enable(IRQ_I2C0);
            
            RELEASEINTERRUPTLOCK();
            break;
        case 1:
            port->REG = REG_I2C1;
            
            ACQUIREINTERRUPTLOCK();

            IRQ_RegisterHandler(IRQ_I2C1, I2C_IRQ);
            IRQ_Enable(IRQ_I2C1);
            
            RELEASEINTERRUPTLOCK();
            break;
        default:
            return ERR_NOTSUPPORTED;
    }
   
    port->REG->CONCLR = 0x6C;                               /* Initialize all flags cleared */

    ticks = (CFG_CPUCLOCKHZ / (clk)) >> 1;    /* Calculate the half clock cycle (50% duty) in time ticks */
    port->REG->SCLH = ticks;
    port->REG->SCLL = ticks;
    port->REG->CONSET = 0x40;                               /* Enable the I2C interface */

    port->number = number;                                  /* Assign the port number */
    mcu_i2c[number] = port;                                 /* Keep a reference to the port for later access */
    
    return SUCCESS;
}

/***************************************************************************************************************************************//**

    Closes an I2C port.

    @param[in]  port        A pointer to the port to be closed.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The port has been closed.
     ERR_NULLREFERENCE      | The argument 'port' was found to be NULL.
     ERR_INVALIDCONTEXT     | This operation is not supported from the context of an interrupt service routine (ISR).
     ERR_NOTINITIALIZED     | The specified port has not been opened.

    @module     i2c-lpc43xx

*******************************************************************************************************************************************/
STATUS I2C_Close(I2C* port)
{
    INTERRUPTLOCK lock;
    
    
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

    ACQUIREINTERRUPTLOCK();
    
    if (port != mcu_i2c[port->number]) {
        RELEASEINTERRUPTLOCK();
        return ERR_NOTINITIALIZED;
    }

    switch (port->number) {
        case 0:
            IRQ_Disable(IRQ_I2C0);
            REGBITS_SFSI2C0.SCLEZI = 0;
            REGBITS_SFSI2C0.SDAEZI = 0;
            break;
         case 1:
            IRQ_Disable(IRQ_I2C1);
            break;
        default:
            RELEASEINTERRUPTLOCK();
            return ERR_NOTSUPPORTED;
    }

    mcu_i2c[port->number] = NULL;
    
    RELEASEINTERRUPTLOCK();
    return SUCCESS;
}

/***************************************************************************************************************************************//**

    Returns an indication of whether an I2C port is currently open for communications.

    @param[in]  port        A pointer to the target I2C port.

    @return     TRUE if the I2C port is currently open; otherwise FALSE.
    @module     i2c-lpc43xx

*******************************************************************************************************************************************/
BOOLEAN I2C_IsOpen(I2C* port)
{
    INTERRUPTLOCK lock;


#if (CFG_NULLCHECKING)
    if (port == NULL) {
        return FALSE;
    }
#endif

    ACQUIREINTERRUPTLOCK();

    if (mcu_i2c[port->number] == port) {
        RELEASEINTERRUPTLOCK();
        return TRUE;
    }

    RELEASEINTERRUPTLOCK();
    return FALSE;
}

/***************************************************************************************************************************************//**

    Reads and returns data received from an I2C port.

    @param[in]  port        A pointer to the port to receive the data.
    @param[in]  address     The target device address to be read.
    @param[out] buf         A pointer to a caller allocated buffer used to receive the data.
    @param[in]  nbytes      The total number of bytes to be received.
    @param[in]  timeout     The maximum amount of time, in kernel ticks, to block and wait for the transfer to complete. Must not be zero
                            and must be large enough to allow the transfer to complete; based upon clock rate and amount of data being
                            transferred. Use INFINITE to wait indefinitely.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The data was been received.
     ERR_NULLREFERENCE      | The argument 'port' or 'buf' was found to be NULL.
     ERR_INVALIDCONTEXT     | This operation is not supported from the context of an interrupt service routine (ISR).
     ERR_NOTINITIALIZED     | The specified port has not been opened.
     ERR_DEVICENAK          | The target device returned a NAK.
     ERR_INCOMPLETE         | An error occurred while transferring the data and the transfer did not complete.
     ERR_TIMEOUT            | The specified timeout interval has elapsed prior to the transfer being completed.

    @module     i2c-lpc43xx

*******************************************************************************************************************************************/
STATUS I2C_Read(I2C* port, BYTE address, void* buf, UINT32 nbytes, UINT32 timeout)
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

    if (buf == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif

    ACQUIREINTERRUPTLOCK();

    if (mcu_i2c[port->number] != port) {
        RELEASEINTERRUPTLOCK();
        return ERR_NOTINITIALIZED;
    }
    
    RELEASEINTERRUPTLOCK();
    
    status = MUTEX_Acquire(&port->mutex, timeout);                  /* Ensure exclusive access to the port */
    if (status != SUCCESS) {
        return status;
    }
    
    SIGNAL_Clear(&port->signals, SIGNAL_0);

    port->address = (address | 0x1);
    port->data = buf;
    port->nbytes = nbytes;
    port->idx = 0;

    port->REG->CONCLR = 0x2C;
    port->REG->CONSET = 0x20;                                       /* Issue a start condition */

    status = SIGNAL_WaitOne(&port->signals, SIGNAL_0, timeout);     /* Wait for the IRQ to complete the transfer */
    
    MUTEX_Release(&port->mutex);                                    /* Release the claim on the port */
    
    if (status != SUCCESS) {
        return status;                                              /* Failed while waiting for the interrupt to complete */
    }

    return port->status;                                            /* Return the result from the interrupt routine */
}

/***************************************************************************************************************************************//**

    Writes data to an I2C port.

    @param[in]  port        A pointer to the port to be written.
    @param[in]  address     The target device address to be written.
    @param[out] data        A pointer to the data to be written.
    @param[in]  nbytes      The total number of bytes to be written.
    @param[in]  timeout     The maximum amount of time, in kernel ticks, to block and wait for the transfer to complete. Must not be zero
                            and must be large enough to allow the transfer to complete; based upon clock rate and amount of data being
                            transferred. Use INFINITE to wait indefinitely.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The data has been written.
     ERR_NULLREFERENCE      | The argument 'port' or 'data' was found to be NULL.
     ERR_INVALIDCONTEXT     | The operation is not supported from the context of an interrupt service routine (ISR).
     ERR_NOTINITIALIZED     | The specified port has not been opened.
     ERR_DEVICENAK          | The target device returned a NAK.
     ERR_INCOMPLETE         | An error occurred while transferring the data and the transfer did not complete.
     ERR_TIMEOUT            | The specified timeout interval has elapsed prior to the transfer being completed.

    @module     i2c-lpc43xx

*******************************************************************************************************************************************/
STATUS I2C_Write(I2C* port, BYTE address, const void* data, UINT32 nbytes, UINT32 timeout)
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
    
    if (data == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif
   
    ACQUIREINTERRUPTLOCK();
    
    if (mcu_i2c[port->number] != port) {
        RELEASEINTERRUPTLOCK();
        return ERR_NOTINITIALIZED;
    }
    
    RELEASEINTERRUPTLOCK();
    
    status = MUTEX_Acquire(&port->mutex, timeout);              /* Ensure exclusive access to the port */
    if (status != SUCCESS) {
        return status;
    }
    
    SIGNAL_Clear(&port->signals, SIGNAL_0);
    
    port->address = (address & 0xFE);                           /* Keep the target device address (minus the read/write bit) */
    port->data = (void*)data;                                   /* Keep a pointer to the data to be transmitted */
    port->nbytes = nbytes;
    port->idx = 0;

    port->REG->CONCLR = 0x2C;
    port->REG->CONSET = 0x20;                                   /* Issue a start condition */
    
    status = SIGNAL_WaitOne(&port->signals, SIGNAL_0, timeout);
    
    MUTEX_Release(&port->mutex);                                /* Release the claim on the port */
    
    if (status != SUCCESS) {
        return status;                                          /* Failed while waiting for the interrupt to complete */
    }
    
    return port->status;                                        /* Return the result from the interrupt routine */
}

/***************************************************************************************************************************************//**

    Claims exclusive access to an I2C port.

    @param[in]  port        A pointer to the port to be claimed.
    @param[in]  timeout     The maximum amount of time, in kernel ticks, to to block and wait to acquire a exclusive claim on the port. 
                            Use 0 to return immediately without waiting. Use INFINITE to wait indefinitely.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The port has been claimed.
     ERR_NULLREFERENCE      | The argument 'port' was found to be NULL.
     ERR_INVALIDCONTEXT     | The operation is not supported from the context of an interrupt service routine (ISR).
     ERR_NOTINITIALIZED     | The specified port has not been opened.
     ERR_TIMEOUT            | The specified amount of time has elapsed prior to acquiring the claim on the port.

    @module     i2c-lpc43xx

*******************************************************************************************************************************************/
STATUS I2C_Claim(I2C* port, UINT32 timeout)
{
    INTERRUPTLOCK lock;
    
    
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
    
    ACQUIREINTERRUPTLOCK();
    
    if (mcu_i2c[port->number] != port) {
        RELEASEINTERRUPTLOCK();
        return ERR_NOTINITIALIZED;
    }
    
    RELEASEINTERRUPTLOCK();
    return MUTEX_Acquire(&port->mutex, timeout);
}

/***************************************************************************************************************************************//**

    Releases a previous claim on an I2C port.

    @param[in]  port        A pointer to the port to be released.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The claim on the port has been released.
     ERR_NULLREFERENCE      | The argument 'port' was found to be NULL.
     ERR_INVALIDCONTEXT     | This operation is not supported from the context of an interrupt service routine (ISR).
     ERR_NOTINITIALIZED     | The specified port has not been opened.
     ERR_NOTOWNER           | The caller is not the thread that claimed the port. Only the owner is allowed to release the port.

    @module     i2c-lpc43xx

*******************************************************************************************************************************************/
STATUS I2C_Release(I2C* port)
{
    INTERRUPTLOCK lock;
    
    
#if (CFG_NULLCHECKING)
    if (port == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif
    
    ACQUIREINTERRUPTLOCK();
    
    if (mcu_i2c[port->number] != port) {
        RELEASEINTERRUPTLOCK();
        return ERR_NOTINITIALIZED;
    }
    
    RELEASEINTERRUPTLOCK();
    return MUTEX_Release(&port->mutex);
}

/***************************************************************************************************************************************//**

    The interrupt handler for an I2C port.

    @param[in]  port        A pointer to the port that has the pending interrupt request.

    @return     None
    @module     internal

*******************************************************************************************************************************************/
static void I2C_IRQ(IRQ irq)
{
    I2C* port;
    
    
    port = mcu_i2c[irq - IRQ_I2C0];
    
    switch (port->REG->STAT) {
        case 0x08:                                                  /* START has been issued */
        case 0x10:                                                  /* Repeated START has been issued */
            port->REG->DAT = port->address;
            break;

        case 0x18:                                                  /* SLA+W has been transmitted. ACK received. */
        case 0x28:                                                  /* Data byte transmitted. ACK received. */
            port->REG->CONCLR = 0x20;
            if (port->idx < port->nbytes) {
                port->REG->DAT = ((BYTE*)port->data)[port->idx++];  /* Send another data byte */
            } else {
                port->REG->CONSET = 0x10;                           /* Issue a stop condition */
                port->status = SUCCESS;
                SIGNAL_Set(&port->signals, SIGNAL_0);
            }
            port->REG->CONSET = 0x4;
            break;

        case 0x40:                                                  /* SLA+R has been transmitted. ACK received. */
            port->REG->CONCLR = 0x20;
            if (port->idx < (port->nbytes - 1)) {
                port->REG->CONSET = 0x4;                            /* More bytes to receive; return ACK */
            } else {
                port->REG->CONCLR = 0x4;                            /* Last byte to receive; return NAK */
            }
            break;

        case 0x50:                                                  /* Data byte received. ACK returned. */
        case 0x58:                                                  /* Data byte received. NAK returned. */
            ((BYTE*)port->data)[port->idx++] = port->REG->DAT;
            if (port->idx >= port->nbytes) {
                port->REG->CONCLR = 0x4;                            /* Receive completed */
                port->REG->CONSET = 0x10;                           /* Issue a stop condition */

                port->status = SUCCESS;
                SIGNAL_Set(&port->signals, SIGNAL_0);
            } else {
                if (port->idx < (port->nbytes - 1)) {
                    port->REG->CONSET = 0x4;                        /* More bytes to receive; return ACK */
                } else {
                    port->REG->CONCLR = 0x4;                        /* Last byte to receive; return NAK */
                }
            }
            break;

        case 0x20:                                                  /* SLA+W has been transmitted. NAK received. */
        case 0x30:                                                  /* Data byte transmitted. NAK received */
            port->REG->CONSET = 0x10;                               /* Issue a stop condition */
            port->REG->CONCLR = 0x4;
            port->status = ERR_DEVICENAK;
            SIGNAL_Set(&port->signals, SIGNAL_0);
            break;

        default:
            port->REG->CONSET = 0x10;                               /* Issue a stop condition */
            port->REG->CONCLR = 0x4;
            port->status = ERR_INCOMPLETE;
            SIGNAL_Set(&port->signals, SIGNAL_0);
            break;

    }
    
    port->REG->CONCLR = 0x8;                                        /* Clear the interrupt */
}
