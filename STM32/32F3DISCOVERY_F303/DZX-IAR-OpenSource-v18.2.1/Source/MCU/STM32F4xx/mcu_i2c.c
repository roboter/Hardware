/*******************************************************************************************************************************************

    DZX | STM32F4xx | I2C                                                                                                 VERSION 18.2.1
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
#include "mcu_irq.h"
#include "mcu_cfg.h"
#include "mcu_rcc.h"

/*******************************************************************************************************************************************
    PRIVATE VARIABLES
*******************************************************************************************************************************************/
static I2C* mcu_i2c[3];

/*******************************************************************************************************************************************
    PRIVATE FUNCTIONS
*******************************************************************************************************************************************/
static void I2C_IRQ(IRQ irq);

/***************************************************************************************************************************************//**

    Opens an I2C port for communications.

    @param[in]  port        A pointer to a caller allocated I2C port to be opened.
    @param[in]  number      The port number for the port to be opened. (valid values are 1-3)
    @param[in]  clk         The clock frequency in hertz for the port.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The port was successfully opened.
     ERR_INVALIDCONTEXT     | This operation is not supported from the context of an interrupt service routine (ISR).
     ERR_NULLREFERENCE      | The argument 'port' was found to be NULL.
     ERR_NOTSUPPORTED       | An unsupported port number was specified.

    @module     i2c-stm32f4xx

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

    switch (number) {                                       /* By port number, power-on, select clock and enable NVIC interrupt */
        case 1:
            port->REG = REG_I2C1;
            
            
            ACQUIREINTERRUPTLOCK();
            REGBITS_RCCAPB1ENR.I2C1EN = 1;
            RELEASEINTERRUPTLOCK();
            
            IRQ_RegisterHandler(IRQ_I2C1_EV, I2C_IRQ);
            IRQ_RegisterHandler(IRQ_I2C1_ER, I2C_IRQ);
            IRQ_Enable(IRQ_I2C1_EV);
            IRQ_Enable(IRQ_I2C1_ER);
            break;
        case 2:
            port->REG = REG_I2C2;
            
            ACQUIREINTERRUPTLOCK();
            REGBITS_RCCAPB1ENR.I2C2EN = 1;
            RELEASEINTERRUPTLOCK();
            
            IRQ_RegisterHandler(IRQ_I2C2_EV, I2C_IRQ);
            IRQ_Enable(IRQ_I2C2_EV);
            break;
        case 3:
            port->REG = REG_I2C3;
            
            ACQUIREINTERRUPTLOCK();
            REGBITS_RCCAPB1ENR.I2C3EN = 1;
            RELEASEINTERRUPTLOCK();
            
            IRQ_RegisterHandler(IRQ_I2C3_EV, I2C_IRQ);
            IRQ_Enable(IRQ_I2C3_EV);
            break;
        default:
            return ERR_NOTSUPPORTED;
    }
    
    SIGNAL_Init(&port->signals);

    port->REG->CR1.BITS.SWRST = 1;
    port->REG->CR1.BITS.SWRST = 0;
    
    port->REG->CR1.BITS.SMBUS = 0;                          /* Configure for I2C mode (not SMBus mode) */
    port->REG->CR2.BITS.FREQ = MCU_APB1ClockHz() / 1000000; /* Assign the current APB1 clock frequency */
    
    ticks = (MCU_APB1ClockHz() / clk) >> 0;
    port->REG->CCR.BITS.CCR = ticks;
    port->REG->CCR.BITS.FS = 1;
    
    port->REG->CR1.BITS.PE = 1;
    port->REG->CR2.BITS.ITEVTEN = 1;                        /* Enable event interrupts */
    port->REG->CR2.BITS.ITBUFEN = 1;                        /* Enable buffer interrupts */
    port->REG->CR2.BITS.ITERREN = 1;                        /* Enable error interrupts */
  
    port->number = number - 1;                              /* Assign the port number */
    mcu_i2c[number - 1] = port;                             /* Keep a reference to the port for later access */
    
    return SUCCESS;
}

