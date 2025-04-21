/*******************************************************************************************************************************************

    DZX | NXP | PCA9673                                                                                                   VERSION 18.2.1
    ------------------------------------------------------------------------------------------------------------------------------------

    This is a driver for the NXP PCA9673 I/O expander.

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
#ifndef PCA9673_H__
#define PCA9673_H__

#include "mcu_i2c.h"

/***************************************************************************************************************************************//**

    Represents an instance of the NXP PCA9532 device driver.
    @module     nxp-pca9673

*******************************************************************************************************************************************/
typedef struct PCA9673 {
    I2C* port;          /**< A pointer to the I2C port used for communications with the device. */
    UINT32 timeout;     /**< The timeout value used for I/O operations with the device */
    BYTE addr;          /**< The address for the I2C device. */ 
} PCA9673;

/*******************************************************************************************************************************************
    PUBLIC FUNCTIONS
*******************************************************************************************************************************************/
/***************************************************************************************************************************************//**

    Creates and initializes a driver for the NXP PCA9673 I/O Expander.

    @param[in]  driver      A pointer to a caller allocated driver instance to be initialized.
    @param[in]  port        A pointer to an open I2C port to be used for communications.
    @param[in]  addr        The address of the device on the bus (A6-A0).

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The driver has been initialized and is ready for communications.
     ERR_NULLREFERENCE      | The argument 'driver' or 'port' was found to be NULL.

    @module     nxp-pca9673

*******************************************************************************************************************************************/
extern STATUS PCA9673_Open(PCA9673* driver, I2C* port, BYTE addr);

/***************************************************************************************************************************************//**

    Sets a new timeout value, in kernel ticks, to be used for I/O operations. The default is 1000.

    @param[in]  driver      A pointer to the driver to be updated.
    @param[in]  timeout     The new maximum amount of time, in kernel ticks, to block and wait for I/O operations to complete. Must be
                            larger than zero and use 'INFINITE' to wait indefinitely.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The driver timeout value has been changed.
     ERR_NULLREFERENCE      | The argument 'driver' was found to be NULL.

    @module     nxp-pca9673

*******************************************************************************************************************************************/
extern STATUS PCA9673_SetTimeout(PCA9673* driver, UINT32 timeout);

/***************************************************************************************************************************************//**

    Reads and returns the pin values from the device.

    @param[in]  driver      A pointer to the driver to be used.
    @param[out] value       A pointer to a caller allocated variable to receive the 16-bit port value from the device.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The port value have been read and returned.
     ERR_NULLREFERENCE      | The argument 'driver' or 'value' was found to be NULL.

    @module     nxp-pca9673

*******************************************************************************************************************************************/
extern STATUS PCA9673_Read(PCA9673* driver, UINT16* value);

/***************************************************************************************************************************************//**

    Writes the pin values to the device.

    @param[in]  driver      A pointer to the driver to be used.
    @param[in]  value       The 16-bit port value to be written to the device.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The values have been written to the device.
     ERR_NULLREFERENCE      | The argument 'driver' was found to be NULL.

    @module     nxp-pca9673

*******************************************************************************************************************************************/
extern STATUS PCA9673_Write(PCA9673* driver, UINT16 value);

#endif /* End PCA9673_H__ */
