/*******************************************************************************************************************************************

    DZX | LPC18xx | SPIFI                                                                                                 VERSION 18.2.1
    ------------------------------------------------------------------------------------------------------------------------------------

    This is part of the MCU peripheral drivers and provides support for the SPIFI interface.

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
#ifndef MCU_SPIFI_H__
#define MCU_SPIFI_H__

#include "Kernel/kernel_mutex.h"
#include "Kernel/kernel_signal.h"
#include "mcu_cfg.h"

/*******************************************************************************************************************************************
    REGISTER DEFINITIONS
*******************************************************************************************************************************************/
#define REG_SPIFI0              ((REG_SPIFI*)0x40003000)

typedef struct SPIFICTRLBITFIELD {
    UINT32 TIMEOUT              :16;
    UINT32 CSHIGH               :4;
    UINT32                      :1;
    UINT32 DPRFTCHDIS           :1;
    UINT32 INTEN                :1;
    UINT32 MODE3                :1;
    UINT32                      :3;
    UINT32 PRFTCHDIS            :1;
    UINT32 DUAL                 :1;
    UINT32 RFCLK                :1;
    UINT32 FBCLK                :1;
    UINT32 DMAEN                :1;
} SPIFICTRLBITFIELD;

typedef struct SPIFICMDBITFIELD {
    UINT32 DATALEN                 :14;
    UINT32 POLLRS                  :1;
    UINT32 DOUT                    :1;
    UINT32 INTLEN                  :3;
    UINT32 PS                      :2;
    UINT32 FRAMEFORM               :3;
    UINT32 OPCODE                  :8;
} SPIFICMDBITFIELD;

typedef struct SPIFIMEMCMDBITFIELD {
    UINT32 DATALEN                 :14;
    UINT32 POLLRS                  :1;
    UINT32 DOUT                    :1;
    UINT32                         :5;
    UINT32 FRAMEFORM               :3;
    UINT32                         :8;
} SPIFIMEMCMDBITFIELD;

typedef struct SPIFISTATBITFIELD {
    UINT32 MCINIT                  :1;
    UINT32 CMD                     :1;
    UINT32                         :2;
    UINT32 RESET                   :1;
    UINT32 INTRQ                   :1;
    UINT32                         :18;
    UINT32 VERSION                 :8;
} SPIFISTATBITFIELD;

typedef struct REG_SPIFI {
	PREG_BITS32(CTRL, SPIFICTRLBITFIELD);
	PREG_32(CMD);
    PREG_32(ADDR);
	PREG_32(IDATA);
	PREG_32(CLIMIT);
    
    union {
        PREG_8(DATA8);
        PREG_16(DATA16);
        PREG_32(DATA32);
    };
    
	PREG_32(MCMD);
	PREG_BITS32(STAT, SPIFISTATBITFIELD);
} REG_SPIFI;

/*******************************************************************************************************************************************
    TYPE DEFINITIONS
*******************************************************************************************************************************************/
typedef enum LPC18XX_SPIFI_FIELDFORM SPIFI_FIELDFORM;
typedef enum LPC18XX_SPIFI_FRAMEFORM SPIFI_FRAMEFORM;
typedef struct LPC18XX_SPIFICMD SPIFICMD;
typedef struct LPC18XX_SPIFI SPIFI;

/***************************************************************************************************************************************//**

    Represents field form options for a SPIFI command.
    @module     spifi-lpc18xx

*******************************************************************************************************************************************/
enum LPC18XX_SPIFI_FIELDFORM {
    FIELDFORM_ALLSERIAL = 0,            /**< All fields (opcode, address and data) are transferred serially */
    FIELDFORM_SERIALOPADDR = 1,         /**< Opcode and address are transferred serially while the data is transferred quad/dual */
    FIELDFORM_SERIALOPONLY = 2,         /**< Opcode is transferred serially while the address and data are transferred quad/dual */
    FIELDFORM_ALLQUADDUAL = 3           /**< All fields (opcode, address and data) are transferred quad/dual */
};

/***************************************************************************************************************************************//**

    Represents frame form options for a SPIFI command.
    @module     spifi-lpc18xx

*******************************************************************************************************************************************/
enum LPC18XX_SPIFI_FRAMEFORM {
    FRAMEFORM_OPONLY = 1,           /**< Only the opcode is to be transferred */
    FRAMEFORM_OP1ADDR = 2,          /**< The opcode and the least significant byte of the address are to be transferred */
    FRAMEFORM_OP2ADDR = 3,          /**< The opcode and the two least significant bytes of the address are to be transferred */
    FRAMEFORM_OP3ADDR = 4,          /**< The opcode and the three least significant bytes of the address are to be transferred */
    FRAMEFORM_OP4ADDR = 5,          /**< The opcode and the four bytes of the address are to be transferred */
    FRAMEFORM_NOP3ADDR = 6,         /**< No opcode, only the three least significant bytes of the address are to be transferred */
    FRAMEFORM_NOP4ADDR = 7          /**< No opcode, only the four bytes of the address are to be transferred */
};

