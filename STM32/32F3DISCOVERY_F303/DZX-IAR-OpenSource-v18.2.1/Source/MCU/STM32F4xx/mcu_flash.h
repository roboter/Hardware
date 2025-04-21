/*******************************************************************************************************************************************

    DZX | STM32F4xx | FLASH                                                                                               VERSION 18.2.1
    ------------------------------------------------------------------------------------------------------------------------------------

    This is part of the MCU peripheral drivers and provides support for the flash control registers.

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
#ifndef MCU_FLASH_H__
#define MCU_FLASH_H__

/*******************************************************************************************************************************************
    REGISTER DEFINITIONS
*******************************************************************************************************************************************/
typedef struct FLASHACRBITFIELD {
    UINT32 LATENCY                 :3;
    UINT32                         :5;
    UINT32 PRFTEN                  :1;
    UINT32 ICEN                    :1;
    UINT32 DCEN                    :1;
    UINT32 ICRST                   :1;
    UINT32 DCRST                   :1;
    UINT32                         :19;
} FLASHACRBITFIELD;

typedef struct FLASHSRBITFIELD {
    UINT32 EOP                     :1;
    UINT32 OPERR                   :1;
    UINT32                         :2;
    UINT32 WRPERR                  :1;
    UINT32 PGAERR                  :1;
    UINT32 PGPERR                  :1;
    UINT32 PGSERR                  :1;
    UINT32                         :8;
    UINT32 BSY                     :1;
    UINT32                         :15;
} FLASHSRBITFIELD;

typedef struct FLASHCRBITFIELD {
    UINT32 PG                      :1;
    UINT32 SER                     :1;
    UINT32 MER                     :1;
    UINT32 SNB                     :4;
    UINT32                         :1;
    UINT32 PSIZE                   :2;
    UINT32                         :6;
    UINT32 STRT                    :1;
    UINT32                         :7;
    UINT32 EOPIE                   :1;
    UINT32 ERRIE                   :1;
    UINT32                         :5;
    UINT32 LOCK                    :1;
} FLASHCRBITFIELD;

typedef struct FLASHOPTCRBITFIELD {
    UINT32 OPTLOCK                 :1;
    UINT32 OPTSTRT                 :1;
    UINT32 BOR_LEV                 :2;
    UINT32                         :1;
    UINT32 WDG_SW                  :1;
    UINT32 NRST_STOP               :1;
    UINT32 NRST_STDBY              :1;
    UINT32 RDP                     :8;
    UINT32 NWRP                    :12;
    UINT32                         :4;
} FLASHOPTCRBITFIELD;

#define REG_FLASHACR                              REG_32(0x40023C00)
#define REGBITS_FLASHACR                          REGBITS_32(0x40023C00, FLASHACRBITFIELD)
#define REG_FLASHCR                               REG_32(0x40023C10)
#define REGBITS_FLASHCR                           REGBITS_32(0x40023C10, FLASHCRBITFIELD)
#define REG_FLASHKEYR                             REG_32(0x40023C04)
#define REG_FLASHOPTCR                            REG_32(0x40023C14)
#define REGBITS_FLASHOPTCR                        REGBITS_32(0x40023C14, FLASHOPTCRBITFIELD)
#define REG_FLASHOPTKEYR                          REG_32(0x40023C08)
#define REG_FLASHSR                               REG_32(0x40023C0C)
#define REGBITS_FLASHSR                           REGBITS_32(0x40023C0C, FLASHSRBITFIELD)

#endif /* MCU_FLASH_H__ */
