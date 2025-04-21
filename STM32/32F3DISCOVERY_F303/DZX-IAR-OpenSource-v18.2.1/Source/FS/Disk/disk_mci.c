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
#include "disk_mci.h"

/*******************************************************************************************************************************************
    PRIVATE DEFINITIONS
*******************************************************************************************************************************************/
#define MCIDISK_BLKSIZE         512

/*******************************************************************************************************************************************
    PRIVATE FUNCTIONS
*******************************************************************************************************************************************/
static  STATUS MCIDISK_Mount(DISK* base);
static  STATUS MCIDISK_Unmount(DISK* base);
static BOOLEAN MCIDISK_MediaPresent(DISK* base);
static  STATUS MCIDISK_Read(DISK* base, UINT32 lba, void* buf, UINT32 num);
static  STATUS MCIDISK_Write(DISK* base, UINT32 lba, const void* data, UINT32 num);
static  STATUS MCIDISK_Flush(DISK* base);

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
STATUS MCIDISK_Create(MCIDISK* disk, UINT32 port)
{
    STATUS status;
   
    
#if (CFG_NULLCHECKING)
    if (disk == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif

    disk->base.mount = MCIDISK_Mount;                           /* Assign specific handler functions */
    disk->base.unmount = MCIDISK_Unmount;
    disk->base.read = MCIDISK_Read;         
    disk->base.write = MCIDISK_Write;
    disk->base.flush = MCIDISK_Flush;
    disk->base.mediapres = MCIDISK_MediaPresent;
   
    disk->maxclk = MCIDISK_MAXCLOCKHZ;                          /* Default max clock rate */
    disk->timeout = MILLISECOND_TICKS(1000);                    /* Default communications I/O timeout */
    
    status = MCI_Open(&disk->mci, port);                        /* Open the underlying card interface driver */
    if (status != SUCCESS) {
        return status;
    }
    
    disk->base.blksize = MCIDISK_BLKSIZE;                       /* Assign the block size for this disk */
    status = MCI_SetBlockSize(&disk->mci, MCIDISK_BLKSIZE);     /* Assign same block size to the underlying interface driver */
    if (status != SUCCESS) {
        return status;
    }
        
    return SUCCESS;
}

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
STATUS MCIDISK_SetMaxClock(MCIDISK* disk, UINT32 clk)
{
#if (CFG_NULLCHECKING)
    if (disk == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif
    
    disk->maxclk = clk;
    return SUCCESS;
}

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
STATUS MCIDISK_SetTimeout(MCIDISK* disk, UINT32 timeout)
{
#if (CFG_NULLCHECKING)
    if (disk == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif
    
    disk->timeout = timeout;
    return SUCCESS;
}

/***************************************************************************************************************************************//**

    A disk handler function that mounts a RAM disk.

    @param[in]  base        A pointer to the base disk to be mounted.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The disk has been mounted.

    @module     internal

*******************************************************************************************************************************************/
static STATUS MCIDISK_Mount(DISK* base)
{
    MCIDISK* disk = (MCIDISK*)base;
    STATUS status;
    MCIRESPONSE resp;
    UINT32 mult;
    UINT32 blksize;
    UINT32 ticks;

    
    disk->ocr = 0;                                              /* Initialize the disk parameters */
    disk->rca = 0;
    disk->hc = FALSE;
    
    
    status = MCI_SetClock(&disk->mci, MCIDISK_INICLOCKHZ);      /* Set the initial clock speed */
    if (status != SUCCESS) {
        return status;
    }

    status = MCI_Command(&disk->mci,                            /* Send initialization clocks to the card */
                         disk->rca,
                         MCI_CMDINIT, 
                         0, 
                         NULL, 
                         MCIRESPONSE_NONE, 
                         disk->timeout);
    
    if (status != SUCCESS) {
        return status;
    }
    
    status = MCI_Command(&disk->mci,                            /* Command the card to idle state */
                         disk->rca,
                         MCI_CMD0, 
                         0, 
                         NULL, 
                         MCIRESPONSE_NONE, 
                         disk->timeout);
    
    if (status != SUCCESS) {
        return status;
    }
    
    
    
    status = MCI_Command(&disk->mci,                            /* Attempt CMD5 to determine if SDIO card */
                         disk->rca,
                         MCI_CMD5, 
                         0, 
                         &resp, 
                         MCIRESPONSE_SHORT, 
                         disk->timeout);
    
    if (status == SUCCESS) {
        return ERR_NOTSUPPORTED;                                /* SDIO card, not currently supported */
    }
    
    THREAD_Sleep(MILLISECOND_TICKS(100));

    status = MCI_Command(&disk->mci,
                         disk->rca,
                         MCI_CMD8, 
                         0x1AA, 
                         &resp, 
                         MCIRESPONSE_SHORT, 
                         disk->timeout);
    
    if (status != SUCCESS) {
        return status;
    }
    
    
    if ((resp.value[0] & 0xFF) == 0xAA) {
        disk->ocr |= (1UL << 30);                               /* Set the HCS bit to indicate support for high capacity */
    }
    
    
    ticks = KERNEL_Ticks();
    
    do {
        status = MCI_Command(&disk->mci,
                             disk->rca,
                             MCI_ACMD41, 
                             0, 
                             &resp, 
                             MCIRESPONSE_SHORT, 
                             disk->timeout);
        
        if (status != SUCCESS) {
            return status;
        }
        
        disk->ocr |= (resp.value[0] & 0x00FF8000);
        
        if (KERNEL_Ticks() - ticks > disk->timeout) {
            return ERR_TIMEOUT;
        }
        
    } while (resp.value[0] & (1UL << 31));

    ticks = KERNEL_Ticks();
    
    do {
        status = MCI_Command(&disk->mci,
                             disk->rca,
                             MCI_ACMD41, 
                             disk->ocr, 
                             &resp, 
                             MCIRESPONSE_SHORT, 
                             disk->timeout);
        
        if (status != SUCCESS) {
            return status;
        }
        
        if (KERNEL_Ticks() - ticks > disk->timeout) {
            return ERR_TIMEOUT;
        }
        
    } while  ((resp.value[0] & (1UL << 31)) == 0);
    
    if (resp.value[0] & (1UL << 30)) {                          /* Check if the card is high capacity */
        disk->hc = TRUE;                                        /* Card is high capacity */
    }
        
    status = MCI_Command(&disk->mci,
                         disk->rca,
                         MCI_CMD2, 
                         0, 
                         (MCIRESPONSE*)&disk->cid, 
                         MCIRESPONSE_LONG, 
                         disk->timeout);
    
    if (status != SUCCESS) {
        return status;
    }
    
    
    status = MCI_Command(&disk->mci,
                         disk->rca,
                         MCI_CMD3, 
                         0, 
                         &resp, 
                         MCIRESPONSE_SHORT, 
                         disk->timeout);
    
    if (status != SUCCESS) {
        return status;
    }
    
    disk->rca = (resp.value[0] & 0xFFFF0000);
    
    status = MCI_Command(&disk->mci,
                         disk->rca,
                         MCI_CMD9, 
                         disk->rca, 
                         (MCIRESPONSE*)&disk->csd, 
                         MCIRESPONSE_LONG, 
                         disk->timeout);
    
    if (status != SUCCESS) {
        return status;
    }
    
    THREAD_Sleep(10);
    
    status = MCI_Select(&disk->mci, disk->rca, disk->timeout);
    if (status != SUCCESS) {
        return status;
    }
    
    
    status = MCI_SetClock(&disk->mci, disk->maxclk);            /* Set the data transfer clock speed */
    if (status != SUCCESS) {
        return status;
    }
    
    status = MCI_Command(&disk->mci,                            /* Command the card to use 4-bit wide transfers */
                         disk->rca,
                         MCI_ACMD6, 
                         2, 
                         &resp, 
                         MCIRESPONSE_SHORT, 
                         disk->timeout);
    
    if (status != SUCCESS) {
        return status;
    }
            
    MCI_SetTransferMode(&disk->mci, MCI_4BIT);                  /* Set 4-bit wide transfers for the interface driver */
    
    THREAD_Sleep(MILLISECOND_TICKS(10));
    
    status = MCI_Command(&disk->mci,                            /* Set the access block size on the card */
                         disk->rca,
                         MCI_CMD16, 
                         512, 
                         &resp, 
                         MCIRESPONSE_SHORT, 
                         disk->timeout);
    
    if (status != SUCCESS) {
        return status;
    }
    
    if (((MCICSD1*)disk->csd)->CSD_STRUCTURE & 0x1) {                       /* CSD version 1.0 or 2.0 structure? */
       
        disk->base.blkcnt = (((MCICSD2*)disk->csd)->C_SIZE + 1);            /* (C_SIZE + 1) represents the number of 512KB blocks */
        disk->base.blkcnt *= (524288UL / disk->base.blksize);               /* Adjust the count based upon the access block size */

    } else {
    
        mult = (1UL << (((MCICSD1*)disk->csd)->C_SIZE_MULT + 2));           /* Calc the block count multiplier value */
        disk->base.blkcnt = (((MCICSD1*)disk->csd)->C_SIZE + 1) * mult;     /* Assign the total block count for the card */
        
        blksize = (1UL << ((MCICSD1*)disk->csd)->READ_BL_LEN);              /* Check if the card block size is greater than access size */
        if (blksize > disk->base.blksize) {
            disk->base.blkcnt *= (blksize / disk->base.blksize);            /* Adjust the block count based upon the access size */
        } else if (blksize < disk->base.blksize) {
            
        }
    }
    
    return SUCCESS;
}

/***************************************************************************************************************************************//**

    A disk handler function that unmounts a RAM disk.

    @param[in]  base        A pointer to the abstract disk to be unmounted.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The disk has been unmounted.

    @module     internal

*******************************************************************************************************************************************/
static STATUS MCIDISK_Unmount(DISK* base)
{
    MCIDISK* disk = (MCIDISK*)base;
    STATUS status;
    
    
    status = MCI_SetClock(&disk->mci, 0);                       /* Turn off the clock to the card */
    if (status != SUCCESS) {
        return status;
    }
    
    return SUCCESS;
}

/***************************************************************************************************************************************//**

    A disk handler function that reads data from a RAM disk.

    @param[in]  disk        A pointer to the disk to be read.
    @param[in]  lba         The logical block address to be read.
    @param[out] buf         A pointer to a caller allocated buffer to receive the data from the disk.
    @param[in]  num         The number of sectors to be read and returned.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The data has been read and returned from the disk.

    @module     internal

*******************************************************************************************************************************************/
static STATUS MCIDISK_Read(DISK* base, UINT32 lba, void* buf, UINT32 num)
{
    MCIDISK* disk = (MCIDISK*)base;
    STATUS status;
    UINT32 addr;
    
    
    if (disk->hc) {                                                 /* Set the target address based upon capacity */
        addr = lba;
    } else {
        addr = lba * disk->base.blksize;
    }

    status = MCI_Read(&disk->mci,                                   /* Read the data from the card */
                      disk->rca,    
                      addr, 
                      buf, 
                      num, 
                      disk->timeout);   
    
    if (status != SUCCESS) {
        return status;
    }
    
    return SUCCESS;
}

/***************************************************************************************************************************************//**

    A disk handler function that writes data to a RAM disk.

    @param[in]  disk        A pointer to the disk to be written.
    @param[in]  lba         The logical block address to be written.
    @param[in]  data        A pointer to the data to be written to the disk.
    @param[in]  num         The number of sectors to be written.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The data has been written to the disk.

    @module     internal

*******************************************************************************************************************************************/
static STATUS MCIDISK_Write(DISK* base, UINT32 lba, const void* data, UINT32 nblks)
{
    MCIDISK* disk = (MCIDISK*)base;
    STATUS status;
    UINT32 addr;
    
    
    if (disk->hc) {                                             /* Set the target address based upon capacity */
        addr = lba;
    } else {
        addr = lba * disk->base.blksize;
    }
    
    status = MCI_Write(&disk->mci,                              /* Write the data to the card */
                       disk->rca, 
                       addr, 
                       data, 
                       nblks, 
                       disk->timeout);
    
    if (status != SUCCESS) {
        return status;
    }
    
    return SUCCESS;
} 

/***************************************************************************************************************************************//**

    A disk handler function that flushes any cached data for the disk. 

    @param[in]  disk        A pointer to the disk to be flushed.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The disk cache has been flushed.

    @module     internal

*******************************************************************************************************************************************/
static STATUS MCIDISK_Flush(DISK* disk)
{
    return SUCCESS;
}

/***************************************************************************************************************************************//**

    A disk handler function that returns an indication of whether the disk media is present

    @param[in]  base        A pointer to the base disk to be checked for media presence.

    @return     TRUE if the disk media is present; otherwise FALSE.
    @module     internal

*******************************************************************************************************************************************/
static BOOLEAN MCIDISK_MediaPresent(DISK* base)
{
    MCIDISK* disk = (MCIDISK*)base;
    
    
    if (MCI_CardDetect(&disk->mci)) {                           /* Check the status within the underlying driver */
        return TRUE;
    }
    
    return FALSE;
}
