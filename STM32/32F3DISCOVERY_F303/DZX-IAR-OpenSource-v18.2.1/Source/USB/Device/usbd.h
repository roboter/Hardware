/*******************************************************************************************************************************************

    DZX | USB DEVICE STACK                                                                                                VERSION 18.2.1
    ------------------------------------------------------------------------------------------------------------------------------------

    This provides the public interface for the USB device stack.

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
#ifndef USBD_H__
#define USBD_H__

#include "Kernel/kernel.h"
#include "Kernel/kernel_list.h"
#include "Kernel/kernel_thread.h"
#include "Kernel/kernel_signal.h"
#include "USB/usb.h"
#include "mcu_usbd.h"
#include "usbd_cfg.h"


/*******************************************************************************************************************************************
    DEFINITIONS
*******************************************************************************************************************************************/
#define OPT_SHORTPKT            1                   /* Option to have endpoint use short packet termination */

/*******************************************************************************************************************************************
    TYPE DEFINITIONS
*******************************************************************************************************************************************/
typedef struct USBDENDPOINT USBDENDPOINT;
typedef struct USBDINTERFACE USBDINTERFACE;
typedef struct USBDDEVICE USBDDEVICE;
typedef struct USBDCFG USBDCFG;
typedef struct USBDCFGSETTINGS USBDCFGSETTINGS;
typedef struct USBDSTRING USBDSTRING;

/***************************************************************************************************************************************//**

    An application-defined function that receives a callback upon the reception of a request from a host.
    @module     usbd

*******************************************************************************************************************************************/
typedef STATUS (*USBDREQUESTCALLBACK)(USBDDEVICE* device, const USBREQUEST* request);

/***************************************************************************************************************************************//**

    An application-defined function that receives a callback upon the reception of a request from a host that has targeted a specific
    interface.
    @module     usbd

*******************************************************************************************************************************************/
typedef STATUS (*USBDINTFREQUESTCALLBACK)(USBDDEVICE* device, USBDINTERFACE* intf, const USBREQUEST* request);

/***************************************************************************************************************************************//**

    An application-defined function that receives a callback when interface descriptors are being requested.
    @module     usbd

*******************************************************************************************************************************************/
typedef UINT32 (*USBDINTFDESCRIPTORCALLBACK)(USBDINTERFACE* intf, void* buf);

/***************************************************************************************************************************************//**

    Represents application-defined settings for a configuration within a USB device stack.
    @module     usbd

*******************************************************************************************************************************************/
struct USBDCFGSETTINGS {
    BOOLEAN     selfPowered;            /**< An indication of whether the device is self powered. */
    BOOLEAN     remoteWakeup;           /**< An indication of whether the device supports remote wakeup. */
    UINT16      maxPower;               /**< The maximum power, in milliamps, required by the device. Limited to 500mA per USB spec. */
};

/***************************************************************************************************************************************//**

    Represents a USB configuration within a USB device stack.
    @module     usbd

*******************************************************************************************************************************************/
struct USBDCFG {
    NODE            node;               /**< A node to place this configuration within a list */
    USBDDEVICE*     device;             /**< A pointer to the device that owns the configuration */
    BYTE            number;             /**< A number for the configuration */
    USBDCFGSETTINGS settings;           /**< Application-defined settings for the configuration */
    LIST            intfs;              /**< A list of interfaces that belong to the configuration */
    USBDINTERFACE*  intf;               /**< The selected interface */
};

/***************************************************************************************************************************************//**

    Represents a string within a USB device stack.
    @module     usbd

*******************************************************************************************************************************************/
struct USBDSTRING {
    NODE        node;                   /**< A node for inserting the string into a list */
    const CHAR* cstr;                   /**< The text of the string */
    BYTE        idx;                    /**< The index for the string */
    BYTE        pad[3];                 /**< Explicit padding for 32-bit alignment */
};

