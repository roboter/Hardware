/*******************************************************************************************************************************************

    DZX | LPC175x6x | PIN                                                                                                 VERSION 18.2.1
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
#define REG_GPIO0          ((REG_GPIO*)(0x2009C000))   /**< The GPIO registers for port 0 */
#define REG_GPIO1          ((REG_GPIO*)(0x2009C020))   /**< The GPIO registers for port 1 */
#define REG_GPIO2          ((REG_GPIO*)(0x2009C040))   /**< The GPIO registers for port 2 */
#define REG_GPIO3          ((REG_GPIO*)(0x2009C060))   /**< The GPIO registers for port 3 */
#define REG_GPIO4          ((REG_GPIO*)(0x2009C080))   /**< The GPIO registers for port 4 */

#define PINFROMNUMBERS(port, pin)   (PIN)((port << 8) | (pin))          /* Convert port & pin numbers into a pin */
#define PIN_NUMBER(pin)             (pin & 0xFF)                        /* Get a pin's pin number */
#define PIN_PORTNUMBER(pin)         ((pin >> 8) & 0xFF)                 /* Get a pin's port number */

#define REGGPIOINT0BASE   0x40028090                                     /**< Base interrupt register address for port 0 */
#define REGGPIOINT2BASE   0x400280B0                                     /**< Base interrupt register address for port 2 */
#define REGGPIOINT0       ((GPIOINTREGISTERS*)REGGPIOINT0BASE)           /**< The GPIO interrupt registers for port 0 */
#define REGGPIOINT2       ((GPIOINTREGISTERS*)REGGPIOINT2BASE)           /**< The GPIO interrupt registers for port 2 */

#define REG_PINSEL(pin)     (void*)(0x4002C000 + (PIN_PORTNUMBER(pin) << 3) + ((PIN_NUMBER(pin) >> 4) << 2))
#define REG_PINMODE(pin)    (void*)(0x4002C040 + (PIN_PORTNUMBER(pin) << 3) + ((PIN_NUMBER(pin) >> 4) << 2))
#define REG_PINOD(pin)      (void*)(0x4002C068 + (PIN_PORTNUMBER(pin) << 3) + ((PIN_NUMBER(pin) >> 4) << 2))

typedef struct REG_GPIO {
	PREG_32(FIODIR);           /**< The FIODIR register for the port */
	volatile UINT32 reserved[3];
	PREG_32(FIOMASK);          /**< The FIOMASK register for the port */
	PREG_32(FIOPIN);           /**< The FIOPIN register for the port */
	PREG_32(FIOSET);           /**< The FIOSET register for the port */
	PREG_32(FIOCLR);           /**< The FIOCLR register for the port */
} REG_GPIO;

typedef struct GPIOINTREGISTERS {
	PREG_32(INTENR);        /**< The INTENR register for the port */
	PREG_32(INTENF);        /**< The INTENF register for the port */
	PREG_32(INTSTATR);      /**< The INTSTATR register for the port */
	PREG_32(INTSTATF);      /**< The INTSTATF register for the port */
	PREG_32(INTCLR);        /**< The INTCLR register for the port */
} GPIOINTREGISTERS;

#define REG_PINSEL0                 REG_32(0x4002C000)
#define REG_PINSEL1                 REG_32(0x4002C004)
#define REG_PINSEL2                 REG_32(0x4002C008)
#define REG_PINSEL3                 REG_32(0x4002C00C)
#define REG_PINSEL4                 REG_32(0x4002C010)
#define REG_PINSEL7                 REG_32(0x4002C01C)
#define REG_PINSEL8                 REG_32(0x4002C020)
#define REG_PINSEL9                 REG_32(0x4002C024)
#define REG_PINSEL10                REG_32(0x4002C028)

