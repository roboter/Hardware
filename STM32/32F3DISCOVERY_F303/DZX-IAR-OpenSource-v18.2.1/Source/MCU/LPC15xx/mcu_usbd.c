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
#include "USB/Device/usbd_core.h"
#include "Kernel/kernel_core.h"
#include "mcu_cfg.h"
#include "mcu_irq.h"
#include "mcu_syscon.h"
#include <string.h>

/*******************************************************************************************************************************************
    LOCAL DEFINITIONS
*******************************************************************************************************************************************/
#define USBDMAXENDPOINTS        10
#define USBPHYENDPOINT(ep)      (((ep->addr & 0x7F) << 1) + ((ep->addr & 0x80) >> 7))       /* Conversion from address to physical number */
#define USBDRAMSTART            0x02000000                           

/*******************************************************************************************************************************************

    Represents the control register for an endpoint.

*******************************************************************************************************************************************/
typedef PREPACKED union USBDENDPTCTRL {
    
    volatile struct {
        UINT32 ADDR         :16;
        UINT32 NBYTES       :10;
        UINT32 TYPE         :1;
        UINT32 RFTV         :1;
        UINT32 TR           :1;
        UINT32 STALL        :1;
        UINT32 DISABLED     :1;
        UINT32 ACTIVE       :1;
    } BITS;
    
    volatile UINT32 VALUE;
} POSTPACKED USBDENDPTCTRL;

/*******************************************************************************************************************************************

    Represents the list of endpoint control registers.

*******************************************************************************************************************************************/
typedef PREPACKED struct USBDENDPTLIST {
    USBDENDPTCTRL phy[USBDMAXENDPOINTS][2];         /**< The individual endpoint control registers (one per endpoint per buffer) */
} POSTPACKED USBDENDPTLIST;

/*******************************************************************************************************************************************
    PRIVATE VARIABLES
*******************************************************************************************************************************************/
ALIGNED(256) static USBDENDPTLIST endpts;           /**< Allocate the endpoint control registers in RAM (must be 256-byte aligned) */

/*******************************************************************************************************************************************
    PRIVATE FUNCTIONS
*******************************************************************************************************************************************/
static void USBD_InitPLL(void);
static void USBD_InitEndpoints(USBDDEVICE* device);
static void USBD_OpenEndpoint(USBDENDPOINT* endpt);
static STATUS USBD_SoftConnect(USBDDEVICE* usbd, BOOLEAN connect);
static void USBD_IRQ(IRQ irq);

