/*******************************************************************************************************************************************

    DZX | LPC1769-LPCX | LED                                                                                              VERSION 18.2.1
    ------------------------------------------------------------------------------------------------------------------------------------

    This is part of the board support drivers and provides the ability to drive the on-board LED and the seven-segment LED display.

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
#include "mcu_spi.h"
#include "mcu_pin.h"


/*******************************************************************************************************************************************
    
    Represents an on-board LED.

*******************************************************************************************************************************************/
typedef enum LED {
    LED_RED = 0,
    LED_GREEN,
    LED_BLUE,
} LED;

/*******************************************************************************************************************************************
    
    Represents a driver for the seven-segment LED display.

*******************************************************************************************************************************************/
typedef struct SEVENSEGMENT {
    SPI*    spi;        /* SPI port used to set the segments */
    PIN     cs;         /* The chip-select pin */
} SEVENSEGMENT;

/*******************************************************************************************************************************************
    PUBLIC FUNCTIONS
*******************************************************************************************************************************************/
/***************************************************************************************************************************************//**

    Initializes the on-board LED by configuring the pin for controlling the LED.

    @return     None.
    @module     BOARD-LED-LPC1769-LPCX

*******************************************************************************************************************************************/
extern void LED_Init(void);

/***************************************************************************************************************************************//**

    Sets the illumination state for the board's LED.

    @param[in]  led         The LED to be updated.
    @param[in]  state       Use TRUE to illuminate the LED; otherwise FALSE.

    @return     None.
    @module     BOARD-LED-LPC1769-LPCX

*******************************************************************************************************************************************/
extern void LED_Set(LED led, BOOLEAN state);

/***************************************************************************************************************************************//**

    Initializes a driver for the on-board seven segment LED display.

    @param[in]  seg         A pointer to a caller allocated seven segment driver instance to be initialized.
    @param[in]  spi         A pointer to an open SPI port to be used to drive the display.
    @param[in]  cs          The chip-select pin to be used for the display.

    @return     None.
    @module     BOARD-LED-LPC1769-LPCX

*******************************************************************************************************************************************/
extern STATUS LED_InitSevenSegment(SEVENSEGMENT* s, SPI* spi, PIN cs);

/***************************************************************************************************************************************//**

    Sets the digit value upon the seven segment display.

    @param[in]  seg         A pointer to the target seven segment driver instance.
    @param[in]  ch          The character, in ASCII, to be displayed.

    @return     None.
    @module     BOARD-LED-LPC1769-LPCX

*******************************************************************************************************************************************/
extern STATUS LED_SetSevenSegment(SEVENSEGMENT* s, CHAR ch);

#endif /* BOARD_LED_H__ */
