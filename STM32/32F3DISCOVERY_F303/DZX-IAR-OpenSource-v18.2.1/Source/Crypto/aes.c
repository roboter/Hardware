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
#include "aes.h"
#include <string.h>

/*******************************************************************************************************************************************
    LOCAL DEFINITIONS
*******************************************************************************************************************************************/
#define AES_CYCLES(aes)         ((aes->keysize == 128) ? 10 : ((aes->keysize == 192) ? 12 : 14))  /**< Gets the required number of cycles */
#define AES_KEYBYTES(aes)       (aes->keysize >> 3)         /**< Gets the key size in bytes (divide by 8) */
#define AES_KEYWORDS(aes)       (aes->keysize >> 5)         /**< Gets the key size in 32-bit words (divide by 32) */

/***************************************************************************************************************************************//**

    A lookup table to perform the forward S-box operation.
    @module     internal

*******************************************************************************************************************************************/
ALIGNED(4) const BYTE AES_FSBOX[256] = {
    0x63, 0x7C, 0x77, 0x7B, 0xF2, 0x6B, 0x6F, 0xC5, 0x30, 0x01, 0x67, 0x2B, 0xFE, 0xD7, 0xAB, 0x76,
    0xCA, 0x82, 0xC9, 0x7D, 0xFA, 0x59, 0x47, 0xF0, 0xAD, 0xD4, 0xA2, 0xAF, 0x9C, 0xA4, 0x72, 0xC0,
    0xB7, 0xFD, 0x93, 0x26, 0x36, 0x3F, 0xF7, 0xCC, 0x34, 0xA5, 0xE5, 0xF1, 0x71, 0xD8, 0x31, 0x15,
    0x04, 0xC7, 0x23, 0xC3, 0x18, 0x96, 0x05, 0x9A, 0x07, 0x12, 0x80, 0xE2, 0xEB, 0x27, 0xB2, 0x75,
    0x09, 0x83, 0x2C, 0x1A, 0x1B, 0x6E, 0x5A, 0xA0, 0x52, 0x3B, 0xD6, 0xB3, 0x29, 0xE3, 0x2F, 0x84,
    0x53, 0xD1, 0x00, 0xED, 0x20, 0xFC, 0xB1, 0x5B, 0x6A, 0xCB, 0xBE, 0x39, 0x4A, 0x4C, 0x58, 0xCF,
    0xD0, 0xEF, 0xAA, 0xFB, 0x43, 0x4D, 0x33, 0x85, 0x45, 0xF9, 0x02, 0x7F, 0x50, 0x3C, 0x9F, 0xA8,
    0x51, 0xA3, 0x40, 0x8F, 0x92, 0x9D, 0x38, 0xF5, 0xBC, 0xB6, 0xDA, 0x21, 0x10, 0xFF, 0xF3, 0xD2,
    0xCD, 0x0C, 0x13, 0xEC, 0x5F, 0x97, 0x44, 0x17, 0xC4, 0xA7, 0x7E, 0x3D, 0x64, 0x5D, 0x19, 0x73,
    0x60, 0x81, 0x4F, 0xDC, 0x22, 0x2A, 0x90, 0x88, 0x46, 0xEE, 0xB8, 0x14, 0xDE, 0x5E, 0x0B, 0xDB,
    0xE0, 0x32, 0x3A, 0x0A, 0x49, 0x06, 0x24, 0x5C, 0xC2, 0xD3, 0xAC, 0x62, 0x91, 0x95, 0xE4, 0x79,
    0xE7, 0xC8, 0x37, 0x6D, 0x8D, 0xD5, 0x4E, 0xA9, 0x6C, 0x56, 0xF4, 0xEA, 0x65, 0x7A, 0xAE, 0x08,
    0xBA, 0x78, 0x25, 0x2E, 0x1C, 0xA6, 0xB4, 0xC6, 0xE8, 0xDD, 0x74, 0x1F, 0x4B, 0xBD, 0x8B, 0x8A,
    0x70, 0x3E, 0xB5, 0x66, 0x48, 0x03, 0xF6, 0x0E, 0x61, 0x35, 0x57, 0xB9, 0x86, 0xC1, 0x1D, 0x9E,
    0xE1, 0xF8, 0x98, 0x11, 0x69, 0xD9, 0x8E, 0x94, 0x9B, 0x1E, 0x87, 0xE9, 0xCE, 0x55, 0x28, 0xDF,
    0x8C, 0xA1, 0x89, 0x0D, 0xBF, 0xE6, 0x42, 0x68, 0x41, 0x99, 0x2D, 0x0F, 0xB0, 0x54, 0xBB, 0x16 
};

