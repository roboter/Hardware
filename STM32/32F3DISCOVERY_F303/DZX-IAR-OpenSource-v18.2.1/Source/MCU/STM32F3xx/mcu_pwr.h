/*******************************************************************************************************************************************

    DZX | STM32F3xx | POWER CONTROL (PWR)                                                                                 VERSION 18.2.1
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
#define BASE_PWR                0x40007000

/*******************************************************************************************************************************************

    CR: power control register

*******************************************************************************************************************************************/
typedef struct PWRCRBITFIELD {
    UINT32 LPDS                 :1;                             /* Low-power deep sleep */
    UINT32 PDDS                 :1;                             /* Power down deepsleep */
    UINT32 CWUF                 :1;                             /* Clear wakeup flag */
    UINT32 CSBF                 :1;                             /* Clear standby flag */
    UINT32 PVDE                 :1;                             /* Power voltage detector enable */
    UINT32 PLS                  :3;                             /* PVD level selection */
    UINT32 DBP                  :1;                             /* Disable backup domain write protection */
    UINT32                      :23;
} PWRCRBITFIELD;

#define REG_PWRCR               REG_32(BASE_PWR + 0x000)
#define REGBITS_PWRCR           REGBITS_32(BASE_PWR + 0x000, PWRCRBITFIELD)

/*******************************************************************************************************************************************

    CSR: power control/status register

*******************************************************************************************************************************************/
typedef struct PWRCSRBITFIELD {
    UINT32 WUF                  :1;                             /* Wakeup flag */
    UINT32 SBF                  :1;                             /* Standby flag */
    UINT32 PVDO                 :1;                             /* PVD output */
    UINT32                      :5;
    UINT32 EWUP1                :1;                             /* Enable WKUP1 pin */
    UINT32 EWUP2                :1;                             /* Enable WKUP2 pin */
    UINT32                      :22;
} PWRCSRBITFIELD;

#define REG_PWRCSR              REG_32(BASE_PWR + 0x004)
#define REGBITS_PWRCSR          REGBITS_32(BASE_PWR + 0x004, PWRCSRBITFIELD)

#endif /* MCU_PWR_H__ */