/***************************************************************************************************************************************//**

    Represents information about a command to be executed by a SPIFI peripheral.
    @module     spifi-lpc18xx

*******************************************************************************************************************************************/
struct LPC18XX_SPIFICMD {
    BYTE opcode;                /**< The opcode value */
    BYTE intlen;                /**< The intermediate length, in bytes, of data */
    SPIFI_FIELDFORM field;      /**< The field form for the command */
    SPIFI_FRAMEFORM frame;      /**< The frame form for the command */
};

/***************************************************************************************************************************************//**

    Represents an instance of the SPIFI peripheral.
    @module     spifi-lpc18xx

*******************************************************************************************************************************************/
struct LPC18XX_SPIFI {
    REG_SPIFI*  REG;            /**< A pointer to the hardware registers */
    UINT32      port;           /**< The port, or peripheral, number */
    MUTEX       mutex;          /**< A mutex to achieve exclusive access to the port */
    
#if (CFG_SPIFIIRQ)
    SIGNALSET   signals;        /**< A signal set to block/release threads */
#endif
};

/*******************************************************************************************************************************************
    PUBLIC FUNCTIONS
*******************************************************************************************************************************************/
/***************************************************************************************************************************************//**

    Opens and initializes the SPIFI peripheral.

    @param[in]  spifi       A pointer to a caller allocated SPIFI instance to be initialized.
    @param[in]  port        The port number to be initialized (only 0 is supported on this platform).

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The peripheral was initialized.
     ERR_NULLREFERENCE      | The argument 'spifi' was found to be NULL.
     ERR_NOTSUPPORTED       | The port number is not supported.

    @remark     This does not setup the clock source to the specified SPIFI peripheral.
    @module     spifi-lpc18xx

*******************************************************************************************************************************************/
extern STATUS SPIFI_Open(SPIFI* spifi, UINT32 port);

/***************************************************************************************************************************************//**

    Closes a SPIFI peripheral.

    @param[in]  spifi       A pointer to the SPIFI instance to be closed.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The peripheral was closed.
     ERR_NULLREFERENCE      | The argument 'spifi' was found to be NULL.
     ERR_INVALIDOPERATION   | The peripheral had an unsupported port number.

    @module     spifi-lpc18xx

*******************************************************************************************************************************************/
extern STATUS SPIFI_Close(SPIFI* spifi);

/***************************************************************************************************************************************//**

    Resets a SPIFI peripheral.

    @param[in]  spifi       A pointer to the SPIFI instance to be reset.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The peripheral was reset.
     ERR_NULLREFERENCE      | The argument 'spifi' was found to be NULL.

    @module     spifi-lpc18xx

*******************************************************************************************************************************************/
extern STATUS SPIFI_Reset(SPIFI* spifi);

/***************************************************************************************************************************************//**

    Sets a SPIFI peripheral into read mode.

    @param[in]  spifi       A pointer to the SPIFI instance to be set to read mode.
    @param[in]  cmd         A pointer to the command used for reading the device.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | Read mode has been set.
     ERR_NULLREFERENCE      | The argument 'spifi' or 'cmd' was found to be NULL.

    @module     spifi-lpc18xx

*******************************************************************************************************************************************/
extern STATUS SPIFI_SetReadMode(SPIFI* spifi, const SPIFICMD* cmd);

/***************************************************************************************************************************************//**

    Claims exclusive access to a SPIFI peripheral.

    @param[in]  spifi       A pointer to the SPIFI instance to be claimed.
    @param[in]  timeout     The maximum amount of time, in kernel ticks, to block and wait to acquire the claim. Use '0' to return 
                            immediately without blocking or use 'INFINITE' to block indefinitely.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The peripheral was claimed.
     ERR_NULLREFERENCE      | The argument 'spifi' was found to be NULL.

    @module     spifi-lpc18xx

*******************************************************************************************************************************************/
extern STATUS SPIFI_Claim(SPIFI* spifi, UINT32 timeout);

