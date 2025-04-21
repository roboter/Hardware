/*******************************************************************************************************************************************

    DZX | LPC177x8x | PIN                                                                                                 VERSION 18.2.1
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

/*******************************************************************************************************************************************
    PRIVATE VARIABLES
*******************************************************************************************************************************************/
REG_GPIO* const REG_GPIOS[PORT_MAX] = {
    REG_GPIO0, REG_GPIO1, REG_GPIO2, REG_GPIO3, REG_GPIO4, REG_GPIO5
};

/***************************************************************************************************************************************//**

    Writes a value to a pin.

    @param[in]  pin         The target pin.
    @param[in]  value       The new value for the specified pin. Use '1' to set the pin as logic level high, or use '0' to set the pin 
                            as logic level low.

    @return     None.
    @module     pin-lpc177x8x

*******************************************************************************************************************************************/
void PIN_Write(PIN pin, UINT32 value)
{
    INTERRUPTLOCK lock;
    
    
    ACQUIREINTERRUPTLOCK();
    
    if (value) {
        REG_GPIOS[PIN_PORTNUMBER(pin)]->FIOSET = (1 << PIN_NUMBER(pin));
    } else {
        REG_GPIOS[PIN_PORTNUMBER(pin)]->FIOCLR = (1 << PIN_NUMBER(pin));
    }
    
    RELEASEINTERRUPTLOCK();
}

/***************************************************************************************************************************************//**

    Reads and returns the current state of a pin.

    @param[in]  pin         The target pin.

    @return     A value '1' if the pin is currently high; otherwise '0' if low.
    @module     pin-lpc177x8x

*******************************************************************************************************************************************/
UINT32 PIN_Read(PIN pin)
{
    INTERRUPTLOCK lock;
    
    
    ACQUIREINTERRUPTLOCK();
 
    if (REG_GPIOS[PIN_PORTNUMBER(pin)]->FIOPIN & (1 << PIN_NUMBER(pin))) {
        RELEASEINTERRUPTLOCK();
        return 1;
    }
    
    RELEASEINTERRUPTLOCK();
    return 0;
}

/***************************************************************************************************************************************//**

    Assigns a new direction setting for a pin.

    @param[in]  pin         The target pin to receive the new direction setting.
    @param[in]  dir         The new direction setting for the pin.

     Direction              | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     DIRECTION_OUTPUT       | Use to configure the pin as an output.
     DIRECTION_INPUT        | Use to configure the pin as an input.

    @return     None.
    @module     pin-lpc177x8x

*******************************************************************************************************************************************/
void PIN_SetDirection(PIN pin, DIRECTION dir)
{
    INTERRUPTLOCK lock;
    
    
    ACQUIREINTERRUPTLOCK();
    
    if (dir) {
        REG_GPIOS[PIN_PORTNUMBER(pin)]->FIODIR |= (1UL << PIN_NUMBER(pin));
    } else {
        REG_GPIOS[PIN_PORTNUMBER(pin)]->FIODIR &= ~(1UL << PIN_NUMBER(pin));
    }
    
    RELEASEINTERRUPTLOCK();
}

/***************************************************************************************************************************************//**

    Returns the current direction setting for a pin.

    @param[in]  pin         The target pin.

    @return

     Direction              | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     DIRECTION_OUTPUT       | The pin is configured as an output.
     DIRECTION_INPUT        | The pin is configured as an input.

    @module     pin-lpc177x8x

*******************************************************************************************************************************************/
DIRECTION PIN_Direction(PIN pin)
{
    INTERRUPTLOCK lock;
    
    
    ACQUIREINTERRUPTLOCK();
    
    if (REG_GPIOS[PIN_PORTNUMBER(pin)]->FIODIR & (1UL << PIN_NUMBER(pin))) {
        
        RELEASEINTERRUPTLOCK();
        return DIRECTION_OUTPUT;
    }
    
    RELEASEINTERRUPTLOCK();
    return DIRECTION_INPUT;
}

