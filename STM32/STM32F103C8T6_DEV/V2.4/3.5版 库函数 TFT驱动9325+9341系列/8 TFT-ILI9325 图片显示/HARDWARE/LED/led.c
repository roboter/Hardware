

#include "led.h"



void LED_Init(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;					 //定义GPIO结构体
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	//使能PC端口时钟
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;			 //LED-->PA.1 端口配置
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(GPIOA, &GPIO_InitStructure);					 //根据设定参数初始化GPIOA.1
 GPIO_SetBits(GPIOA,GPIO_Pin_1);						 //PA.1 输出高

}
 


void led(u8 m)
{
 if(m==1) GPIO_ResetBits(GPIOA,GPIO_Pin_1);			   //给PA1置0	 点亮LED2
 else GPIO_SetBits(GPIOA,GPIO_Pin_1);			      //给PA1置1	 熄灭LED2

}
