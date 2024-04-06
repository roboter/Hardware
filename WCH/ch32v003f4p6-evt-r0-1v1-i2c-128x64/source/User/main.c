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

#include "debug.h"
#include <oled_segment.h>     // OLED functions
#include "embeetle_logo_128x64.c"

/*********************************************************************
 * @fn      IIC_Init
 *
 * @brief   Initializes the IIC peripheral.
 *
 * @return  none
 */
void IIC_Init(u32 bound, u16 address)
{
    GPIO_InitTypeDef GPIO_InitStructure={0};
    I2C_InitTypeDef I2C_InitTSturcture={0};

    RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO, ENABLE );
    RCC_APB1PeriphClockCmd( RCC_APB1Periph_I2C1, ENABLE );

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init( GPIOC, &GPIO_InitStructure );

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init( GPIOC, &GPIO_InitStructure );

    I2C_InitTSturcture.I2C_ClockSpeed = bound;
    I2C_InitTSturcture.I2C_Mode = I2C_Mode_I2C;
    I2C_InitTSturcture.I2C_DutyCycle = I2C_DutyCycle_16_9;
    I2C_InitTSturcture.I2C_OwnAddress1 = address;
    I2C_InitTSturcture.I2C_Ack = I2C_Ack_Enable;
    I2C_InitTSturcture.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
    I2C_Init( I2C1, &I2C_InitTSturcture );

    I2C_Cmd( I2C1, ENABLE );

    I2C_AcknowledgeConfig( I2C1, ENABLE );
}

// ===================================================================================
// Update Function
// ===================================================================================
void update(void) {
	char str[] = "Hello World!5\n";
	//OLED_printS(str);
	OLED_DrawPixel(0,0,White);
	OLED_EmbeetleLogo();
	
}

int main(void)
{
	Delay_Init();
	//USART_Printf_Init(115200);
	//printf("SystemClk:%d\r\n",SystemCoreClock);

	// Setup internal peripherals
	I2C_init();

	// Setup external peripherals
	OLED_init();
	//OLED_clear2();
	update();

	Delay_Ms(1500);
}
