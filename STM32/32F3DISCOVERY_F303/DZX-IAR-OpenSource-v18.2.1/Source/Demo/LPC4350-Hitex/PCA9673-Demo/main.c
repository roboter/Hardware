/*******************************************************************************************************************************************

    DZX | LPC4350-HITEX | PCA9673 DEMO                                                                                    VERSION 18.2.1
    ------------------------------------------------------------------------------------------------------------------------------------

    This is an application that demonstrates using the on-board PCA9673 I/O expander to driver user LEDs and read user buttons.

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
#include "board_led.h"
#include "board_button.h"
#include <stdio.h>
#include <assert.h>

/*******************************************************************************************************************************************
    PRIVATE VARIABLES
*******************************************************************************************************************************************/
static I2C i2c;                 /**< Allocate an I2C port driver to communicate with the PCA9673 */
static PCA9673 pca9673;         /**< Allocate a PCA9673 driver instance */

/*******************************************************************************************************************************************
    PRIVATE FUNCTIONS
*******************************************************************************************************************************************/
static void APP_Main(void* arg);

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

    A timer callback handler that blinks the on-board LEDs.
    @return     None.

*******************************************************************************************************************************************/
static void APP_Timer1(TIMER* timer, void* arg)
{
    static UINT32 state = 1;
    UINT16 value;
    

    state <<= 1;
    if (state == 0x100) {                                       /* Reset the pattern */
        state = 1;
    }
    
    value = 0xFFF0;                                             /* Set unused bits to keep as input pins for button reading */
    value |= (state & 0x81) ? 0 : (1 << 0);
    value |= (state & 0x42) ? 0 : (1 << 1);
    value |= (state & 0x24) ? 0 : (1 << 2);
    value |= (state & 0x18) ? 0 : (1 << 3);
    
    PCA9673_Write(&pca9673, value);
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
    static BUTTON button = BUTTON_NONE;
    

    LED_Init();                                                 /* Initialize for driving the on-board RGB LEDs */

    status = TIMER_Create(&timer1,                              /* Create a timer to blink LEDs */
                          "LED",                                /* Timer name */
                          APP_Timer1,                           /* Timer expiration function */
                          NULL,                                 /* Optional argument */
                          200,                                  /* Timer interval (in kernel ticks) */
                          OPT_START | OPT_AUTORESET);           /* Start and repeat */
    
    assert(status == SUCCESS);
    
    
    status = I2C_Open(&i2c,                                     /* Open and initialize the I2C port */
                      0,                                        /* The port number */
                      400000);                                  /* The clock frequency */
    
    assert(status == SUCCESS);
    
    status = PCA9673_Open(&pca9673,                             /* Open and intialize the PCA9673 driver */
                          &i2c,                                 /* A pointer to the I2C port used by the driver */
                          0x48);                                /* The device address on the I2C bus */
    
    assert(status == SUCCESS);

    for (;;) {
        
        button = BUTTON_Read(&pca9673);                         /* Read the on-board user buttons */
        
        LED_Set(LED_RED, (button & BUTTON_SW3));                /* Illuminate the red LED if SW3 is pressed */
        LED_Set(LED_GREEN, (button & BUTTON_SW5));              /* Illuminate the green LED if SW5 is pressed */
        LED_Set(LED_BLUE, (button & BUTTON_SW6));               /* Illuminate the blue LED if SW6 is pressed */
        
        THREAD_Sleep(50);
    }
}
