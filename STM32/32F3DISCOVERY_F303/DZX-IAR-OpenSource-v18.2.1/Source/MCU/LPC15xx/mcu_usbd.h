/*******************************************************************************************************************************************

    DZX | LPC15xx | USB DEVICE                                                                                            VERSION 18.2.1
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
#define REG_USBD0               ((REG_USBD*)0x1C00C000)

/*******************************************************************************************************************************************

    DEVCMDSTAT: USB Device Command/Status register

*******************************************************************************************************************************************/
typedef struct USBDEVCMDSTATBITFIELD {
    UINT32 DEV_ADDR             :7;                             /* USB device address. After bus reset, the address is reset to 0x00. If the enable bit is set, the device will respond on packets for function address DEV_ADDR. When receiving a SetAddress Control Request from the USB host, software must program the new address before completing the status phase of the SetAddress Control Request. */
    UINT32 DEV_EN               :1;                             /* USB device enable. If this bit is set, the HW will start responding on packets for function address DEV_ADDR. */
    UINT32 SETUP                :1;                             /* SETUP token received. If a SETUP token is received and acknowledged by the device, this bit is set. As long as this bit is set all received IN and OUT tokens will be NAKed by HW. SW must clear this bit by writing a one. If this bit is zero, HW will handle the tokens to the CTRL EP0 as indicated by the CTRL EP0 IN and OUT data information programmed by SW. */
    UINT32 PLL_ON               :1;                             /* USB Clock/PLL control. */
    UINT32                      :1;                             /* Reserved. */
    UINT32 LPM_SUP              :1;                             /* LPM Support. */
    UINT32 INTONNAK_AO          :1;                             /* Interrupt on NAK for interrupt and bulk OUT EP */
    UINT32 INTONNAK_AI          :1;                             /* Interrupt on NAK for interrupt and bulk IN EP */
    UINT32 INTONNAK_CO          :1;                             /* Interrupt on NAK for control OUT EP */
    UINT32 INTONNAK_CI          :1;                             /* Interrupt on NAK for control IN EP */
    UINT32 DCON                 :1;                             /* Device status - connect. The connect bit must be set by SW to indicate that the device must signal a connect. The pull-up resistor on USB_DP will be enabled when this bit is set and the VbusDebounced bit is one. */
    UINT32 DSUS                 :1;                             /* Device status - suspend. The suspend bit indicates the current suspend state. It is set to 1 when the device hasn't seen any activity on its upstream port for more than 3 milliseconds. It is reset to 0 on any activity. When the device is suspended (Suspend bit DSUS = 1) and the software writes a 0 to it, the device will generate a remote wake-up. This will only happen when the device is connected (Connect bit = 1). When the device is not connected or not suspended, a writing a 0 has no effect. Writing a 1 never has an effect. */
    UINT32                      :1;                             /* Reserved. */
    UINT32 LPM_SUS              :1;                             /* Device status - LPM Suspend. This bit represents the current LPM suspend state. It is set to 1 by HW when the device has acknowledged the LPM request from the USB host and the Token Retry Time of 10us has elapsed. When the device is in the LPM suspended state (LPM suspend bit = 1) and the software writes a zero to this bit, the device will generate a remote walk-up. Software can only write a zero to this bit when the LPM_REWP bit is set to 1. HW resets this bit when it receives a host initiated resume. HW only updates the LPM_SUS bit when the LPM_SUPP bit is equal to one. */
    UINT32 LPM_REWP             :1;                             /* LPM Remote Wake-up Enabled by USB host. HW sets this bit to one when the bRemoteWake bit in the LPM extended token is set to 1. HW will reset this bit to 0 when it receives the host initiated LPM resume, when a remote wake-up is sent by the device or when a USB bus reset is received. Software can use this bit to check if the remote wake-up feature is enabled by the host for the LPM transaction. */
    UINT32                      :3;                             /* Reserved. */
    UINT32 DCON_C               :1;                             /* Device status - connect change. The Connect Change bit is set when the device's pull-up resistor is disconnected because VBus disappeared. The bit is reset by writing a one to it. */
    UINT32 DSUS_C               :1;                             /* Device status - suspend change. The suspend change bit is set to 1 when the suspend bit toggles. The suspend bit can toggle because: - The device goes in the suspended state - The device is disconnected - The device receives resume signaling on its upstream port. The bit is reset by writing a one to it. */
    UINT32 DRES_C               :1;                             /* Device status - reset change. This bit is set when the device received a bus reset. On a bus reset the device will automatically go to the default state (unconfigured and responding to address 0). The bit is reset by writing a one to it. */
    UINT32                      :1;                             /* Reserved. */
    UINT32 VBUSDEBOUNCED        :1;                             /* This bit indicates if Vbus is detected or not. The bit raises immediately when Vbus becomes high. It drops to zero if Vbus is low for at least 3 ms. If this bit is high and the DCon bit is set, the HW will enable the pull-up resistor to signal a connect. */
    UINT32                      :3;                             /* Reserved. */
} USBDEVCMDSTATBITFIELD;

