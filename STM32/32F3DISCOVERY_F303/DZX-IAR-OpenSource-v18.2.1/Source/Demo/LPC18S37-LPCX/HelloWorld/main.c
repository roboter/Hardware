/*******************************************************************************************************************************************

    DZX | LPC18S37-LPCX | HELLOWORLD                                                                                      VERSION 18.2.1
    ------------------------------------------------------------------------------------------------------------------------------------

    This is a basic application that demonstrates using the SDK library.

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
#include <stdio.h>
#include <assert.h>

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
	static BOOLEAN state = FALSE;


	state = !state;
	LED_Set(LED_GREEN, state);                                  /* Blink the green LED */
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
    
    
    LED_Init();                                                 /* Initialize for driving the on-board LEDs */
    
    status = TIMER_Create(&timer1,                              /* Create a timer to blink LEDs */
                          "LED",                                /* Timer name */
                          APP_Timer1,                           /* Timer expiration function */
                          NULL,                                 /* Optional argument */
                          200,                                  /* Timer interval (in kernel ticks) */
                          OPT_START | OPT_AUTORESET);           /* Start and repeat */
    
    assert(status == SUCCESS);
    
    
    for (;;) {
        
        THREAD_Sleep(100);
    }
}
