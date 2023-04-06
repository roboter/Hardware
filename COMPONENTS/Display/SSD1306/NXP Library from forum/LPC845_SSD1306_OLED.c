/*
 *---------------------PROGRAMA DE PRUEBA PANTALLA SSD1306 - 128*64 ---------------------
 *
 * */

#include <stdio.h>
#include "board.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "LPC845.h"
#include "fsl_debug_console.h"
#include "fsl_Systick_Delay.h"
#include "fsl_i2c.h"
#include "fsl_swm.h"
#include <fsl_SSD1306_I2C.h>


/*******************************************************************************
 * Variables
 ******************************************************************************/
uint32_t baudRate = 400000;
uint32_t frecuency = 12000000;
/*******************************************************************************
 * Code
 ******************************************************************************/

int main(void) {

	BOARD_InitDebugConsole();                                         // not necessary, only to use the console if needed

	i2c_master_config_t i2config;                                    // config. variable. i2c

	CLOCK_Select(kI2C1_Clk_From_MainClk);

	CLOCK_EnableClock(kCLOCK_Swm);
	SWM_SetMovablePinSelect(SWM0, kSWM_I2C1_SDA, kSWM_PortPin_P0_28);  // SDA to PIO0_28
	SWM_SetMovablePinSelect(SWM0, kSWM_I2C1_SCL, kSWM_PortPin_P0_27);  // SCL to PIO0_27
	CLOCK_DisableClock(kCLOCK_Swm);

	I2C_MasterGetDefaultConfig(&i2config);                             // get the default config of i2c

//------DEFAULT CONFIG---------------
//	  masterConfig.enableMaster  = true;
//    masterConfig.baudRate_Bps  = 100000U;
//    masterConfig.enableTimeout = false;

	i2config.baudRate_Bps = baudRate;                                  //adjusting the baudrate to the OLED oscillator

	I2C_MasterInit(I2C1, &i2config, frecuency);                        //initialization

    /* Initialize the SSD1306 display*/
    OLED_Init();
    OLED_Refresh();
    OLED_Clear();

    /*Print welcome message*/
    OLED_Copy_Image(&logo_nxp[0], sizeof(logo_nxp));
    OLED_Refresh();

    OLED_Set_Text(10, 52, kOLED_Pixel_Set, "LPC845 BoB", 2);
    OLED_Refresh();

    while(1) {

    }
    return 0 ;
}
