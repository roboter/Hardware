/*******************************************************************************************************************************************

    DZX | LPC1343-LPCX | BUTTON                                                                                           VERSION 18.2.1
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

#include "Kernel/kernel_types.h"

/***************************************************************************************************************************************//**

    Represents the possible states for the JOYSTICK.
    @module     BOARD

*******************************************************************************************************************************************/
typedef enum JOYSTICK {
    JOYSTICK_NONE = 0,
    JOYSTICK_LEFT,
    JOYSTICK_RIGHT,
    JOYSTICK_UP,
    JOYSTICK_DOWN,
    JOYSTICK_CENTER,
} JOYSTICK;

/*******************************************************************************************************************************************
    PUBLIC FUNCTIONS
*******************************************************************************************************************************************/
/***************************************************************************************************************************************//**

    Returns an indication of whether the button 'SW3' is currently pressed. 

    @return     A value of '1' if the button is currently pressed; otherwise '0'.
    @remark     Does not perform any sort of debounce logic.

*******************************************************************************************************************************************/
extern UINT32 BTN_ReadSW3(void);

/***************************************************************************************************************************************//**

    Returns an indication of whether the button 'SW4' is currently pressed. 

    @return     A value of '1' if the button is currently pressed; otherwise '0'.
    @remark     Does not perform any sort of debounce logic.

*******************************************************************************************************************************************/
extern UINT32 BTN_ReadSW4(void);

/***************************************************************************************************************************************//**

    Returns the current position of the board's joystick.

    @return

     Position               | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     JOYSTICK_NONE          | The joystick is in an IDLE position.
     JOYSTICK_CENTER        | The joystick is in the CENTER position.
     JOYSTICK_UP            | The joystick is in the UP position.
     JOYSTICK_DOWN          | The joystick is in the DOWN position.
     JOYSTICK_RIGHT         | The joystick is in the RIGHT position.
     JOYSTICK_LEFT          | The joystick is in the LEFT position.   

*******************************************************************************************************************************************/
extern JOYSTICK BTN_ReadJoystick(void);

#endif /* BOARD_BUTTON_H__ */
