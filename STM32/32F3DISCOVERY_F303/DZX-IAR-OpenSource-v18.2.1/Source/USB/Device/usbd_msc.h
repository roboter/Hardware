/*******************************************************************************************************************************************

    DZX | USB DEVICE | MASS STORAGE CLASS (MSC)                                                                           VERSION 18.2.1
    ------------------------------------------------------------------------------------------------------------------------------------

    This is part of the USB device stack and provides support for implementing a mass storage class (MSC) interface.

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
#ifndef USBD_MSC_H__
#define USBD_MSC_H__

#include "USB/Device/usbd.h"
#include "FS/Disk/disk.h"

/*******************************************************************************************************************************************
    TYPE DEFINITIONS
*******************************************************************************************************************************************/
typedef struct MSCDINTERFACE MSCDINTERFACE;
typedef struct SCSIKCQ SCSIKCQ;
typedef struct MSCDLUN MSCDLUN;

/***************************************************************************************************************************************//**

    Represents sense key information.
    @module     internal

*******************************************************************************************************************************************/
struct SCSIKCQ {
    BYTE key;               /**< The sense key value */
    BYTE asc;               /**< The additional sense code */
    BYTE ascq;              /**< The additional sense code qualifier */
    BYTE pad;               /**< Explicit padding for 32-bit alignment */
};

/***************************************************************************************************************************************//**

    Represents a Mass Storage Class (MSC) interface.
    @module     usbd-msc

*******************************************************************************************************************************************/
struct MSCDINTERFACE {
    USBDINTERFACE   base;                                       /**< An extension of the standard USB device interface */
    USBDENDPOINT    eprx;                                       /**< An endpoint for receiving commands */
    USBDENDPOINT    eptx;                                       /**< An endpoint for transmitting */
    LIST            luns;                                       /**< A list of logical units (and media disks) */
    THREAD          thread;                                     /**< A thread for processing mass storage requests */
    UINT32          stk[CFG_MSCDSTACKSIZE / sizeof(UINT32)];    /**< Stack memory for the thread above */
    SCSIKCQ         sense;                                      /**< Sense information (for the request sense) */
    UINT32          reset;
    UINT32          buffer[CFG_MSCDBUFFERSIZE / sizeof(UINT32)];/**< A buffer for data between media disk and usb host */
};

/***************************************************************************************************************************************//**

    Represents a logical unit within a mass storage interface.
    @module     usbd-msc

*******************************************************************************************************************************************/
struct MSCDLUN {
    NODE            node;                   /**< A node to place this unit into a list */
    DISK*           disk;                   /**< A pointer to the media disk used by this unit */
    const BYTE*     inqinfo;                /**< A pointer to the SCSI inquiry information for this unit */
    UINT32          inqlen;                 /**< The length, in bytes, of the inquiry information */
    BOOLEAN         enabled;                /**< An enable/disable state for this logical unit */
};

/*******************************************************************************************************************************************
    PUBLIC FUNCTIONS
*******************************************************************************************************************************************/
/***************************************************************************************************************************************//**

    Creates and initializes a Mass Storage Class (MSC) interface for a USB device.

    @param[in]  device      A pointer to a USB device stack instance that will receive the interface.
    @param[in]  intf        A pointer to a caller allocated mass storage interface instance to be initialized.
    @param[in]  epnum       The number of the endpoints to be created for the interface (must be non-zero).

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The interface was created and initialized.
     ERR_NULLREFERENCE      | The argument 'device' or 'intf' was found to be NULL.
     ERR_INVALIDARGUMENT    | An invalid argument was specified.

    @module     usbd-msc

*******************************************************************************************************************************************/
extern STATUS MSCD_CreateInterface(USBDDEVICE* device, MSCDINTERFACE* intf, BYTE epnum);

/***************************************************************************************************************************************//**

    Adds a logical unit to a mass storage interface.

    @param[in]  intf        A pointer to the mass storage interface to receive the logical unit.
    @param[in]  lun         A pointer to a caller allocated logical unit to be initialized and added to the specified interface.
    @param[in]  disk        A pointer to the media disk driver to be used by the logical unit.
    @param[in]  info        A pointer to the SCSI inquiry information for the logical unit.
    @param[in]  infolen     The size, in bytes, of the inquiry information.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The logical unit was initialized and added to the given interface.
     ERR_NULLREFERENCE      | The argument 'intf', 'lun', 'disk' or 'info' was found to be NULL.

    @module     usbd-msc

*******************************************************************************************************************************************/
extern STATUS MSCD_AddLUN(MSCDINTERFACE* intf, MSCDLUN* lun, DISK* disk, const BYTE* info, UINT32 infolen);

/***************************************************************************************************************************************//**

    Removes a logical unit from a mass storage interface.

    @param[in]  intf        A pointer to the mass storage interface that contains the logical unit.
    @param[in]  lun         A pointer to the logical unit to be removed.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The logical unit was removed from the interface.
     ERR_NULLREFERENCE      | The argument 'intf' or 'lun' was found to be NULL.

    @module     usbd-msc

*******************************************************************************************************************************************/
extern STATUS MSCD_RemoveLUN(MSCDINTERFACE* intf, MSCDLUN* lun);

/***************************************************************************************************************************************//**

    Sets the enable/disable state for a logical unit within a mass storage interface.

    @param[in]  lun         A pointer to the logical unit to be enabled or disabled.
    @param[in]  enabled     The new enabled state for the logical unit.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The enabled state for the logical unit has been updated.
     ERR_NULLREFERENCE      | The argument 'lun' was found to be NULL.

    @module     usbd-msc

*******************************************************************************************************************************************/
extern STATUS MSCD_SetEnabled(MSCDLUN* lun, BOOLEAN enabled);

/***************************************************************************************************************************************//**

    Returns the enable/disable state for a logical unit within a mass storage interface.

    @param[in]  lun         A pointer to the target logical unit.

    @return     TRUE if the logical unit is currently enabled; otherwise FALSE.
    @module     usbd-msc

*******************************************************************************************************************************************/
extern BOOLEAN MSCD_Enabled(MSCDLUN* lun);

#endif /* USBD_MSC_H__ */
