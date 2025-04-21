/*******************************************************************************************************************************************

    DZX | LPC1549-LPCX | LED                                                                                              VERSION 18.2.1
    ------------------------------------------------------------------------------------------------------------------------------------

    This is part of the board support drivers and provides the ability to drive the on-board LEDs.

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

/*******************************************************************************************************************************************
    LOCAL CONFIGURATION
*******************************************************************************************************************************************/
#define CFG_REDLEDPIN           P0_25
#define CFG_GREENLEDPIN         P0_03
#define CFG_BLUELEDPIN          P1_01

/***************************************************************************************************************************************//**

    Initializes the on-board LEDs by configuring the pins for the controlling the LEDs.

    @return     None.
    @module     BOARD-LED-LPC1549-LPCX

*******************************************************************************************************************************************/
void LED_Init(void)
{
    PIN_SetDirection(CFG_REDLEDPIN, DIRECTION_OUTPUT);          /* Configure each of the LED pins as outputs */
    PIN_SetDirection(CFG_GREENLEDPIN, DIRECTION_OUTPUT);
    PIN_SetDirection(CFG_BLUELEDPIN, DIRECTION_OUTPUT);
    
    PIN_Write(CFG_REDLEDPIN, 1);                                /* Begin with all LEDs OFF */
    PIN_Write(CFG_GREENLEDPIN, 1);
    PIN_Write(CFG_BLUELEDPIN, 1);
}

/***************************************************************************************************************************************//**

    Sets the illumination state for the board's LED.

    @param[in]  led         The target LED.
    @param[in]  state       TRUE to illuminate the LED; otherwise FALSE.

    @return     None.
    @module     BOARD-LED-LPC1549-LPCX

*******************************************************************************************************************************************/
void LED_Set(LED led, BOOLEAN state)
{
    switch (led) {
        case LED_RED:
            PIN_Write(P0_25, !state);
            break;
        case LED_GREEN:
            PIN_Write(P0_03, !state);
            break;
        case LED_BLUE:
            PIN_Write(P1_01, !state);
            break;
    }
}
