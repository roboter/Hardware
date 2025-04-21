/*******************************************************************************************************************************************

    DZX | LPC18xx | CGU                                                                                                   VERSION 18.2.1
    ------------------------------------------------------------------------------------------------------------------------------------

    This is part of the MCU peripheral drivers and provides support for the clock generation unit (CGU).

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
#ifndef MCU_CGU_H__
#define MCU_CGU_H__

#include "Kernel/kernel.h"

/*******************************************************************************************************************************************
    REGISTER DEFINITIONS
*******************************************************************************************************************************************/
typedef struct CGUFREQMONBITFIELD {
    UINT32 RCNT                    :9;
    UINT32 FCNT                    :14;
    UINT32 MEAS                    :1;
    UINT32 CLKSEL                  :4;
    UINT32                         :4;
} CGUFREQMONBITFIELD;

typedef struct CGUXTALOSCCTRLBITFIELD {
    UINT32 ENABLE                  :1;
    UINT32 BYPASS                  :1;
    UINT32 HF                      :1;
    UINT32                         :29;
} CGUXTALOSCCTRLBITFIELD;

typedef struct CGUPLL0STATBITFIELD {
    UINT32 LOCK                    :1;
    UINT32 FR                      :1;
    UINT32                         :30;
} CGUPLL0STATBITFIELD;

typedef struct CGUPLL0CTRLBITFIELD {
    UINT32 PD                      :1;
    UINT32 BYPASS                  :1;
    UINT32 DIRECTI                 :1;
    UINT32 DIRECTO                 :1;
    UINT32 CLKEN                   :1;
    UINT32                         :1;
    UINT32 FRM                     :1;
    UINT32                         :4;
    UINT32 AUTOBLOCK               :1;
    UINT32                         :12;
    UINT32 CLKSEL                  :4;
    UINT32                         :4;
} CGUPLL0CTRLBITFIELD;

typedef struct CGUPLL0MDIVBITFIELD {
    UINT32 MDEC                    :17;
    UINT32 SELP                    :5;
    UINT32 SELI                    :6;
    UINT32 SELR                    :4;
} CGUPLL0MDIVBITFIELD;

typedef struct CGUPLL0NPDIVBITFIELD {
    UINT32 PDEC                    :7;
    UINT32                         :5;
    UINT32 NDEC                    :10;
    UINT32                         :10;
} CGUPLL0NPDIVBITFIELD;

typedef struct CGUPLL1STATBITFIELD {
    UINT32 LOCK                    :1;
    UINT32                         :31;
} CGUPLL1STATBITFIELD;

typedef struct CGUPLL1CTRLBITFIELD {
    UINT32 PD                      :1;
    UINT32 BYPASS                  :1;
    UINT32                         :4;
    UINT32 FBSEL                   :1;
    UINT32 DIRECT                  :1;
    UINT32 PSEL                    :2;
    UINT32                         :1;
    UINT32 AUTOBLOCK               :1;
    UINT32 NSEL                    :2;
    UINT32                         :2;
    UINT32 MSEL                    :8;
    UINT32 CLKSEL                  :4;
    UINT32                         :4;
} CGUPLL1CTRLBITFIELD;

typedef struct CGUIDIVACTRLBITFIELD {
    UINT32 PD                      :1;
    UINT32                         :1;
    UINT32 IDIV                    :2;
    UINT32                         :7;
    UINT32 AUTOBLOCK               :1;
    UINT32                         :12;
    UINT32 CLKSEL                  :4;
    UINT32                         :4;
} CGUIDIVACTRLBITFIELD;

typedef struct CGUIDIVBCTRLBITFIELD {
    UINT32 PD                      :1;
    UINT32                         :1;
    UINT32 IDIV                    :4;
    UINT32                         :5;
    UINT32 AUTOBLOCK               :1;
    UINT32                         :12;
    UINT32 CLKSEL                  :4;
    UINT32                         :4;
} CGUIDIVBCTRLBITFIELD;

