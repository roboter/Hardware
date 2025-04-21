/*******************************************************************************************************************************************

    DZX | LPC13x1x2x3 | USB DEVICE                                                                                        VERSION 18.2.1
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
#define USBD_HIGHSPEEDCAPABLE       FALSE       /* This device is not capable of high speed */

/*******************************************************************************************************************************************
    REGISTER DEFINITIONS
*******************************************************************************************************************************************/
#define REG_USBD0         ((REG_USBD*)0x40020000)

typedef struct USBDEVINTBITFIELD {
    UINT32 FRAME               :1;
    UINT32 EP0                     :1;
    UINT32 EP1                     :1;
    UINT32 EP2                     :1;
    UINT32 EP3                     :1;
    UINT32 EP4                     :1;
    UINT32 EP5                     :1;
    UINT32 EP6                     :1;
    UINT32 EP7                     :1;
    UINT32 DEVSTAT                 :1;
    UINT32 CCEMPTY                 :1;
    UINT32 CDFULL                  :1;
    UINT32 RXENDPKT                :1;
    UINT32 TXENDPKT                :1;
    UINT32                         :18;
} USBDEVINTBITFIELD;

typedef struct USBCMDCODEBITFIELD {
    UINT32                         :8;
    UINT32 CMDPHASE                :8;
    UINT32 CMDCODE                 :8;
    UINT32                         :8;
} USBCMDCODEBITFIELD;

typedef struct USBCMDDATABITFIELD {
    UINT32 CMDDATA                 :8;
    UINT32                         :24;
} USBCMDDATABITFIELD;

typedef struct USBRXPLENBITFIELD {
    UINT32 PKTLNGTH                :10;
    UINT32 DV                      :1;
    UINT32 PKTRDY                  :1;
    UINT32                         :20;
} USBRXPLENBITFIELD;

typedef struct USBTXPLENBITFIELD {
    UINT32 PKTLNGHT                :10;
    UINT32                         :22;
} USBTXPLENBITFIELD;

typedef struct USBCTRLBITFIELD {
    UINT32 RDEN                    :1;
    UINT32 WREN                    :1;
    UINT32 LOGENDPOINT             :4;
    UINT32                         :26;
} USBCTRLBITFIELD;

typedef struct USBDEVINTPRIBITFIELD {
    UINT32 FRAME                   :1;
    UINT32 EPFAST                  :1;
    UINT32                         :6;
} USBDEVINTPRIBITFIELD;

typedef struct USBEPBITFIELD {
    UINT32 EP0RX                   :1;
    UINT32 EP0TX                   :1;
    UINT32 EP1RX                   :1;
    UINT32 EP1TX                   :1;
    UINT32 EP2RX                   :1;
    UINT32 EP2TX                   :1;
    UINT32 EP3RX                   :1;
    UINT32 EP3TX                   :1;
    UINT32 EP4RX                   :1;
    UINT32 EP4TX                   :1;
    UINT32 EP5RX                   :1;
    UINT32 EP5TX                   :1;
    UINT32 EP6RX                   :1;
    UINT32 EP6TX                   :1;
    UINT32 EP7RX                   :1;
    UINT32 EP7TX                   :1;
    UINT32 EP8RX                   :1;
    UINT32 EP8TX                   :1;
    UINT32 EP9RX                   :1;
    UINT32 EP9TX                   :1;
    UINT32 EP10RX                  :1;
    UINT32 EP10TX                  :1;
    UINT32 EP11RX                  :1;
    UINT32 EP11TX                  :1;
    UINT32 EP12RX                  :1;
    UINT32 EP12TX                  :1;
    UINT32 EP13RX                  :1;
    UINT32 EP13TX                  :1;
    UINT32 EP14RX                  :1;
    UINT32 EP14TX                  :1;
    UINT32 EP15RX                  :1;
    UINT32 EP15TX                  :1;
} USBEPBITFIELD;

typedef struct REG_USBD {
	PREG_32(DEVINTST);
	PREG_32(DEVINTEN);
	PREG_32(DEVINTCLR);
	PREG_32(DEVINTSET);
	PREG_BITS32(CMDCODE, USBCMDCODEBITFIELD);
	PREG_BITS32(CMDDATA, USBCMDDATABITFIELD);
	PREG_32(RXDATA);
	PREG_32(TXDATA);
	PREG_BITS32(RXPLEN, USBRXPLENBITFIELD);
	PREG_BITS32(TXPLEN, USBTXPLENBITFIELD);
	PREG_BITS32(CTRL, USBCTRLBITFIELD);
} REG_USBD;
    
typedef struct USBPLLCTRLBITFIELD {
    UINT32 MSEL                    :5;
    UINT32 PSEL                    :2;
    UINT32                         :25;
} USBPLLCTRLBITFIELD;
    
typedef struct USBPLLSTATBITFIELD {
    UINT32 LOCK                    :1;
    UINT32                         :31;
} USBPLLSTATBITFIELD;

#define REG_USBPLLCLKSEL            REG_32(0x40048048)
#define REG_USBPLLCLKUEN            REG_32(0x4004804C)
#define REG_USBCLKSEL               REG_32(0x400480C0)
#define REG_USBCLKUEN               REG_32(0x400480C4)
#define REG_USBCLKDIV               REG_32(0x400480C8)
#define REG_USBPLLCTRL              REG_32(0x40048010)
#define REGBITS_USBPLLCTRL          REGBITS_32(0x40048010, USBPLLCTRLBITFIELD)
#define REG_USBPLLSTAT              REG_32(0x40048014)
#define REGBITS_USBPLLSTAT          REGBITS_32(0x40048014, USBPLLSTATBITFIELD)
#define REG_USBDEVINTCLR            REG_32(0x40020008)
#define REG_USBCMDCODE              REG_32(0x40020010) 
#define REGBITS_USBCMDCODE          REGBITS_32(0x40020010, USBCMDCODEBITFIELD)
#define REG_USBDEVINTST             REG_32(0x40020000)
#define REGBITS_USBDEVINTST         REGBITS_32(0x40020000, USBDEVINTBITFIELD)
#define REG_USBCMDDATA              REG_32(0x40020014)
#define REG_USBCTRL                 REG_32(0x40020028)
#define REGBITS_USBCTRL             REGBITS_32(0x40020028, USBCTRLBITFIELD)
#define REG_USBRXDATA               REG_32(0x40020018)
#define REG_USBRXPLEN               REG_32(0x40020020)
#define REGBITS_USBRXPLEN           REGBITS_32(0x40020020, USBRXPLENBITFIELD)
#define REG_USBTXPLEN               REG_32(0x40020024)
#define REGBITS_USBTXPLEN           REGBITS_32(0x40020024, USBTXPLENBITFIELD)
#define REG_TDATA                   REG_32(0x4002001C)


/***************************************************************************************************************************************//**

    Represents a USB device controller driver to be used by the USB device stack.
    @module     INTERNAL

*******************************************************************************************************************************************/
typedef struct LPC13X1X2X3_USBDCD {
    REG_USBD* REG;                          /**< A pointer to the internal registers for the USB device perhiperal. */
} USBDCD;

#endif /* MCU_USBD_H__ */
