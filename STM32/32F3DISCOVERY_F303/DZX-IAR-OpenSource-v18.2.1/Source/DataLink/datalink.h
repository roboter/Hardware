/*******************************************************************************************************************************************

    DZX | DATALINK                                                                                                        VERSION 18.2.1
    ------------------------------------------------------------------------------------------------------------------------------------

    This provides the interface for implementing custom communication data links.

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
#ifndef DATALINK_H__
#define DATALINK_H__

#include "Kernel/kernel.h"
#include "Kernel/kernel_mutex.h"
#include "datalink_cfg.h"

#if (CFG_DATALINKENCAPSULATION)
#include "Util/slip.h"
#endif

/*******************************************************************************************************************************************
    TYPE DEFINITIONS
*******************************************************************************************************************************************/
typedef struct DATALINK DATALINK;

/***************************************************************************************************************************************//**

    Represents a function that can write (transmit) a data link message.

    @param[in]  link        A pointer to the data link to transmit the message.
    @param[in]  arg         A pointer to an application-defined argument.
    @param[in]  data        A pointer to the data to be transmitted.
    @param[in]  nbytes      The number of bytes of data to be transmitted.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The message has been transmitted.
     ERR_NULLREFERENCE      | The argument 'link' or 'data' was found to be NULL.

    @module     datalink

*******************************************************************************************************************************************/
typedef STATUS (*DATALINKWRITEHANDLER)(DATALINK* link, void* arg, const void* data, UINT32 nbytes);

/***************************************************************************************************************************************//**

    Represents a function that creates and initializes an application-defined data link.

    @param[in]  link        A pointer to caller allocated data link instance to be initialized.
    @param[in]  write       A handler function that is called to transmit data over the link.
    @param[in]  arg         An application-defined argument that is passed to the write handler function.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The data link has been initialized.
     ERR_NULLREFERENCE      | The argument 'link' was found to be NULL.

    @module     datalink

*******************************************************************************************************************************************/
typedef STATUS (*DATALINKCREATEHANDLER)(DATALINK* link, DATALINKWRITEHANDLER write, void* arg);

/***************************************************************************************************************************************//**

    Represents an identifier field that begins each message transferred over a data link.
    @module     datalink

*******************************************************************************************************************************************/
typedef union DATALINKID {                     
    struct {
        UINT32 number       :16;        /**< The ID number for the message */
        UINT32              :16;        /**< Reserved for future use */
    };
    UINT32 value;
} DATALINKID;

/***************************************************************************************************************************************//**

    Represents a data link instance.
    @module     datalink

*******************************************************************************************************************************************/
struct DATALINK {
    UINT32 version;                     /**< The protocol version for the link. */
    BOOLEAN useCRC;                     /**< Indication of whether the link should use CRC validation. */
    BOOLEAN encapsulate;
    DATALINKWRITEHANDLER write;         /**< A handler function to write (transmit) a message over the link. */
    void* writearg;
    MUTEX mutex;
    void* buffer;
#if (CFG_DATALINKENCAPSULATION)
    SLIPENCODER encoder;                /**< An encoder for encapsulating a message prior to transmitting */
    SLIPDECODER decoder;                /**< A decoder for decapsulating a message after reception */
#endif
};

/***************************************************************************************************************************************//**

    Processes a received encapsulated message.

    @param[in]  link        A pointer to the data link to process the message.
    @param[in]  data        A pointer to the encapsulated message data to be processed.
    @param[in]  nbytes      The number of bytes of data contained within the message.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The message has been processed.
     ERR_NULLREFERENCE      | The argument 'link' or 'data' was found to be NULL.
     ERR_INVALIDCONTEXT     | The operation is not supported from the context of an interrupt service routine (ISR).
     ERR_INVALIDARGUMENT    | The argument 'nbytes' was invalid. Must be at least 4 bytes.

    @module     datalink

*******************************************************************************************************************************************/
extern STATUS DATALINK_ReceivedMessage(DATALINK* link, void* data, UINT32 nbytes);

#if (CFG_DATALINKENCAPSULATION)
/***************************************************************************************************************************************//**

    Enables and configures a data link for encapsulation of transferred data.

    @param[in]  link        A pointer to the data link to be enabled and configured.
    @param[in]  decbuf      A pointer to a caller allocated buffer for holding decapsulated data. Must be large enough to hold an entire
                            decapsulated message.
    @param[in]  decsize     The size, in bytes, of the provided buffer for decapsulated data.
    @param[in]  encbuf      A pointer to a caller allocated buffer for holding encoded, encapsulated data. Does not have to be large
                            enough to hold an entire encapsulated message as the link will call the write handler any time the buffer
                            becomes full.
    @param[in]  encsize     The size, in bytes, of the provided buffer for encapsulated data.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The data link has been configured for encapsulation.
     ERR_NULLREFERENCE      | The argument 'link', 'decbuf' or 'encbuf' was found to be NULL.
     ERR_INVALIDARGUMENT    | The argument 'decsize' or 'encsize' was invalid. They must be larger than zero.

    @module     datalink

*******************************************************************************************************************************************/
extern STATUS DATALINK_EnableEncapsulation(DATALINK* link, void* decbuf, UINT32 decsize, void* encbuf, UINT32 encsize);

/***************************************************************************************************************************************//**

    Processes received unencapsulated message data.

    @param[in]  link        A pointer to the data link to process to the message data.
    @param[in]  data        A pointer to the unencapsulated message data to be processed.
    @param[in]  nbytes      The size, in bytes, of the data to be processed.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The message data has been processed.
     ERR_NULLREFERENCE      | The argument 'link' or 'data' was found to be NULL.

    @module     datalink

*******************************************************************************************************************************************/
extern STATUS DATALINK_ReceivedBytes(DATALINK* link, void* data, UINT32 nbytes);

#endif /* CFG_DATALINKENCAPSULATION */
#endif /* DATALINK_H__ */
