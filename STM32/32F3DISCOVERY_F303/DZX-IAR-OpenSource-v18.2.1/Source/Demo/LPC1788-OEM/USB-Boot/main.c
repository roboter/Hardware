/*******************************************************************************************************************************************

    DZX | LPC1788-OEM | USB-BOOT                                                                                          VERSION 18.2.1
    ------------------------------------------------------------------------------------------------------------------------------------

    This is a demo application that serves as a USB bootloader that implements the Device Firmware Update (DFU) interface.

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
#include "mcu_flash.h"
#include "board_led.h"
#include "board_button.h"

#include "Crypto/aes.h"
#include "Bootloader/boot.h"
#include "USB/Device/usbd.h"
#include "USB/Device/usbd_dfu.h"

#include <string.h>
#include <assert.h>

/*******************************************************************************************************************************************
    LOCAL CONFIGURATION
*******************************************************************************************************************************************/
#define CFG_ENCRYPTION                      FALSE
#define CFG_KEYSIZE                         256

/*******************************************************************************************************************************************
    PRIVATE VARIABLES
*******************************************************************************************************************************************/
static USBDDEVICE usbd;                                     /* Allocate the USB device for communications */
static DFUDINTERFACE dfu;                                   /* Allocate the DFU interface */

#if (CFG_ENCRYPTION)
static AES aes;

const BYTE iv[] = {                                         /* AES Initialization Vector */ 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0 
};

const BYTE Key[] = {                                        /* AES Key (AES-256 with passphrase "password") */
    0xC7, 0xED, 0x65, 0x53, 0x63, 0x04, 0x1D, 0xC8, 
    0x68, 0xBF, 0x73, 0xAB, 0x3B, 0x4A, 0xC6, 0x86, 
    0x9A, 0xB1, 0xFF, 0x67, 0x51, 0xDD, 0x5D, 0x74, 
    0x88, 0x8D, 0xB1, 0x52, 0xC4, 0x74, 0xC7, 0x6F 
};
#endif

/*******************************************************************************************************************************************
    PRIVATE FUNCTIONS
*******************************************************************************************************************************************/
static void APP_Main(void* arg);
static void APP_TryExecuteRuntime(void);
static void APP_InitUSB(void);
static void APP_Download(DFUDBLOCK* blk);
static void APP_Upload(DFUDBLOCK* blk);
static void CALLBACK_Timer(TIMER* timer, void* arg);

/***************************************************************************************************************************************//**

    Attempts to execute a runtime firmware application unless there is a valid signature in RAM requesting the bootloader, or if button
    SW4 is pressed, or if the first 32-bit word of the firmware image is blank.

    @return     None.
    @remark     Only returns if the runtime firmware was not executed.

*******************************************************************************************************************************************/
static void APP_TryExecuteRuntime(void)
{
    if (BTN_Joystick() & JOYSTICK_CENTER) {                     /* Only launch runtime app if the joystick is not pressed */
        return;
    }
        
    if (BOOT_IsSignatureValid()) {                              /* Is there a valid signature requesting the bootloader? */
        return;                                                 /* Yes, don't switch, stay in bootloader */
    }
    
    if ((*(UINT32*)CFG_RUNTIMEADDRESS) == 0xFFFFFFFF) {         /* Is the start of the runtime firmware blank? */
        return;                                                 /* Yes, don't switch, stay in bootloader */
    }
    
    KERNEL_ExecuteApp(CFG_RUNTIMEADDRESS);                      /* Execute the runtime application */
}

/***************************************************************************************************************************************//**

    The main function for the application. Attempts to execute the runtime firmware and if not, launches the bootloader application.

    @return     None.

*******************************************************************************************************************************************/
int main(void)
{
    APP_TryExecuteRuntime();                                    /* Attempt to execute the runtime app */
    KERNEL_Execute(APP_Main, NULL);                             /* Execute the bootloader */
    return 0;
}

/***************************************************************************************************************************************//**

    A timer expiration callback function. Used to blink the board's LED.

    @return     None.

*******************************************************************************************************************************************/
static void CALLBACK_Timer(TIMER* timer, void* arg)
{
    static BOOLEAN state = FALSE;
    
    state = !state;
    LED_Set(LED_GREEN, state);
}

/***************************************************************************************************************************************//**

    Downloads the specified block of data to the flash memory.

    @param[in]  blk         A pointer to the block of data to be programmed to flash memory.

    @return     None.

*******************************************************************************************************************************************/
static void APP_Download(DFUDBLOCK* blk)
{
    UINT32 address;
    UINT32 k;
    
    
    /* Decrypt the received data if configured */
    
#if (CFG_ENCRYPTION)
    if (blk->lba == 0) {                                                /* Is this the first encrypted block that has been received? */
        AES_Init(&aes, CFG_KEYSIZE, Key, iv);                           /* Yes, initialize the cipher with the key and iv */
    }
                    
    AES_Decrypt(&aes, blk->data, blk->len);                             /* Decrypt the received data, in place */
#endif

    
    address = CFG_RUNTIMEADDRESS + (blk->lba * CFG_DFUDTRANSFERSIZE);   /* Calculate the destination address for the data */
    
    if (FLASH_IsSectorStart(address)) {                                 /* Is the data targeted at a new sector? */
        FLASH_EraseSector(FLASH_GetSector(address));                    /* Erase the sector that is about to be programmed */
    }

    if (blk->len < CFG_DFUDTRANSFERSIZE) {                              /* Is only a partial block being programmed? */
        
        for (k = blk->len; k < CFG_DFUDTRANSFERSIZE; k++) {             /* Fill the remainder of the block as blank */
            ((BYTE*)blk->data)[k] = 0xFF;
        }
        
        blk->len = CFG_DFUDTRANSFERSIZE;                                /* Program an entire block */
    }
    
    FLASH_Write(address, blk->data, blk->len);                          /* Program the data to flash memory */
}

