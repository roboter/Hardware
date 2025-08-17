#ifndef _KEY_H
#define _KEY_H


#include "main.h"

#define	KEY_ON	 1		//按键按下
#define	KEY_OFF	 0		//按键放开

/*------------------------------------------ IO口配置宏 ----------------------------------*/


#define 	KEY_PIN           					GPIO_PIN_1        				 // KEY 引脚      
#define	KEY_PORT          					GPIOC                			 // KEY GPIO端口     
#define 	__HAL_RCC_KEY_CLK_ENABLE         __HAL_RCC_GPIOC_CLK_ENABLE()	 // KEY GPIO端口时钟

/*------------------------------------------ 函数声明 ------------------------------------*/

void 		KEY_Init(void);	//按键IO口初始化函数
uint8_t	KEY_Scan(void);   //按键扫描
uint8_t	KEY_Scan1(void);   //按键扫描

#endif