/***************************************************************************************************************************************//**

    A lookup table to perform the reverse S-box operation.
    @module     internal

*******************************************************************************************************************************************/
ALIGNED(4) const BYTE AES_RSBOX[256] = { 
    0x52, 0x09, 0x6A, 0xD5, 0x30, 0x36, 0xA5, 0x38, 0xBF, 0x40, 0xA3, 0x9E, 0x81, 0xF3, 0xD7, 0xFB,
    0x7C, 0xE3, 0x39, 0x82, 0x9B, 0x2F, 0xFF, 0x87, 0x34, 0x8E, 0x43, 0x44, 0xC4, 0xDE, 0xE9, 0xCB,
    0x54, 0x7B, 0x94, 0x32, 0xA6, 0xC2, 0x23, 0x3D, 0xEE, 0x4C, 0x95, 0x0B, 0x42, 0xFA, 0xC3, 0x4E,
    0x08, 0x2E, 0xA1, 0x66, 0x28, 0xD9, 0x24, 0xB2, 0x76, 0x5B, 0xA2, 0x49, 0x6D, 0x8B, 0xD1, 0x25,
    0x72, 0xF8, 0xF6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xD4, 0xA4, 0x5C, 0xCC, 0x5D, 0x65, 0xB6, 0x92,
    0x6C, 0x70, 0x48, 0x50, 0xFD, 0xED, 0xB9, 0xDA, 0x5E, 0x15, 0x46, 0x57, 0xA7, 0x8D, 0x9D, 0x84,
    0x90, 0xD8, 0xAB, 0x00, 0x8C, 0xBC, 0xD3, 0x0A, 0xF7, 0xE4, 0x58, 0x05, 0xB8, 0xB3, 0x45, 0x06,
    0xD0, 0x2C, 0x1E, 0x8F, 0xCA, 0x3F, 0x0F, 0x02, 0xC1, 0xAF, 0xBD, 0x03, 0x01, 0x13, 0x8A, 0x6B,
    0x3A, 0x91, 0x11, 0x41, 0x4F, 0x67, 0xDC, 0xEA, 0x97, 0xF2, 0xCF, 0xCE, 0xF0, 0xB4, 0xE6, 0x73,
    0x96, 0xAC, 0x74, 0x22, 0xE7, 0xAD, 0x35, 0x85, 0xE2, 0xF9, 0x37, 0xE8, 0x1C, 0x75, 0xDF, 0x6E,
    0x47, 0xF1, 0x1A, 0x71, 0x1D, 0x29, 0xC5, 0x89, 0x6F, 0xB7, 0x62, 0x0E, 0xAA, 0x18, 0xBE, 0x1B,
    0xFC, 0x56, 0x3E, 0x4B, 0xC6, 0xD2, 0x79, 0x20, 0x9A, 0xDB, 0xC0, 0xFE, 0x78, 0xCD, 0x5A, 0xF4,
    0x1F, 0xDD, 0xA8, 0x33, 0x88, 0x07, 0xC7, 0x31, 0xB1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xEC, 0x5F,
    0x60, 0x51, 0x7F, 0xA9, 0x19, 0xB5, 0x4A, 0x0D, 0x2D, 0xE5, 0x7A, 0x9F, 0x93, 0xC9, 0x9C, 0xEF,
    0xA0, 0xE0, 0x3B, 0x4D, 0xAE, 0x2A, 0xF5, 0xB0, 0xC8, 0xEB, 0xBB, 0x3C, 0x83, 0x53, 0x99, 0x61,
    0x17, 0x2B, 0x04, 0x7E, 0xBA, 0x77, 0xD6, 0x26, 0xE1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0C, 0x7D 
};

