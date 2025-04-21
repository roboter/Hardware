/*******************************************************************************************************************************************

    DZX | LPC13x1x2x3 | I2C                                                                                               VERSION 18.2.1
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
#ifndef MCU_I2C_H__
#define MCU_I2C_H__

#include "Kernel/kernel_mutex.h"
#include "Kernel/kernel_signal.h"

/*******************************************************************************************************************************************
    REGISTER DEFINITIONS
*******************************************************************************************************************************************/
#define REG_I2C0     ((REG_I2C*)0x40000000)

typedef struct I2C0ADR0BITFIELD {
    UINT32 GC                      :1;
    UINT32 ADDR                    :7;
    UINT32                         :24;
} I2C0ADR0BITFIELD;

typedef struct I2C0MMCTRLBITFIELD {
    UINT32 MMENA                   :1;
    UINT32 ENASCL                  :1;
    UINT32 MATCHALL                :1;
    UINT32                         :29;
} I2C0MMCTRLBITFIELD;

typedef struct I2C0ADR1BITFIELD {
    UINT32 GC                      :1;
    UINT32 ADDR                    :7;
    UINT32                         :24;
} I2C0ADR1BITFIELD;

typedef struct I2C0ADR2BITFIELD {
    UINT32 GC                      :1;
    UINT32 ADDR                    :7;
    UINT32                         :24;
} I2C0ADR2BITFIELD;

typedef struct I2C0ADR3BITFIELD {
    UINT32 GC                      :1;
    UINT32 ADDR                    :7;
    UINT32                         :24;
} I2C0ADR3BITFIELD;

typedef struct I2C0DATABUFFERBITFIELD {
    UINT32 DATA                    :8;
    UINT32                         :24;
} I2C0DATABUFFERBITFIELD;

typedef struct I2C0MASK0BITFIELD {
    UINT32                         :1;
    UINT32 MASK                    :7;
    UINT32                         :24;
} I2C0MASK0BITFIELD;

typedef struct I2C0MASK1BITFIELD {
    UINT32                         :1;
    UINT32 MASK                    :7;
    UINT32                         :24;
} I2C0MASK1BITFIELD;

typedef struct I2C0MASK2BITFIELD {
    UINT32                         :1;
    UINT32 MASK                    :7;
    UINT32                         :24;
} I2C0MASK2BITFIELD;

typedef struct I2C0MASK3BITFIELD {
    UINT32                         :1;
    UINT32 MASK                    :7;
    UINT32                         :24;
} I2C0MASK3BITFIELD;

typedef struct REG_I2C {
	PREG_32(CONSET);
	PREG_32(STAT);
	PREG_32(DAT);
	PREG_BITS32(ADR0, I2C0ADR0BITFIELD);
	PREG_32(SCLH);
	PREG_32(SCLL);
	PREG_32(CONCLR);
	PREG_BITS32(MMCTRL, I2C0MMCTRLBITFIELD);
	PREG_BITS32(ADR1, I2C0ADR1BITFIELD);
	PREG_BITS32(ADR2, I2C0ADR2BITFIELD);
	PREG_BITS32(ADR3, I2C0ADR3BITFIELD);
	PREG_BITS32(DATABUFFER, I2C0DATABUFFERBITFIELD);
	PREG_BITS32(MASK0, I2C0MASK0BITFIELD);
	PREG_BITS32(MASK1, I2C0MASK1BITFIELD);
	PREG_BITS32(MASK2, I2C0MASK2BITFIELD);
	PREG_BITS32(MASK3, I2C0MASK3BITFIELD);
} REG_I2C;

/*******************************************************************************************************************************************
    TYPE DEFINITIONS
*******************************************************************************************************************************************/
typedef struct LPC13X1X2X3_I2C I2C;

/***************************************************************************************************************************************//**

    A port for I2C communications.
    @module     i2c-lpc13x1x2x3

*******************************************************************************************************************************************/
struct LPC13X1X2X3_I2C {
    REG_I2C*    REG;            /**< A pointer to the peripheral registers for the port */
    BYTE        number;         /**< The port number */
    BYTE        address;        /**< The device address for the current data transfer */
    void*       data;           /**< A pointer to the data for the current transfer */
    UINT16      nbytes;         /**< The total number of bytes within the current transfer */
    UINT16      idx;            /**< An index within the data of the current transfer */
    STATUS      status;         /**< The resulting status of a transfer */
    MUTEX       mutex;          /**< A mutex to achieve exclusive access to the port */
    SIGNALSET   signals;        /**< A set of signals to block/release threads using the port */
};

/*******************************************************************************************************************************************
    PUBLIC FUNCTIONS
*******************************************************************************************************************************************/
/***************************************************************************************************************************************//**

    Opens an I2C port for communications.

    @param[in]  port        A pointer to a caller allocated I2C port to be opened.
    @param[in]  number      The port number for the port to be opened.
    @param[in]  clk         The clock frequency in hertz for the port.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The port was successfully opened.
     ERR_INVALIDCONTEXT     | This operation is not supported from the context of an interrupt service routine (ISR).
     ERR_NULLREFERENCE      | The argument 'port' was found to be NULL.
     ERR_NOTSUPPORTED       | An unsupported port number was specified.

    @module     i2c-lpc13x1x2x3

*******************************************************************************************************************************************/
extern STATUS I2C_Open(I2C* port, BYTE number, UINT clk);

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

    @module     i2c-lpc13x1x2x3

*******************************************************************************************************************************************/
extern STATUS I2C_Close(I2C* port);

/***************************************************************************************************************************************//**

    Gets an indication of whether an I2C port is currently open for communications.

    @param[in]  port        A pointer to the target I2C port.

    @return     TRUE if the I2C port is currently open; otherwise FALSE.
    @module     i2c-lpc13x1x2x3

*******************************************************************************************************************************************/
extern BOOLEAN I2C_IsOpen(I2C* port);

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

    @module     i2c-lpc13x1x2x3

*******************************************************************************************************************************************/
extern STATUS I2C_Read(I2C* port, BYTE address, void* buf, UINT32 nbytes, UINT32 timeout);

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

    @module     i2c-lpc13x1x2x3

*******************************************************************************************************************************************/
extern STATUS I2C_Write(I2C* port, BYTE address, const void* data, UINT32 nbytes, UINT32 timeout);

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

    @module     i2c-lpc13x1x2x3

*******************************************************************************************************************************************/
extern STATUS I2C_Claim(I2C* port, UINT32 timeout);

/***************************************************************************************************************************************//**

    Releases a previous claim on an I2C port.

    @param[in]  port        A pointer to the port to be released.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The previous claim on the port was successfully released.
     ERR_NULLREFERENCE      | The argument 'port' was found to be NULL.
     ERR_INVALIDCONTEXT     | This operation is not supported from the context of an interrupt service routine (ISR).
     ERRCALLERNOTTHREAD   | The caller must be a thread to release the lock (not ISR or mainline code).
     ERRCALLERNOTOWNER    | The caller is not the owner of the lock and therefore cannot be released.

    @module     i2c-lpc13x1x2x3

*******************************************************************************************************************************************/
extern STATUS I2C_Release(I2C* port);

#endif /* MCU_I2C_H__ */