typedef struct CGUIDIVCCTRLBITFIELD {
    UINT32 PD                      :1;
    UINT32                         :1;
    UINT32 IDIV                    :4;
    UINT32                         :5;
    UINT32 AUTOBLOCK               :1;
    UINT32                         :12;
    UINT32 CLKSEL                  :4;
    UINT32                         :4;
} CGUIDIVCCTRLBITFIELD;

typedef struct CGUIDIVDCTRLBITFIELD {
    UINT32 PD                      :1;
    UINT32                         :1;
    UINT32 IDIV                    :4;
    UINT32                         :5;
    UINT32 AUTOBLOCK               :1;
    UINT32                         :12;
    UINT32 CLKSEL                  :4;
    UINT32                         :4;
} CGUIDIVDCTRLBITFIELD;

typedef struct CGUIDIVECTRLBITFIELD {
    UINT32 PD                      :1;
    UINT32                         :1;
    UINT32 IDIV                    :8;
    UINT32                         :1;
    UINT32 AUTOBLOCK               :1;
    UINT32                         :12;
    UINT32 CLKSEL                  :4;
    UINT32                         :4;
} CGUIDIVECTRLBITFIELD;

typedef struct CGUBASESAFECLKBITFIELD {
    UINT32 PD                      :1;
    UINT32                         :10;
    UINT32 AUTOBLOCK               :1;
    UINT32                         :12;
    UINT32 CLKSEL                  :5;
    UINT32                         :3;
} CGUBASESAFECLKBITFIELD;

typedef struct CGUBASEUSB0CLKBITFIELD {
    UINT32 PD                      :1;
    UINT32                         :10;
    UINT32 AUTOBLOCK               :1;
    UINT32                         :12;
    UINT32 CLKSEL                  :5;
    UINT32                         :3;
} CGUBASEUSB0CLKBITFIELD;

typedef struct CGUBASEPERIPHCLKBITFIELD {
    UINT32 PD                      :1;
    UINT32                         :10;
    UINT32 AUTOBLOCK               :1;
    UINT32                         :12;
    UINT32 CLKSEL                  :5;
    UINT32                         :3;
} CGUBASEPERIPHCLKBITFIELD;

typedef struct CGUBASEUSB1CLKBITFIELD {
    UINT32 PD                      :1;
    UINT32                         :10;
    UINT32 AUTOBLOCK               :1;
    UINT32                         :12;
    UINT32 CLKSEL                  :5;
    UINT32                         :3;
} CGUBASEUSB1CLKBITFIELD;

typedef struct CGUBASEM3CLKBITFIELD {
    UINT32 PD                      :1;
    UINT32                         :10;
    UINT32 AUTOBLOCK               :1;
    UINT32                         :12;
    UINT32 CLKSEL                  :5;
    UINT32                         :3;
} CGUBASEM3CLKBITFIELD;

typedef struct CGUBASESPIFICLKBITFIELD {
    UINT32 PD                      :1;
    UINT32                         :10;
    UINT32 AUTOBLOCK               :1;
    UINT32                         :12;
    UINT32 CLKSEL                  :5;
    UINT32                         :3;
} CGUBASESPIFICLKBITFIELD;

typedef struct CGUBASESPICLKBITFIELD {
    UINT32 PD                      :1;
    UINT32                         :10;
    UINT32 AUTOBLOCK               :1;
    UINT32                         :12;
    UINT32 CLKSEL                  :5;
    UINT32                         :3;
} CGUBASESPICLKBITFIELD;

typedef struct CGUBASEPHYRXCLKBITFIELD {
    UINT32 PD                      :1;
    UINT32                         :10;
    UINT32 AUTOBLOCK               :1;
    UINT32                         :12;
    UINT32 CLKSEL                  :5;
    UINT32                         :3;
} CGUBASEPHYRXCLKBITFIELD;

typedef struct CGUBASEPHYTXCLKBITFIELD {
    UINT32 PD                      :1;
    UINT32                         :10;
    UINT32 AUTOBLOCK               :1;
    UINT32                         :12;
    UINT32 CLKSEL                  :5;
    UINT32                         :3;
} CGUBASEPHYTXCLKBITFIELD;

