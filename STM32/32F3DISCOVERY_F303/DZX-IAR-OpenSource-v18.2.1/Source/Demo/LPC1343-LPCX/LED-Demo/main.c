/*******************************************************************************************************************************************

    DZX | LPC1343-LPCX | LED DEMO                                                                                         VERSION 18.2.1
    ------------------------------------------------------------------------------------------------------------------------------------

    This is an application that performs an LED demonstration. It blinks LEDs using the on-board I2C expander and the SPI 
    seven-segment display.

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
#include "Kernel/kernel.h"
#include "Kernel/kernel_timer.h"
#include "mcu_spi.h"
#include "mcu_i2c.h"
#include "board_led.h"
#include "Drivers/NXP/pca9532.h"
#include <assert.h>

/*******************************************************************************************************************************************
    PRIVATE VARIABLES
*******************************************************************************************************************************************/
static SPI spi;
static SEVENSEGMENT seg;
static I2C i2c;
static PCA9532 pca9532;
    
/*******************************************************************************************************************************************
    PRIVATE FUNCTIONS
*******************************************************************************************************************************************/
static void APP_Main(void* arg);
static void APP_Timer(TIMER* timer, void* arg);

/***************************************************************************************************************************************//**

    The main function for the application.
    @return     None.

*******************************************************************************************************************************************/
int main(void)
{
    KERNEL_Execute(APP_Main, NULL);                             /* Execute the kernel */
    return 0;
}

/***************************************************************************************************************************************//**

    The process function for the main application thread.

    @param[in]  arg         An optional argument. Not used here.

    @return     None.

*******************************************************************************************************************************************/
static void APP_Main(void* arg)
{
    static TIMER timer;
    STATUS status;
    CHAR ch;
    UINT32 pcaValue = 1;
    
    
    LED_Init();                                                 /* Initialize for driving the on-board LED */
    
    
    PIN_SetFunction(P2_11, 1);                                  /* Assign P2.11 to the SCK0 function */
    PIN_SetFunction(P0_09, 1);                                  /* Assign P0.9 to the MOSI0 function */
    PIN_SetFunction(P0_08, 1);                                  /* Assign P0.8 to the MISO0 function */
    PIN_SetDirection(P1_11, DIRECTION_OUTPUT);                  /* Assign P1.11 as output to be chip-select for 7-segment LED */

    PIN_SetFunction(P0_04, 1);                                  /* Assign P0.4 to the SCL function */
    PIN_SetFunction(P0_05, 1);                                  /* Assign P0.5 to the SDA function */
    
    
    status = SPI_Open(&spi,                                     /* Initialize the SPI port */
                      0,                                        /* Port number */
                      4000000,                                  /* Clock rate */
                      OPT_DEFAULT);                             /* Default options (clock polarity/phase) */
    assert(status == SUCCESS);
    
    
    status = LED_InitSevenSegment(&seg,                         /* Initialize the 7-segment LED driver */
                                  &spi,                         /* Pointer to the SPI port to be used */
                                  P1_11);                       /* Chip select pin */
    assert(status == SUCCESS);
    
    
    status = I2C_Open(&i2c,                                     /* Open on-board I2C port */
                      0,                                        /* Port number */
                      400000);                                  /* Bit rate */
    assert(status == SUCCESS);
    
    status = PCA9532_Open(&pca9532, &i2c, 0x0);                 /* Open and initialize I/O expander driver */
    assert(status == SUCCESS);
    

    status = TIMER_Create(&timer,                               /* Create a timer for blinking LED */
                          "LED",                                /* Name */
                          APP_Timer,                            /* Callback expiration function */
                          NULL,                                 /* Optional argument */
                          100,                                  /* Interval, in kernel ticks */
                          OPT_START | OPT_AUTORESET);           /* Start the timer and auto-reset on expiration */
    
    assert(status == SUCCESS);
    
    
    
    for (;;) {
        
        ch = ((KERNEL_Ticks() / 100) % 10) + 0x30;              /* Create a character that represents tenths of seconds */
        LED_SetSevenSegment(&seg, ch);                          /* Display the character on the seven segment display */
        
        pcaValue <<= 2;                                         /* Update the LED pattern */
        if (pcaValue == 0) {
            pcaValue = 1;
        }
        
        PCA9532_WritePins(&pca9532, pcaValue);
    
        THREAD_Sleep(20);
    }
}

/***************************************************************************************************************************************//**

    A timer expiration callback function. Used to blink the board's LED.

    @return     None.

*******************************************************************************************************************************************/
static void APP_Timer(TIMER* timer, void* arg)
{
    static BOOLEAN state = FALSE;
    
    state = !state;
    LED_Set(state);                                             /* Blink the on-board LED */
}
