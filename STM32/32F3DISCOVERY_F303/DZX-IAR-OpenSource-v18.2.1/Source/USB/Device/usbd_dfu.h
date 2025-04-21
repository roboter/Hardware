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
#ifndef USBD_DFU_H__
#define USBD_DFU_H__

#include "USB/Device/usbd.h"

/*******************************************************************************************************************************************
    TYPE DEFINITIONS
*******************************************************************************************************************************************/
typedef struct DFUDINTERFACE DFUDINTERFACE;
typedef struct DFUDBLOCK DFUDBLOCK;
typedef enum DFUDEVENT DFUDEVENT;
typedef struct DFUDSETTINGS DFUDSETTINGS;

/*******************************************************************************************************************************************
    SIGNAL DEFINITIONS
*******************************************************************************************************************************************/
#define SIGNAL_DFUDDETACH       SIGNAL_0        /**< The signal to indicate a DFU detach event */
#define SIGNAL_DFUDMANIFEST     SIGNAL_1        /**< The signal to indicate a DFU manifest event */
#define SIGNAL_DFUDDOWNLOAD     SIGNAL_2        /**< The signal to indicate a DFU download event */
#define SIGNAL_DFUDUPLOAD       SIGNAL_3        /**< The signal to indicate a DFU upload event */

/***************************************************************************************************************************************//**

    Represents a block of data that has been downloaded or uploaded from a device firmware update interface.
    @module     usbd-dfu

*******************************************************************************************************************************************/
struct DFUDBLOCK {
    UINT32  lba;            /**< The logical block address for the block */
    UINT32  len;            /**< The length in bytes for the block */
    void*   data;           /**< A pointer to the data values for the block */
};

/***************************************************************************************************************************************//**

    Represents settings for a DFU interface.
    @module     usbd-dfu

*******************************************************************************************************************************************/
struct DFUDSETTINGS {
    UINT16  transferSize;           /**< The size, in bytes, for each data transfer through the interface */
    UINT16  bcdDFU;                 /**< The version of the DFU interface */
    UINT16  detachTimeout;          /**< The time the interface will wait before performing a detach */
    BYTE    attributes;             /**< The attributes for the DFU interface per spec as sent to a host */
    BYTE    pad;                    /**< Padding to preserve 32-bit alignment */
};

/***************************************************************************************************************************************//**

    Represents a Device Firmware Update (DFU) interface.
    @module     usbd-dfu

*******************************************************************************************************************************************/
struct DFUDINTERFACE {
    USBDINTERFACE   base;               /**< An extension of the standard USB device interface */
    DFUSTATUS       status;             /**< The current status for the interface */
    UINT16          pad;                /**< Padding for 32-bit alignment */
    DFUDSETTINGS    settings;           /**< Settings for the interface */
    DFUDBLOCK       blk;                /**< The current data block */
    void*           buf;                /**< A pointer to a buffer used for DFU block data transfers */
    UINT32          bufsize;            /**< The size, in bytes, for the DFU block data buffer */
    SIGNALSET       txsignals;          /**< A signal set used to send signals to the application */
    SIGNALSET       rxsignals;          /**< A signal set used to send signals to the interface */
};

/*******************************************************************************************************************************************
    PUBLIC FUNCTIONS
*******************************************************************************************************************************************/
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
extern STATUS DFUD_CreateInterface(USBDDEVICE* usbd, DFUDINTERFACE* intf, BYTE mode, void* buf, UINT32 bufsize);

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
extern STATUS DFUD_Wait(DFUDINTERFACE* intf, UINT32* signals, UINT32 timeout);

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
extern STATUS DFUD_SetSettings(DFUDINTERFACE* intf, const DFUDSETTINGS* settings);

/***************************************************************************************************************************************//**

    Returns the current settings for a USB device DFU interface.

    @param[in]  intf        A pointer to the interface that contains the settings to be returned.

    @return     A pointer to the settings for the specified interface upon success; otherwise NULL.
    @module     usbd-dfu

*******************************************************************************************************************************************/
extern const DFUDSETTINGS* DFUD_GetSettings(DFUDINTERFACE* intf);

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
extern STATUS DFUD_DownloadComplete(DFUDINTERFACE* intf);

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
extern STATUS DFUD_ManifestComplete(DFUDINTERFACE* intf);

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
extern STATUS DFUD_UploadComplete(DFUDINTERFACE* intf);

/***************************************************************************************************************************************//**

    Returns the current data block for a device DFU interface. The data block contains the data that has most recently been downloaded
    or uploaded.

    @param[in]  intf        A pointer to the target interface.

    @return     A pointer to the data block upon success; otherwise NULL.
    @module     usbd-dfu

*******************************************************************************************************************************************/
extern DFUDBLOCK* DFUD_GetDataBlock(DFUDINTERFACE* intf);

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
extern STATUS DFUD_SetError(DFUDINTERFACE* intf, DFUERROR error);

#endif /* USBD_DFU_H__ */
