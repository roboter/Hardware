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
#include "board_led.h"

/*******************************************************************************************************************************************
    LOCAL CONFIGURATION
*******************************************************************************************************************************************/
#define CFG_REDLEDPIN           P0_22
#define CFG_GREENLEDPIN         P3_25
#define CFG_BLUELEDPIN          P3_26

/***************************************************************************************************************************************//**

    Initializes the on-board LED by configuring the pin for controlling the LED.

    @return     None.
    @module     BOARD-LED-LPC1769-LPCX

*******************************************************************************************************************************************/
void LED_Init(void)
{
    PIN_SetDirection(CFG_REDLEDPIN, DIRECTION_OUTPUT);          /* Configure the pin as an output to drive the LED */
    PIN_SetDirection(CFG_GREENLEDPIN, DIRECTION_OUTPUT);
    PIN_SetDirection(CFG_BLUELEDPIN, DIRECTION_OUTPUT);
    
    LED_Set(LED_RED, FALSE);                                    /* Begin with the LED off */
    LED_Set(LED_GREEN, FALSE);
    LED_Set(LED_BLUE, FALSE);
}

/***************************************************************************************************************************************//**

    Sets the illumination state for the board's LED.

    @param[in]  led         The LED to be updated.
    @param[in]  state       Use TRUE to illuminate the LED; otherwise FALSE.

    @return     None.
    @module     BOARD-LED-LPC1769-LPCX

*******************************************************************************************************************************************/
void LED_Set(LED led, BOOLEAN state)
{
    switch (led) {
        case LED_RED:
            PIN_Write(CFG_REDLEDPIN, !state);
            break;
        case LED_GREEN:
            PIN_Write(CFG_GREENLEDPIN, !state);
            break;
        case LED_BLUE:
            PIN_Write(CFG_BLUELEDPIN, !state);
            break;
    }
}

/***************************************************************************************************************************************//**

    Initializes a driver for the on-board seven segment LED display.

    @param[in]  seg         A pointer to a caller allocated seven segment driver instance to be initialized.
    @param[in]  spi         A pointer to an open SPI port to be used to drive the display.
    @param[in]  cs          The chip-select pin to be used for the display.

    @return     None.
    @module     BOARD-LED-LPC1769-LPCX

*******************************************************************************************************************************************/
STATUS LED_InitSevenSegment(SEVENSEGMENT* seg, SPI* spi, PIN cs)
{
#if (CFG_NULLCHECKING)
    if (seg == NULL) {
        return ERR_NULLREFERENCE;
    }
    
    if (spi == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif
    
    seg->spi = spi;                                             /* Assign the SPI port to be used */
    seg->cs = cs;                                               /* Assign the pin to be used as chip-select */

    PIN_SetDirection(cs, DIRECTION_OUTPUT);                     /* Configure the chip-select pin as an output */
    PIN_Write(cs, 1);                                           /* Begin not-selected */
    
    return SUCCESS;
}

/***************************************************************************************************************************************//**

    Sets the digit value upon the seven segment display.

    @param[in]  seg         A pointer to the target seven segment driver instance.
    @param[in]  ch          The character, in ASCII, to be displayed.

    @return     None.
    @module     BOARD-LED-LPC1769-LPCX

*******************************************************************************************************************************************/
STATUS LED_SetSevenSegment(SEVENSEGMENT* seg, CHAR ch)
{
    STATUS status;
    BYTE val;
    

    switch (ch) {                                           /* Get the segments for the specified character */
        case 0x30:
            val = 0x24;
            break;
        case 0x31:
            val = 0xAF;
            break;
        case 0x32:
            val = 0xE0;
            break;
        case 0x33:
            val = 0xA2;
            break;
        case 0x34:
            val = 0x2B;
            break;
        case 0x35:
            val = 0x32;
            break;
        case 0x36:
            val = 0x30;
            break;
        case 0x37:
            val = 0xA7;
            break;
        case 0x38:
            val = 0x20;
            break;
        case 0x39:
            val = 0x22;
            break;

        default:
            val = 0xFF;
            break;
    }

    status = SPI_Select(seg->spi, seg->cs, INFINITE);           /* Activate the chip-select */
    if (status != SUCCESS) {
        return status;
    }
    
    status = SPI_Write(seg->spi, &val, 1, INFINITE);            /* Write the segment data */

    SPI_Deselect(seg->spi, seg->cs);                            /* Deactivate the chip-select signal */
    return status;
}