/***************************************************************************************************************************************//**

    Represents a USB interface within a USB device stack.
    @module     usbd-intf

*******************************************************************************************************************************************/
struct USBDINTERFACE {
    NODE                    node;           
    NODE                    assocnode;
    NODE                    altnode;
    USBDDEVICE*             device;         /**< A pointer to the device that owns the interface */
    USBDCFG*                cfg;
    USBCLASSCODE            classCode;
    LIST                    endpoints;      /**< A list of endpoints that belong with the interface */
    UINT16                  status;
    BYTE                    number;
    BYTE                    cursetting;
    BYTE                    altsetting;
    USBDINTFREQUESTCALLBACK reqcb;
    USBDINTFDESCRIPTORCALLBACK  descb;
    LIST                    associntfs;
    LIST                    altintfs;
    
    USBDSTRING              str;                /**< A string for the interface */
};

/***************************************************************************************************************************************//**

    Represents an endpoint within a USB device stack.
    @module     usbd-endpt

*******************************************************************************************************************************************/
struct USBDENDPOINT {
    NODE                node;                   /**< A node to register the endpoint with a device stack */
    NODE                inode;                  /**< A node to register the endpoint with a parent interface */
    USBDDEVICE*         device;                 /**< A pointer to the device that owns the endpoint */
    USBDINTERFACE*      intf;                   /**< A pointer to the interface that owns the endpoint */
    BYTE                addr;                   /**< The address for this endpoint */
    USBTRANSFERTYPE     type;                   /**< The type of transfers performed by this endpoint */
    BYTE                interval;               /**< The configured interval value for the endpoint */
    UINT16              pktszfs;                /**< The maximum transfer size, in bytes, per packet for the endpoint in full speed mode */
    UINT16              pktszhs;                /**< The maximum transfer size, in bytes, per packet for the endpoint in high speed mode */
    UINT32              opt;                    /**< Additional options for the endpoint */
    SIGNALSET           signals;                /**< A set of signals used to signal a thread blocked upon the endpoint */
    void*               data;                   /**< A pointer to the transfer data for the endpoint */
    UINT32              nbytes;                 /**< The number of bytes of transfer data for the endpoint */
    UINT32              idx;                    /**< An index into the transfer data for the endpoint */
    STATUS              result;                 /**< The result status code for the latest transfer of the endpoint */
    BOOLEAN             stalled;                /**< An indication of whether the endpoint is currently stalled (halted) */
    BOOLEAN             zlp;                    /**< An indication of whether the endpoint is transferring a zero-length packet */
    
#if (CFG_USBDENDPTBUFFERS)
    void*               buffer;                 /**< A pointer to a copy buffer used to achieve proper alignment */
    UINT32              bufsize;                /**< The size, in bytes, of the copy buffer */
#endif
};

/***************************************************************************************************************************************//**

    Represents a USB device mode instance.
    @module     usbd

*******************************************************************************************************************************************/
struct USBDDEVICE {
    UINT32          port;               /**< Physical port number */
    USBDCD          dcd;                /**< USB Device Controller Driver (DCD) */
    LIST            cfgs;               /**< Supported Configurations */
    LIST            endpts;             /**< A list of currently open endpoints */
    LIST            strs;               /**< Strings for the descriptors */
    USBREQUEST      req;                /**< A request as received from a host */
    UINT32          respbuf[CFG_USBDREQRESBUFSIZE / sizeof(UINT32)];    /**< A buffer for building responses for a host */
    USBDEVICEID     id;                 /**< Vendor and Product IDs */
    USBCLASSCODE    classCode;          /**< Device class codes */
    BYTE            addr;               /**< Device adress */
    UINT16          rls;                /**< Device Release Version */
    USBDEVICESTATUS status;             /**< Current status for the device */
 
    USBDCFG         defcfg;             /**< A default configuration for the stack */
    BOOLEAN         msft;               /**< An indication of whether Microsoft OS descriptors are supported by the device */
    BOOLEAN         open;               /**< An indication of whether the device is currently open for communications */
    BOOLEAN         suspended;          /**< An indication of whether the device is currently suspended */
    
    USBDSTRING      manufstr;           /**< Manufacturer name string */
    USBDSTRING      prodstr;            /**< Product name string */
    USBDSTRING      serstr;             /**< Serial number string */
    
