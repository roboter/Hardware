/*******************************************************************************************************************************************

    DZX | INTERSIL | ISL29003                                                                                             VERSION 18.2.1
    ------------------------------------------------------------------------------------------------------------------------------------

    This is a driver for the Intersil ISL29003 light sensor.

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
#include "Drivers/Intersil/isl29003.h"

/***************************************************************************************************************************************//**

    Creates and initializes an instance of the ISL29003 sensor driver.

    @param[in]  driver      A pointer to a caller allocated instance of a ISL29003 driver to be initialized.
    @param[in]  port        A pointer to an open I2C port to be used for communications.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The driver has been initialized and is ready for communications.
     ERR_NULLREFERENCE      | The argument 'driver' or 'port' was found to be NULL.

    @module     isl29003

*******************************************************************************************************************************************/
STATUS ISL29003_Open(ISL29003* driver, I2C* port)
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
    driver->address = 0x88;
    driver->timeout = MILLISECOND_TICKS(1000);                              /* Default I/O timeout = 1 second */
    
    return SUCCESS;
}

/***************************************************************************************************************************************//**

    Enables the ISL29003 device with the specified options.

    @param[in]  driver      A pointer to the target driver instance.
    @param[in]  timing      The timing mode for the device.

     Timing Mode            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     0                      | Integration is internally timed.
     1                      | Integration is externally sync/controlled by I2C host.

    @param[in]  mode        The ADC work mode.
    
     ADC Work Mode          | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     0                      | Diode1's current to unsigned 16-bit data.
     1                      | Diode2's current to unsigned 16-bit data.
     2                      | Difference between diodes (I1 - I2) to signed 15-bit data.
     3                      | Reserved.

    @param[in]  clock       The number of clock cycles; n-bit resolution.
    
     Clock Cycles           | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     0                      | 2^16 cycles.
     1                      | 2^12 cycles.
     2                      | 2^8 cycles.
     3                      | 2^4 cycles.

    @param[in]  gain        The gain range.
    
     Gain                   | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     0                      | 0 to 1000 lux.
     1                      | 0 to 4000 lux.
     2                      | 0 to 16000 lux.
     3                      | 0 to 64000 lux.

    @param[in]  intPersist  The interrupt trigger rate.
    
     Int Persist            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     0                      | Interrupt is triggered after 1 integration cycle.
     1                      | Interrupt is triggered after 4 integration cycles.
     2                      | Interrupt is triggered after 8 integration cycles.
     3                      | Interrupt is triggered after 16 integration cycles.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The device has been enabled with the specified options.
     ERR_NULLREFERENCE      | The argument 'driver' was found to be NULL.
     ERR_DEVICENAK          | The target device returned a NAK.
     ERR_INCOMPLETE         | An error occurred while transferring the data and the transfer did not complete.

    @module     isl29003

*******************************************************************************************************************************************/
STATUS ISL29003_Enable(ISL29003* driver, BYTE timing, BYTE mode, BYTE clock, BYTE gain, BYTE intPersist)
{
    BYTE buf[3];
    
    
#if (CFG_NULLCHECKING)
    if (driver == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif
    
    buf[0] = 0;                                                 /* Write to register 0x0 (command register) */
    
    buf[1] = 0x80;
    buf[1] |= ((timing & 0x1) << 5);                            /* Assign the timing mode */
    buf[1] |= ((mode & 0x3) << 2);                              /* Assign the ADC work mode */
    buf[1] |= (clock & 0x3);                                    /* Assign the clock width */
    
    buf[2] = 0;
    buf[2] |= ((gain & 0x3) << 2);                              /* Assign the gain */
    buf[2] |= (intPersist & 0x3);                               /* Assign the interrupt trigger */
    
    return ISL29003_Write(driver, buf, 3);                      /* Write the command to the device */
}

/***************************************************************************************************************************************//**

    Disables, and optionally powers down, the ISL29003 device.

    @param[in]  driver      A pointer to the driver to be used.
    @param[in]  powerDown   TRUE to command the device to power down; otherwise FALSE. 

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The device has been disabled.
     ERR_NULLREFERENCE      | The argument 'driver' was found to be NULL.
     ERR_DEVICENAK          | The target device returned a NAK.
     ERR_INCOMPLETE         | An error occurred while transferring the data and the transfer did not complete.

    @module     isl29003

*******************************************************************************************************************************************/
STATUS ISL29003_Disable(ISL29003* driver, BOOLEAN powerDown)
{
    BYTE buf[2];
  
    
#if (CFG_NULLCHECKING)
    if (driver == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif
    
    buf[0] = 0;                                                 /* Write register 0x0 (command register) */
    
    if (powerDown) {                                            /* Assign the power down bit as requested */
        buf[1] = 0x40;
    } else {
        buf[1] = 0x0;
    }
    
    return ISL29003_Write(driver, buf, 2);                      /* Write the command to the device */
}
    
/***************************************************************************************************************************************//**

    Sets the timeout, in kernel ticks, to be used by the driver for I/O operations.

    @param[in]  driver      A pointer to the driver to receive the new timeout value.
    @param[in]  timeout     The new timeout value, in kernel ticks, for the driver. 

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The driver timeout has been updated.
     ERR_NULLREFERENCE      | The argument 'driver' was found to be NULL.

    @module     isl29003

*******************************************************************************************************************************************/
STATUS ISL29003_SetTimeout(ISL29003* driver, UINT32 timeout)
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

    Writes data to the device. The first byte of data is the address of the register to receive the data.

    @param[in]  driver      A pointer to the target driver instance.
    @param[in]  data        A pointer to the data to be written to the device. The first bytes is the address of the register to receive
                            the subsequent data bytes.
    @param[in]  nbytes      The total amount, in bytes, to be written to the device.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The data has been written to the device.
     ERR_NULLREFERENCE      | The argument 'driver' or 'data' was found to be NULL.
     ERR_DEVICENAK          | The target device returned a NAK.
     ERR_INCOMPLETE         | An error occurred while transferring the data and the transfer did not complete.

    @module     isl29003

*******************************************************************************************************************************************/
STATUS ISL29003_Write(ISL29003* driver, const void* data, UINT32 nbytes)
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

    status = I2C_Claim(driver->port, driver->timeout);          /* Claim exclusive access to the bus */
    if (status != SUCCESS) {
        return status;
    }
    
    status = I2C_Write(driver->port,                            /* Write the data to the bus */
                       driver->address,
                       data,
                       nbytes,
                       driver->timeout);
    
    I2C_Release(driver->port);                                  /* Release the claim on the bus */
    return status;
}

/***************************************************************************************************************************************//**

    Reads and returns data from the device.

    @param[in]  driver      A pointer to the target driver instance.
    @param[in]  reg         The register address to be read.
    @param[out] buf         A pointer to a caller allocated buffer to receive the returned data.
    @param[in]  nbytes      The total amount, in bytes, to be read and returned.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The data has been read and returned.
     ERR_NULLREFERENCE      | The argument 'driver' or 'buf' was found to be NULL.
     ERR_DEVICENAK          | The target device returned a NAK.
     ERR_INCOMPLETE         | An error occurred while transferring the data and the transfer did not complete.

    @module     isl29003

*******************************************************************************************************************************************/
STATUS ISL29003_Read(ISL29003* driver, BYTE reg, void* buf, UINT32 nbytes)
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

    status = I2C_Claim(driver->port, driver->timeout);          /* Claim exclusive access to the bus */
    if (status != SUCCESS) {
        return status;
    }

    status = I2C_Write(driver->port,                            /* Write the register address to be read */
                       driver->address,
                       &reg,
                       1,
                       driver->timeout);
    
    if (status == SUCCESS) {
        status = I2C_Read(driver->port,                         /* Read the requested data */
                          driver->address,
                          buf,
                          nbytes,
                          driver->timeout);
    }
        
    I2C_Release(driver->port);                                  /* Release the claim on the bus */
    return status;    
}

