/*******************************************************************************************************************************************

    DZX | USB DEVICE | DEVICE FIRMWARE UPDATE (DFU)                                                                       VERSION 18.2.1
    ------------------------------------------------------------------------------------------------------------------------------------

    This is part of the USB device stack and provides support for implementing a device firmware update (DFU) interface.

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
#include "USB/Device/usbd_dfu.h"

/*******************************************************************************************************************************************
    PRIVATE FUNCTIONS
*******************************************************************************************************************************************/
static STATUS DFUD_Request(USBDDEVICE* device, USBDINTERFACE* intf, const USBREQUEST* request);
static UINT32 DFUD_BuildInterfaceDescriptor(USBDINTERFACE* intf, void* buf);

/***************************************************************************************************************************************//**

    Creates and initializes a Device Firmware Update (DFU) interface for a USB device.

    @param[in]  device      A pointer to a USB device stack instance that will receive the interface.
    @param[in]  intf        A pointer to a caller allocated DFU interface instance to be initialized.
    @param[in]  mode        The DFU mode to be implemented by the class.

     mode                   | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     MODE_RUNTIME           | Indicates the DFU device is in the runtime mode.
     MODE_DFU               | Indicates DFU mode.

    @param[in]  buf         A pointer to a buffer used to hold data that has been downloaded or to be uploaded from the interface. Can
                            be NULL for runtime mode.
    @param[in]  bufsize     The size, in bytes, of the buffer. This is also the default transfer size for the interface.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The DFU interface was created and initialized.
     ERR_NULLREFERENCE      | The argument 'device' or 'intf' was found to be NULL.

    @module     usbd-dfu

*******************************************************************************************************************************************/
STATUS DFUD_CreateInterface(USBDDEVICE* device, DFUDINTERFACE* intf, BYTE mode, void* buf, UINT32 bufsize)
{
    STATUS status;
    
    
#if (CFG_NULLCHECKING)
    if (device == NULL) {
        return ERR_NULLREFERENCE;
    }
    
    if (intf == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif
    
    status = USBD_CreateInterface(device, &intf->base, 0xFE, 0x01, mode);    /* Create a standard interface */
    if (status != SUCCESS) {
        return status;
    }
    
    switch (mode) {                                                         /* Assign the desired mode */
        case MODE_RUNTIME:
            intf->status.bState = appIDLE;
            break;
        case MODE_DFU:
        default:
            intf->status.bState = dfuIDLE;
            break;
    }
    
    intf->base.reqcb = DFUD_Request;                                        /* Provide class-defined callback functions */
    intf->base.descb = DFUD_BuildInterfaceDescriptor;
    
    SIGNAL_Init(&intf->rxsignals);
    SIGNAL_Init(&intf->txsignals);
    
    intf->settings.attributes = CFG_DFUDATTRIBUTES;                         /* Assign default settings */
    intf->settings.detachTimeout = CFG_DFUDDETACHTIMEOUT;
    intf->settings.bcdDFU = CFG_DFUDBCDDFU;
    intf->settings.transferSize = bufsize;
    
    intf->buf = buf;
    intf->bufsize = bufsize;
    
    intf->blk.data = intf->buf;
    intf->status.bwPollTimeout = 10;

    return SUCCESS;
}

/***************************************************************************************************************************************//**

    Waits for any event signals for a device firmware update (DFU) interface to be set.

    @param[in]  intf        A pointer to the interface that will receive the signals.
    @param[out] signals     A pointer to a caller allocated signal array to receive the returned signals.
    @param[in]  timeout     The maximum amount of time, in kernel ticks, to wait for a signal to be received. Use '0' to return 
                            immediately without blocking and use INFINITE to wait indefinitely.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | At least one signal has been received.
     ERR_NULLREFERENCE      | The argument 'intf' or 'signals' was found to be NULL.
     ERR_INVALIDCONTEXT     | The operation is not supported from the context of an interrupt service routine (ISR).
     ERR_TIMEOUT            | The maximum allowable time has elapsed prior to the specified signal being received.

    @module     usbd-dfu

*******************************************************************************************************************************************/
STATUS DFUD_Wait(DFUDINTERFACE* intf, UINT32* signals, UINT32 timeout)
{
#if (CFG_NULLCHECKING)
    if (intf == NULL) {
        return ERR_NULLREFERENCE;
    }
    
    if (signals == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif
    
    return SIGNAL_Wait(&intf->txsignals,
                       OPT_WAITANY,
                       SIGNAL_DFUDDETACH | \
                       SIGNAL_DFUDMANIFEST | \
                       SIGNAL_DFUDDOWNLOAD | \
                       SIGNAL_DFUDUPLOAD,
                       signals,
                       timeout);
}

/***************************************************************************************************************************************//**

    Assigns new settings to a Device Firmware Update (DFU) interface.

    @param[in]  intf        A pointer to the interface to receive the settings.
    @param[in]  settings    A pointer to the new settings that should be applied.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The new settings have been applied.
     ERR_NULLREFERENCE      | The argument 'intf' or 'settings' was found to be NULL.

    @module     usbd-dfu

*******************************************************************************************************************************************/
STATUS DFUD_SetSettings(DFUDINTERFACE* intf, const DFUDSETTINGS* settings)
{
#if (CFG_NULLCHECKING)
    if (intf == NULL) {
        return ERR_NULLREFERENCE;
    }

    if (settings == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif    
    
    intf->settings.attributes = settings->attributes;           /* Assign the specified settings */
    intf->settings.detachTimeout = settings->detachTimeout;
    intf->settings.bcdDFU = settings->bcdDFU;
    intf->settings.transferSize = settings->transferSize;
    
    return SUCCESS;
}

/***************************************************************************************************************************************//**

    Returns the current settings for a USB device DFU interface.

    @param[in]  intf        A pointer to the interface that contains the settings to be returned.

    @return     A pointer to the settings for the specified interface upon success; otherwise NULL.
    @module     usbd-dfu

*******************************************************************************************************************************************/
const DFUDSETTINGS* DFUD_GetSettings(DFUDINTERFACE* intf)
{
#if (CFG_NULLCHECKING)
    if (intf == NULL) {
        return NULL;
    }
#endif
    
    return &intf->settings;
}

/***************************************************************************************************************************************//**

    A class-defined callback handler that builds and returns an interface descriptor that represents the specified interface.

    @param[in]  intf        A pointer to the target interface.
    @param[in]  buf         A pointer to a caller allocated buffer to receive the descriptor.

    @return     The total number of bytes that have been returned.
    @module     usbd-dfu

*******************************************************************************************************************************************/
static UINT32 DFUD_BuildInterfaceDescriptor(USBDINTERFACE* intf, void* buf)
{
    DFUFUNCTIONALDESCRIPTOR* des;
    DFUDINTERFACE* dintf;
    
    
    dintf = (DFUDINTERFACE*)intf;                           /* Access the interface as a DFU interface */
    
    des = (DFUFUNCTIONALDESCRIPTOR*)buf;                    /* Create a functional DFU descriptor */
    des->bLength = sizeof(DFUFUNCTIONALDESCRIPTOR);
    des->bDescriptorType = USBDESTYPEDFUFUNCTIONAL;
    des->bmAttributes = dintf->settings.attributes;
    des->wDetachTimeOut = dintf->settings.detachTimeout;
    des->wTransferSize = dintf->settings.transferSize;
    des->bcdDFUVersion = dintf->settings.bcdDFU;
    
    return sizeof(DFUFUNCTIONALDESCRIPTOR);
}

/***************************************************************************************************************************************//**

    Signals to a device DFU interface that a download operation has been handled and is complete.

    @param[in]  intf        A pointer to the target interface.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The interface state has been updated.
     ERR_NULLREFERENCE      | The argument 'intf' was found to be NULL.

    @module     usbd-dfu

*******************************************************************************************************************************************/
STATUS DFUD_DownloadComplete(DFUDINTERFACE* intf)
{
#if (CFG_NULLCHECKING)
    if (intf == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif

    intf->status.bState = dfuDNLOADIDLE;
    SIGNAL_Clear(&intf->txsignals, SIGNAL_DFUDDOWNLOAD);
    return SUCCESS;
}

/***************************************************************************************************************************************//**

    Signals to a device DFU interface that the manifest operation has been handled and is complete.

    @param[in]  intf        A pointer to the target interface.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The interface state has been updated.
     ERR_NULLREFERENCE      | The argument 'intf' was found to be NULL.

    @module     usbd-dfu

*******************************************************************************************************************************************/
STATUS DFUD_ManifestComplete(DFUDINTERFACE* intf)
{
#if (CFG_NULLCHECKING)
    if (intf == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif

    intf->status.bState = dfuIDLE;
    SIGNAL_Clear(&intf->txsignals, SIGNAL_DFUDMANIFEST);
    return SUCCESS;
}

/***************************************************************************************************************************************//**

    Signals to a device firmware update (DFU) interface that the upload operation has been handled and is complete.

    @param[in]  intf        A pointer to the target interface.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The interface state has been updated.
     ERR_NULLREFERENCE      | The argument 'intf' was found to be NULL.

    @module     usbd-dfu

*******************************************************************************************************************************************/
STATUS DFUD_UploadComplete(DFUDINTERFACE* intf)
{
#if (CFG_NULLCHECKING)
    if (intf == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif

    SIGNAL_Set(&intf->rxsignals, SIGNAL_DFUDUPLOAD);           /* Signal the interface thread */
    return SUCCESS;
}

/***************************************************************************************************************************************//**

    Sets a DFU interface into an error state with the specified status.

    @param[in]  intf        A pointer to the target interface to receive the new status.
    @param[in]  error       The error status for the interface.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The interface error has been assigned.
     ERR_NULLREFERENCE      | The argument 'intf' was found to be NULL.

    @module     usbd-dfu

*******************************************************************************************************************************************/
STATUS DFUD_SetError(DFUDINTERFACE* intf, DFUERROR error)
{
#if (CFG_NULLCHECKING)
    if (intf == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif
    
    intf->status.bStatus = (BYTE)error;                 /* Assign the reason for the error state */
    intf->status.bState = dfuERROR;                     /* Put the interface into the error state */
    return SUCCESS;
}

/***************************************************************************************************************************************//**

    Returns the current data block for a device DFU interface. The data block contains the data that has most recently been downloaded
    or uploaded.

    @param[in]  intf        A pointer to the target interface.

    @return     A pointer to the data block upon success; otherwise NULL.
    @module     usbd-dfu

*******************************************************************************************************************************************/
DFUDBLOCK* DFUD_GetDataBlock(DFUDINTERFACE* intf)
{
#if (CFG_NULLCHECKING)
    if (intf == NULL) {
        return NULL;
    }
#endif
    
    switch (intf->status.bState) {
        case dfuDNBUSY:
        case dfuUPLOADIDLE:
            return &intf->blk;
            
        default:
            return NULL;
    }
}

/***************************************************************************************************************************************//**

    Handles a USB request that has been targeted towards a DFU interface.

    @param[in]  device      A pointer to the USB device that received the request.
    @param[in]  intf        A pointer to the target interface.
    @param[in]  request     A pointer to the request that has been received.

    @return     None.
    @module     internal

*******************************************************************************************************************************************/
static STATUS DFUD_Request(USBDDEVICE* device, USBDINTERFACE* intf, const USBREQUEST* request)
{
    UINT32 num;
    static STATUS status;
    DFUDINTERFACE* dintf;
    
    
    dintf = (DFUDINTERFACE*)intf;                                   /* Access the interface as a DFU interface */
    
    switch (request->bmRequestType.type) {
        
        case USBCLASS:
            switch (request->bRequest) {
                
                case USBDFUDETACH:
                    USBD_Write(&device->tx0,                        /* Acknowledge the request */ 
                               NULL, 
                               0, 
                               NULL, 
                               CFG_USBDWRITETIMEOUT);
                    
                    SIGNAL_Set(&dintf->txsignals, SIGNAL_DFUDDETACH);
                    return SUCCESS;
                    
                case USBDFUGETSTATUS:
                    USBD_Write(&device->tx0,                        /* Respond with the current DFU status */
                               &dintf->status, 
                               sizeof(DFUSTATUS), 
                               NULL, 
                               CFG_USBDWRITETIMEOUT);
                    return SUCCESS;
                    
                case USBDFUCLRSTATUS:
                    dintf->status.bState = dfuIDLE;                 /* Reset and go to idle state */
                    USBD_Write(&device->tx0,                        /* Send an ACK */
                               NULL, 
                               0, 
                               NULL, 
                               CFG_USBDWRITETIMEOUT);
                    return SUCCESS;
                    
                case USBDFUDNLOAD:
                    if (request->wLength > 0) {                     /* Is this the start of a download data transfer? */
                        dintf->status.bState = dfuDNLOADSYNC;       /* Yes, begin receiving the data */
                        
                        dintf->blk.lba = request->wValue;           /* Keep track of the block number being received */
                        
                        USBD_Write(&device->tx0,                    /* ACK the host */
                                   NULL, 
                                   0,
                                   NULL, 
                                   0);
                             
                        device->rx0.opt = OPT_NONE;
                        status = USBD_Read(&device->rx0,            /* Receive all of the data */
                                           dintf->buf,
                                           request->wLength,
                                           &num,
                                           CFG_USBDREADTIMEOUT);
                        device->rx0.opt = OPT_SHORTPKT;
                        
                        if (status == SUCCESS) {
                            dintf->status.bState = dfuDNBUSY;       /* Go to busy state while processing the data */
                            dintf->blk.len = num;
                            
                            SIGNAL_Set(&dintf->txsignals,           /* Signal that a download event has occurred */
                                       SIGNAL_DFUDDOWNLOAD);
                        }
                    } else {
                        dintf->status.bState = dfuMANIFESTSYNC;
                        
                        SIGNAL_Set(&dintf->txsignals, SIGNAL_DFUDMANIFEST);
                        USBD_Write(&device->tx0, NULL, 0, NULL, CFG_USBDWRITETIMEOUT);
                    }
                    
                    return SUCCESS;
                    
                case USBDFUUPLOAD:
                    if (request->wLength > 0) {
                        dintf->blk.lba = request->wValue;           /* Prepare the DFU block for the application */
                        dintf->blk.data = dintf->buf;
                        dintf->blk.len = request->wLength;
                        
                        dintf->status.bState = dfuUPLOADIDLE;
                        
                        SIGNAL_Clear(&dintf->rxsignals, SIGNAL_DFUDUPLOAD);
                        SIGNAL_Set(&dintf->txsignals, SIGNAL_DFUDUPLOAD);
                        
                        status = SIGNAL_WaitOne(&dintf->rxsignals,  /* Wait for the application to provide the program image data */
                                                SIGNAL_DFUDUPLOAD, 
                                                INFINITE);
                        if (status == SUCCESS) {
                        
                            device->tx0.opt = OPT_NONE;
                            
                            USBD_Write(&device->tx0,                /* Write the upload data to the host */
                                       dintf->buf, 
                                       request->wLength, 
                                       NULL, 
                                       CFG_USBDWRITETIMEOUT);
                            
                            device->tx0.opt = OPT_SHORTPKT;
                            
                        } else {
                            USBD_StallEndpoint(&device->tx0);
                        }
                    }
                    return SUCCESS;
                    
                case USBDFUGETSTATE:
                    USBD_Write(&device->tx0,                        /* Provide the current state to the host */
                               &dintf->status.bState, 
                               sizeof(BYTE), 
                               NULL, 
                               CFG_USBDWRITETIMEOUT);
                    return SUCCESS;
                    
                case USBDFUABORT:
                    dintf->status.bState = dfuIDLE;
                    
                    SIGNAL_Clear(&dintf->txsignals, SIGNAL_DFUDDETACH | SIGNAL_DFUDMANIFEST | SIGNAL_DFUDDOWNLOAD);
                    SIGNAL_Clear(&dintf->rxsignals, SIGNAL_DFUDUPLOAD);

                    USBD_Write(&device->tx0, NULL, 0, NULL, CFG_USBDWRITETIMEOUT);
                    return SUCCESS;
            }
            break;
            
        case USBVENDOR:
            break;
    }
    
    return ERR_NOTSUPPORTED;
}
