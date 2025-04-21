/*******************************************************************************************************************************************

    DZX | LPC43xx | MULTIMEDIA CARD INTERFACE                                                                             VERSION 18.2.1
    ------------------------------------------------------------------------------------------------------------------------------------

    This is part of the MCU peripheral drivers and provides support for the MMC/SD card interface (MCI).

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
#ifndef MCU_MCI_H__
#define MCU_MCI_H__

#include "Kernel/kernel.h"
#include "Kernel/kernel_thread.h"
#include "Kernel/kernel_signal.h"

/*******************************************************************************************************************************************
    REGISTER DEFINITIONS
*******************************************************************************************************************************************/
#define REG_MCI0           ((REG_MCI*)0x40004000)

#define MCI_CMDINITFLAG     0x4000
#define MCI_CMDAPPFLAG      0x8000

#define MCI_CMDINIT         MCI_CMDINITFLAG
#define MCI_CMD0            0
#define MCI_CMD2            2
#define MCI_CMD3            3
#define MCI_CMD5            5
#define MCI_CMD7            7
#define MCI_CMD8            8
#define MCI_CMD9            9
#define MCI_CMD13           13
#define MCI_CMD16           16
#define MCI_ACMD6           (MCI_CMDAPPFLAG | 6)
#define MCI_ACMD41          (MCI_CMDAPPFLAG | 41)

typedef struct MCICTRLBITFIELD {
    UINT32 CNTRLRESET           :1;
    UINT32 FIFORESET            :1;
    UINT32 DMARESET             :1;
    UINT32                      :1;
    UINT32 INTENABLE            :1;
    UINT32                      :1;
    UINT32 READWAIT             :1;
    UINT32 SENDIRQRESPONSE      :1;
    UINT32 ABORTREADDATA        :1;
    UINT32 SENDCCSD             :1;
    UINT32 SENDAUTOSTOPCCSD     :1;
    UINT32 CEATADEVICEINTSTAT   :1;
    UINT32                      :4;
    UINT32 CARDVOLTAGEA0        :1;
    UINT32 CARDVOLTAGEA1        :1;
    UINT32 CARDVOLTAGEA2        :1;
    UINT32                      :6;
    UINT32 USEINTERNALDMAC      :1;
    UINT32                      :6;
} MCICTRLBITFIELD;

typedef struct MCICLKDIVBITFIELD {
    UINT32 DIVIDER0             :8;
    UINT32 DIVIDER1             :8;
    UINT32 DIVIDER2             :8;
    UINT32 DIVIDER3             :8;
} MCICLKDIVBITFIELD;

typedef struct MCICLKENABITFIELD {
    UINT32 CCLKENABLE           :1;
    UINT32                      :15;
    UINT32 CCLKLOWPOWER         :1;
    UINT32                      :15;
} MCICLKENABITFIELD;

typedef struct MCITMOUTBITFIELD {
    UINT32 RESPONSETIMEOUT      :8;
    UINT32 DATATIMEOUT          :24;
} MCITMOUTBITFIELD;
    
typedef struct MCICTYPEBITFIELD {
    UINT32 CARDWIDTH0           :1;
    UINT32                      :15;
    UINT32 CARDWIDTH1           :1;
    UINT32                      :15;
} MCICTYPEBITFIELD;

typedef struct MCIINTMASKBITFIELD {
    UINT32 CDET                 :1;
    UINT32 RE                   :1;
    UINT32 CDONE                :1;
    UINT32 DTO                  :1;
    UINT32 TXDR                 :1;
    UINT32 RXDR                 :1;
    UINT32 RCRC                 :1;
    UINT32 DCRC                 :1;
    UINT32 RTO                  :1;
    UINT32 DRTO                 :1;
    UINT32 HTO                  :1;
    UINT32 FRUN                 :1;
    UINT32 HLE                  :1;
    UINT32 SBE                  :1;
    UINT32 ACD                  :1;
    UINT32 EBE                  :1;
    UINT32 SDIOINTMASK          :1;
    UINT32                      :15;
} MCIINTMASKBITFIELD;

