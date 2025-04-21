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
#include "mcu_pin.h"
#include "mcu_rcc.h"

/*******************************************************************************************************************************************
    LOCAL DEFINITIONS
*******************************************************************************************************************************************/
#define PINFROMNUMBERS(port, pin)   (PIN)((port << 8) | (pin))          /* Convert port & pin numbers into a pin */
#define PIN_NUMBER(pin)             (pin & 0xFF)                        /* Get a pin's pin number */
#define PIN_PORTNUMBER(pin)         ((pin >> 8) & 0xFF)                 /* Get a pin's port number */

/*******************************************************************************************************************************************
    PRIVATE VARIABLES
*******************************************************************************************************************************************/
REG_GPIO* const REG_GPIOS[] = {
    REG_GPIOA, REG_GPIOB, REG_GPIOC, REG_GPIOD, REG_GPIOE, REG_GPIOH
};

/***************************************************************************************************************************************//**

    Writes a value to a pin.

    @param[in]  pin         The target pin.
    @param[in]  value       The new value for the specified pin. Use '1' to set the pin as logic level high, or use '0' to set the pin 
                            as logic level low.

    @return     None.
    @module     pin-stm32f4xx

*******************************************************************************************************************************************/
void PIN_Write(PIN pin, UINT32 value)
{
    INTERRUPTLOCK lock;
    
    
    ACQUIREINTERRUPTLOCK();
    
    if (value) {
        REG_GPIOS[PIN_PORTNUMBER(pin)]->BSR = (1UL << PIN_NUMBER(pin));
    } else {
        REG_GPIOS[PIN_PORTNUMBER(pin)]->BSR = (0x10000UL << PIN_NUMBER(pin));
    }
    
    RELEASEINTERRUPTLOCK();
}

/***************************************************************************************************************************************//**

    Reads and returns the current state of a pin.

    @param[in]  pin         The target pin.

    @return     A value '1' if the pin is currently high; otherwise '0' if low.
    @module     pin-stm32f4xx

*******************************************************************************************************************************************/
UINT32 PIN_Read(PIN pin)
{
    INTERRUPTLOCK lock;
    
    
    ACQUIREINTERRUPTLOCK();
 
    if (REG_GPIOS[PIN_PORTNUMBER(pin)]->ID & (1UL << PIN_NUMBER(pin))) {
        RELEASEINTERRUPTLOCK();
        return 1;
    }
    
    RELEASEINTERRUPTLOCK();
    return 0;
}

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
MODE PIN_Mode(PIN pin)
{
    INTERRUPTLOCK lock;
    UINT32 shift;
    MODE mode;
    
    
    shift = (PIN_NUMBER(pin) << 1);
    
    ACQUIREINTERRUPTLOCK();
 
    mode = (MODE)((REG_GPIOS[PIN_PORTNUMBER(pin)]->MODE >> shift) & 0x3);
    
    RELEASEINTERRUPTLOCK();
    return mode;
}

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
void PIN_SetMode(PIN pin, MODE mode)
{
    INTERRUPTLOCK lock;
    UINT32 shift;
    UINT32 port;
    
    
    port = PIN_PORTNUMBER(pin);
    shift = (PIN_NUMBER(pin) << 1);
    
    ACQUIREINTERRUPTLOCK();
    
    REG_GPIOS[port]->MODE &= ~(0x3 << shift);
    REG_GPIOS[port]->MODE |= ((UINT32)mode << shift);

    RELEASEINTERRUPTLOCK();
}

/***************************************************************************************************************************************//**

    Returns the alternate function for a pin.

    @param[in]  pin         The target pin.

    @return     The current alternate function for the specified pin.
    @module     pin-stm32f4xx

*******************************************************************************************************************************************/
BYTE PIN_Function(PIN pin)
{
    INTERRUPTLOCK lock;
    UINT32 shift;
    UINT32 port;
    UINT32 number;
    BYTE function;
    
    
    number = PIN_NUMBER(pin);
    port = PIN_PORTNUMBER(pin);
    shift = (number % 8) << 2;                                  /* Calc the shift into the register for the pin (pin number * 4) */
        
    ACQUIREINTERRUPTLOCK();
    
    if (number < 8) {
        
        function = (REG_GPIOS[port]->AFRL >> shift) & 0xF;      /* Get the function from the low register */
        RELEASEINTERRUPTLOCK();
        return function;
    }
    
    function = (REG_GPIOS[port]->AFRH >> shift) & 0xF;          /* Get the function from the high register */
    RELEASEINTERRUPTLOCK();
    return function;
}

