/*******************************************************************************************************************************************

    DZX | LPC43xx | PIN                                                                                                   VERSION 18.2.1
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
#include "mcu_scu.h"

/*******************************************************************************************************************************************
    LOCAL DEFINITIONS
*******************************************************************************************************************************************/
#define PINFROMNUMBERS(port, pin)   (PIN)((port << 8) | (pin))          /* Convert port & pin numbers into a pin */
#define PIN_NUMBER(pin)             (pin & 0xFF)                        /* Get a pin's pin number */
#define PIN_PORTNUMBER(pin)         ((pin >> 8) & 0xFF)                 /* Get a pin's port number */
#define PIN_SFSP(pin)               (pin >> 16)

/***************************************************************************************************************************************//**

    Writes a value to a pin.

    @param[in]  pin         The target pin.
    @param[in]  value       The new value for the specified pin. Use '1' to set the pin as logic level high, or use '0' to set the pin as 
                            logic level low.

    @return     None.
    @module     pin-lpc43xx

*******************************************************************************************************************************************/
void PIN_Write(PIN pin, UINT32 value)
{
    INTERRUPTLOCK lock;
    UINT32 port;
    
    
    port = PIN_PORTNUMBER(pin);
    if (port < PORT_MAX) {
    
        ACQUIREINTERRUPTLOCK();
        
        if (value) {
            REG_GPIOSET[port] = (1UL << PIN_NUMBER(pin));
        } else {
            REG_GPIOCLR[port] = (1UL << PIN_NUMBER(pin));
        }
        
        RELEASEINTERRUPTLOCK();
    }
}

/***************************************************************************************************************************************//**

    Reads and returns the current state of a pin.

    @param[in]  pin         The target pin.

    @return     A value '1' if the pin is currently high; otherwise '0' if low.
    @module     pin-lpc43xx

*******************************************************************************************************************************************/
UINT32 PIN_Read(PIN pin)
{
    INTERRUPTLOCK lock;
    
    
    ACQUIREINTERRUPTLOCK();
 
    if (REG_GPIOPIN[PIN_PORTNUMBER(pin)] & (1UL << PIN_NUMBER(pin))) {
        RELEASEINTERRUPTLOCK();
        return 1;
    }
    
    RELEASEINTERRUPTLOCK();
    return 0;
}

