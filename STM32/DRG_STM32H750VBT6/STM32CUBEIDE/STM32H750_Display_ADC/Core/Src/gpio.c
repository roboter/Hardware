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
*	�� �� ��:	KEY_Scan
*	��ڲ���:	��
*	�� �� ֵ:KEY_ON - �������£�KEY_OFF - �����ſ� 
*	��������:	����ɨ��
*	˵    ��:�����Ե��øú��������ݷ���ֵ�ж�״̬			
*************************************************************************************************/
	
void LED_Blink(uint32_t delay)
{
	HAL_GPIO_WritePin(LED_GPIO_Port,LED_Pin,GPIO_PIN_SET);
	HAL_Delay(delay - 1);
	HAL_GPIO_WritePin(LED_GPIO_Port,LED_Pin,GPIO_PIN_RESET);
	HAL_Delay(500-1);
}


/*************************************************************************************************
*	�� �� ��:	KEY_Scan
*	��ڲ���:	��
*	�� �� ֵ:KEY_ON - �������£�KEY_OFF - �����ſ� 
*	��������:	����ɨ��
*	˵    ��:�����Ե��øú��������ݷ���ֵ�ж�״̬			
*************************************************************************************************/
	
uint8_t	KEY_Scan(void)
{
	if( HAL_GPIO_ReadPin ( KEY_GPIO_Port,KEY_Pin) == 0 )	//��ⰴ���Ƿ񱻰���
	{	
		HAL_Delay(10);	//��ʱ����
		if( HAL_GPIO_ReadPin ( KEY_GPIO_Port,KEY_Pin) == 0)	//�ٴμ���Ƿ�Ϊ�͵�ƽ
		{
			while(  HAL_GPIO_ReadPin ( KEY_GPIO_Port,KEY_Pin) == 0);	//�ȴ������ſ�
			return KEY_ON;	//���ذ������±�־
		}
	}
	return KEY_OFF;	
}

/* USER CODE BEGIN 2 */

/* USER CODE END 2 */
