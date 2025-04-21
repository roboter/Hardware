/*******************************************************************************************************************************************

    DZX | STM32F4xx | PIN                                                                                                 VERSION 18.2.1
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
#define REG_GPIOA       ((REG_GPIO*)0x40020000)
#define REG_GPIOB       ((REG_GPIO*)0x40020400)
#define REG_GPIOC       ((REG_GPIO*)0x40020800)
#define REG_GPIOD       ((REG_GPIO*)0x40020C00)
#define REG_GPIOE       ((REG_GPIO*)0x40021000)
#define REG_GPIOH       ((REG_GPIO*)0x40021C00)

/***************************************************************************************************************************************//**

    Represents the registers for a GPIO port.
    @module     pin-stm32f4xx

*******************************************************************************************************************************************/
typedef struct REG_GPIO {
    PREG_32(MODE);
    PREG_32(OTYPE);
    PREG_32(OSPEED);
    PREG_32(PUPD);
    PREG_32(ID);
    PREG_32(OD);
    PREG_32(BSR);
    PREG_32(LCK);
    PREG_32(AFRL);
    PREG_32(AFRH);
} REG_GPIO;

/*******************************************************************************************************************************************
    TYPE DEFINITIONS
*******************************************************************************************************************************************/
typedef enum STM32F4XX_PORT PORT;
typedef enum STM32F4XX_PIN PIN;
typedef enum STM32F4XX_MODE MODE;
typedef enum STM32F4XX_EDGE EDGE;
typedef enum STM32F4XX_IOSPEED IOSPEED;
typedef enum STM32F4XX_RESISTOR RESISTOR;

/***************************************************************************************************************************************//**

    Represents a port of pins within the MCU.
    @module     pin-stm32f4xx

*******************************************************************************************************************************************/
enum STM32F4XX_PORT {
	PORT_A = 0,     /**< Pin Port A */
	PORT_B,         /**< Pin Port B */
	PORT_C,         /**< Pin Port C */
	PORT_D,         /**< Pin Port D */
	PORT_E,         /**< Pin Port E */
    PORT_H,         /**< Pin Port H */
	PORT_MAX
};

/***************************************************************************************************************************************//**

    Represents an individual pin on the MCU.
    @module     pin-stm32f4xx

*******************************************************************************************************************************************/
enum STM32F4XX_PIN {
    PA_00 = 0x0000,  /**< PA.0 */
    PA_01 = 0x0001,  /**< PA.1 */
    PA_02 = 0x0002,  /**< PA.2 */
    PA_03 = 0x0003,  /**< PA.3 */
    PA_04 = 0x0004,  /**< PA.4 */
    PA_05 = 0x0005,  /**< PA.5 */
    PA_06 = 0x0006,  /**< PA.6 */
    PA_07 = 0x0007,  /**< PA.7 */
    PA_08 = 0x0008,  /**< PA.8 */
    PA_09 = 0x0009,  /**< PA.9 */
    PA_10 = 0x000A,  /**< PA.10 */
    PA_11 = 0x000B,  /**< PA.11 */
    PA_12 = 0x000C,  /**< PA.12 */
    PA_13 = 0x000D,  /**< PA.13 */
    PA_14 = 0x000E,  /**< PA.14 */
    PA_15 = 0x000F,  /**< PA.15 */
    
    PB_00 = 0x0100,  /**< PB.0 */
    PB_01 = 0x0101,  /**< PB.1 */
    PB_02 = 0x0102,  /**< PB.2 */
    PB_03 = 0x0103,  /**< PB.3 */
    PB_04 = 0x0104,  /**< PB.4 */
    PB_05 = 0x0105,  /**< PB.5 */
    PB_06 = 0x0106,  /**< PB.6 */
    PB_07 = 0x0107,  /**< PB.7 */
    PB_08 = 0x0108,  /**< PB.8 */
    PB_09 = 0x0109,  /**< PB.9 */
    PB_10 = 0x010A,  /**< PB.10 */
    PB_11 = 0x010B,  /**< PB.11 */
    PB_12 = 0x010C,  /**< PB.12 */
    PB_13 = 0x010D,  /**< PB.13 */
    PB_14 = 0x010E,  /**< PB.14 */
    PB_15 = 0x010F,  /**< PB.15 */
    
