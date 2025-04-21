/*******************************************************************************************************************************************

    DZX | DATALINK | UARTLINK                                                                                             VERSION 18.2.1
    ------------------------------------------------------------------------------------------------------------------------------------

    This provides the interface for a basic implementation of a data link that transfers messages over a native vendor specific USB 
    connection.

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
#ifndef USBLINK_H__
#define USBLINK_H__

#include "DataLink/datalink.h"
#include "USB/Device/usbd.h"


/*******************************************************************************************************************************************
    TYPE DEFINITIONS
*******************************************************************************************************************************************/
/***************************************************************************************************************************************//**

    Represents a data link instance that transfers messages over a generic USB connection.
    @module     datalink-usb

*******************************************************************************************************************************************/
typedef struct USBLINK {
    DATALINK        base;                           /**< Build upon the base data link */
    USBDDEVICE      usb;                            /**< USB device stack instance */
    USBDINTERFACE   usbintf;                        /**< USB device interface */
    USBDENDPOINT    rxendpt;                        /**< An endpoint for receiving data */
    USBDENDPOINT    txendpt;                        /**< An endpoint for transmitting data */                
    THREAD          thread;                         /**< A thread for receiving and processing data for the link */
    BYTE            stk[CFG_USBLINKSTACKSIZE];      /**< Stack memory for the thread */
    BYTE            buffer[CFG_USBLINKBUFFERSIZE];  /**< A buffer for receiving data over the receive endpoint */
} USBLINK;


/*******************************************************************************************************************************************
    PUBLIC FUNCTIONS
*******************************************************************************************************************************************/
/***************************************************************************************************************************************//**

    Creates and initializes a data link that transfers messages over a native USB device connection.

    @param[in]  link        A pointer to a caller allocated USB data link instance to be initialized.
    @param[in]  create      The create handler function to initialize the application-defined data link.
    @param[in]  port        The USB port number for the device.
    @param[in]  vid         The USB vendor ID number for the device.
    @param[in]  pid         The USB product ID number for the device.
    @param[in]  epnum       The number of the endpoint used for transmitting and receiving messages.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The data link has been created and initialized.
     ERR_NULLREFERENCE      | The argument 'link' or 'create' was found to be NULL.

    @module     datalink-usb

*******************************************************************************************************************************************/
extern STATUS USBLINK_Create(USBLINK* link, DATALINKCREATEHANDLER create, UINT32 port, UINT16 vid, UINT16 pid, BYTE epnum);

/***************************************************************************************************************************************//**

    Assigns the device name strings to the underlying device stack for a USB data link.

    @param[in]  link            A pointer to the target USB data link.
    @param[in]  manufacturer    A pointer to a new manufacturer name for the device.
    @param[in]  productName     A pointer to a new product name for the device.
    @param[in]  serialNumber    A pointer to a new serial number for the device.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The device name strings have been updated.
     ERR_NULLREFERENCE      | The argument 'link' was found to be NULL.

    @module     datalink-usb

*******************************************************************************************************************************************/
extern STATUS USBLINK_SetDeviceName(USBLINK* link, const CHAR* manufacturer, const CHAR* productName, const CHAR* serialNumber);

/***************************************************************************************************************************************//**

    Opens the underlying port for a USB data link.

    @param[in]  link        A pointer to the USB data link to be opened.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The link has been opened for communications.
     ERR_NULLREFERENCE      | The argument 'link' was found to be NULL.

    @module     datalink-usb

*******************************************************************************************************************************************/
extern STATUS USBLINK_Open(USBLINK* link);

/***************************************************************************************************************************************//**

    Closes the underlying port and stops communications for a USB data link.

    @param[in]  link        A pointer to the USB data link to be closed.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The link has been closed.
     ERR_NULLREFERENCE      | The argument 'link' was found to be NULL.

    @module     datalink-usb

*******************************************************************************************************************************************/
extern STATUS USBLINK_Close(USBLINK* link);

/***************************************************************************************************************************************//**

    Destroys a USB data link.

    @param[in]  link        A pointer to the USB data link to be destroyed.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The link has been destroyed.
     ERR_NULLREFERENCE      | The argument 'link' was found to be NULL.

    @module     DATALINK-UART

*******************************************************************************************************************************************/
extern STATUS USBLINK_Destroy(USBLINK* link);

#endif /* USBLINK_H__ */
