/*******************************************************************************************************************************************

    DZX | LPC177x8x | USB DEVICE                                                                                          VERSION 18.2.1
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
#include "USB/Device/usbd_core.h"
#include "Kernel/kernel_core.h"
#include "mcu_irq.h"
#include "mcu_cfg.h"
#include "mcu_scu.h"

/*******************************************************************************************************************************************
    LOCAL DEFINITIONS
*******************************************************************************************************************************************/
#define USBDBITCCEMPTY  4
#define USBDBITCDFULL   5

/* Serial Interface Engine (SIE) commands */
#define SIESETADDRESS           0xD0
#define SIESETDEVICESTATUS      0xFE
#define SIEGETDEVICESTATUS      0xFE
#define SIECLEARBUFFER          0xF2
#define SIESETMODE              0xF3
#define SIECLEARINTERRUPT       0x40
#define SIESELECTENDPOINT       0x00
#define SIEVALIDATEBUFFER       0xFA
#define SIESETENDPOINTSTATUS    0x40
#define SIECONFIGUREDEVICE      0xD8

#define USBPHYENDPOINT(ep)      (((ep->addr & 0x7F) << 1) + ((ep->addr & 0x80) >> 7))

typedef union SIEDEVICESTATUS {
	struct {
		BYTE CON    :1;
		BYTE CONCH  :1;
		BYTE SUS    :1;
		BYTE SUSCH  :1;
		BYTE RST    :1;
        BYTE        :3;
	} BITS;
	BYTE VALUE;
} SIEDEVICESTATUS;

typedef union SIEEPSTATUS {
	struct {
		BYTE FE     :1;
		BYTE ST     :1;
		BYTE STP    :1;
		BYTE PO     :1;
		BYTE EPN    :1;
		BYTE B1FULL :1;
		BYTE B2FULL :1;
        BYTE        :1;
	} BITS;
	BYTE VALUE;
} SIEEPSTATUS;

/*******************************************************************************************************************************************
    PRIVATE FUNCTIONS
*******************************************************************************************************************************************/
static void USBD_InitPLL(void);
static void USBD_FeedPLL(void);
static void USBD_CommandSIE(BYTE cmd);
static void USBD_WriteSIE(BYTE cmd, BYTE data);
static BYTE USBD_ReadSIE(BYTE cmd);
static void USBD_InitEndpoints(USBDDEVICE* device);
static void USBD_OpenEndpoint(USBDENDPOINT* endpt);
static UINT32 USBD_ReadPacket(USBDENDPOINT* endpt, void* buf);
static STATUS USBD_WritePacket(USBDENDPOINT* endpt, const void* data, UINT32 nbytes);
static STATUS USBD_SoftConnect(USBDDEVICE* usbd, BOOLEAN connect);
static void USBD_IRQ(IRQ irq);

