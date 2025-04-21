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
#include "mcu_pin.h"
#include "mcu_cfg.h"
#include "mcu_kernel.h"

/***************************************************************************************************************************************//**

    Writes a value to a pin.

    @param[in]  pin         The target pin.
    @param[in]  value       The new value for the specified pin. Use '1' (or 'HIGH') to set the pin as logic level high, or use '0' 
                            (or 'LOW') to set the pin as logic level low.

    @return     None.
    @module     pin-lpc13x1x2x3

*******************************************************************************************************************************************/
void PIN_Write(PIN pin, UINT32 value)
{
    INTERRUPTLOCK lock;
    UINT32 mask;
    volatile UINT32* reg;
    
    
    mask = (1 << PIN_NUMBER(pin));
    reg = (volatile UINT32*)(REG_GPIODATABASE + (0x10000 * PIN_PORTNUMBER(pin)) + (mask << 2));

    
    ACQUIREINTERRUPTLOCK();
    
    if (value) {
        *reg = mask;
    } else {
        *reg = 0;
    }
    
    RELEASEINTERRUPTLOCK();
}

/***************************************************************************************************************************************//**

    Reads and returns the current state of a pin.

    @param[in]  pin         The target pin.

    @return     A value '1' if the pin is currently high; otherwise '0' if low.
    @module     pin-lpc13x1x2x3

*******************************************************************************************************************************************/
UINT32 PIN_Read(PIN pin)
{
    INTERRUPTLOCK lock;
    UINT32 mask;
    volatile UINT32* reg;
    
    
    mask = (1 << PIN_NUMBER(pin));
    reg = (volatile UINT32*)(REG_GPIODATABASE + (0x10000 * PIN_PORTNUMBER(pin)) + (mask << 2));
    
    ACQUIREINTERRUPTLOCK();
 
    if (*reg) {
        RELEASEINTERRUPTLOCK();
        return 1;
    }
    
    RELEASEINTERRUPTLOCK();
    return 0;
}

/***************************************************************************************************************************************//**

    Returns the current function of a pin.

    @param[in]  pin         The target pin.

    @return     The function number assigned to the specified to the pin.
    @module     pin-lpc13x1x2x3

*******************************************************************************************************************************************/
BYTE PIN_Function(PIN pin)
{
    volatile UINT32* reg;
    INTERRUPTLOCK lock;
    BYTE function;
    
    
    reg = (volatile UINT32*)(REG_IOCONBASE + (pin >> 16));
    
    ACQUIREINTERRUPTLOCK();
    
    function = *reg & 0x7;
    
    RELEASEINTERRUPTLOCK();
    return function;
}

