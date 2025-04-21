/*******************************************************************************************************************************************

    DZX | NXP | PCA9532                                                                                                   VERSION 18.2.1
    ------------------------------------------------------------------------------------------------------------------------------------

    This is a driver for the NXP PCA9532 I/O expander.

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
#include "Drivers/NXP/pca9532.h"
#include <string.h>

/***************************************************************************************************************************************//**

    Creates and initializes a driver for the NXP PCA9532 LED dimmer.

    @param[in]  driver      A pointer to a caller allocated driver instance to be initialized.
    @param[in]  port        A pointer to an open I2C port to be used for communications.
    @param[in]  addr        The value of the external address pins (3 lower bits A0-A2).

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The driver has been initialized and is ready for communications.
     ERR_NULLREFERENCE      | The argument 'driver' or 'port' was found to be NULL.

    @module     nxp-pca9532

*******************************************************************************************************************************************/
STATUS PCA9532_Open(PCA9532* driver, I2C* port, BYTE addr)
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
    driver->addr = 0xC0 | (addr << 1);                              /* Build and cache the full driver chip address */
    driver->timeout = MILLISECOND_TICKS(1000);                      /* Default I/O timeout */
    
    return SUCCESS;
}

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
     ERR_INVALIDARGUMENT    | The argument 'timeout' must be greater zero.

    @module     nxp-pca9532

*******************************************************************************************************************************************/
STATUS PCA9532_SetTimeout(PCA9532* driver, UINT32 timeout)
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

    Reads and returns register values from the device.

    @param[in]  driver      A pointer to the driver to be used.
    @param[in]  reg         The register address to be read. Valid registers are 0 thru 9. Set the auto-increment bit (bit 4) if reading 
                            more than a single register. 
    @param[out] buf         A pointer to a caller allocated buffer to receive the returned values.
    @param[in]  nbytes      The number of bytes to be read from the device.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The register values have been read and returned.
     ERR_NULLREFERENCE      | The argument 'driver' or 'buf' was found to be NULL.

    @module     nxp-pca9532

*******************************************************************************************************************************************/
STATUS PCA9532_Read(PCA9532* driver, BYTE reg, void* buf, UINT32 nbytes)
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

    Writes values to the registers within the device.

    @param[in]  driver      A pointer to the driver to be used.
    @param[in]  data        A pointer to the data to be written to the device. The first byte is the starting register address to be
                            written. Set the auto-increment bit (bit 4) for this byte if writing more than a single register. 
    @param[in]  nbytes      The number of bytes to be written to the device.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The values have been written to the device.
     ERR_NULLREFERENCE      | The argument 'driver' or 'data' was found to be NULL.

    @module     nxp-pca9532

*******************************************************************************************************************************************/
STATUS PCA9532_Write(PCA9532* driver, void* data, UINT32 nbytes)
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
    
    status = I2C_Write(driver->port,
                      driver->addr,
                      data,
                      nbytes,
                      driver->timeout);
    
    if (status != SUCCESS) {
        return status;
    }                  
    
    return SUCCESS;
}

