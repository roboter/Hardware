/*******************************************************************************************************************************************

    DZX | SPANSION | S25FL032P                                                                                            VERSION 18.2.1
    ------------------------------------------------------------------------------------------------------------------------------------

    This is a driver for the Spansion S25FL032P serial flash that uses the NXP SPIFI peripheral for communications.

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
#include "Drivers/Spansion/s25fl032p_nxpspifi.h"

/*******************************************************************************************************************************************
    PRIVATE FUNCTIONS
*******************************************************************************************************************************************/
static STATUS S25FL032P_SetWREN(S25FL032P* driver);
static STATUS S25FL032P_WaitBusy(S25FL032P* driver, BYTE* devstat);
static STATUS S25FL032P_EraseCmd(S25FL032P* driver, BYTE opcode, UINT32 addr);


/***************************************************************************************************************************************//**

    Creates and initializes a driver for the Spansion S25FL032P serial flash device.

    @param[in]  driver      A pointer to a caller allocated device driver instance to be initialized.
    @param[in]  port        A pointer to an open SPIFI port to be used for communications.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The driver has been initialized and is ready for communications.
     ERR_NULLREFERENCE      | The argument 'driver' or 'port' was found to be NULL.

    @module     spansion-s25f3032p-spifi

*******************************************************************************************************************************************/
STATUS S25FL032P_Open(S25FL032P* driver, SPIFI* port)
{
#if (CFG_NULLCHECKING)
    if (driver == NULL) {
        return ERR_NULLREFERENCE;
    }
    
    if (port == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif
    
    driver->port = port;
    driver->timeout = MILLISECOND_TICKS(1000);
    
    return SUCCESS;
}

/***************************************************************************************************************************************//**

    Assigns a new communications timeout interval for the driver.

    @param[in]  driver      A pointer to the driver to receive the new timeout value.
    @param[in]  timeout     The maximum amount of time, in kernel ticks, to block and wait for communications to complete. Must be
                            larger than '0'. Use INFINITE to block and wait indefinitely.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The new timeout interval has been applied.
     ERR_NULLREFERENCE      | The argument 'driver' was found to be NULL.
     ERR_INVALIDARGUMENT    | The specified timeout value was invalid.

    @module     spansion-s25f3032p-spifi

*******************************************************************************************************************************************/
STATUS S25FL032P_SetTimeout(S25FL032P* driver, UINT32 timeout)
{
#if (CFG_NULLCHECKING)
    if (driver == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif  
    
    if (timeout == 0) {
        return ERR_INVALIDARGUMENT;
    }
    
    driver->timeout = timeout;
    return SUCCESS;
}

/***************************************************************************************************************************************//**

    Sets the write enable bit within the device.

    @param[in]  driver      A pointer to the driver used to execute the command.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The write enable bit has been set.

    @module     internal

*******************************************************************************************************************************************/
static STATUS S25FL032P_SetWREN(S25FL032P* driver)
{
    SPIFICMD cmd;
    STATUS status;
    
    
    cmd.opcode = 0x6;
    cmd.frame = FRAMEFORM_OPONLY;
    cmd.field = FIELDFORM_ALLSERIAL;
    cmd.intlen = 0;
    
    status = SPIFI_Cmd(driver->port, &cmd, 0, driver->timeout);
    if (status != SUCCESS) {
        return status;
    }
    
    return SUCCESS;
}
 
/***************************************************************************************************************************************//**

    Blocks and waits until the device is no longer busy with a write operation.

    @param[in]  driver      A pointer to the driver used to perform the commands.
    @param[out] devstat     A pointer to a caller allocated variable to retreive the last status reported by the device.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The device is no longer busy.
     ERR_TIMEOUT            | The driver timeout interval has elapsed prior to the device becoming not busy.

    @module     internal

*******************************************************************************************************************************************/
static STATUS S25FL032P_WaitBusy(S25FL032P* driver, BYTE* devstat)
{  
    SPIFICMD cmd;
    STATUS status;
    
    
    cmd.opcode = 0x5;                                           /* Use a command to poll status register */
    cmd.frame = FRAMEFORM_OPONLY;
    cmd.field = FIELDFORM_ALLSERIAL;
    cmd.intlen = 0;
    
    status = SPIFI_WaitStatus(driver->port, &cmd, devstat, 0x1, 0, driver->timeout);
    if (status != SUCCESS) {
        return status;
    }

    return SUCCESS;
}

/***************************************************************************************************************************************//**

    Reads the status register from the device.

    @param[in]  driver      A pointer to the driver used to perform the command.
    @param[out] stat        A pointer to a caller allocated variable to receive the status value.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The status value has been read and returned.
     ERR_NULLREFERENCE      | The argument 'driver' or 'stat' was found to be NULL.

    @module     spansion-s25f3032p-spifi

*******************************************************************************************************************************************/
STATUS S25FL032P_ReadStat(S25FL032P* driver, BYTE* stat)
{
    SPIFICMD cmd;
    STATUS status;
    
    
#if (CFG_NULLCHECKING)
    if (driver == NULL) {
        return ERR_NULLREFERENCE;
    }
    
    if (stat == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif
    
    cmd.opcode = 0x5;
    cmd.frame = FRAMEFORM_OPONLY;
    cmd.field = FIELDFORM_ALLSERIAL;
    cmd.intlen = 0;
    
    status = SPIFI_Read(driver->port, &cmd, 0, stat, 1, driver->timeout);
    if (status != SUCCESS) {
        return status;
    }
    
    return SUCCESS;
}

/***************************************************************************************************************************************//**

    Reads the configuration register from the device.

    @param[in]  driver      A pointer to the driver used to perform the command.
    @param[out] cfg         A pointer to a caller allocated variable to receive the configuration value.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The configuration value has been read and returned.
     ERR_NULLREFERENCE      | The argument 'driver' or 'cfg' was found to be NULL.

    @module     spansion-s25f3032p-spifi

*******************************************************************************************************************************************/
STATUS S25FL032P_ReadCfg(S25FL032P* driver, BYTE* cfg)
{
    SPIFICMD cmd;
    STATUS status;
    
    
#if (CFG_NULLCHECKING)
    if (driver == NULL) {
        return ERR_NULLREFERENCE;
    }
    
    if (cfg == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif
    
    cmd.opcode = 0x35;
    cmd.frame = FRAMEFORM_OPONLY;
    cmd.field = FIELDFORM_ALLSERIAL;
    cmd.intlen = 0;
    
    status = SPIFI_Read(driver->port, &cmd, 0, cfg, 1, driver->timeout);
    if (status != SUCCESS) {
        return status;
    }
    
    return SUCCESS;
}

/***************************************************************************************************************************************//**

    Writes the status and configuration registers within the device.

    @param[in]  driver      A pointer to the driver used to perform the command.
    @param[in]  stat        A new status register value to be sent to the device.
    @param[in]  cfg         A new configuration register value to be sent to the device.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The status and configuration values have been updated.
     ERR_NULLREFERENCE      | The argument 'driver' was found to be NULL.

    @module     spansion-s25f3032p-spifi

*******************************************************************************************************************************************/
STATUS S25FL032P_SetStatCfg(S25FL032P* driver, BYTE stat, BYTE cfg)
{
    SPIFICMD cmd;
    STATUS status;
    BYTE devstat;
    BYTE buf[2];
    
    
#if (CFG_NULLCHECKING)
    if (driver == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif
    
    status = S25FL032P_SetWREN(driver);
    if (status != SUCCESS) {
        return status;
    }
    
    cmd.opcode = 0x1;
    cmd.frame = FRAMEFORM_OPONLY;
    cmd.field = FIELDFORM_ALLSERIAL;
    cmd.intlen = 0;
    
    buf[0] = stat;
    buf[1] = cfg;
    
    status = SPIFI_Write(driver->port, &cmd, 0, buf, 2, driver->timeout);
    if (status != SUCCESS) {
        return status;
    }
    
    status = S25FL032P_WaitBusy(driver, &devstat);
    if (status != SUCCESS) {
        return status;
    }
    
    if (devstat & 0x7C) {
        return ERR_DEVICENAK;
    }
    
    return SUCCESS;
}

/***************************************************************************************************************************************//**

    Enters the automatic read mode.

    @param[in]  driver      A pointer to the driver used to perform the automatic read command.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The memory is in automatic read mode.
     ERR_NULLREFERENCE      | The argument 'driver' was found to be NULL.

    @module     spansion-s25f3032p-spifi

*******************************************************************************************************************************************/
STATUS S25FL032P_EnterAutoRead(S25FL032P* driver)
{
    SPIFICMD cmd;
    STATUS status;
    
    
#if (CFG_NULLCHECKING)
    if (driver == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif
    
    cmd.opcode = 0xEB;
    cmd.frame = FRAMEFORM_OP3ADDR;
    cmd.field = FIELDFORM_SERIALOPONLY;
    cmd.intlen = 3;
    
    status = SPIFI_SetReadMode(driver->port, &cmd);
    if (status != SUCCESS) {
        return status;
    }
    
    return SUCCESS;
}

/***************************************************************************************************************************************//**

    Exits the automatic read mode to allow for erasing or programming of the device memory.

    @param[in]  driver      A pointer to the target driver.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The memory is out of automatic read mode.
     ERR_NULLREFERENCE      | The argument 'driver' was found to be NULL.

    @module     spansion-s25f3032p-spifi

*******************************************************************************************************************************************/
STATUS S25FL032P_ExitAutoRead(S25FL032P* driver)
{
    STATUS status;
    
    
#if (CFG_NULLCHECKING)
    if (driver == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif

    status = SPIFI_Reset(driver->port);
    if (status != SUCCESS) {
        return status;
    }
    
    return SUCCESS;
}

/***************************************************************************************************************************************//**

    Reads data from the device.

    @param[in]  driver      A pointer to the driver used to perform the command.
    @param[in]  addr        The starting address to be read.
    @param[out] buf         A pointer to a caller allocated buffer to receive the data that has been read.
    @param[in]  nbytes      The total number of bytes to be read and returned.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The data has been read and returned.
     ERR_NULLREFERENCE      | The argument 'driver' or 'buf' was found to be NULL.

    @module     spansion-s25f3032p-spifi

*******************************************************************************************************************************************/
STATUS S25FL032P_Read(S25FL032P* driver, UINT32 addr, void* buf, UINT32 nbytes)
{
    SPIFICMD cmd;
    STATUS status;
    UINT32 total = 0;
    UINT32 len;
    
    
    cmd.opcode = 0xEB;
    cmd.frame = FRAMEFORM_OP3ADDR;
    cmd.field = FIELDFORM_SERIALOPONLY;
    cmd.intlen = 3;

    while (total < nbytes) {
        
        len = nbytes - total;
        if (len > 4096) {
            len = 4096;
        }
        
        status = SPIFI_Read(driver->port, 
                            &cmd, 
                            addr + total, 
                            (BYTE*)buf + total, 
                            len, 
                            driver->timeout);
        
        if (status != SUCCESS) {
            return status;
        }
       
        total += len;
    }
    
    return SUCCESS;
}

/***************************************************************************************************************************************//**

    Performs an erase operation upon a device.

    @param[in]  driver      A pointer to the driver used to perform the command.
    @param[in]  opcode      The opcode for the erase command.
    @param[in]  addr        The target address to be erased.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The specified memory has been erased.
     ERR_NULLREFERENCE      | The argument 'driver' was found to be NULL.

    @module     internal

*******************************************************************************************************************************************/
static STATUS S25FL032P_EraseCmd(S25FL032P* driver, BYTE opcode, UINT32 addr)
{
    SPIFICMD cmd;
    STATUS status;
    BYTE devstat;
    
    
#if (CFG_NULLCHECKING)
    if (driver == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif
    
    cmd.opcode = opcode;
    cmd.frame = FRAMEFORM_OP3ADDR;
    cmd.field = FIELDFORM_ALLSERIAL;
    cmd.intlen = 0;
    
    status = S25FL032P_SetWREN(driver);
    if (status != SUCCESS) {
        return status;
    }
    
    status = SPIFI_Cmd(driver->port, &cmd, addr, driver->timeout);
    if (status != SUCCESS) {
        return status;
    }
    
    status = S25FL032P_WaitBusy(driver, &devstat);
    if (status != SUCCESS) {
        return status;
    }
    
    if (devstat & 0x7C) {
        return ERR_DEVICENAK;
    }

    return SUCCESS;
}

/***************************************************************************************************************************************//**

    Erases a 4KB sector within a device.

    @param[in]  driver      A pointer to the driver used to perform the command.
    @param[in]  addr        An address within the sector to be erased.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The specified sector has been erased.
     ERR_NULLREFERENCE      | The argument 'driver' was found to be NULL.

    @module     spansion-s25f3032p-spifi

*******************************************************************************************************************************************/
STATUS S25FL032P_Erase4KB(S25FL032P* driver, UINT32 addr)
{
    return S25FL032P_EraseCmd(driver, 0x20, addr);
}

/***************************************************************************************************************************************//**

    Erases an 8KB sector within a device.

    @param[in]  driver      A pointer to the driver used to perform the command.
    @param[in]  addr        An address within the sector to be erased.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The specified sector has been erased.
     ERR_NULLREFERENCE      | The argument 'driver' was found to be NULL.

    @module     spansion-s25f3032p-spifi

*******************************************************************************************************************************************/
STATUS S25FL032P_Erase8KB(S25FL032P* driver, UINT32 addr)
{
    return S25FL032P_EraseCmd(driver, 0x40, addr);
}

/***************************************************************************************************************************************//**

    Erases a 64KB sector within a device.

    @param[in]  driver      A pointer to the driver used to perform the command.
    @param[in]  addr        An address within the sector to be erased.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The specified sector has been erased.
     ERR_NULLREFERENCE      | The argument 'driver' was found to be NULL.

    @module     spansion-s25f3032p-spifi

*******************************************************************************************************************************************/
STATUS S25FL032P_Erase64KB(S25FL032P* driver, UINT32 addr)
{
    return S25FL032P_EraseCmd(driver, 0xD8, addr);
}

/***************************************************************************************************************************************//**

    Programs memory within a device.

    @param[in]  driver      A pointer to the driver used to perform the command.
    @param[in]  addr        The starting address to be programmed.
    @param[in]  data        A pointer to the data to be programmed within the device.
    @param[in]  nbytes      The total number of bytes to be programmed.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The specified sector has been erased.
     ERR_NULLREFERENCE      | The argument 'driver' or 'data' was found to be NULL.

    @module     spansion-s25f3032p-spifi

*******************************************************************************************************************************************/
STATUS S25FL032P_Program(S25FL032P* driver, UINT32 addr, const void* data, UINT32 nbytes)
{
    SPIFICMD cmd;
    STATUS status;
    UINT32 total = 0;
    UINT32 len;
    UINT32 max;
    BYTE devstat;
    
    
    cmd.opcode = 0x32;
    cmd.frame = FRAMEFORM_OP3ADDR;
    cmd.field = FIELDFORM_SERIALOPADDR;
    cmd.intlen = 0;

    while (total < nbytes) {
        
        max = 256 - ((addr + total) % 256);                     /* Max write length before entering the next page */
        
        len = total - nbytes;
        if (len > max) {                                        /* Bound the write to the current page */
            len = max;
        }
        
        status = S25FL032P_SetWREN(driver);
        if (status != SUCCESS) {
            return status;
        }
        
        status = SPIFI_Write(driver->port, 
                             &cmd,
                             addr + total, 
                             (BYTE*)data + total, 
                             len,
                             driver->timeout);
        
        if (status != SUCCESS) {
            return status;
        }
        
        status = S25FL032P_WaitBusy(driver, &devstat);
        if (status != SUCCESS) {
            return status;
        }
        
        if (devstat & 0x7C) {
            return ERR_DEVICENAK;
        }
       
        total += len;
    }
    
    return SUCCESS;
}

