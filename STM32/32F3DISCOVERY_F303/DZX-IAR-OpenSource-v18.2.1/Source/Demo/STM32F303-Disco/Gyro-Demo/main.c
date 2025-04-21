/*******************************************************************************************************************************************

    DZX | STM32F303 DISCOVERY | GYRO DEMO                                                                                 VERSION 18.2.1
    ------------------------------------------------------------------------------------------------------------------------------------

    This is an application that demonstrates using the on-board gyroscope by illuminating LEDs when the board is rotated.

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
#include "Kernel/kernel_thread.h"
#include "Kernel/kernel_timer.h"
#include "board_led.h"
#include "Drivers/ST/l3gd20.h"
#include <assert.h>

/*******************************************************************************************************************************************
    PRIVATE VARIABLES
*******************************************************************************************************************************************/

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

    The process function for the main application thread.

    @param[in]  arg         An optional argument. Not used here.

    @return     None.

*******************************************************************************************************************************************/
static void APP_Main(void* arg)
{
    static SPI spi;
    static L3GD20 gyro;
    STATUS status;
    static L3GD20_SAMPLE sample;
    
    const float level = 20.0F;
    const float half = level / 2.0F;
    
    
    
    LED_Init();                                                 /* Initialize the on-board LEDs */
    
    
    PIN_SetMode(PE_03, MODE_OUTPUT);                            /* Configure PE.3 as a general output for SPI chip-select */
    
    PIN_SetMode(PA_05, MODE_ALTERNATE);                         /* Configure PA.5 for the SPI1_SCK function */
    PIN_SetFunction(PA_05, 5);
    
    PIN_SetMode(PA_06, MODE_ALTERNATE);                         /* Configure PA.6 for the SPI1_MISO function */
    PIN_SetFunction(PA_06, 5);
    
    PIN_SetMode(PA_07, MODE_ALTERNATE);                         /* Configure PA.7 for the SPI1_MOSI function */
    PIN_SetFunction(PA_07, 5);
    
    
    
    status = SPI_Open(&spi, 1, 4000000, SPI_DEFAULT);           /* Open a SPI port (default clock phase/polarity) */
    assert(status == SUCCESS);
    
    status = L3GD20_Open(&gyro, &spi, PE_03);                   /* Open the gyro driver */
    assert(status == SUCCESS);

    static BYTE id;
    status = L3GD20_ReadID(&gyro, &id);
    
    status = L3GD20_SetEnabled(&gyro, TRUE);                    /* Turn on the gyro */
    assert(status == SUCCESS);
    
    status = L3GD20_SubmitChanges(&gyro);                       /* Push all changes to the physical gyro device */
    assert(status == SUCCESS);
    
    
    
    for (;;) {
        
        status = L3GD20_ReadSample(&gyro, &sample);             /* Read the latest gyro sample */
        if (status == SUCCESS) {

            LED_Set(LED_N, sample.x < -level);                  /* Turn on the LEDs based upon the gyro data */
            LED_Set(LED_S, sample.x > level);   
            LED_Set(LED_W, sample.y < -level);
            LED_Set(LED_E, sample.y > level);
            
            LED_Set(LED_NW, (sample.x < -half) && (sample.y < -half));
            LED_Set(LED_NE, (sample.x < -half) && (sample.y > half));
            LED_Set(LED_SW, (sample.x > half) && (sample.y < -half));
            LED_Set(LED_SE, (sample.x > half) && (sample.y > half));
        }
        
        THREAD_Sleep(20);
    }
}
