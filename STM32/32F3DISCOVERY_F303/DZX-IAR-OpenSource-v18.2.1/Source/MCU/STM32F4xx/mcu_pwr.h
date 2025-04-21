/*******************************************************************************************************************************************

    DZX | STM32F4xx | POWER CONTROL (PWR)                                                                                 VERSION 18.2.1
    ------------------------------------------------------------------------------------------------------------------------------------

    This is part of the MCU peripheral drivers and provides the support for the power control block.

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
#ifndef MCU_PWR_H__
#define MCU_PWR_H__

#include "Kernel/kernel.h"

/*******************************************************************************************************************************************
    REGISTER DEFINITIONS
*******************************************************************************************************************************************/
typedef struct PWRCRBITFIELD {
    UINT32 LPDS                    :1;
    UINT32 PDDS                    :1;
    UINT32 CWUF                    :1;
    UINT32 CSBF                    :1;
    UINT32 PVDE                    :1;
    UINT32 PLS                     :3;
    UINT32 DBP                     :1;
    UINT32 FPDS                    :1;
    UINT32                         :3;
    UINT32 ADCDC1                  :1;
    UINT32 VOS                     :2;
    UINT32                         :16;
} PWRCRBITFIELD;

typedef struct PWRCSRBITFIELD {
    UINT32 WUF                     :1;
    UINT32 SBF                     :1;
    UINT32 PVDO                    :1;
    UINT32 BRR                     :1;
    UINT32                         :4;
    UINT32 EWUP                    :1;
    UINT32 BRE                     :1;
    UINT32                         :4;
    UINT32 VOSRDY                  :1;
    UINT32                         :17;
} PWRCSRBITFIELD;

#define REG_PWRCR                                 REG_32(0x40007000)
#define REGBITS_PWRCR                             REGBITS_32(0x40007000, PWRCRBITFIELD)
#define REG_PWRCSR                                REG_32(0x40007004)
#define REGBITS_PWRCSR                            REGBITS_32(0x40007004, PWRCSRBITFIELD)

#endif /* MCU_PWR_H__ */
