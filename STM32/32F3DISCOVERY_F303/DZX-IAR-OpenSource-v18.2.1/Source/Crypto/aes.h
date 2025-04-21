/*******************************************************************************************************************************************

    DZX | CRYPTO | AES                                                                                                    VERSION 18.2.1
    ------------------------------------------------------------------------------------------------------------------------------------

    This provides support for encrypting/decrypting data using the Advanced Encryption Standard (AES). This supports key sizes of 128,
    192 or 256. Only supports CBC mode.

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
#ifndef AES_H__
#define AES_H__

#include "Kernel/kernel.h"

/*******************************************************************************************************************************************
    DEFINITIONS
*******************************************************************************************************************************************/
#define AES_BLOCKSIZE           128     /**< AES block size in bits */
#define AES_BLOCKBYTES          16      /**< AES block size in bytes */
#define AES_BLOCKWORDS          4       /**< AES block size in 32-bit words */
#define AES_MAXKEYBYTES         32      /**< Maximum size of a key in bytes */
#define AES_NCOLS               4       /**< Number of columns within a AES block */
#define AES_NROWS               4       /**< Number of rows within an AES block */

/*******************************************************************************************************************************************
    TYPE DEFINITIONS
*******************************************************************************************************************************************/
typedef struct AES AES;
typedef BYTE AESSTATE[AES_NROWS][AES_NCOLS];

/***************************************************************************************************************************************//**

    An instance of the Advanced Encryption Standard (AES).
    @module     crypto-aes

*******************************************************************************************************************************************/
struct AES {
    UINT32      keysize;                    /**< The size of the key in bits (must be 128, 192 or 256) */
    BYTE        key[AES_MAXKEYBYTES];       /**< The value of the key */
    BYTE        iv[AES_BLOCKBYTES];         /**< The value of the initialization vector */
    AESSTATE*   state;                      /**< A pointer to the current state */
    BYTE        rkey[240];                  /**< The values for the round keys */
};

/*******************************************************************************************************************************************
    PUBLIC FUNCTIONS
*******************************************************************************************************************************************/
/***************************************************************************************************************************************//**

    Initializes an instance of the Advanced Encryption Standard (AES) cipher.

    @param[in]  aes         A pointer to a caller allocated instance to be initialized.
    @param[in]  keysize     The size of the key in bits. Must be 128, 192 or 256.
    @param[in]  key         A pointer to the key value.
    @param[in]  iv          A poniter to the initialization vector value.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The provided instance was successfully initialized.
     ERR_NULLREFERENCE      | The argument 'aes', 'key' or 'iv' was found to be NULL.
     ERR_NOTSUPPORTED       | The specified key size is not supported.

    @module     crypto-aes

*******************************************************************************************************************************************/
extern STATUS AES_Init(AES* aes, UINT32 keysize, const BYTE* key, const BYTE* iv);

/***************************************************************************************************************************************//**

    Encrypts data in-place using the Advanced Encryption Standard (AES) cipher.

    @param[in]  aes         A pointer to a caller allocated and initialized instance.
    @param[out] buf         A pointer to the data to be encrypted.
    @param[in]  nbytes      The total number of bytes to be encrypted. Must be padded to the AES block size of 16-bytes.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The data has been successfully encrypted.
     ERR_NULLREFERENCE      | The argument 'aes' or 'buf' was found to be NULL.
     ERR_ALIGNMENT          | The amount of data must be padded to the AES block size of 16-bytes.

    @module     crypto-aes

*******************************************************************************************************************************************/
extern STATUS AES_Encrypt(AES* aes, void* buf, UINT32 nbytes);

/***************************************************************************************************************************************//**

    Decrypts data in-place using the Advanced Encryption Standard (AES) cipher.

    @param[in]  aes         A pointer to a caller allocated and initialized instance.
    @param[out] buf         A pointer to the data to be decrypted.
    @param[in]  nbytes      The total number of bytes to be decrypted. Must be padded to the AES block size of 16-bytes.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The data has been successfully decrypted.
     ERR_NULLREFERENCE      | The argument 'aes' or 'buf' was found to be NULL.
     ERR_ALIGNMENT          | The amount of data must be padded to the AES block size of 16-bytes.

    @module     crypto-aes

*******************************************************************************************************************************************/
extern STATUS AES_Decrypt(AES* aes, void* buf, UINT32 nbytes);

#endif /* AES_H__ */
