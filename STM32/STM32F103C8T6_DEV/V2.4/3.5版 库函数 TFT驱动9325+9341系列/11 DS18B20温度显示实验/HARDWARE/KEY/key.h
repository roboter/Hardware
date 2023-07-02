

#ifndef __KEY_H
#define __KEY_H
#include "stm32f10x.h"

#define KEY0  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)			   //宏定义 PA1 PD2输出 为采集数据做准备
#define KEY1  GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_2)

void KEY_Init(void);//IO初始化



#endif