/***************************************************************************************************************************************//**

    Assigns a new alternate function for a pin.

    @param[in]  pin         The target pin.
    @param[in]  function    The new alternate function value for the pin.

    @return     None.
    @module     pin-stm32f4xx

*******************************************************************************************************************************************/
void PIN_SetFunction(PIN pin, BYTE function)
{
    INTERRUPTLOCK lock;
    UINT32 port;
    UINT32 number;
    UINT32 shift;
    
    
    number = PIN_NUMBER(pin);
    port = PIN_PORTNUMBER(pin);
    shift = (number % 8) << 2;                                  /* Calc the shift into the register for the pin (pin number * 4) */
    
    ACQUIREINTERRUPTLOCK();
    
    if (number < 8) {                                           /* Either use the low or high function register */
        
        REG_GPIOS[port]->AFRL &= ~(0xF << shift);
        REG_GPIOS[port]->AFRL |= ((function & 0xF) << shift);
    } else {
        
        REG_GPIOS[port]->AFRH &= ~(0xF << shift);
        REG_GPIOS[port]->AFRH |= ((function & 0xF) << shift);
    }
    
    RELEASEINTERRUPTLOCK();
}

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
RESISTOR PIN_Resistor(PIN pin)
{
    INTERRUPTLOCK lock;
    UINT32 shift;
    RESISTOR res;
    
    
    shift = (PIN_NUMBER(pin) << 1);
    
    ACQUIREINTERRUPTLOCK();
 
    res = (RESISTOR)((REG_GPIOS[PIN_PORTNUMBER(pin)]->PUPD >> shift) & 0x3);
    
    RELEASEINTERRUPTLOCK();
    return res;
}

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
void PIN_SetResistor(PIN pin, RESISTOR resistor)
{
    INTERRUPTLOCK lock;
    UINT32 shift;
    UINT32 port;
    
    
    port = PIN_PORTNUMBER(pin);
    shift = (PIN_NUMBER(pin) << 1);
    
    ACQUIREINTERRUPTLOCK();
    
    REG_GPIOS[port]->PUPD &= ~(0x3 << shift);
    REG_GPIOS[port]->PUPD |= ((UINT32)resistor << shift);

    RELEASEINTERRUPTLOCK();
}
    
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
IOSPEED PIN_Speed(PIN pin)
{
    INTERRUPTLOCK lock;
    UINT32 shift;
    IOSPEED speed;
    
    
    shift = (PIN_NUMBER(pin) << 1);
    
    ACQUIREINTERRUPTLOCK();
 
    speed = (IOSPEED)((REG_GPIOS[PIN_PORTNUMBER(pin)]->OSPEED >> shift) & 0x3);
    
    RELEASEINTERRUPTLOCK();
    return speed;
}

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
void PIN_SetSpeed(PIN pin, IOSPEED speed)
{
    INTERRUPTLOCK lock;
    UINT32 shift;
    UINT32 port;
    
    
    port = PIN_PORTNUMBER(pin);
    shift = (PIN_NUMBER(pin) << 1);
    
    ACQUIREINTERRUPTLOCK();
    
    REG_GPIOS[port]->OSPEED &= ~(0x3 << shift);
    REG_GPIOS[port]->OSPEED |= ((UINT32)speed << shift);

    RELEASEINTERRUPTLOCK();
}

/***************************************************************************************************************************************//**

    Returns an indication of whether a pin is configured for open drain mode.

    @param[in]  pin         The target pin.

    @return     TRUE if the pin is in open drain mode; otherwise FALSE.
    @module     pin-stm32f4xx

*******************************************************************************************************************************************/
BOOLEAN PIN_OpenDrain(PIN pin)
{
    INTERRUPTLOCK lock;
    
    
    ACQUIREINTERRUPTLOCK();
    
    if (REG_GPIOS[PIN_PORTNUMBER(pin)]->OTYPE & (1UL << PIN_NUMBER(pin))) {
        
        RELEASEINTERRUPTLOCK();
        return TRUE;
    }
    
    RELEASEINTERRUPTLOCK();
    return FALSE;
}

/***************************************************************************************************************************************//**

    Assigns the open drain mode for a pin.

    @param[in]  pin         The target pin to receive the mode.
    @param[in]  enabled     Use TRUE to enable open drain mode for the pin; otherwise FALSE.

    @return     None.
    @module     pin-stm32f4xx

*******************************************************************************************************************************************/
void PIN_SetOpenDrain(PIN pin, BOOLEAN enabled)
{
    INTERRUPTLOCK lock;
    
    
    ACQUIREINTERRUPTLOCK();
    
    if (enabled) {
        REG_GPIOS[PIN_PORTNUMBER(pin)]->OTYPE |= (1UL << PIN_NUMBER(pin));
    } else {
        REG_GPIOS[PIN_PORTNUMBER(pin)]->OTYPE &= ~(1UL << PIN_NUMBER(pin));
    }
    
    RELEASEINTERRUPTLOCK();
}
