/*******************************************************************************************************************************************

    DZX | STM32F411 DISCOVERY | LED                                                                                       VERSION 18.2.1
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
#include "mcu_pin.h"

/*******************************************************************************************************************************************
    LED PIN ASSIGNMENT
*******************************************************************************************************************************************/
const PIN LED_Pins[] = {
    PD_12, PD_13, PD_14, PD_15
};

/***************************************************************************************************************************************//**

    Initializes the on-board LEDs by configuring the pins that drive the LEDs.

    @return     None.
    @module     BOARD-LED-STM32F411-DISCO

*******************************************************************************************************************************************/
void LED_Init(void)
{
    UINT32 k;
    
    
    for (k = 0; k < 4; k++) {
        PIN_SetMode(LED_Pins[k], MODE_OUTPUT);
    }
}

/***************************************************************************************************************************************//**

    Sets the illumination state for the board's LED.

    @param[in]  led         The LED to be updated.
    @param[in]  state       Use TRUE to illuminate the LED; otherwise FALSE.

    @return     None.
    @module     BOARD-LED-STM32F411-DISCO

*******************************************************************************************************************************************/
void LED_Set(LED led, BOOLEAN state)
{
    PIN_Write(LED_Pins[led], state);
}