typedef struct CGUBASEAPB1CLKBITFIELD {
    UINT32 PD                      :1;
    UINT32                         :10;
    UINT32 AUTOBLOCK               :1;
    UINT32                         :12;
    UINT32 CLKSEL                  :5;
    UINT32                         :3;
} CGUBASEAPB1CLKBITFIELD;

typedef struct CGUBASEAPB3CLKBITFIELD {
    UINT32 PD                      :1;
    UINT32                         :10;
    UINT32 AUTOBLOCK               :1;
    UINT32                         :12;
    UINT32 CLKSEL                  :5;
    UINT32                         :3;
} CGUBASEAPB3CLKBITFIELD;

typedef struct CGUBASELCDCLKBITFIELD {
    UINT32 PD                      :1;
    UINT32                         :10;
    UINT32 AUTOBLOCK               :1;
    UINT32                         :12;
    UINT32 CLKSEL                  :5;
    UINT32                         :3;
} CGUBASELCDCLKBITFIELD;

typedef struct CGUBASEVADCCLKBITFIELD {
    UINT32 PD                      :1;
    UINT32                         :10;
    UINT32 AUTOBLOCK               :1;
    UINT32                         :12;
    UINT32 CLKSEL                  :5;
    UINT32                         :3;
} CGUBASEVADCCLKBITFIELD;

typedef struct CGUBASESDIOCLKBITFIELD {
    UINT32 PD                      :1;
    UINT32                         :10;
    UINT32 AUTOBLOCK               :1;
    UINT32                         :12;
    UINT32 CLKSEL                  :5;
    UINT32                         :3;
} CGUBASESDIOCLKBITFIELD;

typedef struct CGUBASESSP0CLKBITFIELD {
    UINT32 PD                      :1;
    UINT32                         :10;
    UINT32 AUTOBLOCK               :1;
    UINT32                         :12;
    UINT32 CLKSEL                  :5;
    UINT32                         :3;
} CGUBASESSP0CLKBITFIELD;

typedef struct CGUBASESSP1CLKBITFIELD {
    UINT32 PD                      :1;
    UINT32                         :10;
    UINT32 AUTOBLOCK               :1;
    UINT32                         :12;
    UINT32 CLKSEL                  :5;
    UINT32                         :3;
} CGUBASESSP1CLKBITFIELD;

typedef struct CGUBASEUART0CLKBITFIELD {
    UINT32 PD                      :1;
    UINT32                         :10;
    UINT32 AUTOBLOCK               :1;
    UINT32                         :12;
    UINT32 CLKSEL                  :5;
    UINT32                         :3;
} CGUBASEUART0CLKBITFIELD;

typedef struct CGUBASEUART1CLKBITFIELD {
    UINT32 PD                      :1;
    UINT32                         :10;
    UINT32 AUTOBLOCK               :1;
    UINT32                         :12;
    UINT32 CLKSEL                  :5;
    UINT32                         :3;
} CGUBASEUART1CLKBITFIELD;

typedef struct CGUBASEUART2CLKBITFIELD {
    UINT32 PD                      :1;
    UINT32                         :10;
    UINT32 AUTOBLOCK               :1;
    UINT32                         :12;
    UINT32 CLKSEL                  :5;
    UINT32                         :3;
} CGUBASEUART2CLKBITFIELD;

typedef struct CGUBASEUART3CLKBITFIELD {
    UINT32 PD                      :1;
    UINT32                         :10;
    UINT32 AUTOBLOCK               :1;
    UINT32                         :12;
    UINT32 CLKSEL                  :5;
    UINT32                         :3;
} CGUBASEUART3CLKBITFIELD;

typedef struct CGUBASEOUTCLKBITFIELD {
    UINT32 PD                      :1;
    UINT32                         :10;
    UINT32 AUTOBLOCK               :1;
    UINT32                         :12;
    UINT32 CLKSEL                  :5;
    UINT32                         :3;
} CGUBASEOUTCLKBITFIELD;

