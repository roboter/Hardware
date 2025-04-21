/*******************************************************************************************************************************************

    DZX | LPC1857-MCB | DEMO LM75A                                                                                        VERSION 18.2.1
    ------------------------------------------------------------------------------------------------------------------------------------

    This is an application that demonstrates the usage of a driver to communicate with the on-board temperature sensor.

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
#include "mcu_i2c.h"
#include "Drivers/NXP/lm75a.h"
#include <stdio.h>
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
    static I2C i2c;
    static LM75A lm75;
    STATUS status;
    float tempC;
    
    
    
    status = I2C_Open(&i2c, 0, 400000);             /* Open I2C port 0 (400khz) */
    assert(status == SUCCESS);
    
    status = LM75A_Open(&lm75, &i2c, 0x0);          /* Open LM75 driver */
    assert(status == SUCCESS);
    
    
    for (;;) {
        
        status = LM75A_ReadTemp(&lm75, &tempC);     /* Read the latest temperature (in degrees celsius) */
        if (status == SUCCESS) {
            printf("%.2f\n", tempC);
        }
        
        THREAD_Sleep(100);
    }
}