/***************************************************************************************************************************************//**

    Returns the current function of a pin.

    @param[in]  pin         The target pin.

    @return     The function number assigned to the specified to the pin.
    @module     pin-lpc177x8x

*******************************************************************************************************************************************/
BYTE PIN_Function(PIN pin)
{
    INTERRUPTLOCK lock;
    volatile UINT32* reg;
    BYTE value;
    
    
    reg = REG_IOCON(PIN_PORTNUMBER(pin), PIN_NUMBER(pin));      /* Get the IOCON register for the specified pin */
    ACQUIREINTERRUPTLOCK();
    
    value = (*reg & 0x7);
    
    RELEASEINTERRUPTLOCK();
    return value;
}

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
     4                      | Assign the pin to function number 4.
     5                      | Assign the pin to function number 5.
     6                      | Assign the pin to function number 6.
     7                      | Assign the pin to function number 7.

    @return     None.
    @module     pin-lpc177x8x

*******************************************************************************************************************************************/
void PIN_SetFunction(PIN pin, BYTE function)
{
    INTERRUPTLOCK lock;
    volatile UINT32* reg;

    
    reg = REG_IOCON(PIN_PORTNUMBER(pin), PIN_NUMBER(pin));      /* Get the IOCON register for the specified pin */

    ACQUIREINTERRUPTLOCK();
    
    *reg &= ~0x00000007;                                        /* Clear the pin's function bits */
    *reg |= ((UINT32)function & 0x7);                           /* Set the pin's bits according to request */
    
    RELEASEINTERRUPTLOCK();
}

/***************************************************************************************************************************************//**

    Reads and returns the state of a bit within the IOCON register for a pin.

    @param[in]  pin         The target pin.
    @param[in]  bit         The number of the target bit.

    @return     TRUE if the specified bit is set; otherwise FALSE.
    @module     pin-lpc177x8x

*******************************************************************************************************************************************/
BOOLEAN PIN_ConfigBit(PIN pin, UINT32 bit)
{
    INTERRUPTLOCK lock;
    volatile UINT32* reg;

    
    reg = REG_IOCON(PIN_PORTNUMBER(pin), PIN_NUMBER(pin));      /* Get the IOCON register for the specified pin */

    ACQUIREINTERRUPTLOCK();
    
    if (*reg & (1UL << bit)) {
        
        RELEASEINTERRUPTLOCK();
        return TRUE;
    }
    
    RELEASEINTERRUPTLOCK();
    return FALSE;
}

/***************************************************************************************************************************************//**

    Assigns a new state of a bit within the IOCON register for a pin.

    @param[in]  pin         The target pin.
    @param[in]  bit         The number of the bit to be updated.
    @param[in]  state       The new state for the bit. Use TRUE to set the bit and FALSE to clear the bit.

    @return     None.
    @module     pin-lpc177x8x

*******************************************************************************************************************************************/
void PIN_SetConfigBit(PIN pin, UINT32 bit, BOOLEAN state)
{
    INTERRUPTLOCK lock;
    volatile UINT32* reg;

    
    reg = REG_IOCON(PIN_PORTNUMBER(pin), PIN_NUMBER(pin));      /* Get the IOCON register for the specified pin */

    ACQUIREINTERRUPTLOCK();
    
    if (state) {
        *reg |= (1UL << bit);
    } else {
        *reg &= ~(1UL << bit);
    }
    
    RELEASEINTERRUPTLOCK();
}

/***************************************************************************************************************************************//**

    Returns an indication of whether a pin is configured for open drain mode.

    @param[in]  pin         The target pin.

    @return     TRUE if the pin is in open drain mode; otherwise FALSE.
    @module     pin-lpc177x8x

*******************************************************************************************************************************************/
BOOLEAN PIN_OpenDrain(PIN pin)
{
    return PIN_ConfigBit(pin, 10);
}

/***************************************************************************************************************************************//**

    Assigns the open drain mode for a pin.

    @param[in]  pin         The target pin to receive the mode.
    @param[in]  enabled     Use TRUE to enable open drain mode for the pin; otherwise FALSE.

    @return     None.
    @module     pin-lpc177x8x

*******************************************************************************************************************************************/
void PIN_SetOpenDrain(PIN pin, BOOLEAN enabled)
{
    PIN_SetConfigBit(pin, 10, enabled);
}

