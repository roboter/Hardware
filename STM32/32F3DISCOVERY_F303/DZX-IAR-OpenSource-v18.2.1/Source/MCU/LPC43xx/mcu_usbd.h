/*******************************************************************************************************************************************

    DZX | LPC43xx | USB DEVICE                                                                                            VERSION 18.2.1
    ------------------------------------------------------------------------------------------------------------------------------------

    This is part of the MCU peripheral drivers and provides support for the USB device controller.

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
#ifndef MCU_USBD_H__
#define MCU_USBD_H__

#include "Kernel/kernel.h"

/*******************************************************************************************************************************************
    DEFINITIONS
*******************************************************************************************************************************************/
#define USBD_HIGHSPEEDCAPABLE       TRUE       /* This device is capable of high speed */

/*******************************************************************************************************************************************
    REGISTER DEFINITIONS
*******************************************************************************************************************************************/ 
#define REG_USBD0         ((REG_USBD*)0x40006100)
#define REG_USBD1         ((REG_USBD*)0x40007100)

typedef struct USB0CAPLENGTHBITFIELD {
    UINT32 CAPLENGTH               :8;
    UINT32 HCIVERSION              :16;
    UINT32                         :8;
} USB0CAPLENGTHBITFIELD;

typedef struct USB0HCSPARAMSBITFIELD {
    UINT32 NPORTS                  :4;
    UINT32 PPC                     :1;
    UINT32                         :3;
    UINT32 NPCC                    :4;
    UINT32 NCC                     :4;
    UINT32 PI                      :1;
    UINT32                         :3;
    UINT32 NPTT                    :4;
    UINT32 NTT                     :4;
    UINT32                         :4;
} USB0HCSPARAMSBITFIELD;

typedef struct USB0HCCPARAMSBITFIELD {
    UINT32 ADC                     :1;
    UINT32 PFL                     :1;
    UINT32 ASP                     :1;
    UINT32                         :1;
    UINT32 IST                     :4;
    UINT32 EECP                    :8;
    UINT32                         :16;
} USB0HCCPARAMSBITFIELD;

typedef struct USB0DCIVERSIONBITFIELD {
    UINT32 DCIVERSION              :16;
    UINT32                         :16;
} USB0DCIVERSIONBITFIELD;

typedef struct USB0DCCPARAMSBITFIELD {
    UINT32 DEN                     :5;
    UINT32                         :2;
    UINT32 DC                      :1;
    UINT32 HC                      :1;
    UINT32                         :23;
} USB0DCCPARAMSBITFIELD;

typedef struct USB0USBCMDBITFIELD {
    UINT32 RS                      :1;
    UINT32 RST                     :1;
    UINT32 FS0                     :1;
    UINT32 FS1                     :1;
    UINT32 PSE                     :1;
    UINT32 ASE                     :1;
    UINT32 IAA                     :1;
    UINT32                         :1;
    UINT32 ASP                     :2;
    UINT32                         :1;
    UINT32 ASPE                    :1;
    UINT32                         :1;
    UINT32 SUTW                    :1;
    UINT32 ATDTW                   :1;
    UINT32 FS2                     :1;
    UINT32 ITC                     :8;
    UINT32                         :8;
} USB0USBCMDBITFIELD;

typedef struct USB0USBSTSBITFIELD {
    UINT32 UI                      :1;
    UINT32 UEI                     :1;
    UINT32 PCI                     :1;
    UINT32 FRI                     :1;
    UINT32                         :1;
    UINT32 AAI                     :1;
    UINT32 URI                     :1;
    UINT32 SRI                     :1;
    UINT32 SLI                     :1;
    UINT32                         :3;
    UINT32 HCH                     :1;
    UINT32 RCL                     :1;
    UINT32 PS                      :1;
    UINT32 AS                      :1;
    UINT32 NAKI                    :1;
    UINT32                         :1;
    UINT32 UAI                     :1;
    UINT32 UPI                     :1;
    UINT32                         :12;
} USB0USBSTSBITFIELD;

