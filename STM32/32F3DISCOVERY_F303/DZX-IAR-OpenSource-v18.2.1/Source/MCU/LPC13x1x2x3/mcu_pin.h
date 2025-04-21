/*******************************************************************************************************************************************

    DZX | LPC13x1x2x3 | PIN                                                                                               VERSION 18.2.1
    ------------------------------------------------------------------------------------------------------------------------------------

    This is part of the MCU peripheral drivers and provides support for reading and writing the MCU pins.

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
#ifndef MCU_PIN_H__
#define MCU_PIN_H__

#include "Kernel/kernel.h"

/*******************************************************************************************************************************************
    REGISTER DEFINITIONS
*******************************************************************************************************************************************/


/*******************************************************************************************************************************************
    TYPE DEFINITIONS
*******************************************************************************************************************************************/
typedef enum LPC13X1X2X3_PORT PORT;
typedef enum LPC13X1X2X3_PIN PIN;
typedef enum LPC13X1X2X3_DIRECTION DIRECTION;
typedef enum LPC13X1X2X3_EDGE EDGE;

/***************************************************************************************************************************************//**

    Represents a port of pins within the MCU.
    @module     pin-lpc13x1x2x3

*******************************************************************************************************************************************/
enum LPC13X1X2X3_PORT {
	PORT_0 = 0,     /**< Pin Port 0 */
	PORT_1,         /**< Pin Port 1 */
	PORT_2,         /**< Pin Port 2 */
	PORT_3,         /**< Pin Port 3 */
	PORT_MAX
};

/***************************************************************************************************************************************//**

    Represents an individual pin on the MCU.
        
    @remark     The upper 16-bits of the value represents the offset to locate the IOCON register for the pin. The lower 16-bits
                represents the GPIO port number and pin number.
    @module     pin-lpc13x1x2x3

*******************************************************************************************************************************************/
enum LPC13X1X2X3_PIN {
	P0_00 = 0x000C0000,  /**< P0.0 */
	P0_01 = 0x00100001,  /**< P0.1 */
	P0_02 = 0x001C0002,  /**< P0.2 */
	P0_03 = 0x002C0003,  /**< P0.3 */
	P0_04 = 0x00300004,  /**< P0.4 */
	P0_05 = 0x00340005,  /**< P0.5 */
	P0_06 = 0x004C0006,  /**< P0.6 */
	P0_07 = 0x00500007,  /**< P0.7 */
	P0_08 = 0x00600008,  /**< P0.8 */
	P0_09 = 0x00640009,  /**< P0.9 */
	P0_10 = 0x0068000A,  /**< P0.10 */
	P0_11 = 0x0074000B,  /**< P0.11 */

	P1_00 = 0x00780100,  /**< P1.0 */
	P1_01 = 0x007C0101,  /**< P1.1 */
	P1_02 = 0x00800102,  /**< P1.2 */
	P1_03 = 0x00900103,  /**< P1.3 */
	P1_04 = 0x00940104,  /**< P1.4 */
	P1_05 = 0x00A00105,  /**< P1.5 */
	P1_06 = 0x00A40106,  /**< P1.6 */
	P1_07 = 0x00A80107,  /**< P1.7 */
	P1_08 = 0x00140108,  /**< P1.8 */
	P1_09 = 0x00380109,  /**< P1.9 */
	P1_10 = 0x006C010A,  /**< P1.10 */
	P1_11 = 0x0098010B,  /**< P1.11 */

	P2_00 = 0x00080200,  /**< P2.0 */
	P2_01 = 0x00280201,  /**< P2.1 */
	P2_02 = 0x005C0202,  /**< P2.2 */
	P2_03 = 0x008C0203,  /**< P2.3 */
	P2_04 = 0x00400204,  /**< P2.4 */
	P2_05 = 0x00440205,  /**< P2.5 */
	P2_06 = 0x00000206,  /**< P2.6 */
	P2_07 = 0x00200207,  /**< P2.7 */
	P2_08 = 0x00240208,  /**< P2.8 */
	P2_09 = 0x00540209,  /**< P2.9 */
	P2_10 = 0x0058020A,  /**< P2.10 */
	P2_11 = 0x0070020B,  /**< P2.11 */

	P3_00 = 0x00840300,  /**< P3.0 */
	P3_01 = 0x00880301,  /**< P3.1 */
	P3_02 = 0x009C0302,  /**< P3.2 */
	P3_03 = 0x00AC0303,  /**< P3.3 */
	P3_04 = 0x003C0304,  /**< P3.4 */
	P3_05 = 0x00480305,  /**< P3.5 */

