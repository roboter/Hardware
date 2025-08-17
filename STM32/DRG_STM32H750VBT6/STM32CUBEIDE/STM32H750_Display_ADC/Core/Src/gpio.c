/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gpio.c
  * @brief   This file provides code for the configuration
  *          of all used GPIO pins.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "gpio.h"
#include "main.h"
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/** Configure pins
     PC14-OSC32_IN (OSC32_IN)   ------> RCC_OSC32_IN
     PC15-OSC32_OUT (OSC32_OUT)   ------> RCC_OSC32_OUT
     PH0-OSC_IN (PH0)   ------> RCC_OSC_IN
     PH1-OSC_OUT (PH1)   ------> RCC_OSC_OUT
     PA13 (JTMS/SWDIO)   ------> DEBUG_JTMS-SWDIO
     PA14 (JTCK/SWCLK)   ------> DEBUG_JTCK-SWCLK
*/
void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = LED_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LED_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = KEY_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(KEY_GPIO_Port, &GPIO_InitStruct);

}

/*************************************************************************************************
*	函 数 名:	KEY_Scan
*	入口参数:	无
*	返 回 值:KEY_ON - 按键按下，KEY_OFF - 按键放开 
*	函数功能:	按键扫描
*	说    明:周期性调用该函数，根据返回值判断状态			
*************************************************************************************************/
	
void LED_Blink(uint32_t delay)
{
	HAL_GPIO_WritePin(LED_GPIO_Port,LED_Pin,GPIO_PIN_SET);
	HAL_Delay(delay - 1);
	HAL_GPIO_WritePin(LED_GPIO_Port,LED_Pin,GPIO_PIN_RESET);
	HAL_Delay(500-1);
}


/*************************************************************************************************
*	函 数 名:	KEY_Scan
*	入口参数:	无
*	返 回 值:KEY_ON - 按键按下，KEY_OFF - 按键放开 
*	函数功能:	按键扫描
*	说    明:周期性调用该函数，根据返回值判断状态			
*************************************************************************************************/
	
uint8_t	KEY_Scan(void)
{
	if( HAL_GPIO_ReadPin ( KEY_GPIO_Port,KEY_Pin) == 0 )	//检测按键是否被按下
	{	
		HAL_Delay(10);	//延时消抖
		if( HAL_GPIO_ReadPin ( KEY_GPIO_Port,KEY_Pin) == 0)	//再次检测是否为低电平
		{
			while(  HAL_GPIO_ReadPin ( KEY_GPIO_Port,KEY_Pin) == 0);	//等待按键放开
			return KEY_ON;	//返回按键按下标志
		}
	}
	return KEY_OFF;	
}

/* USER CODE BEGIN 2 */

/* USER CODE END 2 */