    USBDCFG*        cfg;                /**< The locally selected configuration */
    USBDCFG*        curcfg;             /**< The configuration that has been selected by the host */
    
    USBDENDPOINT    rx0;                /**< The control receive endpoint */
    USBDENDPOINT    tx0;                /**< The control transmit endpoint */
    
    USBDREQUESTCALLBACK msftcb;         /**< A microsoft OS request callback handler */
    THREAD          thread;                     /**< A thread for processing requests received by a host (enumeration etc) */
    BYTE            stk[CFG_USBDSTACKSIZE];     /**< Stack memory for the thread used to process requests for the device stack */
};
    
    
/*******************************************************************************************************************************************
    PUBLIC FUNCTIONS
*******************************************************************************************************************************************/
/***************************************************************************************************************************************//**

    Creates and initializes a USB device stack instance.

    @param[in]  device      A pointer to a caller allocated USB device stack instance to be initialized.
    @param[in]  port        The port number for the device.
    @param[in]  vendorID    The USB vendor ID number for the device.
    @param[in]  productID   The USB product ID number for the device.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The device stack has been initialized.
     ERR_NULLREFERENCE      | The argument 'device' was found to be NULL.
     ERR_NOTSUPPORTED       | The specified port number is not supported.

    @module     usbd

*******************************************************************************************************************************************/
extern STATUS USBD_Create(USBDDEVICE* device, UINT32 port, UINT16 vendorID, UINT16 productID);

/***************************************************************************************************************************************//**

    Destroys a USB device stack instance.

    @param[in]  device      A pointer to the USB device stack instance to be destroyed.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The device stack has been destroyed.
     ERR_NULLREFERENCE      | The argument 'device' was found to be NULL.

    @module     usbd

*******************************************************************************************************************************************/
extern STATUS USBD_Destroy(USBDDEVICE* device);

/***************************************************************************************************************************************//**

    Opens the port for communications for a USB device stack.

    @param[in]  device      A pointer to the device stack to be opened.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The device stack is now open for communications.
     ERR_NULLREFERENCE      | The argument 'device' was found to be NULL.
     ERR_ACCESSDENIED       | The specified port is already open.
     ERR_NOTSUPPORTED       | The specified port is not supported.

    @module     usbd

*******************************************************************************************************************************************/
extern STATUS USBD_Open(USBDDEVICE* device);

/***************************************************************************************************************************************//**

    Closes and terminates communications for a USB device stack.

    @param[in]  device       A pointer to the device stack to be closed.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The device was closed.
     ERR_NULLREFERENCE      | The argument 'device' was found to be NULL.

    @module     usbd

*******************************************************************************************************************************************/
extern STATUS USBD_Close(USBDDEVICE* device);

/***************************************************************************************************************************************//**

    Gets an indication of whether a USB device stack is open for communications.

    @param[in]  device       A pointer to the target device stack.

    @return     TRUE if the device has been opened for communications; otherwise FALSE.
    @module     usbd

*******************************************************************************************************************************************/
extern BOOLEAN USBD_IsOpen(USBDDEVICE* device);

/***************************************************************************************************************************************//**

    Gets an indication of whether a USB device stack is currently connected to a host.

    @param[in]  device       A pointer to the target device stack.

    @return     TRUE if the device stack has been configured by a host; otherwise FALSE.
    @module     usbd

*******************************************************************************************************************************************/
extern BOOLEAN USBD_IsConnected(USBDDEVICE* device);

/***************************************************************************************************************************************//**

    Gets an indication of whether a USB device stack has been suspended by the host.

    @param[in]  device       A pointer to the target device stack.

    @return     TRUE if the device stack has been suspended by the host; otherwise FALSE.
    @module     usbd

*******************************************************************************************************************************************/
extern BOOLEAN USBD_IsSuspended(USBDDEVICE* device);

