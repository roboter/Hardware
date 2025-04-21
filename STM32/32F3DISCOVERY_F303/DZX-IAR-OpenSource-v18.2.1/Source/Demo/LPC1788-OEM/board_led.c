/*******************************************************************************************************************************************

    DZX | LPC1788-OEM | LED                                                                                               VERSION 18.2.1
    ------------------------------------------------------------------------------------------------------------------------------------

    This is part of the board support drivers and provides support for driving the on-board LEDs.

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
#include "board_led.h"
#include "mcu_pin.h"

/*******************************************************************************************************************************************
    LOCAL CONFIGURATION
*******************************************************************************************************************************************/
#define CFG_REDLEDPIN           P2_26
#define CFG_GREENLEDPIN         P2_27

/***************************************************************************************************************************************//**

    Initializes the on-board LEDs by configuring the pins to drive the LEDs.

    @return     None.
    @module     BOARD-LED-LPC1788-OEM

*******************************************************************************************************************************************/
void LED_Init(void)
{
    PIN_SetDirection(CFG_GREENLEDPIN, DIRECTION_OUTPUT);        /* Configure the pins to drive the LEDs */
    PIN_SetDirection(CFG_REDLEDPIN, DIRECTION_OUTPUT);
 
    LED_Set(LED_GREEN, FALSE);                                  /* Begin with LEDs OFF */
    LED_Set(LED_RED, FALSE);
}

/***************************************************************************************************************************************//**

    Sets the illumination state for the board's LED.

    @param[in]  led         The LED to be set.

     LED                    | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     LED_GREEN              | The green LED.
     LED_RED                | The red LED.

    @param[in]  state       Use TRUE to illuminate the LED; otherwise FALSE.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The LED has been updated.
     ERR_NOTSUPPORTED       | The specified LED is not supported.

    @module     BOARD-LED-LPC1788-OEM

*******************************************************************************************************************************************/
STATUS LED_Set(LED led, BOOLEAN state)
{
    switch (led) {
        case LED_GREEN:
            PIN_Write(CFG_GREENLEDPIN, state ? 0 : 1);
            return SUCCESS;
        case LED_RED:
            PIN_Write(CFG_REDLEDPIN, state ? 0 : 1);
            return SUCCESS;
    }
    
    return ERR_NOTSUPPORTED;
}