/*******************************************************************************************************************************************

    INFO: USB Info register

*******************************************************************************************************************************************/
typedef struct USBINFOBITFIELD {
    UINT32 FRAME_NR             :11;                            /* Frame number. This contains the frame number of the last successfully received SOF. In case no SOF was received by the device at the beginning of a frame, the frame number returned is that of the last successfully received SOF. In case the SOF frame number contained a CRC error, the frame number returned will be the corrupted frame number as received by the device. */
    UINT32 ERR_CODE             :4;                             /* The error code which last occurred: */
    UINT32                      :1;                             /* Reserved. */
    UINT32                      :16;                            /* Reserved */
} USBINFOBITFIELD;

/*******************************************************************************************************************************************

    EPLISTSTART: USB EP Command/Status List start address

*******************************************************************************************************************************************/
typedef struct USBEPLISTSTARTBITFIELD {
    UINT32                      :8;                             /* Reserved */
    UINT32 EP_LIST              :24;                            /* Start address of the USB EP Command/Status List. */
} USBEPLISTSTARTBITFIELD;

/*******************************************************************************************************************************************

    DATABUFSTART: USB Data buffer start address

*******************************************************************************************************************************************/
typedef struct USBDATABUFSTARTBITFIELD {
    UINT32                      :22;                            /* Reserved */
    UINT32 DA_BUF               :10;                            /* Start address of the buffer pointer page where all endpoint data buffers are located. */
} USBDATABUFSTARTBITFIELD;

/*******************************************************************************************************************************************

    LPM: Link Power Management register

*******************************************************************************************************************************************/
typedef struct USBLPMBITFIELD {
    UINT32 HIRD_HW              :4;                             /* Host Initiated Resume Duration - HW. This is the HIRD value from the last received LPM token */
    UINT32 HIRD_SW              :4;                             /* Host Initiated Resume Duration - SW. This is the time duration required by the USB device system to come out of LPM initiated suspend after receiving the host initiated LPM resume. */
    UINT32 DATA_PENDING         :1;                             /* As long as this bit is set to one and LPM supported bit is set to one, HW will return a NYET handshake on every LPM token it receives. If LPM supported bit is set to one and this bit is zero, HW will return an ACK handshake on every LPM token it receives. If SW has still data pending and LPM is supported, it must set this bit to 1. */
    UINT32                      :23;                            /* Reserved */
} USBLPMBITFIELD;