/***************************************************************************************************************************************//**

    Returns the current speed of a USB connection.

    @param[in]  device         A pointer to the target USB device stack instance.

    @return     The current speed of the connection.

     Speed                  | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     USBSPEED_UNKNOWN       | The connection speed is unknown.
     USBSPEED_LOW           | The connection is low speed (1.5 Mbit/s).
     USBSPEED_FULL          | The connection is full speed (12 Mbit/s).
     USBSPEED_HIGH          | The connection is high speed (480 Mbit/s).

    @module     usbd

*******************************************************************************************************************************************/
extern USBSPEED USBD_Speed(USBDDEVICE* device);

/***************************************************************************************************************************************//**

    Returns the identifier values for a USB device stack instance.

    @param[in]  device       A pointer to the target device stack.

    @return     A pointer to the device identifiers for the specified device stack upon success; NULL on any error.
    @module     usbd

*******************************************************************************************************************************************/
extern const USBDEVICEID* USBD_GetDeviceID(USBDDEVICE* device);

/***************************************************************************************************************************************//**

    Assigns the device identifier values for a USB device stack.

    @param[in]  device      A pointer to the target device stack to receive the identifier values.
    @param[in]  vendorID    The new vendor ID value for the device.
    @param[in]  productID   The new product ID value for the device.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The identifier values have been updated.
     ERR_NULLREFERENCE      | The argument 'device' was found to be NULL.

    @module     usbd

*******************************************************************************************************************************************/
extern STATUS USBD_SetDeviceID(USBDDEVICE* device, UINT16 vendorID, UINT16 productID);

/***************************************************************************************************************************************//**

    Returns the device class codes for a USB device stack.

    @param[in]  device       A pointer to the target device stack.

    @return     A pointer to the device class codes for the specified device stack upon success; NULL on any error.
    @module     usbd

*******************************************************************************************************************************************/
extern const USBCLASSCODE* USBD_GetDeviceClass(USBDDEVICE* device);

/***************************************************************************************************************************************//**

    Assigns the device class code values for a USB device stack.

    @param[in]  device      A pointer to the target device stack.
    @param[in]  bClass      The new class code value for the device.
    @param[in]  bSubClass   The new subclass code value for the device.
    @param[in]  bProtocol   The new protocol code value for the device.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The class code values have been updated.
     ERR_NULLREFERENCE      | The argument 'device' was found to be NULL.

    @module     usbd

*******************************************************************************************************************************************/
extern STATUS USBD_SetDeviceClass(USBDDEVICE* device, BYTE bClass, BYTE bSubClass, BYTE bProtocol);

/***************************************************************************************************************************************//**

    Returns the manufacturer name for a USB device.

    @param[in]  device       A pointer to the target device stack.

    @return     A pointer to the manufacturer name for the specified device upon success; NULL on any error.
    @module     usbd

*******************************************************************************************************************************************/
extern const CHAR* USBD_GetManufacturer(USBDDEVICE* device);

/***************************************************************************************************************************************//**

    Returns the product name for a USB device.

    @param[in]  device       A pointer to the target device.

    @return     A pointer to the product name for the specified device upon success; NULL on any error.
    @module     usbd

*******************************************************************************************************************************************/
extern const CHAR* USBD_GetProductName(USBDDEVICE* device);

/***************************************************************************************************************************************//**

    Returns the serial number for a USB device.

    @param[in]  device       A pointer to the target device.

    @return     A pointer to the serial number for the specified device upon success; NULL on any error.
    @module     usbd

*******************************************************************************************************************************************/
extern const CHAR* USBD_GetSerialNumber(USBDDEVICE* device);

/***************************************************************************************************************************************//**

    Assigns the device name strings for a USB device stack.

    @param[in]  device          A pointer to the target device stack.
    @param[in]  manufacturer    A pointer to a new manufacturer name for the device.
    @param[in]  productName     A pointer to a new product name for the device.
    @param[in]  serialNumber    A pointer to a new serial number for the device.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The device name strings have been updated.
     ERR_NULLREFERENCE      | The argument 'device' was found to be NULL.

    @module     usbd

*******************************************************************************************************************************************/
extern STATUS USBD_SetDeviceName(USBDDEVICE* device, const CHAR* manufacturer, const CHAR* productName, const CHAR* serialNumber);