typedef struct USB0USBINTRBITFIELD {
    UINT32 UE                      :1;
    UINT32 UEE                     :1;
    UINT32 PCE                     :1;
    UINT32 FRE                     :1;
    UINT32                         :1;
    UINT32 AAE                     :1;
    UINT32 URE                     :1;
    UINT32 SRE                     :1;
    UINT32 SLE                     :1;
    UINT32                         :7;
    UINT32 NAKE                    :1;
    UINT32                         :1;
    UINT32 UAIE                    :1;
    UINT32 UPIA                    :1;
    UINT32                         :12;
} USB0USBINTRBITFIELD;

typedef struct USB0TTCTRLBITFIELD {
    UINT32                         :24;
    UINT32 TTHA                    :7;
    UINT32                         :1;
} USB0TTCTRLBITFIELD;

typedef struct USB0BURSTSIZEBITFIELD {
    UINT32 RXPBURST                :8;
    UINT32 TXPBURST                :8;
    UINT32                         :16;
} USB0BURSTSIZEBITFIELD;

typedef struct USB0TXFILLTUNINGBITFIELD {
    UINT32 TXSCHOH                 :8;
    UINT32 TXSCHEALTH              :5;
    UINT32                         :3;
    UINT32 TXFIFOTHRES             :6;
    UINT32                         :10;
} USB0TXFILLTUNINGBITFIELD;

typedef struct USB0BINTERVALBITFIELD {
    UINT32 BINT                    :4;
    UINT32                         :28;
} USB0BINTERVALBITFIELD;

typedef struct USB0PORTSC1BITFIELD {
    UINT32 CCS                     :1;
    UINT32 CSC                     :1;
    UINT32 PE                      :1;
    UINT32 PEC                     :1;
    UINT32 OCA                     :1;
    UINT32 OCC                     :1;
    UINT32 FPR                     :1;
    UINT32 SUSP                    :1;
    UINT32 PR                      :1;
    UINT32 HSP                     :1;
    UINT32 LS                      :2;
    UINT32 PP                      :1;
    UINT32                         :1;
    UINT32 PIC                     :2;
    UINT32 PTC                     :4;
    UINT32 WKCN                    :1;
    UINT32 WKDC                    :1;
    UINT32 WKOC                    :1;
    UINT32 PHCD                    :1;
    UINT32 PFSC                    :1;
    UINT32                         :1;
    UINT32 PSPD                    :2;
    UINT32                         :4;
} USB0PORTSC1BITFIELD;

typedef struct USB0OTGSCBITFIELD {
    UINT32 VD                      :1;
    UINT32 VC                      :1;
    UINT32 HAAR                    :1;
    UINT32 OT                      :1;
    UINT32 DP                      :1;
    UINT32 IDPU                    :1;
    UINT32 HADP                    :1;
    UINT32 HABA                    :1;
    UINT32 ID                      :1;
    UINT32 AVV                     :1;
    UINT32 ASV                     :1;
    UINT32 BSV                     :1;
    UINT32 BSE                     :1;
    UINT32 MS1T                    :1;
    UINT32 DPS                     :1;
    UINT32                         :1;
    UINT32 IDIS                    :1;
    UINT32 AVVIS                   :1;
    UINT32 ASVIS                   :1;
    UINT32 BSVIS                   :1;
    UINT32 BSEIS                   :1;
    UINT32 MS1S                    :1;
    UINT32 DPIS                    :1;
    UINT32                         :1;
    UINT32 IDIE                    :1;
    UINT32 AVVIE                   :1;
    UINT32 ASVIE                   :1;
    UINT32 BSVIE                   :1;
    UINT32 BSEIE                   :1;
    UINT32 MS1E                    :1;
    UINT32 DPIE                    :1;
    UINT32                         :1;
} USB0OTGSCBITFIELD;

typedef struct USB0USBMODEBITFIELD {
    UINT32 CM                      :2;
    UINT32 ES                      :1;
    UINT32 SLOM                    :1;
    UINT32 SDIS                    :1;
    UINT32 VBPS                    :1;
    UINT32                         :26;
} USB0USBMODEBITFIELD;

