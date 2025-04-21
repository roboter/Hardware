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
#include "Kernel/kernel_core.h"
#include "USB/Device/usbd_core.h"
#include "mcu_cfg.h"
#include "mcu_irq.h"
#include "mcu_scu.h"
#include "mcu_cgu.h"
#include "mcu_creg.h"
#include <string.h>

typedef PREPACKED struct USBDTD {
	UINT32 next;
    
	UINT32                          :3;
	UINT32 transactionError         :1;
	UINT32                          :1;
	UINT32 bufferError              :1;
	UINT32 halted                   :1;
	UINT32 active                   :1;
	UINT32                          :2;
	UINT32 multiplierOverride       :2;
	UINT32                          :3;
	UINT32 IOC                      :1;
	UINT32 totalBytes               :15;
	UINT32                          :1;
	
	UINT32 bufferPage[5];
	UINT32 reserved;
	
} POSTPACKED USBDTD;

typedef PREPACKED struct USBDQH {
	UINT32                          :15;
	UINT32 interruptOnSetup         :1;
	UINT32 maxPacketLen             :11;
	UINT32                          :2;
	UINT32 ZLT                      :1;
	UINT32 MULT                     :2;	
	
	UINT32 currentTD;
	USBDTD overlay;
	BYTE setupPackage[8];
    
    UINT32 pad[4];
	
} POSTPACKED USBDQH;


/*******************************************************************************************************************************************
    LOCAL DEFINITIONS
*******************************************************************************************************************************************/
#define USBDQUEUEHEADSIZE       64
#define USBDTDINVALID           1

#define USBD_ENDPTNUM(ep)       ((((ep)->addr & 0x7F) << 1) + (((ep)->addr & 0x80) >> 7))
#define USBD_ENDPTREG(endpt)    endpt->device->dcd.REG->ENDPTCTRL[endpt->addr & 0x7F]

/*******************************************************************************************************************************************
    PRIVATE VARIABLES
*******************************************************************************************************************************************/
ALIGNED(2048) static USBDQH USBD_DQH0[12];      /* Allocate possible queue heads for port 0 */
ALIGNED(2048) static USBDQH USBD_DQH1[8];       /* Allocate possible queue heads for port 1 */
ALIGNED(64) static USBDTD USBD_DTD[2][12];      /* Allocate default transfer descriptors */

/*******************************************************************************************************************************************
    PRIVATE FUNCTIONS
*******************************************************************************************************************************************/
static USBDQH* USBD_QueueHead(USBDDEVICE* device, UINT32 idx);
static void USBD_InitPLL(USBDDEVICE* device);
static void USBD_InitEndpoints(USBDDEVICE* device);
static void USBD_OpenEndpoint(USBDENDPOINT* endpt);
static STATUS USBD_SoftConnect(USBDDEVICE* usbd, BOOLEAN connect);
static void USBD_PrimeReceive(USBDENDPOINT* endpt);
static void USBD_IRQ(IRQ irq);