typedef struct CGUBASEAPLLCLKBITFIELD {
    UINT32 PD                      :1;
    UINT32                         :10;
    UINT32 AUTOBLOCK               :1;
    UINT32                         :12;
    UINT32 CLKSEL                  :5;
    UINT32                         :3;
} CGUBASEAPLLCLKBITFIELD;

typedef struct CGUBASECGUOUT0CLKBITFIELD {
    UINT32 PD                      :1;
    UINT32                         :10;
    UINT32 AUTOBLOCK               :1;
    UINT32                         :12;
    UINT32 CLKSEL                  :5;
    UINT32                         :3;
} CGUBASECGUOUT0CLKBITFIELD;

typedef struct CGUBASECGUOUT1CLKBITFIELD {
    UINT32 PD                      :1;
    UINT32                         :10;
    UINT32 AUTOBLOCK               :1;
    UINT32                         :12;
    UINT32 CLKSEL                  :5;
    UINT32                         :3;
} CGUBASECGUOUT1CLKBITFIELD;

typedef struct CGUOUTCLK0CTRLBITFIELD {
    UINT32 PD                      :1;
    UINT32                         :10;
    UINT32 AUTOBLOCK               :1;
    UINT32                         :12;
    UINT32 CLKSEL                  :4;
    UINT32                         :4;
} CGUOUTCLK0CTRLBITFIELD;

typedef struct CGUOUTCLK1CTRLBITFIELD {
    UINT32 PD                      :1;
    UINT32                         :10;
    UINT32 AUTOBLOCK               :1;
    UINT32                         :12;
    UINT32 CLKSEL                  :4;
    UINT32                         :4;
} CGUOUTCLK1CTRLBITFIELD;

typedef struct CGUOUTCLK2CTRLBITFIELD {
    UINT32 PD                      :1;
    UINT32                         :10;
    UINT32 AUTOBLOCK               :1;
    UINT32                         :12;
    UINT32 CLKSEL                  :4;
    UINT32                         :4;
} CGUOUTCLK2CTRLBITFIELD;

typedef struct CGUOUTCLK3CTRLBITFIELD {
    UINT32 PD                      :1;
    UINT32                         :10;
    UINT32 AUTOBLOCK               :1;
    UINT32                         :12;
    UINT32 CLKSEL                  :4;
    UINT32                         :4;
} CGUOUTCLK3CTRLBITFIELD;

typedef struct CGUOUTCLK4CTRLBITFIELD {
    UINT32 PD                      :1;
    UINT32                         :10;
    UINT32 AUTOBLOCK               :1;
    UINT32                         :12;
    UINT32 CLKSEL                  :4;
    UINT32                         :4;
} CGUOUTCLK4CTRLBITFIELD;

typedef struct CGUOUTCLK5CTRLBITFIELD {
    UINT32 PD                      :1;
    UINT32                         :10;
    UINT32 AUTOBLOCK               :1;
    UINT32                         :12;
    UINT32 CLKSEL                  :4;
    UINT32                         :4;
} CGUOUTCLK5CTRLBITFIELD;

typedef struct CGUOUTCLK7CTRLBITFIELD {
    UINT32 PD                      :1;
    UINT32                         :10;
    UINT32 AUTOBLOCK               :1;
    UINT32                         :12;
    UINT32 CLKSEL                  :4;
    UINT32                         :4;
} CGUOUTCLK7CTRLBITFIELD;

typedef struct CGUOUTCLK8CTRLBITFIELD {
    UINT32 PD                      :1;
    UINT32                         :10;
    UINT32 AUTOBLOCK               :1;
    UINT32                         :12;
    UINT32 CLKSEL                  :4;
    UINT32                         :4;
} CGUOUTCLK8CTRLBITFIELD;

typedef struct CGUOUTCLK9CTRLBITFIELD {
    UINT32 PD                      :1;
    UINT32                         :10;
    UINT32 AUTOBLOCK               :1;
    UINT32                         :12;
    UINT32 CLKSEL                  :4;
    UINT32                         :4;
} CGUOUTCLK9CTRLBITFIELD;

