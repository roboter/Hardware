/*******************************************************************************************************************************************

    DZX | LPC43xx | SPI                                                                                                   VERSION 18.2.1
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

#include "Kernel/kernel_mutex.h"
#include "Kernel/kernel_signal.h"
#include "mcu_pin.h"

/*******************************************************************************************************************************************
    REGISTER DEFINITIONS
*******************************************************************************************************************************************/
#define REG_SSP0      ((REG_SSP*)0x40083000)
#define REG_SSP1      ((REG_SSP*)0x400C5000)

typedef struct SSP0CR0BITFIELD {
    UINT32 DSS                     :4;
    UINT32 FRF                     :2;
    UINT32 CPOL                    :1;
    UINT32 CPHA                    :1;
    UINT32 SCR                     :8;
    UINT32                         :16;
} SSP0CR0BITFIELD;

typedef struct SSP0CR1BITFIELD {
    UINT32 LBM                     :1;
    UINT32 SSE                     :1;
    UINT32 MS                      :1;
    UINT32 SOD                     :1;
    UINT32                         :28;
} SSP0CR1BITFIELD;

typedef struct SSP0DRBITFIELD {
    UINT32 DATA                    :16;
    UINT32                         :16;
} SSP0DRBITFIELD;

typedef struct SSP0SRBITFIELD {
    UINT32 TFE                     :1;
    UINT32 TNF                     :1;
    UINT32 RNE                     :1;
    UINT32 RFF                     :1;
    UINT32 BSY                     :1;
    UINT32                         :27;
} SSP0SRBITFIELD;

typedef struct SSP0CPSRBITFIELD {
    UINT32 CPSDVSR                 :8;
    UINT32                         :24;
} SSP0CPSRBITFIELD;

typedef struct SSP0IMSCBITFIELD {
    UINT32 RORIM                   :1;
    UINT32 RTIM                    :1;
    UINT32 RXIM                    :1;
    UINT32 TXIM                    :1;
    UINT32                         :28;
} SSP0IMSCBITFIELD;

typedef struct SSP0RISBITFIELD {
    UINT32 RORRIS                  :1;
    UINT32 RTRIS                   :1;
    UINT32 RXRIS                   :1;
    UINT32 TXRIS                   :1;
    UINT32                         :28;
} SSP0RISBITFIELD;

typedef struct SSP0MISBITFIELD {
    UINT32 RORMIS                  :1;
    UINT32 RTMIS                   :1;
    UINT32 RXMIS                   :1;
    UINT32 TXMIS                   :1;
    UINT32                         :28;
} SSP0MISBITFIELD;

typedef struct SSP0ICRBITFIELD {
    UINT32 RORIC                   :1;
    UINT32 RTIC                    :1;
    UINT32                         :30;
} SSP0ICRBITFIELD;

typedef struct SSP0DMACRBITFIELD {
    UINT32 RXDMAE                  :1;
    UINT32 TXDMAE                  :1;
    UINT32                         :30;
} SSP0DMACRBITFIELD;

typedef struct REG_SSP {
	PREG_BITS32(CR0, SSP0CR0BITFIELD);
	PREG_BITS32(CR1, SSP0CR1BITFIELD);
	PREG_BITS32(DR, SSP0DRBITFIELD);
	PREG_BITS32(SR, SSP0SRBITFIELD);
	PREG_BITS32(CPSR, SSP0CPSRBITFIELD);
	PREG_BITS32(IMSC, SSP0IMSCBITFIELD);
	PREG_BITS32(RIS, SSP0RISBITFIELD);
	PREG_BITS32(MIS, SSP0MISBITFIELD);
	PREG_BITS32(ICR, SSP0ICRBITFIELD);
	PREG_BITS32(DMACR, SSP0DMACRBITFIELD);
} REG_SSP;

/*******************************************************************************************************************************************
    TYPE DEFINITIONS
*******************************************************************************************************************************************/
typedef struct LPC43XX_SPI SPI;

/***************************************************************************************************************************************//**

    A port for SPI communications.
    @module     spi-lpc43xx

*******************************************************************************************************************************************/
struct LPC43XX_SPI {
	UINT32      number;         /**< The port number */
    UINT32      mode;
    UINT32      clkHz;
    REG_SSP*    REG;            /**< A pointer to the SSP peripheral registers for the port */
    MUTEX       mutex;          /**< A mutex to acquire exclusive access to the port */
    SIGNALSET   signals;        /**< A set of signals to block/release threads using the port */
    void*       data;
    void*       buf;
    UINT32      idx;
    UINT32      nbytes;
    STATUS      result;
};

#define SPI_DEFAULT     0
#define SPI_CPHA0       0               /* Clock phase control on first clock edge */
#define SPI_CPHA1       1               /* Clock phase control on second clock edge */
#define SPI_CPOL0       0               /* Clock polarity with SCK as active high */
#define SPI_CPOL1       2               /* Clock polarity with SCK as active low */

/*******************************************************************************************************************************************
    PUBLIC FUNCTIONS
*******************************************************************************************************************************************/
extern  STATUS SPI_Open(SPI* port, UINT32 number, UINT32 clkHz, UINT32 mode);
extern  STATUS SPI_Close(SPI* port);
extern BOOLEAN SPI_IsOpen(SPI* port);
extern  STATUS SPI_Select(SPI* port, PIN cs, UINT32 timeout);
extern  STATUS SPI_Deselect(SPI* port, PIN cs);
extern  STATUS SPI_Write(SPI* port, const void* data, UINT32 nbytes, UINT32 timeout);
extern  STATUS SPI_Read(SPI* port, void* buf, UINT32 nbytes, UINT32 timeout);

#endif /* MCU_SPI_H__ */