	PIN_INVALID = 0xFFFF,       /* An invalid pin */
};

/***************************************************************************************************************************************//**

    Describes a possible pin direction setting.
    @module     PIN-LPC175x6x

*******************************************************************************************************************************************/
enum LPC13X1X2X3_DIRECTION {
    DIRECTION_INPUT = 0,        /**< Indicates the pin is configured as an input */
    DIRECTION_OUTPUT            /**< Indicates the pin is configured as an output */
};

/***************************************************************************************************************************************//**

    Describes a possible signal edge.
    @module     pin-lpc13x1x2x3

*******************************************************************************************************************************************/
enum LPC13X1X2X3_EDGE {
	EDGE_NONE       = 0,        /**< Indicates no edges */
	EDGE_RISING     = 1,        /**< Indicates rising-edge signals only */
	EDGE_FALLING    = 2,        /**< Indicates falling-edge signals only */
	EDGE_BOTH       = 3,        /**< Indicates both rising and falling edge signals */
    
    EDGE_INVALID    = 0xFFFF
};

#define PIN_NUMBER(pin)             (pin & 0xFF)                /* Get a pin's pin number */
#define PIN_PORTNUMBER(pin)         ((pin >> 8) & 0xFF)         /* Get a pin's port number */

#define REG_GPIODATABASE            (0x50000000)                /* The GPIO data registers base address */

#define REG_IOCONBASE               0x40044000

#define REG_IOCONPIO01              REG_32(0x40044010)
#define REG_IOCONPIO02              REG_32(0x4004401C)
#define REG_IOCONPIO03              REG_32(0x4004402C)
#define REG_IOCONPIO04              REG_32(0x40044030)
#define REG_IOCONPIO05              REG_32(0x40044034)
#define REG_IOCONPIO06              REG_32(0x4004404C)
#define REG_IOCONPIO07              REG_32(0x40044050)
#define REG_IOCONPIO08              REG_32(0x40044060)
#define REG_IOCONPIO09              REG_32(0x40044064)
#define REG_IOCONSWCLKPIO010        REG_32(0x40044068)
#define REG_IOCONRPIO011            REG_32(0x40044074)
#define REG_IOCONRPIO10             REG_32(0x40044078)
#define REG_IOCONRPIO11             REG_32(0x4004407C)
#define REG_IOCONRPIO12             REG_32(0x40044080)
#define REG_IOCONSWDIOPIO13         REG_32(0x40044090)
#define REG_IOCONPIO14              REG_32(0x40044094)
#define REG_IOCONPIO15              REG_32(0x400440A0)
#define REG_IOCONPIO16              REG_32(0x400440A4)
#define REG_IOCONPIO17              REG_32(0x400440A8)
#define REG_IOCONPIO18              REG_32(0x40044014)
#define REG_IOCONPIO19              REG_32(0x40044038)
#define REG_IOCONPIO110             REG_32(0x4004406C)
#define REG_IOCONPIO111             REG_32(0x40044098)
#define REG_IOCONPIO20              REG_32(0x40044008)
#define REG_IOCONPIO21              REG_32(0x40044028)
#define REG_IOCONPIO22              REG_32(0x4004405C)
#define REG_IOCONPIO23              REG_32(0x4004408C)
#define REG_IOCONPIO24              REG_32(0x40044040)
#define REG_IOCONPIO25              REG_32(0x40044044)
#define REG_IOCONPIO26              REG_32(0x40044000)
#define REG_IOCONPIO27              REG_32(0x40044020)
#define REG_IOCONPIO28              REG_32(0x40044024)
#define REG_IOCONPIO29              REG_32(0x40044054)
#define REG_IOCONPIO210             REG_32(0x40044058)
#define REG_IOCONPIO211             REG_32(0x40044070)
#define REG_IOCONPIO30              REG_32(0x40044084)
#define REG_IOCONPIO31              REG_32(0x40044088)
#define REG_IOCONPIO32              REG_32(0x4004409C)
#define REG_IOCONPIO33              REG_32(0x400440AC)
#define REG_IOCONPIO34              REG_32(0x4004403C)
#define REG_IOCONPIO35              REG_32(0x40044048)

#define REG_GPIO0DIR                REG_32(0x50008000)
#define REG_GPIO1DIR                REG_32(0x50018000)
#define REG_GPIO2DIR                REG_32(0x50028000)
#define REG_GPIO3DIR                REG_32(0x50038000)