/***************************************************************************************************************************************//**

    Reads and returns the current sensor reading from the device.

    @param[in]  driver      A pointer to the target driver instance.
    @param[out] value       A pointer to a caller allocated variable to receive the sensor value.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The sensor value has been returned.
     ERR_NULLREFERENCE      | The argument 'driver' or 'value' was found to be NULL.
     ERR_INVALIDCONTEXT     | This operation is not supported from the context of an interrupt service routine (ISR).
     ERR_DEVICENAK          | The target device returned a NAK.
     ERR_INCOMPLETE         | An error occurred while transferring the data and the transfer did not complete.

    @module     isl29003

*******************************************************************************************************************************************/
STATUS ISL29003_ReadSensor(ISL29003* driver, UINT16* value)
{
    return ISL29003_Read(driver, 0x4, value, 2);                /* Read 2-bytes starting at register 0x4 for the sensor value */
}

/***************************************************************************************************************************************//**

    Reads and returns the current timer value from the device.

    @param[in]  driver      A pointer to the target driver instance.
    @param[out] value       A pointer to a caller allocated variable to receive the timer value.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The timer value has been returned.
     ERR_NULLREFERENCE      | The argument 'driver' or 'value' was found to be NULL.
     ERR_DEVICENAK          | The target device returned a NAK.
     ERR_INCOMPLETE         | An error occurred while transferring the data and the transfer did not complete.

    @module     isl29003

*******************************************************************************************************************************************/
STATUS ISL29003_ReadTimer(ISL29003* driver, UINT16* value)
{
    return ISL29003_Read(driver, 0x6, value, 2);                /* Read 2-bytes starting at register 0x6 for the timer value */
}