typedef struct CGUOUTCLK10CTRLBITFIELD {
    UINT32 PD                      :1;
    UINT32                         :10;
    UINT32 AUTOBLOCK               :1;
    UINT32                         :12;
    UINT32 CLKSEL                  :4;
    UINT32                         :4;
} CGUOUTCLK10CTRLBITFIELD;

typedef struct CGUOUTCLK11CTRLBITFIELD {
    UINT32 PD                      :1;
    UINT32                         :10;
    UINT32 AUTOBLOCK               :1;
    UINT32                         :12;
    UINT32 CLKSEL                  :4;
    UINT32                         :4;
} CGUOUTCLK11CTRLBITFIELD;

typedef struct CGUOUTCLK13CTRLBITFIELD {
    UINT32 PD                      :1;
    UINT32                         :10;
    UINT32 AUTOBLOCK               :1;
    UINT32                         :12;
    UINT32 CLKSEL                  :4;
    UINT32                         :4;
} CGUOUTCLK13CTRLBITFIELD;

typedef struct CGUOUTCLK14CTRLBITFIELD {
    UINT32 PD                      :1;
    UINT32                         :10;
    UINT32 AUTOBLOCK               :1;
    UINT32                         :12;
    UINT32 CLKSEL                  :4;
    UINT32                         :4;
} CGUOUTCLK14CTRLBITFIELD;

typedef struct CGUOUTCLK15CTRLBITFIELD {
    UINT32 PD                      :1;
    UINT32                         :10;
    UINT32 AUTOBLOCK               :1;
    UINT32                         :12;
    UINT32 CLKSEL                  :4;
    UINT32                         :4;
} CGUOUTCLK15CTRLBITFIELD;

typedef struct CGUOUTCLK16CTRLBITFIELD {
    UINT32 PD                      :1;
    UINT32                         :10;
    UINT32 AUTOBLOCK               :1;
    UINT32                         :12;
    UINT32 CLKSEL                  :4;
    UINT32                         :4;
} CGUOUTCLK16CTRLBITFIELD;

typedef struct CGUOUTCLK17CTRLBITFIELD {
    UINT32 PD                      :1;
    UINT32                         :10;
    UINT32 AUTOBLOCK               :1;
    UINT32                         :12;
    UINT32 CLKSEL                  :4;
    UINT32                         :4;
} CGUOUTCLK17CTRLBITFIELD;

typedef struct CGUOUTCLK18CTRLBITFIELD {
    UINT32 PD                      :1;
    UINT32                         :10;
    UINT32 AUTOBLOCK               :1;
    UINT32                         :12;
    UINT32 CLKSEL                  :4;
    UINT32                         :4;
} CGUOUTCLK18CTRLBITFIELD;

typedef struct CGUOUTCLK19CTRLBITFIELD {
    UINT32 PD                      :1;
    UINT32                         :10;
    UINT32 AUTOBLOCK               :1;
    UINT32                         :12;
    UINT32 CLKSEL                  :4;
    UINT32                         :4;
} CGUOUTCLK19CTRLBITFIELD;

typedef struct CGUOUTCLK20CTRLBITFIELD {
    UINT32 PD                      :1;
    UINT32                         :10;
    UINT32 AUTOBLOCK               :1;
    UINT32                         :12;
    UINT32 CLKSEL                  :4;
    UINT32                         :4;
} CGUOUTCLK20CTRLBITFIELD;