#define REG_GPIO0DATA               REG_32(0x50003FFC)
#define REG_GPIO1DATA               REG_32(0x50013FFC)
#define REG_GPIO2DATA               REG_32(0x50023FFC)
#define REG_GPIO3DATA               REG_32(0x50033FFC)


/*******************************************************************************************************************************************
    PUBLIC FUNCTIONS
*******************************************************************************************************************************************/
/***************************************************************************************************************************************//**

    Writes a value to a pin.

    @param[in]  pin         The target pin.
    @param[in]  value       The new value for the specified pin. Use '1' (or 'HIGH') to set the pin as logic level high, or use '0' 
                            (or 'LOW') to set the pin as logic level low.

    @return     None.
    @module     pin-lpc13x1x2x3

*******************************************************************************************************************************************/
extern void PIN_Write(PIN pin, UINT32 value);

/***************************************************************************************************************************************//**

    Reads and returns the current state of a pin.

    @param[in]  pin         The target pin.

    @return     A value '1' if the pin is currently high; otherwise '0' if low.
    @module     pin-lpc13x1x2x3

*******************************************************************************************************************************************/
extern UINT32 PIN_Read(PIN pin);

/***************************************************************************************************************************************//**

    Returns the current function of a pin.

    @param[in]  pin         The target pin.

    @return     The function number assigned to the specified to the pin.
    @module     pin-lpc13x1x2x3

*******************************************************************************************************************************************/
extern BYTE PIN_Function(PIN pin);

/***************************************************************************************************************************************//**

    Sets the function for a pin.

    @param[in]  pin         The pin to be configured.
    @param[in]  function    The new function for the pin.

    @return     None.
    @module     pin-lpc13x1x2x3

*******************************************************************************************************************************************/
extern void PIN_SetFunction(PIN pin, BYTE function);

/***************************************************************************************************************************************//**

    Assigns a new direction setting for a pin.

    @param[in]  pin         The target pin to receive the new direction setting.
    @param[in]  dir         The new direction setting for the pin.

     Direction              | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     DIRECTION_OUTPUT       | Use to configure the pin as an output.
     DIRECTION_INPUT        | Use to configure the pin as an input.

    @return     None.
    @module     pin-lpc13x1x2x3

*******************************************************************************************************************************************/
extern void PIN_SetDirection(PIN pin, DIRECTION dir);

/***************************************************************************************************************************************//**

    Returns the current direction setting for a pin.

    @param[in]  pin         The target pin.

    @return

     Direction              | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     DIRECTION_OUTPUT       | The pin is configured as an output.
     DIRECTION_INPUT        | The pin is configured as an input.

    @module     pin-lpc13x1x2x3

*******************************************************************************************************************************************/
extern DIRECTION PIN_Direction(PIN pin);

/***************************************************************************************************************************************//**

    Reads and returns the direction bits for each of the pins on a port.

    @param[in]  port        The target pin port.

    @return     A bit-field indicating the configured direction for each of the pins on the specified port. A bit value of '1' indicates 
                the pin is configured as an output while a '0' indicates configured as an input.
    @module     pin-lpc13x1x2x3

*******************************************************************************************************************************************/
extern UINT32 PORT_Direction(PORT port);

/***************************************************************************************************************************************//**

    Sets the direction for each of the pins on a port.

    @param[in]  port        The target pin port.
    @param[in]  value       A bit-field that specifies a direction for each of the pins. A bit value of '1' indicates the pin to be 
                            configured as an output while a '0' indicates to be configured as an input.

    @return     None.
    @module     pin-lpc13x1x2x3

*******************************************************************************************************************************************/
extern void PORT_SetDirection(PORT port, UINT32 value);

/***************************************************************************************************************************************//**

    Reads and returns a bit-field of states of each of the pins for a port.

    @param[in]  port        The target pin port to be read and returned.

    @return     A bit value '1' indicates the pin is currently high; otherwise a '0' if the pin is low.
    @module     pin-lpc13x1x2x3

*******************************************************************************************************************************************/
extern UINT32 PORT_Read(PORT port);

/***************************************************************************************************************************************//**

    Writes and sets the states of each of the pins for a port.

    @param[in]  port        The target pin port to be written.
    @param[in]  value       A bit-field of states for each of the pins. A bit value of '1' sets the pin to a logic level high while a '0'
                            sets the pin to a logic level low.

    @return     None.
    @module     pin-lpc13x1x2x3

*******************************************************************************************************************************************/
extern void PORT_Write(PORT port, UINT32 value);

#endif /* MCU_PIN_H__ */
