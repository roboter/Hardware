/*******************************************************************************************************************************************

    DZX | LPC1549-LPCX | BUTTON                                                                                           VERSION 18.2.1
    ------------------------------------------------------------------------------------------------------------------------------------

    This is part of the board support drivers and provides the ability to read the on-board buttons.

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

    Returns an indication of whether a button is currently pressed. 

    @param[in]  button      The button to be checked for being pressed.

    @return     TRUE if the specified button is currently pressed; otherwise FALSE.
    @remark     Does not perform any sort of debounce logic.
    @module     BOARD-BUTTON-LPC1549-LPCX

*******************************************************************************************************************************************/
BOOLEAN BUTTON_IsPressed(BUTTON button)
{
    switch (button) {
        case BUTTON_SW1:
            return PIN_Read(P0_17) ? FALSE : TRUE;
    }

    return FALSE;
}
