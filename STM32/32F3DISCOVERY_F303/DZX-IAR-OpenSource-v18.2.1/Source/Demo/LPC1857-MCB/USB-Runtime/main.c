/*******************************************************************************************************************************************

    DZX | LPC1857-MCB | USB-RUNTIME                                                                                       VERSION 18.2.1
    ------------------------------------------------------------------------------------------------------------------------------------

    This is a demo application that serves as a runtime application that is launched and updated by a secondary USB bootloader that 
    implements the Device Firmware Update (DFU) interface.

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
#include "Bootloader/boot_runtime.h"
#include "Kernel/kernel_timer.h"
#include "USB/Device/usbd_dfu.h"
#include "board_led.h"
#include <assert.h>

/*******************************************************************************************************************************************
   LOCAL CONFIGURATION
*******************************************************************************************************************************************/

/*******************************************************************************************************************************************
    PRIVATE VARIABLES
*******************************************************************************************************************************************/
static USBDDEVICE usbd;                         /* Allocate the USB device for communications */
static DFUDINTERFACE dfu;                       /* USB device firmware update interface */
static USBDENDPOINT rxendpt;                    /* An endpoint for receiving data for the generic USB communications */
static USBDENDPOINT txendpt;                    /* An endpoint for transmitting data for the generic USB communications */
static THREAD usbThread;                        /* A thread for generic USB communications */

/*******************************************************************************************************************************************
    PRIVATE FUNCTIONS
*******************************************************************************************************************************************/
static void APP_Main(void* arg);
static void APP_InitUSB(void);
static void APP_ProcUSB(void* arg);
static void CALLBACK_Timer(TIMER* timer, void* arg);

/***************************************************************************************************************************************//**

    A hook function that is called by the kernel immediately upon boot-up (before any memory initialization).
    @return     None.

*******************************************************************************************************************************************/
void HOOK_Boot(void)
{
    
}

/***************************************************************************************************************************************//**

    The main entry function for the application.

    @return     None.

*******************************************************************************************************************************************/
int main(void)
{
    KERNEL_Execute(APP_Main, NULL);                             /* Execute the kernel */
    return 0;
}

/***************************************************************************************************************************************//**

    The application function.

    @param[in]  arg         An optional argument. Not used here.

    @return     None.

*******************************************************************************************************************************************/
static void APP_Main(void* arg)
{
    ALIGNED(4) static BYTE stack[384];
    static TIMER timer;
    STATUS status;
    UINT32 signals;
    
    
    LED_Init();                                                 /* Initialize to drive the on-board LEDs */
    
    TIMER_Create(&timer,                                        /* Create a timer for blinking LED */
                 "LED",                                         /* Name */
                 CALLBACK_Timer,                                /* Callback expiration function */
                 NULL,                                          /* Optional argument */
                 10,                                            /* Interval, in kernel ticks */
                 OPT_START | OPT_AUTORESET);                    /* Start the timer and auto-reset on expiration */
    
    APP_InitUSB();                                              /* Initialize the USB interface */
    
    status = THREAD_Create(&usbThread,                          /* Create a thread for generic USB communications */
                           "USB Comms",
                           stack, 
                           sizeof(stack), 
                           PRIO_NORMAL);
    
    assert(status == SUCCESS);
    
    status = THREAD_Start(&usbThread,                           /* Start the thread for generic USB communications */
                          APP_ProcUSB, 
                          NULL);  
    
    assert(status == SUCCESS);
    

    for (;;) {
        
        status = DFUD_Wait(&dfu, &signals, INFINITE);           /* Wait for a signal (event) from the DFU interface */           
        if (status == SUCCESS) {
            
            if (signals & SIGNAL_DFUDDETACH) {                  /* Received a DFU DETACH request? */
                USBD_Close(&usbd);                              /* Yes, close down the port to force bus reset */
                BOOT_ExecuteBootloader();                       /* Request to switch to the bootloader application */
            }
        }
    }
}

