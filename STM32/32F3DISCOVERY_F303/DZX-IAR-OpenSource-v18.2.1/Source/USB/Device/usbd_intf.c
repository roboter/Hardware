/*******************************************************************************************************************************************

    DZX | USB DEVICE | INTERFACES                                                                                         VERSION 18.2.1
    ------------------------------------------------------------------------------------------------------------------------------------

    This is part of the USB device stack and provides support for interfaces.

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

/*******************************************************************************************************************************************
    PRIVATE FUNCTIONS
*******************************************************************************************************************************************/
static STATUS USBD_SetInterface(USBDDEVICE* device, USBDINTERFACE* intf);

/***************************************************************************************************************************************//**

    Creates and adds an interface to the current configuration of a USB device stack instance.

    @param[in]  device      A pointer to the device stack instance to receive the interface.
    @param[in]  intf        A pointer to a caller allocated interface to be initialized.
    @param[in]  bClass      The class code for the interface.
    @param[in]  bSubClass   The subclass code for the interface.
    @param[in]  bProtocol   The protocol code for the interface.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The interface has been initialized and added to the device instance.
     ERR_NULLREFERENCE      | The argument 'device' or 'intf' was found to be NULL.
     ERR_INVALIDOPERATION   | The device does not have a valid active configuration.

    @module     usbd

*******************************************************************************************************************************************/
STATUS USBD_CreateInterface(USBDDEVICE* device, USBDINTERFACE* intf, BYTE bClass, BYTE bSubClass, BYTE bProtocol)
{
#if (CFG_NULLCHECKING)
    if (device == NULL) {
        return ERR_NULLREFERENCE;
    }
    
    if (intf == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif
    
    if (device->cfg == NULL) {                                  /* Does the device have an active configuration? */
        return ERR_INVALIDOPERATION;
    }
    
    intf->device = device;                                      /* Assign a reference to the device for the interface */
    intf->cfg = device->cfg;                                    /* Assign a reference to the configuration that owns the interface */
    
    intf->number = intf->cfg->intfs.count;                      /* Assign the interface a number */
    
    intf->classCode.bClass = bClass;                            /* Assign the interface class codes */
    intf->classCode.bSubClass = bSubClass;
    intf->classCode.bProtocol = bProtocol;
    
    
    intf->altsetting = 0;
    intf->cursetting = 0;
    
    LIST_Init(&intf->associntfs);
    LIST_Init(&intf->altintfs);
    LIST_Init(&intf->endpoints);
    
    LIST_InitNode(&intf->assocnode);
    LIST_InitNode(&intf->altnode);

    LIST_AddLast(&intf->cfg->intfs, &intf->node, intf);
    
    USBD_InitString(&intf->str);
   
    return SUCCESS;
}

/***************************************************************************************************************************************//**

    Creates an associated interface to the current configuration of a USB device stack.

    @param[in]  device      A pointer to the device stack instance to receive the interface.
    @param[in]  other       A pointer to the other interface that is associated with the interface to be initialized.
    @param[in]  intf        A pointer to a caller allocated interface to be initialized.
    @param[in]  bClass      The class code for the interface.
    @param[in]  bSubClass   The subclass code for the interface.
    @param[in]  bProtocol   The protocol code for the interface.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The interface has been initialized and added to the device.
     ERR_NULLREFERENCE      | The argument 'device', 'other' or 'intf' was found to be NULL.
     ERR_INVALIDOPERATION   | The device does not have a valid active configuration.

    @module     usbd

*******************************************************************************************************************************************/
STATUS USBD_CreateAssociatedInterface(USBDDEVICE* device, USBDINTERFACE* other, USBDINTERFACE* intf, BYTE bClass, BYTE bSubClass, BYTE bProtocol)
{
    STATUS status;
    
    
#if (CFG_NULLCHECKING)
    if (other == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif
    
    status = USBD_CreateInterface(device, intf, bClass, bSubClass, bProtocol);
    if (status == SUCCESS) {
        return status;
    }
    
    LIST_AddLast(&other->associntfs, &intf->assocnode, intf);
    return SUCCESS;
}

/***************************************************************************************************************************************//**

    Creates an alternate interface to the current configuration of a USB device stack.

    @param[in]  device      A pointer to the device stack instance to receive the interface.
    @param[in]  alt         A pointer to the other alternate interface for the interface to be created.
    @param[in]  intf        A pointer to a caller allocated interface to be initialized.
    @param[in]  bClass      The class code for the interface.
    @param[in]  bSubClass   The subclass code for the interface.
    @param[in]  bProtocol   The protocol code for the interface.
    @param[in]  altNumber   The number for the alternate interface to be created.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The interface has been initialized and added to the device.
     ERR_NULLREFERENCE      | The argument 'device', 'alt' or 'intf' was found to be NULL.
     ERR_INVALIDOPERATION   | The device does not have a valid active configuration.

    @module     usbd

*******************************************************************************************************************************************/
STATUS USBD_CreateAlternateInterface(USBDDEVICE* device, USBDINTERFACE* alt, USBDINTERFACE* intf, BYTE bClass, BYTE bSubClass, BYTE bProtocol, BYTE altNumber)
{
    STATUS status;
    
   
#if (CFG_NULLCHECKING)
    if (alt == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif
    
    status = USBD_CreateInterface(device, intf, bClass, bSubClass, bProtocol);
    if (status == SUCCESS) {
        return status;
    }
    
    intf->altsetting = altNumber;
    LIST_AddLast(&alt->altintfs, &intf->altnode, intf);
    return SUCCESS;
}

/***************************************************************************************************************************************//**

    Destroys and removes an interface from a USB device stack.

    @param[in]  intf        A pointer to the interface to be destroyed and removed.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The interface has been destroyed and removed from it's device.
     ERR_NULLREFERENCE      | The argument 'device' or 'intf' was found to be NULL.

    @module     usbd

*******************************************************************************************************************************************/
STATUS USBD_DestroyInterface(USBDINTERFACE* intf)
{
    STATUS status;
    NODE* node;
    
    
#if (CFG_NULLCHECKING)
    if (intf == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif
    
    node = intf->endpoints.first;
    while (node) {
        status = USBD_DestroyEndpoint((USBDENDPOINT*)node->value);
        if (status != SUCCESS) {
            return status;
        }
        
        node = intf->endpoints.first;
    }

    if (intf->cfg) {
        LIST_Remove(&intf->cfg->intfs, &intf->node);
        intf->cfg = NULL;
    }

    return SUCCESS;
}

/***************************************************************************************************************************************//**

    Searches for and returns a device interface with the specified number.

    @param[in]  cfg         A pointer to the configuration that contains the interface to be returned.
    @param[in]  number      The number of the interface to be returned.

    @return     A pointer to the interface with the specified number if found; otherwise NULL.
    @module     usbd

*******************************************************************************************************************************************/
USBDINTERFACE* USBD_GetInterface(USBDCFG* cfg, BYTE number)
{
    USBDINTERFACE* intf;
    NODE* node;



    if (cfg == NULL) {
        return NULL;
    }

    LIST_Foreach(node, &cfg->intfs) {
        intf = node->value;
        if (intf->number == number) {
            return intf;
        }
    }

    return NULL;
}

/***************************************************************************************************************************************//**

    Returns the device interface at the specified index.

    @param[in]  cfg         A pointer to the configuration that contains the interface to be returned.
    @param[in]  idx         The index for the interface to be returned.

    @return     A pointer to the interface with the specified number if found; otherwise NULL.
    @module     usbd

*******************************************************************************************************************************************/
USBDINTERFACE* USBD_GetInterfaceByIndex(USBDCFG* cfg, BYTE idx)
{
    NODE* node;
    UINT32 k = 0;



    if (cfg == NULL) {
        return NULL;
    }

    LIST_Foreach(node, &cfg->intfs) {
        if (k == idx) {
            return node->value;
        }
        
        ++k;
    }

    return NULL;
}

/***************************************************************************************************************************************//**

    Assigns a name to a device interface.

    @param[in]  intf        A pointer to the interface to receive the name.
    @param[in]  name        The new name for the interface.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The name was assigned to the interface.
     ERR_NULLREFERENCE      | The argument 'intf' was found to be NULL.
     ERR_NOTINITIALIZED     | The interface has not been initialized.

    @module     usbd

*******************************************************************************************************************************************/
STATUS USBD_SetInterfaceName(USBDINTERFACE* intf, const CHAR* name)
{
#if (CFG_NULLCHECKING)
    if (intf == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif
    
    if (intf->device == NULL) {
        return ERR_NOTINITIALIZED;
    }
    
    return USBD_AssignString(intf->device, &intf->str, name);
}

/***************************************************************************************************************************************//**

    Returns the class codes for a device interface.

    @param[in]  intf        A pointer to the interface that contains the codes to be returned.

    @return     A pointer to the class codes for the specified interface upon success; otherwise NULL.
    @module     usbd

*******************************************************************************************************************************************/
const USBCLASSCODE* USBD_GetInterfaceClass(USBDINTERFACE* intf)
{
#if (CFG_NULLCHECKING)
    if (intf == NULL) {
        return NULL;
    }
#endif
    
    return &intf->classCode;
}

/***************************************************************************************************************************************//**

    Returns the descriptor for a USB device interface.

    @param[in]  intf        A pointer to the target interface.
    @param[out] des         A caller allocated descriptor to be used to receive the returned descriptor.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The descriptor has been returned.
     ERR_NULLREFERENCE      | The argument 'intf' or 'des' was found to be NULL.

    @module     usbd

*******************************************************************************************************************************************/
STATUS USBD_GetInterfaceDescriptor(USBDINTERFACE* intf, USBINTERFACEDESCRIPTOR* des)
{
#if (CFG_NULLCHECKING)
    if (intf == NULL) {
        return ERR_NULLREFERENCE;
    }
    
    if (des == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif
    
    des->bLength            = sizeof(USBINTERFACEDESCRIPTOR);
    des->bDescriptorType    = USBDESTYPEINTERFACE;
    des->bInterfaceNumber   = intf->number;
    des->bAlternateSetting  = intf->altsetting;
    des->bNumEndpoints      = intf->endpoints.count;
    des->bInterfaceClass    = intf->classCode.bClass;
    des->bInterfaceSubClass = intf->classCode.bSubClass;
    des->bInterfaceProtocol = intf->classCode.bProtocol;
    des->iInterface         = intf->str.idx;

    return SUCCESS;
}

/***************************************************************************************************************************************//**

    Returns the interface association descriptor for a USB device interface.

    @param[in]  intf        A pointer to the target interface that contains associated interfaces.
    @param[out] des         A caller allocated descriptor to be used to receive the returned descriptor.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The descriptor has been returned.
     ERR_NULLREFERENCE      | The argument 'intf' or 'des' was found to be NULL.

    @module     usbd

*******************************************************************************************************************************************/
STATUS USBD_GetAssociationDescriptor(USBDINTERFACE* intf, USBINTERFACEASSOCIATIONDESCRIPTOR* des)
{
#if (CFG_NULLCHECKING)
    if (intf == NULL) {
        return ERR_NULLREFERENCE;
    }
    
    if (des == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif
    
    des->bLength = sizeof(USBINTERFACEASSOCIATIONDESCRIPTOR);
    des->bDescriptorType = USBDESTYPEINTERFACEASSOCIATION;
    des->bFirstInterface = intf->number;
    des->bInterfaceCount = intf->associntfs.count + 1;
    des->bFunctionClass = 0xFF;
    des->bFunctionSubClass = 0xFF;
    des->bFunctionProtocol = 0xFF;
    des->iInterface = 0;

    return SUCCESS;
}

/***************************************************************************************************************************************//**

    Handles a USB request that has targeted an interface.

    @param[in]  device      A pointer to the device that has received the request.
    @param[in]  request     A pointer to the request to be handled.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The request has been handled.
     ERR_NOTSUPPORTED       | The request is not supported.

    @module     usbd

*******************************************************************************************************************************************/
STATUS USBD_InterfaceRequest(USBDDEVICE* device, const USBREQUEST* request)
{
    USBDINTERFACE* intf;
    NODE* node;
    STATUS status;
   

    intf = USBD_GetInterfaceByIndex(device->curcfg, request->wIndex);   /* Find the target interface */
    if (intf) {
        if (intf->reqcb) {
            status = intf->reqcb(device, intf, request);
            if (status == SUCCESS) {                                    /* Was the request already handled? */
                return SUCCESS;                                         /* Request handled by specific class, exit. */
            }
        } 
    }
    
    switch (request->bmRequestType.type) {
        case USBSTANDARD:
            switch (request->bRequest) {
                
                case USBGETSTATUS:
                    USBD_Write(&device->tx0, &intf->status, sizeof(UINT16), NULL, CFG_USBDWRITETIMEOUT);
                    return SUCCESS;

                case USBSETINTERFACE:
                    if (device->curcfg) {
                        LIST_Foreach(node, &device->curcfg->intfs) {
                            intf = node->value;
                            if (intf->number == request->wIndex) {
                                intf->cursetting = request->wValue;
                                
                                USBD_SetInterface(device, intf);
                            }
                        }
                    }
                    USBD_Write(&device->tx0, NULL, 0, NULL, CFG_USBDWRITETIMEOUT);
                    break;

                case USBGETINTERFACE:
                    intf = USBD_GetInterface(device->curcfg, request->wIndex);
                    if (intf) {
                        USBD_Write(&device->tx0, &intf->altsetting, sizeof(BYTE), NULL, CFG_USBDWRITETIMEOUT);
                    }
                    break;
            }
            break;
        case USBCLASS:
            break;

        case USBVENDOR:
            break;
    }
    
    return ERR_NOTSUPPORTED;
}

/***************************************************************************************************************************************//**

    Handles a USB request to set an interface.

    @param[in]  device      A pointer to the device that has received the request.
    @param[in]  intf        A pointer to the interface to be set.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The interface has been set.

    @module     internal

*******************************************************************************************************************************************/
static STATUS USBD_SetInterface(USBDDEVICE* device, USBDINTERFACE* intf)
{
    STATUS status;
    NODE* node;
    USBDENDPOINT* endpt;
    
    
    LIST_Foreach(node, &intf->endpoints) {                      /* Go through each endpoint within the interface */
        endpt = node->value;
        
        status = USBD_UnstallEndpoint(endpt);                   /* Unstall, reset each endpoint */
        if (status != SUCCESS) {
            return status;
        }
    }

    return SUCCESS;
}
