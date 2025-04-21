/*******************************************************************************************************************************************

    DZX | LPC1857-MCB | USB-MSC-SD                                                                                        VERSION 18.2.1
    ------------------------------------------------------------------------------------------------------------------------------------

    This is an application that demonstrates a USB device that implements the mass storage class. The device provides the USB host
    acccess to the on-board SD/MMC card.

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
#include "Kernel/kernel_timer.h"
#include "FS/Disk/disk_mci.h"
#include "USB/Device/usbd_msc.h"
#include "board_led.h"
#include "mcu_pin.h"
#include <assert.h>


/*******************************************************************************************************************************************
   CONSTANT DATA
*******************************************************************************************************************************************/
/***************************************************************************************************************************************//**

    Represents information provided over the MSC interface.

*******************************************************************************************************************************************/
const BYTE SCSIInfo[] = {
	0x00,	                                            /* Direct-access block device */
	0x80,	                                            /* Removable medium */
	0x00,	                                            /* ISO, ECMA, and ANSI-approved versions */
	0x01,	                                            /* AEC, TrmIOP, and Response data format */

	0x1F,	                                            /* Additional length */
	0x00,
	0x00,
	0x00,

	'D', 'Z', 'X', ' ', ' ', ' ', ' ', ' ',             /* Vendor identification (ASCII) (bytes 8-15) */

	'S', 'D', ' ', 'D', 'I', 'S', 'K', ' ',             /* Product identification (ASCII) (bytes 16-31) */
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
	
	'1', '.', '0', ' '                                  /* Product revision level (bytes 32-35) */
};

/*******************************************************************************************************************************************
    PRIVATE VARIABLES
*******************************************************************************************************************************************/
static USBDDEVICE usb;                          /* Allocate the USB device for communications */
static MSCDINTERFACE msc;                       /* USB device mass storage class interface */
static MSCDLUN lun;                             /* Allocate a logical unit to assign a disk to the mass storage interface */
static MCIDISK disk;                            /* Allocate a multimedia card interface (MCI) driver */