/***************************************************************************************************************************************//**

    Closes an I2C port.

    @param[in]  port        A pointer to the port to be closed.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The port was successfully closed.
     ERR_NULLREFERENCE      | The argument 'port' was found to be NULL.
     ERR_INVALIDCONTEXT     | This operation is not supported from the context of an interrupt service routine (ISR).
     ERR_NOTINITIALIZED     | The specified port has not been initialized (opened).

    @module     i2c-stm32f4xx

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
            IRQ_Disable(IRQ_I2C1_EV);
            break;
         case 1:
            IRQ_Disable(IRQ_I2C2_EV);
            break;
        case 2:
            IRQ_Disable(IRQ_I2C3_EV);
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

    Gets an indication of whether an I2C port is currently open for communications.

    @param[in]  port        A pointer to the target I2C port.

    @return     TRUE if the I2C port is currently open; otherwise FALSE.
    @module     i2c-stm32f4xx

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
    @param[out] buf         A caller allocated buffer used to receive the data.
    @param[in]  nbytes      The total number of bytes to be received.
    @param[in]  timeout     The maximum amount of time, in kernel ticks, to block and wait for the transfer to complete. Must not be zero
                            and must be large enough to allow the transfer to complete; based upon clock rate and amount of data being
                            transferred. Use INFINITE to wait indefinitely.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The data was successfully received.
     ERR_NULLREFERENCE      | The argument 'port' or 'buf' was found to be NULL.
     ERR_INVALIDCONTEXT     | This operation is not supported from the context of an interrupt service routine (ISR).
     ERR_DEVICENAK          | The target device returned a NAK.
     ERR_INCOMPLETE         | An error occurred while transferring the data and the transfer did not complete.

    @module     i2c-stm32f4xx

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

    port->address = (address | 0x1);
    port->data = buf;
    port->nbytes = nbytes;
    port->idx = 0;
    
    SIGNAL_Clear(&port->signals, SIGNAL_0);

    port->REG->CR1.BITS.START = 1;                                  /* Issue a start condition */

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
     SUCCESS                | The data was successfully written.
     ERR_NULLREFERENCE      | The argument 'port' or 'data' was found to be NULL.
     ERR_INVALIDCONTEXT     | This operation is not supported from the context of an interrupt service routine (ISR).
     ERR_NOTINITIALIZED     | The specified port has not been initialized (opened).
     ERR_DEVICENAK          | The target device returned a NAK.
     ERR_INCOMPLETE         | An error occurred while transferring the data and the transfer did not complete.

    @module     i2c-stm32f4xx

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
    
    port->address = (address & 0xFE);                           /* Take the slave device address without the read/write bit */
    port->data = (void*)data;                                   /* Keep a pointer to the data to be transmitted */
    port->nbytes = nbytes;
    port->idx = 0;
    
    SIGNAL_Clear(&port->signals, SIGNAL_0);

    port->REG->CR1.BITS.START = 1;                              /* Issue a start condition */
    
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
     SUCCESS                | The port was successfully claimed.
     ERR_NULLREFERENCE      | The argument 'port' was found to be NULL.
     ERR_INVALIDCONTEXT     | This operation is not supported from the context of an interrupt service routine (ISR).
     ERR_NOTINITIALIZED     | The underlying mutex for the port does not exist within the kernel.
     ERR_TIMEOUT            | The specified amount of time has elapsed while waiting to acquire the claim on the port.

    @module     i2c-stm32f4xx

*******************************************************************************************************************************************/
STATUS I2C_Claim(I2C* port, UINT32 timeout)
{
#if (CFG_NULLCHECKING)
    if (port == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif

    return MUTEX_Acquire(&port->mutex, timeout);
}

/***************************************************************************************************************************************//**

    Releases a previous claim on an I2C port.

    @param[in]  port        A pointer to the port to be released.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The previous claim on the port was successfully released.
     ERR_NULLREFERENCE      | The argument 'port' was found to be NULL.
     ERR_INVALIDCONTEXT     | This operation is not supported from the context of an interrupt service routine (ISR).
     ERR_NOTOWNER           | The caller is not the thread that acquired the port. Only the owner is allowed to release the port.

    @module     i2c-stm32f4xx

*******************************************************************************************************************************************/
STATUS I2C_Release(I2C* port)
{
#if (CFG_NULLCHECKING)
    if (port == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif
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
    static volatile I2CSR1BITFIELD st1;
    static volatile I2CSR2BITFIELD st2;
    
    
    switch (irq) {
        case IRQ_I2C1_EV:
        case IRQ_I2C1_ER:
            port = mcu_i2c[0];
            break;
        case IRQ_I2C2_EV:
        case IRQ_I2C2_ER:
            port = mcu_i2c[1];
            break;
        case IRQ_I2C3_EV:
        case IRQ_I2C3_ER:
            port = mcu_i2c[2];
            break;
    }
    
    st1 = port->REG->SR1.BITS;
    st2 = port->REG->SR2.BITS;
    
    if (st1.SB) {
        port->REG->DR = port->address;
    } else if (st1.ADDR) {
        
        if (st2.TRA) {
            port->REG->DR = ((BYTE*)port->data)[port->idx++];
        } else {
            if (port->nbytes > 1) {
                port->REG->CR1.BITS.ACK = 1;
            } else {
                port->REG->CR1.BITS.ACK = 0;
                port->REG->CR1.BITS.STOP = 1;
            }
        }
    } 
    
    else if (st1.TXE) {
        if (port->idx < port->nbytes) {
            port->REG->DR = ((BYTE*)port->data)[port->idx++];      /* Send another data byte */
        } else {
            port->REG->CR1.BITS.STOP = 1;                            /* Transmit completed */
            port->status = SUCCESS;
            SIGNAL_Set(&port->signals, SIGNAL_0);
        }
    }
    
    else if (st1.RXNE) {
        ((BYTE*)port->data)[port->idx++] = port->REG->DR;
        
        if (port->idx >= port->nbytes) {
            port->REG->CR1.BITS.STOP = 1;                            /* Receive completed */
            port->status = SUCCESS;
            SIGNAL_Set(&port->signals, SIGNAL_0);
        } else {
            if (port->idx < (port->nbytes - 1)) {
                port->REG->CR1.BITS.ACK = 1;                        /* More bytes to receive; return ACK */
            } else {
                port->REG->CR1.BITS.ACK = 0;                        /* Last byte to receive; return NAK */
                port->REG->CR1.BITS.STOP = 1;
            }
        }
    } else {
        port->REG->SR1.VALUE = 0;
        port->REG->CR1.BITS.STOP = 1;
        
        
        if (st1.AF) {
            port->status = ERR_DEVICENAK;
        } else {
            port->status = ERR_INCOMPLETE;
        }
        
        SIGNAL_Set(&port->signals, SIGNAL_0);
    }
}