    PC_00 = 0x0200,  /**< PC.0 */
    PC_01 = 0x0201,  /**< PC.1 */
    PC_02 = 0x0202,  /**< PC.2 */
    PC_03 = 0x0203,  /**< PC.3 */
    PC_04 = 0x0204,  /**< PC.4 */
    PC_05 = 0x0205,  /**< PC.5 */
    PC_06 = 0x0206,  /**< PC.6 */
    PC_07 = 0x0207,  /**< PC.7 */
    PC_08 = 0x0208,  /**< PC.8 */
    PC_09 = 0x0209,  /**< PC.9 */
    PC_10 = 0x020A,  /**< PC.10 */
    PC_11 = 0x020B,  /**< PC.11 */
    PC_12 = 0x020C,  /**< PC.12 */
    PC_13 = 0x020D,  /**< PC.13 */
    PC_14 = 0x020E,  /**< PC.14 */
    PC_15 = 0x020F,  /**< PC.15 */
    
    PD_00 = 0x0300,  /**< PD.0 */
    PD_01 = 0x0301,  /**< PD.1 */
    PD_02 = 0x0302,  /**< PD.2 */
    PD_03 = 0x0303,  /**< PD.3 */
    PD_04 = 0x0304,  /**< PD.4 */
    PD_05 = 0x0305,  /**< PD.5 */
    PD_06 = 0x0306,  /**< PD.6 */
    PD_07 = 0x0307,  /**< PD.7 */
    PD_08 = 0x0308,  /**< PD.8 */
    PD_09 = 0x0309,  /**< PD.9 */
    PD_10 = 0x030A,  /**< PD.10 */
    PD_11 = 0x030B,  /**< PD.11 */
    PD_12 = 0x030C,  /**< PD.12 */
    PD_13 = 0x030D,  /**< PD.13 */
    PD_14 = 0x030E,  /**< PD.14 */
    PD_15 = 0x030F,  /**< PD.15 */
    
    PE_00 = 0x0400,  /**< PE.0 */
    PE_01 = 0x0401,  /**< PE.1 */
    PE_02 = 0x0402,  /**< PE.2 */
    PE_03 = 0x0403,  /**< PE.3 */
    PE_04 = 0x0404,  /**< PE.4 */
    PE_05 = 0x0405,  /**< PE.5 */
    PE_06 = 0x0406,  /**< PE.6 */
    PE_07 = 0x0407,  /**< PE.7 */
    PE_08 = 0x0408,  /**< PE.8 */
    PE_09 = 0x0409,  /**< PE.9 */
    PE_10 = 0x040A,  /**< PE.10 */
    PE_11 = 0x040B,  /**< PE.11 */
    PE_12 = 0x040C,  /**< PE.12 */
    PE_13 = 0x040D,  /**< PE.13 */
    PE_14 = 0x040E,  /**< PE.14 */
    PE_15 = 0x040F,  /**< PE.15 */
    
    PH_00 = 0x0500,  /**< PH.0 */
    PH_01 = 0x0501,  /**< PH.1 */
    
    PIN_INVALID = 0xFFFF,       /* An invalid pin */
};

/***************************************************************************************************************************************//**

    Describes a possible mode setting for a pin.
    @module     pin-stm32f4xx

*******************************************************************************************************************************************/
enum STM32F4XX_MODE {
    MODE_INPUT = 0,         /**< Indicates the pin is configured as a general purpose input */
    MODE_OUTPUT = 1,        /**< Indicates the pin is configured as a general purpose output */
    MODE_ALTERNATE = 2,     /**< Indicates the pin is configured as an alternate function */
    MODE_ANALOG = 3,        /**< Indicates the pin is configured for analog mode */
};