#define REG_PINMODE0                REG_32(0x4002C040)
#define REG_PINMODE1                REG_32(0x4002C044)
#define REG_PINMODE2                REG_32(0x4002C048)
#define REG_PINMODE3                REG_32(0x4002C04C)
#define REG_PINMODE4                REG_32(0x4002C050)
#define REG_PINMODE5                REG_32(0x4002C054)
#define REG_PINMODE6                REG_32(0x4002C058)
#define REG_PINMODE7                REG_32(0x4002C05C)
#define REG_PINMODE8                REG_32(0x4002C060)
#define REG_PINMODE9                REG_32(0x4002C064)
#define REG_PINMODEOD0              REG_32(0x4002C068)
#define REG_PINMODEOD1              REG_32(0x4002C06C)
#define REG_PINMODEOD2              REG_32(0x4002C070)
#define REG_PINMODEOD3              REG_32(0x4002C074)
#define REG_PINMODEOD4              REG_32(0x4002C078)

#define REG_FIO0DIR                 REG_32(0x2009C000)
#define REG_FIO1DIR                 REG_32(0x2009C020)
#define REG_FIO2DIR                 REG_32(0x2009C040)
#define REG_FIO3DIR                 REG_32(0x2009C060)
#define REG_FIO4DIR                 REG_32(0x2009C080)

/*******************************************************************************************************************************************
    TYPE DEFINITIONS
*******************************************************************************************************************************************/
typedef enum LPC175X6X_PORT PORT;
typedef enum LPC175X6X_PIN PIN;
typedef enum LPC175X6X_DIRECTION DIRECTION;
typedef enum LPC175X6X_MODE MODE;
typedef enum LPC175X6X_EDGE EDGE;

/***************************************************************************************************************************************//**

    Represents a port of pins within the MCU.
    @module     pin-lpc175x6x

*******************************************************************************************************************************************/
enum LPC175X6X_PORT {
	PORT_0 = 0,     /**< Pin Port 0 */
	PORT_1,         /**< Pin Port 1 */
	PORT_2,         /**< Pin Port 2 */
	PORT_3,         /**< Pin Port 3 */
	PORT_4,         /**< Pin Port 4 */
	PORT_MAX
};

/***************************************************************************************************************************************//**

    Represents an individual pin on the MCU.
    @module     pin-lpc175x6x

*******************************************************************************************************************************************/
enum LPC175X6X_PIN {
	P0_00 = 0x0000,  /**< P0.0 */
	P0_01 = 0x0001,  /**< P0.1 */
	P0_02 = 0x0002,  /**< P0.2 */
	P0_03 = 0x0003,  /**< P0.3 */
	P0_04 = 0x0004,  /**< P0.4 */
	P0_05 = 0x0005,  /**< P0.5 */
	P0_06 = 0x0006,  /**< P0.6 */
	P0_07 = 0x0007,  /**< P0.7 */
	P0_08 = 0x0008,  /**< P0.8 */
	P0_09 = 0x0009,  /**< P0.9 */
	P0_10 = 0x000A,  /**< P0.10 */
	P0_11 = 0x000B,  /**< P0.11 */
	P0_12 = 0x000C,  /**< P0.12 */
	P0_13 = 0x000D,  /**< P0.13 */
	P0_14 = 0x000E,  /**< P0.14 */
	P0_15 = 0x000F,  /**< P0.15 */
	P0_16 = 0x0010,  /**< P0.16 */
	P0_17 = 0x0011,  /**< P0.17 */
	P0_18 = 0x0012,  /**< P0.18 */
	P0_19 = 0x0013,  /**< P0.19 */
	P0_20 = 0x0014,  /**< P0.20 */
	P0_21 = 0x0015,  /**< P0.21 */
	P0_22 = 0x0016,  /**< P0.22 */
	P0_23 = 0x0017,  /**< P0.23 */
	P0_24 = 0x0018,  /**< P0.24 */
	P0_25 = 0x0019,  /**< P0.25 */
	P0_26 = 0x001A,  /**< P0.26 */
	P0_27 = 0x001B,  /**< P0.27 */
	P0_28 = 0x001C,  /**< P0.28 */
	P0_29 = 0x001D,  /**< P0.29 */
	P0_30 = 0x001E,  /**< P0.30 */
	P0_31 = 0x001F,  /**< P0.31 */