#if (CFG_USBDENDPTBUFFERS)
/***************************************************************************************************************************************//**

    Assigns buffers to the control endpoints for a device stack.

    @param[in]  device          A pointer to the device stack to receive the buffers.
    @param[in]  rxbuf           A pointer to the buffer memory for the control receive (host OUT) endpoint.
    @param[in]  rxbufsize       The size, in bytes, of the receive buffer memory.
    @param[in]  txbuf           A pointer to the buffer memory for the control transmit (host IN) endpoint.
    @param[in]  txbufsize       The size, in bytes, of the transmit buffer memory.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The provided buffers have been assigned to the device stack.
     ERR_NULLREFERENCE      | The argument 'device' was found to be NULL.

    @module     usbd

*******************************************************************************************************************************************/
extern STATUS USBD_SetCtrlBuffers(USBDDEVICE* device, void* rxbuf, UINT32 rxbufsize, void* txbuf, UINT32 txbufsize);
#endif /* CFG_USBDENDPTBUFFERS */


/*******************************************************************************************************************************************
    USB DEVICE CONFIGURATION FUNCTIONS
*******************************************************************************************************************************************/
/***************************************************************************************************************************************//**

    Creates and initializes a configuration for a USB device stack.

    @param[in]  device      A pointer to the USB device stack instance to receive the configuration.
    @param[in]  cfg         A pointer to a caller allocated configuration to be initialized.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The configuration has been initialized and added to the given device stack.
     ERR_NULLREFERENCE      | The argument 'device' or 'cfg' was found to be NULL.

    @module     usbd

*******************************************************************************************************************************************/
extern STATUS USBD_CreateConfiguration(USBDDEVICE* device, USBDCFG* cfg);

/***************************************************************************************************************************************//**

    Destroys and removes a configuration from a USB device stack.

    @param[in]  cfg         A pointer to the configuration to be destroyed.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The configuration was destroyed and removed from its device stack.
     ERR_NULLREFERENCE      | The argument 'cfg' was found to be NULL.

    @module     usbd

*******************************************************************************************************************************************/
extern STATUS USBD_DestroyConfiguration(USBDCFG* cfg);

/***************************************************************************************************************************************//**

    Returns the settings for a configuration.

    @param[in]  cfg         A pointer to the configuration that contains the settings to be returned.

    @return     A pointer to the settings for the specified configuration upon success; otherwise NULL.
    @module     usbd

*******************************************************************************************************************************************/
extern const USBDCFGSETTINGS* USBD_GetConfigurationSettings(USBDCFG* cfg);

/***************************************************************************************************************************************//**

    Assigns new settings to a USB configuration.

    @param[in]  cfg         A pointer to the configuration to receive the settings.
    @param[in]  settings    A pointer to the new settings to be applied.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The new settings have been applied to the configuration.
     ERR_NULLREFERENCE      | The argument 'cfg' or 'settings' was found to be NULL.

    @module     usbd

*******************************************************************************************************************************************/
extern STATUS USBD_SetConfigurationSettings(USBDCFG* cfg, const USBDCFGSETTINGS* settings);

/***************************************************************************************************************************************//**

    Returns a pointer to the default configuration for a USB device stack.

    @param[in]  device      A pointer to the target USB device stack.

    @return     A pointer to the default configuration for the given USB device stack instance.
    @module     usbd

*******************************************************************************************************************************************/
extern USBDCFG* USBD_DefaultConfiguration(USBDDEVICE* device);

/***************************************************************************************************************************************//**

    Returns the configuration with the specified number from a USB device stack.

    @param[in]  device      A pointer to the USB device stack that contains the configuration to be returned.
    @param[in]  number      The number of the configuration to be returned;

    @return     A pointer to the configuration with the specified number if found; otherwise NULL.
    @module     usbd

*******************************************************************************************************************************************/
extern USBDCFG* USBD_GetConfiguration(USBDDEVICE* device, BYTE number);

