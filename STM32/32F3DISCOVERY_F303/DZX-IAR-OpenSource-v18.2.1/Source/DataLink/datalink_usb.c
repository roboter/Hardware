/*******************************************************************************************************************************************

    DZX | DATALINK | UARTLINK                                                                                             VERSION 18.2.1
    ------------------------------------------------------------------------------------------------------------------------------------

    This provides a basic implementation of a data link that transfers messages over a native vendor specific USB connection.

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
#include "datalink_usb.h"

/*******************************************************************************************************************************************
    PRIVATE FUNCTIONS
*******************************************************************************************************************************************/
static void USBLINK_ThreadProc(void* arg);
static STATUS USBLINK_Write(DATALINK* link, void* arg, const void* data, UINT32 nbytes);

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
STATUS USBLINK_Create(USBLINK* link, DATALINKCREATEHANDLER create, UINT32 port, UINT16 vid, UINT16 pid, BYTE epnum)
{
    STATUS status;
    
    
#if (CFG_NULLCHECKING)
    if (link == NULL) {
        return ERR_NULLREFERENCE;
    }
    
    if (create == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif
    
    status = create(&link->base,                                /* Initialize the application specific data link */
                    USBLINK_Write,                              /* Write handler function */
                    link);                                      /* Optional argument for the write handler function */
    
    if (status != SUCCESS) {
        return status;
    }

    status = USBD_Create(&link->usb,                            /* Create and initialize an underlying USB device stack instance */
                         port,                                  /* USB port number */
                         vid,                                   /* USB device vendor ID */ 
                         pid);                                  /* USB device product ID */
    
    if (status != SUCCESS) {
        return status;
    }
    
    status = USBD_SetDeviceName(&link->usb,                     /* Assign default name strings for the device */
                                "DZX",                          /* Manufacturer Name */
                                "USB Data Link",                /* Product Name */
                                NULL);                          /* Serial Number */
    
    if (status != SUCCESS) {
        return status;
    }
    
    status = USBD_CreateInterface(&link->usb,                   /* Create a vendor defined interface */
                                  &link->usbintf,
                                  USBINTFCLASSVENDOR,
                                  USBINTFSUBCLASSVENDOR,
                                  USBINTFPROTOCOLVENDOR);
    
    status = USBD_CreateEndpoint(&link->usbintf,                /* Create an endpoint for receiving data */
                                 &link->rxendpt,
                                 USBTRANSFERBULK,
                                 epnum,
                                 64,
                                 512,
                                 1,
                                 OPT_SHORTPKT);
    if (status != SUCCESS) {
        return status;
    }

    status = USBD_CreateEndpoint(&link->usbintf,                /* Create an endpoint for transmitting data */
                                 &link->txendpt,
                                 USBTRANSFERBULK,
                                 (epnum | 0x80),
                                 64,
                                 512,
                                 1,
                                 OPT_SHORTPKT);
    if (status != SUCCESS) {
        return status;
    }

    status = USBD_SetMicrosoftDescriptorSupport(&link->usb, TRUE);  /* Enable automatic loading of WinUSB driver on Microsoft Windows */
    if (status != SUCCESS) {
        return status;
    }
    

    status = THREAD_Create(&link->thread,                       /* Create an underlying thread for receiving an processing messages */
                           "USB Data Link",                     /* A name for the thread */
                           link->stk,                           /* A pointer to the stack memory for the thread */
                           sizeof(link->stk),                   /* The size, in bytes, of the stack memory for the thread */
                           PRIO_NORMAL);                        /* The initial priority for the thread */
    
    if (status != SUCCESS) {
        return status;
    }

    return SUCCESS;
}

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
STATUS USBLINK_Destroy(USBLINK* link)
{
    STATUS status;
    
    
#if (CFG_NULLCHECKING)
    if (link == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif
    
    status = USBLINK_Close(link);                               /* Close the link (which will close the USB port and stop the thread) */
    if (status != SUCCESS) {
        return status;
    }
    
    status = THREAD_Destroy(&link->thread);                     /* Destroy the underlying thread */                     
    if (status != SUCCESS) {
        return status;
    }
    
    status = USBD_Destroy(&link->usb);                          /* Destroy the underlying USB device stack instance */
    if (status != SUCCESS) {
        return status;
    }
    
    return SUCCESS;
}

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
STATUS USBLINK_SetDeviceName(USBLINK* link, const CHAR* manufacturer, const CHAR* productName, const CHAR* serialNumber)
{
#if (CFG_NULLCHECKING)
    if (link == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif

    return USBD_SetDeviceName(&link->usb,                       /* Set the names in the underlying device stack instance */
                              manufacturer,
                              productName,
                              serialNumber);
}

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
STATUS USBLINK_Open(USBLINK* link)
{
    STATUS status;
    
    
#if (CFG_NULLCHECKING)
    if (link == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif
    
    status = USBD_Open(&link->usb);                                  /* Open the port and start communications */
    if (status != SUCCESS) {
        return status;
    }
    
    status = THREAD_Start(&link->thread,                            /* Start the thread for processing the received data */
                          USBLINK_ThreadProc,                       /* The process function for the thread */
                          link);                                    /* An argument for the thread process function */
    
    if (status != SUCCESS) {
        return status;
    }

    return SUCCESS;
}

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
STATUS USBLINK_Close(USBLINK* link)
{
    STATUS status;
    
    
#if (CFG_NULLCHECKING)
    if (link == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif
    
    status = THREAD_Abort(&link->thread);                       /* Abort the underlying thread */
    if (status != SUCCESS) {
        return status;
    }
    
    status = THREAD_Join(&link->thread, INFINITE);              /* Wait for the thread to terminate */
    if (status != SUCCESS) {
        return status;
    }
    
    status = USBD_Close(&link->usb);                            /* Close the USB device connection */
    if (status != SUCCESS) {
        return status;
    }
    
    return SUCCESS;
}

/***************************************************************************************************************************************//**

    The thread process function for a USB device data link. This continually reads the underlying receive endpoint and provides any 
    received messages to the data link.

    @param[in]  arg         A pointer to an application-defined argument.

    @return     None.
    @module     datalink-usb

*******************************************************************************************************************************************/
static void USBLINK_ThreadProc(void* arg)
{
    USBLINK* link = (USBLINK*)arg;
    STATUS status;
    UINT32 len;
    
    
    for (;;) {
        
        status = USBD_Read(&link->rxendpt,                          /* Receive messages over the receive endpoint */
                           link->buffer,                            /* A buffer to receive the message data */
                           sizeof(link->buffer),                    /* The maximum amount to receive */
                           &len,                                    /* A variable to retrieve actual amount of data received */
                           INFINITE);                               /* Wait indefinitely for a message (short packet will unblock) */

        if (status == SUCCESS) {
            
            DATALINK_ReceivedMessage(&link->base,                   /* Provide the received message to the data link */
                                     link->buffer,                  /* The buffer containing the message */
                                     len);                          /* The size of the message, in bytes */
        }
        
        if (THREAD_Aborted()) {
            return;                                                 /* Exit if aborted */
        }
    }
}

/***************************************************************************************************************************************//**

    A handler function called by a data link to transmit data over the link. This transmits the data over the underlying transmit
    endpoint.

    @param[in]  arg         A pointer to an application-defined argument.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The data has been written successfully.

    @module     datalink-usb

*******************************************************************************************************************************************/
static STATUS USBLINK_Write(DATALINK* link, void* arg, const void* data, UINT32 nbytes)
{
    USBLINK* usblink = (USBLINK*)arg;
    STATUS status;
    
    
    status = USBD_Write(&usblink->txendpt,                      /* Send the message data over the transmit endpoint */
                        data,                                   /* A pointer to the data to be transmitted */
                        nbytes,                                 /* The number of bytes to be transmitted */
                        NULL,                                   /* Pointer to receive number of bytes transmitted */
                        500);                                   /* Max time to wait for the transmit to complete */
    
    if (status != SUCCESS) {
        return status;                                          /* Transmit failed (nothing receiving on other end) */
    }
    
    return SUCCESS;
}
