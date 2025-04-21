/*******************************************************************************************************************************************

    DZX | LPC1769-LPCX | LED DEMO                                                                                         VERSION 18.2.1
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
static void APP_Timer1(TIMER* timer, void* arg);

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
    static TIMER timer1;
    STATUS status;
    CHAR ch;
    UINT32 pcaValue = 1;
    
    
    LED_Init();                                                 /* Initialize the on-board LED */
    
    PIN_SetFunction(P0_07, 2);                                  /* Assign P0.7 as SCK1 function */
    PIN_SetFunction(P0_08, 2);                                  /* Assign P0.8 as MOSI1 function */
    PIN_SetFunction(P0_09, 2);                                  /* Assign P0.9 as MISO1 function */
    
    status = SPI_Open(&spi,                                     /* Initialize the SPI port */
                      2,                                        /* Port number */
                      4000000,                                  /* Clock rate */
                      OPT_DEFAULT);                             /* Default options (clock polarity/phase) */
    assert(status == SUCCESS);
    
    
    status = LED_InitSevenSegment(&seg,                         /* Initialize the 7-segment LED driver */
                                  &spi,                         /* Pointer to the SPI port to be used */
                                  P2_02);                       /* Chip select pin */
    assert(status == SUCCESS);
    
    
    PIN_SetFunction(P0_10, 2);                                  /* Assign P0.10 as SDA2 function */
    PIN_SetFunction(P0_11, 2);                                  /* Assign P0.11 as SCL2 function */
    
    status = I2C_Open(&i2c,                                     /* Open on-board I2C port */
                      2,                                        /* Port number */
                      400000);                                  /* Bit rate */
    assert(status == SUCCESS);
    
    status = PCA9532_Open(&pca9532, &i2c, 0x0);                 /* Open and initialize I/O expander driver */
    assert(status == SUCCESS);
    

    status = TIMER_Create(&timer1,                              /* Create a timer for blinking LED */
                          "LED",                                /* A name for the timer */
                          APP_Timer1,                           /* A function to be called upon expiration */
                          NULL,                                 /* An optional argument passed to the expiration function */
                          100,                                  /* The timer interval, in kernel ticks */
                          OPT_START | OPT_AUTORESET);           /* Start the timer and auto-reset on expiration */
    assert(status == SUCCESS);
    
    
    for (;;) {
        
        ch = ((KERNEL_Ticks() / 100) % 10) + 0x30;              /* Create a character that represents tenths of seconds */
        LED_SetSevenSegment(&seg, ch);                          /* Display the character on the seven segment display */
        
        pcaValue <<= 2;                                         /* Update a pattern for the extra LEDs */
        if (pcaValue == 0) {
            pcaValue = 1;
        }
        
        PCA9532_WritePins(&pca9532, pcaValue);                  /* Update the extra LEDs */
    
        THREAD_Sleep(20);
    }
}

/***************************************************************************************************************************************//**

    A timer expiration callback function. Used to blink the board's LED.

    @return     None.

*******************************************************************************************************************************************/
static void APP_Timer1(TIMER* timer, void* arg)
{
    static UINT32 state = 1;


    state <<= 1;
    if (state == 0x40) {
        state = 1;
    }
    
    LED_Set(LED_RED, (state & 0x1));
    LED_Set(LED_GREEN, (state & 0x4));
    LED_Set(LED_BLUE, (state & 0x10));
}