/***************************************************************************************************************************************//**

    Returns the configuration at the specified index from a USB device stack.

    @param[in]  device      A pointer to the USB device stack that contains the configuration to be returned.
    @param[in]  idx         The zero-based index of the configuration to be returned;

    @return     A pointer to the configuration at the specified index if found; otherwise NULL.
    @module     usbd

*******************************************************************************************************************************************/
extern USBDCFG* USBD_GetConfigurationByIndex(USBDDEVICE* device, BYTE idx);

/***************************************************************************************************************************************//**

    Returns the currently active configuration for a USB device stack.

    @param[in]  device      A pointer to the USB device stack that contains the configuration to be returned.

    @return     A pointer to the current configuration if one exists; otherwise NULL.
    @module     usbd

*******************************************************************************************************************************************/
extern USBDCFG* USBD_GetActiveConfiguration(USBDDEVICE* device);

/***************************************************************************************************************************************//**

    Selects the current configuration within a USB device stack.

    @param[in]  device      A pointer to the USB device stack that contains the configuration to be selected.
    @param[in]  number      The number of the configuration to be selected.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The specified configuration has been selected.
     ERR_NULLREFERENCE      | The argument 'device' was found to be NULL.
     ERR_NOTFOUND           | No configuration was found with the specified number.

    @module     usbd

*******************************************************************************************************************************************/
extern STATUS USBD_SelectConfiguration(USBDDEVICE* device, BYTE number);


/*******************************************************************************************************************************************
    USB DEVICE INTERFACE FUNCTIONS
*******************************************************************************************************************************************/
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
extern STATUS USBD_CreateInterface(USBDDEVICE* device, USBDINTERFACE* intf, BYTE bClass, BYTE bSubClass, BYTE bProtocol);

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
extern STATUS USBD_CreateAssociatedInterface(USBDDEVICE* device, USBDINTERFACE* other, USBDINTERFACE* intf, BYTE bClass, BYTE bSubClass, BYTE bProtocol);

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
extern STATUS USBD_CreateAlternateInterface(USBDDEVICE* device, USBDINTERFACE* alt, USBDINTERFACE* intf, BYTE bClass, BYTE bSubClass, BYTE bProtocol, BYTE altNumber);

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
extern STATUS USBD_DestroyInterface(USBDINTERFACE* intf);

/***************************************************************************************************************************************//**

    Searches for and returns a device interface with the specified number.

    @param[in]  cfg         A pointer to the configuration that contains the interface to be returned.
    @param[in]  number      The number of the interface to be returned.

    @return     A pointer to the interface with the specified number if found; otherwise NULL.
    @module     usbd

*******************************************************************************************************************************************/
extern USBDINTERFACE* USBD_GetInterface(USBDCFG* cfg, BYTE number);

/***************************************************************************************************************************************//**

    Returns the device interface at the specified index.

    @param[in]  cfg         A pointer to the configuration that contains the interface to be returned.
    @param[in]  idx         The index for the interface to be returned.

    @return     A pointer to the interface with the specified number if found; otherwise NULL.
    @module     usbd

*******************************************************************************************************************************************/
extern USBDINTERFACE* USBD_GetInterfaceByIndex(USBDCFG* cfg, BYTE idx);

/***************************************************************************************************************************************//**

    Returns the class codes for a device interface.

    @param[in]  intf        A pointer to the interface that contains the codes to be returned.

    @return     A pointer to the class codes for the specified interface upon success; otherwise NULL.
    @module     usbd

*******************************************************************************************************************************************/
extern const USBCLASSCODE* USBD_GetInterfaceClass(USBDINTERFACE* intf);

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
extern STATUS USBD_SetInterfaceName(USBDINTERFACE* intf, const CHAR* name);

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
extern STATUS USBD_GetInterfaceDescriptor(USBDINTERFACE* intf, USBINTERFACEDESCRIPTOR* des);

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
extern STATUS USBD_GetAssociationDescriptor(USBDINTERFACE* intf, USBINTERFACEASSOCIATIONDESCRIPTOR* des);


