/*******************************************************************************************************************************************

    DZX | LPC1857-MCB | LED                                                                                               VERSION 18.2.1
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
#define CFG_LED0PIN             P9_02
#define CFG_LED1PIN             P9_01
#define CFG_LED2PIN             P9_00
#define CFG_LED3PIN             PD_14
#define CFG_LED4PIN             PD_13
#define CFG_LED5PIN             PD_12
#define CFG_LED6PIN             PD_11
#define CFG_LED7PIN             PD_10

/***************************************************************************************************************************************//**

    Initializes the on-board LEDs by configuring the pins to drive the LEDs.

    @return     None.
    @module     BOARD-LED-LPC1857-MCB

*******************************************************************************************************************************************/
void LED_Init(void)
{
    PIN_SetFunction(CFG_LED0PIN, 0);                            /* Assign each LED pin as GPIO */
    PIN_SetFunction(CFG_LED1PIN, 0);
    PIN_SetFunction(CFG_LED2PIN, 0);
    PIN_SetFunction(CFG_LED3PIN, 4);
    PIN_SetFunction(CFG_LED4PIN, 4);
    PIN_SetFunction(CFG_LED5PIN, 4);
    PIN_SetFunction(CFG_LED6PIN, 4);
    PIN_SetFunction(CFG_LED7PIN, 4);
    
    PIN_SetDirection(CFG_LED0PIN, DIRECTION_OUTPUT);            /* Configure each LED pin as an output */
    PIN_SetDirection(CFG_LED1PIN, DIRECTION_OUTPUT);
    PIN_SetDirection(CFG_LED2PIN, DIRECTION_OUTPUT);
    PIN_SetDirection(CFG_LED3PIN, DIRECTION_OUTPUT);
    PIN_SetDirection(CFG_LED4PIN, DIRECTION_OUTPUT);
    PIN_SetDirection(CFG_LED5PIN, DIRECTION_OUTPUT);
    PIN_SetDirection(CFG_LED6PIN, DIRECTION_OUTPUT);
    PIN_SetDirection(CFG_LED7PIN, DIRECTION_OUTPUT);
    
    PIN_Write(CFG_LED0PIN, FALSE);                              /* Begin with each LED off */
    PIN_Write(CFG_LED1PIN, FALSE);
    PIN_Write(CFG_LED2PIN, FALSE);
    PIN_Write(CFG_LED3PIN, FALSE);
    PIN_Write(CFG_LED4PIN, FALSE);
    PIN_Write(CFG_LED5PIN, FALSE);
    PIN_Write(CFG_LED6PIN, FALSE);
    PIN_Write(CFG_LED7PIN, FALSE);
}

/***************************************************************************************************************************************//**

    Sets the illumination state for the board's LED.

    @param[in]  state       The new state for the LED. Use a '1' value to turn it ON; otherwise '0' to turn it OFF.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The LED has been updated.
     ERR_NOTSUPPORTED       | The specified LED is not supported.

    @module     BOARD-LED-LPC1857-MCB

*******************************************************************************************************************************************/
STATUS LED_Set(LED led, BOOLEAN state)
{
    switch (led) {
        case LED_0:
            PIN_Write(CFG_LED0PIN, state);
            return SUCCESS;
        case LED_1:
            PIN_Write(CFG_LED1PIN, state);
            return SUCCESS;
        case LED_2:
            PIN_Write(CFG_LED2PIN, state);
            return SUCCESS;
        case LED_3:
            PIN_Write(CFG_LED3PIN, state);
            return SUCCESS;
        case LED_4:
            PIN_Write(CFG_LED4PIN, state);
            return SUCCESS;
        case LED_5:
            PIN_Write(CFG_LED5PIN, state);
            return SUCCESS;
        case LED_6:
            PIN_Write(CFG_LED6PIN, state);
            return SUCCESS;
        case LED_7:
            PIN_Write(CFG_LED7PIN, state);
            return SUCCESS;
        default:
            break;
    }
    
    return ERR_NOTSUPPORTED;
}