/***************************************************************************************************************************************//**

    Initializes a device controller port for a USB device.

    @param[in]  device      A pointer to the device that is to be opened.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The port was opened.
     ERR_NULLREFERENCE      | The argument 'device' was found to be NULL.
     ERR_NOTSUPPORTED       | The port number assigned to the specified device is not supported.

    @module     usbd-dcd

*******************************************************************************************************************************************/
STATUS USBD_InitController(USBDDEVICE* device)
{
    #if (CFG_NULLCHECKING)
    if (device == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif
    
    switch (device->port) {
        case 0:
            IRQ_Disable(IRQ_USB0);
            device->dcd.REG = REG_USBD0;
            break;
        case 1:
            IRQ_Disable(IRQ_USB1);
            device->dcd.REG = REG_USBD1;
            break;
        default:
            return ERR_NOTSUPPORTED;
    }
    
    USBD_InitPLL(device);                                       /* Initialize the PLL and clock source for the USB peripheral */
    
    device->dcd.REG->USBCMD.BITS.RS = 0;                        /* Detach */
    device->dcd.REG->USBCMD.BITS.RST = 1;                       /* Reset controller */
    while (device->dcd.REG->USBCMD.BITS.RST);                   /* Wait for the reset to complete */
    
    device->dcd.REG->USBMODE.BITS.CM = 0x2;                     /* Configure as device mode */
    
    if (device->port == 0) {
        REGBITS_CREG0.USB0PHY = 0;                              /* Enable the high-speed phy for port 0 */
    }
    
    device->dcd.REG->ENDPOINTLISTADDR = (UINT32)USBD_QueueHead(device, 0);
    device->dcd.REG->USBCMD.BITS.ITC = 0;                       /* Configure interrupt threshold */
    
    USBD_SoftConnect(device, FALSE);
    
    USBD_Reset(device);                                         /* Reset the state of the controller */

    if (device->port == 1) {
        device->dcd.REG->PORTSC1.BITS.PFSC = 1;                 /* Force full-speed operation (no chirp) */
    }
    
    device->dcd.REG->USBINTR.BITS.URE = 1;
    device->dcd.REG->USBINTR.BITS.SLE = 1;
    device->dcd.REG->USBINTR.BITS.UE = 1;
    
    switch (device->port) {
        case 0:
            IRQ_RegisterHandler(IRQ_USB0, USBD_IRQ);
            IRQ_Enable(IRQ_USB0);
            break;
        case 1:
            REG_SFSUSB = 0x32;
            IRQ_RegisterHandler(IRQ_USB1, USBD_IRQ);
            IRQ_Enable(IRQ_USB1);
            break;
    }
    
    return SUCCESS;
}

/***************************************************************************************************************************************//**

    Opens a device controller port for a USB device.

    @param[in]  device      A pointer to the device that is to be opened.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The port was opened.
     ERR_NULLREFERENCE      | The argument 'device' was found to be NULL.
     ERR_NOTSUPPORTED       | The port number assigned to the specified device is not supported.

    @module     usbd-dcd

*******************************************************************************************************************************************/
STATUS USBD_OpenController(USBDDEVICE* device)
{
    STATUS status;
    
    
#if (CFG_NULLCHECKING)
    if (device == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif
    
    status = USBD_SoftConnect(device, TRUE);
    if (status != SUCCESS) {
        return status;
    }
    
    return SUCCESS;
}

/***************************************************************************************************************************************//**

    Closes the port used by a USB device.

    @param[in]  device      A pointer to the device that is to be closed.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The port was closed.
     ERR_NULLREFERENCE      | The argument 'device' was found to be NULL.

    @module     usbd-dcd

*******************************************************************************************************************************************/
STATUS USBD_CloseController(USBDDEVICE* device)
{
    INTERRUPTLOCK lock;
    
    
#if (CFG_NULLCHECKING)
    if (device == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif

    switch (device->port) {
        case 0:
            device->dcd.REG->USBINTR.VALUE = 0;                 /* Prevent any further interrupts */
            IRQ_Disable(IRQ_USB0);
            break;
    }
    
    USBD_SoftConnect(device, FALSE);                             /* Deactivate the SoftConnect signal */
    USBD_SetAddress(device, 0);                                  /* Reset device address */
    USBD_SetConfiguration(device, 0);                            /* Reset the state to an unconfigured state */
    
    ACQUIREINTERRUPTLOCK();
    LIST_Clear(&device->endpts);                                 /* Release all open endpoints */
    RELEASEINTERRUPTLOCK();
    
    return SUCCESS;
}

/***************************************************************************************************************************************//**

    Resets the controller for a USB device.

    @param[in]  device      A pointer to the device to be reset.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The device controller has been reset.

    @module     internal

*******************************************************************************************************************************************/
STATUS USBD_Reset(USBDDEVICE* device)
{
    device->dcd.rxsetup = FALSE;
    
    USBD_SetAddress(device, 0);                                  /* Reset device address per spec */
    USBD_SetConfiguration(device, 0);                            /* Reset to the unconfigured state */
    USBD_InitEndpoints(device);                                  /* Re-initialize the endpoint buffers */
    
    device->suspended = FALSE;
    return SUCCESS;
}

/***************************************************************************************************************************************//**

    Initializes the on-chip PLL to generate the clock needed for the USB peripheral.

    @return     None.
    @module     internal

*******************************************************************************************************************************************/
static void USBD_InitPLL(USBDDEVICE* device)
{
    REGBITS_CGUPLL0CTRL.PD = 1;                                 /* Power down the PLL */
    
    REGBITS_CGUPLL0MDIV.SELR = 0;
    REGBITS_CGUPLL0MDIV.SELI = 0x10;
    REGBITS_CGUPLL0MDIV.SELP = 0xB;
    REGBITS_CGUPLL0MDIV.MDEC = 0x7FFA;
    
    REGBITS_CGUPLL0NPDIV.NDEC = 514;
    REGBITS_CGUPLL0NPDIV.PDEC = 98;
    
    REGBITS_CGUPLL0CTRL.BYPASS = 0;
    REGBITS_CGUPLL0CTRL.CLKSEL = 0x6;
    REGBITS_CGUPLL0CTRL.CLKEN = 1;
    REGBITS_CGUPLL0CTRL.DIRECTO = 1;
    REGBITS_CGUPLL0CTRL.DIRECTI = 1;
    
    REGBITS_CGUPLL0CTRL.PD = 0;
    while (REGBITS_CGUPLL0STAT.LOCK == 0);
            
    
    /* USB port 1 requires a 60Mhz clock. Divide the 
    480Mhz clock from the USB PLL down by 4 with
    divider A, then by 2 with divider D. */
    
    if (device->port == 1) {
        REGBITS_CGUIDIVACTRL.AUTOBLOCK = 1;                     /* Configure divider A to divide USB PLL by 4 */
        REGBITS_CGUIDIVACTRL.IDIV = 3;
        REGBITS_CGUIDIVACTRL.CLKSEL = 7;
        REGBITS_CGUIDIVACTRL.PD = 0;
        
        REGBITS_CGUIDIVDCTRL.AUTOBLOCK = 1;                     /* Configure divider D to divide A by 2 */
        REGBITS_CGUIDIVDCTRL.IDIV = 1;
        REGBITS_CGUIDIVDCTRL.CLKSEL = 0xC;
        REGBITS_CGUIDIVDCTRL.PD = 0;
        
        REGBITS_CGUBASEUSB1CLK.AUTOBLOCK = 1;                   /* Select divider D as the USB1 clock source */
        REGBITS_CGUBASEUSB1CLK.CLKSEL = 0xF;
        REGBITS_CGUBASEUSB1CLK.PD = 0;
    }
}

/***************************************************************************************************************************************//**

    Returns a pointer to the queue head for the specified endpoint number.

    @param[in]  device      A pointer to the target device.
    @param[in]  idx         The zero-based index of the queue head to be returned.

    @return     A pointer to the specified queue head upon success; otherwise NULL.
    @module     internal

*******************************************************************************************************************************************/
static USBDQH* USBD_QueueHead(USBDDEVICE* device, UINT32 idx)
{
    switch (device->port) {
        case 0:
            return &USBD_DQH0[idx];
        case 1:
            return &USBD_DQH1[idx];
        default:
            return NULL;
    }
}

/***************************************************************************************************************************************//**

    Returns the current speed of a USB connection.

    @param[in]  device         The read command to be sent.

    @return     The data that has been received from the serial interface engine.
    @module     USBD

*******************************************************************************************************************************************/
USBSPEED USBD_Speed(USBDDEVICE* device) 
{
#if (CFG_NULLCHECKING)
    if (device == NULL) {
        return USBSPEED_UNKNOWN;
    }
#endif
    
    if (device->dcd.REG->PORTSC1.BITS.PSPD == 0x2) {
        return USBSPEED_HIGH;
    }
    
    return USBSPEED_FULL;
}

/***************************************************************************************************************************************//**

    Activates or deactivates the SoftConnect signal.

    @param[in]  device      A pointer to the target device.
    @param[in]  connect     TRUE to activate, or FALSE to deactivate the SoftConnect signal.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The SoftConnect signal has been updated.

    @module     internal

*******************************************************************************************************************************************/
static STATUS USBD_SoftConnect(USBDDEVICE* device, BOOLEAN connect)
{
    INTERRUPTLOCK lock;

    
    ACQUIREINTERRUPTLOCK();
    device->dcd.REG->USBCMD.BITS.RS = (connect) ? 1 : 0;
    RELEASEINTERRUPTLOCK();
    
    USBD_Reset(device);
    return SUCCESS;
}

/***************************************************************************************************************************************//**

    Assigns a new device address for a USB device.

    @param[in]  device      A pointer to the target device.
    @param[in]  address     The new address for the device.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The address has been updated.

    @module     internal

*******************************************************************************************************************************************/
STATUS USBD_SetAddress(USBDDEVICE* device, BYTE address)
{
    device->addr = address;
    
    if (address == 0) {
        device->dcd.REG->DEVICEADDR = ((address & 0x7F) << 25);
    } else {
        device->dcd.REG->DEVICEADDR = ((address & 0x7F) << 25) | (1 << 24);
    }

    return SUCCESS;
}

/***************************************************************************************************************************************//**

    Initializes the default endpoints for a USB device.

    @param[in]  device      A pointer to the target device.

    @return     None.
    @module     internal

*******************************************************************************************************************************************/
static void USBD_InitEndpoints(USBDDEVICE* device)
{
    INTERRUPTLOCK lock;
    UINT32 k;


    device->dcd.REG->ENDPTNAK = 0xFFFFFFFF;
    device->dcd.REG->ENDPTNAKEN = 0;
    device->dcd.REG->USBSTS.VALUE = 0xFFFFFFFF;
    
    device->dcd.REG->ENDPTSETUPSTAT = 0x3F;
    device->dcd.REG->ENDPTCOMPLETE = (0x3F << 16) | 0x3F;
    while (device->dcd.REG->ENDPTPRIME);
    
    device->dcd.REG->ENDPTFLUSH = (0x3F << 16) | 0x3F;
    while (device->dcd.REG->ENDPTFLUSH);
    
    for (k = 0; k < 6; k++) {
        device->dcd.REG->ENDPTCTRL[k].BITS.RXE = 0;
        device->dcd.REG->ENDPTCTRL[k].BITS.TXE = 0;
    }
    
    
    ACQUIREINTERRUPTLOCK();
    LIST_Clear(&device->endpts);                                /* Clear list of open endpoints */
    RELEASEINTERRUPTLOCK();

    USBD_OpenEndpoint(&device->rx0);                            /* Open the control receive endpoint */
    USBD_OpenEndpoint(&device->tx0);                            /* Open the control transmit endpoint */
}

/***************************************************************************************************************************************//**

    Opens an endpoint for communications.

    @param[in]  endpt       A pointer to the endpoint to be opened.

    @return     None.
    @module     internal

*******************************************************************************************************************************************/
static void USBD_OpenEndpoint(USBDENDPOINT* endpt)
{
    INTERRUPTLOCK lock;
    USBDQH* dQH;


    dQH = USBD_QueueHead(endpt->device, USBD_ENDPTNUM(endpt));
    memset(dQH, 0, sizeof(USBDQH));
    
    
    if (endpt->device->dcd.REG->PORTSC1.BITS.PSPD == 2) {
        dQH->maxPacketLen = endpt->pktszhs;
    } else {
        dQH->maxPacketLen = endpt->pktszfs;
    }
    
    dQH->interruptOnSetup = 1;
    dQH->ZLT = 0;
    dQH->overlay.next = USBDTDINVALID;
    dQH->overlay.active = 0;
    
    if (endpt->addr & 0x80) {
        switch (endpt->type) {
            case USBTRANSFERCONTROL:
            default:
                USBD_ENDPTREG(endpt).BITS.TXT = 0;
                break;
            case USBTRANSFERISOCHRONOUS:
                USBD_ENDPTREG(endpt).BITS.TXT = 1;
                break;
            case USBTRANSFERBULK:
                USBD_ENDPTREG(endpt).BITS.TXT = 2;
                break;
            case USBTRANSFERINTERRUPT:
                USBD_ENDPTREG(endpt).BITS.TXT = 3;
                break;
        }
        
        USBD_ENDPTREG(endpt).BITS.TXR = 1;                          /* Reset data toggle */
        USBD_ENDPTREG(endpt).BITS.TXE = 1;                          /* Enable transmit */
        USBD_ENDPTREG(endpt).BITS.TXS = 0;                          /* Unstall */
        
    } else {
        
        switch (endpt->type) {
            case USBTRANSFERCONTROL:
            default:
                USBD_ENDPTREG(endpt).BITS.RXT = 0;
                break;
            case USBTRANSFERISOCHRONOUS:
                USBD_ENDPTREG(endpt).BITS.RXT = 1;
                break;
            case USBTRANSFERBULK:
                USBD_ENDPTREG(endpt).BITS.RXT = 2;
                break;
            case USBTRANSFERINTERRUPT:
                USBD_ENDPTREG(endpt).BITS.RXT = 3;
                break;
        }
        
        USBD_ENDPTREG(endpt).BITS.RXR = 1;                          /* Reset data toggle */
        USBD_ENDPTREG(endpt).BITS.RXE = 1;                          /* Enable receive */
        USBD_ENDPTREG(endpt).BITS.RXS = 0;                          /* Unstall */
    }
    
    
    if (endpt->signals.thread) {                                    /* Is there a thread attempting a transfer upon this endpoint? */
        if ((endpt->addr & 0x80) == 0) {                            /* Is this a receiving endpoint? */
            USBD_PrimeReceive(endpt);
        }
    }
    
    ACQUIREINTERRUPTLOCK();
    
    LIST_AddLast(&endpt->device->endpts, &endpt->node, endpt);      /* Keep track of all open endpoints */
  
    RELEASEINTERRUPTLOCK();
}

/***************************************************************************************************************************************//**

    Stalls a USB device endpoint.

    @param[in]  endpt       A pointer to the endpoint to be stalled.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The endpoint was stalled.
     ERR_NULLREFERENCE      | The argument 'endpt' was found to be NULL.

    @module     USBD-ENDPT

*******************************************************************************************************************************************/
STATUS USBD_StallEndpoint(USBDENDPOINT* endpt)
{
    INTERRUPTLOCK lock;
    
    
#if (CFG_NULLCHECKING)
    if (endpt == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif
    
    ACQUIREINTERRUPTLOCK();
    
    endpt->stalled = TRUE;
    
    if (endpt->addr & 0x80) {
        endpt->device->dcd.REG->ENDPTCTRL[endpt->addr & 0x7F].BITS.TXS = 1;
    } else {
        endpt->device->dcd.REG->ENDPTCTRL[endpt->addr & 0x7F].BITS.RXS = 1;
    }
   
    RELEASEINTERRUPTLOCK();
    return SUCCESS;
}

/***************************************************************************************************************************************//**

    Unstalls a USB device endpoint.

    @param[in]  endpt       A pointer to the endpoint to be unstalled.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The endpoint was unstalled.
     ERR_NULLREFERENCE      | The argument 'endpt' was found to be NULL.

   @module      USBD-ENDPT

*******************************************************************************************************************************************/
STATUS USBD_UnstallEndpoint(USBDENDPOINT* endpt)
{
    INTERRUPTLOCK lock;
    
    
#if (CFG_NULLCHECKING)
    if (endpt == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif

    ACQUIREINTERRUPTLOCK();
    
    endpt->stalled = FALSE;
    
    if (endpt->addr & 0x80) {
        if (endpt->addr & 0x7F) {
            USBD_ENDPTREG(endpt).BITS.TXR = 1;                  /* Reset data toggle */
        }
        USBD_ENDPTREG(endpt).BITS.TXS = 0;                      /* Unstall */
    } else {
        if (endpt->addr & 0x7F) {
            USBD_ENDPTREG(endpt).BITS.RXR = 1;                  /* Reset data toggle */
        }
        USBD_ENDPTREG(endpt).BITS.RXS = 0;                      /* Unstall */
    }

    RELEASEINTERRUPTLOCK();
    return SUCCESS;
}

/***************************************************************************************************************************************//**

    Returns and indication of whether an endpoint is currently stalled.

    @param[in]  endpt       A pointer to the target endpoint.

    @return     TRUE if the endpoint is stalled; otherwise FALSE.
    @module     USBD-ENDPT

*******************************************************************************************************************************************/
BOOLEAN USBD_EndpointStalled(USBDENDPOINT* endpt)
{
    INTERRUPTLOCK lock;
    
    
    ACQUIREINTERRUPTLOCK();
    
    if (endpt->addr & 0x80) {
        if (USBD_ENDPTREG(endpt).BITS.TXS) {
            RELEASEINTERRUPTLOCK();
            return TRUE;
        }
    } else {
        if (USBD_ENDPTREG(endpt).BITS.RXS) {
            RELEASEINTERRUPTLOCK();
            return TRUE;
        }
    }
    
    RELEASEINTERRUPTLOCK();
    return FALSE;
}

/***************************************************************************************************************************************//**

    Sets the configuration for a USB device.

    @param[in]  device      A pointer to the target USB device.
    @param[in]  number      The number of the configuration that should be applied.

    @return     None.
    @module     internal

*******************************************************************************************************************************************/
void USBD_SetConfiguration(USBDDEVICE* device, BYTE number)
{
    USBDINTERFACE* intf;
    USBDENDPOINT* endpt;
    USBDCFG* cfg;
    NODE* inode;
    NODE* enode;



    cfg = USBD_GetConfiguration(device, number);                /* Get the requested configuration */

    if (cfg) {
        device->curcfg = cfg;                                   /* Assign the active configuration */
        
        LIST_Foreach(inode, &cfg->intfs) {                      /* Foreach interface within the configuration */
            intf = inode->value;    
            LIST_Foreach(enode, &intf->endpoints) {             /* Foreach endpoint within the interface */
                endpt = enode->value;
                    USBD_OpenEndpoint(endpt);                   /* Enable and configure the endpoint */
            }
        }
    } else {
        device->curcfg = NULL;
    }
}

/***************************************************************************************************************************************//**
    
    Primes an endpoint for receiving data.

    @param[in]  device      A pointer to the endpoint to receive the data.

    @return     None.
    @module     internal

*******************************************************************************************************************************************/
static void USBD_PrimeReceive(USBDENDPOINT* endpt)
{
    INTERRUPTLOCK lock;
    USBDQH* dQH;
    USBDTD* dTD;
    
    
    
    ACQUIREINTERRUPTLOCK();
    endpt->device->dcd.REG->ENDPTFLUSH = (1 << (endpt->addr & 0x7F));
    RELEASEINTERRUPTLOCK();
    
    dQH = USBD_QueueHead(endpt->device, USBD_ENDPTNUM(endpt));
    dTD = &USBD_DTD[endpt->device->port][USBD_ENDPTNUM(endpt)];
    memset(dTD, 0, sizeof(USBDTD));
    
    dTD->next = USBDTDINVALID;                                          /* Set as tail of the list of transfer descriptors */
    dTD->IOC = 1;
    dTD->active = 1;
    dTD->halted = 0;
    dTD->totalBytes = endpt->nbytes;
    dTD->bufferPage[0] = (UINT32)endpt->data;
    dTD->bufferPage[1] = ((UINT32)endpt->data + 0x1000) & 0xFFFFF000;
	dTD->bufferPage[2] = ((UINT32)endpt->data + 0x2000) & 0xFFFFF000;
	dTD->bufferPage[3] = ((UINT32)endpt->data + 0x3000) & 0xFFFFF000;
	dTD->bufferPage[4] = ((UINT32)endpt->data + 0x4000) & 0xFFFFF000;
    
    dQH->overlay.next = (UINT32)dTD;

    ACQUIREINTERRUPTLOCK();
    endpt->device->dcd.REG->ENDPTPRIME = (1 << (endpt->addr & 0x7F));
    RELEASEINTERRUPTLOCK();
}

/***************************************************************************************************************************************//**

    Reads and returns data that has been received by an endpoint. 

    This call will block until the specified buffer becomes full or until a short packet is received and the endpoint was created with the 
    'OPT_SHORTPKT' option, or until the specified timeout period has elapsed.

    @param[in]  endpt       A pointer to the endpoint to receive the data.
    @param[out] buf         A pointer to a caller allocated buffer to be filled with the data that has been received.
    @param[in]  bufsize     The size in bytes of the buffer pointed to by 'buf'.
    @param[out] nread       A pointer to a caller allocated value used to retreive the number of bytes that were actually received.
    @param[in]  timeout     The maximum amount of time, in kernel ticks, to block and wait for the data to be received. Use '0' to return 
                            without blocking and use INFINITE to block indefinitely.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The call completed successfully. Use 'nread' to determine the number of bytes that were received.
     ERR_NULLREFERENCE      | The argument 'endpt', 'buf' or 'nread' was found to be NULL.
     ERR_TIMEOUT            | The maximum amount of time has elapsed. Use 'nread' to determine the number of bytes that were received.
     ERR_INVALIDOPERATION   | The specified endpoint is a host IN endpoint and can only transmit data.
     ERR_ACCESSDENIED       | The endpoint is in-progress with a transfer from a different thread.

    @module     USBD-ENDPT

*******************************************************************************************************************************************/
STATUS USBD_Read(USBDENDPOINT* endpt, void* buf, UINT32 bufsize, UINT32* nread, UINT32 timeout)
{
    INTERRUPTLOCK lock;
    STATUS status;
    USBDQH* dQH;
    USBDTD* dTD;
    

#if (CFG_NULLCHECKING)
    if (endpt == NULL) {
        return ERR_NULLREFERENCE;
    }

    if (buf == NULL) {
        return ERR_NULLREFERENCE;
    }
    
    if (nread == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif
    
    *nread = 0;                                                 /* Initialize to always return a valid value */

    ACQUIREINTERRUPTLOCK();
    
    if (endpt->addr & 0x80) {
        RELEASEINTERRUPTLOCK();
        return ERR_INVALIDOPERATION;
    }
    
    if (endpt->signals.thread) {
        RELEASEINTERRUPTLOCK();
        return ERR_ACCESSDENIED;
    }
    
    if (endpt->device->dcd.rxsetup) {
        endpt->device->dcd.rxsetup = FALSE;
        memcpy(buf, &endpt->device->dcd.setup, 8);
        *nread = 8;
        RELEASEINTERRUPTLOCK();
        return SUCCESS;
    }
            
    endpt->device->dcd.REG->ENDPTFLUSH = (1UL << (endpt->addr & 0x7F));
    RELEASEINTERRUPTLOCK();
    
    dQH = USBD_QueueHead(endpt->device, USBD_ENDPTNUM(endpt));
    dTD = &USBD_DTD[endpt->device->port][USBD_ENDPTNUM(endpt)];
    memset(dTD, 0, sizeof(USBDTD));
    
    dTD->next = USBDTDINVALID;                                      /* Set as tail of the list of transfer descriptors */
    dTD->IOC = 1;
    dTD->active = 1;
    dTD->halted = 0;
    dTD->totalBytes = bufsize;
    dTD->bufferPage[0] = (UINT32)buf;
    dTD->bufferPage[1] = ((UINT32)buf + 0x1000) & 0xFFFFF000;
	dTD->bufferPage[2] = ((UINT32)buf + 0x2000) & 0xFFFFF000;
	dTD->bufferPage[3] = ((UINT32)buf + 0x3000) & 0xFFFFF000;
	dTD->bufferPage[4] = ((UINT32)buf + 0x4000) & 0xFFFFF000;
    
    dQH->ZLT = (endpt->opt & OPT_SHORTPKT) ? 0 : 1;
    dQH->overlay.active = 0;
	dQH->overlay.halted = 0;
    dQH->overlay.next = (UINT32)dTD;
    
    SIGNAL_Clear(&endpt->signals, SIGNAL_0);
    
    ACQUIREINTERRUPTLOCK();
    
    endpt->data = (void*)buf;                                       /* Initialize the data transfer */
	endpt->nbytes = bufsize;
	endpt->idx = 0;
    
    endpt->device->dcd.REG->ENDPTPRIME = (1 << (endpt->addr & 0x7F));
    RELEASEINTERRUPTLOCK();

    status = SIGNAL_WaitOne(&endpt->signals, SIGNAL_0, timeout);    /* Wait for a signal from the receive interrupt */
    
    ACQUIREINTERRUPTLOCK();
    
    if (endpt->idx) {
        *nread = endpt->idx;
    } else {
        *nread = endpt->nbytes - dTD->totalBytes;
    }

    RELEASEINTERRUPTLOCK();
    return status;
}

/***************************************************************************************************************************************//**

    Transfers data to a host over an endpoint. If the amount of data to be transferred exceeds the configured maximum transfer size for 
    the endpoint, the data will be transferred in maximum transfer sized packets until the transfer completes.

    @param[in]  endpt       A pointer to the endpoint to receive the data.
    @param[in]  data        A pointer to the start of the data to be written to the endpoint. Can be NULL if sending a zero length 
                            packet (zlp).
    @param[in]  nbytes      The total number of bytes to be written.
    @param[out] nwritten    A pointer to a caller allocated variable to receive the number of data bytes that were actually transferred.
    @param[in]  timeout     The maximum amount of time, in kernel ticks, to block and wait for the transfer to complete. Must not be zero
                            and must be large enough to allow the transfer to complete; based upon amount of data being transferred. Use 
                            INFINITE to wait indefinitely.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The data was successfully transferred.
     ERR_NULLREFERENCE      | The argument 'endpt' was found to be NULL.
     ERR_INVALIDCONTEXT     | The operation is not supported from the context of an interrupt service routine (ISR).
     ERR_INVALIDOPERATION   | The specified endpoint is a host OUT endpoint and can only receive data.
     ERR_ACCESSDENIED       | The endpoint is in-progress with a transfer from a different thread.

    @remark     The buffer memory must be aligned on an pointer sized word boundry (i.e. 4 bytes for 32-bit)
    @remark     Ensure that blksize is at least as large as sizeof(void*) (i.e. 4 bytes for 32-bit)
    @module     USBD-ENDPT

*******************************************************************************************************************************************/
STATUS USBD_Write(USBDENDPOINT* endpt, const void* data, UINT32 nbytes, UINT32* nwritten, UINT32 timeout)
{
    INTERRUPTLOCK lock;
    STATUS status;
    USBDQH* dQH;
    USBDTD* dTD;
    

#if (CFG_CONTEXTCHECKING)
    if (KERNEL_IsISR()) {
        return ERR_INVALIDCONTEXT;
    }
#endif 
    
#if (CFG_NULLCHECKING)
    if (endpt == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif
    
    ACQUIREINTERRUPTLOCK();
    
    if ((endpt->addr & 0x80) == 0) {                        /* Is the specified endpoint for receiving? */
        RELEASEINTERRUPTLOCK();
        return ERR_INVALIDOPERATION;                        /* Cannot transmit over a host OUT endpoint */
    }   
    
    if (endpt->signals.thread) {                            /* Is a transfer already pending on this endpoint? */
        RELEASEINTERRUPTLOCK();
        return ERR_ACCESSDENIED;                            /* Cannot have simultaneous transfers */
    }

    endpt->device->dcd.REG->ENDPTFLUSH = (1UL << ((endpt->addr & 0x7F) + 16));
    RELEASEINTERRUPTLOCK();
    
    dQH = USBD_QueueHead(endpt->device, USBD_ENDPTNUM(endpt));
    dTD = &USBD_DTD[endpt->device->port][USBD_ENDPTNUM(endpt)];
    memset(dTD, 0, sizeof(USBDTD));
    
    dTD->next = USBDTDINVALID;
    dTD->IOC = 1;
    dTD->active = 1;
    dTD->totalBytes = nbytes;
    
    /* Point to the data to be transferred */
	dTD->bufferPage[0] = (UINT32)data;
	dTD->bufferPage[1] = ((UINT32)data + 0x1000) & 0xFFFFF000;
	dTD->bufferPage[2] = ((UINT32)data + 0x2000) & 0xFFFFF000;
	dTD->bufferPage[3] = ((UINT32)data + 0x3000) & 0xFFFFF000;
	dTD->bufferPage[4] = ((UINT32)data + 0x4000) & 0xFFFFF000;
    
    dQH->ZLT = (endpt->opt & OPT_SHORTPKT) ? 0 : 1;
    dQH->overlay.active = 0;
	dQH->overlay.halted = 0;
    dQH->overlay.next = (UINT32)dTD;
    
    SIGNAL_Clear(&endpt->signals, SIGNAL_0);
    
    ACQUIREINTERRUPTLOCK();
    
    endpt->data = (void*)data;                                      /* Assign the data to be transferred */
    endpt->nbytes = nbytes;
    endpt->idx = 0;
    
    endpt->device->dcd.REG->ENDPTPRIME = (1 << ((endpt->addr & 0x7F) + 16));
    RELEASEINTERRUPTLOCK();
    
    status = SIGNAL_WaitOne(&endpt->signals, SIGNAL_0, timeout);    /* Wait for the interrupt to signal when the transfer is complete */
    
    ACQUIREINTERRUPTLOCK();

    if (nwritten) {                                                 /* Provide the total number of bytes that were actually transferred */
        *nwritten = endpt->nbytes - dTD->totalBytes;
    }
    
    RELEASEINTERRUPTLOCK();
    return status;
}
    
/***************************************************************************************************************************************//**

    Interrupt request handler for the USB device controller. Responsible for processing completed endpoint transfers and device status 
    change events.

    @return     None
    @module     internal

*******************************************************************************************************************************************/
static void USBD_IRQ(IRQ irq)
{
    USBDDEVICE* device;
    USBDENDPOINT* endpt;
    NODE* node;
    UINT32 endptcmp;
    USBDQH* dQH;
    UINT32 st;

    
    device = USBD_Devices[irq - IRQ_USB0];                              /* Get the target device */
    
    if (device->dcd.REG->ENDPTSETUPSTAT) {
        
        dQH = USBD_QueueHead(device, USBD_ENDPTNUM(&device->rx0));

        if (dQH->overlay.totalBytes > 0) {
            
            if (device->rx0.signals.thread && device->rx0.data) {
                memcpy(device->rx0.data, &dQH->setupPackage, 8);
                device->rx0.idx = 8;
                
                SIGNAL_Set(&device->rx0.signals, SIGNAL_0);
            } else {
                memcpy(&device->dcd.setup, &dQH->setupPackage, 8);
                device->dcd.rxsetup = TRUE;
            }
        } 
        
        device->dcd.REG->ENDPTSETUPSTAT = device->dcd.REG->ENDPTSETUPSTAT;
    }
    
    endptcmp = device->dcd.REG->ENDPTCOMPLETE;
    if (endptcmp) {                                                     /* Did an endpoint interrupt occur? */
        
        LIST_Foreach(node, &device->endpts) {                           /* Yes, search through each open endpoint */
            endpt = node->value;

            if (endpt->addr & 0x80) {
                if (endptcmp & (0x10000UL << (endpt->addr & 0x7F))) {
                    SIGNAL_Set(&endpt->signals, SIGNAL_0);
                }
            } else {
                if (endptcmp & (1UL << (endpt->addr & 0x7F))) {
                    SIGNAL_Set(&endpt->signals, SIGNAL_0);
                }
            }
        }
        
        device->dcd.REG->ENDPTCOMPLETE = endptcmp;
    }
    
    
    st = device->dcd.REG->USBSTS.VALUE;
    
    if (device->dcd.REG->USBSTS.BITS.URI) {                     /* Bus reset? */
        USBD_Reset(device);                                     /* Yes, reset the controller */
    }
    
    if (device->dcd.REG->PORTSC1.BITS.SUSP) {                   /* Suspended status changed? */
        device->suspended = TRUE;
    } else {
        device->suspended = FALSE;
    }
    
    device->dcd.REG->USBSTS.VALUE = st;                         /* Clear the status interrupts */
}