typedef struct USB0ENDPTSTATUSBITFIELD {
    UINT32 ERBR0                   :1;
    UINT32 ERBR1                   :1;
    UINT32 ERBR2                   :1;
    UINT32 ERBR3                   :1;
    UINT32 ERBR4                   :1;
    UINT32 ERBR5                   :1;
    UINT32                         :10;
    UINT32 ETBR0                   :1;
    UINT32 ETBR1                   :1;
    UINT32 ETBR2                   :1;
    UINT32 ETBR3                   :1;
    UINT32 ETBR4                   :1;
    UINT32 ETBR5                   :1;
    UINT32                         :10;
} USB0ENDPTSTATUSBITFIELD;

typedef struct USB0ENDPTCTRL1BITFIELD {
    UINT32 RXS                     :1;
    UINT32                         :1;
    UINT32 RXT                     :2;
    UINT32                         :1;
    UINT32 RXI                     :1;
    UINT32 RXR                     :1;
    UINT32 RXE                     :1;
    UINT32                         :8;
    UINT32 TXS                     :1;
    UINT32                         :1;
    UINT32 TXT                     :2;
    UINT32                         :1;
    UINT32 TXI                     :1;
    UINT32 TXR                     :1;
    UINT32 TXE                     :1;
    UINT32                         :8;
} USB0ENDPTCTRL1BITFIELD;

typedef struct REG_USBD {
    PREG_BITS32(CAPLENGTH, USB0CAPLENGTHBITFIELD);
    PREG_BITS32(HCSPARAMS, USB0HCSPARAMSBITFIELD);
    PREG_BITS32(HCCPARAMS, USB0HCCPARAMSBITFIELD);
    volatile UINT32 reserved1[5];
    PREG_BITS32(DCIVERSION, USB0DCIVERSIONBITFIELD);
    PREG_BITS32(DCCPARAMS, USB0DCCPARAMSBITFIELD);
    volatile UINT32 reserved2[6];
    PREG_BITS32(USBCMD, USB0USBCMDBITFIELD);
    PREG_BITS32(USBSTS, USB0USBSTSBITFIELD);
    PREG_BITS32(USBINTR, USB0USBINTRBITFIELD);
    PREG_32(FRINDEX);
    PREG_RSRVD32(reserved3);
    PREG_32(DEVICEADDR);
    PREG_32(ENDPOINTLISTADDR);
    PREG_BITS32(TTCTRL, USB0TTCTRLBITFIELD);
    PREG_BITS32(BURSTSIZE, USB0BURSTSIZEBITFIELD);
    PREG_BITS32(TXFILLTUNING, USB0TXFILLTUNINGBITFIELD);
    volatile UINT32 reserved4[3];
    PREG_BITS32(BINTERVAL, USB0BINTERVALBITFIELD);
    PREG_32(ENDPTNAK);
    PREG_32(ENDPTNAKEN);
    PREG_RSRVD32(reserved5);
    PREG_BITS32(PORTSC1, USB0PORTSC1BITFIELD);
    volatile UINT32 reserved6[7];
    PREG_BITS32(OTGSC, USB0OTGSCBITFIELD);
    PREG_BITS32(USBMODE, USB0USBMODEBITFIELD);
    PREG_32(ENDPTSETUPSTAT);
    PREG_32(ENDPTPRIME);
    PREG_32(ENDPTFLUSH);
    PREG_BITS32(ENDPTSTATUS, USB0ENDPTSTATUSBITFIELD);
    PREG_32(ENDPTCOMPLETE);
    PREG_BITS32(ENDPTCTRL, USB0ENDPTCTRL1BITFIELD)[6];
} REG_USBD;

/***************************************************************************************************************************************//**

    Represents a USB device controller driver to be used by the USB device stack.
    @module     INTERNAL

*******************************************************************************************************************************************/
typedef struct LPC43XX_USBDCD {
    REG_USBD* REG;                          /**< A pointer to the internal registers for the USB device perhiperal. */
    USBREQUEST setup;
    BOOLEAN rxsetup;
} USBDCD;

#endif /* MCU_USBD_H__ */
