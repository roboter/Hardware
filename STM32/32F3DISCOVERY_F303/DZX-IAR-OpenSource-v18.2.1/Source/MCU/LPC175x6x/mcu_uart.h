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
#ifndef MCU_UART_H__
#define MCU_UART_H__

#include "Kernel/kernel_buffer.h"
#include "mcu_cfg.h"

/*******************************************************************************************************************************************
    REGISTER DEFINITIONS
*******************************************************************************************************************************************/
#define REG_UART0      ((REG_UART*)0x4000C000)
#define REG_UART1      ((REG_UART*)0x40010000)
#define REG_UART2      ((REG_UART*)0x40098000)
#define REG_UART3      ((REG_UART*)0x4009C000)

typedef struct U0IERBITFIELD {
    UINT32 RDAIE                   :1;
    UINT32 THREIE                  :1;
    UINT32 RXLSIE                  :1;
    UINT32                         :5;
    UINT32 ABEOINTEN               :1;
    UINT32 ABTOINTEN               :1;
    UINT32                         :22;
} U0IERBITFIELD;

typedef struct U0FCRBITFIELD {
    UINT32 FCRFE                   :1;
    UINT32 RFR                     :1;
    UINT32 TFR                     :1;
    UINT32 DMA                     :1;
    UINT32                         :2;
    UINT32 RTLS                    :2;
    UINT32                         :24;
} U0FCRBITFIELD;

typedef struct U0IIRBITFIELD {
    UINT32 IP                      :1;
    UINT32 IID                     :3;
    UINT32                         :2;
    UINT32 IIRFE                   :2;
    UINT32 ABEOINT                 :1;
    UINT32 ABTOINT                 :1;
    UINT32                         :22;
} U0IIRBITFIELD;

typedef struct U0LCRBITFIELD {
    UINT32 WLS                     :2;
    UINT32 SBS                     :1;
    UINT32 PE                      :1;
    UINT32 PS                      :2;
    UINT32 BC                      :1;
    UINT32 DLAB                    :1;
} U0LCRBITFIELD;

typedef struct U0LSRBITFIELD {
    UINT32 DR                      :1;
    UINT32 OE                      :1;
    UINT32 PE                      :1;
    UINT32 FE                      :1;
    UINT32 BI                      :1;
    UINT32 THRE                    :1;
    UINT32 TEMT                    :1;
    UINT32 RXFE                    :1;
} U0LSRBITFIELD;

typedef struct U0ACRBITFIELD {
    UINT32 START                   :1;
    UINT32 MODE                    :1;
    UINT32 AUTORESTART             :1;
    UINT32                         :5;
    UINT32 ABEOINTCLR              :1;
    UINT32 ABTOINTCLR              :1;
    UINT32                         :22;
} U0ACRBITFIELD;

typedef struct U0FDRBITFIELD {
    UINT32 DIVADDVAL               :4;
    UINT32 MULVAL                  :4;
    UINT32                         :24;
} U0FDRBITFIELD;

typedef struct U0TERBITFIELD {
    UINT32                         :7;
    UINT32 TXEN                    :1;
} U0TERBITFIELD;

typedef struct U0FIFOLVLBITFIELD {
    UINT32 RXFIFILVL               :4;
    UINT32                         :4;
    UINT32 TXFIFOLVL               :4;
    UINT32                         :20;
} U0FIFOLVLBITFIELD;

typedef struct U1MSRBITFIELD {
    UINT32 DCTS                    :1;
    UINT32 DDSR                    :1;
    UINT32 TERI                    :1;
    UINT32 DDCD                    :1;
    UINT32 CTS                     :1;
    UINT32 DSR                     :1;
    UINT32 RI                      :1;
    UINT32 DCD                     :1;
} U1MSRBITFIELD;

typedef struct REG_UART {
    
	union {
		PREG_32(RBR);
		PREG_32(THR);
		PREG_32(DLL);
	};

	union {
		PREG_32(DLM);
		PREG_BITS32(IER, U0IERBITFIELD);
	};

	union {
		PREG_BITS32(IIR, U0IIRBITFIELD);
		PREG_BITS32(FCR, U0FCRBITFIELD);
	};

	PREG_BITS32(LCR, U0LCRBITFIELD);
	PREG_32(MCR);
	PREG_BITS32(LSR, U0LSRBITFIELD);
	PREG_BITS32(MSR, U1MSRBITFIELD);
	PREG_32(SCR);
	PREG_BITS32(ACR, U0ACRBITFIELD);
	PREG_32(ICR);
	PREG_BITS32(FDR, U0FDRBITFIELD);
	PREG_32(TER);
} REG_UART;