/***************************************************************************************************************************************//**

    Describes a possible speed setting for a pin.
    @module     pin-stm32f4xx

*******************************************************************************************************************************************/
enum STM32F4XX_IOSPEED {
    IOSPEED_LOW = 0,        /**< Indicates the pin is configured for low I/O speed */
    IOSPEED_MEDIUM = 1,     /**< Indicates the pin is configured for medium I/O speed */
    IOSPEED_FAST = 2,       /**< Indicates the pin is configured for fast I/O speed */
    IOSPEED_HIGH = 3,       /**< Indicates the pin is configured for high I/O speed */
};

/***************************************************************************************************************************************//**

    Describes a possible signal edge.
    @module     pin-stm32f4xx

*******************************************************************************************************************************************/
enum STM32F4XX_EDGE {
	EDGE_NONE       = 0,        /**< Indicates no edges */
	EDGE_RISING     = 1,        /**< Indicates rising-edge signals only */
	EDGE_FALLING    = 2,        /**< Indicates falling-edge signals only */
	EDGE_BOTH       = 3,        /**< Indicates both rising and falling edge signals */
    
    EDGE_INVALID    = 0xFFFF
};

/***************************************************************************************************************************************//**

    Describes a possible resistor setting for a pin.
    @module     pin-stm32f4xx

*******************************************************************************************************************************************/
enum STM32F4XX_RESISTOR {
    RESISTOR_NONE = 0,          /**< Indicates the pin is configured with neither a pull-up nor pull-down resistor */
    RESISTOR_PULLUP = 1,        /**< Indicates the pin is configured with a pull-up resistor */
    RESISTOR_PULLDOWN = 2,      /**< Indicates the pin is configured with a pull-down resistor */
};


/*******************************************************************************************************************************************
    PUBLIC FUNCTIONS
*******************************************************************************************************************************************/
/***************************************************************************************************************************************//**

    Reads and returns the current state of a pin.

    @param[in]  pin         The target pin.

    @return     A value '1' if the pin is currently high; otherwise '0' if low.
    @module     pin-stm32f4xx

*******************************************************************************************************************************************/
extern UINT32 PIN_Read(PIN pin);

/***************************************************************************************************************************************//**

    Writes a value to a pin.

    @param[in]  pin         The target pin.
    @param[in]  value       The new value for the specified pin. Use '1' to set the pin as logic level high, or use '0' to set the pin 
                            as logic level low.

    @return     None.
    @module     pin-stm32f4xx

*******************************************************************************************************************************************/
extern void PIN_Write(PIN pin, UINT32 value); 

/***************************************************************************************************************************************//**

    Returns the mode for a pin.

    @param[in]  pin         The target pin.

    @return

     mode                   | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     MODE_INPUT             | The pin is configured as a general purpose input.
     MODE_OUTPUT            | The pin is configured as a general purpose output.
     MODE_ALTERNATE         | The pin is configured for an alternate function.
     MODE_ANALOG            | The pin is configured for analog mode.

    @module     pin-stm32f4xx

*******************************************************************************************************************************************/
extern MODE PIN_Mode(PIN pin);

/***************************************************************************************************************************************//**

    Sets the mode for a pin.

    @param[in]  pin         The pin to receive the new mode.
    @param[in]  mode        The new mode for the pin.

     mode                   | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     MODE_INPUT             | Use to configure the pin as a general purpose input.
     MODE_OUTPUT            | Use to configure the pin as a general purpose output.
     MODE_ALTERNATE         | Use to configure the pin for an alternate function.
     MODE_ANALOG            | Use to configure the pin for analog mode.

    @return     None.
    @module     pin-stm32f4xx

*******************************************************************************************************************************************/
extern void PIN_SetMode(PIN pin, MODE mode);

