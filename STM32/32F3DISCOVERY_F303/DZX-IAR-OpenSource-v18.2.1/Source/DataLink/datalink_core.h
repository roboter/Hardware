/*******************************************************************************************************************************************

    DZX | DATALINK | CORE                                                                                                 VERSION 18.2.1
    ------------------------------------------------------------------------------------------------------------------------------------

    This provides the core interface for implementing custom communication data links. This interface is used internally by data links 
    and is not intended to be used directly by an application.

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
#include "DataLink/datalink.h"

/***************************************************************************************************************************************//**

    Creates and initializes a generic data link.

    @param[in]  link        A pointer to a caller allocated data link to be initialized.
    @param[in]  write       A handler function called upon to transfer data for the data link.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The data link has been initialized.
     ERR_NULLREFERENCE      | The argument 'link' or 'write' was found to be NULL.

    @module     DATALINK-CORE

*******************************************************************************************************************************************/
extern STATUS DATALINK_Create(DATALINK* link, DATALINKWRITEHANDLER write, void* arg);

/***************************************************************************************************************************************//**

    Processes a received encapsulated message.

    @param[in]  link        A pointer to the data link to process to the message.
    @param[in]  data        A pointer to the encapsulated message data to be processed.
    @param[in]  nbytes      The size, in bytes, of the message.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The message has been processed.
     ERR_NULLREFERENCE      | The argument 'link' or 'data' was found to be NULL.
     ERR_INVALIDARGUMENT    | The argument 'nbytes' was invalid. Must be at least 4 bytes.

    @module     DATALINK-CORE

*******************************************************************************************************************************************/
extern STATUS DATALINK_HandleMessage(DATALINK* link, DATALINKID id, void* data, UINT32 nbytes);

/***************************************************************************************************************************************//**

    Writes (transmits) a message over a data link.

    @param[in]  link        A pointer to the data link to transmit the message.
    @param[in]  data        A pointer to the message data to be transmitted.
    @param[in]  nbytes      The number of bytes to be transmitted.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The message has been transmitted.
     ERR_NULLREFERENCE      | The argument 'link' or 'data' was found to be NULL.

    @module     DATALINK-CORE

*******************************************************************************************************************************************/
extern STATUS DATALINK_Write(DATALINK* link, void* data, UINT32 nbytes);

/***************************************************************************************************************************************//**

    Deserializes data from a buffer into a value object.

    @param[in]  buffer      A pointer to the buffer that contains the serialized data.
    @param[in]  offset      A zero-based offset into the buffer.
    @param[out] value       A pointer to a caller allocated value object.
    @param[in]  nbytes      The size, in bytes, of the value to be deserialized.

    @return     The total number of bytes that have been deserialized.
    @module     DATALINK-CORE

*******************************************************************************************************************************************/
extern UINT32 DATALINK_Deserialize(const void* buffer, UINT32 offset, void* value, UINT32 nbytes);

/***************************************************************************************************************************************//**

    Serializes a value object into a buffer.

    @param[in]  buffer      A pointer to a buffer to receive the serialized values.
    @param[in]  offset      A zero-based offset into the buffer.
    @param[out] value       A pointer to the value to be serialized.
    @param[in]  nbytes      The size, in bytes, of the value to be serialized.

    @return     The total number of bytes that have been serialized and placed into the buffer.
    @module     DATALINK-CORE

*******************************************************************************************************************************************/
extern UINT32 DATALINK_Serialize(void* buffer, UINT32 offset, const void* value, UINT32 nbytes);
