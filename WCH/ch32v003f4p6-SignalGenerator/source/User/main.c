/********************************** (C) COPYRIGHT *******************************
 * File Name          : main.c
 * Author             : Robby Roboter
 * Version            : V1.0.0
 * Date               : 2022/08/08
 * Description        : Main program body.

/*
      Hardware connection:
			      PC1 -- SDA
            PC2 -- SCL
*/
#include "ch32v00x_i2c.h"
#include "ch32v00x_gpio.h"
#include "ch32v00x_rcc.h"
#include "debug.h"

#include <ssd1306.h>
//#define I2C_CLKRATE   400000    // I2C bus clock rate (Hz)
// Set system clock frequency
//#ifndef F_CPU
//  #define F_CPU           24000000  // 24Mhz if not otherwise defined
//#endif
//#include "embeetle_logo_128x64.c"

/*********************************************************************
 * @fn      IIC_Init
 *
 * @brief   Initializes the IIC peripheral.
 *
 * @return  none
 */

//
// ===================================================================================
// Update Function
// ===================================================================================
void update(void) {
	char str[] = "Hello World!5\n";
	OLED_printS(str);
	OLED_DrawPixel(0,0,White);
	//OLED_EmbeetleLogo();
	
}

int main(void)
{
	Delay_Init();
	USART_Printf_Init(115200);
	printf("SystemClk:%d\r\n", SystemCoreClock);

	OLED_init();

//	update();

  OLED_clear();
    OLED_println("I2C Scanner Demo");
    Delay_Ms(1000);
    
    // Run the scanner
    OLED_test_all_addresses();
while(1);
	Delay_Ms(1500);
}
