/*******************************************************************************************************************************************

    DZX | USB DEVICE | MICROSOFT                                                                                          VERSION 18.2.1
    ------------------------------------------------------------------------------------------------------------------------------------

    This is part of the USB device stack and provides support for Microsoft OS descriptors.

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

#if (CFG_USBDMSFT)
/***************************************************************************************************************************************//**

    A Microsoft OS descriptor.
    @module     internal

*******************************************************************************************************************************************/
ALIGNED(4) const USBMSFTOSDESCRIPTOR MsftOSDescriptor = {
    sizeof(USBMSFTOSDESCRIPTOR),                /* bLength */
    USBDESTYPESTRING,                           /* bDescriptorType */
    {'M','S','F','T','1','0','0'},              /* qwSignature */
    0x1,                                        /* bMS_VendorCode */
    0x0,                                        /* bPad */
};

/***************************************************************************************************************************************//**

    A Microsoft OS descriptor that defines a WinUSB interface.
    @module     internal

*******************************************************************************************************************************************/
ALIGNED(4) const MSFTCOMPATFEATUREDESCRIPTOR MsftCompatIDFeatureDescriptor = {
    0x28,                                       /* bLength */
    0x0100,                                     /* bcdVersion */
    4,                                          /* wIndex */
    0x01,                                       /* bCount */
    {0,0,0,0,0,0,0},                            /* reserved[7] */
    0x00,                                       /* bFirstInterfaceNumber */
    0x01,                                       /* reserved2 */
    {'W','I','N','U','S','B',0,0},              /* compatibleID */
    {0,0,0,0,0,0,0,0},                          /* subCompatibleID */
    {0,0,0,0,0,0}                               /* reserved3[6] */
};

/***************************************************************************************************************************************//**

    A Microsoft extended feature descriptor that defines the device interface guid.
    @module     internal

*******************************************************************************************************************************************/
ALIGNED(4) const MSFTWINUSBEXTENDEDFEATURESDESCRIPTOR MsftExtPropertyFeatureDescriptor = {
    0x8E,                                                       /* bLength */
    0x0100,                                                     /* bcdVersion */
    5,                                                          /* wIndex */
    0x0001,                                                     /* wCount */
                                                                /* Section[0] */
    132,                                                        /* dwSize */
    0x00000001,                                                 /* dwPropertyDataType */
    40,                                                         /* wPropertyNameLength */
    { 'D','e','v','i','c','e',
      'I','n','t','e','r','f','a','c','e',
      'G','U','I','D',0 },                                      /* bPropertyName */
    78,                                                         /* dwPropertyDataLength */
    
    { '{', 'F', '1', '3', '0', '9', '9', '4', '7', '-',         /* bPropertyData */
           'B', 'B', '1', 'B', '-', 
           '4', 'B', '2', '6', '-', 
           'B', '6', '1', '1', '-',
           '7', '9', 'C', '2', '3', '4', 'D', '2', '6', 'B', 'C', 'D', '}', 0 
    }     
};

/***************************************************************************************************************************************//**

    Handles any Microsoft vendor specific USB requests.

    @param[in]  device      A pointer to the device that has received the request.
    @param[in]  request     A pointer to the request to be handled.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The request was handled.
     ERR_NOTSUPPORTED       | The request is not supported.

    @module     usbd-msft

*******************************************************************************************************************************************/
STATUS USBD_MicrosoftRequest(USBDDEVICE* device, const USBREQUEST* request)
{
    STATUS status;
    
    
    switch (request->bRequest) {
        case USBGETMSDESCRIPTOR:
        
            if (device->msftcb) {                                       /* Is there a registered handler? */
                status = device->msftcb(device, request);               /* Call the registered handler */
                if (status == SUCCESS) {
                    return SUCCESS;
                }
            }
            
            switch (request->wIndex) {
                case USBGETEXTENDEDCOMPATID:
                    USBD_Write(&device->tx0, 
                               &MsftCompatIDFeatureDescriptor, 
                               MIN(sizeof(MSFTCOMPATFEATUREDESCRIPTOR), request->wLength), 
                               NULL,
                               CFG_USBDWRITETIMEOUT);
                    return SUCCESS;
                case USBGETEXTENDEDPROPERTIES:
                    USBD_Write(&device->tx0, 
                               &MsftExtPropertyFeatureDescriptor, 
                               MIN(sizeof(MSFTWINUSBEXTENDEDFEATURESDESCRIPTOR), request->wLength), 
                               NULL,
                               CFG_USBDWRITETIMEOUT);
                    return SUCCESS;
            }
            break;
    }
   
    return ERR_NOTSUPPORTED;
}
    
/***************************************************************************************************************************************//**

    Sets an application-defined function to receive a callback when a Microsoft Descriptor request has been received.

    @param[in]  device      A pointer to the device stack instance that will receive the request.
    @param[in]  callback    A pointer to the application-defined function to receive the callback. Use NULL to clear a previously set
                            function.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The specified function has been assigned to receive a callback.
     ERR_NULLREFERENCE      | The argument 'device' was found to be NULL.

    @module     usbd-msft

*******************************************************************************************************************************************/
STATUS USBD_SetMicrosoftDescriptorEventHandler(USBDDEVICE* device, USBDREQUESTCALLBACK callback)
{
#if (CFG_NULLCHECKING)
    if (device == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif
    
    device->msftcb = callback;
    return SUCCESS;
}

/***************************************************************************************************************************************//**

    Enables/disables built-in support for Microsoft OS descriptors for a device stack.

    @param[in]  device      A pointer to the target device stack instance.
    @param[in]  enabled     Use TRUE to enable, or FALSE to disable support for Microsoft OS descriptors.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The option has been updated.
     ERR_NULLREFERENCE      | The argument 'device' was found to be NULL.

    @module     usbd-msft

*******************************************************************************************************************************************/
STATUS USBD_SetMicrosoftDescriptorSupport(USBDDEVICE* device, BOOLEAN enabled)
{
#if (CFG_NULLCHECKING)
    if (device == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif
    
    device->msft = enabled;
    return SUCCESS;
}

/***************************************************************************************************************************************//**

    Handles a Microsoft OS descriptor request.

    @param[in]  device      A pointer to the device that has received the request.
    @param[in]  request     A pointer to the request to be handled.

    @return

     Status Code        | Description
    ------------------- | ----------------------------------------------------------
     SUCCESS            | The request was handled.
     ERR_NOTSUPPORTED   | The request is not supported.

    @module     usbd-msft
         
*******************************************************************************************************************************************/
STATUS USBD_MicrosoftDescriptorRequest(USBDDEVICE* device, const USBREQUEST* request)
{
    USBD_Write(&device->tx0, 
               &MsftOSDescriptor, 
               MIN(MsftOSDescriptor.bLength, request->wLength), 
               NULL,
               INFINITE);
    return SUCCESS;
}
#endif /* CFG_USBDMSFT */
