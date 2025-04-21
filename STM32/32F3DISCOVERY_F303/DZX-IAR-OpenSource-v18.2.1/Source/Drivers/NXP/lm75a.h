/*******************************************************************************************************************************************

    DZX | NXP | LM75A                                                                                                     VERSION 18.2.1
    ------------------------------------------------------------------------------------------------------------------------------------

    This is a driver for the NXP LM75A digital temperature sensor.

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
#ifndef LM75A_H__
#define LM75A_H__

#include "Kernel/kernel.h"
#include "mcu_i2c.h"

/***************************************************************************************************************************************//**

    Represents an instance of the NXP LM75A device driver.
    @module     nxp-lm75a

*******************************************************************************************************************************************/
typedef struct LM75A {
    I2C* port;          /**< A pointer to the I2C port used for communications with the device. */
    UINT32 timeout;     /**< The timeout value used for I/O operations with the device */
    BYTE addr;          /**< The address for the I2C device. */ 
} LM75A;

/*******************************************************************************************************************************************
    PUBLIC FUNCTIONS
*******************************************************************************************************************************************/
/***************************************************************************************************************************************//**

    Creates and initializes a driver for the NXP LM75A digital temperature sensor.

    @param[in]  driver      A pointer to a caller allocated driver instance to be initialized.
    @param[in]  port        A pointer to an open I2C port to be used for communications.
    @param[in]  addr        The value of the external address pins (3 lower bits A0-A2).

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The driver has been initialized and is ready for communications.
     ERR_NULLREFERENCE      | The argument 'driver' or 'port' was found to be NULL.

    @module     nxp-lm75a

*******************************************************************************************************************************************/
extern STATUS LM75A_Open(LM75A* driver, I2C* port, BYTE addr);

/***************************************************************************************************************************************//**

    Sets a new timeout value, in kernel ticks, to be used for I/O operations. The default is 1000 milliseconds.

    @param[in]  driver      A pointer to the driver to be updated.
    @param[in]  timeout     The new maximum amount of time, in kernel ticks, to block and wait for I/O operations to complete. Must be
                            larger than zero and use 'INFINITE' to wait indefinitely.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The driver timeout value has been changed.
     ERR_NULLREFERENCE      | The argument 'driver' was found to be NULL.

    @module     nxp-lm75a

*******************************************************************************************************************************************/
extern STATUS LM75A_SetTimeout(LM75A* driver, UINT32 timeout);

/***************************************************************************************************************************************//**

    Reads and returns register values from the device.

    @param[in]  driver      A pointer to the driver to be used.
    @param[in]  reg         The register address to be read. Valid registers are 0 thru 3.
    @param[out] buf         A pointer to a caller allocated buffer to receive the returned values.
    @param[in]  nbytes      The number of bytes to be read from the device.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The values have been read and returned.
     ERR_NULLREFERENCE      | The argument 'driver' or 'buf' was found to be NULL.
     ERR_DEVICENAK          | The target device returned a NAK.
     ERR_INCOMPLETE         | An error occurred while transferring the data and the transfer did not complete.

    @module     nxp-lm75a

*******************************************************************************************************************************************/
extern STATUS LM75A_Read(LM75A* driver, BYTE reg, void* data, UINT32 nbytes);

/***************************************************************************************************************************************//**

    Reads and returns a 16-bit value from the device.

    @param[in]  driver      A pointer to the driver to be used.
    @param[in]  reg         The register address to be read. Valid registers are 0 thru 3.
    @param[out] value       A pointer to a caller allocated variable to receive the value.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The value has been read and returned.
     ERR_NULLREFERENCE      | The argument 'driver' or 'value' was found to be NULL.
     ERR_DEVICENAK          | The target device returned a NAK.
     ERR_INCOMPLETE         | An error occurred while transferring the data and the transfer did not complete.

    @module     nxp-lm75a

*******************************************************************************************************************************************/
extern STATUS LM75A_Read16(LM75A* driver, BYTE reg, INT16* value);

/***************************************************************************************************************************************//**

    Writes values to the registers within the device.

    @param[in]  driver      A pointer to the driver to be used.
    @param[in]  data        A pointer to the data to be written to the device. The first byte is the starting register address to be
                            written. 
    @param[in]  nbytes      The number of bytes to be written to the device.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The values have been written to the device.
     ERR_NULLREFERENCE      | The argument 'driver' or 'data' was found to be NULL.
     ERR_DEVICENAK          | The target device returned a NAK.
     ERR_INCOMPLETE         | An error occurred while transferring the data and the transfer did not complete.

    @module     nxp-lm75a

*******************************************************************************************************************************************/
extern STATUS LM75A_Write(LM75A* driver, void* data, UINT32 nbytes);

/***************************************************************************************************************************************//**

    Writes a 16-bit value to the device.

    @param[in]  driver      A pointer to the driver to be used.
    @param[in]  reg         The register address to be written. Valid registers are 0 thru 3.
    @param[in]  value       The value to be written to the specified register.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The value has been written.
     ERR_NULLREFERENCE      | The argument 'driver' was found to be NULL.
     ERR_DEVICENAK          | The target device returned a NAK.
     ERR_INCOMPLETE         | An error occurred while transferring the data and the transfer did not complete.

    @module     nxp-lm75a

*******************************************************************************************************************************************/
extern STATUS LM75A_Write16(LM75A* driver, BYTE reg, INT16 value);