typedef struct MCICMDBITFIELD {
    UINT32 CMDINDEX             :6;
    UINT32 RESPONSEEXPECT       :1;
    UINT32 RESPONSELENGTH       :1;
    UINT32 CHECKRESPONSECRC     :1;
    UINT32 DATAEXPECTED         :1;
    UINT32 READWRITE            :1;
    UINT32 TRANSFERMODE         :1;
    UINT32 SENDAUTOSTOP         :1;
    UINT32 WAITPRVDATACOMPLETE  :1;
    UINT32 STOPABORTCMD         :1;
    UINT32 SENDINITIALIZATION   :1;
    UINT32                      :5;
    UINT32 UPDATECLOCKREGONLY   :1;
    UINT32 READCEATADEVICE      :1;
    UINT32 CCSEXPECTED          :1;
    UINT32 ENABLEBOOT           :1;
    UINT32 EXPECTBOOTACK        :1;
    UINT32 DISABLEBOOT          :1;
    UINT32 BOOTMODE             :1;
    UINT32 VOLTSWITCH           :1;
    UINT32                      :2;
    UINT32 STARTCMD             :1;
} MCICMDBITFIELD;

typedef struct MCISTATUSBITFIELD {
    UINT32 FIFORXWATERMARK      :1;
    UINT32 FIFOTXWATERMARK      :1;
    UINT32 FIFOEMPTY            :1;
    UINT32 FIFOFULL             :1;
    UINT32 CMDFSMSTATES         :4;
    UINT32 DATA3STATUS          :1;
    UINT32 DATABUSY             :1;
    UINT32 DATASTATEMCBUSY      :1;
    UINT32 RESPONSEINDEX        :6;
    UINT32 FIFOCOUNT            :13;
    UINT32 DMAACK               :1;
    UINT32 DMAREQ               :1;
} MCISTATUSBITFIELD;

typedef struct MCIFIFOTHBITFIELD {
    UINT32 TXWMARK              :12;
    UINT32                      :4;
    UINT32 RXWMARK              :12;
    UINT32 DMAMTS               :3;
    UINT32                      :1;
} MCIFIFOTHBITFIELD;

typedef struct MCIBMODBITFIELD {
    UINT32 SWR                  :1;
    UINT32 FB                   :1;
    UINT32 DSL                  :5;
    UINT32 DE                   :1;
    UINT32 PBL                  :3;
    UINT32                      :21;
} MCIBMODBITFIELD;

typedef struct SDMMCINTENBITFIELD {
    UINT32 TI                   :1;
    UINT32 RI                   :1;
    UINT32 FBE                  :1;
    UINT32                      :1;
    UINT32 DU                   :1;
    UINT32 CES                  :1;
    UINT32                      :2;
    UINT32 NIS                  :1;
    UINT32 AIS                  :1;
    UINT32                      :22;
} SDMMCINTENBITFIELD;

typedef struct REG_MCI {
    PREG_BITS32(CTRL, MCICTRLBITFIELD);
    PREG_32(PWREN);
    PREG_BITS32(CLKDIV, MCICLKDIVBITFIELD);
    PREG_32(CLKSRC);
    PREG_BITS32(CLKENA, MCICLKENABITFIELD);
    PREG_BITS32(TMOUT, MCITMOUTBITFIELD);
    PREG_BITS32(CTYPE, MCICTYPEBITFIELD);
    PREG_32(BLKSIZ);
    PREG_32(BYTCNT);
    PREG_BITS32(INTMASK, MCIINTMASKBITFIELD);
    PREG_32(CMDARG);
    PREG_32(CMD);
    PREG_32(RESP0);
    PREG_32(RESP1);
    PREG_32(RESP2);
    PREG_32(RESP3);
    PREG_BITS32(MINTSTS, MCIINTMASKBITFIELD);
    PREG_BITS32(RINTSTS, MCIINTMASKBITFIELD);
    PREG_BITS32(STATUS, MCISTATUSBITFIELD);
    PREG_BITS32(FIFOTH, MCIFIFOTHBITFIELD);
    PREG_32(CDETECT);
    PREG_32(WRTPRT);
    volatile UINT32 reserved;
    PREG_32(TCBCNT);
    PREG_32(TBBCNT);
    PREG_32(DEBNCE);
    volatile UINT32 reserved2[4];
    PREG_32(RST);
    volatile UINT32 reserved3;
    PREG_BITS32(BMOD, MCIBMODBITFIELD);
    PREG_32(PLDMND);
    PREG_32(DBADDR);
    PREG_32(IDSTS);
    PREG_BITS32(IDINTEN, SDMMCINTENBITFIELD);
} REG_MCI;