/***************************************************************************************************************************************//**

    A timer expiration callback function. Used to blink the board's LED.

    @return     None.

*******************************************************************************************************************************************/
static void CALLBACK_Timer(TIMER* timer, void* arg)
{
    static UINT32 state = 1;
    static BYTE dir = 0;
    
    
    if (dir) {
        state >>= 1;
    } else {
        state <<= 1;
    }
    
    if (state & 0x200001) {
        dir ^= 1;
    } 

    LED_Set(LED_0, state & 0x0000FF);
    LED_Set(LED_1, state & 0x000100);
    LED_Set(LED_2, state & 0x000200);
    LED_Set(LED_3, state & 0x000400);
    LED_Set(LED_4, state & 0x000800);
    LED_Set(LED_5, state & 0x001000);
    LED_Set(LED_6, state & 0x002000);
    LED_Set(LED_7, state & 0x3FC000);
}

/***************************************************************************************************************************************//**

    A thread process for the generic USB communications.
    
    @param[in]  arg         A pointer to an optional argument that was provided when the thread was started (not used here).

    @return     None.

*******************************************************************************************************************************************/
static void APP_ProcUSB(void* arg)
{
    ALIGNED(4) static BYTE buffer[1024];
    STATUS status;
    UINT32 len;
    
    
    for (;;) {
        
        /* Loop forever and echo all data that is received */
        
        status = USBD_Read(&rxendpt,                            /* Wait to receive any data */
                           buffer, 
                           sizeof(buffer), 
                           &len, 
                           INFINITE);
        
        if (status == SUCCESS) {
            status = USBD_Write(&txendpt, buffer, len, NULL, 1000);     /* Echo the received data */
        }
    }
}
 
/***************************************************************************************************************************************//**

    Initializes the USB device interface.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The USB device interface has been initialized.

*******************************************************************************************************************************************/
static void APP_InitUSB(void)
{
    STATUS status;
    
    
    /* Create and initialize the USB device stack */
    
    status = USBD_Create(&usbd,
                         0,                                     /* Port number */
                         0x0000,                                /* Vendor ID */ 
                         0x0010);                               /* Product ID */
    
    assert(status == SUCCESS);
    
    status = USBD_SetDeviceName(&usbd,                          /* Assign name strings for the device */
                                "DZX",                          /* Manufacturer Name */
                                "LPC1857 DEMO",                 /* Product Name */
                                NULL);                          /* Serial Number */
    
    assert(status == SUCCESS);
    
    /* Create and initialize a Device Firmware Update interface */
   
    status = DFUD_CreateInterface(&usbd,                        /* A pointer to the usb device stack */
                                  &dfu,                         /* A pointer to the interface to be initialized */
                                  MODE_RUNTIME,                 /* The mode of the application (runtime application mode) */
                                  NULL,
                                  0);              
    assert(status == SUCCESS);
    
    
    /* Create an endpoint for receiving data */
    status = USBD_CreateEndpoint(&dfu.base,
                                 &rxendpt,
                                 USBTRANSFERBULK,
                                 0x01,
                                 64,
                                 512,
                                 1,
                                 OPT_SHORTPKT);
    assert(status == SUCCESS);

    
    /* Create an endpoint for transmitting data */
    status = USBD_CreateEndpoint(&dfu.base,
                                 &txendpt,
                                 USBTRANSFERBULK,
                                 0x81,
                                 64,
                                 512,
                                 1,
                                 OPT_SHORTPKT);
    assert(status == SUCCESS);

    status = USBD_SetMicrosoftDescriptorSupport(&usbd, TRUE);   /* Enable automatic loading of WinUSB driver on Microsoft Windows */
    assert(status == SUCCESS);
    
    status = USBD_Open(&usbd);                                  /* Open the port and start communications */
    assert(status == SUCCESS);
}
