

#ifndef __KEY_H
#define __KEY_H
#include "stm32f10x.h"

#define KEY0  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)			   //�궨�� PA0 PD2��� Ϊ�ɼ�������׼��
#define KEY1  GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_2)

void KEY_Init(void);//IO��ʼ��



#endif