/***************************************************************************************************************************************//**

    A lookup table used to perform the exponentiation of 2 to a user-specified value.
    @module     internal

*******************************************************************************************************************************************/
ALIGNED(4) const BYTE AES_RCON[256] = {
    0x8D, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1B, 0x36, 0x6C, 0xD8, 0xAB, 0x4D, 0x9A, 
    0x2F, 0x5E, 0xBC, 0x63, 0xC6, 0x97, 0x35, 0x6A, 0xD4, 0xB3, 0x7D, 0xFA, 0xEF, 0xC5, 0x91, 0x39, 
    0x72, 0xE4, 0xD3, 0xBD, 0x61, 0xC2, 0x9F, 0x25, 0x4A, 0x94, 0x33, 0x66, 0xCC, 0x83, 0x1D, 0x3A, 
    0x74, 0xE8, 0xCB, 0x8D, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1B, 0x36, 0x6C, 0xD8, 
    0xAB, 0x4D, 0x9A, 0x2F, 0x5E, 0xBC, 0x63, 0xC6, 0x97, 0x35, 0x6A, 0xD4, 0xB3, 0x7D, 0xFA, 0xEF, 
    0xC5, 0x91, 0x39, 0x72, 0xE4, 0xD3, 0xBD, 0x61, 0xC2, 0x9F, 0x25, 0x4A, 0x94, 0x33, 0x66, 0xCC, 
    0x83, 0x1D, 0x3A, 0x74, 0xE8, 0xCB, 0x8D, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1B, 
    0x36, 0x6C, 0xD8, 0xAB, 0x4D, 0x9A, 0x2F, 0x5E, 0xBC, 0x63, 0xC6, 0x97, 0x35, 0x6A, 0xD4, 0xB3, 
    0x7D, 0xFA, 0xEF, 0xC5, 0x91, 0x39, 0x72, 0xE4, 0xD3, 0xBD, 0x61, 0xC2, 0x9F, 0x25, 0x4A, 0x94, 
    0x33, 0x66, 0xCC, 0x83, 0x1D, 0x3A, 0x74, 0xE8, 0xCB, 0x8D, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 
    0x40, 0x80, 0x1B, 0x36, 0x6C, 0xD8, 0xAB, 0x4D, 0x9A, 0x2F, 0x5E, 0xBC, 0x63, 0xC6, 0x97, 0x35, 
    0x6A, 0xD4, 0xB3, 0x7D, 0xFA, 0xEF, 0xC5, 0x91, 0x39, 0x72, 0xE4, 0xD3, 0xBD, 0x61, 0xC2, 0x9F, 
    0x25, 0x4A, 0x94, 0x33, 0x66, 0xCC, 0x83, 0x1D, 0x3A, 0x74, 0xE8, 0xCB, 0x8D, 0x01, 0x02, 0x04, 
    0x08, 0x10, 0x20, 0x40, 0x80, 0x1B, 0x36, 0x6C, 0xD8, 0xAB, 0x4D, 0x9A, 0x2F, 0x5E, 0xBC, 0x63, 
    0xC6, 0x97, 0x35, 0x6A, 0xD4, 0xB3, 0x7D, 0xFA, 0xEF, 0xC5, 0x91, 0x39, 0x72, 0xE4, 0xD3, 0xBD, 
    0x61, 0xC2, 0x9F, 0x25, 0x4A, 0x94, 0x33, 0x66, 0xCC, 0x83, 0x1D, 0x3A, 0x74, 0xE8, 0xCB, 0x8D  
};