/*******************************************************************************************************************************************

    EPSKIP: USB Endpoint skip

*******************************************************************************************************************************************/
typedef struct USBEPSKIPBITFIELD {
    UINT32 SKIP                 :30;                            /* Endpoint skip: Writing 1 to one of these bits, will indicate to HW that it must deactivate the buffer assigned to this endpoint and return control back to software. When HW has deactivated the endpoint, it will clear this bit, but it will not modify the EPINUSE bit. An interrupt will be generated when the Active bit goes from 1 to 0. Note: In case of double-buffering, HW will only clear the Active bit of the buffer indicated by the EPINUSE bit. */
    UINT32                      :2;                             /* Reserved */
} USBEPSKIPBITFIELD;

/*******************************************************************************************************************************************

    EPINUSE: USB Endpoint Buffer in use

*******************************************************************************************************************************************/
typedef struct USBEPINUSEBITFIELD {
    UINT32                      :2;                             /* Reserved. Fixed to zero because the control endpoint zero is fixed to single-buffering for each physical endpoint. */
    UINT32 BUF                  :8;                             /* Buffer in use: This register has one bit per physical endpoint. 0: HW is accessing buffer 0. 1: HW is accessing buffer 1. */
    UINT32                      :22;                            /* Reserved */
} USBEPINUSEBITFIELD;

/*******************************************************************************************************************************************

    EPBUFCFG: USB Endpoint Buffer Configuration register

*******************************************************************************************************************************************/
typedef struct USBEPBUFCFGBITFIELD {
    UINT32                      :2;                             /* Reserved. Fixed to zero because the control endpoint zero is fixed to single-buffering for each physical endpoint. */
    UINT32 BUF_SB               :8;                             /* Buffer usage: This register has one bit per physical endpoint. 0: Single-buffer. 1: Double-buffer. If the bit is set to single-buffer (0), it will not toggle the corresponding EPINUSE bit when it clears the active bit. If the bit is set to double-buffer (1), HW will toggle the EPINUSE bit when it clears the Active bit for the buffer. */
    UINT32                      :22;                            /* Reserved */
} USBEPBUFCFGBITFIELD;

