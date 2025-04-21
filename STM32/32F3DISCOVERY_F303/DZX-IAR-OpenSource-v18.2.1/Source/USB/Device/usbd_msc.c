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
#include "USB/Device/usbd_msc.h"

/*******************************************************************************************************************************************
    PRIVATE FUNCTIONS
*******************************************************************************************************************************************/
static STATUS MSCD_Request(USBDDEVICE* device, USBDINTERFACE* intf, const USBREQUEST* request);
static void MSCD_Reset(MSCDINTERFACE* intf);
static void MSCD_Thread(void* arg);
static MSCDLUN* MSCD_GetLUN(MSCDINTERFACE* intf, BYTE lun);
static UINT32 MSCD_GetLBA(const CBW* cbw);
static UINT32 MSCD_GetBlockCount(const CBW* cbw);
static STATUS MSCD_ProcessRequest(MSCDINTERFACE* intf, MSCDLUN* lun, const CBW* cbw, CSW* csw);
static STATUS MSCD_WriteData(MSCDINTERFACE* intf, CSW* csw, const void* data, UINT32 size);
static STATUS MSCD_WriteStatus(MSCDINTERFACE* intf, CSW* csw, BYTE status);
static void MSCD_Failed(MSCDINTERFACE* intf, const CBW* cbw, CSW* csw, BYTE key, BYTE asc, BYTE ascq);
static BOOLEAN MSCD_Ready(MSCDLUN* lun);
static STATUS MSCD_TestUnitReady(MSCDINTERFACE* intf, MSCDLUN* lun, const CBW* cbw, CSW* csw);
static STATUS MSCD_Inquiry(MSCDINTERFACE* intf, MSCDLUN* lun, const CBW* cbw, CSW* csw);
static STATUS MSCD_StartStopUnit(MSCDINTERFACE* intf, MSCDLUN* lun, const CBW* cbw, CSW* csw);
static STATUS MSCD_PreventAllowRemoval(MSCDINTERFACE* intf, MSCDLUN* lun, const CBW* cbw, CSW* csw);
static STATUS MSCD_Read10(MSCDINTERFACE* intf, MSCDLUN* lun, const CBW* cbw, CSW* csw);
static STATUS MSCD_Write10(MSCDINTERFACE* intf, MSCDLUN* lun, const CBW* cbw, CSW* csw);
static STATUS MSCD_ReadCapacity10(MSCDINTERFACE* intf, MSCDLUN* lun, const CBW* cbw, CSW* csw);
static STATUS MSCD_ReadFormatCapacities(MSCDINTERFACE* intf, MSCDLUN* lun, const CBW* cbw, CSW* csw);
static STATUS MSCD_RequestSense(MSCDINTERFACE* intf, CSW* csw);
static STATUS MSCD_ModeSense6(MSCDINTERFACE* intf, MSCDLUN* lun, const CBW* cbw, CSW* csw);

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
STATUS MSCD_CreateInterface(USBDDEVICE* device, MSCDINTERFACE* intf, BYTE epnum)
{
    STATUS status;
    
    
#if (CFG_NULLCHECKING)
    if (device == NULL) {
        return ERR_NULLREFERENCE;
    }
    
    if (intf == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif
    
    if (epnum == 0) {
        return ERR_INVALIDARGUMENT;
    }
    
    intf->base.reqcb = MSCD_Request;                            /* Provide class-defined callback functions */
    intf->base.descb = NULL;
    intf->reset = 0;
    
    status = USBD_CreateInterface(device,                       /* Create the interface within the usb device stack */
                                  &intf->base,                  /* The base (common) interface */
                                  USBINTFCLASSMASSSTORAGE,      /* Mass storage class code */
                                  USBINTFSUBCLASSSCSI,          /* SCSI sub-class code */
                                  USBINTFPROTOCOLBULKONLY);     /* Bulk only protocol code */
    
    if (status != SUCCESS) {
        return status;
    }

    status = USBD_CreateEndpoint(&intf->base,                   /* Create an endpoint for transmitting to the host (IN) */
                                 &intf->eptx,
                                 USBTRANSFERBULK,
                                 epnum | 0x80,                  
                                 64,
                                 512,
                                 0,
                                 OPT_NONE);
    
    if (status != SUCCESS) {
        return status;
    }
    
    status = USBD_CreateEndpoint(&intf->base,                   /* Create an endpoint for receiving from the host (OUT) */
                                 &intf->eprx,
                                 USBTRANSFERBULK,
                                 (epnum & 0x7F),
                                 64,
                                 512,
                                 0,
                                 OPT_NONE);
    
    if (status != SUCCESS) {
        return status;
    }
    
    status = THREAD_Create(&intf->thread,                       /* Create a thread for processing mass storage requests */
                           "USBD MSC",                          /* The thread name */
                           intf->stk,                           /* Stack memory for the thread */
                           CFG_MSCDSTACKSIZE,                   /* Configured stack memory size (in usbd_cfg.h) */
                           CFG_MSCDPRIO);                       /* Configured priority for the thread (in usbd_cfg.h) */
    
    if (status != SUCCESS) {
        return status;
    }
    
    status = THREAD_Start(&intf->thread,                        /* Start the mass storage process thread */
                          MSCD_Thread, 
                          intf);
    
    if (status != SUCCESS) {
        return status;
    }                             
    
    return SUCCESS;
}

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
STATUS MSCD_AddLUN(MSCDINTERFACE* intf, MSCDLUN* lun, DISK* disk, const BYTE* info, UINT32 infolen)
{
#if (CFG_NULLCHECKING)
    if (intf == NULL) {
        return ERR_NULLREFERENCE;
    }
    
    if (lun == NULL) {
        return ERR_NULLREFERENCE;
    }    
    
    if (disk == NULL) {
        return ERR_NULLREFERENCE;
    }
    
    if (info == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif
    
    lun->disk = disk;
    lun->inqinfo = info;
    lun->inqlen = infolen;
    lun->enabled = TRUE;
                                 
    LIST_AddLast(&intf->luns, &lun->node, lun);
    return SUCCESS;
}

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
STATUS MSCD_RemoveLUN(MSCDINTERFACE* intf, MSCDLUN* lun)
{
#if (CFG_NULLCHECKING)
    if (intf == NULL) {
        return ERR_NULLREFERENCE;
    }
    
    if (lun == NULL) {
        return ERR_NULLREFERENCE;
    }    
#endif

    LIST_Remove(&intf->luns, &lun->node);
    return SUCCESS;
}

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
STATUS MSCD_SetEnabled(MSCDLUN* lun, BOOLEAN enabled)
{
    INTERRUPTLOCK lock;
    
    
#if (CFG_NULLCHECKING)
    if (lun == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif
    
    ACQUIREINTERRUPTLOCK();
    lun->enabled = enabled;
    RELEASEINTERRUPTLOCK();
    return SUCCESS;
}

/***************************************************************************************************************************************//**

    Returns the enable/disable state for a logical unit within a mass storage interface.

    @param[in]  lun         A pointer to the target logical unit.

    @return     TRUE if the logical unit is currently enabled; otherwise FALSE.
    @module     usbd-msc

*******************************************************************************************************************************************/
BOOLEAN MSCD_Enabled(MSCDLUN* lun)
{
    INTERRUPTLOCK lock;
    
    
#if (CFG_NULLCHECKING)
    if (lun == NULL) {
        return FALSE;
    }
#endif
    
    ACQUIREINTERRUPTLOCK();
    if (lun->enabled) {
        RELEASEINTERRUPTLOCK();
        return TRUE;
    }
    
    RELEASEINTERRUPTLOCK();
    return FALSE;
}

/***************************************************************************************************************************************//**

    Handles a request from a host for a mass storage interface.

    @param[in]  device      A pointer to the device that received the request.
    @param[in]  intf        A pointer to the mass storage interface.
    @param[in]  request     A pointer to the received request message.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The request has been handled.
     ERR_NOTSUPPORTED       | The request is not supported.

    @module     internal

*******************************************************************************************************************************************/
static STATUS MSCD_Request(USBDDEVICE* device, USBDINTERFACE* intf, const USBREQUEST* request)
{
    ALIGNED(4) BYTE value;
    
    
    switch (request->bRequest) {
        case MSCGETMAXLUN:
            value = ((MSCDINTERFACE*)intf)->luns.count - 1;
            USBD_Write(&device->tx0, &value, 1, NULL, CFG_USBDWRITETIMEOUT);
            return SUCCESS;
            
        case MSCRESET:
            MSCD_Reset((MSCDINTERFACE*)intf);
            USBD_Write(&device->tx0, NULL, 0, NULL, CFG_USBDWRITETIMEOUT);
            return SUCCESS;
            
        default:
            break;
    }
    
    return ERR_NOTSUPPORTED;
}

/***************************************************************************************************************************************//**

    Performs a reset upon a mass storage interface.

    @param[in]  intf        A pointer to the interface to be reset.

    @return     None.
    @module     internal

*******************************************************************************************************************************************/
static void MSCD_Reset(MSCDINTERFACE* intf)
{
    intf->reset = 0;
    
    USBD_UnstallEndpoint(&intf->eptx);                          /* Reset the endpoints if they've been stalled due to a failed request */
    USBD_UnstallEndpoint(&intf->eprx);
}

/***************************************************************************************************************************************//**

    A thread for processing requests for a mass storage interface.

    @param[in]  arg         A pointer to the target mass storage interface.

    @return     None.
    @module     internal

*******************************************************************************************************************************************/
static void MSCD_Thread(void* arg)
{
    ALIGNED(4) CBW cbw;
    ALIGNED(4) CSW csw;
    MSCDINTERFACE* intf;
    STATUS status;
    MSCDLUN* lun;
    UINT32 nrd;
    
    
    intf = (MSCDINTERFACE*)arg;
    
    for (;;) {
        
        status = USBD_Read(&intf->eprx,                         /* Block until receiving a request */
                           &cbw, 
                           sizeof(CBW), 
                           &nrd, 
                           INFINITE);
        
        if (status == SUCCESS) {

            if (!intf->reset && nrd == sizeof(CBW)) {

                csw.dCSWSignature = CSW_SIGNATURE;                  /* Pre-populate the status response */
                csw.dCSWTag = cbw.dCBWTag;
                csw.dCSWDataResidue = cbw.dCBWDataTransferLength;
                
                lun = MSCD_GetLUN(intf, cbw.bCBWLUN);               /* Lookup the target logical unit */
                if (lun) {
                    MSCD_ProcessRequest(intf, lun, &cbw, &csw);     /* Process the request */
                } else {
                    USBD_StallEndpoint(&intf->eprx);
                    USBD_StallEndpoint(&intf->eptx);
                }
            } else {
                USBD_StallEndpoint(&intf->eprx);
                USBD_StallEndpoint(&intf->eptx);
            }
        }
    }
}
              
/***************************************************************************************************************************************//**

    Returns a pointer to the logical unit with the specified number.

    @param[in]  intf        A pointer to the mass storage interface that contains the logical unit to be returned.
    @param[in]  number      The number of the logical unit to be returned (zero based).     

    @return     A pointer to the logical unit with the specified number if found; otherwise NULL.
    @module     internal

*******************************************************************************************************************************************/
static MSCDLUN* MSCD_GetLUN(MSCDINTERFACE* intf, BYTE number)
{
    NODE* node;
    UINT32 count = 0;
    
    
    LIST_Foreach(node, &intf->luns) {
        if (count == number) {
            return (MSCDLUN*)node->value;
        }
        
        count++;
    }
    
    return NULL;
}

/***************************************************************************************************************************************//**

    Returns the logical block address (LBA) from a command block wrapper (CBW).

    @param[in]  cbw         A pointer to a command block wrapper to be parsed.  

    @return     The logical block address represented by the given command block wrapper.
    @module     internal

*******************************************************************************************************************************************/
static UINT32 MSCD_GetLBA(const CBW* cbw)
{
    return ((cbw->CBWCB[2] << 24) | (cbw->CBWCB[3] << 16) | (cbw->CBWCB[4] << 8) | (cbw->CBWCB[5]));
}

/***************************************************************************************************************************************//**

    Returns the block count from a command block wrapper (CBW).

    @param[in]  cbw         A pointer to a command block wrapper to be parsed.  

    @return     The block count represented by the given command block wrapper.
    @module     internal

*******************************************************************************************************************************************/
static UINT32 MSCD_GetBlockCount(const CBW* cbw)
{
    return ((cbw->CBWCB[7] << 8) | (cbw->CBWCB[8]));
}

/***************************************************************************************************************************************//**

    Handles a mass storage command block wrapper request.

    @param[in]  intf        A pointer to the mass storage interface that received the request.
    @param[in]  lun         A pointer to the target logical unit for the request.
    @param[in]  cbw         A pointer to the received command block wrapper.
    @param[in]  csw         A pointer to the status wrapper used to provide a response.

    @return     The logical block address represented by the given command block wrapper.
    @module     internal

*******************************************************************************************************************************************/
static STATUS MSCD_ProcessRequest(MSCDINTERFACE* intf, MSCDLUN* lun, const CBW* cbw, CSW* csw)
{
    if (cbw->dCBWSignature != CBW_SIGNATURE) {                  /* Validate the command signature */
        USBD_StallEndpoint(&intf->eprx);
        USBD_StallEndpoint(&intf->eptx);
        return ERR_NOTSUPPORTED;
    }
    
    switch (cbw->CBWCB[0]) {
        case SCSI_TESTUNITREADY:
            MSCD_TestUnitReady(intf, lun, cbw, csw);
            break;
        case SCSI_INQUIRY:
            MSCD_Inquiry(intf, lun, cbw, csw);
            break;
        case SCSI_REQUESTSENSE:
            MSCD_RequestSense(intf, csw);
            break;
        case SCSI_READFORMATCAPACITIES:
            MSCD_ReadFormatCapacities(intf, lun, cbw, csw);
            break;
        case SCSI_READCAPACITY10:
            MSCD_ReadCapacity10(intf, lun, cbw, csw);
            break;
        case SCSI_READ10:
            MSCD_Read10(intf, lun, cbw, csw);
            break;
        case SCSI_WRITE10:
            MSCD_Write10(intf, lun, cbw, csw);
            break;
        case SCSI_MODESENSE6:
            MSCD_ModeSense6(intf, lun, cbw, csw);
            break;  
        case SCSI_STARTSTOPUNIT:
            MSCD_StartStopUnit(intf, lun, cbw, csw);
            break;
        case SCSI_MEDIAREMOVAL:
            MSCD_PreventAllowRemoval(intf, lun, cbw, csw);
            break;

        default:
            MSCD_Failed(intf,                                   /* Unsupported request */
                        cbw, 
                        csw, 
                        SENSEKEY_ILLEGALREQUEST, 
                        ASC_UNSUPPORTEDCOMMAND, 
                        ASCQ_NONE);
            return ERR_NOTSUPPORTED;
    }
 
    return SUCCESS;
}

/***************************************************************************************************************************************//**

    Handles a failed request for a mass storage interface.

    @param[in]  intf        A pointer to the mass storage interface that received the request.
    @param[in]  cbw         A pointer to the received command block that has failed.
    @param[in]  csw         A pointer to the status wrapper used to provide a response.
    @param[in]  key         The sense key value for the error-code.
    @param[in]  asc         The additional sense code value of the error-code.
    @param[in]  ascq        The additional sense code qualifier value for the error-code.

    @return     None.
    @module     internal

*******************************************************************************************************************************************/
static void MSCD_Failed(MSCDINTERFACE* intf, const CBW* cbw, CSW* csw, BYTE key, BYTE asc, BYTE ascq)
{
    USBDENDPOINT* endpt;

    
    intf->sense.key = key;                                      /* Update the sense information to be retreived by the host */
    intf->sense.asc = asc;
    intf->sense.ascq = ascq;

    if (csw->dCSWDataResidue) {                                 /* Is there a data transfer pending? */
        
        if (cbw->bmCBWFlags & 0x80) {                           /* Get the endpoint for the pending data transfer */
            endpt = &((MSCDINTERFACE*)intf)->eptx;
        } else {
            endpt = &((MSCDINTERFACE*)intf)->eprx;
        }
        
        USBD_StallEndpoint(endpt);                              /* Terminate the pending transfer with a stall handshake */
        
        while (USBD_EndpointStalled(endpt)) {                   /* Wait for the host to clear the stall condition */
            THREAD_Sleep(0);                                    /* Yeild cpu time while waiting */
        }
    }
    
    MSCD_WriteStatus(intf, csw, CSW_FAILED);                    /* Complete the request with the status stage */
}

/***************************************************************************************************************************************//**

    Performs the status stage of a mass storage request by transmitting a command status wrapper to the host.

    @param[in]  intf        A pointer to the mass storage interface that received the request.
    @param[in]  csw         A pointer to the status wrapper used to provide a response.
    @param[in]  code        The mass storage status code to be supplied with the response.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The response has been transferred.

    @module     internal

*******************************************************************************************************************************************/
static STATUS MSCD_WriteStatus(MSCDINTERFACE* intf, CSW* csw, BYTE code)
{
    STATUS status;
    
    
    csw->dCSWStatus = code;
    status = USBD_Write(&intf->eptx, 
                        csw, 
                        sizeof(CSW), 
                        NULL, 
                        CFG_MSCDWRITETIMEOUT);
    
    if (status != SUCCESS) {
        return status;
    }
    
    return SUCCESS;
}

/***************************************************************************************************************************************//**

    Performs the data and status stage of a mass storage request by transmitting the requested data followed by a command status wrapper 
    to the host.

    @param[in]  intf        A pointer to the mass storage interface that received the request.
    @param[in]  csw         A pointer to the status wrapper used to provide a response.
    @param[in]  data        A pointer to the data to be transferred to the host.
    @param[in]  size        The size, in bytes, of the data payload to be transferred.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The response has been transferred.

    @module     internal

*******************************************************************************************************************************************/
static STATUS MSCD_WriteData(MSCDINTERFACE* intf, CSW* csw, const void* data, UINT32 size)
{
    STATUS status;
    USBDENDPOINT* endpt;
    
    
    
    if (csw->dCSWDataResidue >= size) {                         /* Verify not to send out more data than expected by the host */

        status = USBD_Write(&intf->eptx,                        /* Transmit the data to the host */
                            data, 
                            size, 
                            NULL, 
                            CFG_MSCDWRITETIMEOUT);
        
        if (status != SUCCESS) {
            return status;
        }
        
        csw->dCSWDataResidue -= size;                           /* Account for the transferred data */
        csw->dCSWStatus = CSW_PASSED;
        
    } else {
        
        endpt = &((MSCDINTERFACE*)intf)->eptx;                  /* Cannot send more than expected by host */
        
        USBD_StallEndpoint(endpt);                              /* Terminate the remainder of this transfer by stall handshake */
        while (USBD_EndpointStalled(endpt)) {                   /* Wait for the host to clear the stall condition */
            THREAD_Sleep(0);                                    /* Yield time slice while waiting */
        }
        
        csw->dCSWDataResidue = 0;
        csw->dCSWStatus = CSW_FAILED;
    }

    status = USBD_Write(&intf->eptx,                            /* Transmit the status for the request */
                        csw, 
                        sizeof(CSW), 
                        NULL, 
                        CFG_MSCDWRITETIMEOUT);
    
    if (status != SUCCESS) {
        return status;
    }
    
    return SUCCESS;
}

/***************************************************************************************************************************************//**

    Returns an indication of whether a logical unit is ready for data transfers.

    @param[in]  lun         A pointer to the logical unit to be tested for readiness.

    @return     TRUE if the logical unit is ready for data transfers; otherwise FALSE.
    @module     internal

*******************************************************************************************************************************************/
static BOOLEAN MSCD_Ready(MSCDLUN* lun)
{
    if (!MSCD_Enabled(lun)) {                                   /* Is the unit explicitly disabled? */
        return FALSE;
    }
    
    if (!DISK_MediaPresent(lun->disk)) {                        /* Is the physical media present (i.e. card inserted) */
        return FALSE;
    }
    
    if (!DISK_Mounted(lun->disk)) {                             /* Is the disk mounted? (enumerated/initialized) */
        return FALSE;
    }
    
    return TRUE;                                                /* Yes, disk is ready for data transfers */
}

/***************************************************************************************************************************************//**

    Handles a TESTUNITREADY command for a mass storage interface.

    @param[in]  intf        A pointer to the mass storage interface that received the request.
    @param[in]  lun         A pointer to the logical unit for the request.
    @param[in]  cbw         A pointer to the received command block wrapper.
    @param[in]  csw         A pointer to the status wrapper used to provide a response.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The request has been handled.

    @module     internal

*******************************************************************************************************************************************/
static STATUS MSCD_TestUnitReady(MSCDINTERFACE* intf, MSCDLUN* lun, const CBW* cbw, CSW* csw)
{
    if (!MSCD_Ready(lun)) {                                     /* Check if the unit is ready for data transfers */
        
        intf->sense.key = SENSEKEY_NOTREADY;                    /* Unit is NOT ready */
        intf->sense.asc = ASC_MEDIUMNOTPRESET;
        intf->sense.ascq = 0;

        MSCD_WriteStatus(intf, csw, CSW_FAILED);
    } else {
        
        intf->sense.key = 0;                                    /* Unit is ready, clear sense information */
        intf->sense.asc = 0;
        intf->sense.ascq = 0;

        MSCD_WriteStatus(intf, csw, CSW_PASSED);
    }
        
    return SUCCESS;
}

/***************************************************************************************************************************************//**

    Handles a INQUIRY command for a mass storage interface.

    @param[in]  intf        A pointer to the mass storage interface that received the request.
    @param[in]  lun         A pointer to the logical unit for the request.
    @param[in]  cbw         A pointer to the received command block wrapper.
    @param[in]  csw         A pointer to the status wrapper used to provide a response.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The request has been handled.

    @module     internal

*******************************************************************************************************************************************/
static STATUS MSCD_Inquiry(MSCDINTERFACE* intf, MSCDLUN* lun, const CBW* cbw, CSW* csw)
{
    UINT32 alloclen;
    
    
    alloclen = (cbw->CBWCB[3] << 8) | cbw->CBWCB[4];
    
    if (alloclen == 0) {
        MSCD_Failed(intf,                                       /* Unsupported command */
                    cbw,
                    csw, 
                    SENSEKEY_ILLEGALREQUEST, 
                    ASC_UNSUPPORTEDCOMMAND, 
                    ASCQ_NONE);
        return ERR_NOTSUPPORTED;
    }
    
    if (alloclen < lun->inqlen) {
        MSCD_WriteData(intf, csw, lun->inqinfo, alloclen);
        return SUCCESS;
    }
    
    MSCD_WriteData(intf, csw, lun->inqinfo, lun->inqlen);
    return SUCCESS;
}

/***************************************************************************************************************************************//**

    Handles a STARTSTOPUNIT command for a mass storage interface.

    @param[in]  intf        A pointer to the mass storage interface that received the request.
    @param[in]  lun         A pointer to the logical unit for the request.
    @param[in]  cbw         A pointer to the received command block wrapper.
    @param[in]  csw         A pointer to the status wrapper used to provide a response.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The request has been handled.

    @module     internal

*******************************************************************************************************************************************/
static STATUS MSCD_StartStopUnit(MSCDINTERFACE* intf, MSCDLUN* lun, const CBW* cbw, CSW* csw)
{
    if ((cbw->CBWCB[4] & 0x1) == 0) {                           /* Is the unit being stopped? */
        
        DISK_Flush(lun->disk);                                  /* Flush any cache within the disk driver */
    }
    
    MSCD_WriteStatus(intf, csw, CSW_PASSED);
    return SUCCESS;
}

/***************************************************************************************************************************************//**

    Handles a PREVENTALLOWMEDIAREMOVAL command for a mass storage interface.

    @param[in]  intf        A pointer to the mass storage interface that received the request.
    @param[in]  lun         A pointer to the logical unit for the request.
    @param[in]  cbw         A pointer to the received command block wrapper.
    @param[in]  csw         A pointer to the status wrapper used to provide a response.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The request has been handled.

    @module     internal

*******************************************************************************************************************************************/
static STATUS MSCD_PreventAllowRemoval(MSCDINTERFACE* intf, MSCDLUN* lun, const CBW* cbw, CSW* csw)
{
    MSCD_WriteStatus(intf, csw, CSW_PASSED);
    return SUCCESS;
}

/***************************************************************************************************************************************//**

    Handles a READ(10) command for a mass storage interface.

    @param[in]  intf        A pointer to the mass storage interface that received the request.
    @param[in]  lun         A pointer to the logical unit for the request.
    @param[in]  cbw         A pointer to the received command block wrapper.
    @param[in]  csw         A pointer to the status wrapper used to provide a response.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The request has been handled.

    @module     internal

*******************************************************************************************************************************************/
static STATUS MSCD_Read10(MSCDINTERFACE* intf, MSCDLUN* lun, const CBW* cbw, CSW* csw)
{
    STATUS status;
    UINT32 lba;
    UINT32 nblks;
    UINT32 blksize;
    UINT32 num;
    UINT32 max;
    UINT32 total;
    
    
    if (!MSCD_Ready(lun)) {
        MSCD_Failed(intf,                                       /* Media is not accessible */
                    cbw,
                    csw, 
                    SENSEKEY_NOTREADY, 
                    ASC_MEDIUMNOTPRESET, 
                    ASCQ_NONE);
        return SUCCESS;
    }
    
    lba = MSCD_GetLBA(cbw);
    nblks = MSCD_GetBlockCount(cbw);
    blksize = DISK_BlockSize(lun->disk);
    
    max = CFG_MSCDBUFFERSIZE / blksize;
    
    total = 0;
    while (total < nblks) {
        
        num = nblks - total;
        if (num > max) {                                        /* Bound this transfer to the size of the underlying buffer */
            num = max;
        }
        
        status = DISK_Read(lun->disk,                           /* Read from the disk media */
                           lba + total, 
                           intf->buffer, 
                           num);
        
        if (status != SUCCESS) {
            MSCD_Failed(intf,                                   /* Failed to read the disk */
                        cbw, 
                        csw, 
                        SENSEKEY_HARDWAREERROR, 
                        ASC_NONE, 
                        ASCQ_NONE);
            return status;
        }
        
        if (csw->dCSWDataResidue < (num * blksize)) {
            MSCD_Failed(intf,                                   /* Fail since host is expecting less data than about to transfer */
                        cbw,
                        csw, 
                        SENSEKEY_ILLEGALREQUEST, 
                        ASC_NONE, 
                        ASCQ_NONE);
            return ERR_INVALIDOPERATION;
        }
        
        csw->dCSWDataResidue -= (num * blksize);
        
        status = USBD_Write(&intf->eptx,                        /* Transfer the disk data to the host */
                            intf->buffer, 
                            num * blksize, 
                            NULL, 
                            CFG_MSCDWRITETIMEOUT);
        
        if (status != SUCCESS) {
            return status;
        }
        
        total += num;
    }
    
    if (csw->dCSWDataResidue) {
        MSCD_Failed(intf,                                       /* Fail since the host is expecting more data */
                    cbw,
                    csw, 
                    SENSEKEY_ILLEGALREQUEST, 
                    ASC_NONE, 
                    ASCQ_NONE);
        return ERR_INVALIDOPERATION;
    }
    
    MSCD_WriteStatus(intf, csw, CSW_PASSED);
    return SUCCESS;
}

/***************************************************************************************************************************************//**

    Handles a WRITE(10) command for a mass storage interface.

    @param[in]  intf        A pointer to the mass storage interface that received the request.
    @param[in]  lun         A pointer to the logical unit for the request.
    @param[in]  cbw         A pointer to the received command block wrapper.
    @param[in]  csw         A pointer to the status wrapper used to provide a response.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The request has been handled.

    @module     internal

*******************************************************************************************************************************************/
static STATUS MSCD_Write10(MSCDINTERFACE* intf, MSCDLUN* lun, const CBW* cbw, CSW* csw)
{
    STATUS status;
    UINT32 lba;
    UINT32 nblks;
    UINT32 blksize;
    UINT32 num;
    UINT32 max;
    UINT32 total;
    UINT32 actual;

    
    
    if (!MSCD_Ready(lun)) {
        MSCD_Failed(intf,                                       /* Media is not accessible */
                    cbw,
                    csw, 
                    SENSEKEY_NOTREADY, 
                    ASC_MEDIUMNOTPRESET, 
                    ASCQ_NONE);
        return SUCCESS;
    }
    
    if (DISK_WriteProtect(lun->disk)) {
        MSCD_Failed(intf,                                       /* Media is write protected */
                    cbw,
                    csw, 
                    SENSEKEY_WRITEPROTECT, 
                    ASC_NONE, 
                    ASCQ_NONE);
        return SUCCESS;
    }
    
    lba = MSCD_GetLBA(cbw);
    nblks = MSCD_GetBlockCount(cbw);
    blksize = DISK_BlockSize(lun->disk);


    max = CFG_MSCDBUFFERSIZE / blksize;
    
    total = 0;
    while (total < nblks) {
        
        num = nblks - total;
        if (num > max) {                                        /* Bound this transfer to the size of the underlying buffer */
            num = max;
        }
        
        if (csw->dCSWDataResidue < (num * blksize)) {
            MSCD_Failed(intf,                                   /* Failed since host isn't expecting to send enough data */
                        cbw,
                        csw, 
                        SENSEKEY_ILLEGALREQUEST, 
                        ASC_NONE, 
                        ASCQ_NONE);
            
            return ERR_INVALIDOPERATION;
        }
        
        USBD_Read(&intf->eprx,                                  /* Receive the data from the host */
                  intf->buffer, 
                  num * blksize, 
                  &actual, 
                  CFG_MSCDREADTIMEOUT);
         
        if (actual < (num * blksize)) {
            MSCD_Failed(intf,                                   /* Failed to receive all of the data from the host */
                        cbw, 
                        csw, 
                        SENSEKEY_HARDWAREERROR, 
                        ASC_NONE, 
                        ASCQ_NONE);
            return ERR_INVALIDOPERATION;
        }
            
        status = DISK_Write(lun->disk,                          /* Write the received data to the disk media */
                            lba + total, 
                            intf->buffer, 
                            num);
        
        if (status != SUCCESS) {
            MSCD_Failed(intf,                                   /* Failed to write the data to the disk media */
                        cbw, 
                        csw, 
                        SENSEKEY_HARDWAREERROR, 
                        ASC_NONE, 
                        ASCQ_NONE);
            return status;
        }
            
        csw->dCSWDataResidue -= (num * blksize);
        total += num;
    }

    if (csw->dCSWDataResidue) {
        MSCD_Failed(intf,                                       /* Failed since the host is expecting to transfer more data */
                    cbw,
                    csw, 
                    SENSEKEY_ILLEGALREQUEST, 
                    ASC_NONE, 
                    ASCQ_NONE);
        
        return ERR_INVALIDOPERATION;
    }
        
    MSCD_WriteStatus(intf, csw, CSW_PASSED);
    DISK_Flush(lun->disk);
    return SUCCESS;
}

/***************************************************************************************************************************************//**

    Handles a READCAPACITY(10) command for a mass storage interface.

    @param[in]  intf        A pointer to the mass storage interface that received the request.
    @param[in]  lun         A pointer to the logical unit for the request.
    @param[in]  cbw         A pointer to the received command block wrapper.
    @param[in]  csw         A pointer to the status wrapper used to provide a response.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The request has been handled.

    @module     internal

*******************************************************************************************************************************************/
static STATUS MSCD_ReadCapacity10(MSCDINTERFACE* intf, MSCDLUN* lun, const CBW* cbw, CSW* csw)
{
    UINT32 size;
    UINT32 count;
    ALIGNED(4) BYTE caps[8];
	

    if (!MSCD_Ready(lun)) {                                     /* Ensure the disk is accessible for transfers */
        MSCD_Failed(intf,                                       /* Disk not currently accessible */
                    cbw,
                    csw, 
                    SENSEKEY_NOTREADY, 
                    ASC_MEDIUMNOTPRESET, 
                    ASCQ_NONE);
        return SUCCESS;
    }
    
    size = DISK_BlockSize(lun->disk);                           /* Query the underlying disk */
    count = DISK_BlockCount(lun->disk);

	caps[0] = ((count - 1) >> 24) & 0xFF;                       /* Last logical block address (lba) */
	caps[1] = ((count - 1) >> 16) & 0xFF;
	caps[2] = ((count - 1) >> 8) & 0xFF;
	caps[3] = ((count - 1) >> 0) & 0xFF;
	
	caps[4] = (size >> 24) & 0xFF;                              /* Block size */
	caps[5] = (size >> 16) & 0xFF;
	caps[6] = (size >> 8) & 0xFF;
	caps[7] = (size >> 0) & 0xFF;
    
    MSCD_WriteData(intf, csw, caps, 8);
    return SUCCESS;
}

/***************************************************************************************************************************************//**

    Handles a READFORMATCAPACITIES command for a mass storage interface.

    @param[in]  intf        A pointer to the mass storage interface that received the request.
    @param[in]  lun         A pointer to the logical unit for the request.
    @param[in]  cbw         A pointer to the received command block wrapper.
    @param[in]  csw         A pointer to the status wrapper used to provide a response.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The request has been handled.

    @module     internal

*******************************************************************************************************************************************/
static STATUS MSCD_ReadFormatCapacities(MSCDINTERFACE* intf, MSCDLUN* lun, const CBW* cbw, CSW* csw)
{
    UINT32 size;
    UINT32 count;
    ALIGNED(4) BYTE caps[12];
	

    
    if (!MSCD_Ready(lun)) {
        MSCD_Failed(intf,
                    cbw,
                    csw, 
                    SENSEKEY_NOTREADY, 
                    ASC_MEDIUMNOTPRESET, 
                    ASCQ_NONE);
        return SUCCESS;
    }
    
    size = DISK_BlockSize(lun->disk);                           /* Query the underlying disk */
    count = DISK_BlockCount(lun->disk);

	caps[0] = 0x00;
	caps[1] = 0x00;
	caps[2] = 0x00;
	caps[3] = 0x08;
	
	caps[4] = (count >> 24) & 0xFF;
	caps[5] = (count >> 16) & 0xFF;
	caps[6] = (count >> 8) & 0xFF;
	caps[7] = (count >> 0) & 0xFF;
	
	caps[8] = 0x02;                                             /* Descriptor Code: Formatted Media */
	
	caps[9] = (size >> 16) & 0xFF;
	caps[10] = (size >> 8) & 0xFF;
	caps[11] = (size >> 0) & 0xFF;


    MSCD_WriteData(intf, csw, caps, 12);
    return SUCCESS;
}

/***************************************************************************************************************************************//**

    Handles a REQUESTSENSE command for a mass storage interface.

    @param[in]  intf        A pointer to the mass storage interface that received the request.
    @param[in]  lun         A pointer to the logical unit for the request.
    @param[in]  cbw         A pointer to the received command block wrapper.
    @param[in]  csw         A pointer to the status wrapper used to provide a response.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The request has been handled.

    @module     internal

*******************************************************************************************************************************************/
static STATUS MSCD_RequestSense(MSCDINTERFACE* intf, CSW* csw)
{
    ALIGNED(4) BYTE buf[18];


    buf[0] = 0x70;                                              /* Response code */
    buf[1] = 0x00;                                              /* Segment number */
    buf[2] = intf->sense.key;                                   /* Sense key */

    buf[3] = 0x00;                                              /* Information */
    buf[4] = 0x00;
    buf[5] = 0x00;
    buf[6] = 0x00;

    buf[7] = 0x0A;                                              /* Additional length */

    buf[8] = 0x00;                                              /* Command specfic information */
    buf[9] = 0x00;
    buf[10] = 0x00;
    buf[11] = 0x00;

    buf[12] = intf->sense.asc;                                  /* Additional sense code */
    buf[13] = intf->sense.ascq;                                 /* Additional sense code qualifier */

    buf[14] = 0x00;                                             /* Sense key specfic information */
    buf[15] = 0x00;
    buf[16] = 0x00;
    buf[17] = 0x00;

    MSCD_WriteData(intf, csw, buf, 18);
    return SUCCESS;
}

/***************************************************************************************************************************************//**

    Handles a MODESENSE(6) command for a mass storage interface.

    @param[in]  intf        A pointer to the mass storage interface that received the request.
    @param[in]  lun         A pointer to the logical unit for the request.
    @param[in]  cbw         A pointer to the received command block wrapper.
    @param[in]  csw         A pointer to the status wrapper used to provide a response.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The request has been handled.

    @module     internal

*******************************************************************************************************************************************/
static STATUS MSCD_ModeSense6(MSCDINTERFACE* intf, MSCDLUN* lun, const CBW* cbw, CSW* csw)
{
    ALIGNED(4) BYTE buf[4];
    
    
    buf[0] = 0x3;
    buf[1] = 0x0;
    buf[2] = 0x0;
    buf[3] = 0x0;
    
    MSCD_WriteData(intf, csw, buf, 4);
    return SUCCESS;
}