/*******************************************************************************************************************************************
    PRIVATE FUNCTIONS
*******************************************************************************************************************************************/
static void APP_Main(void* arg);
static void APP_Timer1(TIMER* timer, void* arg);

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
    STATUS status;
    static TIMER timer;
    
    
    
    LED_Init();                                                 /* Initialize to drive the on-board LEDs */
    
    
    PIN_SetFunction(PC_00, 7);                                  /* Assign PC.10 to the SD_CLK function */
    PIN_SetInputBuffer(PC_00, TRUE);
    PIN_SetFastSlewRate(PC_00, TRUE);
    PIN_SetGlitchFilter(PC_00, FALSE);
    
    PIN_SetFunction(PC_10, 7);                                  /* Assign PC.10 to the SD_CMD function */
    PIN_SetInputBuffer(PC_10, TRUE);
    PIN_SetFastSlewRate(PC_10, TRUE);
    PIN_SetGlitchFilter(PC_10, FALSE);
    
    PIN_SetFunction(PC_08, 7);                                  /* Assign PC.8 to the SD_CD function */
    PIN_SetInputBuffer(PC_08, TRUE);
    
    PIN_SetFunction(PC_04, 7);                                  /* Assign PC.4 to the SD_DAT0 function */
    PIN_SetInputBuffer(PC_04, TRUE);
    PIN_SetFastSlewRate(PC_04, TRUE);
    PIN_SetGlitchFilter(PC_04, FALSE);
    
    PIN_SetFunction(PC_05, 7);                                  /* Assign PC.5 to the SD_DAT1 function */
    PIN_SetInputBuffer(PC_05, TRUE);
    PIN_SetFastSlewRate(PC_05, TRUE);
    PIN_SetGlitchFilter(PC_05, FALSE);
    
    PIN_SetFunction(PC_06, 7);                                  /* Assign PC.6 to the SD_DAT2 function */
    PIN_SetInputBuffer(PC_06, TRUE);
    PIN_SetFastSlewRate(PC_06, TRUE);
    PIN_SetGlitchFilter(PC_06, FALSE);
    
    PIN_SetFunction(PC_07, 7);                                  /* Assign PC.7 to the SD_DAT3 function */
    PIN_SetInputBuffer(PC_07, TRUE);
    PIN_SetFastSlewRate(PC_07, TRUE);
    PIN_SetGlitchFilter(PC_07, FALSE);
    
    
    
    
    status = TIMER_Create(&timer,                               /* Create a timer for blinking LED */
                          "LED",                                /* Name */
                          APP_Timer1,                           /* Callback expiration function */
                          NULL,                                 /* Optional argument */
                          10,                                   /* Interval, in kernel ticks */
                          OPT_START | OPT_AUTORESET);           /* Start the timer and auto-reset on expiration */
    
    assert(status == SUCCESS);
    
    
    status = MCIDISK_Create(&disk, 0);                          /* Create and initialize the SD/MMC interface driver */
    assert(status == SUCCESS);
    
    
    
    status = USBD_Create(&usb,                                  /* Create and initialize the USB device stack instance */
                         0,                                     /* Port number */
                         0x0000,                                /* Vendor ID */ 
                         0x0011);                               /* Product ID */
    
    assert(status == SUCCESS);
    
    status = USBD_SetDeviceName(&usb,                           /* Assign name strings for the device */
                                "DZX",                          /* Manufacturer Name */
                                "SD USB Disk",                  /* Product Name */
                                "0123456789ABC");               /* Serial Number */
    
    assert(status == SUCCESS);
    
    status = MSCD_CreateInterface(&usb,                         /* Create and initialize the USB mass storage interface */ 
                                  &msc,                         /* Pointer to the interface instance to be initialized */
                                  1);                           /* The endpoint number used by the mass storage interface */
    assert(status == SUCCESS);
    
    status = MSCD_AddLUN(&msc,                                  /* Assign the disk driver to the mass storage interface */
                         &lun,                                  /* Pointer to the logical unit */
                         &disk.base,                            /* Pointer to the disk driver */
                         SCSIInfo,                              /* Pointer to the SCSI information to be sent to the host */
                         sizeof(SCSIInfo));                     /* Size of the SCSI information */
    
    assert(status == SUCCESS);
    
    status = USBD_Open(&usb);                                   /* Start and allow USB communications */
    assert(status == SUCCESS);

    
    for (;;) {
        
        if (DISK_MediaPresent(&disk.base)) {                    /* Provide automatic mounting based upon SD card presence */
            
            if (!DISK_Mounted(&disk.base)) {                    /* Mount the card if it's present and not mounted */
                DISK_Mount(&disk.base);
            }
        } else {
            
            if (DISK_Mounted(&disk.base)) {                     /* Unmount the card if it's not present and mounted */
                DISK_Unmount(&disk.base);
            }
        }
    
        THREAD_Sleep(100);
    }
}

/***************************************************************************************************************************************//**

    A handler function for a timer that blinks the on-board LEDs.

    @return     None.

*******************************************************************************************************************************************/
static void APP_Timer1(TIMER* timer, void* arg)
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
    
    if (DISK_Mounted(&disk.base)) {                             /* Blink the LEDs based upon the mount status of the SD card */
        
        LED_Set(LED_0, state & 0x0000FF);                       /* Mounted, blink all in a pattern */
        LED_Set(LED_1, state & 0x000100);
        LED_Set(LED_2, state & 0x000200);
        LED_Set(LED_3, state & 0x000400);
        LED_Set(LED_4, state & 0x000800);
        LED_Set(LED_5, state & 0x001000);
        LED_Set(LED_6, state & 0x002000);
        LED_Set(LED_7, state & 0x3FC000);
        
    } else {
        
        LED_Set(LED_0, state & 0x0000FF);                       /* Not mounted, just blink single LED */
        LED_Set(LED_1, 0);
        LED_Set(LED_2, 0);
        LED_Set(LED_3, 0);
        LED_Set(LED_4, 0);
        LED_Set(LED_5, 0);
        LED_Set(LED_6, 0);
        LED_Set(LED_7, 0);
    }
}