/*******************************************************************************************************************************************

    INTSTAT: USB interrupt status register

*******************************************************************************************************************************************/
typedef struct USBINTSTATBITFIELD {
    UINT32 EP0OUT               :1;                             /* Interrupt status register bit for the Control EP0 OUT direction. This bit will be set if NBytes transitions to zero or the skip bit is set by software or a SETUP packet is successfully received for the control EP0. If the IntOnNAK_CO is set, this bit will also be set when a NAK is transmitted for the Control EP0 OUT direction. Software can clear this bit by writing a one to it. */
    UINT32 EP0IN                :1;                             /* Interrupt status register bit for the Control EP0 IN direction. This bit will be set if NBytes transitions to zero or the skip bit is set by software. If the IntOnNAK_CI is set, this bit will also be set when a NAK is transmitted for the Control EP0 IN direction. Software can clear this bit by writing a one to it. */
    UINT32 EP1OUT               :1;                             /* Interrupt status register bit for the EP1 OUT direction. This bit will be set if the corresponding Active bit is cleared by HW. This is done in case the programmed NBytes transitions to zero or the skip bit is set by software. If the IntOnNAK_AO is set, this bit will also be set when a NAK is transmitted for the EP1 OUT direction. Software can clear this bit by writing a one to it. */
    UINT32 EP1IN                :1;                             /* Interrupt status register bit for the EP1 IN direction. This bit will be set if the corresponding Active bit is cleared by HW. This is done in case the programmed NBytes transitions to zero or the skip bit is set by software. If the IntOnNAK_AI is set, this bit will also be set when a NAK is transmitted for the EP1 IN direction. Software can clear this bit by writing a one to it. */
    UINT32 EP2OUT               :1;                             /* Interrupt status register bit for the EP2 OUT direction. This bit will be set if the corresponding Active bit is cleared by HW. This is done in case the programmed NBytes transitions to zero or the skip bit is set by software. If the IntOnNAK_AO is set, this bit will also be set when a NAK is transmitted for the EP2 OUT direction. Software can clear this bit by writing a one to it. */
    UINT32 EP2IN                :1;                             /* Interrupt status register bit for the EP2 IN direction. This bit will be set if the corresponding Active bit is cleared by HW. This is done in case the programmed NBytes transitions to zero or the skip bit is set by software. If the IntOnNAK_AI is set, this bit will also be set when a NAK is transmitted for the EP2 IN direction. Software can clear this bit by writing a one to it. */
    UINT32 EP3OUT               :1;                             /* Interrupt status register bit for the EP3 OUT direction. This bit will be set if the corresponding Active bit is cleared by HW. This is done in case the programmed NBytes transitions to zero or the skip bit is set by software. If the IntOnNAK_AO is set, this bit will also be set when a NAK is transmitted for the EP3 OUT direction. Software can clear this bit by writing a one to it. */
    UINT32 EP3IN                :1;                             /* Interrupt status register bit for the EP3 IN direction. This bit will be set if the corresponding Active bit is cleared by HW. This is done in case the programmed NBytes transitions to zero or the skip bit is set by software. If the IntOnNAK_AI is set, this bit will also be set when a NAK is transmitted for the EP3 IN direction. Software can clear this bit by writing a one to it. */
    UINT32 EP4OUT               :1;                             /* Interrupt status register bit for the EP4 OUT direction. This bit will be set if the corresponding Active bit is cleared by HW. This is done in case the programmed NBytes transitions to zero or the skip bit is set by software. If the IntOnNAK_AO is set, this bit will also be set when a NAK is transmitted for the EP4 OUT direction. Software can clear this bit by writing a one to it. */
    UINT32 EP4IN                :1;                             /* Interrupt status register bit for the EP4 IN direction. This bit will be set if the corresponding Active bit is cleared by HW. This is done in case the programmed NBytes transitions to zero or the skip bit is set by software. If the IntOnNAK_AI is set, this bit will also be set when a NAK is transmitted for the EP4 IN direction. Software can clear this bit by writing a one to it. */
    UINT32                      :20;                            /* Reserved */
    UINT32 FRAME_INT            :1;                             /* Frame interrupt. This bit is set to one every millisecond when the VbusDebounced bit and the DCON bit are set. This bit can be used by software when handling isochronous endpoints. Software can clear this bit by writing a one to it. */
    UINT32 DEV_INT              :1;                             /* Device status interrupt. This bit is set by HW when one of the bits in the Device Status Change register are set. Software can clear this bit by writing a one to it. */
} USBINTSTATBITFIELD;

/*******************************************************************************************************************************************

    INTEN: USB interrupt enable register

*******************************************************************************************************************************************/
typedef struct USBINTENBITFIELD {
    UINT32 EP_INT_EN            :10;                            /* If this bit is set and the corresponding USB interrupt status bit is set, a HW interrupt is generated on the interrupt line indicated by the corresponding USB interrupt routing bit. */
    UINT32                      :20;                            /* Reserved */
    UINT32 FRAME_INT_EN         :1;                             /* If this bit is set and the corresponding USB interrupt status bit is set, a HW interrupt is generated on the interrupt line indicated by the corresponding USB interrupt routing bit. */
    UINT32 DEV_INT_EN           :1;                             /* If this bit is set and the corresponding USB interrupt status bit is set, a HW interrupt is generated on the interrupt line indicated by the corresponding USB interrupt routing bit. */
} USBINTENBITFIELD;

/*******************************************************************************************************************************************

    INTSETSTAT: USB set interrupt status register

*******************************************************************************************************************************************/
typedef struct USBINTSETSTATBITFIELD {
    UINT32 EP_SET_INT           :10;                            /* If software writes a one to one of these bits, the corresponding USB interrupt status bit is set. When this register is read, the same value as the USB interrupt status register is returned. */
    UINT32                      :20;                            /* Reserved */
    UINT32 FRAME_SET_INT        :1;                             /* If software writes a one to one of these bits, the corresponding USB interrupt status bit is set. When this register is read, the same value as the USB interrupt status register is returned. */
    UINT32 DEV_SET_INT          :1;                             /* If software writes a one to one of these bits, the corresponding USB interrupt status bit is set. When this register is read, the same value as the USB interrupt status register is returned. */
} USBINTSETSTATBITFIELD;