	P1_00 = 0x0100,  /**< P1.0 */
	P1_01 = 0x0101,  /**< P1.1 */
	P1_02 = 0x0102,  /**< P1.2 */
	P1_03 = 0x0103,  /**< P1.3 */
	P1_04 = 0x0104,  /**< P1.4 */
	P1_05 = 0x0105,  /**< P1.5 */
	P1_06 = 0x0106,  /**< P1.6 */
	P1_07 = 0x0107,  /**< P1.7 */
	P1_08 = 0x0108,  /**< P1.8 */
	P1_09 = 0x0109,  /**< P1.9 */
	P1_10 = 0x010A,  /**< P1.10 */
	P1_11 = 0x010B,  /**< P1.11 */
	P1_12 = 0x010C,  /**< P1.12 */
	P1_13 = 0x010D,  /**< P1.13 */
	P1_14 = 0x010E,  /**< P1.14 */
	P1_15 = 0x010F,  /**< P1.15 */
	P1_16 = 0x0110,  /**< P1.16 */
	P1_17 = 0x0111,  /**< P1.17 */
	P1_18 = 0x0112,  /**< P1.18 */
	P1_19 = 0x0113,  /**< P1.19 */
	P1_20 = 0x0114,  /**< P1.20 */
	P1_21 = 0x0115,  /**< P1.21 */
	P1_22 = 0x0116,  /**< P1.22 */
	P1_23 = 0x0117,  /**< P1.23 */
	P1_24 = 0x0118,  /**< P1.24 */
	P1_25 = 0x0119,  /**< P1.25 */
	P1_26 = 0x011A,  /**< P1.26 */
	P1_27 = 0x011B,  /**< P1.27 */
	P1_28 = 0x011C,  /**< P1.28 */
	P1_29 = 0x011D,  /**< P1.29 */
	P1_30 = 0x011E,  /**< P1.30 */
	P1_31 = 0x011F,  /**< P1.31 */

	P2_00 = 0x0200,  /**< P2.0 */
	P2_01 = 0x0201,  /**< P2.1 */
	P2_02 = 0x0202,  /**< P2.2 */
	P2_03 = 0x0203,  /**< P2.3 */
	P2_04 = 0x0204,  /**< P2.4 */
	P2_05 = 0x0205,  /**< P2.5 */
	P2_06 = 0x0206,  /**< P2.6 */
	P2_07 = 0x0207,  /**< P2.7 */
	P2_08 = 0x0208,  /**< P2.8 */
	P2_09 = 0x0209,  /**< P2.9 */
	P2_10 = 0x020A,  /**< P2.10 */
	P2_11 = 0x020B,  /**< P2.11 */
	P2_12 = 0x020C,  /**< P2.12 */
	P2_13 = 0x020D,  /**< P2.13 */
	P2_14 = 0x020E,  /**< P2.14 */
	P2_15 = 0x020F,  /**< P2.15 */
	P2_16 = 0x0210,  /**< P2.16 */
	P2_17 = 0x0211,  /**< P2.17 */
	P2_18 = 0x0212,  /**< P2.18 */
	P2_19 = 0x0213,  /**< P2.19 */
	P2_20 = 0x0214,  /**< P2.20 */
	P2_21 = 0x0215,  /**< P2.21 */
	P2_22 = 0x0216,  /**< P2.22 */
	P2_23 = 0x0217,  /**< P2.23 */
	P2_24 = 0x0218,  /**< P2.24 */
	P2_25 = 0x0219,  /**< P2.25 */
	P2_26 = 0x021A,  /**< P2.26 */
	P2_27 = 0x021B,  /**< P2.27 */
	P2_28 = 0x021C,  /**< P2.28 */
	P2_29 = 0x021D,  /**< P2.29 */
	P2_30 = 0x021E,  /**< P2.30 */
	P2_31 = 0x021F,  /**< P2.31 */

