/*******************************************************************************************************************************************

    DZX | FILE SYSTEM | MULTIMEDIA CARD INTERFACE DISK                                                                    VERSION 18.2.1
    ------------------------------------------------------------------------------------------------------------------------------------

    This provides a driver for accessing a media disk that uses a multimedia card interface (MCI) for storage. Once the driver has been 
    created, use the generic DISK functions for mounting or reading/writing the disk.

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
#ifndef DISK_MCI_H__
#define DISK_MCI_H__

#include "disk.h"
#include "mcu_mci.h"

/*******************************************************************************************************************************************
    DEFINITIONS
*******************************************************************************************************************************************/
#define MCIDISK_INICLOCKHZ          400000
#define MCIDISK_MAXCLOCKHZ          50000000

/*******************************************************************************************************************************************
    TYPE DEFINITIONS
*******************************************************************************************************************************************/
typedef struct MCIDISK MCIDISK;
typedef struct MCICID MCICID;
typedef struct MCICSD1 MCICSD1;
typedef struct MCICSD2 MCICSD2;

/***************************************************************************************************************************************//**

    Represents the SD CID register.
    @module     internal

*******************************************************************************************************************************************/
PREPACKED struct MCICID {
    BYTE    CRC;
    UINT16  MDT;
    UINT32  PSN;
    BYTE    PRV;
    CHAR    PNM[5];
    UINT16  OID;
    BYTE    MID; 
} POSTPACKED;
    
/***************************************************************************************************************************************//**

    Represents the SD CSD version 1 register.
    @module     internal

*******************************************************************************************************************************************/
PREPACKED struct MCICSD1 {
    UINT32                      :1;
    UINT32 CRC                  :7;
    UINT32                      :2;
    UINT32 FILE_FORMAT          :2;
    UINT32 TMP_WRITE_PROTECT    :1;
    UINT32 PERM_WRITE_PROTECT   :1;
    UINT32 COPY                 :1;
    UINT32 FILE_FORMAT_GRP      :1;
    UINT32                      :5;
    UINT32 WRITE_BL_PARTIAL     :1;
    UINT32 WRITE_BL_LEN         :4;
    UINT32 R2W_FACTOR           :3;
    UINT32                      :2;
    UINT32 WP_GRP_ENABLE        :1;
    UINT32 WP_GRP_SIZE          :7;
    UINT32 SECTOR_SIZE          :7;
    UINT32 ERASE_BLK_EN         :1;
    UINT32 C_SIZE_MULT          :3;
    UINT32 VDD_W_CURR_MAX       :3;
    UINT32 VDD_W_CURR_MIN       :3;
    UINT32 VDD_R_CURR_MAX       :3;
    UINT32 VDD_R_CURR_MIN       :3;
    UINT32 C_SIZE               :12;
    UINT32                      :2;
    UINT32 DSR_IMP              :1;
    UINT32 READ_BLK_MISALIGN    :1;
    UINT32 WRITE_BLK_MISALIGN   :1;
    UINT32 READ_BL_PARTIAL      :1;
    UINT32 READ_BL_LEN          :4;
    UINT32 CCC                  :12;
    UINT32 TRAN_SPEED           :8;
    UINT32 NSAC                 :8;
    UINT32 TAAC                 :8;
    UINT32                      :6;
    UINT32 CSD_STRUCTURE        :2;
} POSTPACKED;