#define REG_CGUFREQMON                            REG_32(0x40050014)
#define REGBITS_CGUFREQMON                        REGBITS_32(0x40050014, CGUFREQMONBITFIELD)
#define REG_CGUIDIVACTRL                          REG_32(0x40050048)
#define REGBITS_CGUIDIVACTRL                      REGBITS_32(0x40050048, CGUIDIVACTRLBITFIELD)
#define REG_CGUIDIVBCTRL                          REG_32(0x4005004C)
#define REGBITS_CGUIDIVBCTRL                      REGBITS_32(0x4005004C, CGUIDIVBCTRLBITFIELD)
#define REG_CGUIDIVCCTRL                          REG_32(0x40050050)
#define REGBITS_CGUIDIVCCTRL                      REGBITS_32(0x40050050, CGUIDIVCCTRLBITFIELD)
#define REG_CGUIDIVDCTRL                          REG_32(0x40050054)
#define REGBITS_CGUIDIVDCTRL                      REGBITS_32(0x40050054, CGUIDIVDCTRLBITFIELD)
#define REG_CGUIDIVECTRL                          REG_32(0x40050058)
#define REGBITS_CGUIDIVECTRL                      REGBITS_32(0x40050058, CGUIDIVECTRLBITFIELD)


#define REG_CGUBASEAPB1CLK                        REG_32(0x40050080)
#define REGBITS_CGUBASEAPB1CLK                    REGBITS_32(0x40050080, CGUBASEAPB1CLKBITFIELD)
#define REG_CGUBASEAPB3CLK                        REG_32(0x40050084)
#define REGBITS_CGUBASEAPB3CLK                    REGBITS_32(0x40050084, CGUBASEAPB3CLKBITFIELD)
#define REG_CGUBASEAPLLCLK                        REG_32(0x400500C0)
#define REGBITS_CGUBASEAPLLCLK                    REGBITS_32(0x400500C0, CGUBASEAPLLCLKBITFIELD)
#define REG_CGUBASECGUOUT0CLK                     REG_32(0x400500C4)
#define REGBITS_CGUBASECGUOUT0CLK                 REGBITS_32(0x400500C4, CGUBASECGUOUT0CLKBITFIELD)
#define REG_CGUBASECGUOUT1CLK                     REG_32(0x400500C8)
#define REGBITS_CGUBASECGUOUT1CLK                 REGBITS_32(0x400500C8, CGUBASECGUOUT1CLKBITFIELD)
#define REG_CGUBASELCDCLK                         REG_32(0x40050088)
#define REGBITS_CGUBASELCDCLK                     REGBITS_32(0x40050088, CGUBASELCDCLKBITFIELD)
#define REG_CGUBASEM3CLK                          REG_32(0x4005006C)
#define REGBITS_CGUBASEM3CLK                      REGBITS_32(0x4005006C, CGUBASEM3CLKBITFIELD)
#define REG_CGUBASEOUTCLK                         REG_32(0x400500AC)
#define REGBITS_CGUBASEOUTCLK                     REGBITS_32(0x400500AC, CGUBASEOUTCLKBITFIELD)
#define REG_CGUBASEPERIPHCLK                      REG_32(0x40050064)
#define REGBITS_CGUBASEPERIPHCLK                  REGBITS_32(0x40050064, CGUBASEPERIPHCLKBITFIELD)
#define REG_CGUBASEPHYRXCLK                       REG_32(0x40050078)
#define REGBITS_CGUBASEPHYRXCLK                   REGBITS_32(0x40050078, CGUBASEPHYRXCLKBITFIELD)
#define REG_CGUBASEPHYTXCLK                       REG_32(0x4005007C)
#define REGBITS_CGUBASEPHYTXCLK                   REGBITS_32(0x4005007C, CGUBASEPHYTXCLKBITFIELD)
#define REG_CGUBASESAFECLK                        REG_32(0x4005005C)
#define REGBITS_CGUBASESAFECLK                    REGBITS_32(0x4005005C, CGUBASESAFECLKBITFIELD)
#define REG_CGUBASESDIOCLK                        REG_32(0x40050090)
#define REGBITS_CGUBASESDIOCLK                    REGBITS_32(0x40050090, CGUBASESDIOCLKBITFIELD)
#define REG_CGUBASESPICLK                         REG_32(0x40050074)
#define REGBITS_CGUBASESPICLK                     REGBITS_32(0x40050074, CGUBASESPICLKBITFIELD)
#define REG_CGUBASESPIFICLK                       REG_32(0x40050070)
#define REGBITS_CGUBASESPIFICLK                   REGBITS_32(0x40050070, CGUBASESPIFICLKBITFIELD)
#define REG_CGUBASESSP0CLK                        REG_32(0x40050094)
#define REGBITS_CGUBASESSP0CLK                    REGBITS_32(0x40050094, CGUBASESSP0CLKBITFIELD)
#define REG_CGUBASESSP1CLK                        REG_32(0x40050098)
#define REGBITS_CGUBASESSP1CLK                    REGBITS_32(0x40050098, CGUBASESSP1CLKBITFIELD)
#define REG_CGUBASEUART0CLK                       REG_32(0x4005009C)
#define REGBITS_CGUBASEUART0CLK                   REGBITS_32(0x4005009C, CGUBASEUART0CLKBITFIELD)
#define REG_CGUBASEUART1CLK                       REG_32(0x400500A0)
#define REGBITS_CGUBASEUART1CLK                   REGBITS_32(0x400500A0, CGUBASEUART1CLKBITFIELD)
#define REG_CGUBASEUART2CLK                       REG_32(0x400500A4)
#define REGBITS_CGUBASEUART2CLK                   REGBITS_32(0x400500A4, CGUBASEUART2CLKBITFIELD)
#define REG_CGUBASEUART3CLK                       REG_32(0x400500A8)
#define REGBITS_CGUBASEUART3CLK                   REGBITS_32(0x400500A8, CGUBASEUART3CLKBITFIELD)
#define REG_CGUBASEUSB0CLK                        REG_32(0x40050060)
#define REGBITS_CGUBASEUSB0CLK                    REGBITS_32(0x40050060, CGUBASEUSB0CLKBITFIELD)
#define REG_CGUBASEUSB1CLK                        REG_32(0x40050068)
#define REGBITS_CGUBASEUSB1CLK                    REGBITS_32(0x40050068, CGUBASEUSB1CLKBITFIELD)
#define REG_CGUBASEVADCCLK                        REG_32(0x4005008C)
#define REGBITS_CGUBASEVADCCLK                    REGBITS_32(0x4005008C, CGUBASEVADCCLKBITFIELD)