	P3_00 = 0x0300,  /**< P3.0 */
	P3_01 = 0x0301,  /**< P3.1 */
	P3_02 = 0x0302,  /**< P3.2 */
	P3_03 = 0x0303,  /**< P3.3 */
	P3_04 = 0x0304,  /**< P3.4 */
	P3_05 = 0x0305,  /**< P3.5 */
	P3_06 = 0x0306,  /**< P3.6 */
	P3_07 = 0x0307,  /**< P3.7 */
	P3_08 = 0x0308,  /**< P3.8 */
	P3_09 = 0x0309,  /**< P3.9 */
	P3_10 = 0x030A,  /**< P3.10 */
	P3_11 = 0x030B,  /**< P3.11 */
	P3_12 = 0x030C,  /**< P3.12 */
	P3_13 = 0x030D,  /**< P3.13 */
	P3_14 = 0x030E,  /**< P3.14 */
	P3_15 = 0x030F,  /**< P3.15 */
	P3_16 = 0x0310,  /**< P3.16 */
	P3_17 = 0x0311,  /**< P3.17 */
	P3_18 = 0x0312,  /**< P3.18 */
	P3_19 = 0x0313,  /**< P3.19 */
	P3_20 = 0x0314,  /**< P3.20 */
	P3_21 = 0x0315,  /**< P3.21 */
	P3_22 = 0x0316,  /**< P3.22 */
	P3_23 = 0x0317,  /**< P3.23 */
	P3_24 = 0x0318,  /**< P3.24 */
	P3_25 = 0x0319,  /**< P3.25 */
	P3_26 = 0x031A,  /**< P3.26 */
	P3_27 = 0x031B,  /**< P3.27 */
	P3_28 = 0x031C,  /**< P3.28 */
	P3_29 = 0x031D,  /**< P3.29 */
	P3_30 = 0x031E,  /**< P3.30 */
	P3_31 = 0x031F,  /**< P3.31 */

	P4_00 = 0x0400,  /**< P4.0 */
	P4_01 = 0x0401,  /**< P4.1 */
	P4_02 = 0x0402,  /**< P4.2 */
	P4_03 = 0x0403,  /**< P4.3 */
	P4_04 = 0x0404,  /**< P4.4 */
	P4_05 = 0x0405,  /**< P4.5 */
	P4_06 = 0x0406,  /**< P4.6 */
	P4_07 = 0x0407,  /**< P4.7 */
	P4_08 = 0x0408,  /**< P4.8 */
	P4_09 = 0x0409,  /**< P4.9 */
	P4_10 = 0x040A,  /**< P4.10 */
	P4_11 = 0x040B,  /**< P4.11 */
	P4_12 = 0x040C,  /**< P4.12 */
	P4_13 = 0x040D,  /**< P4.13 */
	P4_14 = 0x040E,  /**< P4.14 */
	P4_15 = 0x040F,  /**< P4.15 */
	P4_16 = 0x0410,  /**< P4.16 */
	P4_17 = 0x0411,  /**< P4.17 */
	P4_18 = 0x0412,  /**< P4.18 */
	P4_19 = 0x0413,  /**< P4.19 */
	P4_20 = 0x0414,  /**< P4.20 */
	P4_21 = 0x0415,  /**< P4.21 */
	P4_22 = 0x0416,  /**< P4.22 */
	P4_23 = 0x0417,  /**< P4.23 */
	P4_24 = 0x0418,  /**< P4.24 */
	P4_25 = 0x0419,  /**< P4.25 */
	P4_26 = 0x041A,  /**< P4.26 */
	P4_27 = 0x041B,  /**< P4.27 */
	P4_28 = 0x041C,  /**< P4.28 */
	P4_29 = 0x041D,  /**< P4.29 */
	P4_30 = 0x041E,  /**< P4.30 */
	P4_31 = 0x041F,  /**< P4.31 */

	PIN_INVALID = 0xFFFF,       /* An invalid pin */
};

/***************************************************************************************************************************************//**

    Describes a possible pin direction setting.
    @module     pin-lpc175x6x

*******************************************************************************************************************************************/
enum LPC175X6X_DIRECTION {
    DIRECTION_INPUT = 0,        /**< Indicates the pin is configured as an input */
    DIRECTION_OUTPUT            /**< Indicates the pin is configured as an output */
};

