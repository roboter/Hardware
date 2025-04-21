/*******************************************************************************************************************************************

    DZX | LPC4350-HITEX | DATALINK                                                                                        VERSION 18.2.1
    ------------------------------------------------------------------------------------------------------------------------------------

    This is an application that implements a demonstration data link on the NXP LPC4350 Hitex evaluation board. The application provides 
    the link over native USB and over UART 0.

    The data link definition is from demolink.xml that is found within the Microsoft.NET and Development Tools download from 
    <https://dzxdesigns.com>.

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
#include "Kernel/kernel_stat.h"
#include "board_led.h"
#include "mcu_pin.h"
#include "DataLink/datalink_uart.h"
#include "DataLink/datalink_usb.h"
#include "datalink_app.h"
#include <stdio.h>
#include <assert.h>

/*******************************************************************************************************************************************
    LOCAL CONFIGURATION
*******************************************************************************************************************************************/
/*******************************************************************************************************************************************

    SCRATCH PAD SIZE                The size, in bytes, of the scratch pad memory that is exposed over the data link to allow reading
                                    and writing from a connected host.

*******************************************************************************************************************************************/
#define CFG_SCRATCHPADSIZE          1024

/*******************************************************************************************************************************************
    PRIVATE VARAIBLES
*******************************************************************************************************************************************/
ALIGNED(4) static BYTE scratch[CFG_SCRATCHPADSIZE];  /* Scratch pad memory exposed over the data links */
static TIMER timer1;                /* A timer for blinking LEDs */
static TIMER timer2;                /* A timer for sending device status stream via USB */
static TIMER timer3;                /* A timer for sending device status stream via UART */
static USBLINK usblink;             /* A data link for transferring messages over USB */
static UARTLINK uartlink;           /* A data link for transferring messages over a UART */

/*******************************************************************************************************************************************
    PRIVATE FUNCTIONS
*******************************************************************************************************************************************/
static void APP_Main(void* arg);

/***************************************************************************************************************************************//**

    A hook function that is called by the kernel immediately upon boot-up (before any memory initialization).
    @return     None.

*******************************************************************************************************************************************/
void HOOK_Boot(void)
{

}

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
    
    if (TIMER_IsRunning(&timer2)) {                             /* Timer running indicates whether streaming device status */
        
        LED_Set(LED_RED, 0);                                    /* Blink green LED while streaming device status */
        LED_Set(LED_GREEN, state);
    } else {
        
        LED_Set(LED_RED, state);                                /* Blink red LED while streaming is disabled */
        LED_Set(LED_GREEN, 0);
    }
}

/***************************************************************************************************************************************//**

    A timer callback handler that sends out the device status message over the USB data link.
    @return     None.

*******************************************************************************************************************************************/
static void APP_Timer2(TIMER* timer, void* arg)
{
    DEVICESTATUSARGS args;
    
    
    args.kernelTicks = KERNEL_Ticks();
    args.kernelUtilization = KERNEL_Utilization();
    
    
    DATALINK_DeviceStatus(&usblink.base, &args);                /* Send out the USB link */
}

/***************************************************************************************************************************************//**

    A timer callback handler that sends out the device status message over the UART data link.
    @return     None.

*******************************************************************************************************************************************/
static void APP_Timer3(TIMER* timer, void* arg)
{
    DEVICESTATUSARGS args;
    
    
    args.kernelTicks = KERNEL_Ticks();
    args.kernelUtilization = KERNEL_Utilization();
    
    
    DATALINK_DeviceStatus(&uartlink.base, &args);               /* Send out the UART link */
}

