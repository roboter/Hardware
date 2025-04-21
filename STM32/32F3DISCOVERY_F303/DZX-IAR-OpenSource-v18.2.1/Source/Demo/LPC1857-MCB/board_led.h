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
#ifndef BOARD_LED_H__
#define BOARD_LED_H__

#include "Kernel/kernel.h"

/***************************************************************************************************************************************//**

    Represents each of the on-board LEDs.
    @module     BTN-LPC1857-MCB

*******************************************************************************************************************************************/
typedef enum LED {
    LED_0 = (1 << 0),
    LED_1 = (1 << 1),
    LED_2 = (1 << 2),
    LED_3 = (1 << 3),
    LED_4 = (1 << 4),
    LED_5 = (1 << 5),
    LED_6 = (1 << 6),
    LED_7 = (1 << 7),
} LED;

/*******************************************************************************************************************************************
    PUBLIC FUNCTIONS
*******************************************************************************************************************************************/
/***************************************************************************************************************************************//**

    Initializes the on-board LEDs by configuring the pins to drive the LEDs.

    @return     None.
    @module     BOARD-LED-LPC1857-MCB

*******************************************************************************************************************************************/
extern void LED_Init(void);

/***************************************************************************************************************************************//**

    Sets the illumination state for an LED.

    @param[in]  led         The LED to be updated.
    @param[in]  state       Use TRUE to illuminate the LED; otherwise FALSE.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The LED has been updated.
     ERR_NOTSUPPORTED       | The specified LED is not supported.

    @module     BOARD-LED-LPC1857-MCB

*******************************************************************************************************************************************/
extern STATUS LED_Set(LED led, BOOLEAN state);

#endif /* BOARD_LED_H__*/