/***************************************************************************************************************************************//**

    Sets a new prescalar value for a channel within the device.

    @param[in]  driver      A pointer to the driver to be used.
    @param[in]  ch          The prescalar channel to be set (0 or 1).
    @param[in]  value       The new prescalar value (0-255).

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The new prescalar value has been set.
     ERR_NULLREFERENCE      | The argument 'driver' was found to be NULL.
     ERR_NOTSUPPORTED       | The specified prescalar channel is not supported.

    @module     nxp-pca9532

*******************************************************************************************************************************************/
STATUS PCA9532_SetPrescalar(PCA9532* driver, BYTE ch, BYTE value)
{
    STATUS status;
    BYTE buf[2];
    
    
#if (CFG_NULLCHECKING)
    if (driver == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif

    switch (ch) {
        case 0:
            buf[0] = 0x12;
            break;
        case 1:
            buf[0] = 0x14;
            break;
        default:
            return ERR_NOTSUPPORTED;
    }
    
    buf[1] = value;

    status = PCA9532_Write(driver, buf, 2);
    if (status != SUCCESS) {
        return status;
    }
    
    return SUCCESS;
}

/***************************************************************************************************************************************//**

    Sets a new pulse width modulation (PWM) value for a channel within the device. The outputs are low (LED on) when the count is less 
    than this value and high (LED off) when it is greater.

    @param[in]  driver      A pointer to the driver to be used.
    @param[in]  ch          The PWM channel to be set (0 or 1).
    @param[in]  value       The new PWM value (0-255).

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The new PWM value has been set.
     ERR_NULLREFERENCE      | The argument 'driver' was found to be NULL.
     ERR_NOTSUPPORTED       | The specified PWM channel is not supported.

    @module     nxp-pca9532

*******************************************************************************************************************************************/
STATUS PCA9532_SetPWM(PCA9532* driver, BYTE ch, BYTE value)
{
    STATUS status;
    BYTE buf[2];
    
    
#if (CFG_NULLCHECKING)
    if (driver == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif

    switch (ch) {
        case 0:
            buf[0] = 0x13;
            break;
        case 1:
            buf[0] = 0x15;
            break;
        default:
            return ERR_NOTSUPPORTED;
    }
    
    buf[1] = value;
    
    status = PCA9532_Write(driver, buf, 2);
    if (status != SUCCESS) {
        return status;
    }
    
    return SUCCESS;
}

/***************************************************************************************************************************************//**

    Reads and returns the 16 pin states from the device.

    @param[in]  driver      A pointer to the driver to be used.
    @param[out] value       A pointer to a caller allocated value to receive the returned pin states.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The pin states have been read and returned.
     ERR_NULLREFERENCE      | The argument 'driver' or 'value' was found to be NULL.

    @module     nxp-pca9532

*******************************************************************************************************************************************/
STATUS PCA9532_ReadPins(PCA9532* driver, UINT16* value)
{
    STATUS status;
    BYTE buf[2];

    
#if (CFG_NULLCHECKING)
    if (driver == NULL) {
        return ERR_NULLREFERENCE;
    }
    
    if (value == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif

    status = PCA9532_Read(driver, 0x00, &buf[0], sizeof(BYTE));         /* Read INPUT0 */
    if (status != SUCCESS) {
        return status;
    }
    
    status = PCA9532_Read(driver, 0x01, &buf[1], sizeof(BYTE));         /* Read INPUT1 */
    if (status != SUCCESS) {
        return status;
    }
    
    *value = (buf[1] << 8) | (buf[0]);                                  /* Provide the result */
    return SUCCESS;
}

/***************************************************************************************************************************************//**

    Writes all 16-pin states to the device.

    @param[in]  driver      A pointer to the driver to be used.
    @param[in]  value       The 32-bit representation of all 16-pin states. Each pin state is 2-bits wide with the following definition.

     Pin State              | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     0                      | Pin output is high impedance (LED off, default).
     1                      | Pin output is low (LED on).
     2                      | Pin output blinks at PWM0 rate.
     3                      | Pin output blinks at PWM1 rate.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The new pin states have been set.
     ERR_NULLREFERENCE      | The argument 'driver' was found to be NULL.

    @module     nxp-pca9532

*******************************************************************************************************************************************/
STATUS PCA9532_WritePins(PCA9532* driver, UINT32 value)
{
    STATUS status;
    BYTE buf[5];
    
    
#if (CFG_NULLCHECKING)
    if (driver == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif

    buf[0] = 0x16;
    memcpy(&buf[1], &value, sizeof(UINT32));
    
    status = PCA9532_Write(driver, buf, 5);
    if (status != SUCCESS) {
        return status;
    }
    
    return SUCCESS;
}
