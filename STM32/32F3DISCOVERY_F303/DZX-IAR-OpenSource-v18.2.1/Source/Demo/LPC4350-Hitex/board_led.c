/*******************************************************************************************************************************************

    DZX | LPC4350-HITEX | LED                                                                                             VERSION 18.2.1
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
#define CFG_LEDREDPIN           PE_05
#define CFG_LEDGREENPIN         PE_06
#define CFG_LEDBLUEPIN          PE_08

/***************************************************************************************************************************************//**

    Initializes support for driving the on-board LEDs by configuring the pins used to drive the LEDs.
        
    @return     None.
    @module     BOARD-LPC4350-HITEX

*******************************************************************************************************************************************/
void LED_Init(void)
{
    PIN_SetFunction(CFG_LEDREDPIN, 4);                          /* Configure the LED pins for GPIO */
    PIN_SetFunction(CFG_LEDGREENPIN, 4);
    PIN_SetFunction(CFG_LEDBLUEPIN, 4);
    
    PIN_SetDirection(CFG_LEDREDPIN, DIRECTION_OUTPUT);          /* Configure the LED pins as outputs */
    PIN_SetDirection(CFG_LEDGREENPIN, DIRECTION_OUTPUT);
    PIN_SetDirection(CFG_LEDBLUEPIN, DIRECTION_OUTPUT);
    
    LED_Set(LED_RED, FALSE);                                    /* Begin with LEDs off */
    LED_Set(LED_GREEN, FALSE);
    LED_Set(LED_BLUE, FALSE);
}

/***************************************************************************************************************************************//**

    Sets the illumination state for one of the RGB LEDs.

    @param[in]  led         The LED to be updated.
    @param[in]  state       Use TRUE to illuminate the LED; otherwise FALSE.
        
    @return     None.
    @module     BOARD-LED-LPC4350-HITEX

*******************************************************************************************************************************************/
void LED_Set(LED led, BOOLEAN state)
{
    switch (led) {
        case LED_RED:
            PIN_Write(CFG_LEDREDPIN, !state);
            break;
        case LED_GREEN:
            PIN_Write(CFG_LEDGREENPIN, !state);
            break;
        case LED_BLUE:
            PIN_Write(CFG_LEDBLUEPIN, !state);
            break;
    }
}
