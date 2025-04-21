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
#ifndef BOARD_LED_H__
#define BOARD_LED_H__

#include "Kernel/kernel.h"

/***************************************************************************************************************************************//**

    Represents the available on-board LEDs.

*******************************************************************************************************************************************/
typedef enum LED {
    LED_GREEN = 0,      /**< The green LED */
    LED_RED,            /**< The red LED */
} LED;

/*******************************************************************************************************************************************
    PUBLIC FUNCTIONS
*******************************************************************************************************************************************/
/***************************************************************************************************************************************//**

    Initializes the on-board LEDs by configuring the pins to drive the LEDs.

    @return     None.
    @module     BOARD-LED-LPC1788-OEM

*******************************************************************************************************************************************/
extern void LED_Init(void);

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
extern STATUS LED_Set(LED led, UINT32 state);

#endif /* BOARD_LED_H__ */