/*******************************************************************************************************************************************
    USB DEVICE ENDPOINT FUNCTIONS
*******************************************************************************************************************************************/
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
extern STATUS USBD_CreateEndpoint(USBDINTERFACE* intf, USBDENDPOINT* endpt, USBTRANSFERTYPE type, BYTE addr, UINT16 pktszfs, UINT16 pktszhs, BYTE interval, UINT32 opt);

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
extern STATUS USBD_DestroyEndpoint(USBDENDPOINT* endpt);

/***************************************************************************************************************************************//**

    Finds and returns an endpoint from within a device that has the specified address.

    @param[in]  device      A pointer to the device that contains the endpoint to be returned.
    @param[in]  addr        The address of the endpoint to be returned.

    @return     A pointer to the endpoint upon success; otherwise NULL on any error.
    @module     usbd

*******************************************************************************************************************************************/
extern USBDENDPOINT* USBD_GetEndpoint(USBDDEVICE* device, BYTE addr);

/***************************************************************************************************************************************//**

    Gets the descriptor for an endpoint.

    @param[in]  endpt       A pointer to the target endpoint.
    @param[in]  des         A pointer to a caller allocated endpoint descriptor to be initialized from the specified endpoint.
    @param[in]  speed       The operating speed for which the descriptor should describe.

    @return     A pointer to the endpoint upon success; otherwise NULL on any error.
    @module     usbd

*******************************************************************************************************************************************/
extern STATUS USBD_GetEndpointDescriptor(USBDENDPOINT* endpt, USBENDPOINTDESCRIPTOR* des, USBSPEED speed);

/***************************************************************************************************************************************//**

    Stalls a USB device endpoint.

    @param[in]  endpt       A pointer to the endpoint to be stalled.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The endpoint was stalled.
     ERR_NULLREFERENCE      | The argument 'endpt' was found to be NULL.

    @module     usbd

*******************************************************************************************************************************************/
extern STATUS USBD_StallEndpoint(USBDENDPOINT* endpt);

/***************************************************************************************************************************************//**

    Unstalls a USB device endpoint.

    @param[in]  endpt       A pointer to the endpoint to be unstalled.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The endpoint was unstalled.
     ERR_NULLREFERENCE      | The argument 'endpt' was found to be NULL.

   @module      USBD

*******************************************************************************************************************************************/
extern STATUS USBD_UnstallEndpoint(USBDENDPOINT* endpt);

/***************************************************************************************************************************************//**

    Returns and indication of whether an endpoint is currently stalled.

    @param[in]  endpt       A pointer to the target endpoint.

    @return     TRUE if the endpoint is stalled; otherwise FALSE.
    @module     usbd

*******************************************************************************************************************************************/
extern BOOLEAN USBD_EndpointStalled(USBDENDPOINT* endpt);

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
extern STATUS USBD_SetEndpointBuffer(USBDENDPOINT* endpt, void* buffer, UINT32 bufsize);
#endif

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

    @module     usbd

*******************************************************************************************************************************************/
extern STATUS USBD_Read(USBDENDPOINT* endpt, void* buf, UINT32 nbytes, UINT32* nread, UINT32 timeout);

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
    @module     usbd

*******************************************************************************************************************************************/
extern STATUS USBD_Write(USBDENDPOINT* endpt, const void* data, UINT32 nbytes, UINT32* nwritten, UINT32 timeout);

/*******************************************************************************************************************************************
    USB DEVICE DESCRIPTOR FUNCTIONS
*******************************************************************************************************************************************/
/***************************************************************************************************************************************//**

    Returns the device descriptor for a USB device stack.

    @param[in]  device      A pointer to the target USB device stack instance.
    @param[in]  des         A pointer to a caller allocated descriptor to be returned.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The device descriptor was returned.
     ERR_NULLREFERENCE      | The argument 'device' or 'des' was found to be NULL.

    @module     usbd

*******************************************************************************************************************************************/
extern STATUS USBD_GetDeviceDescriptor(USBDDEVICE* device, USBDEVICEDESCRIPTOR* des);

