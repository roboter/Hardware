/*******************************************************************************************************************************************

    DZX | STM32F303 DISCOVERY | LED                                                                                       VERSION 18.2.1
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
#ifndef BOARD_LED_H__
#define BOARD_LED_H__

#include "Kernel/kernel.h"

/*******************************************************************************************************************************************
    TYPE DEFINITIONS
*******************************************************************************************************************************************/
typedef enum LED {
    LED_N = 0,
    LED_NE,
    LED_E,
    LED_SE,
    LED_S,
    LED_SW,
    LED_W,
    LED_NW,
} LED;

/*******************************************************************************************************************************************
    PUBLIC FUNCTIONS
*******************************************************************************************************************************************/
/***************************************************************************************************************************************//**

    Initializes the on-board LEDs by configuring the pins that drive the LEDs.

    @return     None.
    @module     BOARD-LED-STM32F303-DISCO

*******************************************************************************************************************************************/
extern void LED_Init(void);

/***************************************************************************************************************************************//**

    Sets the illumination state for the board's LED.

    @param[in]  led         The LED to be updated.
    @param[in]  state       Use TRUE to illuminate the LED; otherwise FALSE.

    @return     None.
    @module     BOARD-LED-STM32F303-DISCO

*******************************************************************************************************************************************/
extern void LED_Set(LED led, BOOLEAN state);

#endif /* BOARD_LED_H__ */