/***************************************************************************************************************************************//**

    Sets the function for a pin.

    @param[in]  pin         The pin to be configured.
    @param[in]  function    The new function for the pin.

    @return     None.
    @module     pin-lpc13x1x2x3

*******************************************************************************************************************************************/
void PIN_SetFunction(PIN pin, BYTE function)
{
    volatile UINT32* reg;
    INTERRUPTLOCK lock;
    
    
    reg = (volatile UINT32*)(REG_IOCONBASE + (pin >> 16));
    
    ACQUIREINTERRUPTLOCK();
    
    *reg &= ~(0x7);
    *reg |= (function & 0x7);
    
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

    @module     pin-lpc13x1x2x3

*******************************************************************************************************************************************/
DIRECTION PIN_Direction(PIN pin)
{
    volatile UINT32* reg;
    INTERRUPTLOCK lock;
    
    
    reg = (volatile UINT32*)(0x50008000 + (PIN_PORTNUMBER(pin) << 16));
    
    ACQUIREINTERRUPTLOCK();
    
    if (*reg & (1UL << PIN_NUMBER(pin))) {
        
        RELEASEINTERRUPTLOCK();
        return DIRECTION_OUTPUT;
    }
    
    RELEASEINTERRUPTLOCK();
    return DIRECTION_INPUT;
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
    @module     pin-lpc13x1x2x3

*******************************************************************************************************************************************/
void PIN_SetDirection(PIN pin, DIRECTION dir)
{
    volatile UINT32* reg;
    INTERRUPTLOCK lock;
    
    
    reg = (volatile UINT32*)(0x50008000 + (PIN_PORTNUMBER(pin) << 16));
    
    ACQUIREINTERRUPTLOCK();
    
    if (dir) {
        *reg |= (1UL << PIN_NUMBER(pin));
    } else {
        *reg &= ~(1UL << PIN_NUMBER(pin));
    }
    
    RELEASEINTERRUPTLOCK();
}

/***************************************************************************************************************************************//**

    Reads and returns the direction bits for each of the pins on a port.

    @param[in]  port        The target pin port.

    @return     A bit-field indicating the configured direction for each of the pins on the specified port. A bit value of '1' indicates 
                the pin is configured as an output while a '0' indicates configured as an input.
    @module     pin-lpc13x1x2x3

*******************************************************************************************************************************************/
UINT32 PORT_Direction(PORT port)
{
    INTERRUPTLOCK lock;
    UINT32 value;
    volatile UINT32* reg;

    
    if (port >= PORT_MAX) {
        return 0;
    }
    
    reg = (volatile UINT32*)(0x50008000 + (0x10000 * port));

    ACQUIREINTERRUPTLOCK();
    value = *reg;
    RELEASEINTERRUPTLOCK();  
    return value;
}

/***************************************************************************************************************************************//**

    Sets the direction for each of the pins on a port.

    @param[in]  port        The target pin port.
    @param[in]  value       A bit-field that specifies a direction for each of the pins. A bit value of '1' indicates the pin to be 
                            configured as an output while a '0' indicates to be configured as an input.

    @return     None.
    @module     pin-lpc13x1x2x3

*******************************************************************************************************************************************/
void PORT_SetDirection(PORT port, UINT32 value)
{
    INTERRUPTLOCK lock;
    volatile UINT32* reg;

    
    if (port >= PORT_MAX) {
        return;
    }
    
    reg = (volatile UINT32*)(0x50008000 + (0x10000 * port));

    ACQUIREINTERRUPTLOCK();
    *reg = value;
    RELEASEINTERRUPTLOCK();
}

/***************************************************************************************************************************************//**

    Reads and returns a bit-field of states of each of the pins for a port.

    @param[in]  port        The target pin port to be read and returned.

    @return     A bit value '1' indicates the pin is currently high; otherwise a '0' if the pin is low.
    @module     pin-lpc13x1x2x3

*******************************************************************************************************************************************/
UINT32 PORT_Read(PORT port)
{
    INTERRUPTLOCK lock;
    UINT32 value;
    
    
    ACQUIREINTERRUPTLOCK();
    
    switch (port) {
        case PORT_0:
            value = REG_GPIO0DATA;
            break;
        case PORT_1:
            value = REG_GPIO1DATA;
            break;
        case PORT_2:
            value = REG_GPIO2DATA;
            break;
        case PORT_3:
            value = REG_GPIO3DATA;
            break;
        default:
            value = 0;
            break;
    }

    RELEASEINTERRUPTLOCK();
    return value;
}

/***************************************************************************************************************************************//**

    Writes and sets the states of each of the pins for a port.

    @param[in]  port        The target pin port to be written.
    @param[in]  value       A bit-field of states for each of the pins. A bit value of '1' sets the pin to a logic level high while a '0'
                            sets the pin to a logic level low.

    @return     None.
    @module     pin-lpc13x1x2x3

*******************************************************************************************************************************************/
void PORT_Write(PORT port, UINT32 value)
{
    INTERRUPTLOCK lock;
    
    
    ACQUIREINTERRUPTLOCK();
    
    switch (port) {
        case PORT_0:
            REG_GPIO0DATA = value;
            break;
        case PORT_1:
            REG_GPIO1DATA = value;
            break;
        case PORT_2:
            REG_GPIO2DATA = value;
            break;
        case PORT_3:
            REG_GPIO3DATA = value;
            break;
        default:
            break;
    }
    
    RELEASEINTERRUPTLOCK();
}
