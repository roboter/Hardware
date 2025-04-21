/*******************************************************************************************************************************************

    DZX | LPC177x8x | SCU                                                                                                 VERSION 18.2.1
    ------------------------------------------------------------------------------------------------------------------------------------

    This is part of the MCU peripheral drivers and provides support for the system control unit (SCU).

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
#ifndef MCU_SCU_H__
#define MCU_SCU_H__

#include "Kernel/kernel.h"

typedef struct FLASHCFGBITFIELD {
    UINT32                         :12;
    UINT32 FLASHTIM                :4;
    UINT32                         :16;
} FLASHCFGBITFIELD;

typedef struct PCLKSELBITFIELD {
    UINT32 PCLKDIV                 :5;
    UINT32                         :27;
} PCLKSELBITFIELD;

typedef struct PCONBITFIELD {
    UINT32 PM0                     :1;
    UINT32 PM1                     :1;
    UINT32 BODPDM                  :1;
    UINT32 BOGD                    :1;
    UINT32 BORD                    :1;
    UINT32                         :3;
    UINT32 SMFLAG                  :1;
    UINT32 DSFLAG                  :1;
    UINT32 PDFLAG                  :1;
    UINT32 DPDFLAG                 :1;
    UINT32                         :20;
} PCONBITFIELD;

typedef struct PCONPBITFIELD {
    UINT32 PCLCD                   :1;
    UINT32 PCTIM0                  :1;
    UINT32 PCTIM1                  :1;
    UINT32 PCUART0                 :1;
    UINT32 PCUART1                 :1;
    UINT32 PCPWM0                  :1;
    UINT32 PCPWM1                  :1;
    UINT32 PCI2C0                  :1;
    UINT32 PCUART4                 :1;
    UINT32 PCRTC                   :1;
    UINT32 PCSSP1                  :1;
    UINT32 PCEMC                   :1;
    UINT32 PCAD                    :1;
    UINT32 PCAN1                   :1;
    UINT32 PCAN2                   :1;
    UINT32 PCGPIO                  :1;
    UINT32                         :1;
    UINT32 PCMCPWM                 :1;
    UINT32 PCQEI                   :1;
    UINT32 PCI2C1                  :1;
    UINT32 PCSSP2                  :1;
    UINT32 PCSSP0                  :1;
    UINT32 PCTIM2                  :1;
    UINT32 PCTIM3                  :1;
    UINT32 PCUART2                 :1;
    UINT32 PCUART3                 :1;
    UINT32 PCI2C2                  :1;
    UINT32 PCI2S                   :1;
    UINT32 PCSDC                   :1;
    UINT32 PCGPDMA                 :1;
    UINT32 PCENET                  :1;
    UINT32 PCUSB                   :1;
} PCONPBITFIELD;

typedef struct PLL0CONBITFIELD {
    UINT32 PLLE                    :1;
    UINT32                         :31;
} PLL0CONBITFIELD;

typedef struct PLL0CFGBITFIELD {
    UINT32 MSEL                    :5;
    UINT32 PSEL                    :2;
    UINT32                         :25;
} PLL0CFGBITFIELD;

typedef struct PLL0STATBITFIELD {
    UINT32 MSEL                    :5;
    UINT32 PSEL                    :2;
    UINT32                         :1;
    UINT32 PLLESTAT                :1;
    UINT32                         :1;
    UINT32 PLOCK                   :1;
    UINT32                         :21;
} PLL0STATBITFIELD;

typedef struct PLL0FEEDBITFIELD {
    UINT32 FEED                    :8;
    UINT32                         :24;
} PLL0FEEDBITFIELD;

typedef struct PLL1CONBITFIELD {
    UINT32 PLLE                    :1;
    UINT32                         :31;
} PLL1CONBITFIELD;

typedef struct PLL1CFGBITFIELD {
    UINT32 MSEL                    :5;
    UINT32 PSEL                    :2;
    UINT32                         :25;
} PLL1CFGBITFIELD;

typedef struct PLL1STATBITFIELD {
    UINT32 MSEL                    :5;
    UINT32 PSEL                    :2;
    UINT32                         :1;
    UINT32 PLLESTAT                :1;
    UINT32                         :1;
    UINT32 PLOCK                   :1;
    UINT32                         :21;
} PLL1STATBITFIELD;

typedef struct PLL1FEEDBITFIELD {
    UINT32 FEED                    :8;
    UINT32                         :24;
} PLL1FEEDBITFIELD;

typedef struct SCSBITFIELD {
    UINT32 EMCSC                   :1;
    UINT32 EMCRD                   :1;
    UINT32 EMCBC                   :1;
    UINT32 MCIPWR                  :1;
    UINT32 OSCRANGE                :1;
    UINT32 OSCEN                   :1;
    UINT32 OSCSTAT                 :1;
    UINT32                         :25;
} SCSBITFIELD;

#define REG_CCLKSEL                               REG_32(0x400FC104)
#define REG_CLKOUTCFG                             REG_32(0x400FC1C8)
#define REG_CLKSRCSEL                             REG_32(0x400FC10C)
#define REG_FLASHCFG                              REG_32(0x400FC000)
#define REGBITS_FLASHCFG                          REGBITS_32(0x400FC000, FLASHCFGBITFIELD)
#define REG_PBOOST                                REG_32(0x400FC1B0)
#define REG_PCLKSEL                               REG_32(0x400FC1A8)
#define REGBITS_PCLKSEL                           REGBITS_32(0x400FC1A8, PCLKSELBITFIELD)
#define REG_PCON                                  REG_32(0x400FC0C0)
#define REGBITS_PCON                              REGBITS_32(0x400FC0C0, PCONBITFIELD)
#define REG_PCONP                                 REG_32(0x400FC0C4)
#define REGBITS_PCONP                             REGBITS_32(0x400FC0C4, PCONPBITFIELD)
#define REG_PLL0CFG                               REG_32(0x400FC084)
#define REGBITS_PLL0CFG                           REGBITS_32(0x400FC084, PLL0CFGBITFIELD)
#define REG_PLL0CON                               REG_32(0x400FC080)
#define REGBITS_PLL0CON                           REGBITS_32(0x400FC080, PLL0CONBITFIELD)
#define REG_PLL0FEED                              REG_32(0x400FC08C)
#define REGBITS_PLL0FEED                          REGBITS_32(0x400FC08C, PLL0FEEDBITFIELD)
#define REG_PLL0STAT                              REG_32(0x400FC088)
#define REGBITS_PLL0STAT                          REGBITS_32(0x400FC088, PLL0STATBITFIELD)
#define REG_PLL1CFG                               REG_32(0x400FC0A4)
#define REGBITS_PLL1CFG                           REGBITS_32(0x400FC0A4, PLL1CFGBITFIELD)
#define REG_PLL1CON                               REG_32(0x400FC0A0)
#define REGBITS_PLL1CON                           REGBITS_32(0x400FC0A0, PLL1CONBITFIELD)
#define REG_PLL1FEED                              REG_32(0x400FC0AC)
#define REGBITS_PLL1FEED                          REGBITS_32(0x400FC0AC, PLL1FEEDBITFIELD)
#define REG_PLL1STAT                              REG_32(0x400FC0A8)
#define REGBITS_PLL1STAT                          REGBITS_32(0x400FC0A8, PLL1STATBITFIELD)
#define REG_SCS                                   REG_32(0x400FC1A0)
#define REGBITS_SCS                               REGBITS_32(0x400FC1A0, SCSBITFIELD)

#endif /* MCU_SCU_H__ */
