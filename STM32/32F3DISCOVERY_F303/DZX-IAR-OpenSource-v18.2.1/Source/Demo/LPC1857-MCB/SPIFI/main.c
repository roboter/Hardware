/*******************************************************************************************************************************************

    DZX | LPC1857-MCB | DEMO SPIFI                                                                                        VERSION 18.2.1
    ------------------------------------------------------------------------------------------------------------------------------------

    This is an application that demonstrates the usage of a SPIFI driver to communicate with an on-board serial flash chip.

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
#include "mcu_spifi.h"
#include "Drivers/Spansion/s25fl032p_nxpspifi.h"
#include "board_button.h"
#include "mcu_pin.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>

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
    KERNEL_Execute(APP_Main, NULL);
    return 0;
}

/***************************************************************************************************************************************//**

    The process function for the main application thread.

    @param[in]  arg         An optional argument. Not used here.

    @return     None.

*******************************************************************************************************************************************/
static void APP_Main(void* arg)
{
    static SPIFI spifi;
    static S25FL032P mem;
    ALIGNED(4) static BYTE data[32];
    ALIGNED(4) static BYTE buf[32];
    STATUS status;
    UINT32 k;
    
    
    BUTTON_Init();                                              /* Initialize for reading the on-board buttons */
    
    
    /* Configure the SPIFI pins */

    PIN_SetFunction(P3_08, 3);                                  /* Assign P3.8 to the SPIFI_CS function */
    PIN_SetGlitchFilter(P3_08, FALSE);
    PIN_SetFastSlewRate(P3_08, TRUE);
    
    PIN_SetFunction(P3_03, 3);                                  /* Assign P3.3 to the SPIFI_SCK function */
    PIN_SetInputBuffer(P3_03, TRUE);
    PIN_SetGlitchFilter(P3_03, FALSE);
    PIN_SetFastSlewRate(P3_03, TRUE);  
    
    PIN_SetFunction(P3_07, 3);                                  /* Assign P3.7 to the SPIFI_MOSI function */
    PIN_SetInputBuffer(P3_07, TRUE);
    PIN_SetGlitchFilter(P3_07, FALSE);
    PIN_SetFastSlewRate(P3_07, TRUE);
    
    PIN_SetFunction(P3_06, 3);                                  /* Assign P3.6 to the SPIFI_MISO function */
    PIN_SetInputBuffer(P3_06, TRUE);
    PIN_SetGlitchFilter(P3_06, FALSE);
    PIN_SetFastSlewRate(P3_06, TRUE);
    
    PIN_SetFunction(P3_05, 3);                                  /* Assign P3.5 to the SPIFI_SIO2 function */
    PIN_SetInputBuffer(P3_05, TRUE);
    PIN_SetGlitchFilter(P3_05, FALSE);
    PIN_SetFastSlewRate(P3_05, TRUE);
    
    PIN_SetFunction(P3_04, 3);                                  /* Assign P3.4 to the SPIFI_SIO3 function */
    PIN_SetInputBuffer(P3_04, TRUE);
    PIN_SetGlitchFilter(P3_04, FALSE);
    PIN_SetFastSlewRate(P3_04, TRUE);                             
    
    
    
    status = SPIFI_Open(&spifi, 0);                             /* Initialize the SPIFI peripheral */
    assert(status == SUCCESS);
    
    status = S25FL032P_Open(&mem, &spifi);                      /* Open and init the serial flash memory */
    assert(status == SUCCESS);
    
    
    /* Press button P4_3 to have a test array
       of data programmed into the serial flash */
    
    if (BUTTON_IsPressed(BTN_P4_03)) {                          /* Is button P4_3 pressed? */
        
        status = S25FL032P_Erase4KB(&mem, 0);                   /* Erase first 4KB sector */
        assert(status == SUCCESS);
         
        for (k = 0; k < 32; k++) {                              /* Create an array of test data */
            data[k] = (BYTE)k;
        }
        
        status = S25FL032P_Program(&mem, 0, data, 32);          /* Program the test array to the serial flash chip */
        assert(status == SUCCESS);
    }
    
    
    /* Press button P4_4 to have the first sector
       of the serial flash erased */
    
    if (BUTTON_IsPressed(BTN_P4_04)) {
        
        status = S25FL032P_Erase4KB(&mem, 0);                   /* Erase first 4KB sector */
        assert(status == SUCCESS);
    }
    
    
    status = S25FL032P_EnterAutoRead(&mem);                     /* Set the flash chip for automatic read */
    assert(status == SUCCESS);
    
    
    /* Read in the first 32-bytes of the serial flash
       chip. Run this demo with either buttons pressed
       to see the flash contents change. */
    
    memcpy(buf, (void*)0x80000000, 32);                         /* Read the first 32 bytes of the flash */
    
    for (;;) {
        
        THREAD_Sleep(100);
    }
}
