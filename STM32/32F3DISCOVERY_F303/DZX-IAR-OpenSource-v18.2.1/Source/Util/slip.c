/*******************************************************************************************************************************************

    DZX | UTIL | SLIP                                                                                                     VERSION 18.2.1
    ------------------------------------------------------------------------------------------------------------------------------------

    This provides methods for encapsulating a stream of data using the Serial Line Internet Protocol (SLIP) (RFC 1055).

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
#include "Util/slip.h"

/*******************************************************************************************************************************************
    PRIVATE FUNCTIONS
*******************************************************************************************************************************************/
static void SLIP_DecodeValue(SLIPDECODER* decoder, BYTE value);
static void SLIP_DecodeComplete(SLIPDECODER* decoder);
static void SLIP_BufferDecodedValue(SLIPDECODER* decoder, BYTE value);
static void SLIP_BufferEncodedValue(SLIPENCODER* encoder, BYTE value);
static void SLIP_EncodeComplete(SLIPENCODER* encoder);

/***************************************************************************************************************************************//**

    Creates and initializes a decoder for decapsulating a data stream.

    @param[in]  decoder     A pointer to a caller allocated decoder instance to be initialized.
    @param[in]  buffer      A pointer to a caller allocated buffer to hold the decapsulated data. Must be large enough to hold an
                            entire decapsulated message.
    @param[in]  bufsize     The size, in bytes, of the provided buffer.
    @param[in]  handler     A handler function that is called when the data has been completely decapsulated.
    @param[in]  arg         An application-defined argument that is passed to the provided handler function. Can be NULL.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The decoder has been initialized.
     ERR_NULLREFERENCE      | The argument 'decoder' or 'buffer' was found to be NULL.
     ERR_INVALIDARGUMENT    | The argument 'bufsize' was invalid. Must be larger than zero.

    @module     slip

*******************************************************************************************************************************************/
STATUS SLIP_CreateDecoder(SLIPDECODER* decoder, void* buffer, UINT32 bufsize, SLIPDECODERHANDLER handler, void* arg)
{
#if (CFG_NULLCHECKING)
    if (decoder == NULL) {
        return ERR_NULLREFERENCE;
    }
    
    if (buffer == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif
    
    if (bufsize == 0) {
        return ERR_INVALIDARGUMENT;
    }
    
    decoder->buffer = buffer;
    decoder->bufsize = bufsize;
    decoder->handler = handler; 
    decoder->arg = arg;
    
    return SUCCESS;
}

/***************************************************************************************************************************************//**

    Decodes and decapsulates data from a data stream.

    @param[in]  decoder     A pointer to an initialized decoder instance.
    @param[in]  data        A pointer to the encapsulated data to be decoded.
    @param[in]  nbytes      The size, in bytes, of the provided data.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The data has been decoded.
     ERR_NULLREFERENCE      | The argument 'decoder' or 'data' was found to be NULL.

    @module     slip

*******************************************************************************************************************************************/
STATUS SLIP_Decode(SLIPDECODER* decoder, const void* data, UINT32 nbytes)
{
    UINT32 k;
    
    
#if (CFG_NULLCHECKING)
    if (decoder == NULL) {
        return ERR_NULLREFERENCE;
    }
    
    if (data == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif
    
    for (k = 0; k < nbytes; k++) {
        SLIP_DecodeValue(decoder, ((BYTE*)data)[k]);            /* Decode each byte */
    }
    
    return SUCCESS;
}
        
/***************************************************************************************************************************************//**

    Returns the number of errors that have occurred during decoding of data.

    @param[in]  decoder     A pointer to the target decoder instance.

    @return     The number of errors that have occurred while decoding data.
    @module     slip

*******************************************************************************************************************************************/
UINT32 SLIP_DecoderErrors(SLIPDECODER* decoder)
{
#if (CFG_NULLCHECKING)
    if (decoder == NULL) {
        return 0;
    }
#endif
    
    return decoder->errors;
}

/***************************************************************************************************************************************//**

    Creates and initializes an encoder for encapsulating a data stream.

    @param[in]  decoder     A pointer to a caller allocated encoder instance to be initialized.
    @param[in]  buffer      A pointer to a caller allocated buffer to temporarily hold the encapsulated data. Does not have to be large 
                            enough to fit an entire encapsulated message, as the handler function will be called upon a full buffer.
    @param[in]  bufsize     The size, in bytes, of the provided buffer.
    @param[in]  handler     A handler function that is called when the data has been completely encapsulated, or when the provided buffer
                            is full.
    @param[in]  arg         An application-defined argument that is passed to the provided handler function. Can be NULL.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The encoder has been initialized.
     ERR_NULLREFERENCE      | The argument 'encoder' or 'buffer' was found to be NULL.
     ERR_INVALIDARGUMENT    | The argument 'bufsize' was invalid. Must be larger than zero.

    @module     slip

*******************************************************************************************************************************************/
STATUS SLIP_CreateEncoder(SLIPENCODER* encoder, void* buffer, UINT32 bufsize, SLIPENCODERHANDLER handler, void* arg)
{
#if (CFG_NULLCHECKING)
    if (encoder == NULL) {
        return ERR_NULLREFERENCE;
    }
    
    if (buffer == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif
    
    if (bufsize == 0) {
        return ERR_INVALIDARGUMENT;
    }
    
    encoder->buffer = buffer;
    encoder->bufsize = bufsize;
    encoder->handler = handler;
    encoder->arg = arg;
    
    return SUCCESS;
}

/***************************************************************************************************************************************//**

    Encodes and encapsulates data for a data stream.

    @param[in]  encoder     A pointer to an initialized encoder instance.
    @param[in]  data        A pointer to the data to be encoded and encapsulated.
    @param[in]  nbytes      The size, in bytes, of the provided data.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The data has been encoded and encapsulated.
     ERR_NULLREFERENCE      | The argument 'encoder' or 'data' was found to be NULL.

    @module     slip

*******************************************************************************************************************************************/
STATUS SLIP_Encode(SLIPENCODER* encoder, const void* data, UINT32 nbytes)
{
    UINT32 k;
    BYTE value;
    
    
#if (CFG_NULLCHECKING)
    if (encoder == NULL) {
        return ERR_NULLREFERENCE;
    }
    
    if (data == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif
    
    for (k = 0; k < nbytes; k++) {                              /* Encode each data byte */
        
        value = ((BYTE*)data)[k];
        
        switch (value) {
            case SLIPESC:                                       /* The value is the ESC character, escape it */
                SLIP_BufferEncodedValue(encoder, SLIPESC);
                SLIP_BufferEncodedValue(encoder, SLIPESCESC);
                break;
            
            case SLIPEND:
                SLIP_BufferEncodedValue(encoder, SLIPESC);      /* The value is the END character, escape it */
                SLIP_BufferEncodedValue(encoder, SLIPESCEND);
                break;
                
            default:
                SLIP_BufferEncodedValue(encoder, value);        /* No special encoding */
                break;
        }
    }
                
    SLIP_BufferEncodedValue(encoder, SLIPEND);                  /* Append end-of-message character */
    
    if (encoder->nbytes > 0) {                                  /* Notify of the end, if neccessary */
        SLIP_EncodeComplete(encoder);               
    }
    
    return SUCCESS;
}

/***************************************************************************************************************************************//**

    Decodes and decapsulates a single data byte.

    @param[in]  decoder     A pointer to an initialized decoder instance.
    @param[in]  value       The data byte to be decoded.

    @return     None.
    @module     internal

*******************************************************************************************************************************************/
static void SLIP_DecodeValue(SLIPDECODER* decoder, BYTE value)
{
    if (decoder->escaped) {                                     /* Previous value was an escape? */
        
        switch (value) {
            case SLIPESCESC:
                SLIP_BufferDecodedValue(decoder, SLIPESC);      /* Found an escaped ESC character */
                break;
            case SLIPESCEND:
                SLIP_BufferDecodedValue(decoder, SLIPEND);      /* Found an escaped END character */
                break;
            default:
                ++decoder->errors;                              /* Found an unsupported escaped character, note and move on */
                break;
        }
        
        decoder->escaped = FALSE;                               /* Done with escaped character */
        
    } else {
    
        switch (value) {
            case SLIPEND:
                SLIP_DecodeComplete(decoder);                   /* Found end-of-message character */
                break;
            case SLIPESC:
                decoder->escaped = TRUE;                        /* Escape character, next character is special */
                break;
            default:
                SLIP_BufferDecodedValue(decoder, value);        /* Regular value */
                break;
        }
    }
}

/***************************************************************************************************************************************//**

    Places a decoded data byte into a decoder's buffer.

    @param[in]  decoder     A pointer to an initialized decoder instance.
    @param[in]  value       The data byte to be buffered.

    @return     None.
    @module     internal

*******************************************************************************************************************************************/
static void SLIP_BufferDecodedValue(SLIPDECODER* decoder, BYTE value)
{
    if (decoder->nbytes >= decoder->bufsize) {                  /* Check for overflow */
        ++decoder->errors;                                      /* Decoder's buffer cannot hold anymore, note error */
        decoder->nbytes--;                                      /* Throw out most recent data in place for the latest */
    }
    
    ((BYTE*)decoder->buffer)[decoder->nbytes++] = value;        /* Place the value into the buffer */
}

/***************************************************************************************************************************************//**

    Called when a decoder has completed decoded and decapsulated a stream of data.

    @param[in]  decoder     A pointer to the target decoder instance.

    @return     None.
    @module     internal

*******************************************************************************************************************************************/
static void SLIP_DecodeComplete(SLIPDECODER* decoder)
{
    if (decoder->handler) {                                     /* A valid handler function? */
        decoder->handler(decoder,                               /* Call the decode complete handler function */
                         decoder->arg,
                         decoder->buffer, 
                         decoder->nbytes);
    }
    
    decoder->nbytes = 0;                                        /* Reset the decoder */
}

/***************************************************************************************************************************************//**

    Places an encoded data byte into a encoder's buffer.

    @param[in]  decoder     A pointer to an initialized decoder instance.
    @param[in]  value       The data byte to be buffered.

    @return     None.
    @module     internal

*******************************************************************************************************************************************/
static void SLIP_BufferEncodedValue(SLIPENCODER* encoder, BYTE value)
{
    if (encoder->nbytes >= encoder->bufsize) {
        SLIP_EncodeComplete(encoder);                           /* Notify handler that buffer is full */
    }
    
    ((BYTE*)encoder->buffer)[encoder->nbytes++] = value;
}

/***************************************************************************************************************************************//**

    Called when an encoder has completely encoded and encapsulated a stream of data, or when the encoder's buffer is full.

    @param[in]  encoder     A pointer to the target encoder instance.

    @return     None.
    @module     internal

*******************************************************************************************************************************************/
static void SLIP_EncodeComplete(SLIPENCODER* encoder)
{
    if (encoder->handler) {
        encoder->handler(encoder, 
                         encoder->arg,
                         encoder->buffer, 
                         encoder->nbytes);
    }
    
    encoder->nbytes = 0;
}
