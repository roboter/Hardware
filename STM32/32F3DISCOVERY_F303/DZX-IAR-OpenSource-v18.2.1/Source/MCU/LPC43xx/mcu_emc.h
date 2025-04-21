/*******************************************************************************************************************************************

    DZX | LPC43xx | EMC                                                                                                   VERSION 18.2.1
    ------------------------------------------------------------------------------------------------------------------------------------

    This file is part of the MCU peripheral drivers and provides definitions for the external memory controller (EMC) registers.

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
#ifndef MCU_EMC_H__
#define MCU_EMC_H__


#include "Kernel/kernel.h"

#define REG_EMC0            ((REG_EMC*)0x40005000)

typedef struct EMCCLKDELAYBITFIELD
{
    UINT32 CLK0DELAY               :3;
    UINT32                         :1;
    UINT32 CLK1DELAY               :3;
    UINT32                         :1;
    UINT32 CLK2DELAY               :3;
    UINT32                         :1;
    UINT32 CLK3DELAY               :3;
    UINT32                         :1;
    UINT32 CKE0DELAY               :3;
    UINT32                         :1;
    UINT32 CKE1DELAY               :3;
    UINT32                         :1;
    UINT32 CKE2DELAY               :3;
    UINT32                         :1;
    UINT32 CKE3DELAY               :3;
    UINT32                         :1;
} EMCCLKDELAYBITFIELD;
typedef struct EMCCTRLDELAYBITFIELD
{
    UINT32 RASDELAY                :3;
    UINT32                         :1;
    UINT32 CASDELAY                :3;
    UINT32                         :1;
    UINT32 OEDELAY                 :3;
    UINT32                         :1;
    UINT32 WEDELAY                 :3;
    UINT32                         :1;
    UINT32 BLS0DELAY               :3;
    UINT32                         :1;
    UINT32 BLS1DELAY               :3;
    UINT32                         :1;
    UINT32 BLS2DELAY               :3;
    UINT32                         :1;
    UINT32 BLS3DELAY               :3;
    UINT32                         :1;
} EMCCTRLDELAYBITFIELD;
typedef struct EMCCSDELAYBITFIELD
{
    UINT32 DYCS0DELAY              :3;
    UINT32                         :1;
    UINT32 DYCS1DELAY              :3;
    UINT32                         :1;
    UINT32 DYCS2DELAY              :3;
    UINT32                         :1;
    UINT32 DYCS3DELAY              :3;
    UINT32                         :1;
    UINT32 CS0DELAY                :3;
    UINT32                         :1;
    UINT32 CS1DELAY                :3;
    UINT32                         :1;
    UINT32 CS2DELAY                :3;
    UINT32                         :1;
    UINT32 CS3DELAY                :3;
    UINT32                         :1;
} EMCCSDELAYBITFIELD;
typedef struct EMCDOUTDELAYBITFIELD
{
    UINT32 DQM0DELAY               :3;
    UINT32                         :1;
    UINT32 DQM1DELAY               :3;
    UINT32                         :1;
    UINT32 DQM2DELAY               :3;
    UINT32                         :1;
    UINT32 DQM3DELAY               :3;
    UINT32                         :1;
    UINT32 D0DELAY                 :3;
    UINT32                         :1;
    UINT32 D1DELAY                 :3;
    UINT32                         :1;
    UINT32 D2DELAY                 :3;
    UINT32                         :1;
    UINT32 D3DELAY                 :3;
    UINT32                         :1;
} EMCDOUTDELAYBITFIELD;
typedef struct EMCFBCLKDELAYBITFIELD
{
    UINT32 FBCLK0DELAY             :3;
    UINT32                         :1;
    UINT32 FBCLK1DELAY             :3;
    UINT32                         :1;
    UINT32 FBCLK2DELAY             :3;
    UINT32                         :1;
    UINT32 FBCLK3DELAY             :3;
    UINT32                         :1;
    UINT32 CCLKDELAY               :3;
    UINT32                         :13;
} EMCFBCLKDELAYBITFIELD;
typedef struct EMCADDRDELAY0BITFIELD
{
    UINT32 ADDR0DELAY              :3;
    UINT32                         :1;
    UINT32 ADDR1DELAY              :3;
    UINT32                         :1;
    UINT32 ADDR2DELAY              :3;
    UINT32                         :1;
    UINT32 ADDR3DELAY              :3;
    UINT32                         :1;
    UINT32 ADDR4DELAY              :3;
    UINT32                         :1;
    UINT32 ADDR5DELAY              :3;
    UINT32                         :1;
    UINT32 ADDR6DELAY              :3;
    UINT32                         :1;
    UINT32 ADDR7DELAY              :3;
    UINT32                         :1;
} EMCADDRDELAY0BITFIELD;
typedef struct EMCADDRDELAY1BITFIELD
{
    UINT32 ADDR8DELAY              :3;
    UINT32                         :1;
    UINT32 ADDR9DELAY              :3;
    UINT32                         :1;
    UINT32 ADDR10DELAY             :3;
    UINT32                         :1;
    UINT32 ADDR11DELAY             :3;
    UINT32                         :1;
    UINT32 ADDR12DELAY             :3;
    UINT32                         :1;
    UINT32 ADDR13DELAY             :3;
    UINT32                         :1;
    UINT32 ADDR14DELAY             :3;
    UINT32                         :1;
    UINT32 ADDR15DELAY             :3;
    UINT32                         :1;
} EMCADDRDELAY1BITFIELD;
typedef struct EMCADDRDELAY2BITFIELD
{
    UINT32 ADDR16DELAY             :3;
    UINT32                         :1;
    UINT32 ADDR17DELAY             :3;
    UINT32                         :1;
    UINT32 ADDR18DELAY             :3;
    UINT32                         :1;
    UINT32 ADDR19DELAY             :3;
    UINT32                         :1;
    UINT32 ADDR20DELAY             :3;
    UINT32                         :1;
    UINT32 ADDR21DELAY             :3;
    UINT32                         :1;
    UINT32 ADDR22DELAY             :3;
    UINT32                         :1;
    UINT32 ADDR23DELAY             :3;
    UINT32                         :1;
} EMCADDRDELAY2BITFIELD;

typedef struct EMCDINDELAYBITFIELD {
    UINT32 DIN0DELAY               :3;
    UINT32                         :1;
    UINT32 DIN1DELAY               :3;
    UINT32                         :1;
    UINT32 DIN2DELAY               :3;
    UINT32                         :1;
    UINT32 DIN3DELAY               :3;
    UINT32                         :1;
    UINT32 DEN0DELAY               :3;
    UINT32                         :1;
    UINT32 DEN1DELAY               :3;
    UINT32                         :1;
    UINT32 DEN2DELAY               :3;
    UINT32                         :5;
} EMCDINDELAYBITFIELD;













typedef struct EMCCONTROLBITFIELD
{
    UINT32 E                       :1;
    UINT32 M                       :1;
    UINT32 L                       :1;
    UINT32                         :29;
} EMCCONTROLBITFIELD;
typedef struct EMCSTATUSBITFIELD
{
    UINT32 B                       :1;
    UINT32 S                       :1;
    UINT32 SA                      :1;
    UINT32                         :29;
} EMCSTATUSBITFIELD;
typedef struct EMCCONFIGBITFIELD
{
    UINT32 EM                      :1;
    UINT32                         :7;
    UINT32 CR                      :1;
    UINT32                         :23;
} EMCCONFIGBITFIELD;
typedef struct EMCDYNAMICCONTROLBITFIELD
{
    UINT32 CE                      :1;
    UINT32 CS                      :1;
    UINT32 SR                      :1;
    UINT32                         :2;
    UINT32 MMC                     :1;
    UINT32                         :1;
    UINT32 I                       :2;
    UINT32                         :4;
    UINT32 DP                      :1;
    UINT32                         :18;
} EMCDYNAMICCONTROLBITFIELD;
typedef struct EMCDYNAMICREFRESHBITFIELD
{
    UINT32 REFRESH                 :11;
    UINT32                         :21;
} EMCDYNAMICREFRESHBITFIELD;
typedef struct EMCDYNAMICREADCONFIGBITFIELD
{
    UINT32 RD                      :2;
    UINT32                         :30;
} EMCDYNAMICREADCONFIGBITFIELD;
typedef struct EMCDYNAMICTRPBITFIELD
{
    UINT32 TRP                     :4;
    UINT32                         :28;
} EMCDYNAMICTRPBITFIELD;
typedef struct EMCDYNAMICTRASBITFIELD
{
    UINT32 TRAS                    :4;
    UINT32                         :28;
} EMCDYNAMICTRASBITFIELD;
typedef struct EMCDYNAMICTSREXBITFIELD
{
    UINT32 TSREX                   :4;
    UINT32                         :28;
} EMCDYNAMICTSREXBITFIELD;
typedef struct EMCDYNAMICTAPRBITFIELD
{
    UINT32 TAPR                    :4;
    UINT32                         :28;
} EMCDYNAMICTAPRBITFIELD;
typedef struct EMCDYNAMICTDALBITFIELD
{
    UINT32 TDAL                    :4;
    UINT32                         :28;
} EMCDYNAMICTDALBITFIELD;
typedef struct EMCDYNAMICTWRBITFIELD
{
    UINT32 TWR                     :4;
    UINT32                         :28;
} EMCDYNAMICTWRBITFIELD;
typedef struct EMCDYNAMICTRCBITFIELD
{
    UINT32 TRC                     :5;
    UINT32                         :27;
} EMCDYNAMICTRCBITFIELD;
typedef struct EMCDYNAMICTRFCBITFIELD
{
    UINT32 TRFC                    :5;
    UINT32                         :27;
} EMCDYNAMICTRFCBITFIELD;
typedef struct EMCDYNAMICTXSRBITFIELD
{
    UINT32 TXSR                    :5;
    UINT32                         :27;
} EMCDYNAMICTXSRBITFIELD;
typedef struct EMCDYNAMICTRRDBITFIELD
{
    UINT32 TRRD                    :4;
    UINT32                         :28;
} EMCDYNAMICTRRDBITFIELD;
typedef struct EMCDYNAMICTMRDBITFIELD
{
    UINT32 TMRD                    :4;
    UINT32                         :28;
} EMCDYNAMICTMRDBITFIELD;
typedef struct EMCSTATICEXTENDEDWAITBITFIELD
{
    UINT32 EXTENDEDWAIT            :10;
    UINT32                         :22;
} EMCSTATICEXTENDEDWAITBITFIELD;
typedef struct EMCDYNAMICCONFIG0BITFIELD
{
    UINT32                         :3;
    UINT32 MD                      :2;
    UINT32                         :2;
    UINT32 AML                     :6;
    UINT32                         :1;
    UINT32 AMH                     :1;
    UINT32                         :4;
    UINT32 B                       :1;
    UINT32 P                       :1;
    UINT32                         :11;
} EMCDYNAMICCONFIG0BITFIELD;
typedef struct EMCDYNAMICRASCAS0BITFIELD
{
    UINT32 RAS                     :2;
    UINT32                         :6;
    UINT32 CAS                     :2;
    UINT32                         :22;
} EMCDYNAMICRASCAS0BITFIELD;
typedef struct EMCDYNAMICCONFIG1BITFIELD
{
    UINT32                         :3;
    UINT32 MD                      :2;
    UINT32                         :2;
    UINT32 AML                     :6;
    UINT32                         :1;
    UINT32 AMH                     :1;
    UINT32                         :4;
    UINT32 B                       :1;
    UINT32 P                       :1;
    UINT32                         :11;
} EMCDYNAMICCONFIG1BITFIELD;
typedef struct EMCDYNAMICRASCAS1BITFIELD
{
    UINT32 RAS                     :2;
    UINT32                         :6;
    UINT32 CAS                     :2;
    UINT32                         :22;
} EMCDYNAMICRASCAS1BITFIELD;
typedef struct EMCDYNAMICCONFIG2BITFIELD
{
    UINT32                         :3;
    UINT32 MD                      :2;
    UINT32                         :2;
    UINT32 AML                     :6;
    UINT32                         :1;
    UINT32 AMH                     :1;
    UINT32                         :4;
    UINT32 B                       :1;
    UINT32 P                       :1;
    UINT32                         :11;
} EMCDYNAMICCONFIG2BITFIELD;
typedef struct EMCDYNAMICRASCAS2BITFIELD
{
    UINT32 RAS                     :2;
    UINT32                         :6;
    UINT32 CAS                     :2;
    UINT32                         :22;
} EMCDYNAMICRASCAS2BITFIELD;
typedef struct EMCDYNAMICCONFIG3BITFIELD
{
    UINT32                         :3;
    UINT32 MD                      :2;
    UINT32                         :2;
    UINT32 AML                     :6;
    UINT32                         :1;
    UINT32 AMH                     :1;
    UINT32                         :4;
    UINT32 B                       :1;
    UINT32 P                       :1;
    UINT32                         :11;
} EMCDYNAMICCONFIG3BITFIELD;
typedef struct EMCDYNAMICRASCAS3BITFIELD
{
    UINT32 RAS                     :2;
    UINT32                         :6;
    UINT32 CAS                     :2;
    UINT32                         :22;
} EMCDYNAMICRASCAS3BITFIELD;
typedef struct EMCSTATICCONFIG0BITFIELD
{
    UINT32 MW                      :2;
    UINT32                         :1;
    UINT32 PM                      :1;
    UINT32                         :2;
    UINT32 PC                      :1;
    UINT32 PB                      :1;
    UINT32 EW                      :1;
    UINT32                         :10;
    UINT32 B                       :1;
    UINT32 P                       :1;
    UINT32                         :11;
} EMCSTATICCONFIG0BITFIELD;
typedef struct EMCSTATICWAITWEN0BITFIELD
{
    UINT32 WAITWEN                 :4;
    UINT32                         :28;
} EMCSTATICWAITWEN0BITFIELD;
typedef struct EMCSTATICWAITOEN0BITFIELD
{
    UINT32 WAITOEN                 :4;
    UINT32                         :28;
} EMCSTATICWAITOEN0BITFIELD;
typedef struct EMCSTATICWAITRD0BITFIELD
{
    UINT32 WAITRD                  :5;
    UINT32                         :27;
} EMCSTATICWAITRD0BITFIELD;
typedef struct EMCSTATICWAITPAGE0BITFIELD
{
    UINT32 WAITPAGE                :5;
    UINT32                         :27;
} EMCSTATICWAITPAGE0BITFIELD;
typedef struct EMCSTATICWAITWR0BITFIELD
{
    UINT32 WAITWR                  :5;
    UINT32                         :27;
} EMCSTATICWAITWR0BITFIELD;
typedef struct EMCSTATICWAITTURN0BITFIELD
{
    UINT32 WAITTURN                :4;
    UINT32                         :28;
} EMCSTATICWAITTURN0BITFIELD;
typedef struct EMCSTATICCONFIG1BITFIELD
{
    UINT32 MW                      :2;
    UINT32                         :1;
    UINT32 PM                      :1;
    UINT32                         :2;
    UINT32 PC                      :1;
    UINT32 PB                      :1;
    UINT32 EW                      :1;
    UINT32                         :10;
    UINT32 B                       :1;
    UINT32 P                       :1;
    UINT32                         :11;
} EMCSTATICCONFIG1BITFIELD;
typedef struct EMCSTATICWAITWEN1BITFIELD
{
    UINT32 WAITWEN                 :4;
    UINT32                         :28;
} EMCSTATICWAITWEN1BITFIELD;
typedef struct EMCSTATICWAITOEN1BITFIELD
{
    UINT32 WAITOEN                 :4;
    UINT32                         :28;
} EMCSTATICWAITOEN1BITFIELD;
typedef struct EMCSTATICWAITRD1BITFIELD
{
    UINT32 WAITRD                  :5;
    UINT32                         :27;
} EMCSTATICWAITRD1BITFIELD;
typedef struct EMCSTATICWAITPAGE1BITFIELD
{
    UINT32 WAITPAGE                :5;
    UINT32                         :27;
} EMCSTATICWAITPAGE1BITFIELD;
typedef struct EMCSTATICWAITWR1BITFIELD
{
    UINT32 WAITWR                  :5;
    UINT32                         :27;
} EMCSTATICWAITWR1BITFIELD;
typedef struct EMCSTATICWAITTURN1BITFIELD
{
    UINT32 WAITTURN                :4;
    UINT32                         :28;
} EMCSTATICWAITTURN1BITFIELD;
typedef struct EMCSTATICCONFIG2BITFIELD
{
    UINT32 MW                      :2;
    UINT32                         :1;
    UINT32 PM                      :1;
    UINT32                         :2;
    UINT32 PC                      :1;
    UINT32 PB                      :1;
    UINT32 EW                      :1;
    UINT32                         :10;
    UINT32 B                       :1;
    UINT32 P                       :1;
    UINT32                         :11;
} EMCSTATICCONFIG2BITFIELD;
typedef struct EMCSTATICWAITWEN2BITFIELD
{
    UINT32 WAITWEN                 :4;
    UINT32                         :28;
} EMCSTATICWAITWEN2BITFIELD;
typedef struct EMCSTATICWAITOEN2BITFIELD
{
    UINT32 WAITOEN                 :4;
    UINT32                         :28;
} EMCSTATICWAITOEN2BITFIELD;
typedef struct EMCSTATICWAITRD2BITFIELD
{
    UINT32 WAITRD                  :5;
    UINT32                         :27;
} EMCSTATICWAITRD2BITFIELD;
typedef struct EMCSTATICWAITPAGE2BITFIELD
{
    UINT32 WAITPAGE                :5;
    UINT32                         :27;
} EMCSTATICWAITPAGE2BITFIELD;
typedef struct EMCSTATICWAITWR2BITFIELD
{
    UINT32 WAITWR                  :5;
    UINT32                         :27;
} EMCSTATICWAITWR2BITFIELD;
typedef struct EMCSTATICWAITTURN2BITFIELD
{
    UINT32 WAITTURN                :4;
    UINT32                         :28;
} EMCSTATICWAITTURN2BITFIELD;
typedef struct EMCSTATICCONFIG3BITFIELD
{
    UINT32 MW                      :2;
    UINT32                         :1;
    UINT32 PM                      :1;
    UINT32                         :2;
    UINT32 PC                      :1;
    UINT32 PB                      :1;
    UINT32 EW                      :1;
    UINT32                         :10;
    UINT32 B                       :1;
    UINT32 P                       :1;
    UINT32                         :11;
} EMCSTATICCONFIG3BITFIELD;
typedef struct EMCSTATICWAITWEN3BITFIELD
{
    UINT32 WAITWEN                 :4;
    UINT32                         :28;
} EMCSTATICWAITWEN3BITFIELD;
typedef struct EMCSTATICWAITOEN3BITFIELD
{
    UINT32 WAITOEN                 :4;
    UINT32                         :28;
} EMCSTATICWAITOEN3BITFIELD;
typedef struct EMCSTATICWAITRD3BITFIELD
{
    UINT32 WAITRD                  :5;
    UINT32                         :27;
} EMCSTATICWAITRD3BITFIELD;
typedef struct EMCSTATICWAITPAGE3BITFIELD
{
    UINT32 WAITPAGE                :5;
    UINT32                         :27;
} EMCSTATICWAITPAGE3BITFIELD;
typedef struct EMCSTATICWAITWR3BITFIELD
{
    UINT32 WAITWR                  :5;
    UINT32                         :27;
} EMCSTATICWAITWR3BITFIELD;
typedef struct EMCSTATICWAITTURN3BITFIELD
{
    UINT32 WAITTURN                :4;
    UINT32                         :28;
} EMCSTATICWAITTURN3BITFIELD;

typedef struct REG_EMC {
    PREG_BITS32(CONTROL, EMCCONTROLBITFIELD);
    PREG_BITS32(STATUS, EMCSTATUSBITFIELD);
    PREG_BITS32(CONFIG, EMCCONFIGBITFIELD);
    volatile UINT32 reserved0[5];
    PREG_BITS32(DYNAMICCONTROL, EMCDYNAMICCONTROLBITFIELD);
    PREG_BITS32(DYNAMICREFRESH, EMCDYNAMICREFRESHBITFIELD);
    PREG_BITS32(DYNAMICREADCONFIG, EMCDYNAMICREADCONFIGBITFIELD);
    PREG_RSRVD32(reserved1);
    PREG_BITS32(DYNAMICRP, EMCDYNAMICTRPBITFIELD);
   
    
} REG_EMC;


#define REG_EMCADDRDELAY0                         REG_32(0x40086D14)
#define REGBITS_EMCADDRDELAY0                     REGBITS_32(0x40086D14, EMCADDRDELAY0BITFIELD)
#define REG_EMCADDRDELAY1                         REG_32(0x40086D18)
#define REGBITS_EMCADDRDELAY1                     REGBITS_32(0x40086D18, EMCADDRDELAY1BITFIELD)
#define REG_EMCADDRDELAY2                         REG_32(0x40086D1C)
#define REGBITS_EMCADDRDELAY2                     REGBITS_32(0x40086D1C, EMCADDRDELAY2BITFIELD)
#define REG_EMCCLKDELAY                           REG_32(0x40086D00)
#define REGBITS_EMCCLKDELAY                       REGBITS_32(0x40086D00, EMCCLKDELAYBITFIELD)
#define REG_EMCCONFIG                             REG_32(0x40005008)
#define REGBITS_EMCCONFIG                         REGBITS_32(0x40005008, EMCCONFIGBITFIELD)
#define REG_EMCCONTROL                            REG_32(0x40005000)
#define REGBITS_EMCCONTROL                        REGBITS_32(0x40005000, EMCCONTROLBITFIELD)
#define REG_EMCCSDELAY                            REG_32(0x40086D08)
#define REGBITS_EMCCSDELAY                        REGBITS_32(0x40086D08, EMCCSDELAYBITFIELD)
#define REG_EMCCTRLDELAY                          REG_32(0x40086D04)
#define REGBITS_EMCCTRLDELAY                      REGBITS_32(0x40086D04, EMCCTRLDELAYBITFIELD)
#define REG_EMCDINDELAY                           REG_32(0x40086D24)
#define REGBITS_EMCDINDELAY                       REGBITS_32(0x40086D24, EMCDINDELAYBITFIELD)
#define REG_EMCDOUTDELAY                          REG_32(0x40086D0C)
#define REGBITS_EMCDOUTDELAY                      REGBITS_32(0x40086D0C, EMCDOUTDELAYBITFIELD)
#define REG_EMCDYNAMICCONFIG0                     REG_32(0x40005100)
#define REGBITS_EMCDYNAMICCONFIG0                 REGBITS_32(0x40005100, EMCDYNAMICCONFIG0BITFIELD)
#define REG_EMCDYNAMICCONFIG1                     REG_32(0x40005120)
#define REGBITS_EMCDYNAMICCONFIG1                 REGBITS_32(0x40005120, EMCDYNAMICCONFIG1BITFIELD)
#define REG_EMCDYNAMICCONFIG2                     REG_32(0x40005140)
#define REGBITS_EMCDYNAMICCONFIG2                 REGBITS_32(0x40005140, EMCDYNAMICCONFIG2BITFIELD)
#define REG_EMCDYNAMICCONFIG3                     REG_32(0x40005160)
#define REGBITS_EMCDYNAMICCONFIG3                 REGBITS_32(0x40005160, EMCDYNAMICCONFIG3BITFIELD)
#define REG_EMCDYNAMICCONTROL                     REG_32(0x40005020)
#define REGBITS_EMCDYNAMICCONTROL                 REGBITS_32(0x40005020, EMCDYNAMICCONTROLBITFIELD)
#define REG_EMCDYNAMICRASCAS0                     REG_32(0x40005104)
#define REGBITS_EMCDYNAMICRASCAS0                 REGBITS_32(0x40005104, EMCDYNAMICRASCAS0BITFIELD)
#define REG_EMCDYNAMICRASCAS1                     REG_32(0x40005124)
#define REGBITS_EMCDYNAMICRASCAS1                 REGBITS_32(0x40005124, EMCDYNAMICRASCAS1BITFIELD)
#define REG_EMCDYNAMICRASCAS2                     REG_32(0x40005144)
#define REGBITS_EMCDYNAMICRASCAS2                 REGBITS_32(0x40005144, EMCDYNAMICRASCAS2BITFIELD)
#define REG_EMCDYNAMICRASCAS3                     REG_32(0x40005164)
#define REGBITS_EMCDYNAMICRASCAS3                 REGBITS_32(0x40005164, EMCDYNAMICRASCAS3BITFIELD)
#define REG_EMCDYNAMICREADCONFIG                  REG_32(0x40005028)
#define REGBITS_EMCDYNAMICREADCONFIG              REGBITS_32(0x40005028, EMCDYNAMICREADCONFIGBITFIELD)
#define REG_EMCDYNAMICREFRESH                     REG_32(0x40005024)
#define REGBITS_EMCDYNAMICREFRESH                 REGBITS_32(0x40005024, EMCDYNAMICREFRESHBITFIELD)
#define REG_EMCDYNAMICTAPR                        REG_32(0x4000503C)
#define REGBITS_EMCDYNAMICTAPR                    REGBITS_32(0x4000503C, EMCDYNAMICTAPRBITFIELD)
#define REG_EMCDYNAMICTDAL                        REG_32(0x40005040)
#define REGBITS_EMCDYNAMICTDAL                    REGBITS_32(0x40005040, EMCDYNAMICTDALBITFIELD)
#define REG_EMCDYNAMICTMRD                        REG_32(0x40005058)
#define REGBITS_EMCDYNAMICTMRD                    REGBITS_32(0x40005058, EMCDYNAMICTMRDBITFIELD)
#define REG_EMCDYNAMICTRAS                        REG_32(0x40005034)
#define REGBITS_EMCDYNAMICTRAS                    REGBITS_32(0x40005034, EMCDYNAMICTRASBITFIELD)
#define REG_EMCDYNAMICTRC                         REG_32(0x40005048)
#define REGBITS_EMCDYNAMICTRC                     REGBITS_32(0x40005048, EMCDYNAMICTRCBITFIELD)
#define REG_EMCDYNAMICTRFC                        REG_32(0x4000504C)
#define REGBITS_EMCDYNAMICTRFC                    REGBITS_32(0x4000504C, EMCDYNAMICTRFCBITFIELD)
#define REG_EMCDYNAMICTRP                         REG_32(0x40005030)
#define REGBITS_EMCDYNAMICTRP                     REGBITS_32(0x40005030, EMCDYNAMICTRPBITFIELD)
#define REG_EMCDYNAMICTRRD                        REG_32(0x40005054)
#define REGBITS_EMCDYNAMICTRRD                    REGBITS_32(0x40005054, EMCDYNAMICTRRDBITFIELD)
#define REG_EMCDYNAMICTSREX                       REG_32(0x40005038)
#define REGBITS_EMCDYNAMICTSREX                   REGBITS_32(0x40005038, EMCDYNAMICTSREXBITFIELD)
#define REG_EMCDYNAMICTWR                         REG_32(0x40005044)
#define REGBITS_EMCDYNAMICTWR                     REGBITS_32(0x40005044, EMCDYNAMICTWRBITFIELD)
#define REG_EMCDYNAMICTXSR                        REG_32(0x40005050)
#define REGBITS_EMCDYNAMICTXSR                    REGBITS_32(0x40005050, EMCDYNAMICTXSRBITFIELD)
#define REG_EMCFBCLKDELAY                         REG_32(0x40086D10)
#define REGBITS_EMCFBCLKDELAY                     REGBITS_32(0x40086D10, EMCFBCLKDELAYBITFIELD)
#define REG_EMCSTATICCONFIG0                      REG_32(0x40005200)
#define REGBITS_EMCSTATICCONFIG0                  REGBITS_32(0x40005200, EMCSTATICCONFIG0BITFIELD)
#define REG_EMCSTATICCONFIG1                      REG_32(0x40005220)
#define REGBITS_EMCSTATICCONFIG1                  REGBITS_32(0x40005220, EMCSTATICCONFIG1BITFIELD)
#define REG_EMCSTATICCONFIG2                      REG_32(0x40005240)
#define REGBITS_EMCSTATICCONFIG2                  REGBITS_32(0x40005240, EMCSTATICCONFIG2BITFIELD)
#define REG_EMCSTATICCONFIG3                      REG_32(0x40005260)
#define REGBITS_EMCSTATICCONFIG3                  REGBITS_32(0x40005260, EMCSTATICCONFIG3BITFIELD)
#define REG_EMCSTATICEXTENDEDWAIT                 REG_32(0x40005080)
#define REGBITS_EMCSTATICEXTENDEDWAIT             REGBITS_32(0x40005080, EMCSTATICEXTENDEDWAITBITFIELD)
#define REG_EMCSTATICWAITOEN0                     REG_32(0x40005208)
#define REGBITS_EMCSTATICWAITOEN0                 REGBITS_32(0x40005208, EMCSTATICWAITOEN0BITFIELD)
#define REG_EMCSTATICWAITOEN1                     REG_32(0x40005228)
#define REGBITS_EMCSTATICWAITOEN1                 REGBITS_32(0x40005228, EMCSTATICWAITOEN1BITFIELD)
#define REG_EMCSTATICWAITOEN2                     REG_32(0x40005248)
#define REGBITS_EMCSTATICWAITOEN2                 REGBITS_32(0x40005248, EMCSTATICWAITOEN2BITFIELD)
#define REG_EMCSTATICWAITOEN3                     REG_32(0x40005268)
#define REGBITS_EMCSTATICWAITOEN3                 REGBITS_32(0x40005268, EMCSTATICWAITOEN3BITFIELD)
#define REG_EMCSTATICWAITPAGE0                    REG_32(0x40005210)
#define REGBITS_EMCSTATICWAITPAGE0                REGBITS_32(0x40005210, EMCSTATICWAITPAGE0BITFIELD)
#define REG_EMCSTATICWAITPAGE1                    REG_32(0x40005230)
#define REGBITS_EMCSTATICWAITPAGE1                REGBITS_32(0x40005230, EMCSTATICWAITPAGE1BITFIELD)
#define REG_EMCSTATICWAITPAGE2                    REG_32(0x40005250)
#define REGBITS_EMCSTATICWAITPAGE2                REGBITS_32(0x40005250, EMCSTATICWAITPAGE2BITFIELD)
#define REG_EMCSTATICWAITPAGE3                    REG_32(0x40005270)
#define REGBITS_EMCSTATICWAITPAGE3                REGBITS_32(0x40005270, EMCSTATICWAITPAGE3BITFIELD)
#define REG_EMCSTATICWAITRD0                      REG_32(0x4000520C)
#define REGBITS_EMCSTATICWAITRD0                  REGBITS_32(0x4000520C, EMCSTATICWAITRD0BITFIELD)
#define REG_EMCSTATICWAITRD1                      REG_32(0x4000522C)
#define REGBITS_EMCSTATICWAITRD1                  REGBITS_32(0x4000522C, EMCSTATICWAITRD1BITFIELD)
#define REG_EMCSTATICWAITRD2                      REG_32(0x4000524C)
#define REGBITS_EMCSTATICWAITRD2                  REGBITS_32(0x4000524C, EMCSTATICWAITRD2BITFIELD)
#define REG_EMCSTATICWAITRD3                      REG_32(0x4000526C)
#define REGBITS_EMCSTATICWAITRD3                  REGBITS_32(0x4000526C, EMCSTATICWAITRD3BITFIELD)
#define REG_EMCSTATICWAITTURN0                    REG_32(0x40005218)
#define REGBITS_EMCSTATICWAITTURN0                REGBITS_32(0x40005218, EMCSTATICWAITTURN0BITFIELD)
#define REG_EMCSTATICWAITTURN1                    REG_32(0x40005238)
#define REGBITS_EMCSTATICWAITTURN1                REGBITS_32(0x40005238, EMCSTATICWAITTURN1BITFIELD)
#define REG_EMCSTATICWAITTURN2                    REG_32(0x40005258)
#define REGBITS_EMCSTATICWAITTURN2                REGBITS_32(0x40005258, EMCSTATICWAITTURN2BITFIELD)
#define REG_EMCSTATICWAITTURN3                    REG_32(0x40005278)
#define REGBITS_EMCSTATICWAITTURN3                REGBITS_32(0x40005278, EMCSTATICWAITTURN3BITFIELD)
#define REG_EMCSTATICWAITWEN0                     REG_32(0x40005204)
#define REGBITS_EMCSTATICWAITWEN0                 REGBITS_32(0x40005204, EMCSTATICWAITWEN0BITFIELD)
#define REG_EMCSTATICWAITWEN1                     REG_32(0x40005224)
#define REGBITS_EMCSTATICWAITWEN1                 REGBITS_32(0x40005224, EMCSTATICWAITWEN1BITFIELD)
#define REG_EMCSTATICWAITWEN2                     REG_32(0x40005244)
#define REGBITS_EMCSTATICWAITWEN2                 REGBITS_32(0x40005244, EMCSTATICWAITWEN2BITFIELD)
#define REG_EMCSTATICWAITWEN3                     REG_32(0x40005264)
#define REGBITS_EMCSTATICWAITWEN3                 REGBITS_32(0x40005264, EMCSTATICWAITWEN3BITFIELD)
#define REG_EMCSTATICWAITWR0                      REG_32(0x40005214)
#define REGBITS_EMCSTATICWAITWR0                  REGBITS_32(0x40005214, EMCSTATICWAITWR0BITFIELD)
#define REG_EMCSTATICWAITWR1                      REG_32(0x40005234)
#define REGBITS_EMCSTATICWAITWR1                  REGBITS_32(0x40005234, EMCSTATICWAITWR1BITFIELD)
#define REG_EMCSTATICWAITWR2                      REG_32(0x40005254)
#define REGBITS_EMCSTATICWAITWR2                  REGBITS_32(0x40005254, EMCSTATICWAITWR2BITFIELD)
#define REG_EMCSTATICWAITWR3                      REG_32(0x40005274)
#define REGBITS_EMCSTATICWAITWR3                  REGBITS_32(0x40005274, EMCSTATICWAITWR3BITFIELD)
#define REG_EMCSTATUS                             REG_32(0x40005004)
#define REGBITS_EMCSTATUS                         REGBITS_32(0x40005004, EMCSTATUSBITFIELD)




#endif /* MCU_EMC_H__ */
