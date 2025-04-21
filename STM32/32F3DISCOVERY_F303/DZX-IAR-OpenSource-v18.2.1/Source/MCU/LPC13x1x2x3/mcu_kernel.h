/*******************************************************************************************************************************************

    DZX | LPC13x1x2x3 | KERNEL                                                                                            VERSION 18.2.1
    ------------------------------------------------------------------------------------------------------------------------------------

    This is part of the MCU peripheral drivers and provides the support that is required by the real-time kernel. This configures
    the system clock and performs any required initialization for the peripheral drivers.

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
#ifndef MCU_KERNEL_H__
#define MCU_KERNEL_H__

#include "Kernel/kernel_types.h"

/*******************************************************************************************************************************************
    REGISTER DEFINITIONS
*******************************************************************************************************************************************/
typedef struct PDRUNCFGBITFIELD {
    UINT32 IRCOUTPD                :1;
    UINT32 IRCPD                   :1;
    UINT32 FLASHPD                 :1;
    UINT32 BODPD                   :1;
    UINT32 ADCPD                   :1;
    UINT32 SYSOSCPD                :1;
    UINT32 WDTOSCPD                :1;
    UINT32 SYSPLLPD                :1;
    UINT32 USBPLLPD                :1;
    UINT32                         :1;
    UINT32 USBPADPD                :1;
    UINT32                         :21;
} PDRUNCFGBITFIELD;

typedef struct SYSAHBCLKCTRLBITFIELD {
    UINT32 SYS                     :1;
    UINT32 ROM                     :1;
    UINT32 RAM                     :1;
    UINT32 FLASHREG                :1;
    UINT32 FLASHARRAY              :1;
    UINT32 I2C                     :1;
    UINT32 GPIO                    :1;
    UINT32 CT16B0                  :1;
    UINT32 CT16B1                  :1;
    UINT32 CT32B0                  :1;
    UINT32 CT32B1                  :1;
    UINT32 SSP                     :1;
    UINT32 UART                    :1;
    UINT32 ADC                     :1;
    UINT32 USBREG                  :1;
    UINT32 WDT                     :1;
    UINT32 IOCON                   :1;
    UINT32                         :1;
    UINT32 SSP1                    :1;
    UINT32                         :13;
} SYSAHBCLKCTRLBITFIELD;

typedef struct SYSOSCCTRLBITFIELD {
    UINT32 BYPASS                  :1;
    UINT32 FREQRANGE               :1;
    UINT32                         :30;
} SYSOSCCTRLBITFIELD;

typedef struct SYSPLLCTRLBITFIELD {
    UINT32 MSEL                    :5;
    UINT32 PSEL                    :2;
    UINT32                         :25;
} SYSPLLCTRLBITFIELD;
    
typedef struct SYSPLLSTATBITFIELD {
    UINT32 LOCK                    :1;
    UINT32                         :31;
} SYSPLLSTATBITFIELD;


#define REG_MAINCLKSEL              REG_32(0x40048070)
#define REG_MAINCLKUEN              REG_32(0x40048074)
#define REG_PDRUNCFG                REG_32(0x40048238)
#define REGBITS_PDRUNCFG            REGBITS_32(0x40048238, PDRUNCFGBITFIELD)
#define REG_PRESETCTRL              REG_32(0x40048004)
#define REG_SYSAHBCLKCTRL           REG_32(0x40048080)
#define REGBITS_SYSAHBCLKCTRL       REGBITS_32(0x40048080, SYSAHBCLKCTRLBITFIELD)
#define REG_SYSOSCCTRL              REG_32(0x40048020)
#define REGBITS_SYSOSCCTRL          REGBITS_32(0x40048020, SYSOSCCTRLBITFIELD)
#define REG_SYSPLLCLKSEL            REG_32(0x40048040)
#define REG_SYSPLLCLKUEN            REG_32(0x40048044)
#define REG_SYSPLLCTRL              REG_32(0x40048008)
#define REGBITS_SYSPLLCTRL          REGBITS_32(0x40048008, SYSPLLCTRLBITFIELD)
#define REG_SYSPLLSTAT              REG_32(0x4004800C)
#define REGBITS_SYSPLLSTAT          REGBITS_32(0x4004800C, SYSPLLSTATBITFIELD)

/*******************************************************************************************************************************************
    PUBLIC FUNCTIONS
*******************************************************************************************************************************************/
/***************************************************************************************************************************************//**

    Requests a full-system reset of the MCU.

    @return     Does not return as the system is reset.
    @module     kernel-lpc13x1x2x3

*******************************************************************************************************************************************/
extern void MCU_Reset(void);

/***************************************************************************************************************************************//**

    Returns the frequency, in hertz, of the core CPU clock.

    @return     None.
    @module     kernel-lpc13x1x2x3

*******************************************************************************************************************************************/
extern UINT32 MCU_ClockHz(void);

#endif /* MCU_KERNEL_H__ */
