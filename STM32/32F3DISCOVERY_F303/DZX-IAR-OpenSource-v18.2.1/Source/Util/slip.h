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
#include "Kernel/kernel.h"

#ifndef SLIP_H__
#define SLIP_H__

/*******************************************************************************************************************************************
    SPECIAL CHARACTERS
*******************************************************************************************************************************************/
#define SLIPEND         0xC0
#define SLIPESC         0xDB
#define SLIPESCEND      0xDC
#define SLIPESCESC      0xDD

/*******************************************************************************************************************************************
    TYPE DEFINITIONS
*******************************************************************************************************************************************/
typedef struct SLIPDECODER SLIPDECODER;
typedef struct SLIPENCODER SLIPENCODER;

/***************************************************************************************************************************************//**

    Represents a handler function that is called when a SLIP decoder has completed decapsulating data.

    @param[in]  decoder     A pointer to the decoder instance that has completed decapsulation of data.
    @param[in]  arg         A pointer to an application-defined argument. Can be NULL.
    @param[in]  data        A pointer to the resulting decapsulated data.
    @param[in]  nbytes      The size of the data, in bytes.

    @return     None.
    @module     slip

*******************************************************************************************************************************************/
typedef void (*SLIPDECODERHANDLER)(SLIPDECODER* decoder, void* arg, const void* data, UINT32 nbytes);

/***************************************************************************************************************************************//**

    Represents a handler function that is called when a SLIP encoder has completed encapsulation of data, or when the encoder's buffer
    is full.

    @param[in]  encoder     A pointer to the decoder instance that has completed encapsulation.
    @param[in]  arg         A pointer to an application-defined argument. Can be NULL.
    @param[in]  data        A pointer to the resulting encapsulated data.
    @param[in]  nbytes      The size of the data, in bytes.

    @return     None.
    @module     slip

*******************************************************************************************************************************************/
typedef void (*SLIPENCODERHANDLER)(SLIPENCODER* encoder, void* arg, const void* data, UINT32 nbytes);
                   
/*******************************************************************************************************************************************

    Represents a decoder for decapsulating a stream of data.
    @module     slip

*******************************************************************************************************************************************/
struct SLIPDECODER {
    void* buffer;                   /**< A pointer to an underlying buffer to hold decapsulated data. */
    UINT32 bufsize;                 /**< The size, in bytes, of the underlying buffer. */
    UINT32 nbytes;                  /**< The number of bytes currently contained within the buffer. */
    SLIPDECODERHANDLER handler;     /**< A handler function called upon completion. */
    void* arg;                      /**< An application-defined argument provided to the handler function. */
    SLIPDECODERHANDLER overflow;
    BOOLEAN escaped;                /**< An indication of whether the decoder has previously received an escape character. */
    UINT32 errors;                  /**< A count of errors that have occurred while decoding data. */
};

/*******************************************************************************************************************************************

    Represents an encoder for encapsulating a stream of data.
    @module     slip

*******************************************************************************************************************************************/
struct SLIPENCODER {
    void* buffer;                   /**< A pointer to an underlying buffer to hold encapsulated data. */
    UINT32 bufsize;                 /**< The size, in bytes, of the underlying buffer. */ 
    UINT32 nbytes;                  /**< The number of bytes currently contained within the buffer. */
    SLIPENCODERHANDLER handler;     /**< A handler function called upon completion and buffer full. */
    void* arg;                      /**< An application-defined argument provided to the handler function. */
};

/*******************************************************************************************************************************************
    PUBLIC FUNCTIONS
*******************************************************************************************************************************************/
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
extern STATUS SLIP_CreateDecoder(SLIPDECODER* decoder, void* buffer, UINT32 bufsize, SLIPDECODERHANDLER handler, void* arg);

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
extern STATUS SLIP_Decode(SLIPDECODER* decoder, const void* data, UINT32 nbytes);

/***************************************************************************************************************************************//**

    Returns the number of errors that have occurred during decoding of data.

    @param[in]  decoder     A pointer to the target decoder instance.

    @return     The number of errors that have occurred while decoding data.
    @module     slip

*******************************************************************************************************************************************/
extern UINT32 SLIP_DecoderErrors(SLIPDECODER* decoder);

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
extern STATUS SLIP_CreateEncoder(SLIPENCODER* encoder, void* buffer, UINT32 bufsize, SLIPENCODERHANDLER handler, void* arg);

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
extern STATUS SLIP_Encode(SLIPENCODER* encoder, const void* data, UINT32 nbytes);
                                   
#endif /* SLIP_H__ */