/***************************************************************************************************************************************//**

    Represents the SD CSD version 2 register.
    @module     internal

*******************************************************************************************************************************************/
PREPACKED struct MCICSD2 {
    UINT32                      :1;
    UINT32 CRC                  :7;
    UINT32                      :2;
    UINT32 FILE_FORMAT          :2;
    UINT32 TMP_WRITE_PROTECT    :1;
    UINT32 PERM_WRITE_PROTECT   :1;
    UINT32 COPY                 :1;
    UINT32 FILE_FORMAT_GRP      :1;
    UINT32                      :5;
    UINT32 WRITE_BL_PARTIAL     :1;
    UINT32 WRITE_BL_LEN         :4;
    UINT32 R2W_FACTOR           :3;
    UINT32                      :2;
    UINT32 WP_GRP_ENABLE        :1;
    UINT32 WP_GRP_SIZE          :7;
    UINT32 SECTOR_SIZE          :7;
    UINT32 ERASE_BLK_EN         :1;
    UINT32                      :1;
    UINT32 C_SIZE               :22;
    UINT32                      :6;
    UINT32 DSR_IMP              :1;
    UINT32 READ_BLK_MISALIGN    :1;
    UINT32 WRITE_BLK_MISALIGN   :1;
    UINT32 READ_BL_PARTIAL      :1;
    UINT32 READ_BL_LEN          :4;
    UINT32 CCC                  :12;
    UINT32 TRAN_SPEED           :8;
    UINT32 NSAC                 :8;
    UINT32 TAAC                 :8;
    UINT32                      :6;
    UINT32 CSD_STRUCTURE        :2;
} POSTPACKED;

/***************************************************************************************************************************************//**

    Represents a media disk driver that uses a multimedia card interface.
    @module     fs-mcidisk

*******************************************************************************************************************************************/
struct MCIDISK {
    DISK base;                              /**< The base disk driver that is being extended */
    MCI mci;                                /**< A multimedia card interface driver */
    UINT32 maxclk;                          /**< The maximum clock rate used for data transfers with the card */
    UINT32 timeout;                         /**< The timeout used for I/O communications with the card */
    UINT32 rca;                             /**< The relative card address for the card representing this disk */
    UINT32 ocr;                             /**< The operation conditions register value for the card */
    MCICID cid;                             /**< Card identification information */
    UINT32 csd[4];                          /**< Card specific data */
    BOOLEAN hc;                             /**< Indication of whether the card is high or standard capacity */
};

/*******************************************************************************************************************************************
    PUBLIC FUNCTIONS
*******************************************************************************************************************************************/
/***************************************************************************************************************************************//**

    Creates and initializes a disk driver that uses a multimedia card interface (MCI) to communicate with an SD/MMC card for storage.

    @param[in]  disk        A pointer to a caller allocated MCI disk driver instance to be initialized.
    @param[in]  port        The port number of the multimedia card interface to be used by the driver.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The disk driver has been initialized.
     ERR_NULLREFERENCE      | The argument 'disk' was found to be NULL.

    @module     fs-mcidisk

*******************************************************************************************************************************************/
extern STATUS MCIDISK_Create(MCIDISK* disk, UINT32 port);

/***************************************************************************************************************************************//**

    Sets the maximum clock rate, in hertz, to be used for data transfers with the card.

    @param[in]  disk        A pointer to the disk driver to receive the new maximum clock rate.
    @param[in]  iniclk      The maximum clock rate, in hertz, to be used for data transfers.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The new maximum clock rate has been assigned.
     ERR_NULLREFERENCE      | The argument 'disk' was found to be NULL.

    @module     fs-mcidisk

*******************************************************************************************************************************************/
extern STATUS MCIDISK_SetMaxClock(MCIDISK* disk, UINT32 clk);

/***************************************************************************************************************************************//**

    Sets a new timeout value, in kernel ticks, to be used for I/O operations. The default is 1000 milliseconds.

    @param[in]  driver      A pointer to the disk to receive the new timeout value.
    @param[in]  timeout     The new maximum amount of time, in kernel ticks, to block and wait for I/O operations to complete. Must be
                            larger than zero and use 'INFINITE' to wait indefinitely.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The disk driver timeout value has been changed.
     ERR_NULLREFERENCE      | The argument 'disk' was found to be NULL.

    @module     fs-mcidisk

*******************************************************************************************************************************************/
extern STATUS MCIDISK_SetTimeout(MCIDISK* disk, UINT32 timeout);

#endif /* DISK_MCI_H__ */