/***************************************************************************************************************************************//**

    Releases a previous claim that was made for a SPIFI peripheral.

    @param[in]  spifi       A pointer to the SPIFI instance to be released.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The peripheral was claimed.
     ERR_NULLREFERENCE      | The argument 'spifi' was found to be NULL.

    @module     spifi-lpc18xx

*******************************************************************************************************************************************/
extern STATUS SPIFI_Release(SPIFI* spifi);

/***************************************************************************************************************************************//**

    Executes a command upon a SPIFI peripheral.

    @param[in]  spifi       A pointer to the SPIFI to execute the command.
    @param[in]  cmd         A pointer to the command to be executed.
    @param[in]  addr        An address argument for the command.
    @param[in]  timeout     The maximum amount of time, in kernel ticks, to block and wait for the transfer to complete. Must not be zero
                            and must be large enough to allow the transfer to complete; based upon clock rate and amount of data being
                            transferred. Use INFINITE to wait indefinitely.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The peripheral was claimed.
     ERR_NULLREFERENCE      | The argument 'spifi' or 'cmd' was found to be NULL.

    @module     spifi-lpc18xx

*******************************************************************************************************************************************/
extern STATUS SPIFI_Cmd(SPIFI* spifi, const SPIFICMD* cmd, UINT32 addr, UINT32 timeout);

/***************************************************************************************************************************************//**

    Executes a read command upon a SPIFI peripheral.

    @param[in]  spifi       A pointer to the SPIFI to execute the read command.
    @param[in]  cmd         A pointer to the command to be executed.
    @param[in]  addr        The address to be read.
    @param[out] buf         A pointer to a caller allocated buffer to receive the read data.
    @param[in]  nbytes      The total number of bytes to be read and returned.
    @param[in]  timeout     The maximum amount of time, in kernel ticks, to block and wait for the transfer to complete. Must not be zero
                            and must be large enough to allow the transfer to complete; based upon clock rate and amount of data being
                            transferred. Use INFINITE to wait indefinitely.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The requested data was read and returned.
     ERR_NULLREFERENCE      | The argument 'spifi', 'cmd' or 'buf' was found to be NULL.

    @module     spifi-lpc18xx

*******************************************************************************************************************************************/
extern STATUS SPIFI_Read(SPIFI* spifi, const SPIFICMD* cmd, UINT32 addr, void* buf, UINT32 nbytes, UINT32 timeout);

/***************************************************************************************************************************************//**

    Executes a write command upon a SPIFI peripheral.

    @param[in]  spifi       A pointer to the SPIFI to execute the write command.
    @param[in]  cmd         A pointer to the command to be executed.
    @param[in]  addr        The address to be written.
    @param[in]  data        A pointer to the data to be written.
    @param[in]  nbytes      The total number of bytes to be written.
    @param[in]  timeout     The maximum amount of time, in kernel ticks, to block and wait for the transfer to complete. Must not be zero
                            and must be large enough to allow the transfer to complete; based upon clock rate and amount of data being
                            transferred. Use INFINITE to wait indefinitely.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The requested data was written.
     ERR_NULLREFERENCE      | The argument 'spifi', 'cmd' or 'data' was found to be NULL.

    @module     spifi-lpc18xx

*******************************************************************************************************************************************/
extern STATUS SPIFI_Write(SPIFI* spifi, const SPIFICMD* cmd, UINT32 addr, const void* data, UINT32 nbytes, UINT32 timeout);

/***************************************************************************************************************************************//**

    Waits for status bits to match.

    @param[in]  spifi       A pointer to the SPIFI to execute the command.
    @param[in]  cmd         A pointer to the command to be executed.
    @param[out] devstat     A pointer to caller allocated variable to receive the final status value from the device.
    @param[in]  mask        The bits to be checked within the receive status byte (only bits 2:0 are supported).
    @param[in]  bitval      The bit value that must be matched to return.
    @param[in]  timeout     The maximum amount of time, in kernel ticks, to block and wait for the coommand to complete. Must not be zero
                            and must be large enough to allow the command to complete. Use INFINITE to wait indefinitely.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The status bits matched the specified value.
     ERR_NULLREFERENCE      | The argument 'spifi' or 'cmd' was found to be NULL.
     ERR_TIMEOUT            | The specified amount of time has elapsed before the command was complete.

    @module     spifi-lpc18xx

*******************************************************************************************************************************************/
extern STATUS SPIFI_WaitStatus(SPIFI* spifi, const SPIFICMD* cmd, BYTE* devstat, BYTE mask, BYTE bitval, UINT32 timeout);

#endif /* MCU_SPIFI_H__ */
