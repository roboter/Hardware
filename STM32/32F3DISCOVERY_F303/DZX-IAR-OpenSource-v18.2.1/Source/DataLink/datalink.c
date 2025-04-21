/*******************************************************************************************************************************************

    DZX | DATALINK                                                                                                        VERSION 18.2.1
    ------------------------------------------------------------------------------------------------------------------------------------

    This provides support for a device data link.

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
#include "DataLink/datalink_core.h"

#if (CFG_DATALINKCRC)
#include "Crypto/crc32.h"
#endif


/*******************************************************************************************************************************************
    PRIVATE FUNCTIONS
*******************************************************************************************************************************************/
static STATUS DATALINK_HandleInfo(DATALINK* link, void* data, UINT32 nbytes);
#if (CFG_DATALINKCRC)
static void DATALINK_AppendCRC(void* data, UINT32 nbytes);
static STATUS DATALINK_VerifyCRC(const void* data, UINT32 nbytes);
#endif
#if (CFG_DATALINKENCAPSULATION)
static void DATALINK_BytesDecoded(SLIPDECODER* decoder, void* arg, const void* data, UINT32 nbytes);
static void DATALINK_BytesEncoded(SLIPENCODER* encoder, void* arg, const void* data, UINT32 nbytes);
#endif


/***************************************************************************************************************************************//**

    Creates and initializes a generic data link.

    @param[in]  link        A pointer to a caller allocated data link to be initialized.
    @param[in]  write       A handler function called upon to transfer data for the data link.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The data link has been initialized.
     ERR_NULLREFERENCE      | The argument 'link' or 'write' was found to be NULL.

    @module     datalink

*******************************************************************************************************************************************/
STATUS DATALINK_Create(DATALINK* link, DATALINKWRITEHANDLER write, void* arg)
{
    STATUS status;
    
    
#if (CFG_NULLCHECKING)
    if (link == NULL) {
        return ERR_NULLREFERENCE;
    }
    
    if (write == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif
    
    link->encapsulate = FALSE;                                  /* No encapsulation by default */
    
    link->write = write;                                        /* Assign write handler and custom argument */
    link->writearg = arg;

    status = MUTEX_Create(&link->mutex,                         /* Create an underlying mutex for transfer synchronization */
                          "Data Link",                          /* Name for the mutex */
                          FALSE);                               /* Calling thread is not the initial owner */
    
    if (status != SUCCESS) {
        return status;
    }
    
    return SUCCESS;
}
    
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
STATUS DATALINK_EnableEncapsulation(DATALINK* link, void* decbuf, UINT32 decsize, void* encbuf, UINT32 encsize)
{
    STATUS status;
    
    
#if (CFG_NULLCHECKING)
    if (link == NULL) {
        return ERR_NULLREFERENCE;
    }
    
    if (decbuf == NULL) {
        return ERR_NULLREFERENCE;
    }
    
    if (encbuf == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif
    
    if (decsize == 0) {
        return ERR_INVALIDARGUMENT;
    }
    
    if (encsize == 0) {
        return ERR_INVALIDARGUMENT;
    }
    
    link->encapsulate = TRUE;                                   /* Signal that the link should use encapsulation */
    
    status = SLIP_CreateDecoder(&link->decoder,                 /* Initialize a decoder for decapsulating data */
                                decbuf,                         /* A pointer to the decoding buffer */
                                decsize,                        /* The size of the decoding buffer */
                                DATALINK_BytesDecoded,          /* A handler function called when data has been completely decapsulated */
                                link);                          /* Application-defined argument, the target data link */
    
    if (status != SUCCESS) {
        return status;
    }
    
    status = SLIP_CreateEncoder(&link->encoder,                 /* Initialize an encoder for encapsulating data */
                                encbuf,                         /* A pointer to the encoding buffer */
                                encsize,                        /* The size of the encoding buffer */
                                DATALINK_BytesEncoded,          /* A handler function called when done encapsulating, or buffer full */
                                link);                          /* Application-defined argument, the target data link */
    
    if (status != SUCCESS) {
        return status;
    }
    
    return SUCCESS;
}
#endif

/***************************************************************************************************************************************//**

    Deserializes data from a buffer into a value object.

    @param[in]  buffer      A pointer to the buffer that contains the serialized data.
    @param[in]  offset      A zero-based offset into the buffer.
    @param[out] value       A pointer to a caller allocated value object.
    @param[in]  nbytes      The size, in bytes, of the value to be deserialized.

    @return     The total number of bytes that have been deserialized.
    @module     datalink

*******************************************************************************************************************************************/
UINT32 DATALINK_Deserialize(const void* buffer, UINT32 offset, void* value, UINT32 nbytes)
{
    UINT32 k;
    
    
    for (k = 0; k < nbytes; k++) {
        ((BYTE*)value)[k] = ((BYTE*)buffer)[offset + k];
    }
    
    return nbytes;
}

/***************************************************************************************************************************************//**

    Serializes a value object into a buffer.

    @param[in]  buffer      A pointer to a buffer to receive the serialized values.
    @param[in]  offset      A zero-based offset into the buffer.
    @param[out] value       A pointer to the value to be serialized.
    @param[in]  nbytes      The size, in bytes, of the value to be serialized.

    @return     The total number of bytes that have been serialized and placed into the buffer.
    @module     datalink

*******************************************************************************************************************************************/
UINT32 DATALINK_Serialize(void* buffer, UINT32 offset, const void* value, UINT32 nbytes)
{
    UINT32 k;
    
    
    for (k = 0; k < nbytes; k++) {
        ((BYTE*)buffer)[offset + k] = ((BYTE*)value)[k];
    }
    
    return nbytes;
}

/***************************************************************************************************************************************//**

    A handler called when a request for link info has been received.

    @param[in]  link        A pointer to the link that received the reqest.
    @param[in]  data        A pointer to the received data.
    @param[in]  nbytes      The size, in bytes, of the given data.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The message has been handled.

    @module     datalink

*******************************************************************************************************************************************/
static STATUS DATALINK_HandleInfo(DATALINK* link, void* data, UINT32 nbytes)
{
    STATUS status;
    UINT32 offset;
    
    
    offset = sizeof(DATALINKID);
    offset += DATALINK_Serialize(data,                          /* Provide the protocol version for the link */
                                 offset, 
                                 &link->version, 
                                 sizeof(UINT32));
    
    status = DATALINK_Write(link, data, offset);                /* Transmit the response */
    if (status != SUCCESS) {
        return status;
    }
    
    return SUCCESS;
}

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

    @module     datalink

*******************************************************************************************************************************************/
STATUS DATALINK_Write(DATALINK* link, void* data, UINT32 nbytes)
{
    STATUS status;
    UINT32 len;
    
    
#if (CFG_NULLCHECKING)
    if (link == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif
    
    if (link->write == NULL) {
        return ERR_NOTSUPPORTED;                                /* No write handler for the data link */
    }
    
    len = nbytes;
    
    if (link->useCRC) {                                         /* Append a CRC value? */
#if (CFG_DATALINKCRC)
        DATALINK_AppendCRC(data, nbytes);                       /* Calculate and append the CRC value */
        len += sizeof(UINT32);                                  /* Account for the extra length of the CRC value */
#else
        return ERR_NOTSUPPORTED;                                /* CRC code is not included */
#endif
    }
    
    if (link->encapsulate) {                                    /* Encapsulate the message data? */
#if (CFG_DATALINKENCAPSULATION)
        SLIP_Encode(&link->encoder,                             /* Encapsulate by encoding with SLIP */
                    data,
                    len);
        
        return SUCCESS;
#else
        return ERR_NOTSUPPORTED;                                /* Encapsulation code is not included */
#endif
    }
    
    status = MUTEX_Acquire(&link->mutex, INFINITE);             /* Get exclusive access to the link before writing */
    if (status != SUCCESS) {
        return status;
    }
    
    status = link->write(link,                                  /* Call upon the configured handler for writing the message */
                         link->writearg,
                         data, 
                         len);      
    
    if (status != SUCCESS) {
        MUTEX_Release(&link->mutex);
        return status;
    }
    
    MUTEX_Release(&link->mutex);
    return SUCCESS;
}

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
STATUS DATALINK_ReceivedMessage(DATALINK* link, void* data, UINT32 nbytes)
{
    DATALINKID id;
    STATUS status;
    

    if (nbytes < sizeof(DATALINKID)) {
        return ERR_INVALIDARGUMENT;                             /* The message doesn't contain enough data */
    }
    
    if (link->useCRC) {                                         /* Validate the message using CRC? */
#if (CFG_DATALINKCRC)
        status = DATALINK_VerifyCRC(data, nbytes);              /* Check the CRC value */
        if (status != SUCCESS) {
            return status;                                      /* CRC failed */
        }
#else
        return ERR_NOTSUPPORTED;                                /* CRC is not supported (edit CFG_DATALINKCRC in datalink_cfg.h) */
#endif
    }
    
    DATALINK_Deserialize(data, 0, &id, sizeof(DATALINKID));     /* Deserialize the identifier */                   
    
    if (id.number == 0) {
        return DATALINK_HandleInfo(link, data, nbytes);         /* Request for link information */
    }
    
    status = DATALINK_HandleMessage(link, id, data, nbytes);    /* Handle the request within the generated link code */
    if (status != SUCCESS) {
        return status;
    }
    
    return SUCCESS;
}

#if (CFG_DATALINKENCAPSULATION)
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
STATUS DATALINK_ReceivedBytes(DATALINK* link, void* data, UINT32 nbytes)
{
    STATUS status;
    
    
#if (CFG_NULLCHECKING)
    if (link == NULL) {
        return ERR_NULLREFERENCE;
    }
    
    if (data == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif   
    
    status = SLIP_Decode(&link->decoder, data, nbytes);         /* Decode the data to recover the encapsulated message */
    if (status != SUCCESS) {
        return status;
    }
    
    return SUCCESS;
}

/***************************************************************************************************************************************//**

    A callback function that is called when uncapsulated data has been processed into a complete message. 

    @param[in]  decoder     A pointer to the decoder instance that completed decoding the uncapsulated data.
    @param[in]  arg         A pointer to the data link that received the message (a user argument for the decoder).
    @param[in]  data        A pointer to the data that has been decoded by the decoder.
    @param[in]  nbytes      The number of bytes that has been decoded.

    @return     None.
    @module     datalink

*******************************************************************************************************************************************/
static void DATALINK_BytesDecoded(SLIPDECODER* decoder, void* arg, const void* data, UINT32 nbytes)
{
    DATALINK_ReceivedMessage((DATALINK*)arg, (void*)data, nbytes);        /* Parse and process the received message */
}

/***************************************************************************************************************************************//**

    A callback function that is called when data has been encapsulated into a complete message. The message is then transferred over
    the data link.

    @param[in]  encoder     A pointer to the encoder instance that has encapsulated the data.
    @param[in]  arg         A pointer to the data link that is to transfer the encapsulated message (a user argument for the decoder).
    @param[in]  data        A pointer to the data that has been encoded by the encoder.
    @param[in]  nbytes      The number of bytes that has been encoded.

    @return     None.
    @module     datalink

*******************************************************************************************************************************************/
static void DATALINK_BytesEncoded(SLIPENCODER* encoder, void* arg, const void* data, UINT32 nbytes)
{
    DATALINK* link = (DATALINK*)arg;
    STATUS status;
    
    
    if (link == NULL) {
        return;
    }
    
    if (link->write == NULL) {
        return;
    }
    
    status = MUTEX_Acquire(&link->mutex, INFINITE);             /* Get exclusive access to the link before writing the message */
    if (status != SUCCESS) {
        return;
    }
    
    status = link->write(link,                                  /* Call upon the configured handler for writing */
                         link->writearg,
                         data, 
                         nbytes);      
    
    MUTEX_Release(&link->mutex);                                /* Release the exclusive access on the link */
    return;
}
#endif /* CFG_DATALINKENCAPSULATION */

#if (CFG_DATALINKCRC)
/***************************************************************************************************************************************//**

    Appends a cyclic redundancy check (CRC) value on a data link message. 

    @param[in]  data        A pointer to the message data to have a check value appended.
    @param[in]  nbytes      The size, in bytes, of the message data.

    @return     None.
    @module     datalink

*******************************************************************************************************************************************/
static void DATALINK_AppendCRC(void* data, UINT32 nbytes)
{
    UINT32 crc;
    
    
    crc = CRC32_Calculate(0, data, nbytes);                     /* Calculate the check value for the data */
    DATALINK_Serialize(data, nbytes, &crc, sizeof(UINT32));     /* Append the CRC to the end of the data */
}

/***************************************************************************************************************************************//**

    Verifies the cyclic redundancy check (CRC) value on a data link message. 

    @param[in]  data        A pointer to the message data to be verified.
    @param[in]  nbytes      The size, in bytes, of the message data to be verified.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The CRC value has been verified.
     ERR_NULLREFERENCE      | The argument 'data' was found to be NULL.
     ERR_CORRUPTED          | The CRC value did not match; the message data is considered corrupted.

    @module     datalink

*******************************************************************************************************************************************/
static STATUS DATALINK_VerifyCRC(const void* data, UINT32 nbytes)
{
    UINT32 crc;
    UINT32 check;
    
    
#if (CFG_NULLCHECKING)
    if (data == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif
    
    crc = CRC32_Calculate(0, data, nbytes - sizeof(UINT32));    /* Calculate the CRC value for the message */
    
    DATALINK_Deserialize(data,                                  /* Deserialize the received CRC value */
                         nbytes - sizeof(UINT32),
                         &check, 
                         sizeof(UINT32));
    
    if (crc != check) {                                         /* Compare the calculated value against the received value */
        return ERR_CORRUPTED;                                   /* Failed verification, invalid message */
    }
    
    return SUCCESS;                                             /* CRC value matched, message verified */
}
#endif /* CFG_DATALINKCRC */
