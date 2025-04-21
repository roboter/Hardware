/*******************************************************************************************************************************************

    DZX | LPC4350-HITEX | UART ECHO                                                                                       VERSION 18.2.1
    ------------------------------------------------------------------------------------------------------------------------------------

    This is an application that will echo data received over the on-board UART.

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
#include "mcu_uart.h"
#include "mcu_pin.h"
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
    static UART uart;
    ALIGNED(4) static BYTE buf[32];
    STATUS status;
    UINT32 n;
    

    LED_Init();                                         /* Initialize for driving the on-board LEDs */
    
    PIN_SetFunction(PF_10, 1);                          /* Assign PF.10 to the U0_TXD function */
    PIN_SetFunction(PF_11, 1);                          /* Assign PF.11 to the U0_RXD function */
    PIN_SetInputBuffer(PF_11, TRUE);

    status = TIMER_Create(&timer1,                      /* Create a timer to blink LEDs */
                          "LED",                        /* Timer name */
                          APP_Timer1,                   /* Timer expiration function */
                          NULL,                         /* Optional argument */
                          200,                          /* Timer interval (in kernel ticks) */
                          OPT_START | OPT_AUTORESET);   /* Start and repeat */
    
    assert(status == SUCCESS);
    
    
    status = UART_Open(&uart,                           /* Open the on-board UART */
                       0,                               /* Port number '0' */
                       115200,                          /* Baud rate */
                       8,                               /* Data bits */
                       STOPBITS_ONE,                    /* Stop bits */
                       PARITY_NONE,                     /* Parity */
                       HANDSHAKE_NONE);                 /* Flow control */
    
    assert(status == SUCCESS);
    
    
    for (;;) {
        
        UART_Read(&uart,                                /* Receive data from the UART */
                  buf,                                  /* Pointer to buffer to receive the data */
                  sizeof(buf),                          /* Max number of bytes to receive */
                  &n,                                   /* Pointer to get how many bytes have been received */
                  20);                                  /* Max time, in kernel ticks, to wait for data to be received */
        
        if (n > 0) {                                    /* Any data received? */
            
            UART_Write(&uart,                           /* Transmit the recieved data */
                       buf,                             /* Pointer to the data to be transmitted */
                       n,                               /* Number of bytes to be transmitted */
                       NULL,                            /* Variable to receive actual number of bytes transmitted; NULL as don't care. */
                       INFINITE);                       /* Max time, in kernel ticks, to wait for data to be transmitted */
            
        }
    }
}