/*******************************************************************************************************************************************
    PRIVATE FUNCTIONS
*******************************************************************************************************************************************/
static void AES_ExpandKey(AES* aes);
static void AES_AddRoundKey(AES* aes, BYTE round);
static BYTE AES_Xtime(BYTE x);
static void AES_SubBytes(AES* aes);
static void AES_ShiftRows(AES* aes);
static void AES_MixColumns(AES* aes);
static void AES_InvSubBytes(AES* aes);
static void AES_InvShiftRows(AES* aes);
static BYTE AES_Mult(BYTE x, BYTE y);
static void AES_InvMixColumns(AES* aes);


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
STATUS AES_Init(AES* aes, UINT32 keysize, const BYTE* key, const BYTE* iv)
{
#if (CFG_NULLCHECKING)
    if (aes == NULL) {
        return ERR_NULLREFERENCE;
    }
    
    if (key == NULL) {
        return ERR_NULLREFERENCE;
    }
    
    if (iv == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif
    
    if (keysize != 128 && keysize != 192 && keysize != 256) {   /* Verify a supported key size */
        return ERR_NOTSUPPORTED;
    }
        
    aes->keysize = keysize;                                     /* Assign the key size */
    memcpy(aes->key, key, AES_KEYBYTES(aes));                   /* Copy in the key value */
    memcpy(aes->iv, iv, AES_BLOCKBYTES);                        /* Copy in the iv value */
    
    AES_ExpandKey(aes);                                         /* Create the internal round keys */
    
    return SUCCESS;
}

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
STATUS AES_Encrypt(AES* aes, void* buf, UINT32 nbytes)
{
    UINT32 i;
    UINT32 k;
    
    
#if (CFG_NULLCHECKING)
    if (aes == NULL) {
        return ERR_NULLREFERENCE;
    }
    
    if (buf == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif
    
    if (nbytes % AES_BLOCKBYTES) {
        return ERR_ALIGNMENT;
    }

    for (i = 0; i < nbytes; i += AES_BLOCKBYTES) {                  /* Process the data in blocks */
        
        for (k = 0; k < AES_BLOCKBYTES; k++) {                      /* Perform initial XOR */
            ((BYTE*)buf)[i + k] ^= aes->iv[k];
        }
        
        aes->state = (AESSTATE*)&((BYTE*)buf)[i];                   /* Assign the new state to work on */
        
        AES_AddRoundKey(aes, 0);                                    /* Perform the cipher operation */
    
        for (k = 1; k < AES_CYCLES(aes); k++) {
            AES_SubBytes(aes);
            AES_ShiftRows(aes);
            AES_MixColumns(aes);
            
            AES_AddRoundKey(aes, k);
        }
        
        AES_SubBytes(aes);
        AES_ShiftRows(aes);   
        AES_AddRoundKey(aes, AES_CYCLES(aes));
        
        memcpy(aes->iv, aes->state, AES_BLOCKBYTES);                /* Set the IV for the next block */
    }
    
    return SUCCESS;
}

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
STATUS AES_Decrypt(AES* aes, void* buf, UINT32 nbytes)
{
    UINT32 i;
    UINT32 k;
    BYTE temp[AES_BLOCKBYTES];
    
    
#if (CFG_NULLCHECKING)
    if (aes == NULL) {
        return ERR_NULLREFERENCE;
    }
    
    if (buf == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif
    
    if (nbytes % AES_BLOCKBYTES) {
        return ERR_ALIGNMENT;
    }
    
    for (i = 0; i < nbytes; i += AES_BLOCKBYTES) {              /* Process the data in blocks */

        memcpy(temp, &((BYTE*)buf)[i], AES_BLOCKBYTES);         /* Capture some more raw data for later use */
        
        aes->state = (AESSTATE*)&((BYTE*)buf)[i];               /* Assign the new state to work on */
        
        
        AES_AddRoundKey(aes, AES_CYCLES(aes));                  /* Perform the cipher operation */    
    
        for (k = AES_CYCLES(aes) - 1; k > 0; k--) {
            AES_InvShiftRows(aes);
            AES_InvSubBytes(aes);
            AES_AddRoundKey(aes, k);
            
            AES_InvMixColumns(aes);
        }

        AES_InvShiftRows(aes);
        AES_InvSubBytes(aes);
        AES_AddRoundKey(aes, 0);

                                
        for (k = 0; k < AES_BLOCKBYTES; k++) {                  /* Reverse XOR */
            ((BYTE*)buf)[i + k] ^= aes->iv[k];
        }
        
        
        memcpy(aes->iv, temp, AES_BLOCKBYTES);
    }
    
    return SUCCESS;
}

/***************************************************************************************************************************************//**

    Derives the round keys from the cipher key using Rijndael's key schedule.

    @param[in]  aes         A pointer to the cipher instance.

    @return     None
    @module     internal

*******************************************************************************************************************************************/
static void AES_ExpandKey(AES* aes)
{
    UINT32 i;
    UINT32 j;
    UINT32 k;
    BYTE temp[4];
    
    
    memcpy(aes->rkey, aes->key, AES_KEYBYTES(aes));             /* Start with the actual key */

    for (i = AES_KEYWORDS(aes); i < (AES_NCOLS * (AES_CYCLES(aes) + 1)); i++) {
        for (j = 0; j < 4; j++) {
            temp[j] = aes->rkey[(i-1) * 4 + j];
        }
        
        if ((i % AES_KEYWORDS(aes)) == 0) {
            
            /* Rotate to the left */
            k = temp[0];
            temp[0] = temp[1];
            temp[1] = temp[2];
            temp[2] = temp[3];
            temp[3] = k;
            
            /* Subword */
            temp[0] = AES_FSBOX[temp[0]];
            temp[1] = AES_FSBOX[temp[1]];
            temp[2] = AES_FSBOX[temp[2]];
            temp[3] = AES_FSBOX[temp[3]];
            
            temp[0] = temp[0] ^ AES_RCON[i/AES_KEYWORDS(aes)];
            
        } else if (AES_KEYWORDS(aes) > 6 && (i % AES_KEYWORDS(aes)) == 4) {
            
            temp[0] = AES_FSBOX[temp[0]];
            temp[1] = AES_FSBOX[temp[1]];
            temp[2] = AES_FSBOX[temp[2]];
            temp[3] = AES_FSBOX[temp[3]];              
        }
        
        aes->rkey[(i*4)+0] = aes->rkey[(i-AES_KEYWORDS(aes))*4 + 0] ^ temp[0];
        aes->rkey[(i*4)+1] = aes->rkey[(i-AES_KEYWORDS(aes))*4 + 1] ^ temp[1];
        aes->rkey[(i*4)+2] = aes->rkey[(i-AES_KEYWORDS(aes))*4 + 2] ^ temp[2];
        aes->rkey[(i*4)+3] = aes->rkey[(i-AES_KEYWORDS(aes))*4 + 3] ^ temp[3];
    }
}

/***************************************************************************************************************************************//**

    Combines each byte of the state with a block of the round key using XOR.

    @param[in]  aes         A pointer to the cipher instance.
    @param[in]  round       The round key to be used.

    @return     None
    @module     internal

*******************************************************************************************************************************************/
static void AES_AddRoundKey(AES* aes, BYTE round)
{
    UINT32 row;
    UINT32 col;
    
    
    for (row = 0; row < AES_NROWS; row++) {
        for (col = 0; col < AES_NCOLS; col++) {
            (*aes->state)[row][col] ^= aes->rkey[round * AES_NCOLS * 4 + row * AES_NCOLS + col];
        }
    }
}

/***************************************************************************************************************************************//**

    Performs the xtime operation upon the value 'x'.

    @param[in]  x           The value to be operated upon.

    @return     The xtime value of 'x'.
    @module     internal

*******************************************************************************************************************************************/
static BYTE AES_Xtime(BYTE x)
{
    return ((x << 1) ^ (((x >> 7) & 1) * 0x1b));
}

/***************************************************************************************************************************************//**

    Replaces each byte within the state matrix with a value from the substitution box (S-box).

    @param[in]  aes         A pointer to the cipher instance.

    @return     None
    @module     internal

*******************************************************************************************************************************************/
static void AES_SubBytes(AES* aes)
{
    UINT32 col;
    UINT32 row;
    
    
    for (col = 0; col < AES_NCOLS; col++) {
        for (row = 0; row < AES_NROWS; row++) {
            (*aes->state)[row][col] = AES_FSBOX[(*aes->state)[row][col]];
        }
    }
}

/***************************************************************************************************************************************//**

    Cyclically shifts the bytes within each row of the state matrix.

    @param[in]  aes         A pointer to the cipher instance.

    @return     None
    @module     internal

*******************************************************************************************************************************************/
static void AES_ShiftRows(AES* aes)
{
    BYTE temp;
    
    
    temp                = (*aes->state)[0][1];
    (*aes->state)[0][1] = (*aes->state)[1][1];
    (*aes->state)[1][1] = (*aes->state)[2][1];
    (*aes->state)[2][1] = (*aes->state)[3][1];
    (*aes->state)[3][1] = temp;
    
    temp                = (*aes->state)[0][2];
    (*aes->state)[0][2] = (*aes->state)[2][2];
    (*aes->state)[2][2] = temp;
    
    temp                = (*aes->state)[1][2];
    (*aes->state)[1][2] = (*aes->state)[3][2];
    (*aes->state)[3][2] = temp;
    
    temp                = (*aes->state)[0][3];
    (*aes->state)[0][3] = (*aes->state)[3][3];
    (*aes->state)[3][3] = (*aes->state)[2][3];
    (*aes->state)[2][3] = (*aes->state)[1][3];
    (*aes->state)[1][3] = temp;
}

/***************************************************************************************************************************************//**

    Mixes the columns for an AES instance.

    @param[in]  aes         A pointer to the cipher instance.

    @return     None
    @module     internal

*******************************************************************************************************************************************/
static void AES_MixColumns(AES* aes)
{
    BYTE row;
    BYTE temp;
    BYTE tm;
    BYTE t;
    
    
    for (row = 0; row < AES_NROWS; row++) {
        
        t = (*aes->state)[row][0];
        temp = (*aes->state)[row][0] ^ (*aes->state)[row][1] ^ (*aes->state)[row][2] ^ (*aes->state)[row][3];
        
        tm = (*aes->state)[row][0] ^ (*aes->state)[row][1]; 
        tm = AES_Xtime(tm); 
        (*aes->state)[row][0] ^= tm ^ temp;
        
        tm = (*aes->state)[row][1] ^ (*aes->state)[row][2]; 
        tm = AES_Xtime(tm); 
        (*aes->state)[row][1] ^= tm ^ temp;
        
        tm = (*aes->state)[row][2] ^ (*aes->state)[row][3]; 
        tm = AES_Xtime(tm); 
        (*aes->state)[row][2] ^= tm ^ temp;
        
        tm = (*aes->state)[row][3] ^ t;  
        tm = AES_Xtime(tm); 
        (*aes->state)[row][3] ^= tm ^ temp;
    }
}

/***************************************************************************************************************************************//**

    Replaces each byte within the state matrix with a value from the reverse substitution box (S-box).

    @param[in]  aes         A pointer to the cipher instance.

    @return     None
    @module     internal

*******************************************************************************************************************************************/
static void AES_InvSubBytes(AES* aes)
{
    UINT32 col;
    UINT32 row;
    
    
    for (col = 0; col < AES_NCOLS; col++) {
        for (row = 0; row < AES_NROWS; row++) {
            (*aes->state)[row][col] = AES_RSBOX[(*aes->state)[row][col]];
        }
    }
}

/***************************************************************************************************************************************//**

    Cyclically shifts the bytes within each row of the state matrix.

    @param[in]  aes         A pointer to the cipher instance.

    @return     None
    @module     internal

*******************************************************************************************************************************************/
static void AES_InvShiftRows(AES* aes)
{
    BYTE temp;
    
    
    temp                = (*aes->state)[3][1];
    (*aes->state)[3][1] = (*aes->state)[2][1];
    (*aes->state)[2][1] = (*aes->state)[1][1];
    (*aes->state)[1][1] = (*aes->state)[0][1];
    (*aes->state)[0][1] = temp;
    
    temp                = (*aes->state)[0][2];
    (*aes->state)[0][2] = (*aes->state)[2][2];
    (*aes->state)[2][2] = temp;
    
    temp                = (*aes->state)[1][2];
    (*aes->state)[1][2] = (*aes->state)[3][2];
    (*aes->state)[3][2] = temp;
    
    temp                = (*aes->state)[0][3];
    (*aes->state)[0][3] = (*aes->state)[1][3];
    (*aes->state)[1][3] = (*aes->state)[2][3];
    (*aes->state)[2][3] = (*aes->state)[3][3];
    (*aes->state)[3][3] = temp;
}

/***************************************************************************************************************************************//**

    Finds the product of two arguments.

    @param[in]  x       The first argument.
    @param[in]  y       The second argument.

    @return     The product of the specified arguments.
    @module     internal

*******************************************************************************************************************************************/
static BYTE AES_Mult(BYTE x, BYTE y)
{
    return  (((y & 1) * x) ^
            ((y >> 1 & 1) * AES_Xtime(x)) ^
            ((y >> 2 & 1) * AES_Xtime(AES_Xtime(x))) ^
            ((y >> 3 & 1) * AES_Xtime(AES_Xtime(AES_Xtime(x)))) ^
            ((y >> 4 & 1) * AES_Xtime(AES_Xtime(AES_Xtime(AES_Xtime(x))))));
}

/***************************************************************************************************************************************//**

    Reverse mixes the columns for an AES instance.

    @param[in]  aes         A pointer to the cipher instance.

    @return     None
    @module     internal

*******************************************************************************************************************************************/
static void AES_InvMixColumns(AES* aes)
{
    UINT32 row;
    BYTE a,b,c,d;
    
    
    for (row = 0; row < AES_NROWS; row++) { 
        
        a = (*aes->state)[row][0];
        b = (*aes->state)[row][1];
        c = (*aes->state)[row][2];
        d = (*aes->state)[row][3];
    
        (*aes->state)[row][0] = AES_Mult(a, 0x0e) ^ AES_Mult(b, 0x0b) ^ AES_Mult(c, 0x0d) ^ AES_Mult(d, 0x09);
        (*aes->state)[row][1] = AES_Mult(a, 0x09) ^ AES_Mult(b, 0x0e) ^ AES_Mult(c, 0x0b) ^ AES_Mult(d, 0x0d);
        (*aes->state)[row][2] = AES_Mult(a, 0x0d) ^ AES_Mult(b, 0x09) ^ AES_Mult(c, 0x0e) ^ AES_Mult(d, 0x0b);
        (*aes->state)[row][3] = AES_Mult(a, 0x0b) ^ AES_Mult(b, 0x0d) ^ AES_Mult(c, 0x09) ^ AES_Mult(d, 0x0e);
    }
}