/***************************************************************************************************************************************//**

    Opens a device controller port for a USB device.

    @param[in]  device      A pointer to the device that is to be opened.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The port was opened.
     ERR_NULLREFERENCE      | The argument 'device' was found to be NULL.

    @module     USBD-DCD

*******************************************************************************************************************************************/
STATUS USBD_InitController(USBDDEVICE* device)
{
#if (CFG_NULLCHECKING)
    if (device == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif
    
    IRQ_Disable(IRQ_USB);                                      /* Disable USB interrupts */
    
    USBD_InitPLL();                                             /* Initialize the PLL and clock source for the USB peripheral */
    REGBITS_PCONP.PCUSB = 1;                                    /* Power up the USB peripheral */
    REG_USBCLKCTRL = 0x1A;                                      /* Enable the clocks within the USB peripheral */
    while ((REG_USBCLKCTRL & 0x1A) != 0x1A) { }                 /* Wait for the clocks to become valid */
    
    device->dcd.REG = REG_USBD0;                                /* Assign the registers for the peripheral */
    
#if (CFG_USBDPORTSEL == 1)
    REG_OTGSTCTRL = 0;
    
#elif (CFG_USBDPORTSEL == 2)
    REG_OTGSTCTRL = 3;
    
#else
#error "Must specify a port selection of either '1' or '2'"
#endif

    device->dcd.REG->DEVINTCLR = 0xFFFFFFFF;                    /* Clear all pending device interrupts */            

    USBD_Reset(device);                                         /* Reset the state of the controller */

    device->dcd.REG->DEVINTEN.VALUE = 0;
    device->dcd.REG->DEVINTEN.BITS.DEVSTAT = 1;                 /* Enable device status interrupts */
    device->dcd.REG->DEVINTEN.BITS.EPSLOW = 1;                  /* Enable endpoint interrupts */

    USBD_SoftConnect(device, FALSE);
    
    USBD_WriteSIE(SIESETMODE, 0);
    IRQ_RegisterHandler(IRQ_USB, USBD_IRQ);
    IRQ_Enable(IRQ_USB);                                        /* Enable USB interrupts within the NVIC */

    
    
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

    @module     USBD-DCD

*******************************************************************************************************************************************/
STATUS USBD_CloseController(USBDDEVICE* device)
{
    INTERRUPTLOCK lock;
    
    
#if (CFG_NULLCHECKING)
    if (device == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif

    IRQ_Disable(IRQ_USB);
    
    device->dcd.REG->DEVINTEN.VALUE = 0;                         /* Disable USB device interrupts */
    device->dcd.REG->DEVINTCLR = 0xFFFFFFFF;                     /* Clear all pending device interrupts */
    
    USBD_SoftConnect(device, FALSE);                             /* Deactivate the SoftConnect signal */
    USBD_SetAddress(device, 0);                                  /* Reset device address */
    USBD_SetConfiguration(device, 0);                            /* Reset the state to an unconfigured state */
    
    ACQUIREINTERRUPTLOCK();
    LIST_Clear(&device->endpts);                                 /* Clear list of open endpoints */
    RELEASEINTERRUPTLOCK();
    
    return SUCCESS;
}

STATUS USBD_OpenController(USBDDEVICE* device)
{
    USBD_SoftConnect(device, TRUE);                             /* Activate the SoftConnect signal */
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
    USBD_SetAddress(device, 0);                                  /* Reset device address */
    USBD_SetConfiguration(device, 0);                            /* Reset the state to an unconfigured state */
    USBD_InitEndpoints(device);                                  /* Re-initialize the endpoint buffers */
    
    device->suspended = FALSE;
    return SUCCESS;
}

/***************************************************************************************************************************************//**

    Initializes the on-chip PLL to generate the clock needed for the USB peripheral.

    @return     None.
    @module     internal

*******************************************************************************************************************************************/
static void USBD_InitPLL(void)
{
    REGBITS_USBCLKSEL.USBSEL = 0;                               /* Switch the USB clock to not use PLL 1 */
    
    if (REGBITS_PLL1STAT.PLLESTAT) {                            /* Check if the PLL is currently enabled and should be disabled */
        REGBITS_PLL1CON.PLLE = 0;                               /* Command the PLL to be disabled */
        USBD_FeedPLL();
    }

    REGBITS_PLL1CFG.MSEL = CFG_CLKPLL1MSEL;                     /* Assign multiplier and divider values */
    REGBITS_PLL1CFG.PSEL = CFG_CLKPLL1PSEL;
    USBD_FeedPLL();

    REGBITS_PLL1CON.PLLE = 1;                                   /* Enable the PLL */
    USBD_FeedPLL();
    
    REGBITS_USBCLKSEL.USBDIV = 2;

    while (REGBITS_PLL1STAT.PLOCK == 0);                        /* Wait for the PLL to lock */
    
    REGBITS_USBCLKSEL.USBSEL = 2;                               /* Switch the USB clock to use PLL 1 */
}

/***************************************************************************************************************************************//**

    Performs a feed sequence on the PLL used by the USB peripheral.

    @return     None.
    @module     internal

*******************************************************************************************************************************************/
static void USBD_FeedPLL(void)
{
    REG_PLL1FEED = 0xAA;
    REG_PLL1FEED = 0x55;
}

/***************************************************************************************************************************************//**

    Writes a command to the serial interface engine (SIE) within the USB peripheral.

    @param[in]  cmd         The command to be sent.

    @return     None.
    @module     internal

*******************************************************************************************************************************************/
static void USBD_CommandSIE(BYTE cmd)
{
    REG_USBDEVINTCLR = BIT(USBDBITCCEMPTY);                     /* Clear the command code register empty interrupt flag (CCEMPTY) */
    REG_USBCMDCODE = 0x0500 + (cmd << 16);                      /* Send the command */
    while (REGBITS_USBDEVINTST.CCEMTY == 0);                    /* Wait for the command to be accepted */
}

/***************************************************************************************************************************************//**

    Writes data to the serial interface engine (SIE) within the USB peripheral.

    @param[in]  cmd         The write command to be sent.
    @param[in]  data        The data to be sent.

    @return     None.
    @module     internal

*******************************************************************************************************************************************/
static void USBD_WriteSIE(BYTE cmd, BYTE data)
{
    INTERRUPTLOCK lock;

    
    ACQUIREINTERRUPTLOCK();

    USBD_CommandSIE(cmd);                                       /* Send the specified command */

    REG_USBDEVINTCLR = BIT(USBDBITCCEMPTY);                     /* Clear the command code register empty interrupt flag */
    REG_USBCMDCODE = 0x0100 + (data << 16);                     /* Send the data */

    while (REGBITS_USBDEVINTST.CCEMTY == 0);                    /* Wait for the data to be accepted */

    RELEASEINTERRUPTLOCK();
}

/***************************************************************************************************************************************//**

    Reads data from the serial interface engine (SIE) within the USB peripheral.

    @param[in]  cmd         The read command to be sent.

    @return     The data that has been received from the serial interface engine.
    @module     internal

*******************************************************************************************************************************************/
static BYTE USBD_ReadSIE(BYTE cmd)
{
    INTERRUPTLOCK lock;
    BYTE val;


    ACQUIREINTERRUPTLOCK();

    USBD_CommandSIE(cmd);                                       /* Send the specified command */

    REG_USBDEVINTCLR = BIT(5);                                  /* Clear the command data register full (CDFULL) flag */
    REG_USBCMDCODE = 0x0200 + (UINT32)(cmd << 16);              /* Set code to read data */

    while (REGBITS_USBDEVINTST.CDFULL == 0);                    /* Wait to receive the data by waiting for CDFULL bit to be set */
    val = (BYTE)REG_USBCMDDATA;
    
    RELEASEINTERRUPTLOCK();
    return val;                                                 /* Return the received data */
}

/***************************************************************************************************************************************//**

    Returns the current speed of a USB connection.

    @param[in]  device         The read command to be sent.

    @return     The data that has been received from the serial interface engine.
    @module     USBD

*******************************************************************************************************************************************/
USBSPEED USBD_Speed(USBDDEVICE* device) 
{
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
    USBD_WriteSIE(SIESETDEVICESTATUS, connect);
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
    USBD_WriteSIE(SIESETADDRESS, 0x80 | address);

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


    ACQUIREINTERRUPTLOCK();

    device->dcd.REG->EPINTEN = 0;                               /* Disable all endpoint interrupts */               
    device->dcd.REG->EPINTCLR = 0xFFFFFFFF;                     /* Clear all pending endpoint interrupts */
    device->dcd.REG->REEP = 0;                                  /* Unrealize all the endpoints */

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
    UINT32 epnum;


    epnum = USBPHYENDPOINT(endpt);

    ACQUIREINTERRUPTLOCK();
    
    endpt->stalled = FALSE;
    
    endpt->device->dcd.REG->DEVINTCLR = (1 << 8);                   /* Clear any pending endpt realized interrupt */
    endpt->device->dcd.REG->EPIN = epnum;                           /* Select the specified endpt */
    endpt->device->dcd.REG->MAXPSIZE = endpt->pktszfs;              /* Assign the max packet size for the endpt */

    endpt->device->dcd.REG->REEP |= (1 << epnum);                   /* Request to realize the endpt */
    while (endpt->device->dcd.REG->DEVINTST.BITS.EPRLZED == 0);     /* Wait for the endpt to be realized */
    
    

    endpt->device->dcd.REG->DEVINTCLR = (1 << 8);                   /* Clear any pending endpt realized interrupt */
    endpt->device->dcd.REG->EPINTCLR = (1 << epnum);                /* Clear the endpt interrupt */
    RELEASEINTERRUPTLOCK();
    
    USBD_ReadSIE((BYTE)(SIECLEARINTERRUPT + epnum));                /* Clear the interrupt within the SIE */

    ACQUIREINTERRUPTLOCK();
    if (endpt->signals.thread) {                                    /* Is there a thread attempting a transfer upon this endpoint? */
        if ((endpt->addr & 0x80) == 0) {                            /* Is this a receiving endpoint? */
            endpt->device->dcd.REG->EPINTEN |= (1 << epnum);        /* Yes, enable interrupts to receive data */
        }
    }
    
    LIST_AddLast(&endpt->device->endpts, &endpt->node, endpt);      /* Keep track of all open endpoints */
  
    RELEASEINTERRUPTLOCK();
}

/***************************************************************************************************************************************//**

    Reads a single packet that has been received by the on-chip USB peripheral.

    @param[in]  endpt       A pointer to the endpoint that received the packet.
    @param[out] buf         A pointer to a caller allocated buffer to be filled with the received data.

    @return     The size in bytes of the packet that has been received by the endpoint.
    @module     internal

*******************************************************************************************************************************************/
static UINT32 USBD_ReadPacket(USBDENDPOINT* endpt, void* buf)
{
    INTERRUPTLOCK lock;
    UINT32* data;
    UINT32 len;
    UINT32 epnum;


    epnum = USBPHYENDPOINT(endpt);                                      /* Get the physical number of the endpoint */

    ACQUIREINTERRUPTLOCK();
    
    REG_USBCTRL = (UINT32)((UINT32)(endpt->addr & 0x7F) << 2) | 0x01;   /* Select the endpoint and enable reading */
    while (REGBITS_USBRXPLEN.PKTRDY == 0);                              /* Wait for the data to be ready */

    data = (UINT32*)buf;                                                /* Get access to the endpoint buffer */
    len = REGBITS_USBRXPLEN.PKTLNGTH;                                   /* Retrieve the size of the received packet */
   
    while (REGBITS_USBRXPLEN.DV != 0) {                                 /* Read the data payload from the SIE */
        *data++ = REG_USBRXDATA;
    }
    
    REG_USBCTRL = 0;                                                    /* Disable reading */
    USBD_CommandSIE(epnum);                                             /* Select the endpoint */
    USBD_CommandSIE(SIECLEARBUFFER);                                    /* Clear the endpoint buffer */
    USBD_ReadSIE(SIECLEARINTERRUPT + epnum);                            /* Clear the interrupt on this endpoint */

    RELEASEINTERRUPTLOCK();
    return len;
}

/***************************************************************************************************************************************//**

    Transmits a packet over an endpoint.

    @param[in]  endpt       A pointer to the endpoint that will transmit the packet.
    @param[in]  data        A pointer to the data to be written.
    @param[in]  nbytes      The number of bytes of data to be written.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The packet has been staged for transfer.
     ERR_ALIGNMENT          | The data to be sent is not properly aligned.

    @module     internal

*******************************************************************************************************************************************/
static STATUS USBD_WritePacket(USBDENDPOINT* endpt, const void* data, UINT32 nbytes)
{
    INTERRUPTLOCK lock;
    UINT32* data32;
    UINT32 phyep;


    if ((UINT32)data % sizeof(UINT32)) {
        return ERR_ALIGNMENT;
    }

    phyep = USBPHYENDPOINT(endpt);                              /* Get the physical IN (device-to-host) endpoint */
   
    ACQUIREINTERRUPTLOCK();

    REG_USBCTRL = ((endpt->addr & 0x7F) << 2) | 0x02;           /* Select the endpoint and enable writing */
    REG_USBTXPLEN = nbytes;
    data32 = (UINT32*)data;

    if (nbytes > 0) {
        while (REGBITS_USBCTRL.WREN) {
            REG_TDATA = *data32++;                              /* Write the data to the SIE */
        } 
    } else {
        REG_TDATA = 0;
    }
    
    RELEASEINTERRUPTLOCK();
    
    ACQUIREINTERRUPTLOCK();

    USBD_CommandSIE(SIESELECTENDPOINT + phyep);                 /* Select endpoint */
    USBD_CommandSIE(SIEVALIDATEBUFFER);                         /* Send the packet */

    RELEASEINTERRUPTLOCK();
    return SUCCESS;
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
    USBD_WriteSIE(SIESETENDPOINTSTATUS + USBPHYENDPOINT(endpt), 0x1);
   
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
    USBD_WriteSIE(SIESETENDPOINTSTATUS + USBPHYENDPOINT(endpt), 0);
    
    endpt->device->dcd.REG->EPINTCLR = (1 << USBPHYENDPOINT(endpt));                /* Clear the endpt interrupt */

    USBD_ReadSIE((BYTE)(SIECLEARINTERRUPT + USBPHYENDPOINT(endpt)));                /* Clear the interrupt within the SIE */
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
    if (endpt->stalled) {
        RELEASEINTERRUPTLOCK();
        return TRUE;
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

        USBD_WriteSIE(SIECONFIGUREDEVICE, 1);

        LIST_Foreach(inode, &cfg->intfs) {                      /* Foreach interface within the configuration */
            intf = inode->value;    
            LIST_Foreach(enode, &intf->endpoints) {             /* Foreach endpoint within the interface */
                endpt = enode->value;
                    USBD_OpenEndpoint(endpt);                   /* Enable and configure the endpoint */
            }
        }
    } else {
        device->curcfg = NULL;
        USBD_WriteSIE(SIECONFIGUREDEVICE, 0);
    }
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
     ERR_ACCESSDENIED       | The endpoint is in-progress with a transfer from a different thread.

    @module     USBD-ENDPT

*******************************************************************************************************************************************/
STATUS USBD_Read(USBDENDPOINT* endpt, void* buf, UINT32 bufsize, UINT32* nread, UINT32 timeout)
{
    INTERRUPTLOCK lock;
    STATUS status;
    UINT32 phyep;
    BYTE value;
    

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
    
    if (endpt->signals.thread) {
        RELEASEINTERRUPTLOCK();
        return ERR_ACCESSDENIED;
    }
    
    RELEASEINTERRUPTLOCK();
    
    endpt->data = (void*)buf;                                    /* Initialize the data transfer */
	endpt->nbytes = bufsize;
	endpt->idx = 0;
    
    phyep = USBPHYENDPOINT(endpt);
    
    SIGNAL_Clear(&endpt->signals, SIGNAL_0);
    
    ACQUIREINTERRUPTLOCK();
    
    endpt->device->dcd.REG->EPINTEN |= (1 << phyep);            /* Enable receive interrupts */
    
    value = USBD_ReadSIE(phyep);                                /* Get the current status of the target endpoint */
    if (value & 0x61) {                                         /* Is there data already available? */
        endpt->device->dcd.REG->EPINTSET = (1 << phyep);        /* Yes, invoke a receive interrupt */
    }
    
    RELEASEINTERRUPTLOCK();
    
    if (timeout == 0) {                                         /* Did the caller request no blocking? */
        ACQUIREINTERRUPTLOCK();
        
        endpt->device->dcd.REG->EPINTEN &= ~(1 << phyep);       /* Disable further receive interrupts */            
        *nread = endpt->idx;
        
        RELEASEINTERRUPTLOCK();
        return SUCCESS;
    }

    status = SIGNAL_WaitOne(&endpt->signals, SIGNAL_0, timeout);               /* Wait for a signal from the receive interrupt */
    
    ACQUIREINTERRUPTLOCK();
    
    endpt->device->dcd.REG->EPINTEN &= ~(1 << phyep);           /* Disable further receive interrupts */
    *nread = endpt->idx;

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
    UINT32 num;
    UINT32 epnum;
    

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
    
    epnum = USBPHYENDPOINT(endpt);                          /* Get the physical endpoint number */
    
    ACQUIREINTERRUPTLOCK();
    
    if ((endpt->addr & 0x80) == 0) {                        /* Is the specified endpoint for receiving? */
        RELEASEINTERRUPTLOCK();
        return ERR_INVALIDOPERATION;                        /* Cannot transmit over a host OUT endpoint */
    }   
    
    if (endpt->signals.thread) {                            /* Is a transfer already pending on this endpoint? */
        RELEASEINTERRUPTLOCK();
        return ERR_ACCESSDENIED;                            /* Cannot have simultaneous transfers */
    }

    endpt->data = (void*)data;                              /* Assign the data to be transferred */
    endpt->nbytes = nbytes;
    endpt->idx = 0;

    num = nbytes;                                           /* Capture the total amount to be transferred */
    if (num > endpt->pktszfs) {                             /* Bound the initial transfer to the limit of a single packet */
        num = endpt->pktszfs;
    } else if (num == endpt->pktszfs) {                     /* Does the transfer end on a packet boundry? */
        if (endpt->opt & OPT_SHORTPKT) {                    /* Is short packet termination specified? */
            endpt->zlp = TRUE;                              /* Yes, mark to terminate with zero-length packet */
        }
    }
    
    endpt->idx += num;                                      /* Account for this initial transfer */                               

    endpt->device->dcd.REG->EPINTCLR = (1 << epnum);
    endpt->device->dcd.REG->EPINTEN |= (1 << epnum);        /* Enable interrupt to signal when the transfer is complete */
    
    RELEASEINTERRUPTLOCK();
    
    USBD_ReadSIE(SIECLEARINTERRUPT + epnum);                /* Clear the interrupt on this endpoint */
    
    SIGNAL_Clear(&endpt->signals, SIGNAL_0);
    status = USBD_WritePacket(endpt, data, num);            /* Write the data to the device controller */
    
    if (status == SUCCESS) {
        status = SIGNAL_WaitOne(&endpt->signals, SIGNAL_0, timeout);    /* Wait for the interrupt to signal when the transfer is complete */
    }
    
    ACQUIREINTERRUPTLOCK();
    
    endpt->device->dcd.REG->EPINTEN &= ~(1 << epnum);       /* Disable further interrupts */
    
    if (nwritten) {                                         /* Provide the total number of bytes that were actually transferred */
        *nwritten = endpt->idx;
    }
    
    RELEASEINTERRUPTLOCK();
    return status;
}
    
/***************************************************************************************************************************************//**

    Interrupt request handler for the USB device controller. Processes device status change events and any completion of data transfers 
    upon endpoints.

    @return     None
    @module     internal

*******************************************************************************************************************************************/
static void USBD_IRQ(IRQ irq)
{
    SIEDEVICESTATUS sts;
    UINT32 len;
    USBDDEVICE* device;
    USBDENDPOINT* endpt;
    NODE* node;
    UINT32 epnum;
    UINT32 n;
    INTERRUPTLOCK lock;
   
    
    device = USBD_Devices[0];                                           /* Get the target device */
    
    if (REGBITS_USBDEVINTST.EPSLOW) {                                   /* Did an endpoint interrupt? */
        
        LIST_Foreach(node, &device->endpts) {                           /* Go through each open endpoint */
            endpt = node->value;                                        /* Get the endpoint */
            
            epnum = USBPHYENDPOINT(endpt);
            
            if (REG_USBEPINTST & (1 << epnum)) {                        /* Interrupt pending for the endpoint? */
                
                if ((endpt->addr & 0x80) == 0) {                        /* A receive (host OUT) endpoint? */
                    
                    device->dcd.REG->EPINTCLR = (1 << epnum);
                    while (REGBITS_USBDEVINTST.CDFULL == 0);
                    
                    if (endpt->data) {
                        len = USBD_ReadPacket(endpt, &((BYTE*)endpt->data)[endpt->idx]);
                        endpt->idx += len;
                       
                        
                        if (len < endpt->pktszfs ||                             /* Was a short packet received? */
                            endpt->idx >= endpt->nbytes) {                      /* Is the supplied buffer full? */
                                
                            ACQUIREINTERRUPTLOCK();
                            endpt->device->dcd.REG->EPINTEN &= ~(1 << epnum);   /* Disable further receiving to this buffer */
                            RELEASEINTERRUPTLOCK();
                            
                            
                            endpt->data = NULL; 
                            SIGNAL_Set(&endpt->signals, SIGNAL_0);              /* Signal the thread waiting for the receive to complete */
                        }
                    } else {
                        endpt->device->dcd.REG->EPINTEN &= ~(1 << epnum);       /* Disable further receive interrupts */
                    }
                    
                } else {                                                        /* A transmit (host IN) endpoint */
                    
                    device->dcd.REG->EPINTCLR = (1 << epnum);
                    while (REGBITS_USBDEVINTST.CDFULL == 0);

                    n = endpt->nbytes - endpt->idx;                             /* Get the amount of data left to be transmitted */
                    if (n > 0) {                                                /* More to be transferred? */
                        
                        if (n > endpt->pktszfs) {                               /* Limit the transfer to the maximum packet length */
                            n = endpt->pktszfs; 
                        } else if (n == endpt->pktszfs) {                       /* Transmitting the exact length of packet? */
                            if (endpt->opt & OPT_SHORTPKT) {                    /* Configured to short packet terminate? */                 
                                endpt->zlp = TRUE;                              /* Yes, mark to send a zero-length packet */
                            }
                        }
                        
                        USBD_WritePacket(endpt,                                 /* Transmit the next packet */
                                         &((BYTE*)endpt->data)[endpt->idx], 
                                         n);
                        
                        endpt->idx += n;                                        /* Keep track of total transmitted */
                    } else {
                        
                        if (endpt->zlp) {                                       /* Marked to transmit a zero-length packet? */
                            endpt->zlp = FALSE;                                 /* Yes, clear the mark and transmit */
                            USBD_WritePacket(endpt, NULL, 0);                   /* Transmit the zero-length packet */
                        } else {
                       
                            endpt->device->dcd.REG->EPINTEN &= ~(1 << epnum);   /* Done transmitting, disable further interrupts */
                            SIGNAL_Set(&endpt->signals, SIGNAL_0);              /* Signal any waiting thread */
                        }
                    }
                }
            }
        }
        
        REG_USBDEVINTCLR = (1 << 2);                            /* Clear the interrupt */
    }
    
    if (REGBITS_USBDEVINTST.DEVSTAT) {                          /* A device level interrupt? */
        REG_USBDEVINTCLR = (1 << 3);                            /* Clear the interrupt */

        sts.VALUE = USBD_ReadSIE(SIEGETDEVICESTATUS);           /* Check on the device status */
        if (sts.BITS.SUSCH) {                                   /* Did the suspended status change? */
            if (sts.BITS.SUS) {
                device->suspended = TRUE;                        /* Device has been suspended */
            } else {
                device->suspended = FALSE;                       /* Device has been unsuspended */
            }
        } 
        
        if (sts.BITS.RST) {                                     /* Did a bus reset occur? */
            USBD_Reset(device);                                  /* Yes, reset the controller to accommodate */
        }
    }
    
    if (REGBITS_USBDEVINTST.ERRINT) {
        REG_USBDEVINTCLR = (1 << 9);
    }
}
