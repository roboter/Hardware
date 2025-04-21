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
#ifndef S25FL032P_NXPSPIFI_H__
#define S25FL032P_NXPSPIFI_H__

#include "Kernel/kernel.h"
#include "mcu_spifi.h"

/***************************************************************************************************************************************//**

    Represents an instance of the Spansion SP25L032P device driver.
    @module     spansion-s25f3032p-spifi

*******************************************************************************************************************************************/
typedef struct S25FL032P {
    SPIFI* port;                /**< A pointer to the SPIFI port used for communications */
    UINT32 timeout;             /**< The timeout interval, in kernel ticks, used for communications */
} S25FL032P;

/*******************************************************************************************************************************************
    PUBLIC FUNCTIONS
*******************************************************************************************************************************************/
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
extern STATUS S25FL032P_Open(S25FL032P* driver, SPIFI* spifi);

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
extern STATUS S25FL032P_SetTimeout(S25FL032P* driver, UINT32 timeout);

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
extern STATUS S25FL032P_ReadStat(S25FL032P* driver, BYTE* stat);

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
extern STATUS S25FL032P_ReadCfg(S25FL032P* driver, BYTE* cfg);

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
extern STATUS S25FL032P_SetStatCfg(S25FL032P* driver, BYTE stat, BYTE cfg);

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
extern STATUS S25FL032P_EnterAutoRead(S25FL032P* driver);

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
extern STATUS S25FL032P_ExitAutoRead(S25FL032P* driver);

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
extern STATUS S25FL032P_Read(S25FL032P* driver, UINT32 addr, void* buf, UINT32 nbytes);

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
extern STATUS S25FL032P_Erase4KB(S25FL032P* driver, UINT32 addr);

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
extern STATUS S25FL032P_Erase8KB(S25FL032P* driver, UINT32 addr);

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
extern STATUS S25FL032P_Erase64KB(S25FL032P* driver, UINT32 addr);

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
extern STATUS S25FL032P_Program(S25FL032P* driver, UINT32 addr, const void* data, UINT32 nbytes);

#endif /* S25FL032P_NXPSPIFI_H__ */
