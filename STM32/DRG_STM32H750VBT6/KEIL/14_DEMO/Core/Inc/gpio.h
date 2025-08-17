/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gpio.h
  * @brief   This file contains all the function prototypes for
  *          the gpio.c file
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __GPIO_H__
#define __GPIO_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

#define LED1_ON 	  	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET)		// 输出低电平，点亮LED1	
#define LED1_OFF 	  	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET)			// 输出高电平，关闭LED1	
#define LED1_Toggle	  HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_13);							// 翻转IO口状态
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

void MX_GPIO_Init(void);

/* USER CODE BEGIN Prototypes */

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__ GPIO_H__ */

