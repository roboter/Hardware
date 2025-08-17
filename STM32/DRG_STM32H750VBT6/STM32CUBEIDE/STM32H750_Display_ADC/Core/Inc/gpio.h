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

/*------------------------------------------ LED���ú� ----------------------------------*/

#define LED1_PIN            			   GPIO_PIN_13        				 	// LED1 ����      
#define LED1_PORT           			   GPIOC                 			 	// LED1 GPIO�˿�     
#define __HAL_RCC_LED1_CLK_ENABLE    __HAL_RCC_GPIOC_CLK_ENABLE() 	// LED1 GPIO�˿�ʱ��
	
/*----------------------------------------- LED���ƺ� ----------------------------------*/
						
#define LED1_ON 	  	HAL_GPIO_WritePin(LED1_PORT, LED1_PIN, GPIO_PIN_RESET)		// ����͵�ƽ������LED1	
#define LED1_OFF 	  	HAL_GPIO_WritePin(LED1_PORT, LED1_PIN, GPIO_PIN_SET)			// ����ߵ�ƽ���ر�LED1	
#define LED1_Toggle	  HAL_GPIO_TogglePin(LED1_PORT,LED1_PIN);							// ��תIO��״̬


	
#define	KEY_ON	 1		//��������
#define	KEY_OFF	 0		//�����ſ�

/*------------------------------------------ IO�����ú� ----------------------------------*/


//#define 	KEY_PIN           					GPIO_PIN_1        				 // KEY ����      
//#define	  KEY_PORT          					GPIOC                			 // KEY GPIO�˿�     
//#define 	__HAL_RCC_KEY_CLK_ENABLE    __HAL_RCC_GPIOC_CLK_ENABLE()	 // KEY GPIO�˿�ʱ��

/*------------------------------------------ �������� ------------------------------------*/  
uint8_t	KEY_Scan(void);   //����ɨ��

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__ GPIO_H__ */

