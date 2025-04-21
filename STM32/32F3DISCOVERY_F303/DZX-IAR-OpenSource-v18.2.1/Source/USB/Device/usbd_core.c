/*******************************************************************************************************************************************

    DZX | USB DEVICE | CORE                                                                                               VERSION 18.2.1
    ------------------------------------------------------------------------------------------------------------------------------------

    This provides the core functionality for the USB device stack.

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
#include <string.h>

/*******************************************************************************************************************************************
    PRIVATE VARIABLES
*******************************************************************************************************************************************/
USBDDEVICE* USBD_Devices[CFG_USBDEVICEPORTS];           /* An array of created USB devices */

/*******************************************************************************************************************************************
    PRIVATE FUNCTIONS
*******************************************************************************************************************************************/
static void USBD_Request(USBDDEVICE* device, const USBREQUEST* request);
static STATUS USBD_DeviceRequest(USBDDEVICE* device, const USBREQUEST* request);
static STATUS USBD_DeviceDescriptorRequest(USBDDEVICE* device, const USBREQUEST* request);
static STATUS USBD_CfgDescriptorRequest(USBDDEVICE* device, const USBREQUEST* request);
static STATUS USBD_DeviceQualifierRequest(USBDDEVICE* device, const USBREQUEST* request);
static STATUS USBD_OtherSpeedRequest(USBDDEVICE* device, const USBREQUEST* request);
static STATUS USBD_StringRequest(USBDDEVICE* device, const USBREQUEST* request);
static void USBD_Thread(void* arg);

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
STATUS USBD_Create(USBDDEVICE* device, UINT32 port, UINT16 vendorID, UINT16 productID)
{
    STATUS status;
    
    
#if (CFG_NULLCHECKING)
    if (device == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif
    
    if (port >= CFG_USBDEVICEPORTS) {
        return ERR_NOTSUPPORTED;
    }

    device->id.idVendor = vendorID;                                 /* Assign the initial device IDs */
    device->id.idProduct = productID;
    
    device->classCode.bClass = USBDEVCLASSINTFDEFINED;              /* Initialize the device class codes as interface-defined */
    device->classCode.bSubClass = 0;
    device->classCode.bProtocol = 0;
    
    device->rls = 0;

    device->status.VALUE = 0;
    device->status.BITS.SELFPOWERED = 0;
    device->status.BITS.REMOTEWAKEUP = 0;

    LIST_Init(&device->cfgs);                                       /* Initialize the list of configurations for the device */
    
    status = USBD_CreateConfiguration(device, &device->defcfg);     /* Create the default configuration for the device */
    if (status != SUCCESS) {
        return status;
    }

    device->rx0.addr = 0x00;                                        /* Create device receive (host OUT) control endpoint */
    device->rx0.interval = 1;
    device->rx0.type = USBTRANSFERCONTROL;
    device->rx0.pktszfs = 0x40;
    device->rx0.pktszhs = 0x40;
    device->rx0.device = device;
    device->rx0.opt = OPT_SHORTPKT;
    device->rx0.zlp = FALSE;
    
#if (CFG_USBDENDPTBUFFERS)
    device->rx0.buffer = NULL;
    device->rx0.bufsize = 0;
#endif
    
    device->tx0.addr = 0x80;                                        /* Create device transmit (host IN) control endpoint */
    device->tx0.interval = 1;            
    device->tx0.type = USBTRANSFERCONTROL;
    device->tx0.pktszfs = 0x40;
    device->tx0.pktszhs = 0x40;
    device->tx0.device = device;
    device->tx0.opt = OPT_SHORTPKT;
    device->tx0.zlp = FALSE;
    
#if (CFG_USBDENDPTBUFFERS)
    device->tx0.buffer = NULL;
    device->tx0.bufsize = 0;
#endif

    LIST_Init(&device->strs);                                       /* Initialize the list of strings for the device */
    
    USBD_InitString(&device->manufstr);                             /* Initialize each of the name strings */
    USBD_InitString(&device->prodstr);
    USBD_InitString(&device->serstr);

    device->port = port;                                            /* Assign the port number */
    device->msft = FALSE;
    device->open = FALSE;
    
    status = USBD_InitController(device);
    if (status != SUCCESS) {
        return status;
    }
    
    USBD_Devices[device->port] = device;                            /* Keep a reference of this initialized device */
    return SUCCESS;
}

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
STATUS USBD_Destroy(USBDDEVICE* device)
{
    STATUS status;
    NODE* node;
    
    
#if (CFG_NULLCHECKING)
    if (device == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif
    
    status = USBD_Close(device);                                        /* Close any existing connections */
    if (status != SUCCESS) {
        return status;
    }
    
    node = device->cfgs.first;                                          /* Begin with the first configuration */
        
    while (node) {
        status = USBD_DestroyConfiguration((USBDCFG*)node->value);      /* Destroy and remove the configuration */
        if (status != SUCCESS) {
            return status;                                              /* Bubble up any errors */
        }
        
        node = device->cfgs.first;                                      /* Go to the next configuration */
    }

    LIST_Clear(&device->strs);
    
    USBD_Devices[device->port] = NULL;                                  /* Release the reference to the device */
    return SUCCESS;
}

/***************************************************************************************************************************************//**

    Returns the identifier values for a USB device stack instance.

    @param[in]  device       A pointer to the target device stack.

    @return     A pointer to the device identifiers for the specified device stack upon success; NULL on any error.
    @module     usbd

*******************************************************************************************************************************************/
const USBDEVICEID* USBD_GetDeviceID(USBDDEVICE* device)
{
#if (CFG_NULLCHECKING)
    if (device == NULL) {
        return NULL;
    }
#endif
    
    return &device->id;
}

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
STATUS USBD_SetDeviceID(USBDDEVICE* device, UINT16 vendorID, UINT16 productID)
{
#if (CFG_NULLCHECKING)
    if (device == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif    
    
    device->id.idVendor = vendorID;
    device->id.idProduct = productID;
    
    return SUCCESS;
}

/***************************************************************************************************************************************//**

    Returns the device class codes for a USB device stack.

    @param[in]  device       A pointer to the target device stack.

    @return     A pointer to the device class codes for the specified device stack upon success; NULL on any error.
    @module     usbd

*******************************************************************************************************************************************/
const USBCLASSCODE* USBD_GetDeviceClass(USBDDEVICE* device)
{
#if (CFG_NULLCHECKING)
    if (device == NULL) {
        return NULL;
    }
#endif
    
    return &device->classCode;
}

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
STATUS USBD_SetDeviceClass(USBDDEVICE* device, BYTE bClass, BYTE bSubClass, BYTE bProtocol)
{
#if (CFG_NULLCHECKING)
    if (device == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif    

    device->classCode.bClass = bClass;
    device->classCode.bSubClass = bSubClass;
    device->classCode.bProtocol = bProtocol;
    
    return SUCCESS;
}

/***************************************************************************************************************************************//**

    Returns the manufacturer name for a USB device.

    @param[in]  device       A pointer to the target device stack.

    @return     A pointer to the manufacturer name for the specified device upon success; NULL on any error.
    @module     usbd

*******************************************************************************************************************************************/
const CHAR* USBD_GetManufacturer(USBDDEVICE* device)
{
#if (CFG_NULLCHECKING)
    if (device == NULL) {
        return NULL;
    }
#endif
    
    return device->manufstr.cstr;
}

/***************************************************************************************************************************************//**

    Returns the product name for a USB device.

    @param[in]  device       A pointer to the target device.

    @return     A pointer to the product name for the specified device upon success; NULL on any error.
    @module     usbd

*******************************************************************************************************************************************/
const CHAR* USBD_GetProductName(USBDDEVICE* device)
{
#if (CFG_NULLCHECKING)
    if (device == NULL) {
        return NULL;
    }
#endif
    
    return device->prodstr.cstr;   
}

/***************************************************************************************************************************************//**

    Returns the serial number for a USB device.

    @param[in]  device       A pointer to the target device.

    @return     A pointer to the serial number for the specified device upon success; NULL on any error.
    @module     usbd

*******************************************************************************************************************************************/
const CHAR* USBD_GetSerialNumber(USBDDEVICE* device)
{
#if (CFG_NULLCHECKING)
    if (device == NULL) {
        return NULL;
    }
#endif
    
    return device->serstr.cstr;  
}

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
STATUS USBD_SetDeviceName(USBDDEVICE* device, const CHAR* manufacturer, const CHAR* productName, const CHAR* serialNumber)
{
    STATUS status;
    
    
#if (CFG_NULLCHECKING)
    if (device == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif    

    status = USBD_AssignString(device, &device->manufstr, manufacturer);      /* Assign the manufacturer name */
    if (status != SUCCESS) {
        return status;
    }
    
    status = USBD_AssignString(device, &device->prodstr, productName);        /* Assign the product name */
    if (status != SUCCESS) {
        return status;
    }
    
    status = USBD_AssignString(device, &device->serstr, serialNumber);        /* Assign the serial number */
    if (status != SUCCESS) {
        return status;
    }
        
    return SUCCESS;
}

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
STATUS USBD_SetCtrlBuffers(USBDDEVICE* device, void* rxbuf, UINT32 rxbufsize, void* txbuf, UINT32 txbufsize)
{
    STATUS status;
    
    
#if (CFG_NULLCHECKING)
    if (device == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif
    
    status = USBD_SetEndpointBuffer(&device->rx0, rxbuf, rxbufsize);
    if (status != SUCCESS) {
        return status;
    }
    
    status = USBD_SetEndpointBuffer(&device->tx0, txbuf, txbufsize);
    if (status != SUCCESS) {
        return status;
    }
    
    return SUCCESS;
}
#endif /* CFG_USBDENDPTBUFFERS */

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
STATUS USBD_Open(USBDDEVICE* device)
{
    STATUS status;
    

#if (CFG_NULLCHECKING)
    if (device == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif
    
    if (device->open) {                                          /* Is the device already open on an existing port? */
        status = USBD_Close(device);                             /* Yes, close it before re-opening it */
    }
    
    status = THREAD_Create(&device->thread,                      /* Create a thread for processing USB device requests */
                           "USBD Stack",
                           device->stk,                          /* Pointer to device memory for the thread */
                           CFG_USBDSTACKSIZE,                   /* Size in bytes of the device memory */
                           CFG_USBDPRIORITY);                   /* The priority for the USB thread */
    
    if (status != SUCCESS) { 
        return status;                                          /* Bubble up any error */
    }
    
    status = THREAD_Start(&device->thread,                       /* Start execution of the thread */
                          USBD_Thread,                          /* The entry function for the thread */
                          device);                               /* An argument for the thread (the device instance) */
  
    if (status != SUCCESS) {
        return status;                                          /* Bubble up any error */
    }
    
    status = USBD_OpenController(device);                       /* Open the port within the device controller driver */
    if (status != SUCCESS) {
        return status;                                          /* Bubble up any error */
    }
    
    device->open = TRUE;                                        /* Mark the device as open for communications */
    return SUCCESS;
}

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
STATUS USBD_Close(USBDDEVICE* device)
{
    STATUS status;
    
    
#if (CFG_NULLCHECKING)
    if (device == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif
    
    device->open = FALSE;
    
    THREAD_Abort(&device->thread);                              /* Abort the device thread */
    THREAD_Join(&device->thread, 100);                          /* Wait for the thread to terminate on it's own */
    
    THREAD_Destroy(&device->thread);                            /* Destroy and release the thread */
    
    status = USBD_CloseController(device);                      /* Close the port within the device controller driver */
    if (status != SUCCESS) {                                    /* Did an error occur? */
        return status;                                          /* Bubble up the error */
    }
    
    return SUCCESS;
}

/***************************************************************************************************************************************//**

    Gets an indication of whether a USB device stack is open for communications.

    @param[in]  device       A pointer to the target device stack.

    @return     TRUE if the device has been opened for communications; otherwise FALSE.
    @module     usbd

*******************************************************************************************************************************************/
BOOLEAN USBD_IsOpen(USBDDEVICE* device)
{
#if (CFG_NULLCHECKING)
    if (device == NULL) {
        return FALSE;
    }
#endif
    
    return device->open;
}

/***************************************************************************************************************************************//**

    Gets an indication of whether a USB device stack is currently connected to a host.

    @param[in]  device       A pointer to the target device stack.

    @return     TRUE if the device stack has been configured by a host; otherwise FALSE.
    @module     usbd

*******************************************************************************************************************************************/
BOOLEAN USBD_IsConnected(USBDDEVICE* device)
{
#if (CFG_NULLCHECKING)
    if (device == NULL) {
        return FALSE;
    }
#endif
    
    if (device->suspended) {
        return FALSE;
    }
    
    if (device->curcfg == NULL) {
        return FALSE;
    }
    
    return TRUE;
}

/***************************************************************************************************************************************//**

    Gets an indication of whether a USB device stack has been suspended by the host.

    @param[in]  device       A pointer to the target device stack.

    @return     TRUE if the device stack has been suspended by the host; otherwise FALSE.
    @module     usbd

*******************************************************************************************************************************************/
BOOLEAN USBD_IsSuspended(USBDDEVICE* device)
{
#if (CFG_NULLCHECKING)
    if (device == NULL) {
        return FALSE;
    }
#endif
    
    return device->suspended;   
}

/***************************************************************************************************************************************//**

    The thread process function for a USB device instance.

    @param[in]  arg         A pointer to the USB device instance.

    @return     None.
    @module     usbd

*******************************************************************************************************************************************/
static void USBD_Thread(void* arg)
{
    UINT32 num;
    USBDDEVICE* device;
    static UINT32 emptyreads = 0;
    
    
    device = (USBDDEVICE*)arg;                                  /* Get the USB device to process */
    
    while (!THREAD_Aborted()) {                                 /* Process until the thread is aborted */
        
        USBD_Read(&device->rx0,                                 /* Read the next request from the connected host */
                  &device->req,                                 /* Pointer to the buffer to receive the request */
                  sizeof(USBREQUEST),                           /* The maximum amount to be read */
                  &num,                                         /* A pointer to a variable to receive how many bytes have been returned */ 
                  INFINITE);                                    /* Wait indefinitely */
        
        
        
        if (num > 0) {                                          /* Were any data bytes received? */
            USBD_Request(device, &device->req);                 /* Process the request */   
            
            
        } else {
            ++emptyreads;
        }
    }
}

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
STATUS USBD_CreateConfiguration(USBDDEVICE* device, USBDCFG* cfg)
{
#if (CFG_NULLCHECKING)
    if (device == NULL) {
        return ERR_NULLREFERENCE;
    }
    
    if (cfg == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif
    
    cfg->device = device;
    cfg->number = device->cfgs.count + 1;
    
    cfg->settings.selfPowered = CFG_USBDCFGSELFPOWERED;         /* Assign default settings from configuration file */
    cfg->settings.remoteWakeup = CFG_USBDCFGREMOTEWAKEUP;
    cfg->settings.maxPower = CFG_USBDCFGMAXPOWER;

    LIST_Init(&cfg->intfs);
    LIST_AddLast(&device->cfgs, &cfg->node, cfg);
    
    device->cfg = cfg;                                          /* Select the recently added configuration as active */
    return SUCCESS;
}

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
STATUS USBD_DestroyConfiguration(USBDCFG* cfg)
{
    STATUS status;
    NODE* node;
    
    
#if (CFG_NULLCHECKING)
    if (cfg == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif

    if (cfg->device == NULL) {                                           /* Does the configuration belong within a device? */
        return SUCCESS;                                                 /* No, nothing left to do */
    }
    
        
    node = cfg->intfs.first;                                            /* Go through each interface within the configuration */
    while (node) {
        status = USBD_DestroyInterface((USBDINTERFACE*)node->value);    /* Destroy and remove the interface */
        if (status != SUCCESS) {
            return status;                                              /* Bubble up any errors */
        }
        
        node = cfg->intfs.first;                                        /* Go to the next interface */
    }
    
    LIST_Remove(&cfg->device->cfgs, &cfg->node);                         /* Remove the configuration from the device */
    cfg->device = NULL;
    
    return SUCCESS;
}

/***************************************************************************************************************************************//**

    Returns the settings for a configuration.

    @param[in]  cfg         A pointer to the configuration that contains the settings to be returned.

    @return     A pointer to the settings for the specified configuration upon success; otherwise NULL.
    @module     usbd

*******************************************************************************************************************************************/
const USBDCFGSETTINGS* USBD_GetConfigurationSettings(USBDCFG* cfg)
{
#if (CFG_NULLCHECKING)
    if (cfg == NULL) {
        return NULL;
    }
#endif
    
    return &cfg->settings;
}
                           
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
STATUS USBD_SetConfigurationSettings(USBDCFG* cfg, const USBDCFGSETTINGS* settings)
{
#if (CFG_NULLCHECKING)
    if (cfg == NULL) {
        return ERR_NULLREFERENCE;
    }
    
    if (settings == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif
    
    cfg->settings.selfPowered = settings->selfPowered;
    cfg->settings.remoteWakeup = settings->remoteWakeup;
    cfg->settings.maxPower = settings->maxPower;
    
    return SUCCESS;
}

/***************************************************************************************************************************************//**

    Returns a pointer to the default configuration for a USB device stack.

    @param[in]  device      A pointer to the target USB device stack.

    @return     A pointer to the default configuration for the given USB device stack instance.
    @module     usbd

*******************************************************************************************************************************************/
USBDCFG* USBD_DefaultConfiguration(USBDDEVICE* device)
{
#if (CFG_NULLCHECKING)
    if (device == NULL) {
        return NULL;
    }
#endif
    return &device->defcfg;
}

/***************************************************************************************************************************************//**

    Returns the configuration with the specified number from a USB device stack.

    @param[in]  device      A pointer to the USB device stack that contains the configuration to be returned.
    @param[in]  number      The number of the configuration to be returned;

    @return     A pointer to the configuration with the specified number if found; otherwise NULL.
    @module     usbd

*******************************************************************************************************************************************/
USBDCFG* USBD_GetConfiguration(USBDDEVICE* device, BYTE number)
{
    USBDCFG* cfg;
    NODE* node;


#if (CFG_NULLCHECKING)
    if (device == NULL) {
        return NULL;
    }
#endif

    LIST_Foreach(node, &device->cfgs) {
        cfg = node->value;
        if (cfg->number == number) {
            return cfg;
        }
    }

    return NULL;
}

/***************************************************************************************************************************************//**

    Returns the configuration at the specified index from a USB device stack.

    @param[in]  device      A pointer to the USB device stack that contains the configuration to be returned.
    @param[in]  idx         The zero-based index of the configuration to be returned;

    @return     A pointer to the configuration at the specified index if found; otherwise NULL.
    @module     usbd

*******************************************************************************************************************************************/
USBDCFG* USBD_GetConfigurationByIndex(USBDDEVICE* device, BYTE idx)
{
    NODE* node;
    BYTE cnt;
    
    
#if (CFG_NULLCHECKING)
    if (device == NULL) {
        return NULL;
    }
#endif
    
    cnt = 0;
    LIST_Foreach(node, &device->cfgs) {                         /* Walk the list of configurations until at the specified index */
        if (cnt == idx) {
            return (USBDCFG*)node->value;                       /* Return the specified configuration */
        }
    }
    
    return NULL;                                                /* Configuration wasn't found */
}

/***************************************************************************************************************************************//**

    Returns the currently active configuration for a USB device stack.

    @param[in]  device      A pointer to the USB device stack that contains the configuration to be returned.

    @return     A pointer to the current configuration if one exists; otherwise NULL.
    @module     usbd

*******************************************************************************************************************************************/
USBDCFG* USBD_GetActiveConfiguration(USBDDEVICE* device)
{
    return (USBDCFG*)&device->curcfg;
}

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
STATUS USBD_SelectConfiguration(USBDDEVICE* device, BYTE number)
{
    NODE* node;
    USBDCFG* cfg;
    

#if (CFG_NULLCHECKING)
    if (device == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif
    
    LIST_Foreach(node, &device->cfgs) {                         /* Search through all of the configurations within the device */
        cfg = (USBDCFG*)node->value;
        if (cfg->number == number) {                            /* Does the configuration match the requested number? */
            device->cfg = cfg;                                  /* Select the configuration */
            return SUCCESS;
        }
    }
    
    return ERR_NOTFOUND;
}

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
STATUS USBD_GetDeviceDescriptor(USBDDEVICE* device, USBDEVICEDESCRIPTOR* des)
{
#if (CFG_NULLCHECKING)
    if (device == NULL) {
        return ERR_NULLREFERENCE;
    }
    
    if (des == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif
    
    des->bLength            = sizeof(USBDEVICEDESCRIPTOR);
    des->bDescriptorType    = USBDESTYPEDEVICE;
    des->bcdUSB             = 0x0200;
    des->bDeviceClass       = device->classCode.bClass;
    des->bDeviceSubClass    = device->classCode.bSubClass;
    des->bDeviceProtocol    = device->classCode.bProtocol;
    des->bMaxPacketSize     = device->rx0.pktszfs;
    des->idVendor           = device->id.idVendor;
    des->idProduct          = device->id.idProduct;
    des->bcdDevice          = device->rls;
    des->iManufacturer      = device->manufstr.idx;
    des->iProduct           = device->prodstr.idx;
    des->iSerialNumber      = device->serstr.idx;
    des->bNumConfigurations = device->cfgs.count;

    return SUCCESS;
}

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
STATUS USBD_GetDeviceQualifierDescriptor(USBDDEVICE* device, USBDEVICEQUALIFIERDESCRIPTOR* des)
{
#if (CFG_NULLCHECKING)
    if (device == NULL) {
        return ERR_NULLREFERENCE;
    }
    
    if (des == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif
    
    des->bLength            = sizeof(USBDEVICEQUALIFIERDESCRIPTOR);
    des->bDescriptorType    = USBDESTYPEDEVICEQUALIFIER;
    des->bcdUSB             = 0x0200;
    des->bDeviceClass       = device->classCode.bClass;
    des->bDeviceSubClass    = device->classCode.bSubClass;
    des->bDeviceProtocol    = device->classCode.bProtocol;
    des->bMaxPacketSize     = device->rx0.pktszfs;
    des->bNumConfigurations = device->cfgs.count;
    des->reserved           = 0;
    
    return SUCCESS;
}
#endif /* USBD_HIGHSPEEDCAPABLE */

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
STATUS USBD_GetConfigurationDescriptor(USBDCFG* cfg, void* buf, UINT32 bufsize, USBSPEED speed)
{
    UINT32 idx;
    USBDINTERFACE* intf;
    USBDENDPOINT* endpt;
    USBCONFIGURATIONDESCRIPTOR* des;
    NODE* inode;
    NODE* enode;
    
    
#if (CFG_NULLCHECKING)
    if (cfg == NULL) {
        return ERR_NULLREFERENCE;
    }
    
    if (buf == NULL) {
        return ERR_NULLREFERENCE;
    }    
#endif


    idx = 0;
    des = (USBCONFIGURATIONDESCRIPTOR*)buf;

    des->bLength                = sizeof(USBCONFIGURATIONDESCRIPTOR);
    des->bDescriptorType        = USBDESTYPECONFIGURATION;
    des->bNumInterfaces         = cfg->intfs.count;
    des->bConfigurationValue    = cfg->number;
    des->iConfiguration         = 0;
    
    des->bmAttributes = 0x80;
    
    if (cfg->settings.selfPowered) {
        des->bmAttributes |= (1 << 6);
    }
    
    if (cfg->settings.remoteWakeup) {
        des->bmAttributes |= (1 << 5);
    }
    
    des->bMaxPower = (cfg->settings.maxPower >> 1);

    idx += des->bLength;

    LIST_Foreach(inode, &cfg->intfs) {                                      /* Walk through each interface */
        intf = inode->value;
        
        if (intf->associntfs.count > 0) {
            USBD_GetAssociationDescriptor(intf, (USBINTERFACEASSOCIATIONDESCRIPTOR*)&((BYTE*)buf)[idx]);
            idx += ((USBDESCRIPTOR*)&((BYTE*)buf)[idx])->bLength;
        }
        
        USBD_GetInterfaceDescriptor(intf, (USBINTERFACEDESCRIPTOR*)&((BYTE*)buf)[idx]);     /* Get the interface descriptor */
        idx += ((USBDESCRIPTOR*)&((BYTE*)buf)[idx])->bLength;

        if (intf->descb) {                                                  /* Does the interface have a descriptor callback? */
            idx += intf->descb(intf, &((BYTE*)buf)[idx]);                   /* Call the interface descriptor callback */
        }
      
        LIST_Foreach(enode, &intf->endpoints) {                             /* Walk through each endpoint for the interface */
            endpt = enode->value;                                           /* Access the endpoint */
            
            USBD_GetEndpointDescriptor(endpt,                               /* Get the endpoint descriptor */
                                       (USBENDPOINTDESCRIPTOR*)&((BYTE*)buf)[idx],
                                       speed);   
            
            idx += ((USBDESCRIPTOR*)&((BYTE*)buf)[idx])->bLength;
        }
    }

    des->wTotalLength = idx;
    return SUCCESS;
}

#if (USBD_HIGHSPEEDCAPABLE)
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
STATUS USBD_GetOtherSpeedDescriptor(USBDCFG* cfg, void* buf, UINT32 bufsize, USBSPEED speed)
{
    STATUS status;
    
    
#if (CFG_NULLCHECKING)
    if (cfg == NULL) {
        return ERR_NULLREFERENCE;
    }
    
    if (buf == NULL) {
        return ERR_NULLREFERENCE;
    }    
#endif
    
    status = USBD_GetConfigurationDescriptor(cfg, buf, bufsize, speed);
    if (status != SUCCESS) {
        return status;
    }
    
    ((USBDESCRIPTOR*)buf)->bDescriptorType = USBDESTYPEOTHERSPEED;
    return SUCCESS;
}
#endif /* USBD_HIGHSPEEDCAPABLE */

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
STATUS USBD_GetLanguageDescriptor(USBSTRINGDESCRIPTOR* des)
{
#if (CFG_NULLCHECKING)
    if (des == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif
    
    des->bLength = sizeof(USBSTRINGDESCRIPTOR);
    des->bDescriptorType = USBDESTYPESTRING;
    des->wChar[0] = 0x0409;
    
    return SUCCESS;
}

/***************************************************************************************************************************************//**

    Processes a setup request that has been received from a host.

    @param[in]  device      A pointer to the device that has received the request.
    @param[in]  request     A pointer to the request to be processed.

    @return     None.
    @module     usbd

*******************************************************************************************************************************************/
static void USBD_Request(USBDDEVICE* device, const USBREQUEST* request)
{
    STATUS status = SUCCESS;
    
    
    switch (request->bmRequestType.type) {
        case USBSTANDARD:
        case USBCLASS:
            switch (request->bmRequestType.recipient) {                 /* Determine the recipient of the request */
                case USBRECIPIENTDEVICE:
                    status = USBD_DeviceRequest(device, request);
                    break;
                case USBRECIPIENTINTERFACE:
                    status = USBD_InterfaceRequest(device, request);
                    break;
                case USBRECIPIENTENDPOINT:
                    status = USBD_EndpointRequest(device, request);
                    break;
                default:
                    status = ERR_NOTSUPPORTED;
                    break;
            }
            break;
             
#if (CFG_USBDMSFT)
         case USBVENDOR:
            if (device->msft) {
                USBD_MicrosoftRequest(device, request);
            }
            break;
#endif

        default:
            status = ERR_NOTSUPPORTED;
            break;
    }
    
    if (status != SUCCESS) {                                            /* Was the request handled? */
        USBD_StallEndpoint(&device->tx0);                               /* Not handled, stall the endpoint */
    }
}

/***************************************************************************************************************************************//**

    Handles a USB request that has targeted the device.

    @param[in]  device      A pointer to the USB device that has received the request.
    @param[in]  request     A pointer to the request to be handled.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The request has been handled.
     ERR_NOTSUPPORTED       | The request is not supported.

    @module     internal

*******************************************************************************************************************************************/
static STATUS USBD_DeviceRequest(USBDDEVICE* device, const USBREQUEST* request)
{
    switch (request->bRequest) {
        
        case USBGETDESCRIPTOR:                                                          /* Host is requesting general descriptor */
            switch (USB_GETDESTYPE(request)) {                                          /* What type of descriptor? */
                
                case USBDESTYPEDEVICE:
                    return USBD_DeviceDescriptorRequest(device, request);
                    
                case USBDESTYPECONFIGURATION:
                    return USBD_CfgDescriptorRequest(device, request);
                    
                case USBDESTYPEDEVICEQUALIFIER:
                    return USBD_DeviceQualifierRequest(device, request);
                    
                case USBDESTYPEOTHERSPEED:
                    return USBD_OtherSpeedRequest(device, request);
                    
                case USBDESTYPESTRING:
                    return USBD_StringRequest(device, request);
            }
            break;

        case USBGETSTATUS:
            memcpy(device->respbuf, &device->status, sizeof(USBDEVICESTATUS));
            USBD_Write(&device->tx0, 
                       device->respbuf, 
                       MIN(sizeof(USBDEVICESTATUS), request->wLength), 
                       NULL,
                       CFG_USBDWRITETIMEOUT);
            return SUCCESS;
            
        case USBCLEARFEATURE:
            USBD_Write(&device->tx0, NULL, 0, NULL, CFG_USBDWRITETIMEOUT);            /* Transfer an ACK */
            return SUCCESS;
          
        case USBSETFEATURE:
            USBD_Write(&device->tx0, NULL, 0, NULL, CFG_USBDWRITETIMEOUT);            /* Transfer an ACK */
            return SUCCESS;

        case USBSETADDRESS:
            USBD_SetAddress(device, request->wValue);                                 /* Set the new address within the controller */
            USBD_Write(&device->tx0, NULL, 0, NULL, CFG_USBDWRITETIMEOUT);            /* Transfer an ACK */
            return SUCCESS;

        case USBSETCONFIGURATION:
            USBD_SetConfiguration(device, request->wValue);                           /* Apply the specified configuration */
            USBD_Write(&device->tx0, NULL, 0, NULL, CFG_USBDWRITETIMEOUT);            /* Transfer an ACK */
            return SUCCESS;

        case USBGETCONFIGURATION:
            if (device->curcfg) {
                USBD_Write(&device->tx0, 
                           &device->curcfg->number, 
                           sizeof(BYTE), 
                           NULL, 
                           CFG_USBDWRITETIMEOUT);
            } else {
                device->respbuf[0] = 0;
                USBD_Write(&device->tx0, 
                           device->respbuf, 
                           sizeof(BYTE), 
                           NULL, 
                           CFG_USBDWRITETIMEOUT);
            }
            return SUCCESS;
    }
    
    return ERR_NOTSUPPORTED;
}

/***************************************************************************************************************************************//**

    Handles a get device descriptor request for the device.

    @param[in]  device      A pointer to the device that has received the request.
    @param[in]  request     A pointer to the request to be handled.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The request has been handled.
     ERR_NOTSUPPORTED       | The request is not supported.

    @module     internal

*******************************************************************************************************************************************/
static STATUS USBD_DeviceDescriptorRequest(USBDDEVICE* device, const USBREQUEST* request)
{
    USBD_GetDeviceDescriptor(device,                                    /* Get the device descriptor */
                             (USBDEVICEDESCRIPTOR*)device->respbuf);    
    USBD_Write(&device->tx0,                                            /* Send the descriptor to the host */
               device->respbuf, 
               MIN(sizeof(USBDEVICEDESCRIPTOR), request->wLength),
               NULL,
               CFG_USBDWRITETIMEOUT);
    
    return SUCCESS;
}

/***************************************************************************************************************************************//**

    Handles a get configuration descriptor request for the device.

    @param[in]  device      A pointer to the device that has received the request.
    @param[in]  request     A pointer to the request to be handled.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The request has been handled.
     ERR_NOTSUPPORTED       | The request is not supported.

    @module     internal

*******************************************************************************************************************************************/
static STATUS USBD_CfgDescriptorRequest(USBDDEVICE* device, const USBREQUEST* request)
{
    USBDCFG* cfg;
    
    
    cfg = USBD_GetConfigurationByIndex(device, 
                                       USB_GETDESINDEX(request));       /* Find the requested configuration */
    if (cfg == NULL) {
        return ERR_NOTSUPPORTED;                                        /* Didn't find the requested configuration */
    }
    
    USBD_GetConfigurationDescriptor(cfg,                                /* Get the configuration descriptor */
                                    device->respbuf, 
                                    CFG_USBDREQRESBUFSIZE,
                                    USBD_Speed(device));                 
    USBD_Write(&device->tx0,                                            /* Send the descriptor to the host */ 
               device->respbuf, 
               MIN(((USBCONFIGURATIONDESCRIPTOR*)device->respbuf)->wTotalLength, 
                   request->wLength), 
               NULL,
               CFG_USBDWRITETIMEOUT);
    
    return SUCCESS;
}

/***************************************************************************************************************************************//**

    Handles a get device qualifier descriptor request for the device.

    @param[in]  device      A pointer to the device that has received the request.
    @param[in]  request     A pointer to the request to be handled.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The request has been handled.
     ERR_NOTSUPPORTED       | The request is not supported.

    @module     internal

*******************************************************************************************************************************************/
static STATUS USBD_DeviceQualifierRequest(USBDDEVICE* device, const USBREQUEST* request)
{
#if (USBD_HIGHSPEEDCAPABLE)
    USBD_GetDeviceQualifierDescriptor(device, 
                                      (USBDEVICEQUALIFIERDESCRIPTOR*)device->respbuf);
    USBD_Write(&device->tx0,
               device->respbuf, 
               MIN(sizeof(USBDEVICEQUALIFIERDESCRIPTOR), request->wLength),
               NULL,
               CFG_USBDWRITETIMEOUT);
    return SUCCESS;
#else
    return ERR_NOTSUPPORTED;                                                            /* Not supported for full speed only devices */
#endif
}

/***************************************************************************************************************************************//**

    Handles a get other speed descriptor request for the device.

    @param[in]  device      A pointer to the device that has received the request.
    @param[in]  request     A pointer to the request to be handled.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The request has been handled.
     ERR_NOTSUPPORTED       | The request is not supported.

    @module     internal

*******************************************************************************************************************************************/
static STATUS USBD_OtherSpeedRequest(USBDDEVICE* device, const USBREQUEST* request)
{
#if (USBD_HIGHSPEEDCAPABLE)
    USBDCFG* cfg;
    USBSPEED other;

    
    cfg = USBD_GetConfigurationByIndex(device, USB_GETDESINDEX(request));   /* Find the requested configuration */
    if (cfg == NULL) {
        return ERR_NOTSUPPORTED;
    }
    
    other = USBD_Speed(device);                                             /* Get the current speed */
    if (other == USBSPEED_HIGH) {                                           /* Find the speed other than the current */
        other = USBSPEED_FULL;
    }
    
    USBD_GetOtherSpeedDescriptor(cfg,                                       /* Get the other speed descriptor */
                                 device->respbuf, 
                                 CFG_USBDREQRESBUFSIZE,
                                 other);                 
    USBD_Write(&device->tx0,                                                /* Send the descriptor the host */
               device->respbuf, 
               MIN(((USBCONFIGURATIONDESCRIPTOR*)device->respbuf)->wTotalLength, 
                   request->wLength), 
               NULL,
               CFG_USBDWRITETIMEOUT);
    
    return SUCCESS;
#else
    return ERR_NOTSUPPORTED;                                                /* Not supported for full speed only devices */
#endif
}

/***************************************************************************************************************************************//**

    Handles a get string descriptor request for the device.

    @param[in]  device      A pointer to the device that has received the request.
    @param[in]  request     A pointer to the request to be handled.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The request has been handled.
     ERR_NOTSUPPORTED       | The request is not supported.

    @module     internal

*******************************************************************************************************************************************/
static STATUS USBD_StringRequest(USBDDEVICE* device, const USBREQUEST* request)
{
    STATUS status;
    
    
    switch (USB_GETDESINDEX(request)) {
        
        case 0:     /* Language descriptor */
            USBD_GetLanguageDescriptor((USBSTRINGDESCRIPTOR*)device->respbuf);
            USBD_Write(&device->tx0, 
                       device->respbuf, 
                       MIN(((USBDESCRIPTOR*)device->respbuf)->bLength, request->wLength), 
                       NULL,
                       CFG_USBDWRITETIMEOUT);
            return SUCCESS;
            
#if (CFG_USBDMSFT)
        case 0xEE:  /* Microsoft OS descriptor */
            if (device->msft) {       /* Is Microsoft OS Descriptor support enabled? */
                return USBD_MicrosoftDescriptorRequest(device, request);
            }
            break;   
#endif
            
        default:    /* Generic string descriptor */
            status = USBD_GetStringDescriptor(device,                           /* Get the string descriptor */
                                              USB_GETDESINDEX(request),         /* The index of the requested string */
                                              device->respbuf,                  /* A buffer to receive the descriptor */
                                              CFG_USBDREQRESBUFSIZE);           /* The size of the supplied buffer */
            if (status == SUCCESS) {
                USBD_Write(&device->tx0, 
                           device->respbuf, 
                           MIN(((USBDESCRIPTOR*)device->respbuf)->bLength, 
                               request->wLength), 
                           NULL,
                           CFG_USBDWRITETIMEOUT);
                return SUCCESS;
            }
            break;
    }
    
    return ERR_NOTSUPPORTED;
}