/***************************************************************************************************************************************//**

    The process function for the main application thread.

    @param[in]  arg         An optional argument. Not used here.

    @return     None.

*******************************************************************************************************************************************/
static void APP_Main(void* arg)
{
    STATUS status;
    

    
    LED_Init();                                         /* Initialize for driving the on-board LEDs */
    
    PIN_SetFunction(PF_10, 1);                          /* Assign PF.10 to the U0_TXD function */
    PIN_SetFunction(PF_11, 1);                          /* Assign PF.11 to the U0_RXD function */
    PIN_SetInputBuffer(PF_11, TRUE);
    
    
    status = UARTLINK_Create(&uartlink,                 /* Create and initialize an instance of the data link over a UART */
                             DATALINK_CreateApp);       /* Function to initialize the application specific data link */
                             
    assert(status == SUCCESS);
    
    status = UARTLINK_Open(&uartlink,                   /* Open and start communications on the UART data link */
                           0,                           /* UART port number */
                           115200);                     /* UART baud rate */
    
    assert(status == SUCCESS);
    
    
    
    
    status = USBLINK_Create(&usblink,                   /* Create and initialize an instance of the data link over USB */
                            DATALINK_CreateApp,         /* Function to initialize the application specific data link */
                            0,                          /* Port number */
                            0x0000,                     /* USB vendor ID */
                            0x0010,                     /* USB product ID */
                            1);                         /* USB endpoint number for message transfers */
    
    assert(status == SUCCESS);
    
    status = USBLINK_Open(&usblink);                    /* Open and start communications on the USB data link */
    assert(status == SUCCESS);
    
    
    
    
    status = TIMER_Create(&timer1, 						/* Create a timer to blink LEDs */
       	   				  "LED",					    /* Timer name */
						  APP_Timer1,					/* Timer expiration function */
       					  NULL,							/* Optional argument */
       					  200,							/* Timer interval (in kernel ticks) */
       					  OPT_START | OPT_AUTORESET);	/* Start and repeat */
    
    assert(status == SUCCESS);
    
    status = TIMER_Create(&timer2, 						/* Create a timer to send stream updates */
       	   				  "USB Stream",	            	/* Timer name */
						  APP_Timer2,					/* Timer expiration function */
       					  NULL,							/* Optional argument */
       					  67,							/* Timer interval (in kernel ticks) */
       					  OPT_START | OPT_AUTORESET);	/* Start and repeat */
    
    assert(status == SUCCESS);
    
    status = TIMER_Create(&timer3, 						/* Create a timer to send stream updates */
       	   				  "UART Stream",		    	/* Timer name */
						  APP_Timer3,					/* Timer expiration function */
       					  NULL,							/* Optional argument */
       					  67,							/* Timer interval (in kernel ticks) */
       					  OPT_START | OPT_AUTORESET);	/* Start and repeat */
    
    assert(status == SUCCESS);
    
    
    
    
    for (;;) {
        
        THREAD_Sleep(100);
    }
}

/***************************************************************************************************************************************//**

    A handler function called when the 'Enable Status Stream' message has been received.

    @param[in]  link        A pointer to the target data link.
    @param[in]  args        A pointer the arguments for the message.

    @return     None.

*******************************************************************************************************************************************/
void DATALINK_EnableStatusStream_Handler(DATALINK* link, const ENABLESTATUSSTREAMARGS* args)
{
    if (args->enabled) {
        
        TIMER_Start(&timer2);
        TIMER_Start(&timer3);
        
    } else {
        
        TIMER_Stop(&timer2);
        TIMER_Stop(&timer3);
    }
}

/***************************************************************************************************************************************//**

    A handler function called when the 'Read Memory' message has been received.

    @param[in]  link        A pointer to the target data link.
    @param[in]  request     A pointer the request parameters for the message.
    @param[in]  response    A pointer to the response parameters for the message.

    @return     None.

*******************************************************************************************************************************************/
void DATALINK_ReadMemory_Handler(DATALINK* link, const REQUEST_READMEMORY* request, RESPONSE_READMEMORY* response)
{
    if (request->length > 256) {
        response->data.count = 0;                               /* Invalid read length, return no data */
        response->result = 1;                                   /* Indicate NAK */     
        return;
    }
    
    if (request->address >= CFG_SCRATCHPADSIZE ||
        (request->address + request->length > CFG_SCRATCHPADSIZE)) {

        response->data.count = 0;                               /* Invalid read address + length, return no data */
        response->result = 2;                                   /* Indicate NAK */
        return;
    }
    
    
    memcpy(response->data.values,                               /* Read the requested data from the scatch pad to the response data array */
           (BYTE*)scratch + request->address, 
           request->length);
    
    response->data.count = request->length;                     /* Assign the amount that has been read */
    response->result = 0;                                       /* Indicate ACK */
}

/***************************************************************************************************************************************//**

    A handler function called when the 'Write Memory' message has been received.

    @param[in]  link        A pointer to the target data link.
    @param[in]  request     A pointer the request parameters for the message.
    @param[in]  response    A pointer to the response parameters for the message.

    @return     None.

*******************************************************************************************************************************************/
void DATALINK_WriteMemory_Handler(DATALINK* link, const REQUEST_WRITEMEMORY* request, RESPONSE_WRITEMEMORY* response)
{
    if (request->address >= CFG_SCRATCHPADSIZE ||
        (request->address + request->data.count > CFG_SCRATCHPADSIZE)) {
            
        response->result = 1;                                   /* Invalid write address + count, indicate NAK */
        return;
    }
    
    memcpy((BYTE*)scratch + request->address,                   /* Write the specified data to the scratch pad memory */
           request->data.values,
           request->data.count);
    
    response->result = 0;                                       /* Indicate ACK */
}