#define REG_CGUOUTCLK0CTRL                        REG_32(0x40050048)
#define REGBITS_CGUOUTCLK0CTRL                    REGBITS_32(0x40050048, CGUOUTCLK0CTRLBITFIELD)
#define REG_CGUOUTCLK10CTRL                       REG_32(0x40050070)
#define REGBITS_CGUOUTCLK10CTRL                   REGBITS_32(0x40050070, CGUOUTCLK10CTRLBITFIELD)
#define REG_CGUOUTCLK11CTRL                       REG_32(0x40050074)
#define REGBITS_CGUOUTCLK11CTRL                   REGBITS_32(0x40050074, CGUOUTCLK11CTRLBITFIELD)
#define REG_CGUOUTCLK13CTRL                       REG_32(0x4005007C)
#define REGBITS_CGUOUTCLK13CTRL                   REGBITS_32(0x4005007C, CGUOUTCLK13CTRLBITFIELD)
#define REG_CGUOUTCLK14CTRL                       REG_32(0x40050080)
#define REGBITS_CGUOUTCLK14CTRL                   REGBITS_32(0x40050080, CGUOUTCLK14CTRLBITFIELD)
#define REG_CGUOUTCLK15CTRL                       REG_32(0x40050084)
#define REGBITS_CGUOUTCLK15CTRL                   REGBITS_32(0x40050084, CGUOUTCLK15CTRLBITFIELD)
#define REG_CGUOUTCLK16CTRL                       REG_32(0x40050088)
#define REGBITS_CGUOUTCLK16CTRL                   REGBITS_32(0x40050088, CGUOUTCLK16CTRLBITFIELD)
#define REG_CGUOUTCLK17CTRL                       REG_32(0x4005008C)
#define REGBITS_CGUOUTCLK17CTRL                   REGBITS_32(0x4005008C, CGUOUTCLK17CTRLBITFIELD)
#define REG_CGUOUTCLK18CTRL                       REG_32(0x40050090)
#define REGBITS_CGUOUTCLK18CTRL                   REGBITS_32(0x40050090, CGUOUTCLK18CTRLBITFIELD)
#define REG_CGUOUTCLK19CTRL                       REG_32(0x40050094)
#define REGBITS_CGUOUTCLK19CTRL                   REGBITS_32(0x40050094, CGUOUTCLK19CTRLBITFIELD)
#define REG_CGUOUTCLK1CTRL                        REG_32(0x4005004C)
#define REGBITS_CGUOUTCLK1CTRL                    REGBITS_32(0x4005004C, CGUOUTCLK1CTRLBITFIELD)
#define REG_CGUOUTCLK20CTRL                       REG_32(0x40050098)
#define REGBITS_CGUOUTCLK20CTRL                   REGBITS_32(0x40050098, CGUOUTCLK20CTRLBITFIELD)
#define REG_CGUOUTCLK2CTRL                        REG_32(0x40050050)
#define REGBITS_CGUOUTCLK2CTRL                    REGBITS_32(0x40050050, CGUOUTCLK2CTRLBITFIELD)
#define REG_CGUOUTCLK3CTRL                        REG_32(0x40050054)
#define REGBITS_CGUOUTCLK3CTRL                    REGBITS_32(0x40050054, CGUOUTCLK3CTRLBITFIELD)
#define REG_CGUOUTCLK4CTRL                        REG_32(0x40050058)
#define REGBITS_CGUOUTCLK4CTRL                    REGBITS_32(0x40050058, CGUOUTCLK4CTRLBITFIELD)
#define REG_CGUOUTCLK5CTRL                        REG_32(0x4005005C)
#define REGBITS_CGUOUTCLK5CTRL                    REGBITS_32(0x4005005C, CGUOUTCLK5CTRLBITFIELD)
#define REG_CGUOUTCLK7CTRL                        REG_32(0x40050064)
#define REGBITS_CGUOUTCLK7CTRL                    REGBITS_32(0x40050064, CGUOUTCLK7CTRLBITFIELD)
#define REG_CGUOUTCLK8CTRL                        REG_32(0x40050068)
#define REGBITS_CGUOUTCLK8CTRL                    REGBITS_32(0x40050068, CGUOUTCLK8CTRLBITFIELD)
#define REG_CGUOUTCLK9CTRL                        REG_32(0x4005006C)
#define REGBITS_CGUOUTCLK9CTRL                    REGBITS_32(0x4005006C, CGUOUTCLK9CTRLBITFIELD)