/*******************************************************************************************************************************************

    INTROUTING: USB interrupt routing register

*******************************************************************************************************************************************/
typedef struct USBINTROUTINGBITFIELD {
    UINT32 ROUTE_INT9_0         :10;                            /* This bit can control on which hardware interrupt line the interrupt will be generated: 0: IRQ interrupt line is selected for this interrupt bit 1: FIQ interrupt line is selected for this interrupt bit */
    UINT32                      :20;                            /* Reserved */
    UINT32 ROUTE_INT30          :1;                             /* This bit can control on which hardware interrupt line the interrupt will be generated: 0: IRQ interrupt line is selected for this interrupt bit 1: FIQ interrupt line is selected for this interrupt bit */
    UINT32 ROUTE_INT31          :1;                             /* This bit can control on which hardware interrupt line the interrupt will be generated: 0: IRQ interrupt line is selected for this interrupt bit 1: FIQ interrupt line is selected for this interrupt bit */
} USBINTROUTINGBITFIELD;

/*******************************************************************************************************************************************

    EPTOGGLE: USB Endpoint toggle register

*******************************************************************************************************************************************/
typedef struct USBEPTOGGLEBITFIELD {
    UINT32 TOGGLE               :10;                            /* Endpoint data toggle: This field indicates the current value of the data toggle for the corresponding endpoint. */
    UINT32                      :22;                            /* Reserved */
} USBEPTOGGLEBITFIELD;

typedef struct REG_USBD {
    PREG_BITS32(DEVCMDSTAT, USBDEVCMDSTATBITFIELD);             /* USB Device Command/Status register */
    PREG_BITS32(INFO, USBINFOBITFIELD);                         /* USB Info register */
    PREG_BITS32(EPLISTSTART, USBEPLISTSTARTBITFIELD);           /* USB EP Command/Status List start address */
    PREG_BITS32(DATABUFSTART, USBDATABUFSTARTBITFIELD);         /* USB Data buffer start address */
    PREG_BITS32(LPM, USBLPMBITFIELD);                           /* Link Power Management register */
    PREG_BITS32(EPSKIP, USBEPSKIPBITFIELD);                     /* USB Endpoint skip */
    PREG_BITS32(EPINUSE, USBEPINUSEBITFIELD);                   /* USB Endpoint Buffer in use */
    PREG_BITS32(EPBUFCFG, USBEPBUFCFGBITFIELD);                 /* USB Endpoint Buffer Configuration register */
    PREG_BITS32(INTSTAT, USBINTSTATBITFIELD);                   /* USB interrupt status register */
    PREG_BITS32(INTEN, USBINTENBITFIELD);                       /* USB interrupt enable register */
    PREG_BITS32(INTSETSTAT, USBINTSETSTATBITFIELD);             /* USB set interrupt status register */
    PREG_BITS32(INTROUTING, USBINTROUTINGBITFIELD);             /* USB interrupt routing register */
    PREG_BITS32(EPTOGGLE, USBEPTOGGLEBITFIELD);                 /* USB Endpoint toggle register */
} REG_USBD;

/***************************************************************************************************************************************//**

    Represents a USB device controller driver to be used by the USB device stack.
    @module     INTERNAL

*******************************************************************************************************************************************/
typedef struct LPC15XX_USBDCD {
    REG_USBD* REG;                          /**< A pointer to the internal registers for the USB device perhiperal. */
    BOOLEAN rxsetup;
    void* setup;                            /**< A pointer to a properly aligned buffer to receive setup packets */
} USBDCD;

#endif /* MCU_USBD_H__ */