/***************************************************************************************************************************************//**

    Describes a possible pin mode setting.
    @module     pin-lpc175x6x

*******************************************************************************************************************************************/
enum LPC175X6X_MODE {
    MODE_PULLUP = 0,            /**< Indicates the pin has a pull-up resistor enabled */
    MODE_REPEATER = 1,          /**< Indicates the pin has repeater mode enabled */
    MODE_NONE = 2,              /**< Indicates the pin has neither a pull-up nor pull-down */
    MODE_PULLDOWN = 3,          /**< Indicates the pin has a pull-down resistor enabled */
};

/***************************************************************************************************************************************//**

    Describes a possible signal edge.
    @module     pin-lpc175x6x

*******************************************************************************************************************************************/
enum LPC175X6X_EDGE {
	EDGE_NONE       = 0,        /**< Indicates no edges */
	EDGE_RISING     = 1,        /**< Indicates rising-edge signals only */
	EDGE_FALLING    = 2,        /**< Indicates falling-edge signals only */
	EDGE_BOTH       = 3,        /**< Indicates both rising and falling edge signals */
    EDGE_INVALID    = 0xFFFF
};

/*******************************************************************************************************************************************
    PUBLIC FUNCTIONS
*******************************************************************************************************************************************/
/***************************************************************************************************************************************//**

    Returns the current function of a pin.

    @param[in]  pin         The target pin.

    @return     The function number assigned to the specified to the pin.
    @module     pin-lpc175x6x

*******************************************************************************************************************************************/
extern BYTE PIN_Function(PIN pin);

/***************************************************************************************************************************************//**

    Sets the function for a pin.

    @param[in]  pin         The pin to be configured.
    @param[in]  function    The new function for the pin.

     function               | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     0                      | Assign the pin to function number 0 (GPIO by default).
     1                      | Assign the pin to function number 1.
     2                      | Assign the pin to function number 2.
     3                      | Assign the pin to function number 3.

    @return     None.
    @module     pin-lpc175x6x

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
    @module     pin-lpc175x6x

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

    @module     pin-lpc175x6x

*******************************************************************************************************************************************/
extern DIRECTION PIN_Direction(PIN pin);

/***************************************************************************************************************************************//**

    Returns the mode for a pin.

    @param[in]  pin         The target pin

    @return

     mode                   | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     MODE_PULLUP            | The pin has a pull-up resistor enabled.
     MODE_REPEATER          | The pin has repeater mode enabled.
     MODE_NONE              | The pin has neither a pull-up nor pull-down resistor enabled.
     MODE_PULLDOWN          | The pin has a pull-down resistor enabled.

    @module     pin-lpc175x6x

*******************************************************************************************************************************************/
extern MODE PIN_Mode(PIN pin);

/***************************************************************************************************************************************//**

    Sets the mode for a pin.

    @param[in]  pin         The pin to receive the new mode.
    @param[in]  mode        The new mode for the pin.

     mode                   | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     MODE_PULLUP            | Use to enable a pull-up resistor.
     MODE_REPEATER          | Use to enable repeater mode.
     MODE_NONE              | Use to have neither a pull-up nor pull-down resistor.
     MODE_PULLDOWN          | Use to enable a pull-down resistor.

    @return     None.
    @module     pin-lpc175x6x

*******************************************************************************************************************************************/
extern void PIN_SetMode(PIN pin, MODE mode);

/***************************************************************************************************************************************//**

    Returns an indication of whether a pin is configured for open drain mode.

    @param[in]  pin         The target pin.

    @return     TRUE if the pin is in open drain mode; otherwise FALSE.
    @module     pin-lpc175x6x

*******************************************************************************************************************************************/
extern BOOLEAN PIN_OpenDrain(PIN pin);

