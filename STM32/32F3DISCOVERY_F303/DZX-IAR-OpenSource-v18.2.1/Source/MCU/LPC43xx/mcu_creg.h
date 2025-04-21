/*******************************************************************************************************************************************

    DZX | LPC43xx | CREG                                                                                                  VERSION 18.2.1
    ------------------------------------------------------------------------------------------------------------------------------------

    This is part of the MCU peripheral drivers and provides support for the configuration registers (CREG).

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
#ifndef MCU_CREG_H__
#define MCU_CREG_H__

#include "Kernel/kernel.h"

typedef struct CREG0BITFIELD {
    UINT32 EN1KHZ                  :1;
    UINT32 EN32KHZ                 :1;
    UINT32 RESET32KHZ              :1;
    UINT32 PD32KHZ                 :1;
    UINT32                         :1;
    UINT32 USB0PHY                 :1;
    UINT32 ALARMCTRL               :2;
    UINT32 BODLVL1                 :2;
    UINT32 BODLVL2                 :2;
    UINT32                         :20;
} CREG0BITFIELD;

typedef struct CREG5BITFIELD {
    UINT32                         :6;
    UINT32 M3TAPSEL                :1;
    UINT32                         :1;
    UINT32 OTPJTAG                 :1;
    UINT32                         :23;
} CREG5BITFIELD;

typedef struct CREG6BITFIELD {
    UINT32 ETHMODE                 :3;
    UINT32                         :1;
    UINT32 CTOUTCTRL               :1;
    UINT32                         :7;
    UINT32 I2S0TXSCKINSEL          :1;
    UINT32 I2S0RXSCKINSEL          :1;
    UINT32 I2S1TXSCKINSEL          :1;
    UINT32 I2S1RXSCKINSEL          :1;
    UINT32 EMCCLKSEL               :1;
    UINT32                         :15;
} CREG6BITFIELD;

typedef struct FLASHCFGBITFIELD {
    UINT32                         :12;
    UINT32 FLASHTIM                :4;
    UINT32                         :15;
    UINT32 POW                     :1;
} FLASHCFGBITFIELD;

#define REG_CREG0                                 REG_32(0x40043004)
#define REGBITS_CREG0                             REGBITS_32(0x40043004, CREG0BITFIELD)
#define REG_CREG5                                 REG_32(0x40043118)
#define REGBITS_CREG5                             REGBITS_32(0x40043118, CREG5BITFIELD)
#define REG_CREG6                                 REG_32(0x4004312C)
#define REGBITS_CREG6                             REGBITS_32(0x4004312C, CREG6BITFIELD)

#define REG_FLASHCFGA                             REG_32(0x40043120)
#define REGBITS_FLASHCFGA                         REGBITS_32(0x40043120, FLASHCFGBITFIELD)
#define REG_FLASHCFGB                             REG_32(0x40043124)
#define REGBITS_FLASHCFGB                         REGBITS_32(0x40043124, FLASHCFGBITFIELD)

#endif /* MCU_CREG_H__ */