/***************************************************************************************************************************************//**

    Returns the configuration descriptor for a USB device stack.

    @param[in]  cfg         A pointer to the target configuration.
    @param[out] buf         A pointer to a caller allocated buffer to receive the configuration descriptor.
    @param[in]  bufsize     The size, in bytes, of the supplied buffer.
    @param[in]  speed       The operating speed for which the descriptor should describe.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The configuration descriptor was returned.
     ERR_NULLREFERENCE      | The argument 'cfg' or 'buf' was found to be NULL.

    @module     usbd

*******************************************************************************************************************************************/
extern STATUS USBD_GetConfigurationDescriptor(USBDCFG* cfg, void* buf, UINT32 bufsize, USBSPEED speed);

/***************************************************************************************************************************************//**

    Returns the default language descriptor.

    @param[out] des         A pointer a caller allocated descriptor to receive the language descriptor.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The language descriptor was returned.
     ERR_NULLREFERENCE      | The argument 'des' was found to be NULL.

    @module     usbd

*******************************************************************************************************************************************/
extern STATUS USBD_GetLanguageDescriptor(USBSTRINGDESCRIPTOR* des);

/***************************************************************************************************************************************//**

    Returns the descriptor for the string at a specified index within a USB device stack.

    @param[in]  stack       A pointer to the USB device stack instance that contains the string.
    @param[in]  idx         The index of the string descriptor to be returned.
    @param[out] des         A pointer to a caller allocated string descriptor.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The string descriptor has been returned.
     ERR_NOTFOUND           | There was no string found for the specified index.
     ERR_OUTOFRANGE         | The specified buffer was not large enough to return the descriptor.

    @module     usbd

*******************************************************************************************************************************************/
extern STATUS USBD_GetStringDescriptor(USBDDEVICE* device, BYTE idx, void* buf, UINT32 bufsize);

#if (USBD_HIGHSPEEDCAPABLE)
/***************************************************************************************************************************************//**

    Returns the device qualifier descriptor for a USB device stack.

    @param[in]  device      A pointer to the target USB device stack instance.
    @param[in]  des         A pointer to a caller allocated descriptor to be returned.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The device qualifier descriptor was returned.
     ERR_NULLREFERENCE      | The argument 'device' or 'des' was found to be NULL.

    @module     usbd

*******************************************************************************************************************************************/
extern STATUS USBD_GetDeviceQualifierDescriptor(USBDDEVICE* device, USBDEVICEQUALIFIERDESCRIPTOR* des);

/***************************************************************************************************************************************//**

    Returns the other speed descriptor for a USB device stack.

    @param[in]  cfg         A pointer to the target configuration.
    @param[out] buf         A pointer to a caller allocated buffer to receive the other speed descriptor.
    @param[in]  bufsize     The size, in bytes, of the supplied buffer.
    @param[in]  speed       The operating speed for which the descriptor should describe.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The configuration descriptor was returned.
     ERR_NULLREFERENCE      | The argument 'cfg' or 'buf' was found to be NULL.

    @module     usbd

*******************************************************************************************************************************************/  
extern STATUS USBD_GetOtherSpeedDescriptor(USBDCFG* cfg, void* buf, UINT32 bufsize, USBSPEED speed);
#endif /* USBD_HIGHSPEEDCAPABLE */


/*******************************************************************************************************************************************
    MICROSOFT OS DESCRIPTOR FUNCTIONS
*******************************************************************************************************************************************/
/***************************************************************************************************************************************//**

    Enables/disables built-in support for Microsoft OS descriptors for a device stack.

    @param[in]  device      A pointer to the target device stack instance.
    @param[in]  enabled     Use TRUE to enable, or FALSE to disable support for Microsoft OS descriptors.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The option has been updated.
     ERR_NULLREFERENCE      | The argument 'device' was found to be NULL.

    @module     usbd

*******************************************************************************************************************************************/
extern STATUS USBD_SetMicrosoftDescriptorSupport(USBDDEVICE* usbd, BOOLEAN enabled);

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

    @module     usbd

*******************************************************************************************************************************************/
extern STATUS USBD_SetMicrosoftDescriptorEventHandler(USBDDEVICE* usbd, USBDREQUESTCALLBACK callback);

#endif /* USBD_H__ */
