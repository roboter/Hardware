/*******************************************************************************************************************************************

    DZX | LPC18xx | LCD                                                                                                   VERSION 18.2.1
    ------------------------------------------------------------------------------------------------------------------------------------

    This is part of the MCU peripheral drivers and provides support for the LCD controller.

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
#ifndef MCU_LCD_H__
#define MCU_LCD_H__

#include "Kernel/kernel.h"

/*******************************************************************************************************************************************
    REGISTER DEFINITIONS
*******************************************************************************************************************************************/
typedef struct LCDCTRLBITFIELD {
    UINT32 LCDEN                   :1;
    UINT32 LCDBPP                  :3;
    UINT32 LCDBW                   :1;
    UINT32 LCDTFT                  :1;
    UINT32 LCDMONO8                :1;
    UINT32 LCDDUAL                 :1;
    UINT32 BGR                     :1;
    UINT32 BEBO                    :1;
    UINT32 BEPO                    :1;
    UINT32 LCDPWR                  :1;
    UINT32 LCDVCOMP                :2;
    UINT32                         :2;
    UINT32 WATERMARK               :1;
    UINT32                         :15;
} LCDCTRLBITFIELD;

typedef struct LCDTIMHBITFIELD {
    UINT32                         :2;
    UINT32 PPL                     :6;
    UINT32 HSW                     :8;
    UINT32 HFP                     :8;
    UINT32 HBP                     :8;
} LCDTIMHBITFIELD;

typedef struct LCDTIMVBITFIELD {
    UINT32 LPP                     :10;
    UINT32 VSW                     :6;
    UINT32 VFP                     :8;
    UINT32 VBP                     :8;
} LCDTIMVBITFIELD;

typedef struct LCDPOLBITFIELD {
    UINT32 PCDLO                   :5;
    UINT32 CLKSEL                  :1;
    UINT32 ACB                     :5;
    UINT32 IVS                     :1;
    UINT32 IHS                     :1;
    UINT32 IPC                     :1;
    UINT32 IOE                     :1;
    UINT32                         :1;
    UINT32 CPL                     :10;
    UINT32 BCD                     :1;
    UINT32 PCDHI                   :5;
} LCDPOLBITFIELD;

typedef struct LCDLEBITFIELD {
    UINT32 LED                     :7;
    UINT32                         :9;
    UINT32 LEE                     :1;
    UINT32                         :15;
} LCDLEBITFIELD;

typedef struct LCDINTMSKBITFIELD {
    UINT32                         :1;
    UINT32 FUFIM                   :1;
    UINT32 LNBUIM                  :1;
    UINT32 VCOMPIM                 :1;
    UINT32 BERIM                   :1;
    UINT32                         :27;
} LCDINTMSKBITFIELD;

typedef struct LCDINTRAWBITFIELD {
    UINT32                         :1;
    UINT32 FUFRIS                  :1;
    UINT32 LNBURIS                 :1;
    UINT32 VCOMPRIS                :1;
    UINT32 BERRAW                  :1;
    UINT32                         :27;
} LCDINTRAWBITFIELD;

typedef struct LCDINTSTATBITFIELD {
    UINT32                         :1;
    UINT32 FUFMIS                  :1;
    UINT32 LNBUMIS                 :1;
    UINT32 VCOMPMIS                :1;
    UINT32 BERMIS                  :1;
    UINT32                         :27;
} LCDINTSTATBITFIELD;

typedef struct LCDINTCLRBITFIELD {
    UINT32                         :1;
    UINT32 FUFIC                   :1;
    UINT32 LNBUIC                  :1;
    UINT32 VCOMPIC                 :1;
    UINT32 BERIC                   :1;
    UINT32                         :27;
} LCDINTCLRBITFIELD;

#define REG_LCDCTRL                               REG_32(0x40008018)
#define REGBITS_LCDCTRL                           REGBITS_32(0x40008018, LCDCTRLBITFIELD)
#define REG_LCDINTCLR                             REG_32(0x40008028)
#define REGBITS_LCDINTCLR                         REGBITS_32(0x40008028, LCDINTCLRBITFIELD)
#define REG_LCDINTMSK                             REG_32(0x4000801C)
#define REGBITS_LCDINTMSK                         REGBITS_32(0x4000801C, LCDINTMSKBITFIELD)
#define REG_LCDINTRAW                             REG_32(0x40008020)
#define REGBITS_LCDINTRAW                         REGBITS_32(0x40008020, LCDINTRAWBITFIELD)
#define REG_LCDINTSTAT                            REG_32(0x40008024)
#define REGBITS_LCDINTSTAT                        REGBITS_32(0x40008024, LCDINTSTATBITFIELD)
#define REG_LCDLE                                 REG_32(0x4000800C)
#define REGBITS_LCDLE                             REGBITS_32(0x4000800C, LCDLEBITFIELD)
#define REG_LCDLPBASE                             REG_32(0x40008014)
#define REG_LCDLPCURR                             REG_32(0x40008030)
#define REG_LCDPALBASE                            REG_32(0x40008200)
#define REG_LCDPOL                                REG_32(0x40008008)
#define REGBITS_LCDPOL                            REGBITS_32(0x40008008, LCDPOLBITFIELD)
#define REG_LCDTIMH                               REG_32(0x40008000)
#define REGBITS_LCDTIMH                           REGBITS_32(0x40008000, LCDTIMHBITFIELD)
#define REG_LCDTIMV                               REG_32(0x40008004)
#define REGBITS_LCDTIMV                           REGBITS_32(0x40008004, LCDTIMVBITFIELD)
#define REG_LCDUPBASE                             REG_32(0x40008010)
#define REG_LCDUPCURR                             REG_32(0x4000802C)

#endif /* MCU_LCD_H__ */
