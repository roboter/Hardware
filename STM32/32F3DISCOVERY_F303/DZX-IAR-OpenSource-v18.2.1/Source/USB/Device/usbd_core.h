/*******************************************************************************************************************************************

    DZX | USB DEVICE | CORE                                                                                               VERSION 18.2.1
    ------------------------------------------------------------------------------------------------------------------------------------

    This provides the core interface for the USB device stack. This interface is used by the USB device stack and is not intended to
    be used directly by an application.

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
#ifndef USBD_CORE_H__
#define USBD_CORE_H__

#include "usbd.h"

/*******************************************************************************************************************************************
    PRIVATE VARIABLES
*******************************************************************************************************************************************/
extern USBDDEVICE* USBD_Devices[CFG_USBDEVICEPORTS];

/*******************************************************************************************************************************************
    MACROS
*******************************************************************************************************************************************/
#define USB_GETRECIPIENT(request)       (request->bmRequestType & 0x01F)
#define USB_GETREQUESTTYPE(request)     ((request->bmRequestType & 0x60) >> 5)
#define USB_GETDESTYPE(request)         ((request->wValue & 0xFF00) >> 8)
#define USB_GETDESINDEX(request)        (request->wValue & 0x00FF)
#define USB_REQUESTDIRECTION(request)   ((request.bmRequestType & 0x80) >> 7 )   


/*******************************************************************************************************************************************
    DEVICE CONTROLLER FUNCTIONS
*******************************************************************************************************************************************/
/***************************************************************************************************************************************//**

    Initializes a device controller port for a USB device.

    @param[in]  device      A pointer to the device that is to be opened.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The port was opened.
     ERR_NULLREFERENCE      | The argument 'device' was found to be NULL.
     ERR_NOTSUPPORTED       | The port number assigned to the specified device is not supported.

    @module     internal

*******************************************************************************************************************************************/
extern STATUS USBD_InitController(USBDDEVICE* device);

/***************************************************************************************************************************************//**

    Opens a device controller port for a USB device.

    @param[in]  device      A pointer to the device that is to be opened.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The port was opened.
     ERR_NULLREFERENCE      | The argument 'device' was found to be NULL.
     ERR_NOTSUPPORTED       | The port number assigned to the specified device is not supported.

    @module     internal

*******************************************************************************************************************************************/
extern STATUS USBD_OpenController(USBDDEVICE* device);

/***************************************************************************************************************************************//**

    Closes the port used by a USB device.

    @param[in]  device      A pointer to the device that is to be closed.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The port was closed.
     ERR_NULLREFERENCE      | The argument 'device' was found to be NULL.

    @module     internal

*******************************************************************************************************************************************/
extern STATUS USBD_CloseController(USBDDEVICE* device);

/***************************************************************************************************************************************//**

    Resets the controller for a USB device.

    @param[in]  device      A pointer to the device to be reset.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The device controller has been reset.

    @module     internal

*******************************************************************************************************************************************/
extern STATUS USBD_Reset(USBDDEVICE* device);

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
extern STATUS USBD_SetAddress(USBDDEVICE* device, BYTE address);

/***************************************************************************************************************************************//**

    Sets the configuration for a USB device.

    @param[in]  device      A pointer to the target USB device.
    @param[in]  number      The number of the configuration that should be applied.

    @return     None.
    @module     internal

*******************************************************************************************************************************************/
extern void USBD_SetConfiguration(USBDDEVICE* device, BYTE number);


/*******************************************************************************************************************************************
    STRING MANIPULATION FUNCTIONS
*******************************************************************************************************************************************/
/***************************************************************************************************************************************//**

    Initializes a USB device stack string.

    @param[in]  str         A pointer to the string to be initialized.

    @return     None.
    @module     internal

*******************************************************************************************************************************************/
extern void USBD_InitString(USBDSTRING* str);

/***************************************************************************************************************************************//**

    Assigns a new string value for a USB device stack.

    @param[in]  stack       A pointer to the USB device stack instance to receive the string.
    @param[in]  str         A pointer to a caller allocated string object used to reference the string within the stack.
    @param[in]  cstr        A pointer to the string's actual text value.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The string has been assigned the specified value.

    @module     internal

*******************************************************************************************************************************************/
extern STATUS USBD_AssignString(USBDDEVICE* device, USBDSTRING* str, const CHAR* cstr);

/***************************************************************************************************************************************//**

    Removes a string from a USB device stack.

    @param[in]  stack       A pointer to the USB device stack instance that contains the string.
    @param[in]  str         A pointer to the string to be removed.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The string has been removed.

    @module     internal

*******************************************************************************************************************************************/
extern STATUS USBD_RemoveString(USBDDEVICE* device, USBDSTRING* str);


/*******************************************************************************************************************************************
    CORE REQUEST HANDLERS
*******************************************************************************************************************************************/
/***************************************************************************************************************************************//**

    Handles a USB request that has targeted an interface.

    @param[in]  device      A pointer to the device that has received the request.
    @param[in]  request     A pointer to the request to be handled.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The request has been handled.
     ERR_NOTSUPPORTED       | The request is not supported.

    @module     internal

*******************************************************************************************************************************************/
extern STATUS USBD_InterfaceRequest(USBDDEVICE* device, const USBREQUEST* request);

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
extern STATUS USBD_EndpointRequest(USBDDEVICE* device, const USBREQUEST* request);

/***************************************************************************************************************************************//**

    Handles any Microsoft vendor specific USB requests.

    @param[in]  device      A pointer to the device that has received the request.
    @param[in]  request     A pointer to the request to be handled.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The request was handled.
     ERR_NOTSUPPORTED       | The request is not supported.

    @module     internal

*******************************************************************************************************************************************/
extern STATUS USBD_MicrosoftRequest(USBDDEVICE* device, const USBREQUEST* request);

/***************************************************************************************************************************************//**

    Handles a Microsoft OS descriptor request.

    @param[in]  device      A pointer to the device that has received the request.
    @param[in]  request     A pointer to the request to be handled.

    @return

     Status Code        | Description
    ------------------- | ----------------------------------------------------------
     SUCCESS            | The request was handled.
     ERR_NOTSUPPORTED   | The request is not supported.

    @module     internal
         
*******************************************************************************************************************************************/
extern STATUS USBD_MicrosoftDescriptorRequest(USBDDEVICE* device, const USBREQUEST* request);

#endif /* USBD_CORE_H__ */