/*******************************************************************************************************************************************
    TYPE DEFINITIONS
*******************************************************************************************************************************************/
typedef struct LPC175X6X_UART UART;
typedef enum LPC175X6X_STOPBITS STOPBITS;
typedef enum LPC175X6X_PARITY PARITY;
typedef enum LPC175X6X_HANDSHAKE HANDSHAKE;

/***************************************************************************************************************************************//**

    An application-defined function that receives a callback upon data being received by a UART.
    @module     uart-lpc175x6x

*******************************************************************************************************************************************/
typedef void (*UARTRXCALLBACK)(UART* uart, const void* data, UINT32 nbytes);

/***************************************************************************************************************************************//**

    The number of stop bits to be used by a UART.
    @module     uart-lpc175x6x

*******************************************************************************************************************************************/
enum LPC175X6X_STOPBITS {
	STOPBITS_ONE = 0,   /**< Inidicates 1 stop bit */
	STOPBITS_ONE5,      /**< Inidicates 1.5 stop bits */
	STOPBITS_TWO,       /**< Inidicates 2 stop bits */
};

/***************************************************************************************************************************************//**

    The parity to be used by a UART.
    @module     uart-lpc175x6x

*******************************************************************************************************************************************/
enum LPC175X6X_PARITY {
    PARITY_NONE = 0,    /**< Indicates no parity check */
	PARITY_ODD,         /**< Indicates odd parity check */
    PARITY_EVEN,        /**< Indicates even parity check */
	PARITY_MARK,        /**< Indicates mark parity check */
	PARITY_SPACE,       /**< Indicates space parity check */
};

/***************************************************************************************************************************************//**

    The handshake to be used by a UART.
    @module     uart-lpc175x6x

*******************************************************************************************************************************************/
enum LPC175X6X_HANDSHAKE {
	HANDSHAKE_NONE = 0,     /**< No handshake */
	HANDSHAKE_RTSCTS,       /**< Use RTS/CTS flow control */
	HANDSHAKE_XONXOFF,      /**< Use software XON/XOFF flow control */
};

/***************************************************************************************************************************************//**

    A UART port for serial communications.
    @module     uart-lpc175x6x

*******************************************************************************************************************************************/
struct LPC175X6X_UART {
    NODE        node;
	UINT32      number;                         /**< The port number of the UART */
	UINT32      baud;                           /**< The baud rate for the UART */
	REG_UART*   REG;                            /**< A pointer to the peripheral registers for the UART */

    BUFFER      rxb;                            /**< A circular buffer for storing received data */
    BUFFER      txb;                            /**< A circular buffer for storing data to be transmitted */
    BYTE        rxmem[CFG_UARTRXBUFFERSIZE];    /**< Memory allocation for the receive buffer */
    BYTE        txmem[CFG_UARTTXBUFFERSIZE];    /**< Memory allocation for the transmit buffer */
};

/*******************************************************************************************************************************************
    PUBLIC FUNCTIONS
*******************************************************************************************************************************************/
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
extern STATUS UART_Open(UART* uart, UINT32 number, UINT32 baud, UINT32 nbits, STOPBITS stopbits, PARITY parity, HANDSHAKE hs);

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
extern STATUS UART_Close(UART* uart);

/***************************************************************************************************************************************//**

    Gets an indication of whether a UART is currently open for communications.

    @param[in]  uart        A pointer to the target UART.

    @return     TRUE if the uart is currently open; otherwise FALSE.
    @module     uart-lpc175x6x

*******************************************************************************************************************************************/
extern BOOLEAN UART_IsOpen(UART* uart);

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
extern STATUS UART_SetBreak(UART* uart, BOOLEAN active);

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
extern STATUS UART_Clear(UART* uart);

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
extern STATUS UART_Read(UART* uart, void* buf, UINT32 nbytes, UINT32* actual, UINT32 timeout);

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
extern STATUS UART_Write(UART* uart, const void* data, UINT32 nbytes, UINT32* actual, UINT32 timeout);

#endif /* MCU_UART_H__ */
