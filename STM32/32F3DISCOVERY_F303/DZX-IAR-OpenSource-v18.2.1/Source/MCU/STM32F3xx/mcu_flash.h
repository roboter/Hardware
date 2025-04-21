/*******************************************************************************************************************************************

    DZX | STM32F3xx | FLASH                                                                                               VERSION 18.2.1
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
#define BASE_FLASH              0x40022000

/*******************************************************************************************************************************************

    ACR: Flash access control register

*******************************************************************************************************************************************/
typedef struct FLASHACRBITFIELD {
    UINT32 LATENCY              :3;                             /* LATENCY */
    UINT32                      :1;
    UINT32 PRFTBE               :1;                             /* PRFTBE */
    UINT32 PRFTBS               :1;                             /* PRFTBS */
    UINT32                      :26;
} FLASHACRBITFIELD;

#define REG_FLASHACR            REG_32(BASE_FLASH + 0x000)
#define REGBITS_FLASHACR        REGBITS_32(BASE_FLASH + 0x000, FLASHACRBITFIELD)

/*******************************************************************************************************************************************

    KEYR: Flash key register

*******************************************************************************************************************************************/
typedef struct FLASHKEYRBITFIELD {
    UINT32 FKEYR                :32;                            /* Flash Key */
} FLASHKEYRBITFIELD;

#define REG_FLASHKEYR           REG_32(BASE_FLASH + 0x004)
#define REGBITS_FLASHKEYR       REGBITS_32(BASE_FLASH + 0x004, FLASHKEYRBITFIELD)

/*******************************************************************************************************************************************

    OPTKEYR: Flash option key register

*******************************************************************************************************************************************/
typedef struct FLASHOPTKEYRBITFIELD {
    UINT32 OPTKEYR              :32;                            /* Option byte key */
} FLASHOPTKEYRBITFIELD;

#define REG_FLASHOPTKEYR        REG_32(BASE_FLASH + 0x008)
#define REGBITS_FLASHOPTKEYR    REGBITS_32(BASE_FLASH + 0x008, FLASHOPTKEYRBITFIELD)

/*******************************************************************************************************************************************

    SR: Flash status register

*******************************************************************************************************************************************/
typedef struct FLASHSRBITFIELD {
    UINT32                      :5;
    UINT32 EOP                  :1;                             /* End of operation */
    UINT32 WRPRT                :1;                             /* Write protection error */
    UINT32 PGERR                :1;                             /* Programming error */
    UINT32 BSY                  :1;                             /* Busy */
    UINT32                      :31;
} FLASHSRBITFIELD;

#define REG_FLASHSR             REG_32(BASE_FLASH + 0x00C)
#define REGBITS_FLASHSR         REGBITS_32(BASE_FLASH + 0x00C, FLASHSRBITFIELD)

/*******************************************************************************************************************************************

    CR: Flash control register

*******************************************************************************************************************************************/
typedef struct FLASHCRBITFIELD {
    UINT32                      :13;
    UINT32 FORCE_OPTLOAD        :1;                             /* Force option byte loading */
    UINT32 EOPIE                :1;                             /* End of operation interrupt enable */
    UINT32 ERRIE                :1;                             /* Error interrupt enable */
    UINT32 OPTWRE               :1;                             /* Option bytes write enable */
    UINT32 LOCK                 :1;                             /* Lock */
    UINT32 STRT                 :1;                             /* Start */
    UINT32 OPTER                :1;                             /* Option byte erase */
    UINT32 OPTPG                :1;                             /* Option byte programming */
    UINT32 MER                  :1;                             /* Mass erase */
    UINT32 PER                  :1;                             /* Page erase */
    UINT32 PG                   :1;                             /* Programming */
    UINT32                      :31;
} FLASHCRBITFIELD;

#define REG_FLASHCR             REG_32(BASE_FLASH + 0x010)
#define REGBITS_FLASHCR         REGBITS_32(BASE_FLASH + 0x010, FLASHCRBITFIELD)

/*******************************************************************************************************************************************

    AR: Flash address register

*******************************************************************************************************************************************/
typedef struct FLASHARBITFIELD {
    UINT32 FAR                  :32;                            /* Flash address */
} FLASHARBITFIELD;

#define REG_FLASHAR             REG_32(BASE_FLASH + 0x014)
#define REGBITS_FLASHAR         REGBITS_32(BASE_FLASH + 0x014, FLASHARBITFIELD)

/*******************************************************************************************************************************************

    OBR: Option byte register

*******************************************************************************************************************************************/
typedef struct FLASHOBRBITFIELD {
    UINT32 OPTERR               :1;                             /* Option byte error */
    UINT32 LEVEL1_PROT          :1;                             /* Level 1 protection status */
    UINT32 LEVEL2_PROT          :1;                             /* Level 2 protection status */
    UINT32                      :5;
    UINT32 WDG_SW               :1;                             /* WDG_SW */
    UINT32 nRST_STOP            :1;                             /* nRST_STOP */
    UINT32 nRST_STDBY           :1;                             /* nRST_STDBY */
    UINT32                      :1;
    UINT32 BOOT1                :1;                             /* BOOT1 */
    UINT32 VDDA_MONITOR         :1;                             /* VDDA_MONITOR */
    UINT32 SRAM_PARITY_CHECK    :1;                             /* SRAM_PARITY_CHECK */
    UINT32                      :1;
    UINT32 Data0                :8;                             /* Data0 */
    UINT32 Data1                :8;                             /* Data1 */
} FLASHOBRBITFIELD;

#define REG_FLASHOBR            REG_32(BASE_FLASH + 0x01C)
#define REGBITS_FLASHOBR        REGBITS_32(BASE_FLASH + 0x01C, FLASHOBRBITFIELD)

/*******************************************************************************************************************************************

    WRPR: Write protection register

*******************************************************************************************************************************************/
typedef struct FLASHWRPRBITFIELD {
    UINT32 WRP                  :32;                            /* Write protect */
} FLASHWRPRBITFIELD;

#define REG_FLASHWRPR           REG_32(BASE_FLASH + 0x020)
#define REGBITS_FLASHWRPR       REGBITS_32(BASE_FLASH + 0x020, FLASHWRPRBITFIELD)



#endif /* MCU_FLASH_H__ */
