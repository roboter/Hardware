/*******************************************************************************************************************************************

    DZX | LPC15xx | PIN                                                                                                   VERSION 18.2.1
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
#include "mcu_syscon.h"

/*******************************************************************************************************************************************
    PRIVATE DEFINITIONS
*******************************************************************************************************************************************/
#define PINFROMNUMBERS(port, pin)   (PIN)((port << 8) | (pin))          /* Convert port & pin numbers into a pin */
#define PIN_NUMBER(pin)             (pin & 0xFF)                        /* Get a pin's pin number */
#define PIN_PORTNUMBER(pin)         ((pin >> 8) & 0xFF)                 /* Get a pin's port number */

/*******************************************************************************************************************************************
    PRIVATE VARIABLES
*******************************************************************************************************************************************/

/***************************************************************************************************************************************//**

    Assigns a pin to a function.

    @param[in]  function    The target function to be assigned the pin.
    @param[in]  pin         The pin to be assigned to the function.

    @return     None.
    @module     pin-lpc15xx

*******************************************************************************************************************************************/
void PIN_Assign(FUNCTION function, PIN pin)
{
    volatile UINT32* reg;
    INTERRUPTLOCK lock;
    UINT32 offset;
    UINT32 value;
    
    
    reg = (volatile UINT32*)(REG_PINASSIGNBASE + (((UINT32)function >> 2) << 2));
    offset = ((UINT32)function % 4) << 3;
    value = (PIN_PORTNUMBER(pin) << 5) + PIN_NUMBER(pin);
    
    ACQUIREINTERRUPTLOCK();
    
    *reg &= (0xFF << offset);
    *reg |= (value << offset);
    
    RELEASEINTERRUPTLOCK();
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
    @module     pin-lpc15xx

*******************************************************************************************************************************************/
void PIN_SetDirection(PIN pin, DIRECTION dir)
{
    volatile UINT32* reg;
    INTERRUPTLOCK lock;
    
    
    reg = (volatile UINT32*)(REG_GPIODIRBASE + (PIN_PORTNUMBER(pin) << 2));
    
    ACQUIREINTERRUPTLOCK();
    if (dir) {
        *reg |= (1UL << PIN_NUMBER(pin));
    } else {
        *reg &= ~(1UL << PIN_NUMBER(pin));
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

    @module     pin-lpc15xx

*******************************************************************************************************************************************/
DIRECTION PIN_Direction(PIN pin)
{
    volatile UINT32* reg;
    INTERRUPTLOCK lock;
    
    
    reg = (volatile UINT32*)(REG_GPIODIRBASE + (PIN_PORTNUMBER(pin) << 2));
    
    ACQUIREINTERRUPTLOCK();
    
    if (*reg & (1UL << PIN_NUMBER(pin))) {
        
        RELEASEINTERRUPTLOCK();
        return DIRECTION_OUTPUT;
    }
    
    RELEASEINTERRUPTLOCK();
    return DIRECTION_INPUT;
}

/***************************************************************************************************************************************//**

    Writes a value to a pin.

    @param[in]  pin         The target pin.
    @param[in]  value       The new value for the specified pin. Use '1' to set the pin as logic level high, or use '0' to set the pin 
                            as logic level low.

    @return     None.
    @module     pin-lpc15xx

*******************************************************************************************************************************************/
void PIN_Write(PIN pin, UINT32 value)
{
    volatile UINT32* reg;
    INTERRUPTLOCK lock;
    

    
    if (value) {
        reg = (volatile UINT32*)(REG_GPIOSETBASE + (PIN_PORTNUMBER(pin) << 2));     /* Get the GPIO SET register */
    } else {
        reg = (volatile UINT32*)(REG_GPIOCLRBASE + (PIN_PORTNUMBER(pin) << 2));     /* Get the GPIO CLR register */
    }
    
    ACQUIREINTERRUPTLOCK();
    *reg = (1UL << PIN_NUMBER(pin));
    RELEASEINTERRUPTLOCK();
}

/***************************************************************************************************************************************//**

    Reads and returns the current state of a pin.

    @param[in]  pin         The target pin.

    @return     A value '1' if the pin is currently high; otherwise '0' if low.
    @module     pin-lpc15xx

*******************************************************************************************************************************************/
UINT32 PIN_Read(PIN pin)
{
    volatile UINT32* reg;
    INTERRUPTLOCK lock;
    
    
    reg = (volatile UINT32*)(REG_GPIOPINBASE + (PIN_PORTNUMBER(pin) << 2));
    
    ACQUIREINTERRUPTLOCK();
    
    if (*reg & (1UL << PIN_NUMBER(pin))) {
        RELEASEINTERRUPTLOCK();
        return 1;
    }
    
    RELEASEINTERRUPTLOCK();
    return 0;
}

/***************************************************************************************************************************************//**

    Reads and returns the current mask for a pin port. A zero in this register�s bit enables an access to the corresponding physical pin 
    via a read or write access using either PINPORT_Write() or PINPORT_Read(). If a bit in this register is one, the corresponding pin 
    will not be changed with write using PINPORT_Write().

    @param[in]  port        The target pin port.

    @return     The current mask that is applied to the specified port.
    @module     pin-lpc15xx

*******************************************************************************************************************************************/
UINT32 PORT_Mask(PORT port)
{
    INTERRUPTLOCK lock;
    UINT32 mask = 0;
    
    
    ACQUIREINTERRUPTLOCK();
    
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
    @module     pin-lpc15xx

*******************************************************************************************************************************************/
void PORT_SetMask(PORT port, UINT32 mask)
{
    INTERRUPTLOCK lock;
    
    
    ACQUIREINTERRUPTLOCK();

    RELEASEINTERRUPTLOCK();
}

/***************************************************************************************************************************************//**

    Reads and returns the direction bits for each of the pins on a port.

    @param[in]  port        The target pin port.

    @return     A bit-field indicating the configured direction for each of the pins on the specified port. A bit value of '1' indicates 
                the pin is configured as an output while a '0' indicates configured as an input.
    @module     pin-lpc15xx

*******************************************************************************************************************************************/
UINT32 PORT_Direction(PORT port)
{
    INTERRUPTLOCK lock;
    UINT32 value = 0;


    ACQUIREINTERRUPTLOCK();
    
    RELEASEINTERRUPTLOCK();  
    return value;
}

/***************************************************************************************************************************************//**

    Sets the direction for each of the pins on a port.

    @param[in]  port        The target pin port.
    @param[in]  value       A bit-field that specifies a direction for each of the pins. A bit value of '1' indicates the pin to be 
                            configured as an output while a '0' indicates to be configured as an input.

    @return     None.
    @module     pin-lpc15xx

*******************************************************************************************************************************************/
void PORT_SetDirection(PORT port, UINT32 value)
{
    INTERRUPTLOCK lock;


    ACQUIREINTERRUPTLOCK();  
    
    RELEASEINTERRUPTLOCK();
}

/***************************************************************************************************************************************//**

    Reads and returns a bit-field of states of each of the pins for a port. Only valid for the pins that are not currently masked by the
    PINPORT_SetMask() function.

    @param[in]  port        The target pin port.

    @return     A bit value '1' indicates the pin is currently high; otherwise a '0' if the pin is low.
    @module     pin-lpc15xx

*******************************************************************************************************************************************/
UINT32 PORT_Read(PORT port)
{
    INTERRUPTLOCK lock;
    UINT32 value = 0;
    
    
    ACQUIREINTERRUPTLOCK();
   
    
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
    @module     pin-lpc15xx

*******************************************************************************************************************************************/
void PORT_Write(PORT port, UINT32 value)
{
    INTERRUPTLOCK lock;
    
    
    ACQUIREINTERRUPTLOCK();
    
    RELEASEINTERRUPTLOCK();
}
