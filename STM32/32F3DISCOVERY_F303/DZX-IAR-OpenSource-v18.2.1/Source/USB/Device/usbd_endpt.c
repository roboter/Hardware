/*******************************************************************************************************************************************

    DZX | USB DEVICE | ENDPOINTS                                                                                          VERSION 18.2.1
    ------------------------------------------------------------------------------------------------------------------------------------

    This is part of the USB device stack and provides support for endpoints.

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

/***************************************************************************************************************************************//**

    Creates an endpoint for an interface.

    @param[in]  intf        A pointer to the interface instance to receive the endpoint.
    @param[in]  endpt       A pointer to a caller allocated usb device endpoint to be created and initialized.
    @param[in]  type        The transfer type for the endpoint.

     type                   | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     USBTRANSFERCONTROL     | The endpoint is a control transfer endpoint.
     USBTRANSFERISOCHRONOUS | The endpoint is an isochronous transfer endpoint.
     USBTRANSFERBULK        | The endpoint is a bulk transfer endpoint.
     USBTRANSFERINTERRUPT   | The endpoint is an interrupt transfer endpoint.

    @param[in]  addr        The address for the endpoint.
    @param[in]  pktszfs     The maximum packet size, in bytes, for the endpoint when operating at full speed.
    @param[in]  pktszhs     The maximum packet size, in bytes, for the endpoint when operating at high speed.
    @param[in]  interval    The interval rate, in frames, for polling the endpoint for data transfers. Ignored if the endpoint is a 
                            bulk or control transfer endpoint.
    @param[in]  opt         Additional options for the endpoint.

     opt                    | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     OPT_NONE               | No additional options.
     OPT_SHORTPKT           | Indicates to have the endpoint terminate transfers with a short packet.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The endpoint was successfully created.
     ERR_NULLREFERENCE      | The argument 'intf' or 'endpt' was found to be NULL.
     ERR_INVALIDCONTEXT     | This operation is not supported from the context of an interrupt service routine (ISR).
     ERR_NOTINITIALIZED     | The specified thread does not exist within the kernel.

    @module     usbd

*******************************************************************************************************************************************/
STATUS USBD_CreateEndpoint(USBDINTERFACE* intf, USBDENDPOINT* endpt, USBTRANSFERTYPE type, BYTE addr, UINT16 pktszfs, UINT16 pktszhs, BYTE interval, UINT32 opt)
{
    
#if (CFG_CONTEXTCHECKING)
    if (KERNEL_IsISR()) {
        return ERR_INVALIDCONTEXT;
    }
#endif
    
#if (CFG_NULLCHECKING)
    if (intf == NULL) {
        return ERR_NULLREFERENCE;
    }
    
    if (endpt == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif
    
    if (intf->device == NULL) {
        return ERR_NOTINITIALIZED;
    }
    
    if (intf->cfg == NULL) {
        return ERR_NOTINITIALIZED;
    }

    endpt->intf = intf;                                         /* Keep a reference to the parent interface (for reverse lookup) */
    endpt->device = intf->device;                               /* Keep a reference to the device for the endpoint (for reverse lookup) */
    
    endpt->type = type;                                         /* Assign the properties of the endpoint */
    endpt->addr = addr;
    endpt->pktszfs = pktszfs;
    endpt->pktszhs = pktszhs;
    endpt->interval = interval;
    
    endpt->data = NULL;                                         /* Initialize the transfer information */
    endpt->nbytes = 0;
    endpt->idx = 0;
    endpt->opt = opt;
    endpt->zlp = FALSE;
    
    SIGNAL_Init(&endpt->signals);
    
#if (CFG_USBDENDPTBUFFERS)
    endpt->buffer = NULL;
    endpt->bufsize = 0;
#endif
    
    LIST_AddLast(&intf->endpoints, &endpt->inode, endpt);       /* Register the endpoint within the specified interface */
    
    return SUCCESS;
}

/***************************************************************************************************************************************//**

    Destroys and removes an endpoint from it's interface.

    @param[in]  endpt       A pointer to the endpoint to be destroyed.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The endpoint was successfully destroyed and removed.
     ERR_NULLREFERENCE      | The argument 'endpt' was found to be NULL.

    @module     usbd

*******************************************************************************************************************************************/
STATUS USBD_DestroyEndpoint(USBDENDPOINT* endpt)
{
#if (CFG_NULLCHECKING)
    if (endpt == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif

    if (endpt->intf) {
        LIST_Remove(&endpt->intf->endpoints, &endpt->inode);
        endpt->intf = NULL;
    }

    return SUCCESS;
}

/***************************************************************************************************************************************//**

    Gets the descriptor for an endpoint.

    @param[in]  endpt       A pointer to the target endpoint.
    @param[in]  des         A pointer to a caller allocated endpoint descriptor to be initialized from the specified endpoint.
    @param[in]  speed       The operating speed for which the descriptor should describe.

    @return     A pointer to the endpoint upon success; otherwise NULL on any error.
    @module     usbd

*******************************************************************************************************************************************/
STATUS USBD_GetEndpointDescriptor(USBDENDPOINT* endpt, USBENDPOINTDESCRIPTOR* des, USBSPEED speed)
{
#if (CFG_NULLCHECKING)
    if (endpt == NULL) {
        return ERR_NULLREFERENCE;
    }
    
    if (des == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif
    
    des->bLength            = sizeof(USBENDPOINTDESCRIPTOR);
    des->bDescriptorType    = USBDESTYPEENDPOINT;
    des->bEndpointAddress   = (endpt->addr);
    des->bmAttributes       = (endpt->type);
    
    if (speed == USBSPEED_HIGH) {
        des->wMaxPacketSize = endpt->pktszhs;
    } else {
        des->wMaxPacketSize = endpt->pktszfs;
    }
    
    des->bInterval          = endpt->interval;

    return SUCCESS;
}

/***************************************************************************************************************************************//**

    Finds and returns an endpoint from within a device that has the specified address.

    @param[in]  device      A pointer to the device that contains the endpoint to be returned.
    @param[in]  addr        The address of the endpoint to be returned.

    @return     A pointer to the endpoint upon success; otherwise NULL on any error.
    @module     usbd

*******************************************************************************************************************************************/
USBDENDPOINT* USBD_GetEndpoint(USBDDEVICE* device, BYTE addr)
{
    USBDINTERFACE* intf;
    USBDENDPOINT* endpoint;
    NODE* inode;
    NODE* enode;


#if (CFG_NULLCHECKING)
    if (device == NULL) {
        return NULL;
    }
#endif
    
    if ((addr & 0x7F) == 0) {                                   /* Is a control endpoint requested? */
        
        if ((addr & 0x80) == 0) {                               /* Yes, is it the control OUT endpoint? */
            return &device->rx0;                                /* Return the control OUT endpoint */
        }
             
        return &device->tx0;                                    /* Return the control IN endpoint */
    }

    if (device->curcfg == NULL) {                               /* Is there a configuration selected? */
        return NULL;                                            /* No configuration, cannot find the endpoint */
    }

    LIST_Foreach(inode, &device->curcfg->intfs) {               /* Search through the registered interfaces */
        intf = inode->value;                                    /* Access the interface */
        
        LIST_Foreach(enode, &intf->endpoints) {                 /* Search through the endpoints for the interface */       
            endpoint = enode->value;                            /* Access the endpoint */
            
            if (endpoint->addr == addr) {                       /* Does this endpoint have the requested address? */
                return endpoint;                                /* Yes, return the found endpoint */
            }
        }
    }

    return NULL;                                                /* Unable to find the requested endpoint */
}

#if (CFG_USBDENDPTBUFFERS)
/***************************************************************************************************************************************//**

    Assigns a buffer to an endpoint.

    @param[in]  endpt       A pointer to the endpoint to receive the buffer.
    @param[in]  buffer      A pointer to the start of the buffer memory.
    @param[in]  bufsize     The size, in bytes, of the buffer.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The buffer has been assigned to the endpoint.
     ERR_NULLREFERENCE      | The argument 'endpt' was found to be NULL.

    @module     usbd

*******************************************************************************************************************************************/
STATUS USBD_SetEndpointBuffer(USBDENDPOINT* endpt, void* buffer, UINT32 bufsize)
{
#if (CFG_NULLCHECKING)
    if (endpt == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif
    
    endpt->buffer = buffer;
    endpt->bufsize = bufsize;
    return SUCCESS;
}
#endif /* CFG_USBDENDPTBUFFERS */

/***************************************************************************************************************************************//**

    Handles a USB request that has targeted an endpoint.

    @param[in]  device      A pointer to the device that has received the request.
    @param[in]  request     A pointer to the request to be handled.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The request has been handled.
     ERR_NOTSUPPORTED       | The request is not supported.

    @module     internal

*******************************************************************************************************************************************/
STATUS USBD_EndpointRequest(USBDDEVICE* device, const USBREQUEST* request)
{
    ALIGNED(4) USBENDPOINTSTATUS status;
    USBDENDPOINT* endpt;


    endpt = USBD_GetEndpoint(device, request->wIndex);                                  /* Find the requested endpoint by it's address */
    if (endpt) {                                                                        /* Endpoint was found? */
        
        switch (request->bRequest) {
            case USBGETSTATUS:
                status.VALUE = 0;
                if (USBD_EndpointStalled(endpt)) {
                    status.BITS.HALT = 1;
                }                        
                USBD_Write(&device->tx0, &status, 2, NULL, CFG_USBDWRITETIMEOUT);
                return SUCCESS;
                
            case USBCLEARFEATURE:
                switch (request->wValue) {
                    case USBDENDPOINTHALT:
                        USBD_UnstallEndpoint(endpt);                                    /* Request to unstall the endpoint */
                        USBD_Write(&device->tx0, NULL, 0, NULL, CFG_USBDWRITETIMEOUT);  /* Return an ACK to the host */
                        return SUCCESS;
                }
                break;
                
            case USBSETFEATURE:
                switch (request->wValue) {
                    case USBDENDPOINTHALT:
                        USBD_StallEndpoint(endpt);                                      /* Request to stall the endpoint */
                        USBD_Write(&device->tx0, NULL, 0, NULL, CFG_USBDWRITETIMEOUT);  /* Return an ACK to the host */
                        return SUCCESS;
                }
                break;
        }
    }
    
    return ERR_NOTSUPPORTED;                                                            /* Unsupported request */
}