/***************************************************************************************************************************************//**

    Returns an indication of whether hysteresis is enabled for a pin.

    @param[in]  pin         The target pin.

    @return     TRUE if hysteresis is enabled for the pin; otherwise FALSE.
    @module     pin-lpc177x8x

*******************************************************************************************************************************************/
BOOLEAN PIN_Hysteresis(PIN pin)
{
    return PIN_ConfigBit(pin, 5);
}

/***************************************************************************************************************************************//**

    Enables or disables hysteresis for a pin.

    @param[in]  pin         The target pin.
    @param[in]  enabled     Use TRUE to enable hysteresis for the pin; otherwise FALSE.

    @return     None.
    @module     pin-lpc177x8x

*******************************************************************************************************************************************/
void PIN_SetHysteresis(PIN pin, BOOLEAN enabled)
{
    PIN_SetConfigBit(pin, 5, enabled);
}
        
/***************************************************************************************************************************************//**

    Returns an indication of whether the pin has inverted polarity.

    @param[in]  pin         The target pin.

    @return     TRUE if the pin has inverted polarity; otherwise FALSE.
    @module     pin-lpc177x8x

*******************************************************************************************************************************************/
BOOLEAN PIN_InvertPolarity(PIN pin)
{
    return PIN_ConfigBit(pin, 6);
}

/***************************************************************************************************************************************//**

    Enables or disables inverted polarity for a pin.

    @param[in]  pin         The target pin.
    @param[in]  enabled     Use TRUE to enable inverted polarity for the pin; otherwise FALSE.

    @return     None.
    @module     pin-lpc177x8x

*******************************************************************************************************************************************/
void PIN_SetInvertPolarity(PIN pin, BOOLEAN enabled)
{
    PIN_SetConfigBit(pin, 6, enabled);
}

/***************************************************************************************************************************************//**

    Returns the mode for a pin.

    @param[in]  pin         The target pin.

    @return

     mode                   | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     MODE_PULLUP            | The pin has a pull-up resistor enabled.
     MODE_REPEATER          | The pin has repeater mode enabled.
     MODE_NONE              | The pin has neither a pull-up nor pull-down resistor enabled.
     MODE_PULLDOWN          | The pin has a pull-down resistor enabled.

    @module     pin-lpc177x8x

*******************************************************************************************************************************************/
MODE PIN_Mode(PIN pin)
{
    INTERRUPTLOCK lock;
    volatile UINT32* reg;
    MODE mode;

    
    reg = REG_IOCON(PIN_PORTNUMBER(pin), PIN_NUMBER(pin));      /* Get the IOCON register for the specified pin */

    ACQUIREINTERRUPTLOCK();
    
    mode = (MODE)((*reg >> 3) & 0x3); 
    
    RELEASEINTERRUPTLOCK();                  
    return mode;
}

/***************************************************************************************************************************************//**

    Sets the mode for a pin.

    @param[in]  pin         The pin to be configured.
    @param[in]  mode        The new mode for the pin.

     mode                   | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     INPUT                  | Configure the pin as an input.
     OUTPUT                 | Configure the pin as an output.
     PULLUP                 | Enable an on-chip pull-up resistor on the pin.
     PULLDOWN               | Enable an on-chip pull-down resistor on the pin.
     OPENDRAIN              | Enable the open-drain mode for the pin.

    @return     None.
    @module     pin-lpc177x8x

*******************************************************************************************************************************************/
void PIN_SetMode(PIN pin, MODE mode)
{
    INTERRUPTLOCK lock;
    volatile UINT32* reg;

    
    reg = REG_IOCON(PIN_PORTNUMBER(pin), PIN_NUMBER(pin));      /* Get the IOCON register for the specified pin */

    ACQUIREINTERRUPTLOCK();
    *reg &= ~(0x3 << 3);                                        /* Clear the mode bits */
    *reg |= (((UINT32)mode) << 3);                              /* Set any mode bits */
    RELEASEINTERRUPTLOCK();
}

