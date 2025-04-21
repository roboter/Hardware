/*******************************************************************************************************************************************

    DZX | LPC1857-MCB | BUTTON                                                                                            VERSION 18.2.1
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

/***************************************************************************************************************************************//**

    Represents each of the on-board buttons.
    @module     BTN-LPC1857-MCB

*******************************************************************************************************************************************/
typedef enum BTN {
    BTN_P4_00 = 0,
    BTN_P4_03,
    BTN_P4_04,
    BTN_WUP,
} BTN;

/***************************************************************************************************************************************//**

    Represents the possible states for the JOYSTICK.
    @module     BTN-LPC1857-MCB

*******************************************************************************************************************************************/
typedef enum JOYSTICK {
    JOYSTICK_NONE       = 0,
    JOYSTICK_LEFT       = (1 << 0),
    JOYSTICK_RIGHT      = (1 << 1),
    JOYSTICK_UP         = (1 << 2),
    JOYSTICK_DOWN       = (1 << 3),
    JOYSTICK_CENTER     = (1 << 4)
} JOYSTICK;

/*******************************************************************************************************************************************
    PUBLIC FUNCTIONS
*******************************************************************************************************************************************/
/***************************************************************************************************************************************//**

    Initializes the pins for reading the on-board buttons.

    @return     None.
    @module     BOARD-BUTTON-LPC1857-MCB

*******************************************************************************************************************************************/
extern void BUTTON_Init(void);

/***************************************************************************************************************************************//**

    Returns and indication of whether a button is currently pressed.

    @param[in]  btn         The button to be checked for being pressed.

     btn                    | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     BTN_P4_00              | The button labeled P4_0.
     BTN_P4_03              | The button labeled P4_3.
     BTN_P4_04              | The button labeled P4_4. 
    
    @return     TRUE if the specified button is currently pressed; otherwise FALSE.
    @module     BOARD-BUTTON-LPC1857-MCB

*******************************************************************************************************************************************/
extern BOOLEAN BUTTON_IsPressed(BTN btn);

/***************************************************************************************************************************************//**

    Returns the current position of the board's joystick.

    @return     A bit-field of the current joystick buttons.     

     Position               | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     JOYSTICK_NONE          | The joystick is in an IDLE position.
     JOYSTICK_CENTER        | The joystick is in the CENTER position.
     JOYSTICK_UP            | The joystick is in the UP position.
     JOYSTICK_DOWN          | The joystick is in the DOWN position.
     JOYSTICK_RIGHT         | The joystick is in the RIGHT position.
     JOYSTICK_LEFT          | The joystick is in the LEFT position.   
    
    @module     BOARD-BUTTON-LPC1857-MCB

*******************************************************************************************************************************************/
extern JOYSTICK BUTTON_Joystick(void);

#endif /* BOARD_BUTTON_H__ */