#define REG_CGUPLL0CTRL                           REG_32(0x40050020)
#define REGBITS_CGUPLL0CTRL                       REGBITS_32(0x40050020, CGUPLL0CTRLBITFIELD)
#define REG_CGUPLL0MDIV                           REG_32(0x40050024)
#define REGBITS_CGUPLL0MDIV                       REGBITS_32(0x40050024, CGUPLL0MDIVBITFIELD)
#define REG_CGUPLL0NPDIV                          REG_32(0x40050028)
#define REGBITS_CGUPLL0NPDIV                      REGBITS_32(0x40050028, CGUPLL0NPDIVBITFIELD)
#define REG_CGUPLL0STAT                           REG_32(0x4005001C)
#define REGBITS_CGUPLL0STAT                       REGBITS_32(0x4005001C, CGUPLL0STATBITFIELD)
#define REG_CGUPLL1CTRL                           REG_32(0x40050044)
#define REGBITS_CGUPLL1CTRL                       REGBITS_32(0x40050044, CGUPLL1CTRLBITFIELD)
#define REG_CGUPLL1STAT                           REG_32(0x40050040)
#define REGBITS_CGUPLL1STAT                       REGBITS_32(0x40050040, CGUPLL1STATBITFIELD)
#define REG_CGUXTALOSCCTRL                        REG_32(0x40050018)
#define REGBITS_CGUXTALOSCCTRL                    REGBITS_32(0x40050018, CGUXTALOSCCTRLBITFIELD)

#endif /* MCU_CGU_H__ */