/***************************************************************************************************************************************//**

    Opens a device controller port for a USB device.

    @param[in]  device      A pointer to the device that is to be opened.
    @param[in]  port        The number of the port to be opened.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The port was opened.
     ERR_NULLREFERENCE      | The argument 'device' was found to be NULL.

    @module     usbd-dcd

*******************************************************************************************************************************************/
STATUS USBD_InitController(USBDDEVICE* device)
{
    ALIGNED(64) static USBREQUEST setupbuf;                     /**< Allocate a buffer with proper alignment for receiving setup packets */
    INTERRUPTLOCK lock;
    
    
#if (CFG_NULLCHECKING)
    if (device == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif

    IRQ_Disable(IRQ_USB);                                       /* Disable USB interrupts */
    device->dcd.REG = REG_USBD0;                                /* Get the registers for the device controller */

    USBD_InitPLL();                                             /* Initialize the PLL and clock source for the USB peripheral */
    
    ACQUIREINTERRUPTLOCK();
    REGBITS_PRESETCTRL1.USB_RST = 1;
    REGBITS_PRESETCTRL1.USB_RST = 0;
    RELEASEINTERRUPTLOCK();
    
    device->dcd.setup = &setupbuf;
    device->dcd.rxsetup = FALSE;
    
    device->dcd.REG->INTEN.VALUE = 0;                           /* Disable all interrupts */
    device->dcd.REG->INTSTAT.VALUE = 0xFFFFFFFF;                /* Clear all pending interrupts */

    device->dcd.REG->EPLISTSTART.VALUE = (UINT32)&endpts;
    device->dcd.REG->DATABUFSTART.VALUE = USBDRAMSTART;
    device->dcd.REG->INTEN.BITS.DEV_INT_EN = 1;                 /* Enable device status interrupts */
    
    
    USBD_Reset(device);                                         /* Reset the state of the controller */

    IRQ_RegisterHandler(IRQ_USB, USBD_IRQ);
    IRQ_Enable(IRQ_USB);                                        /* Enable USB interrupts within the NVIC */

    USBD_SoftConnect(device, FALSE);
    
    device->dcd.REG->DEVCMDSTAT.BITS.LPM_SUP = 0;
    device->dcd.REG->DEVCMDSTAT.BITS.DEV_EN = 1;                /* Enable the device */
    
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

    IRQ_Disable(IRQ_USB);
    
    device->dcd.REG->INTEN.VALUE = 0;                           /* Disable all interrupts */
    device->dcd.REG->INTSTAT.VALUE = 0xFFFFFFFF;                /* Clear all pending interrupts */
    
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

    Initializes the on-chip PLL to generate the clock for the USB peripheral.

    @return     None.
    @module     internal

*******************************************************************************************************************************************/
static void USBD_InitPLL(void)
{
    REGBITS_PDRUNCFG.USBPLL_PD = 1;                             /* Power down the USB PLL */
    REG_USBPLLCLKSEL = 1;                                       /* Select the system oscillator for USB source */
    
    REGBITS_USBPLLCTRL.MSEL = CFG_USBPLLMSEL;                   /* Configure the USB PLL */
    REGBITS_USBPLLCTRL.PSEL = CFG_USBPLLPSEL;
    
    REGBITS_PDRUNCFG.USBPLL_PD = 0;                             /* Power up the USB PLL */
    while (REGBITS_USBPLLSTAT.LOCK == 0);                       /* Wait for the PLL to lock */
    
    REG_USBCLKSEL = 2;                                          /* Select the PLL output as the USB clock source */
    REGBITS_SYSAHBCLKCTRL1.USB = 1;                             /* Enable the USB peripheral clock */
    REGBITS_PDRUNCFG.USBPHY_PD = 0;                             /* Power up the USB phy */
    
    REG_USBCLKDIV = 1;                                          /* Set divider and enable the USB clock */
}

/***************************************************************************************************************************************//**

    Returns the current speed of a USB connection.

    @param[in]  device         A pointer to the target device stack instance.

    @return     The current speed used by the given device.
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
    
    device->dcd.REG->DEVCMDSTAT.BITS.DCON = (connect) ? 1 : 0;
    
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
    INTERRUPTLOCK lock;
    
    
    ACQUIREINTERRUPTLOCK();
    
    device->addr = address;
    
    device->dcd.REG->DEVCMDSTAT.VALUE &= ~0x7F;
    device->dcd.REG->DEVCMDSTAT.VALUE |= (0x80 | address);
    
    RELEASEINTERRUPTLOCK();
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
    USBDENDPTCTRL* ctrl;
    UINT32 k, b;


    ACQUIREINTERRUPTLOCK();
    LIST_Clear(&device->endpts);                                /* Clear list of open endpoints */
    RELEASEINTERRUPTLOCK();
    
    ACQUIREINTERRUPTLOCK();
    device->dcd.REG->INTEN.VALUE &= ~(0x3FF);                   /* Disable all endpoint interrupts */
    device->dcd.REG->EPSKIP.VALUE = 0xFFFFFFFF;                 /* Release all hardware buffers */
    device->dcd.REG->INTSTAT.VALUE = 0xFFFFFFFF;                /* Clear all pending interrupt flags */
    device->dcd.REG->DEVCMDSTAT.BITS.SETUP = 1;
    RELEASEINTERRUPTLOCK();
    
    for (k = 0; k < USBDMAXENDPOINTS; k++) {                    /* Clear all endpoint control registers */
        for (b = 0; b < 2; b++) {                               /* Clear each buffer within each endpoint */
            ctrl = &endpts.phy[k][b];
            ctrl->VALUE = 0;
            
            if (k > 1) {
                ctrl->BITS.DISABLED = 1;                            
            }
        }
    }

    device->dcd.rxsetup = FALSE;
    
    USBD_OpenEndpoint(&device->tx0);                            /* Open the control transmit endpoint */
    USBD_OpenEndpoint(&device->rx0);                            /* Open the control receive endpoint */
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
    
    if (epnum > 1) {
        endpts.phy[epnum][0].BITS.DISABLED = 0;
        endpts.phy[epnum][1].BITS.DISABLED = 0;
    }

    RELEASEINTERRUPTLOCK();
    
    ACQUIREINTERRUPTLOCK();
    
    switch (endpt->type) {
        case USBTRANSFERCONTROL:
        case USBTRANSFERBULK:
        case USBTRANSFERINTERRUPT:
        default:
            endpts.phy[epnum][0].BITS.TYPE = 0;
            endpts.phy[epnum][1].BITS.TYPE = 0;
            break;
        case USBTRANSFERISOCHRONOUS:
            endpts.phy[epnum][0].BITS.TYPE = 1;
            endpts.phy[epnum][1].BITS.TYPE = 1;
            break;
    }
    
    if (epnum > 1) {
        
    }
    
    RELEASEINTERRUPTLOCK();

    ACQUIREINTERRUPTLOCK();
    
    if (endpt->signals.thread) {                                    /* Is there a thread attempting a transfer upon this endpoint? */
        if ((endpt->addr & 0x80) == 0) {                            /* Is this a receiving endpoint? */

            if ((UINT32)endpt->data == (UINT32)&endpt->device->req) {   /* Is the thread waiting for a setup packet? */ 
                endpts.phy[epnum][1].BITS.ADDR = ((UINT32)endpt->device->dcd.setup >> 6);
            } else {
                endpts.phy[epnum][0].BITS.ADDR = ((UINT32)endpt->data >> 6);
            }

            endpts.phy[epnum][0].BITS.NBYTES = endpt->nbytes;
            endpts.phy[epnum][0].BITS.STALL = 0;
            endpts.phy[epnum][0].BITS.ACTIVE = 1;
        }
    }

    endpt->device->dcd.REG->INTEN.VALUE |= (1UL << epnum);          /* Enable interrupts for the endpoint */
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
    UINT32 epnum;
    
    
#if (CFG_NULLCHECKING)
    if (endpt == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif
    
    epnum = USBPHYENDPOINT(endpt);
  
    ACQUIREINTERRUPTLOCK();
    
    endpt->stalled = TRUE;
    endpts.phy[epnum][0].BITS.STALL = 1;
    
    if (endpt->device->dcd.REG->EPBUFCFG.VALUE & (1UL << epnum)) {
        endpts.phy[epnum][1].BITS.STALL = 1;
        
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
    UINT32 epnum;
    
    
    
#if (CFG_NULLCHECKING)
    if (endpt == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif

    epnum = USBPHYENDPOINT(endpt);                                  /* Get the physical endpoint number */

    ACQUIREINTERRUPTLOCK();
    
    endpt->stalled = FALSE;                                         /* Clear indication that the endpoint is stalled */
    
    endpts.phy[epnum][0].BITS.STALL = 0;
    endpts.phy[epnum][0].BITS.TR = 1;
    endpts.phy[epnum][0].BITS.RFTV = 0;
    
    if (endpt->device->dcd.REG->EPBUFCFG.VALUE & (1UL << epnum)) {  /* Is the endpoint double buffered? */
        
        endpts.phy[epnum][1].BITS.STALL = 0;                        /* Reset the other buffer too */
        endpts.phy[epnum][1].BITS.TR = 1;
        endpts.phy[epnum][1].BITS.RFTV = 0;
    }
    
    RELEASEINTERRUPTLOCK();
    return SUCCESS;
}

/***************************************************************************************************************************************//**

    Returns and indication of whether an endpoint is currently stalled.

    @param[in]  endpt       A pointer to the target endpoint.

    @return     @c TRUE if the endpoint is stalled; otherwise @c FALSE.
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

    Returns an indication of whether the specified data memory meets the requirements of the hardware to be transferred directly.
    
    @param[in]  mem         A pointer to the memory to be checked.

    @return     @c TRUE if the given memory must be buffered; otherwise @c false.
    @module     USBD-ENDPT

*******************************************************************************************************************************************/
static BOOLEAN USBD_RequiresBuffer(USBDDEVICE* stack, const void* mem)
{
    UINT32 addr = (UINT32)mem;
    
    
    if (addr == (UINT32)&stack->req) {
        return FALSE;                                           /* Reading the request (SETUP) packet doesn't need to be buffered */
    }
    
    if (addr % 64) {
        return TRUE;                                            /* Must be buffered, doesn't meet 64-byte alignment */
    }
    
    if (addr < USBDRAMSTART) {
        return TRUE;                                            /* Must be buffered, isn't within the local RAM space */
    }
    
    return FALSE;                                               /* Can be transferred directly */
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
    USBDENDPTCTRL* ctrl;


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
    
    if (USBD_RequiresBuffer(endpt->device, buf)) {                                 /* Check if the required buffer meets the hardware requirements */
        if (endpt->buffer == NULL) {
            return ERR_ALIGNMENT;
        }
        
        endpt->data = endpt->buffer;
    } else {
        endpt->data = buf;
    }
    
	endpt->nbytes = bufsize;
	endpt->idx = 0;
    
    phyep = USBPHYENDPOINT(endpt);
    ctrl = &endpts.phy[phyep][0];
    
    SIGNAL_Clear(&endpt->signals, SIGNAL_0);
    
    ACQUIREINTERRUPTLOCK();
    
    if ((UINT32)buf == (UINT32)&endpt->device->req) {
        
        endpts.phy[0][1].BITS.ADDR = ((UINT32)(endpt->device->dcd.setup) >> 6);
        ctrl->BITS.NBYTES = 8; 
        
        if (endpt->device->dcd.rxsetup) {
            memcpy(buf, endpt->device->dcd.setup, sizeof(USBREQUEST));
            *nread = sizeof(USBREQUEST);
            endpt->device->dcd.rxsetup = FALSE;
            endpt->data = NULL;
            
            RELEASEINTERRUPTLOCK();
            return SUCCESS;
        }

    } else {
        ctrl->BITS.ADDR = ((UINT32)endpt->data >> 6);
        ctrl->BITS.NBYTES = bufsize; 
    }
    
    ctrl->BITS.STALL = 0;
    ctrl->BITS.ACTIVE = 1;
    RELEASEINTERRUPTLOCK();
    
    status = SIGNAL_WaitOne(&endpt->signals, SIGNAL_0, timeout);        /* Wait for a signal from the receive interrupt */
    
    ACQUIREINTERRUPTLOCK();

    if ((UINT32)buf == (UINT32)&endpt->device->req) {

        if (endpt->device->dcd.rxsetup) {
            memcpy(buf, endpt->device->dcd.setup, sizeof(USBREQUEST));
            endpt->idx = sizeof(USBREQUEST);
            
            endpt->device->dcd.rxsetup = FALSE;
        }
    } else {
        if (endpt->data != buf) {
            memcpy(buf, endpt->data, endpt->idx);
        }
    }
    
    endpt->data = NULL;
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
     ERR_ALIGNMENT          | The specified data is not properly aligned and the endpoint does not have a copy buffer.
     ERR_ACCESSDENIED       | The endpoint is in-progress with a transfer from a different thread.

    @remark     The data to be transferred must be aligned to a 64-byte boundry; otherwise a copy buffer must be provided for the 
                endpoint. See USBD_SetCtrlBuffers() and USBD_SetEndpointBuffer().
    @module     USBD-ENDPT

*******************************************************************************************************************************************/
STATUS USBD_Write(USBDENDPOINT* endpt, const void* data, UINT32 nbytes, UINT32* nwritten, UINT32 timeout)
{
    INTERRUPTLOCK lock;
    STATUS status;
    UINT32 epnum;
    USBDENDPTCTRL* ctrl;
    

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
    
    if (USBD_RequiresBuffer(endpt->device, data)) {                            /* Check if the data meets the requirements of the hardware? */
        
        if (endpt->buffer == NULL) {
            return ERR_ALIGNMENT;                               /* The data must be buffered (for alignment), but no buffer exists */
        }
        
        memcpy(endpt->buffer, data, nbytes);                    /* Buffer the data to be written to achieve alignment */
        data = endpt->buffer;
    }
    
    epnum = USBPHYENDPOINT(endpt);                              /* Get the physical endpoint number */
    
    ACQUIREINTERRUPTLOCK();
    
    if ((endpt->addr & 0x80) == 0) {                            /* Is the specified endpoint for receiving? */
        RELEASEINTERRUPTLOCK();
        return ERR_INVALIDOPERATION;                            /* Cannot transmit over a host OUT endpoint */
    }   
    
    if (endpt->signals.thread) {                                /* Is a transfer already pending on this endpoint? */
        RELEASEINTERRUPTLOCK();
        return ERR_ACCESSDENIED;                                /* Cannot have simultaneous transfers */
    }

    endpt->data = (void*)data;                                  /* Assign the data to be transferred */
    endpt->nbytes = nbytes;
    endpt->idx = 0;

    if (nbytes > 0 && (nbytes % endpt->pktszfs) == 0) {         /* Does the transfer end on a packet boundry? */
        if (endpt->opt & OPT_SHORTPKT) {                        /* Is short packet termination specified? */
            endpt->zlp = TRUE;                                  /* Yes, mark to terminate with zero-length packet */
        }
    }
    
    ctrl = &endpts.phy[epnum][0];                       
    RELEASEINTERRUPTLOCK();

    SIGNAL_Clear(&endpt->signals, SIGNAL_0);
    
    ACQUIREINTERRUPTLOCK();
    
    ctrl->BITS.NBYTES = nbytes;
    ctrl->BITS.ADDR = ((UINT32)data >> 6) & 0xFFFF;
    ctrl->BITS.STALL = 0;
    ctrl->BITS.ACTIVE = 1;  
    
    RELEASEINTERRUPTLOCK();
  
    status = SIGNAL_WaitOne(&endpt->signals, SIGNAL_0, timeout);    /* Wait for the interrupt to signal when the transfer is complete */

    ACQUIREINTERRUPTLOCK();

    if (nwritten) {                                                 /* Provide the total number of bytes that were actually transferred */
        *nwritten = endpt->idx;
    }
    
    RELEASEINTERRUPTLOCK();
    return status;
}
    
/***************************************************************************************************************************************//**

    Interrupt request handler for the USB device controller. Processes device status change events and any completion of data transfers 
    upon endpoints.
    
    @param[in]  irq         The interrupt request to be handled.

    @return     None
    @module     internal

*******************************************************************************************************************************************/
static void USBD_IRQ(IRQ irq)
{
    USBDDEVICE* usb;
    USBDENDPOINT* endpt;
    UINT32 intstat;
    NODE* node;
    UINT32 epnum;
    
    
    usb = USBD_Devices[0];
    
    intstat = usb->dcd.REG->INTSTAT.VALUE;                      /* Capture the interrupt status bits */
    
    if (usb->dcd.REG->DEVCMDSTAT.BITS.DSUS_C) {
        
        if (usb->dcd.REG->DEVCMDSTAT.BITS.DSUS) {
            usb->suspended = TRUE;                           /* Device has been suspended */
        } else {
            usb->suspended = FALSE;                          /* Device has been resumed */
        }
        
        usb->dcd.REG->DEVCMDSTAT.BITS.DSUS_C = 1;
    }

    if (usb->dcd.REG->DEVCMDSTAT.BITS.DCON_C) {              /* SoftConnect change? */
        usb->dcd.REG->DEVCMDSTAT.BITS.DCON_C = 1;
    }

    if (usb->dcd.REG->DEVCMDSTAT.BITS.DRES_C) {              /* Bus reset? */
        usb->dcd.REG->DEVCMDSTAT.BITS.DRES_C = 1;
        
        USBD_Reset(usb);                                     /* Reset the controller and stack */
    }
    
    usb->dcd.REG->INTSTAT.VALUE = intstat;                      /* Clear the interrupts that are being serviced */

    if (intstat & 0x3FF) {

        LIST_Foreach(node, &usb->endpts) {                          /* Go through each open endpoint */
            endpt = node->value;                                    /* Get the endpoint */
            epnum = USBPHYENDPOINT(endpt);    
            
            if (intstat & (1UL << epnum)) {                         /* Endpoint interrupt pending? */
                
                endpt->idx = endpt->nbytes - endpts.phy[epnum][0].BITS.NBYTES;
                
                if ((endpt->addr & 0x80) == 0) {                    /* A receive (host OUT) endpoint? */
                     if (endpt->idx > 0 || endpt->nbytes == 0) { 
                         SIGNAL_Set(&endpt->signals, SIGNAL_0);
                    }
                } else {
                    
                    if (endpt->zlp) {                                   /* Need to transfer a zero-length packet? */ 
                        endpt->zlp = FALSE;
                        
                        endpts.phy[epnum][0].BITS.NBYTES = 0;           /* Transfer the zero length packet */
                        endpts.phy[epnum][0].BITS.ACTIVE = 1;
                        
                    } else {
                        SIGNAL_Set(&endpt->signals, SIGNAL_0);
                    }
                }
            }
        }
    }
    
    if (usb->dcd.REG->DEVCMDSTAT.BITS.SETUP) {
       
        endpts.phy[0][0].BITS.STALL = 0;
        endpts.phy[1][0].BITS.STALL = 0;
        endpts.phy[0][0].BITS.ACTIVE = 0;
        endpts.phy[1][0].BITS.ACTIVE = 0;

        usb->dcd.rxsetup = TRUE;
        endpt = &usb->rx0;                                              /* Capture the control receive endpoint */
        
        if ((UINT32)endpt->data == (UINT32)&usb->req) {                 /* Only signal if thread is waiting for a setup packet */
            SIGNAL_Set(&endpt->signals, SIGNAL_0);
        }
        
        usb->dcd.REG->DEVCMDSTAT.BITS.SETUP = 1;
    }
}