/***************************************************************************************************************************************//**

    Returns the alternate function for a pin.

    @param[in]  pin         The target pin.

    @return     The current alternate function for the specified pin.
    @module     pin-stm32f4xx

*******************************************************************************************************************************************/
extern BYTE PIN_Function(PIN pin);

/***************************************************************************************************************************************//**

    Assigns a new alternate function for a pin.

    @param[in]  pin         The target pin.
    @param[in]  function    The new alternate function value for the pin.

    @return     None.
    @module     pin-stm32f4xx

*******************************************************************************************************************************************/
extern void PIN_SetFunction(PIN pin, BYTE function);

/***************************************************************************************************************************************//**

    Returns the resistor setting for a pin.

    @param[in]  pin         The target pin.

    @return

     Setting                | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     RESISTOR_NONE          | The pin is configured with no resistor.
     RESISTOR_PULLUP        | The pin is configured with a pull-up resistor.
     RESISTOR_PULLDOWN      | The pin is configured with a pull-down resistor.

    @module     pin-stm32f4xx

*******************************************************************************************************************************************/
extern RESISTOR PIN_Resistor(PIN pin);

/***************************************************************************************************************************************//**

    Assigns a resistor setting for a pin.

    @param[in]  pin         The pin to receive the new setting.
    @param[in]  resistor    The new resistor setting for the pin.

     Resistor               | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     RESISTOR_NONE          | Use to configure the pin with no resistor.
     RESISTOR_PULLUP        | Use to configure the pin with a pull-up resistor.
     RESISTOR_PULLDOWN      | Use to configure the pin with a pull-down resistor.

    @return     None.
    @module     pin-stm32f4xx

*******************************************************************************************************************************************/
extern void PIN_SetResistor(PIN pin, RESISTOR resistor);

/***************************************************************************************************************************************//**

    Returns the speed setting for a pin.

    @param[in]  pin         The target pin.

    @return

     Setting                | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     IOSPEED_LOW            | The pin is configured for low speed.
     IOSPEED_MEDIUM         | The pin is configured for medium speed.
     IOSPEED_FAST           | The pin is configured for fast speed.
     IOSPEED_HIGH           | The pin is configured for high speed.

    @module     pin-stm32f4xx

*******************************************************************************************************************************************/
extern IOSPEED PIN_Speed(PIN pin);

/***************************************************************************************************************************************//**

    Assigns a speed setting for a pin.

    @param[in]  pin         The pin to receive the new setting.
    @param[in]  speed       The new speed setting for the pin.

     Speed                  | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     IOSPEED_LOW            | Use to configure the pin for low speed.
     IOSPEED_MEDIUM         | Use to configure the pin for medium speed.
     IOSPEED_FAST           | Use to configure the pin for fast speed.
     IOSPEED_HIGH           | Use to configure the pin for high speed.

    @return     None.
    @module     pin-stm32f4xx

*******************************************************************************************************************************************/
extern void PIN_SetSpeed(PIN pin, IOSPEED speed);

/***************************************************************************************************************************************//**

    Returns an indication of whether a pin is configured for open drain mode.

    @param[in]  pin         The target pin.

    @return     TRUE if the pin is in open drain mode; otherwise FALSE.
    @module     pin-stm32f4xx

*******************************************************************************************************************************************/
extern BOOLEAN PIN_OpenDrain(PIN pin);

/***************************************************************************************************************************************//**

    Assigns the open drain mode for a pin.

    @param[in]  pin         The target pin to receive the mode.
    @param[in]  enabled     Use TRUE to enable open drain mode for the pin; otherwise FALSE.

    @return     None.
    @module     pin-stm32f4xx

*******************************************************************************************************************************************/
extern void PIN_SetOpenDrain(PIN pin, BOOLEAN enabled);

#endif /* MCU_PIN_H__ */
