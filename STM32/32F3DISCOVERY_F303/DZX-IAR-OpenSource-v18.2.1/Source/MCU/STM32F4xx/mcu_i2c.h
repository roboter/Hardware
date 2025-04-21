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
#ifndef MCU_I2C_H__
#define MCU_I2C_H__

#include "Kernel/kernel.h"
#include "Kernel/kernel_mutex.h"
#include "Kernel/kernel_signal.h"

/*******************************************************************************************************************************************
    REGISTER DEFINITIONS
*******************************************************************************************************************************************/
#define REG_I2C1        ((REG_I2C*)0x40005400)
#define REG_I2C2        ((REG_I2C*)0x40005800)
#define REG_I2C3        ((REG_I2C*)0x40005C00)

typedef struct I2CCR1BITFIELD {
    UINT32 PE                   :1;
    UINT32 SMBUS                :1;
    UINT32                      :1;
    UINT32 SMBTYPE              :1;
    UINT32 ENARP                :1;
    UINT32 ENPEC                :1;
    UINT32 ENGC                 :1;
    UINT32 NOSTRETCH            :1;
    UINT32 START                :1;
    UINT32 STOP                 :1;
    UINT32 ACK                  :1;
    UINT32 POS                  :1;
    UINT32 PEC                  :1;
    UINT32 ALERT                :1;
    UINT32                      :1;
    UINT32 SWRST                :1;
    UINT32                      :16;
} I2CCR1BITFIELD;

typedef struct I2CCR2BITFIELD {
    UINT32 FREQ                 :6;
    UINT32                      :2;
    UINT32 ITERREN              :1;
    UINT32 ITEVTEN              :1;
    UINT32 ITBUFEN              :1;
    UINT32 DMAEN                :1;
    UINT32 LAST                 :1;
    UINT32                      :19;
} I2CCR2BITFIELD;

typedef struct I2CSR1BITFIELD {
    UINT32 SB                   :1;
    UINT32 ADDR                 :1;
    UINT32 BTF                  :1;
    UINT32 ADD10                :1;
    UINT32 STOPF                :1;
    UINT32                      :1;
    UINT32 RXNE                 :1;
    UINT32 TXE                  :1;
    UINT32 BERR                 :1;
    UINT32 ARLO                 :1;
    UINT32 AF                   :1;
    UINT32 OVR                  :1;
    UINT32 PECERR               :1;
    UINT32                      :1;
    UINT32 TIMEOUT              :1;
    UINT32 SMBALERT             :1;
    UINT32                      :16;
} I2CSR1BITFIELD;
    
typedef struct I2CSR2BITFIELD {
    UINT32 MSL                  :1;
    UINT32 BUSY                 :1;
    UINT32 TRA                  :1;
    UINT32                      :1;
    UINT32 GENCALL              :1;
    UINT32 SMBDEFAULT           :1;
    UINT32 SMBHOST              :1;
    UINT32 DUALF                :1;
    UINT32 PEC                  :8;
    UINT32                      :16;
} I2CSR2BITFIELD;

typedef struct I2CCCRBITFIELD {
    UINT32 CCR                  :12;
    UINT32                      :2;
    UINT32 DUTY                 :1;
    UINT32 FS                   :1;
    UINT32                      :16;
} I2CCCRBITFIELD;

typedef struct I2CFLTRBITFIELD {
    UINT32 DNF                  :4;
    UINT32 ANOFF                :1;
    UINT32                      :27;
} I2CFLTRBITFIELD;

typedef struct REG_I2C {
    PREG_BITS32(CR1, I2CCR1BITFIELD);
    PREG_BITS32(CR2, I2CCR2BITFIELD);
    PREG_32(OAR1);
    PREG_32(OAR2);
    PREG_32(DR);
    PREG_BITS32(SR1, I2CSR1BITFIELD);
    PREG_BITS32(SR2, I2CSR2BITFIELD);
    PREG_BITS32(CCR, I2CCCRBITFIELD);
    PREG_32(TRISE);
    PREG_BITS32(FLTR, I2CFLTRBITFIELD);
} REG_I2C;

/*******************************************************************************************************************************************
    TYPE DEFINITIONS
*******************************************************************************************************************************************/
typedef struct STM32F4XX_I2C I2C;               /* Defines the I2C type */

/***************************************************************************************************************************************//**

    A port for I2C communications.
    @module     i2c-stm32f4xx

*******************************************************************************************************************************************/
struct STM32F4XX_I2C {
    REG_I2C*    REG;            /**< A pointer to the peripheral registers for the port */
    BYTE        number;         /**< The port number */
    BYTE        address;        /**< The device address for the current data transfer */
    void*       data;           /**< A pointer to the data for the current transfer */
    UINT16      nbytes;         /**< The total number of bytes within the current transfer */
    UINT16      idx;            /**< An index within the data of the current transfer */
    STATUS      status;         /**< The resulting status of a transfer */
    MUTEX       mutex;          /**< A mutex to achieve exclusive access to the port */
    SIGNALSET   signals;        /**< A set of signals to block/release the thread using the port */
};

/*******************************************************************************************************************************************
    PUBLIC FUNCTIONS
*******************************************************************************************************************************************/
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
extern STATUS I2C_Open(I2C* port, BYTE number, UINT32 clk);

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
extern STATUS I2C_Close(I2C* port);

/***************************************************************************************************************************************//**

    Gets an indication of whether an I2C port is currently open for communications.

    @param[in]  port        A pointer to the target I2C port.

    @return     TRUE if the I2C port is currently open; otherwise FALSE.
    @module     i2c-stm32f4xx

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

    @module     i2c-stm32f4xx

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

    @module     i2c-stm32f4xx

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

    @module     i2c-stm32f4xx

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
     ERR_NOTOWNER           | The caller is not the thread that acquired the port. Only the owner is allowed to release the port.

    @module     i2c-stm32f4xx

*******************************************************************************************************************************************/
extern STATUS I2C_Release(I2C* port);

#endif /* MCU_I2C_H__ */