/***************************************************************************************************************************************//**

    Uploads program memory into the specified block of data.

    @param[in]  blk         A pointer to the block of data to receive the program memory contents.

    @return     None.

*******************************************************************************************************************************************/
static void APP_Upload(DFUDBLOCK* blk)
{
    memcpy(blk->data,                                                   /* Copy the program memory into the block */
           (UINT32*)(CFG_RUNTIMEADDRESS + (blk->lba * CFG_DFUDTRANSFERSIZE)), 
           blk->len);     
    
    
    /* Encrypt the contents prior to sending if configured */
    
#if (CFG_ENCRYPTION)
    if (blk->lba == 0) {                                                /* Is this the first block of encrypted data? */
        AES_Init(&aes, CFG_KEYSIZE, Key, iv);                           /* Yes, initialize the cipher with the key and iv */
    }
                                
    AES_Encrypt(&aes, blk->data, blk->len);                             /* Encrypt the data in-place */
#endif
}

/***************************************************************************************************************************************//**

    The process function for the main thread.

    For this application (bootloader), will only get here if the runtime firmware was not executed.

    @param[in]  arg         An optional argument. Not used here.

    @return     None.

*******************************************************************************************************************************************/
static void APP_Main(void* arg)
{
    static TIMER timer;
    STATUS status;
    UINT32 signals;
    DFUDBLOCK* blk;
    

    
    LED_Init();                                                 /* Initialize the on-board LEDs */
    
    PIN_SetFunction(P0_31, 1);                                  /* Assign P0.31 to the USB_D+2 function */
    PIN_SetFunction(P0_14, 3);                                  /* Assign P0.14 to the USB_CONNECT2 function */
    
    
    TIMER_Create(&timer,                                        /* Create a timer for blinking LED */
                 "LED",                                         /* Name */
                 CALLBACK_Timer,                                /* Callback expiration function */
                 NULL,                                          /* Optional argument */
                 100,                                           /* Interval, in kernel ticks */
                 OPT_START | OPT_AUTORESET);                    /* Start the timer and auto-reset on expiration */
    
    
    APP_InitUSB();                                              /* Initialize the USB interface */
    
    
    for (;;) {
        
        status = DFUD_Wait(&dfu, &signals, INFINITE);               /* Wait for a DFU event */
        
        if (status == SUCCESS) {
            
            if (signals & SIGNAL_DFUDDOWNLOAD) {                    /* Download block completed? */
                
                blk = DFUD_GetDataBlock(&dfu);                      /* Get the data that has been received from the host */
                if (blk) {        
                    APP_Download(blk);                              /* Download the block to flash memory */
                    DFUD_DownloadComplete(&dfu);                    /* Signal that the download operation is complete */
                }
            }
            
            if (signals & SIGNAL_DFUDMANIFEST) {                    /* Manifest firmware stage? */
                DFUD_ManifestComplete(&dfu);                        /* Signal manifest stage complete */
            }
            
            if (signals & SIGNAL_DFUDDETACH) {
                
                USBD_Close(&usbd);                                  /* Close and disconnect the USB connection (host will see this) */
                BOOT_ExecuteRuntime();                              /* Attempt to execute the runtime application */
                
                DFUD_SetError(&dfu, DFUERROR_FIRMWARE);             /* Failed to switch to runtime application, go to error state */
            }
            
            if (signals & SIGNAL_DFUDUPLOAD) {
                blk = DFUD_GetDataBlock(&dfu);                      /* Get the data that has been received from the host */
                if (blk) {
                    APP_Upload(blk);
                    DFUD_UploadComplete(&dfu);
                }
            }
        }                 
    }
}

/***************************************************************************************************************************************//**

    Initializes the USB device interface.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The USB device interface has been initialized.
     ---                    | An underlying error has occurred.

*******************************************************************************************************************************************/
static void APP_InitUSB(void)
{
    ALIGNED(4) static BYTE dfubuf[CFG_DFUDTRANSFERSIZE];
    STATUS status;

    
    
    status = USBD_Create(&usbd,                                 /* Create and initialize the USB device stack */
                         0,                                     /* Port number */
                         0x0000,                                /* Vendor ID */
                         0x0010);                               /* Product ID */
    
    assert(status == SUCCESS);
    
    
    status = USBD_SetDeviceName(&usbd,                          /* Assign name strings for the device */
                                "DZX",                          /* Manufacturer Name */
                                "LPC1788 BOOTLOADER",           /* Product Name */
                                NULL);                          /* Serial Number */
    
    assert(status == SUCCESS);
    
    
    
    /* Create and initialize a Device Firmware Update interface */
    
    status = DFUD_CreateInterface(&usbd,                        /* A pointer to the USB device stack */
                                  &dfu,                         /* A pointer to the interface to be initialized */
                                  MODE_DFU,                     /* The mode of the application (bootloader mode) */
                                  dfubuf,                       /* A pointer to a buffer for download/upload data */
                                  CFG_DFUDTRANSFERSIZE);        /* The size, in bytes, of the provided buffer */   
    assert(status == SUCCESS);
    
    status = USBD_SetMicrosoftDescriptorSupport(&usbd, TRUE);   /* Enable automatic loading of WinUSB driver on Microsoft Windows */
    assert(status == SUCCESS);
    
    status = USBD_Open(&usbd);                                  /* Open and start communications */
    assert(status == SUCCESS);
}