typedef struct MCIDMADES {
    PREG_32(DESC0);
    PREG_32(DESC1);
    PREG_32(DESC2);
    PREG_32(DESC3);
} MCIDMADES;

/*******************************************************************************************************************************************
    TYPE DEFINITIONS
*******************************************************************************************************************************************/
typedef struct LPC43XX_MCI MCI;
typedef enum LPC43XX_MCITRANSFERMODE MCITRANSFERMODE;
typedef struct LPC43XX_MCIRESPONSE MCIRESPONSE;
typedef enum LPC43XX_MCIRESPONSETYPE MCIRESPONSETYPE;
typedef enum LPC43XX_MCICARDSTATE MCICARDSTATE;

/***************************************************************************************************************************************//**

    A port for multimedia card interface communications.
    @module     mci-lpc43xx

*******************************************************************************************************************************************/
struct LPC43XX_MCI {
    UINT32 number;                  /**< Port number */
    REG_MCI* REG;                   /**< Pointer to the registers for the peripheral */
    MCIINTMASKBITFIELD sts;         /**< Status information from the previous command */
    THREAD* thread;                 /**< A pointer to the thread that is currently executing a command */
    MCIDMADES dma[4];               /**< DMA descriptors used for data transfers */
    SIGNALSET signals;              /**< A set of signals to block/release the thread using the port */
};

/***************************************************************************************************************************************//**

    Represents a multimedia card interface response.
    @module     mci-lpc43xx

*******************************************************************************************************************************************/
struct LPC43XX_MCIRESPONSE {
    UINT32 value[4];
};

/***************************************************************************************************************************************//**

    Represents a type of response from s multimedia card interface.
    @module     mci-lpc43xx

*******************************************************************************************************************************************/
enum LPC43XX_MCIRESPONSETYPE {
    MCIRESPONSE_NONE = 0,           /**< No response */
    MCIRESPONSE_SHORT,              /**< A short response (32-bit) */
    MCIRESPONSE_LONG,               /**< A long response (128-bit) */
};

/***************************************************************************************************************************************//**

    Represents the possible states for a card.
    @module     mci-lpc43xx

*******************************************************************************************************************************************/
enum LPC43XX_MCICARDSTATE {
    MCICARD_IDLE = 0,
    MCICARD_READY,
    MCICARD_IDENT,
    MCICARD_STBY,
    MCICARD_TRANS,
    MCICARD_DATA,
    MCICARD_RCV,
    MCICARD_PRG,
    MCICARD_DIS,
};

/***************************************************************************************************************************************//**

    A transfer mode for a multimedia card interface.
    @module     mci-lpc43xx

*******************************************************************************************************************************************/
enum LPC43XX_MCITRANSFERMODE {
    MCI_1BIT = 0,               /**< Indicates 1-bit transfer mode */
    MCI_4BIT,                   /**< Indicates 4-bit transfer mode */
    MCI_8BIT,                   /**< Indicates 8-bit transfer mode */
};

/*******************************************************************************************************************************************
    PUBLIC FUNCTIONS
*******************************************************************************************************************************************/
/***************************************************************************************************************************************//**

    Opens and initializes a multimedia card interface.

    @param[in]  port        A caller allocated card interface port to be initialized.
    @param[in]  number      The number of the port to be opened. Only one interface (number 0) is supported.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The port interface was successfully configured and is ready for communications.
     ERR_NULLREFERENCE      | The argument 'port' was found to be NULL.
     ERR_INVALIDCONTEXT     | This operation is not supported from the context of an interrupt service routine (ISR).
     ERR_NOTSUPPORTED       | The specified port number is not supported.

    @module     mci-lpc43xx

*******************************************************************************************************************************************/
extern STATUS MCI_Open(MCI* port, UINT32 number);

