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
#include "board_button.h"
#include "mcu_pin.h"

/***************************************************************************************************************************************//**

    Initializes the pins for reading the on-board buttons.

    @return     None.
    @module     BOARD-BUTTON-LPC1857-MCB

*******************************************************************************************************************************************/
void BUTTON_Init(void)
{
    PIN_SetFunction(P4_00, 0);                                  /* Configure the button pins as GPIO */
    PIN_SetFunction(P4_03, 0);
    PIN_SetFunction(P4_04, 0);
    
    PIN_SetDirection(P4_00, DIRECTION_INPUT);                   /* Configure the button pins as inputs */
    PIN_SetDirection(P4_03, DIRECTION_INPUT);
    PIN_SetDirection(P4_04, DIRECTION_INPUT);
    
    PIN_SetInputBuffer(P4_00, TRUE);                            /* Enable the input buffer to read the pins */
    PIN_SetInputBuffer(P4_03, TRUE);
    PIN_SetInputBuffer(P4_04, TRUE);
}

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
BOOLEAN BUTTON_IsPressed(BTN btn)
{
    switch (btn) {
        case BTN_P4_00:
            if (PIN_Read(P4_00) == 0) {
                return TRUE;
            }
            break;
        case BTN_P4_03:
            if (PIN_Read(P4_03) == 0) {
                return TRUE;
            }
            break;
        case BTN_P4_04:
            if (PIN_Read(P4_04) == 0) {
                return TRUE;
            }
            break;
            
        default:
            break;
    }
    
    return FALSE;
}

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
JOYSTICK BUTTON_Joystick(void)
{
    JOYSTICK value = JOYSTICK_NONE;
    
    
    if (PIN_Read(PC_12) == 0) {
        value |= JOYSTICK_DOWN;
    }
    
    if (PIN_Read(PC_14) == 0) {
        value |= JOYSTICK_RIGHT;
    }
    
    if (PIN_Read(PC_11) == 0) {
        value |= JOYSTICK_UP;
    }
    
    if (PIN_Read(PC_13) == 0) {
        value |= JOYSTICK_LEFT;
    }
    
    if (PIN_Read(PC_09) == 0) {
        value |= JOYSTICK_CENTER;
    }
    
    return value;
}
