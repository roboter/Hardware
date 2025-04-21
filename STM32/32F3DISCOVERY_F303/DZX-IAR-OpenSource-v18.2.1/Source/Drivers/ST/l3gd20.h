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
#ifndef L3GD20_H__
#define L3GD20_H__

#include "Kernel/kernel.h"
#include "mcu_spi.h"

/*******************************************************************************************************************************************
    TYPE DEFINITIONS
*******************************************************************************************************************************************/
typedef struct L3GD20 L3GD20;
typedef struct L3GD20_SAMPLE L3GD20_SAMPLE;
typedef enum L3GD20_SENSITIVITY L3GD20_SENSITIVITY;
typedef struct L3GD20_CTRL L3GD20_CTRL;

/***************************************************************************************************************************************//**

    A sample from the gyro.
    @module     st-l3gd20

*******************************************************************************************************************************************/
struct L3GD20_SAMPLE {
    float x;    /**< The current X-Axis DPS value */
    float y;    /**< The current Y-Axis DPS value */
    float z;    /**< The current Z-Axis DPS value */
};

/***************************************************************************************************************************************//**

    A sensitivity setting for the gyroscope.
    @module     st-l3gd20

*******************************************************************************************************************************************/
enum L3GD20_SENSITIVITY {
    L3GD20_SENSITIVITY_250DPS = 0,      /**< Indicates 250 DPS full scale */
    L3GD20_SENSITIVITY_500DPS,          /**< Indicates 500 DPS full scale */    
    L3GD20_SENSITIVITY_2000DPS,         /**< Indicates 2000 DPS full scale */
};

/***************************************************************************************************************************************//**

    Represents the control registers within the device.
    @module     st-l3gd20

*******************************************************************************************************************************************/
PREPACKED struct L3GD20_CTRL {
    struct {
        BYTE XEN            :1;         /**< X-Axis enable. Default is 1. */
        BYTE YEN            :1;         /**< Y-Axis enable. Default is 1. */
        BYTE ZEN            :1;         /**< Z-Axis enable. Default is 1. */
        BYTE PD             :1;         /**< Power-down mode enable. Default is 0. */
        BYTE BW             :2;         /**< Bandwidth selection. */
        BYTE DR             :2;         /**< Output data rate */
    } CTRL1;
    
    struct {
        BYTE HPCF           :4;         /**< High-pass filter cutoff frequency selection */
        BYTE HPM            :2;         /**< High-pass filter mode selection */
        BYTE reserved       :2;
    } CTRL2;
    
    struct {
        BYTE I2EMPTY        :1;         /**< FIFO empty interrupt on DRDY/INT2. Default 0. (0:disable, 1:enable) */
        BYTE I2ORUN         :1;         /**< FIFO overrun interrupt on DRDY/INT2. Default 0. (0:disable, 1:enable) */
        BYTE I2WTM          :1;         /**< FIFO watermark interrupt on DRDY/INT2. Default 0. (0:disable, 1:enable) */
        BYTE I2DRDY         :1;         /**< Data-ready on DRDY/INT2. Default 0. (0:disable, 1:enable) */
        BYTE PPOD           :1;         /**< Push-pull/Open drain. Default 0. (0:push-pull, 1:open drain) */
        BYTE HLACTIVE       :1;         /**< Interrupt active configuration on INT1. Default 0. (0:high, 1:low) */
        BYTE I1BOOT         :1;         /**< Boot status available on INT1. Default 0. (0:disable, 1:enable) */
        BYTE I1INT          :1;         /**< Interrupt enable on INT1 pin. Default 0. (0:disable, 1:enable) */
    } CTRL3;
    
    struct {
        BYTE SIM            :1;         /**< SPI serial interface mode selection. Default 0. (0:4-wire, 1:3-wire) */
        BYTE reserved       :3;
        BYTE FS             :2;         /**< Full scale selection. Default 0. (0:250dps, 1:500dps, 2:2000dps, 3:2000dps) */
        BYTE BLE            :1;         /**< Big/little endian data selection. Default 0. (0:LSb@lower, 1:MSb@lower) */
        BYTE BDU            :1;         /**< Block data update. Default 0. (0:continuous, 1:when MSb and LSb reading) */
    } CTRL4;
    
    struct {
        BYTE OUTSEL         :2;         /**< Output selection configuration. Default 0. */
        BYTE INTSEL         :2;         /**< INT1 selection configuration. Deafult 0. */
        BYTE HPEN           :1;         /**< High-pass filter enable. Default 0. */
        BYTE reserved       :1;
        BYTE FIFOEN         :1;         /**< FIFO enable. */
        BYTE BOOT           :1;         /**< Reboot memory content. */
    } CTRL5;
    
} POSTPACKED;


/***************************************************************************************************************************************//**

    Represents an instance of the ST L3GD20 device driver.
    @module     st-l3gd20

*******************************************************************************************************************************************/
struct L3GD20 {
    SPI* port;                                                  /**< A pointer to the SPI port used for communications with the device. */
    PIN cs;                                                     /**< The chip select pin for the device */
    UINT32 timeout;                                             /**< The timeout value used for I/O operations with the device */
    L3GD20_CTRL ctrl;                                           /**< A cache of the device control registers */
};

/*******************************************************************************************************************************************
    PUBLIC FUNCTIONS
*******************************************************************************************************************************************/
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
extern STATUS L3GD20_Open(L3GD20* driver, SPI* port, PIN cs);

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
extern STATUS L3GD20_ReadID(L3GD20* driver, BYTE* id);

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
extern STATUS L3GD20_Read(L3GD20* driver, BYTE reg, void* buf, UINT32 nbytes);

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
extern STATUS L3GD20_Write(L3GD20* driver, const void* data, UINT32 nbytes);

/***************************************************************************************************************************************//**

    Returns the current control register values for the device.

    @param[in]  driver      A pointer to the target L3GD20 driver.

    @return     A pointer to the control register values for the device.
    @module     st-l3gd20

*******************************************************************************************************************************************/
extern L3GD20_CTRL* L3GD20_Ctrl(L3GD20* driver); 

/***************************************************************************************************************************************//**

    Returns whether the device is currently enabled or disabled.

    @param[in]  driver      A pointer to the target driver.

    @return     TRUE if the device is currently enabled; otherwise FALSE.
    @module     st-l3gd20

*******************************************************************************************************************************************/
extern BOOLEAN L3GD20_Enabled(L3GD20* driver);

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
extern STATUS L3GD20_SetEnabled(L3GD20* driver, BOOLEAN enabled);

/***************************************************************************************************************************************//**

    Returns the current sensitivity setting for the device.

    @param[in]  driver      A pointer to the target L3GD20 driver.

    @return     The current sensitivity setting for the device.
    @module     st-l3gd20

*******************************************************************************************************************************************/
extern L3GD20_SENSITIVITY L3GDSO_Sensitivity(L3GD20* driver);

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
extern STATUS L3GD20_SetSensitivity(L3GD20* driver, L3GD20_SENSITIVITY value);

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
extern STATUS L3GD20_SubmitChanges(L3GD20* driver);

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
extern STATUS L3GD20_ReadSample(L3GD20* driver, L3GD20_SAMPLE* sample);

#endif /* L3GD20_H__ */