/***************************************************************************************************************************************//**

    Reads and returns the configuration value from within the device.

    @param[in]  driver      A pointer to the driver to be used.
    @param[out] cfg         A pointer to a caller allocated variable to receive the configuration.

        Bit[7:5]    Reserved        Should be kept as zeroes for normal operation

        Bit[4:3]    OS_F_QUE[1:0]   00* - Queue Value = 1
                                    01  - Queue Value = 2
                                    10  - Queue Value = 4
                                    11  - Queue Value = 6

        Bit[2]      OS_POL          0*  - OS Active LOW
                                    1   - OS Active HIGH

        Bit[1]      OS_COMP_INT     0*  - OS Comparator
                                    1   - OS Interrupt

        Bit[0]      SHUTDOWN        0*  - Normal
                                    1   - Shutdown

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The configuration value has been returned.
     ERR_NULLREFERENCE      | The argument 'driver' or 'cfg' was found to be NULL.
     ERR_DEVICENAK          | The target device returned a NAK.
     ERR_INCOMPLETE         | An error occurred while transferring the data and the transfer did not complete.

    @module     nxp-lm75a

*******************************************************************************************************************************************/
extern STATUS LM75A_Configuration(LM75A* driver, BYTE* cfg);

/***************************************************************************************************************************************//**

    Sets a new configuration value within the device.

    @param[in]  driver      A pointer to the driver to be used.
    @param[in]  cfg         The new configuration value for the device.

        Bit[7:5]    Reserved        Should be kept as zeroes for normal operation

        Bit[4:3]    OS_F_QUE[1:0]   00* - Queue Value = 1
                                    01  - Queue Value = 2
                                    10  - Queue Value = 4
                                    11  - Queue Value = 6

        Bit[2]      OS_POL          0*  - OS Active LOW
                                    1   - OS Active HIGH

        Bit[1]      OS_COMP_INT     0*  - OS Comparator
                                    1   - OS Interrupt

        Bit[0]      SHUTDOWN        0*  - Normal
                                    1   - Shutdown

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The configuration value has been updated.
     ERR_NULLREFERENCE      | The argument 'driver' was found to be NULL.
     ERR_DEVICENAK          | The target device returned a NAK.
     ERR_INCOMPLETE         | An error occurred while transferring the data and the transfer did not complete.

    @module     nxp-lm75a

*******************************************************************************************************************************************/
extern STATUS LM75A_SetConfiguration(LM75A* driver, BYTE cfg);

/***************************************************************************************************************************************//**

    Reads and returns the threshold level, in units of degrees celsius, within the device.

    @param[in]  driver      A pointer to the driver to be used.
    @param[out] threshC     A pointer to a caller allocated variable to receive the threshold level.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The threshold level has been returned.
     ERR_NULLREFERENCE      | The argument 'driver' or 'threshC' was found to be NULL.
     ERR_DEVICENAK          | The target device returned a NAK.
     ERR_INCOMPLETE         | An error occurred while transferring the data and the transfer did not complete.

    @module     nxp-lm75a

*******************************************************************************************************************************************/
extern STATUS LM75A_Threshold(LM75A* driver, float* threshC);

/***************************************************************************************************************************************//**

    Sets a new threshold level, in units of degrees celsius, within the device.

    @param[in]  driver      A pointer to the driver to be used.
    @param[in]  threshC     The new threshold level for the device.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The threshold level has been updated.
     ERR_NULLREFERENCE      | The argument 'driver' was found to be NULL.
     ERR_DEVICENAK          | The target device returned a NAK.
     ERR_INCOMPLETE         | An error occurred while transferring the data and the transfer did not complete.

    @module     nxp-lm75a

*******************************************************************************************************************************************/
extern STATUS LM75A_SetThreshold(LM75A* driver, float threshC);

/***************************************************************************************************************************************//**

    Reads and returns the hysteresis value, in units of degrees celsius, within the device.

    @param[in]  driver      A pointer to the driver to be used.
    @param[out] hystC       A pointer to a caller allocated variable to receive the hysteresis value.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The hysteresis value has been returned.
     ERR_NULLREFERENCE      | The argument 'driver' or 'hystC' was found to be NULL.
     ERR_DEVICENAK          | The target device returned a NAK.
     ERR_INCOMPLETE         | An error occurred while transferring the data and the transfer did not complete.

    @module     nxp-lm75a

*******************************************************************************************************************************************/
extern STATUS LM75A_Hysteresis(LM75A* driver, float* hystC);

/***************************************************************************************************************************************//**

    Sets a new hysteresis value, in units of degrees celsius, within the device.

    @param[in]  driver      A pointer to the driver to be used.
    @param[in]  hystC       The new amount of hysteresis for the device.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The hysteresis value has been updated.
     ERR_NULLREFERENCE      | The argument 'driver' was found to be NULL.
     ERR_DEVICENAK          | The target device returned a NAK.
     ERR_INCOMPLETE         | An error occurred while transferring the data and the transfer did not complete.

    @module     nxp-lm75a

*******************************************************************************************************************************************/
extern STATUS LM75A_SetHysteresis(LM75A* driver, float hystC);

/***************************************************************************************************************************************//**

    Reads and returns the most recent temperature reading from the device.

    @param[in]  driver      A pointer to the driver to be used.
    @param[in]  tempC       A pointer to a value to receive the temperature value, in degrees celsius.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The temperature value has been returned.
     ERR_NULLREFERENCE      | The argument 'driver' or 'tempC' was found to be NULL.
     ERR_DEVICENAK          | The target device returned a NAK.
     ERR_INCOMPLETE         | An error occurred while transferring the data and the transfer did not complete.

    @module     nxp-lm75a

*******************************************************************************************************************************************/
extern STATUS LM75A_ReadTemp(LM75A* driver, float* tempC);

#endif /* End LM75A_H__ */
