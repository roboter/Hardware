/*******************************************************************************************************************************************

    DZX | STMICRO | L3GD20                                                                                                VERSION 18.2.1
    ------------------------------------------------------------------------------------------------------------------------------------

    This is a driver for the STMicro L3GD20 digital gyroscope.

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
#include "Drivers/ST/l3gd20.h"
#include <string.h>

/***************************************************************************************************************************************//**

    Creates and initializes an instance of the ST L3GD20 device driver.

    @param[in]  driver      A pointer to a caller allocated instance of a L3GD20 driver to be initialized.
    @param[in]  port        A pointer to an open SPI port to be used for communications.
    @param[in]  cs          The pin to be used as the chip select signal for the device.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The driver has been initialized and is ready for communications.
     ERR_NULLREFERENCE      | The argument 'driver' or 'port' was found to be NULL.

    @module     st-l3gd20

*******************************************************************************************************************************************/
STATUS L3GD20_Open(L3GD20* driver, SPI* port, PIN cs)
{
    STATUS status;
    
    
#if (CFG_NULLCHECKING)
    if (driver == NULL) {
        return ERR_NULLREFERENCE;
    }
    
    if (port == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif
    
    driver->port = port;                                        /* Assign the SPI port */
    driver->cs = cs;
    driver->timeout = MILLISECOND_TICKS(1000);                  /* Default I/O timeout = 1 second */
    
    PIN_Write(cs, 1);                                           /* Initialize the chip select signal state */
    
    status = L3GD20_Read(driver, 0x20, &driver->ctrl, 5);       /* Cache the current control registers of the device */
    if (status != SUCCESS) {
        return status;
    }
    
    return SUCCESS;
}

/***************************************************************************************************************************************//**

    Reads and returns the identifier from the device.

    @param[in]  driver      A pointer to the driver to be used for communications.
    @param[out] id          A pointer to a caller allocated identifier to retrieve the value received from the device.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The identifier value has been returned.
     ERR_NULLREFERENCE      | The argument 'driver' or 'id' was found to be NULL.

    @module     st-l3gd20

*******************************************************************************************************************************************/
STATUS L3GD20_ReadID(L3GD20* driver, BYTE* id)
{
    STATUS status;
    
    
#if (CFG_NULLCHECKING)
    if (driver == NULL) {
        return ERR_NULLREFERENCE;
    }
    
    if (id == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif
    
    status = L3GD20_Read(driver, 0x0F, id, sizeof(BYTE));       /* Read the 'who am I' register */
    if (status != SUCCESS) {
        return status;
    }
    
    return SUCCESS;
}

/***************************************************************************************************************************************//**

    Reads data directly from the device.

    @param[in]  driver      A pointer to the L3GD20 driver to be used for communications.
    @param[in]  reg         The starting register to be read.
    @param[out] buf         A pointer to a caller allocated buffer to retrieve the received data.
    @param[in]  nbytes      The number of data bytes to be read and returned.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The specified amount of data has been received and returned.
     ERR_NULLREFERENCE      | The argument 'driver' or 'buf' was found to be NULL.
     ERR_TIMEOUT            | The maximum amount of time has elapsed prior to completing the transfer with the device.

    @module     st-l3gd20

*******************************************************************************************************************************************/
STATUS L3GD20_Read(L3GD20* driver, BYTE reg, void* buf, UINT32 nbytes)
{
    STATUS status;
    BYTE req;
    
    
#if (CFG_NULLCHECKING)
    if (driver == NULL) {
        return ERR_NULLREFERENCE;
    }
    
    if (buf == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif
    
    req = reg | 0xC0;                                           /* Set to 'read' and 'auto increment' */
    
    status = SPI_Select(driver->port,                           /* Select the device */
                        driver->cs, 
                        driver->timeout);
    
    if (status != SUCCESS) {
        return status;
    }

    status = SPI_Write(driver->port,                            /* Write the read command */
                       &req,
                       1,
                       driver->timeout);
    
    if (status != SUCCESS) {
        SPI_Deselect(driver->port, driver->cs);
        return status;
    }
    
    status = SPI_Read(driver->port,                             /* Read the requested amount of data */
                      buf, 
                      nbytes, 
                      driver->timeout);
    
    SPI_Deselect(driver->port, driver->cs);
    return status;
}

/***************************************************************************************************************************************//**

    Writes data directly to the device.

    @param[in]  driver      A pointer to the L3GD20 driver to be used for communications.
    @param[in]  data        A pointer to the data to be sent to the device. The first byte is the command byte.
    @param[in]  nbytes      The number of data bytes to be written.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The specified amount of data has been written to the device.
     ERR_NULLREFERENCE      | The argument 'driver' or 'data' was found to be NULL.
     ERR_TIMEOUT            | The maximum amount of time has elapsed prior to completing the transfer with the device.

    @module     st-l3gd20

*******************************************************************************************************************************************/
STATUS L3GD20_Write(L3GD20* driver, const void* data, UINT32 nbytes)
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
    
    status = SPI_Select(driver->port,                           /* Select the device (assert chip select signal) */
                        driver->cs, 
                        driver->timeout);
    
    if (status != SUCCESS) {
        return status;
    }

    status = SPI_Write(driver->port,                            /* Transfer the data to the device */
                       data,
                       nbytes,
                       driver->timeout);
    
    SPI_Deselect(driver->port, driver->cs);                     /* Deselect the device (deassert chip select signal) */
    return status;
}

/***************************************************************************************************************************************//**

    Returns the current control register values for the device.

    @param[in]  driver      A pointer to the target L3GD20 driver.

    @return     A pointer to the control register values for the device.
    @module     st-l3gd20

*******************************************************************************************************************************************/
L3GD20_CTRL* L3GD20_Ctrl(L3GD20* driver)
{
#if (CFG_NULLCHECKING)
    if (driver == NULL) {
        return NULL;
    }
#endif
    
    return &driver->ctrl;
}

/***************************************************************************************************************************************//**

    Returns whether the device is currently enabled or disabled.

    @param[in]  driver      A pointer to the target driver.

    @return     TRUE if the device is currently enabled; otherwise FALSE.
    @module     st-l3gd20

*******************************************************************************************************************************************/
BOOLEAN L3GD20_Enabled(L3GD20* driver)
{
#if (CFG_NULLCHECKING)
    if (driver == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif
    
    if (driver->ctrl.CTRL1.PD == 1)
        return TRUE;
    
    return FALSE;
}

/***************************************************************************************************************************************//**

    Enables/disables the device.

    @param[in]  driver      A pointer to the target driver to receive the new enabled value.
    @param[in]  enabled     TRUE to enable the device; FALSE to disable the device.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The enabled/disabled value has been assigned.
     ERR_NULLREFERENCE      | The argument 'driver' was found to be NULL.

    @remark     This does not actually transfer the change to the device. Use L3GD20_SubmitChanges() to push all the current
                configuration values to the physical device.
    @module     st-l3gd20

*******************************************************************************************************************************************/
STATUS L3GD20_SetEnabled(L3GD20* driver, BOOLEAN enabled)
{
#if (CFG_NULLCHECKING)
    if (driver == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif
    
    driver->ctrl.CTRL1.PD = (enabled) ? 1 : 0;                  /* Enable or power down */
    return SUCCESS;
}

/***************************************************************************************************************************************//**

    Returns the current sensitivity setting for the device.

    @param[in]  driver      A pointer to the target L3GD20 driver.

    @return     The current sensitivity setting for the device.
    @module     st-l3gd20

*******************************************************************************************************************************************/
L3GD20_SENSITIVITY L3GDSO_Sensitivity(L3GD20* driver)
{
#if (CFG_NULLCHECKING)
    if (driver == NULL) {
        return L3GD20_SENSITIVITY_250DPS;
    }
#endif
    
    switch (driver->ctrl.CTRL4.FS) {
        case 0:
        default:
            return L3GD20_SENSITIVITY_250DPS;
        case 1:
            return L3GD20_SENSITIVITY_500DPS;
        case 2:
        case 3:
            return L3GD20_SENSITIVITY_2000DPS;
    }
}

/***************************************************************************************************************************************//**

    Assigns a new sensitivity setting for the device.

    @param[in]  driver      A pointer to the target driver to receive the new sensitivity value.
    @param[in]  value       The new sensitivity value.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The new sensitivity value has been assigned.
     ERR_NULLREFERENCE      | The argument 'driver' was found to be NULL.
     ERR_NOTSUPPORTED       | The specified sensitivity value is not supported.

    @remark     This does not actually transfer the change to the device. Use L3GD20_SubmitChanges() to push all the current
                configuration values to the physical device.
    @module     st-l3gd20

*******************************************************************************************************************************************/
STATUS L3GD20_SetSensitivity(L3GD20* driver, L3GD20_SENSITIVITY value)
{
#if (CFG_NULLCHECKING)
    if (driver == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif    
    
    switch (value) {
        case L3GD20_SENSITIVITY_250DPS:
            driver->ctrl.CTRL4.FS = 0;
            return SUCCESS;
        case L3GD20_SENSITIVITY_500DPS:
            driver->ctrl.CTRL4.FS = 1;
            return SUCCESS;
        case L3GD20_SENSITIVITY_2000DPS:
            driver->ctrl.CTRL4.FS = 2;
            return SUCCESS;
    }
    
    return ERR_NOTSUPPORTED;
}

/***************************************************************************************************************************************//**

    Submits all changes made to the control registers within the driver to the physical device.

    @param[in]  driver      A pointer to the target driver.
    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The physical device has been updated.
     ERR_NULLREFERENCE      | The argument 'driver' was found to be NULL.
     ERR_TIMEOUT            | The maximum amount of time has elapsed prior to completing the transfer with the device.

    @module     st-l3gd20

*******************************************************************************************************************************************/
STATUS L3GD20_SubmitChanges(L3GD20* driver)
{
    BYTE buf[6];
    
    
#if (CFG_NULLCHECKING)
    if (driver == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif 
    
    buf[0] = 0x60;
    memcpy(&buf[1], &driver->ctrl, 5);
    
    return L3GD20_Write(driver, buf, 6);
}

/***************************************************************************************************************************************//**

    Receives and returns a data sample from the device.

    @param[in]  driver      A pointer to the target L3GD20 driver.
    @param[out] sample      A pointer to a caller allocated sample to be filled.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The sample value has been returned.
     ERR_NULLREFERENCE      | The argument 'driver' or 'sample' was found to be NULL.
     ERR_TIMEOUT            | The maximum amount of time has elapsed prior to completing the transfer with the device.

    @module     st-l3gd20

*******************************************************************************************************************************************/
STATUS L3GD20_ReadSample(L3GD20* driver, L3GD20_SAMPLE* sample)
{
    STATUS status;
    INT16 buf[3];
    float factor;
    
    
#if (CFG_NULLCHECKING)
    if (driver == NULL) {
        return ERR_NULLREFERENCE;
    }
    
    if (sample == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif
    
    status = L3GD20_Read(driver, 0x28, buf, 6);
    if (status != SUCCESS) {
        return status;
    }
    
    switch (L3GDSO_Sensitivity(driver)) {                       /* Get the dps per digit based upon sensitivity setting */
        case L3GD20_SENSITIVITY_250DPS:
        default:
            factor = 0.00875;
            break;
        case L3GD20_SENSITIVITY_500DPS:
            factor = 0.01750;
            break;
        case L3GD20_SENSITIVITY_2000DPS:
            factor = 0.070;
            break;
    }
    
    sample->x = (float)buf[0] * factor;                         /* Convert each reading into dps */
    sample->y = (float)buf[1] * factor;
    sample->z = (float)buf[2] * factor;

    return status;
}