/***************************************************************************************************************************************//**

    Assigns the open drain mode for a pin.

    @param[in]  pin         The target pin to receive the mode.
    @param[in]  enabled     Use TRUE to enable open drain mode for the pin; otherwise FALSE.

    @return     None.
    @module     pin-lpc175x6x

*******************************************************************************************************************************************/
extern void PIN_SetOpenDrain(PIN pin, BOOLEAN enabled);

/***************************************************************************************************************************************//**

    Reads and returns the current state of a pin.

    @param[in]  pin         The target pin.

    @return     A value '1' if the pin is currently high; otherwise '0' if low.
    @module     pin-lpc175x6x

*******************************************************************************************************************************************/
extern UINT32 PIN_Read(PIN pin);

/***************************************************************************************************************************************//**

    Writes a value to a pin.

    @param[in]  pin         The target pin.
    @param[in]  value       The new value for the specified pin. Use '1' to set the pin as logic level high, or use '0' to set the pin as 
                            logic level low.

    @return     None.
    @module     pin-lpc175x6x

*******************************************************************************************************************************************/
extern void PIN_Write(PIN pin, UINT32 value);

/***************************************************************************************************************************************//**

    Reads and returns the current mask for a pin port. A zero in this register�s bit enables an access to the corresponding physical pin 
    via a read or write access using either PINPORT_Write() or PINPORT_Read(). If a bit in this register is one, the corresponding pin 
    will not be changed with write using PINPORT_Write().

    @param[in]  port        The target pin port.

    @return     The current mask that is applied to the specified port.
    @module     pin-lpc175x6x

*******************************************************************************************************************************************/
extern UINT32 PORT_Mask(PORT port);

/***************************************************************************************************************************************//**

    Sets the mask register for a pin port. A zero in this register�s bit enables an access to the corresponding physical pin via a read
    or write access using either PINPORT_Write() or PINPORT_Read(). If a bit in this register is one, the corresponding pin will not be 
    changed with write using PINPORT_Write().

    @param[in]  port        The target pin port.
    @param[in]  mask        The new mask value to be applied to the specified port.

    @return     None.
    @module     pin-lpc175x6x

*******************************************************************************************************************************************/
extern void PORT_SetMask(PORT port, UINT32 mask);

/***************************************************************************************************************************************//**

    Reads and returns the direction bits for each of the pins on a port.

    @param[in]  port        The target pin port.

    @return     A bit-field indicating the configured direction for each of the pins on the specified port. A bit value of '1' indicates 
                the pin is configured as an output while a '0' indicates configured as an input.
    @module     pin-lpc175x6x

*******************************************************************************************************************************************/
extern UINT32 PORT_Direction(PORT port);

/***************************************************************************************************************************************//**

    Sets the direction for each of the pins on a port.

    @param[in]  port        The target pin port.
    @param[in]  value       A bit-field that specifies a direction for each of the pins. A bit value of '1' indicates the pin to be 
                            configured as an output while a '0' indicates to be configured as an input.

    @return     None.
    @module     pin-lpc175x6x

*******************************************************************************************************************************************/
extern void PORT_SetDirection(PORT port, UINT32 value);

/***************************************************************************************************************************************//**

    Reads and returns a bit-field of states of each of the pins for a port. Only valid for the pins that are not currently masked by the
    PINPORT_SetMask() function.

    @param[in]  port        The target pin port to be read and returned.

    @return     A bit value '1' indicates the pin is currently high; otherwise a '0' if the pin is low.
    @module     pin-lpc175x6x

*******************************************************************************************************************************************/
extern UINT32 PORT_Read(PORT port);

/***************************************************************************************************************************************//**

    Writes and sets the states of each of the pins for a port. Only applies to the pins that are not currently masked by the 
    PINPORT_SetMask() function.

    @param[in]  port        The target pin port to be written.
    @param[in]  value       A bit-field of states for each of the pins. A bit value of '1' sets the pin to a logic level high while a '0'
                            sets the pin to a logic level low.

    @return     None.
    @module     pin-lpc175x6x

*******************************************************************************************************************************************/
extern void PORT_Write(PORT port, UINT32 value);

#endif /* MCU_PIN_H__ */
