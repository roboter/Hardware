

#include "led.h"
#include <stm32f103x6.h>

#include "stm32f10x.h"
#include "stm32f10x_conf.h"

void LED_Init(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;					 //����GPIO�ṹ��

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	//ʹ��PA�˿�ʱ��

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;			 //LED-->PA1�˿�����
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
    GPIO_Init(GPIOA, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOA.1
    GPIO_SetBits(GPIOA,GPIO_Pin_1);						 //PA.A �����
}
 
