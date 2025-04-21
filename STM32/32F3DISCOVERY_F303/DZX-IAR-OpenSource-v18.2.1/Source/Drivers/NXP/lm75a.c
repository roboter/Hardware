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
#include "Drivers/NXP/lm75a.h"

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
STATUS LM75A_Open(LM75A* driver, I2C* port, BYTE addr)
{
#if (CFG_NULLCHECKING)
    if (driver == NULL) {
        return ERR_NULLREFERENCE;
    }

    if (port == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif

    driver->port = port;                                            /* Assign the I2C port used for communications */
    driver->addr = 0x90 | (addr << 1);                              /* Build and cache the full driver chip address */
    driver->timeout = MILLISECOND_TICKS(1000);                      /* Default I/O timeout */
    
    return SUCCESS;
}

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
STATUS LM75A_SetTimeout(LM75A* driver, UINT32 timeout)
{
#if (CFG_NULLCHECKING)
    if (driver == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif
    
    driver->timeout = timeout;
    return SUCCESS;
}

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
STATUS LM75A_Read(LM75A* driver, BYTE reg, void* buf, UINT32 nbytes)
{
    STATUS status;
    
    
#if (CFG_NULLCHECKING)
    if (driver == NULL) {
        return ERR_NULLREFERENCE;
    }
    
    if (buf == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif
    
    status = I2C_Claim(driver->port, driver->timeout);          /* Claim exclusive access to eliminate interruptions between transfers */
    if (status != SUCCESS) {
        return status;
    }
    
    status = I2C_Write(driver->port,                            /* Write the register address */
                       driver->addr, 
                       &reg,
                       1,
                       driver->timeout);
    
    if (status != SUCCESS) {
        I2C_Release(driver->port);                  
        return status;                                          /* Bubble up any errors */
    }
    
    status = I2C_Read(driver->port,                             /* Read the register values */
                      driver->addr,
                      buf,
                      nbytes,
                      driver->timeout);
    
    if (status != SUCCESS) {
        I2C_Release(driver->port);
        return status;                                          /* Bubble up any errors */
    }                  
    
    I2C_Release(driver->port);
    return SUCCESS;
}

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
STATUS LM75A_Read16(LM75A* driver, BYTE reg, INT16* value)
{
    STATUS status;
    BYTE buf[2];
    
    
#if (CFG_NULLCHECKING)
    if (value == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif  
    
    status = LM75A_Read(driver, reg, buf, 2);
    if (status != SUCCESS) {
        return status;
    }
    
    *value = (buf[0] << 8) | buf[1];
    return SUCCESS;
}

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
STATUS LM75A_Write(LM75A* driver, void* data, UINT32 nbytes)
{
    STATUS status;
    
    
#if (CFG_NULLCHECKING)
    if (driver == NULL) {
        return ERR_NULLREFERENCE;
    }
    
    if (data == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif
    
    status = I2C_Write(driver->port,                            /* Write the data to the device */
                       driver->addr,                            /* Device address */
                       data,                                    /* Data to be written */
                       nbytes,                                  /* Total number of bytes */
                       driver->timeout);                        /* Maximum amount of time to wait for transfer to complete */
    
    if (status != SUCCESS) {
        return status;
    }                  
    
    return SUCCESS;
}

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
STATUS LM75A_Write16(LM75A* driver, BYTE reg, INT16 value)
{
    STATUS status;
    BYTE buf[3];
    
    
    buf[0] = reg;
    buf[1] = (BYTE)(value >> 8);
    buf[2] = (BYTE)(value & 0xFF);
    
    status = LM75A_Write(driver, buf, 2);
    if (status != SUCCESS) {
        return status;
    }
    
    return SUCCESS;
}

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
STATUS LM75A_Configuration(LM75A* driver, BYTE* cfg)
{
    STATUS status;
    
    
#if (CFG_NULLCHECKING)
    if (cfg == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif 
    
    status = LM75A_Read(driver, 1, cfg, 1);
    if (status != SUCCESS) {
        return status;
    }
    
    return SUCCESS;
}

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
STATUS LM75A_SetConfiguration(LM75A* driver, BYTE cfg)
{
    STATUS status;
    BYTE buf[2];
    
    
    buf[0] = 0x1;                                               /* Write to register 0x1 */
    buf[1] = cfg;                                               /* The new configuration value */
    
    status = LM75A_Write(driver, buf, 2);
    if (status != SUCCESS) {
        return status;
    }
    
    return SUCCESS;
}

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
STATUS LM75A_Threshold(LM75A* driver, float* threshC)
{
    STATUS status;
    INT16 raw;
    
    
#if (CFG_NULLCHECKING)
    if (threshC == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif   
    
    status = LM75A_Read16(driver, 3, &raw);
    if (status != SUCCESS) {
        return status;
    }
    
    raw >>= 7;
    *threshC = raw * 0.5;
    
    return SUCCESS;    
}

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
STATUS LM75A_SetThreshold(LM75A* driver, float threshC)
{
    STATUS status;
    INT16 raw;
    
    
    raw = (INT16)(threshC * 2);
    raw <<= 7;
    
    status = LM75A_Write16(driver, 0x3, raw);
    if (status != SUCCESS) {
        return status;
    }
    
    return SUCCESS;
}

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
STATUS LM75A_Hysteresis(LM75A* driver, float* hystC)
{
    STATUS status;
    INT16 raw;
    
    
#if (CFG_NULLCHECKING)
    if (hystC == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif   
    
    status = LM75A_Read16(driver, 2, &raw);
    if (status != SUCCESS) {
        return status;
    }
    
    raw >>= 7;
    *hystC = raw * 0.5;
    
    return SUCCESS;    
}

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
STATUS LM75A_SetHysteresis(LM75A* driver, float hystC)
{
    STATUS status;
    INT16 raw;
    
    
    raw = (INT16)(hystC * 2);
    raw <<= 7;
    
    status = LM75A_Write16(driver, 0x2, raw);
    if (status != SUCCESS) {
        return status;
    }
    
    return SUCCESS;
}

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
STATUS LM75A_ReadTemp(LM75A* driver, float* tempC)
{
    STATUS status;
    INT16 raw;
    
    
#if (CFG_NULLCHECKING)
    if (tempC == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif   
    
    status = LM75A_Read16(driver, 0, &raw);
    if (status != SUCCESS) {
        return status;
    }
    
    raw >>= 5;
    *tempC = raw * 0.125;
    
    return SUCCESS;
}
