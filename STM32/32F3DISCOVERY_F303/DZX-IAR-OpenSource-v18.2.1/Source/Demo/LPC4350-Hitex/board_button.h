/*******************************************************************************************************************************************

    DZX | LPC4350-HITEX | BUTTON                                                                                          VERSION 18.2.1
    ------------------------------------------------------------------------------------------------------------------------------------

    This is part of the board support drivers and provides the ability to read the on-board buttons and joystick.

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
#ifndef BOARD_BUTTON_H__
#define BOARD_BUTTON_H__

#include "Kernel/kernel.h"
#include "Drivers/NXP/pca9673.h"

/*******************************************************************************************************************************************
    TYPE DEFINITIONS
*******************************************************************************************************************************************/
/***************************************************************************************************************************************//**

    Represents the possible states for the JOYSTICK.
    @module     BOARD-BUTTON-LPC4350-HITEX

*******************************************************************************************************************************************/
typedef enum BUTTON {
    BUTTON_NONE         = 0,
    JOYSTICK_RIGHT      = (1 << 0),
    JOYSTICK_UP         = (1 << 1),
    JOYSTICK_CENTER     = (1 << 2),
    JOYSTICK_LEFT       = (1 << 3),
    JOYSTICK_DOWN       = (1 << 4),
    BUTTON_SW3          = (1 << 5),
    BUTTON_SW5          = (1 << 6),
    BUTTON_SW6          = (1 << 7)
} BUTTON;

/*******************************************************************************************************************************************
    PUBLIC FUNCTIONS
*******************************************************************************************************************************************/
/***************************************************************************************************************************************//**

    Reads and returns the current pressed buttons from the on-board PCA9673 I/O expander.

    @param[in]  pca9673     A pointer to the PCA9673 driver to be used to read the buttons.

    @return     A bit-field of the current user buttons.     

     Position               | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     JOYSTICK_NONE          | The joystick is in an IDLE position.
     JOYSTICK_CENTER        | The joystick is in the CENTER position.
     JOYSTICK_UP            | The joystick is in the UP position.
     JOYSTICK_DOWN          | The joystick is in the DOWN position.
     JOYSTICK_RIGHT         | The joystick is in the RIGHT position.
     JOYSTICK_LEFT          | The joystick is in the LEFT position.
     BUTTON_SW3             | The SW3 button is pressed.
     BUTTON_SW5             | The SW5 button is pressed.
     BUTTON_SW6             | The SW5 button is pressed.
    
    @module     BOARD-BUTTON-LPC4350-HITEX

*******************************************************************************************************************************************/
extern BUTTON BUTTON_Read(PCA9673* pca9673);

#endif /* BOARD_BUTTON_H__ */