/***************************************************************************************************************************************//**

    Closes a multimedia card interface.

    @param[in]  port        A pointer to the card interface port to be closed.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The port interface was closed.
     ERR_NULLREFERENCE      | The argument 'port' was found to be NULL.
     ERR_INVALIDCONTEXT     | This operation is not supported from the context of an interrupt service routine (ISR).

    @module     mci-lpc43xx

*******************************************************************************************************************************************/
extern STATUS MCI_Close(MCI* port);

/***************************************************************************************************************************************//**

    Returns an indication of whether the card is detected.

    @param[in]  port        A pointer to the target card interface port.

    @return     TRUE if the card is detected; otherwise FALSE.
    @module     mci-lpc43xx

*******************************************************************************************************************************************/
extern BOOLEAN MCI_CardDetect(MCI* port);

/***************************************************************************************************************************************//**

    Returns the configured block size for a multimedia card interface.

    @param[in]  port        A pointer to the target card interface port.

    @return     The configured block size, in bytes, for the specified interface port.
    @module     mci-lpc43xx

*******************************************************************************************************************************************/
extern UINT32 MCI_BlockSize(MCI* port);

/***************************************************************************************************************************************//**

    Sets the block size for a multimedia card interface.

    @param[in]  port        A pointer to the target card interface port.
    @param[in]  size        The new block size, in bytes.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The interface block size was set.
     ERR_NULLREFERENCE      | The argument 'port' was found to be NULL.

    @module     mci-lpc43xx

*******************************************************************************************************************************************/
extern STATUS MCI_SetBlockSize(MCI* port, UINT32 size);

/***************************************************************************************************************************************//**

    Returns the current clock speed for a multimedia card interface.

    @param[in]  port        A pointer to the target card interface.

    @return     The clock speed, in hertz, for the specified card interface.
    @remark     The value returned is the actual clock rate and may not be exactly what was set using MCI_SetClock() since every possible
                rate is not attainable by the hardware.
    @module     mci-lpc43xx

*******************************************************************************************************************************************/
extern UINT32 MCI_Clock(MCI* port);

/***************************************************************************************************************************************//**

    Sets a new clock speed for a multimedia card interface.

    @param[in]  port        A pointer to the interface port to receive the new clock speed.
    @param[in]  freqHz      The new clock speed, in hertz, for the interface. Use '0' to disable the clock to the card.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The clock speed has been set.
     ERR_NULLREFERENCE      | The argument 'port' was found to be NULL.

    @module     mci-lpc43xx

*******************************************************************************************************************************************/
extern STATUS MCI_SetClock(MCI* port, UINT32 freqHz);

/***************************************************************************************************************************************//**

    Returns the transfer mode for a multimedia card interface.

    @param[in]  port        A pointer to the target card interface port.

    @return

     Mode                   | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     MCI_1BIT               | The interface is using the 1-bit transfer mode.
     MCI_4BIT               | The interface is using the 4-bit transfer mode.

    @module     mci-lpc43xx

*******************************************************************************************************************************************/
extern MCITRANSFERMODE MCI_TransferMode(MCI* port);

/***************************************************************************************************************************************//**

    Assigns a transfer mode for a multimedia card interface.

    @param[in]  port        A pointer to the target card interface port.
    @param[in]  mode        The new tranfer mode for the interface.

     mode                   | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     MCI_1BIT               | Use the 1-bit transfer mode.
     MCI_4BIT               | Use the 4-bit transfer mode.
     MCI_8BIT               | Not supported by this driver.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The command was executed successfully.
     ERR_NULLREFERENCE      | The argument 'port' was found to be NULL.
     ERR_NOTSUPPORTED       | The specified mode is not supported.

    @module     mci-lpc43xx

*******************************************************************************************************************************************/
extern STATUS MCI_SetTransferMode(MCI* port, MCITRANSFERMODE mode);

