/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gpio.h
  * @brief   This file contains all the function prototypes for
  *          the gpio.c file
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

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

void MX_GPIO_Init(void);

/* USER CODE BEGIN Prototypes */

/*------------------------------------------ LED配置宏 ----------------------------------*/

#define LED1_PIN            			   GPIO_PIN_13        				 	// LED1 引脚      
#define LED1_PORT           			   GPIOC                 			 	// LED1 GPIO端口     
#define __HAL_RCC_LED1_CLK_ENABLE    __HAL_RCC_GPIOC_CLK_ENABLE() 	// LED1 GPIO端口时钟
	
/*----------------------------------------- LED控制宏 ----------------------------------*/
						
#define LED1_ON 	  	HAL_GPIO_WritePin(LED1_PORT, LED1_PIN, GPIO_PIN_RESET)		// 输出低电平，点亮LED1	
#define LED1_OFF 	  	HAL_GPIO_WritePin(LED1_PORT, LED1_PIN, GPIO_PIN_SET)			// 输出高电平，关闭LED1	
#define LED1_Toggle	  HAL_GPIO_TogglePin(LED1_PORT,LED1_PIN);							// 翻转IO口状态


	
#define	KEY_ON	 1		//按键按下
#define	KEY_OFF	 0		//按键放开

/*------------------------------------------ IO口配置宏 ----------------------------------*/


//#define 	KEY_PIN           					GPIO_PIN_1        				 // KEY 引脚      
//#define	  KEY_PORT          					GPIOC                			 // KEY GPIO端口     
//#define 	__HAL_RCC_KEY_CLK_ENABLE    __HAL_RCC_GPIOC_CLK_ENABLE()	 // KEY GPIO端口时钟

/*------------------------------------------ 函数声明 ------------------------------------*/  
uint8_t	KEY_Scan(void);   //按键扫描

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__ GPIO_H__ */