/***************************************************************************************************************************************//**

    Returns the current direction setting for a pin.

    @param[in]  pin         The target pin.

    @return

     Direction              | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     DIRECTION_OUTPUT       | The pin is configured as an output.
     DIRECTION_INPUT        | The pin is configured as an input.

    @module     pin-lpc43xx

*******************************************************************************************************************************************/
DIRECTION PIN_Direction(PIN pin)
{
    INTERRUPTLOCK lock;
    
    
    ACQUIREINTERRUPTLOCK();
    
    if (REG_GPIODIR[PIN_PORTNUMBER(pin)] & (1UL << PIN_NUMBER(pin))) {
        
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
    @module     pin-lpc43xx

*******************************************************************************************************************************************/
void PIN_SetDirection(PIN pin, DIRECTION dir)
{
    INTERRUPTLOCK lock;
    
    
    ACQUIREINTERRUPTLOCK();
    
    if (dir) {
        REG_GPIODIR[PIN_PORTNUMBER(pin)] |= (1UL << PIN_NUMBER(pin));
    } else {
        REG_GPIODIR[PIN_PORTNUMBER(pin)] &= ~(1UL << PIN_NUMBER(pin));
    }
    
    RELEASEINTERRUPTLOCK();
}

/***************************************************************************************************************************************//**

    Returns the current function of a pin.

    @param[in]  pin         The target pin.

    @return     The function number assigned to the specified to the pin.
    @module     pin-lpc43xx

*******************************************************************************************************************************************/
BYTE PIN_Function(PIN pin)
{
    volatile UINT32* reg;
    INTERRUPTLOCK lock;
    BYTE function;
    
    
    reg = (volatile UINT32*)(REG_SFSPBASE + ((UINT32)pin >> 16));
    
    ACQUIREINTERRUPTLOCK();
    function = *reg & 0x7;
    RELEASEINTERRUPTLOCK();
    
    return function;
}

/***************************************************************************************************************************************//**

    Sets the function for a pin.

    @param[in]  pin         The pin to be configured.
    @param[in]  function    The new function for the pin.

     function               | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     0                      | Assign the pin to function number 0 (default).
     1                      | Assign the pin to function number 1.
     2                      | Assign the pin to function number 2.
     3                      | Assign the pin to function number 3.
     4                      | Assign the pin to function number 4.
     5                      | Assign the pin to function number 5.
     6                      | Assign the pin to function number 6.
     7                      | Assign the pin to function number 7.

    @return     None.
    @module     pin-lpc43xx

*******************************************************************************************************************************************/
void PIN_SetFunction(PIN pin, BYTE function)
{
    volatile UINT32* reg;
    INTERRUPTLOCK lock;
    
    
    reg = (volatile UINT32*)(REG_SFSPBASE + ((UINT32)pin >> 16));
    
    ACQUIREINTERRUPTLOCK();
    *reg &= ~0x00000007;
    *reg |= (function & 0x7);
    RELEASEINTERRUPTLOCK();
}

/***************************************************************************************************************************************//**

    Reads and returns the state of a bit within the SFSP register for a pin.

    @param[in]  pin         The target pin.
    @param[in]  bit         The number of the target bit.

    @return     TRUE if the specified bit is set; otherwise FALSE.
    @module     pin-lpc43xx

*******************************************************************************************************************************************/
BOOLEAN PIN_ConfigBit(PIN pin, UINT32 bit)
{
    volatile UINT32* reg;
    INTERRUPTLOCK lock;
    
    
    reg = (volatile UINT32*)(REG_SFSPBASE + ((UINT32)pin >> 16));
    
    ACQUIREINTERRUPTLOCK();
    
    if (*reg & (1UL << bit)) {  
        
        RELEASEINTERRUPTLOCK();
        return TRUE;
    }

    RELEASEINTERRUPTLOCK();
    return FALSE;
}

/***************************************************************************************************************************************//**

    Assigns a new state of a bit within the SFSP register for a pin.

    @param[in]  pin         The target pin.
    @param[in]  bit         The number of the bit to be updated.
    @param[in]  state       The new state for the bit. Use TRUE to set the bit and FALSE to clear the bit.

    @return     None.
    @module     pin-lpc43xx

*******************************************************************************************************************************************/
void PIN_SetConfigBit(PIN pin, UINT32 bit, BOOLEAN state)
{
    volatile UINT32* reg;
    INTERRUPTLOCK lock;
    
    
    reg = (volatile UINT32*)(REG_SFSPBASE + ((UINT32)pin >> 16));
    
    ACQUIREINTERRUPTLOCK();
    
    if (state) {
        *reg |= (1UL << bit);
    } else {
        *reg &= ~(1UL << bit);
    }
    
    RELEASEINTERRUPTLOCK();
}

/***************************************************************************************************************************************//**

    Returns an indication of whether the input buffer is enabled for the specified pin.

    @param[in]  pin         The target pin.

    @return     TRUE if the input buffer is enabled for the pin; otherwise FALSE.
    @module     pin-lpc43xx

*******************************************************************************************************************************************/
BOOLEAN PIN_InputBuffer(PIN pin)
{
    return PIN_ConfigBit(pin, 6);
}

/***************************************************************************************************************************************//**

    Enables or disables the input buffer for a pin.

    @param[in]  pin         The target pin.
    @param[in]  enabled     Use TRUE to enable the input buffer for the pin, otherwise FALSE to disable the input buffer.

    @return     None.
    @module     pin-lpc43xx

*******************************************************************************************************************************************/
void PIN_SetInputBuffer(PIN pin, BOOLEAN enabled)
{
    PIN_SetConfigBit(pin, 6, enabled);
}

/***************************************************************************************************************************************//**

    Returns an indication of whether the pull down resistor is enabled for the specified pin.

    @param[in]  pin         The target pin.

    @return     TRUE if the pull down resistor is enabled for the pin; otherwise FALSE.
    @module     pin-lpc43xx

*******************************************************************************************************************************************/
BOOLEAN PIN_PullDown(PIN pin)
{
    return PIN_ConfigBit(pin, 3);
}

/***************************************************************************************************************************************//**

    Enables or disables the pull down resistor for a pin.

    @param[in]  pin         The target pin.
    @param[in]  enabled     Use TRUE to enable the pull down resistor for the pin, otherwise FALSE to disable the pull down resistor.

    @return     None.
    @module     pin-lpc43xx

*******************************************************************************************************************************************/
void PIN_SetPullDown(PIN pin, BOOLEAN enabled)
{
    PIN_SetConfigBit(pin, 3, enabled);
}

/***************************************************************************************************************************************//**

    Returns an indication of whether the pull up resistor is enabled for the specified pin.

    @param[in]  pin         The target pin.

    @return     TRUE if the pull up resistor is enabled for the pin; otherwise FALSE.
    @module     pin-lpc43xx

*******************************************************************************************************************************************/
BOOLEAN PIN_PullUp(PIN pin)
{
    return !PIN_ConfigBit(pin, 4);
}

/***************************************************************************************************************************************//**

    Enables or disables the pull up resistor for a pin.

    @param[in]  pin         The target pin.
    @param[in]  enabled     Use TRUE to enable the pull up resistor for the pin, otherwise FALSE to disable the pull up resistor.

    @return     None.
    @module     pin-lpc43xx

*******************************************************************************************************************************************/
void PIN_SetPullUp(PIN pin, BOOLEAN enabled)
{
    PIN_SetConfigBit(pin, 4, !enabled);
}

/***************************************************************************************************************************************//**

    Returns an indication of whether the glitch filter is enabled for the specified pin.

    @param[in]  pin         The target pin.

    @return     TRUE if the glitch filter is enabled for the pin; otherwise FALSE.
    @module     pin-lpc43xx

*******************************************************************************************************************************************/
BOOLEAN PIN_GlitchFilter(PIN pin)
{
    return !PIN_ConfigBit(pin, 7);
}

/***************************************************************************************************************************************//**

    Enables or disables the glitch filter for a pin.

    @param[in]  pin         The target pin.
    @param[in]  enabled     Use TRUE to enable the glitch filter for the pin, otherwise FALSE to disable the glitch filter.

    @return     None.
    @module     pin-lpc43xx

*******************************************************************************************************************************************/
void PIN_SetGlitchFilter(PIN pin, BOOLEAN enabled)
{
    PIN_SetConfigBit(pin, 7, !enabled);
}

/***************************************************************************************************************************************//**

    Returns an indication of whether the fast slew rate is enabled for the specified pin.

    @param[in]  pin         The target pin.

    @return     TRUE if the fast slew rate is enabled for the pin; otherwise FALSE.
    @module     pin-lpc43xx

*******************************************************************************************************************************************/
BOOLEAN PIN_FastSlewRate(PIN pin)
{
    return PIN_ConfigBit(pin, 5);
}

/***************************************************************************************************************************************//**

    Enables or disables the fast slew rate for a pin.

    @param[in]  pin         The target pin.
    @param[in]  enabled     Use TRUE to enable the fast slew rate for the pin, otherwise FALSE.

    @return     None.
    @module     pin-lpc43xx

*******************************************************************************************************************************************/
void PIN_SetFastSlewRate(PIN pin, BOOLEAN enabled)
{
    PIN_SetConfigBit(pin, 5, enabled);
}

/***************************************************************************************************************************************//**

    Reads and returns the current mask for a pin port. A zero in this register�s bit enables an access to the corresponding physical pin 
    via a read or write access using either PINPORT_Write() or PINPORT_Read(). If a bit in this register is one, the corresponding pin 
    will not be changed with write using PINPORT_Write().

    @param[in]  port        The target pin port.

    @return     The current mask that is applied to the specified port.
    @module     pin-lpc43xx

*******************************************************************************************************************************************/
UINT32 PORT_Mask(PORT port)
{
    INTERRUPTLOCK lock;
    UINT32 mask;
    
    
    ACQUIREINTERRUPTLOCK();
    
    mask = REG_GPIOMASK[port];
    
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
    @module     pin-lpc43xx

*******************************************************************************************************************************************/
void PORT_SetMask(PORT port, UINT32 mask)
{
    INTERRUPTLOCK lock;
    
    
    ACQUIREINTERRUPTLOCK();
    
    REG_GPIOMASK[port] = mask;
    
    RELEASEINTERRUPTLOCK();
}

/***************************************************************************************************************************************//**

    Reads and returns the direction bits for each of the pins on a port.

    @param[in]  port        The target pin port.

    @return     A bit-field indicating the configured direction for each of the pins on the specified port. A bit value of '1' indicates 
                the pin is configured as an output while a '0' indicates configured as an input.
    @module     pin-lpc43xx

*******************************************************************************************************************************************/
UINT32 PORT_Direction(PORT port)
{
    INTERRUPTLOCK lock;
    UINT32 value;


    ACQUIREINTERRUPTLOCK();
    
    value = REG_GPIODIR[port];
    
    RELEASEINTERRUPTLOCK();  
    return value;
}

/***************************************************************************************************************************************//**

    Sets the direction for each of the pins on a port.

    @param[in]  port        The target pin port.
    @param[in]  value       A bit-field that specifies a direction for each of the pins. A bit value of '1' indicates the pin to be 
                            configured as an output while a '0' indicates to be configured as an input.

    @return     None.
    @module     pin-lpc43xx

*******************************************************************************************************************************************/
void PORT_SetDirection(PORT port, UINT32 value)
{
    INTERRUPTLOCK lock;


    ACQUIREINTERRUPTLOCK();
    
    REG_GPIODIR[port] = value;  
    
    RELEASEINTERRUPTLOCK();
}

/***************************************************************************************************************************************//**

    Reads and returns a bit-field of states of each of the pins for a port. Only valid for the pins that are not currently masked by the
    PINPORT_SetMask() function.

    @param[in]  port        The target pin port.

    @return     A bit value '1' indicates the pin is currently high; otherwise a '0' if the pin is low.
    @module     pin-lpc43xx

*******************************************************************************************************************************************/
UINT32 PORT_Read(PORT port)
{
    INTERRUPTLOCK lock;
    UINT32 value;
    
    
    ACQUIREINTERRUPTLOCK();
    
    value = REG_GPIOPIN[port];
    
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
    @module     pin-lpc43xx

*******************************************************************************************************************************************/
void PORT_Write(PORT port, UINT32 value)
{
    INTERRUPTLOCK lock;
    
    
    ACQUIREINTERRUPTLOCK();
    
    REG_GPIOPIN[port] = value;
    
    RELEASEINTERRUPTLOCK();
}
