/*******************************************************************************************************************************************

    DZX | STM32F4xx | SPI                                                                                                 VERSION 18.2.1
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
#ifndef MCU_SPI_H__
#define MCU_SPI_H__

#include "Kernel/kernel.h"
#include "Kernel/kernel_mutex.h"
#include "Kernel/kernel_signal.h"
#include "mcu_pin.h"

/*******************************************************************************************************************************************
    REGISTER DEFINITIONS
*******************************************************************************************************************************************/
#define REG_SPI1        ((REG_SPI*)0x40013000)
#define REG_SPI2        ((REG_SPI*)0x40003800)
#define REG_SPI3        ((REG_SPI*)0x40003C00)
#define REG_SPI4        ((REG_SPI*)0x40013400)
#define REG_SPI5        ((REG_SPI*)0x40015000)

typedef struct SPICR1BITFIELD {
    UINT32 CPHA                     :1;
    UINT32 CPOL                     :1;
    UINT32 MSTR                     :1;
    UINT32 BR                       :3;
    UINT32 SPE                      :1;
    UINT32 LSBFIRST                 :1;
    UINT32 SSI                      :1;
    UINT32 SSM                      :1;
    UINT32 RXONLY                   :1;
    UINT32 DFF                      :1;
    UINT32 CRCNEXT                  :1;
    UINT32 CRCEN                    :1;
    UINT32 BIDIOE                   :1;
    UINT32 BIDIMODE                 :1;
    UINT32                          :16;
} SPICR1BITFIELD;

typedef struct SPICR2BITFIELD {
    UINT32 RXDMAEN                  :1;
    UINT32 TXDMAEN                  :1;
    UINT32 SSOE                     :1;
    UINT32                          :1;
    UINT32 FRF                      :1;
    UINT32 ERRIE                    :1;
    UINT32 RXNEIE                   :1;
    UINT32 TXEIE                    :1;
    UINT32                          :24;
} SPICR2BITFIELD;

typedef struct SPISRBITFIELD {
    UINT32 RXNE                     :1;
    UINT32 TXE                      :1;
    UINT32 CHSIDE                   :1;
    UINT32 UDR                      :1;
    UINT32 CRCERR                   :1;
    UINT32 MODF                     :1;
    UINT32 OVR                      :1;
    UINT32 BSY                      :1;
    UINT32 FRE                      :1;
    UINT32                          :23;
} SPISRBITFIELD;

typedef struct SPII2SCFGRBITFIELD {
    UINT32 CHLEN                    :1;
    UINT32 DATALEN                  :2;
    UINT32 CKPOL                    :1;
    UINT32 I2SSTD                   :2;
    UINT32                          :1;
    UINT32 PCMSYNC                  :1;
    UINT32 I2SCFG                   :2;
    UINT32 I2SE                     :1;
    UINT32 I2SMOD                   :1;
    UINT32                          :20;
} SPII2SCFGRBITFIELD;

typedef struct SPII2SPRBITFIELD {
    UINT32 I2SDIV                   :8;
    UINT32 ODD                      :1;
    UINT32 MCKOE                    :1;
    UINT32                          :22;
} SPII2SPRBITFIELD;
    
typedef struct REG_SPI {
	PREG_BITS32(CR1, SPICR1BITFIELD);
    PREG_BITS32(CR2, SPICR2BITFIELD);
    PREG_BITS32(SR, SPISRBITFIELD);
    PREG_32(DR);
    PREG_32(CRCPR);
    PREG_32(RXCRCR);
    PREG_32(TXCRCR);
    PREG_BITS32(I2SCFG, SPII2SCFGRBITFIELD);
    PREG_BITS32(I2SPR, SPII2SPRBITFIELD);
} REG_SPI;


#define SPI_DEFAULT     0               /* Default clock phase and polarity (clock active LOW and phase on first clock edge) */
#define SPI_CPHA0       0               /* Clock phase control on first clock edge */
#define SPI_CPHA1       1               /* Clock phase control on second clock edge */
#define SPI_CPOL0       0               /* Clock polarity with SCK as active high */
#define SPI_CPOL1       2               /* Clock polarity with SCK as active low */

/*******************************************************************************************************************************************
    TYPE DEFINITIONS
*******************************************************************************************************************************************/
typedef struct STM32F4XX_SPI SPI;       /* Defines the SPI type */

/***************************************************************************************************************************************//**

    A port for SPI communications.
    @module     spi-stm32f4xx

*******************************************************************************************************************************************/
struct STM32F4XX_SPI {
	UINT32      number;         /**< The port number */
    UINT32      mode;
    UINT32      clkHz;
    REG_SPI*    REG;            /**< A pointer to the SPI peripheral registers for the port */
    MUTEX       mutex;          /**< A mutex to acquire exclusive access to the port */
    SIGNALSET   signals;        /**< A set of signals to block/release the thread using the port */
    void*       data;
    void*       buf;
    UINT32      idx;
    UINT32      nbytes;
    STATUS      result;
};

/*******************************************************************************************************************************************
    PUBLIC FUNCTIONS
*******************************************************************************************************************************************/
/***************************************************************************************************************************************//**

    Opens an SPI port for communications.

    The port is opened by powering the peripheral and configuring it's clock for the specified baud rate. Interrupts for the port are
    enabled within the NVIC.

    @param[in]  port        A caller allocated SPI port to be initialized.
    @param[in]  number      The number of the port to be opened (valid values are 1-5).
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
    @module     spi-stm32f4xx

*******************************************************************************************************************************************/
extern STATUS SPI_Open(SPI* port, UINT32 number, UINT32 clkHz, UINT32 mode);

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
    @module     spi-stm32f4xx

*******************************************************************************************************************************************/
extern STATUS SPI_Close(SPI* port);

/***************************************************************************************************************************************//**

    Gets an indication of whether an SPI port is currently open for communications.

    @param[in]  port        A pointer to the target SPI port.

    @return     TRUE if the SPI port is currently open; otherwise FALSE.
    @module     spi-stm32f4xx

*******************************************************************************************************************************************/
extern BOOLEAN SPI_IsOpen(SPI* port);

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

    @module     spi-stm32f4xx

*******************************************************************************************************************************************/
extern STATUS SPI_Select(SPI* port, PIN cs, UINT32 timeout);

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

    @module     spi-stm32f4xx

*******************************************************************************************************************************************/
extern STATUS SPI_Deselect(SPI* port, PIN cs);

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

    @module     spi-stm32f4xx

*******************************************************************************************************************************************/
extern STATUS SPI_Write(SPI* port, const void* data, UINT32 nbytes, UINT32 timeout);

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

    @module     spi-stm32f4xx

*******************************************************************************************************************************************/
extern STATUS SPI_Read(SPI* port, void* buf, UINT32 nbytes, UINT32 timeout);

#endif /* MCU_SPI_H__ */
