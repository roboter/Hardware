/*******************************************************************************************************************************************

    DZX | LPC175x6x | UART                                                                                                VERSION 18.2.1
    ------------------------------------------------------------------------------------------------------------------------------------

    This is part of the MCU peripheral drivers and provides support for the UART ports.

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
#include "mcu_uart.h"
#include "mcu_irq.h"
#include "mcu_scu.h"


/*******************************************************************************************************************************************
    PRIVATE DEFINITIONS
*******************************************************************************************************************************************/
#define UARTBAUDPRECISION           10000                               /* The precision of the UART baud calculation */
#define UARTFIFOSIZE                16                                  /* The size of the UART hardware's fifo */

/*******************************************************************************************************************************************
    PRIVATE VARIABLES
*******************************************************************************************************************************************/
static UART* mcu_uart[4];

/*******************************************************************************************************************************************
    PRIVATE FUNCTIONS
*******************************************************************************************************************************************/
static void UART_SetBaud(UART* uart);
static void UART_IRQ(IRQ irq);
       
/***************************************************************************************************************************************//**

    Initializes and opens a UART for communications.

    @param[in]  uart        A caller allocated uart to be opened.
    @param[in]  number      The uart number to be opened.
    @param[in]  baud        The baud rate in bits per second for the uart.
    @param[in]  nbits       The number of bits per byte transmitted and received (5-8).
    @param[in]  stopbits    The number of stopbits to be used.

     STOPBITS               | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     STOPBITS_ONE           | Use 1 stop bit
     STOPBITS_ONE5          | Use 1.5 stop bits
     STOPBITS_TWO           | Use 2 stop bits

    @param[in]  parity     The parity check to be used by the uart.

     PARITY                 | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     PARITY_NONE            | No parity check
     PARITY_EVENT           | Use even parity check
     PARITY_ODD             | Use odd parity check
     PARITY_MARK            | Use mark parity check
     PARITY_SPACE           | Use space parity check

    @param[in]  hs          The handshake to be used by the uart.

     HANDSHAKE              | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     HANDSHAKE_NONE         | No handshake.
     HANDSHAKE_RTSCTS       | Use RTS/CTS hardware flow control.
     HANDSHAKE_XONXOFF      | Use XON/XOFF software flow control.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The UART was initialized and is open for communications.
     ERR_INVALIDCONTEXT     | The operation is not supported from the context of an interrupt service routine (ISR).
     ERR_NULLREFERENCE      | The argument 'uart' was found to be NULL.
     ERR_NOTSUPPORTED       | An unsupported port number, nbits, stopbits, parity or handshake was specified.
     ERR_ACCESSDENIED       | The specified port number is already in use.

    @remark     Not thread safe.
    @remark     Cannot be called from ISR.
    @module     uart-lpc175x6x

*******************************************************************************************************************************************/
STATUS UART_Open(UART* uart, UINT32 number, UINT32 baud, UINT32 nbits, STOPBITS stopbits, PARITY parity, HANDSHAKE hs)
{
    INTERRUPTLOCK lock;
    STATUS status;


#if (CFG_CONTEXTCHECKING)
    if (KERNEL_IsISR()) {
        return ERR_INVALIDCONTEXT;
    }
#endif
#if (CFG_NULLCHECKING)
    if (uart == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif
   
    if (number >= 4) {                                          /* A valid port number? */
        return ERR_NOTSUPPORTED;                                 /* Unsupported port */
    }
    
    if (mcu_uart[number]) {                                     /* Is the specified port already open? */
        return ERR_ACCESSDENIED;                                 /* Already open */
    }
   
    switch (number) {                                           /* Power up the UART and set peripheral clock frequency */
        case 0:
            uart->REG = REG_UART0;
            REGBITS_PCONP.PCUART0 = 1;
            REGBITS_PCLKSEL0.PCLKUART0 = 1;
            IRQ_RegisterHandler(IRQ_UART0, UART_IRQ);
            IRQ_Enable(IRQ_UART0);
            break;
        case 1:
            uart->REG = REG_UART1;
            REGBITS_PCONP.PCUART1 = 1;
            REGBITS_PCLKSEL0.PCLKUART1 = 1;
            IRQ_RegisterHandler(IRQ_UART1, UART_IRQ);
            IRQ_Enable(IRQ_UART1);
            break;
        case 2:
            uart->REG = REG_UART2;
            REGBITS_PCONP.PCUART2 = 1;
            REGBITS_PCLKSEL1.PCLKUART2 = 1;
            IRQ_RegisterHandler(IRQ_UART2, UART_IRQ);
            IRQ_Enable(IRQ_UART2);
            break;
        case 3:
            uart->REG = REG_UART3;
            REGBITS_PCONP.PCUART3 = 1;
            REGBITS_PCLKSEL1.PCLKUART3 = 1;
            IRQ_RegisterHandler(IRQ_UART3, UART_IRQ);
            IRQ_Enable(IRQ_UART3);
            break;
        default:
            return ERR_NOTSUPPORTED;
    }

    uart->number = number;
    uart->baud = baud;

#if (CFG_UARTRXBUFFERSIZE > 0)
    status = BUFFER_Create(&uart->rxb,                          /* Create the receive buffer */
                           "UART RX",
                           uart->rxmem, 
                           CFG_UARTRXBUFFERSIZE);
    
    if (status != SUCCESS) {
        return status;
    }
#endif
    
#if (CFG_UARTTXBUFFERSIZE > 0)
    status = BUFFER_Create(&uart->txb,                          /* Create the transmit buffer */
                           "UART TX",
                           uart->txmem, 
                           CFG_UARTTXBUFFERSIZE);
    
    if (status != SUCCESS) {
        return status;
    }
#endif
    
    UART_SetBaud(uart);                                         /* Configure the baud rate for the uart */

    switch (nbits) {                                            /* Set the bits-per-byte */
        case 5:
            uart->REG->LCR.BITS.WLS = 0;
            break;
        case 6:
            uart->REG->LCR.BITS.WLS = 1;
            break;
        case 7:
            uart->REG->LCR.BITS.WLS = 2;
            break;
        case 8:
            uart->REG->LCR.BITS.WLS = 3;
            break;
        default:
            return ERR_NOTSUPPORTED;
    }

    switch (stopbits) {                                         /* Setup the stop bits */
        case STOPBITS_ONE:                                      /* Use one stop bit */
            uart->REG->LCR.BITS.SBS = 0;
            break;
        case STOPBITS_ONE5:                                     /* Use one and a half stop bits */
            uart->REG->LCR.BITS.SBS = 1;
            uart->REG->LCR.BITS.WLS = 0;                        /* 1.5 stop bits requires 5-bit byteSize */
            break;
        case STOPBITS_TWO:                                      /* Use two stop bits */
            uart->REG->LCR.BITS.SBS = 1;
            break;
        default:
            return ERR_NOTSUPPORTED;
    }

    switch (parity) {                                           /* Setup the parity */
        case PARITY_ODD:
            uart->REG->LCR.BITS.PS = 0;
            uart->REG->LCR.BITS.PE = 1;
            break;
        case PARITY_EVEN:
            uart->REG->LCR.BITS.PS = 1;
            uart->REG->LCR.BITS.PE = 1;
            break;
        case PARITY_MARK:
            uart->REG->LCR.BITS.PS = 2;
            uart->REG->LCR.BITS.PE = 1;
            break;
        case PARITY_SPACE:
            uart->REG->LCR.BITS.PS = 3;
            uart->REG->LCR.BITS.PE = 1;
            break;
        case PARITY_NONE:
            uart->REG->LCR.BITS.PE = 0;
            break;
        default:
            return ERR_NOTSUPPORTED;
    }

    ACQUIREINTERRUPTLOCK();
    
    mcu_uart[uart->number] = uart;
    
    RELEASEINTERRUPTLOCK();

    uart->REG->FCR.BITS.FCRFE = 1;                          /* Enable FIFO's for the uart */
    uart->REG->FCR.BITS.RTLS = 2;                           /* Receive interrupt level at 8 characters */
    uart->REG->IER.BITS.RDAIE = 1;                          /* Enable the receive interrupt */

    return SUCCESS;
}

/***************************************************************************************************************************************//**

    Closes and releases all resources used by a UART.

    @param[in]  uart        A pointer to the UART to be closed.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The UART was successfully closed.
     ERR_NULLREFERENCE       | The argument 'uart' was found to be NULL.

    @module     uart-lpc175x6x

*******************************************************************************************************************************************/
STATUS UART_Close(UART* uart)
{
    INTERRUPTLOCK lock;
    
    
#if (CFG_NULLCHECKING)
    if (uart == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif

    uart->REG->IER.VALUE = 0;               /* Clear the interrupt enables for the UART */

    switch (uart->number) {
        case 0:
            IRQ_Disable(IRQ_UART0);         /* Disable the NVIC interrupt */
            REGBITS_PCONP.PCUART0 = 0;      /* Power down the peripheral */
            break;
        case 1:
            IRQ_Disable(IRQ_UART1);         /* Disable the NVIC interrupt */
            REGBITS_PCONP.PCUART1 = 0;      /* Power down the peripheral */
            break;
        case 2:
            IRQ_Disable(IRQ_UART2);         /* Disable the NVIC interrupt */
            REGBITS_PCONP.PCUART2 = 0;      /* Power down the peripheral */
            break;
        case 3:
            IRQ_Disable(IRQ_UART3);         /* Disable the NVIC interrupt */
            REGBITS_PCONP.PCUART3 = 0;      /* Power down the peripheral */
            break;
    }

    BUFFER_Destroy(&uart->rxb);

    ACQUIREINTERRUPTLOCK();
    
    mcu_uart[uart->number] = NULL;
    
    RELEASEINTERRUPTLOCK();
    return SUCCESS;
}

/***************************************************************************************************************************************//**

    Configures and assigns the given baud rate to a UART

    @param[in]  uart        A pointer to the UART to be assigned the baud rate.
    @param[in]  baud        The new baud rate in bits per second for the UART.

    @return     None
    @module     internal

*******************************************************************************************************************************************/
static void UART_SetBaud(UART* uart)
{
    UINT32 mval;
    UINT32 dval;
    UINT32 divisor;
    UINT32 base;
    UINT32 error;
    UINT32 minerror = 0xFFFFFFFF;


    base = (UINT32)(((UINT64)CFG_CPUCLOCKHZ * UARTBAUDPRECISION) / (uart->baud * 16));      /* Calculate a base divisor */
    uart->REG->LCR.BITS.DLAB = 1;                          /* Allow access to the fractional divisor latches */

    for (mval = 1; mval < 16; mval++) {                    /* Attempt each possible fractional multiplier */
        for (dval = 0; dval < mval; dval++) {              /* Attempt each possible fractional divider */
            divisor = (base * mval) / (mval + dval);       /* Calc the ideal divisor with extra precision */
            error = divisor % UARTBAUDPRECISION;           /* Use the extra precision to determine the amount of error */

            if (error > (UARTBAUDPRECISION / 2)) {
                error = UARTBAUDPRECISION - error;         /* Correct the error to reflect both negative and positive */
            }

            if (error < minerror) {                        /* Check if this attempt has been the best fit */
                divisor += (UARTBAUDPRECISION / 2);        /* Round the divisor up by adding half of the fixed precision */
                divisor /= UARTBAUDPRECISION;              /* Remove the fixed precision */

                uart->REG->DLM = (divisor >> 8) & 0xFF;    /* Set the upper divider byte */
                uart->REG->DLL = (divisor & 0xFF);         /* Set the lower divider byte */
                uart->REG->FDR.BITS.MULVAL = mval;         /* Assign fractional multiplier */
                uart->REG->FDR.BITS.DIVADDVAL = dval;      /* Assign fractional divider */

                minerror = error;                          /* Mark as the best error to eliminate next time around */
            }
        }
    }
    uart->REG->LCR.BITS.DLAB = 0;                          /* Disable access to the divisor latches */
}

/***************************************************************************************************************************************//**

    Gets an indication of whether a UART is currently open for communications.

    @param[in]  uart        A pointer to the target UART.

    @return     TRUE if the uart is currently open; otherwise FALSE.
    @module     uart-lpc175x6x

*******************************************************************************************************************************************/
BOOLEAN UART_IsOpen(UART* uart)
{
#if (CFG_NULLCHECKING)
    if (uart == NULL) {
        return FALSE;
    }
#endif
    
    return (mcu_uart[uart->number] == uart);
}

/***************************************************************************************************************************************//**

    Clears and removes all data from the UART's receive buffer.

    @param[in]  uart        A pointer to the UART to be cleared.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The UART was successfully flushed.
     ERR_NULLREFERENCE       | The argument 'uart' was found to be NULL.

    @module     uart-lpc175x6x

*******************************************************************************************************************************************/
STATUS UART_Clear(UART* uart)
{
    INTERRUPTLOCK lock;


#if (CFG_NULLCHECKING)
    if (uart == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif

    ACQUIREINTERRUPTLOCK();
    uart->REG->FCR.BITS.RFR = 1;        /* Empty the hardware receive FIFO */
    RELEASEINTERRUPTLOCK();
    
    BUFFER_Clear(&uart->rxb);           /* Empty the software buffer for receiving */
    
    return SUCCESS;
}
    
/***************************************************************************************************************************************//**

    Attempts to read data from the transmit buffer and writes the data to the UART.

    @param[in]  uart        A pointer to the target UART.

    @return     The number of bytes that were transferred to the UART.
    @module     internal

*******************************************************************************************************************************************/
static UINT32 UART_WriteFIFO(UART* uart)
{
    INTERRUPTLOCK lock;
    UINT32 k;
    UINT32 num;
    BYTE buf[UARTFIFOSIZE];
    
    
    BUFFER_Read(&uart->txb, buf, UARTFIFOSIZE, &num, 0);        /* Attempt to read data from the transmit buffer */
    if (num > 0) {                                              /* Any data to be transmitted? */
        
        ACQUIREINTERRUPTLOCK();
        
        for (k = 0; k < num; k++) {                             /* Yes, load the data into the hardware FIFO */
            uart->REG->THR = ((BYTE*)buf)[k];
        }
        
        RELEASEINTERRUPTLOCK();
    }
    
    return num;
}

/***************************************************************************************************************************************//**

    Writes data to be transmitted by a UART. The data is written to an underlying circular buffer and is queued for transmission by
    interrupt. This call will block for the maximum amount of time specified if the buffer happens to be full.

    @param[in]  uart        A pointer to the UART that will transmit the data.
    @param[in]  data        A pointer to the data to be transmitted.
    @param[in]  nbytes      The total number of bytes to be transmitted.
    @param[out] actual      A pointer to a caller allocated value used to determine the actual number of bytes that have been queued for
                            transmission. Use 'NULL' to force either all or none of the data to be written.
    @param[in]  timeout     The maximum amount of time, in kernel ticks, to block the calling thread and wait if the transmit buffer
                            happens to be full. Use '0' to return immediately without waiting and use 'INFINITE' to wait indefinitely.
    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The data was successfully queued for transmission.
     ERR_NULLREFERENCE      | The argument 'uart' or 'data' was found to be NULL.
     ERR_NOTINITIALIZED     | The specified port has not been initialized (opened).
     ERR_TIMEOUT            | The maximum amount of time has elapsed before the data could be queued for transmission.

    @module     uart-lpc175x6x

*******************************************************************************************************************************************/
STATUS UART_Write(UART* uart, const void* data, UINT32 nbytes, UINT32* actual, UINT32 timeout)
{
    INTERRUPTLOCK lock;
    STATUS status;

    
#if (CFG_NULLCHECKING)
    if (uart == NULL) {
        return ERR_NULLREFERENCE;
    }
    
    if (data == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif
   
    ACQUIREINTERRUPTLOCK();
    
    if (mcu_uart[uart->number] != uart) {
        RELEASEINTERRUPTLOCK();
        return ERR_NOTINITIALIZED;
    }
       
    RELEASEINTERRUPTLOCK();

    status = BUFFER_Write(&uart->txb, data, nbytes, actual, timeout);
    
    if (status != SUCCESS) {
        return status;
    }
    
    ACQUIREINTERRUPTLOCK();
    if (uart->REG->IER.BITS.THREIE == 0) {
        if (uart->txb.count > 0) {
            uart->REG->IER.BITS.THREIE = 1;
            RELEASEINTERRUPTLOCK();
            UART_WriteFIFO(uart);
            return SUCCESS;
            
        }
    }
    
    RELEASEINTERRUPTLOCK();
    return SUCCESS;
}

/***************************************************************************************************************************************//**

    Reads and returns any available data that has been received by a UART.

    @param[in]  uart        A pointer to the UART that will receive the data to be returned.
    @param[in]  buf         A pointer to a caller allocated buffer to retrieve the returned data.
    @param[in]  nbytes      The total number of bytes to be received.
    @param[out] actual      A pointer to a caller allocated value used to determine the actual number of bytes that have been returned.
                            Use 'NULL' to only return either all or none of the requested amount.
    @param[in]  timeout     The maximum amount of time, in kernel ticks, to block the calling thread and wait for the requested amount of 
                            data to be received. Use '0' to return immediately without blocking. Use 'INFINITE' to block indefinitely.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The operation completed successfully. Use argument 'actual' to determine the number of bytes returned.
     ERR_NULLREFERENCE      | The argument 'b', 'buf' or 'actual' was found to be NULL.
     ERR_NOTINITIALIZED     | The specified uart has not been initialized (created).

    @module     uart-lpc175x6x

*******************************************************************************************************************************************/
STATUS UART_Read(UART* uart, void* buf, UINT32 nbytes, UINT32* actual, UINT32 timeout)
{
#if (CFG_NULLCHECKING)
    if (uart == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif
    
    if (mcu_uart[uart->number] != uart) {
        return ERR_NOTINITIALIZED;
    }
    
    return BUFFER_Read(&uart->rxb, buf, nbytes, actual, timeout);
}

/***************************************************************************************************************************************//**

    Sets or clears a break signal on a UART.

    @param[in]  uart        A pointer to the target UART.
    @param[in]  active      Use TRUE to set the break signal. Use FALSE to clear the break signal.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The uart was successfully configured to drive a break signal 
     ERR_NULLREFERENCE      | The argument 'uart' was found to be NULL.
     ERR_NOTINITIALIZED     | The specified uart has not been initialized (opened). 

    @module     uart-lpc175x6x

*******************************************************************************************************************************************/
STATUS UART_SetBreak(UART* uart, BOOLEAN active)
{
    INTERRUPTLOCK lock;
    
    
#if (CFG_NULLCHECKING)
    if (uart == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif
    
    ACQUIREINTERRUPTLOCK();
    
    if (mcu_uart[uart->number] != uart) {
        RELEASEINTERRUPTLOCK();
        return ERR_NOTINITIALIZED;
    }
    
    if (active) {
        uart->REG->LCR.BITS.BC = 1;                             /* Enable break transmission */
    } else {
        uart->REG->LCR.BITS.BC = 0;                             /* Disable break transmission */
    }
    
    RELEASEINTERRUPTLOCK();
    return SUCCESS;
}

/*******************************************************************************************************************************************

    Interrupt request handler for a UART.

    @param[in]  irq         The interrupt request to be handled.

    @return     None
    @module     internal

*******************************************************************************************************************************************/
static void UART_IRQ(IRQ irq)
{
    BYTE buf[UARTFIFOSIZE];
    UINT32 num;
    UART* uart;

        
    switch (irq) {
        case IRQ_UART0:
            uart = mcu_uart[0];
            break;
        case IRQ_UART1:
            uart = mcu_uart[1];
            break;
        case IRQ_UART2:
            uart = mcu_uart[2];
            break;
        case IRQ_UART3:
            uart = mcu_uart[3];
            break;
        default:
            return;
    }   

    switch (uart->REG->IIR.BITS.IID) {                                  /* Determine the source of the interrupt */
        case 0x1:                                                       /* THRE Interrupt */
        
            num = UART_WriteFIFO(uart);                                 /* Attempt to write more data */
            if (num == 0) {                                             /* Is the transfer complete? */
                uart->REG->IER.BITS.THREIE = 0;                         /* Disable further transmit interrupts */
            }
            break;
            
        case 0x2:                                                       /* Receive Data Available Interrupt (RDA) */
        case 0x6:                                                       /* Character Time-out Indicator Interrupt (CTI) */
        
            num = 0;
            while (uart->REG->LSR.BITS.DR == 1) {                       /* Empty the receive FIFO */
                buf[num++] = uart->REG->RBR;
                if (num >= UARTFIFOSIZE) {
                    break;
                }
            }
            
            BUFFER_Write(&uart->rxb, buf, num, NULL, 0);                /* Buffer the received data */
            break;
            
        case 0x3:                                                       /* Receive Line Status Interrupt (RLS) */
        case 0x0:                                                       /* Reserved */
        case 0x4:                                                       /* Reserved */
        case 0x5:                                                       /* Reserved */
        case 0x7:                                                       /* Reserved */
        default:
            break;
    }
}