/***************************************************************************************************************************************//**

    Executes a command over a multimedia card interface.

    @param[in]  port        A pointer to the card interface port to execute the command.
    @param[in]  rca         The relative card address for the target card.
    @param[in]  cmd         The command to be executed.
    @param[in]  arg         The argument for the command to be executed.
    @param[out] resp        A pointer to a caller allocated response to receive the response values. Can be NULL.
    @param[in]  type        The type of response expected.
    @param[in]  timeout     The maximum amount of time to wait for the command to complete. Must be larger than zero.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The command was executed successfully.
     ERR_NULLREFERENCE      | The argument 'port' was found to be NULL.
     ERR_TIMEOUT            | The specified timeout interval elapsed before the command completed.

    @module     mci-lpc43xx

*******************************************************************************************************************************************/
extern STATUS MCI_Command(MCI* port, UINT32 rca, UINT32 cmd, UINT32 arg, MCIRESPONSE* resp, MCIRESPONSETYPE type, UINT32 timeout);

/***************************************************************************************************************************************//**

    Reads and returns the current state for a multimedia card.

    @param[in]  port        A pointer to the interface port used for communications.
    @param[in]  rca         The relative card address for the target card.
    @param[out] state       A pointer to a caller allocated variable to receive the state.
    @param[in]  timeout     The maximum amount of time to wait for the command to complete. Must be larger than zero.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The command was executed successfully.
     ERR_NULLREFERENCE      | The argument 'port' or 'state' was found to be NULL.
     ERR_TIMEOUT            | The specified timeout interval elapsed before the command completed.

    @module     mci-lpc43xx

*******************************************************************************************************************************************/
extern STATUS MCI_State(MCI* port, UINT32 rca, MCICARDSTATE* state, UINT32 timeout);

/***************************************************************************************************************************************//**

    Selects a card for data transfers.

    @param[in]  port        A pointer to the card interface port used to execute the command.
    @param[in]  rca         The relative card address for the target card.
    @param[in]  timeout     The maximum amount of time to wait for the command to complete. Must be larger than zero.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The command was executed successfully.
     ERR_NULLREFERENCE      | The argument 'port' was found to be NULL.
     ERR_TIMEOUT            | The specified timeout interval elapsed before the command completed.

    @module     mci-lpc43xx

*******************************************************************************************************************************************/
extern STATUS MCI_Select(MCI* port, UINT32 rca, UINT32 timeout);

/***************************************************************************************************************************************//**

    Reads and returns data from a multimedia card.

    @param[in]  port        A pointer to the interface port for communications with the card.
    @param[in]  rca         The relative card address for the target card.
    @param[out] buf         A pointer to a caller allocated buffer to receive the data.
    @param[in]  nblks       The total number of blocks to be received and returned.
    @param[in]  timeout     The maximum amount of time to wait for the command to complete. Must be larger than zero.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The data has been received and returned.
     ERR_NULLREFERENCE      | The argument 'port' or 'buf' was found to be NULL.
     ERR_TIMEOUT            | The specified timeout interval elapsed before the command completed.

    @module     mci-lpc43xx

*******************************************************************************************************************************************/
extern STATUS MCI_Read(MCI* port, UINT32 rca, UINT32 addr, void* buf, UINT32 nblks, UINT32 timeout);

/***************************************************************************************************************************************//**

    Writes data to a multimedia card.

    @param[in]  port        A pointer to the interface port for communications with the card.
    @param[in]  rca         The relative card address for the target card.
    @param[in]  data        A pointer to the data to be written to the card.
    @param[in]  nblks       The total number of blocks to be written.
    @param[in]  timeout     The maximum amount of time to wait for the command to complete. Must be larger than zero.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The data has been written to the card.
     ERR_NULLREFERENCE      | The argument 'port' or 'data' was found to be NULL.
     ERR_TIMEOUT            | The specified timeout interval elapsed before the command completed.

    @module     mci-lpc43xx

*******************************************************************************************************************************************/
extern STATUS MCI_Write(MCI* port, UINT32 rca, UINT32 addr, const void* data, UINT32 nblks, UINT32 timeout);

#endif /* MCU_MCI_H__ */