/***************************************************************************************************************************************//**

    Reads and returns the current mask for a pin port. A zero in this register�s bit enables an access to the corresponding physical pin 
    via a read or write access using either PINPORT_Write() or PINPORT_Read(). If a bit in this register is one, the corresponding pin 
    will not be changed with write using PINPORT_Write().

    @param[in]  port        The target pin port.

    @return     The current mask that is applied to the specified port.
    @module     pin-lpc177x8x

*******************************************************************************************************************************************/
UINT32 PORT_Mask(PORT port)
{
    INTERRUPTLOCK lock;
    UINT32 mask;
    
    
    ACQUIREINTERRUPTLOCK();
    
    mask = REG_GPIOS[port]->FIOMASK;
    
    RELEASEINTERRUPTLOCK();
    return mask;
}

/***************************************************************************************************************************************//**

    Sets the mask register for a pin port. A zero in this register�s bit enables an access to the corresponding physical pin via a read
    or write access using either PINPORT_Write() or PINPORT_Read(). If a bit in this register is one, the corresponding pin will not be 
    changed with write using PINPORT_Write().

    @param[in]  port        The target pin port.
    @param[in]  mask        The new mask value to be applied to the specified port.

    @return     None.
    @module     pin-lpc177x8x

*******************************************************************************************************************************************/
void PORT_SetMask(PORT port, UINT32 mask)
{
    INTERRUPTLOCK lock;
    
    
    ACQUIREINTERRUPTLOCK();
    
    REG_GPIOS[port]->FIOMASK = mask;
    
    RELEASEINTERRUPTLOCK();
}

/***************************************************************************************************************************************//**

    Reads and returns the direction bits for each of the pins on a port.

    @param[in]  port        The target pin port.

    @return     A bit-field indicating the configured direction for each of the pins on the specified port. A bit value of '1' indicates 
                the pin is configured as an output while a '0' indicates configured as an input.
    @module     pin-lpc177x8x

*******************************************************************************************************************************************/
UINT32 PORT_Direction(PORT port)
{
    INTERRUPTLOCK lock;
    UINT32 value;


    ACQUIREINTERRUPTLOCK();
    
    value = REG_GPIOS[port]->FIODIR;
    
    RELEASEINTERRUPTLOCK();  
    return value;
}

/***************************************************************************************************************************************//**

    Sets the direction for each of the pins on a port.

    @param[in]  port        The target pin port.
    @param[in]  value       A bit-field that specifies a direction for each of the pins. A bit value of '1' indicates the pin to be 
                            configured as an output while a '0' indicates to be configured as an input.

    @return     None.
    @module     pin-lpc177x8x

*******************************************************************************************************************************************/
void PORT_SetDirection(PORT port, UINT32 value)
{
    INTERRUPTLOCK lock;


    ACQUIREINTERRUPTLOCK();
    
    REG_GPIOS[port]->FIODIR = value;  
    
    RELEASEINTERRUPTLOCK();
}

/***************************************************************************************************************************************//**

    Reads and returns a bit-field of states of each of the pins for a port. Only valid for the pins that are not currently masked by the
    PINPORT_SetMask() function.

    @param[in]  port        The target pin port.

    @return     A bit value '1' indicates the pin is currently high; otherwise a '0' if the pin is low.
    @module     pin-lpc177x8x

*******************************************************************************************************************************************/
UINT32 PORT_Read(PORT port)
{
    INTERRUPTLOCK lock;
    UINT32 value;
    
    
    ACQUIREINTERRUPTLOCK();
    
    value = REG_GPIOS[port]->FIOPIN;
    
    RELEASEINTERRUPTLOCK();
    return value;
}

/***************************************************************************************************************************************//**

    Writes and sets the states of each of the pins for a port. Only applies to the pins that are not currently masked by the 
    PINPORT_SetMask() function.

    @param[in]  port        The target pin port to be written.
    @param[in]  value       A bit-field of states for each of the pins. A bit value of '1' sets the pin to a logic level high while a '0'
                            sets the pin to a logic level low.

    @return     None.
    @module     pin-lpc177x8x

*******************************************************************************************************************************************/
void PORT_Write(PORT port, UINT32 value)
{
    INTERRUPTLOCK lock;
    
    
    ACQUIREINTERRUPTLOCK();
    
    REG_GPIOS[port]->FIOPIN = value;
    
    RELEASEINTERRUPTLOCK();
}
