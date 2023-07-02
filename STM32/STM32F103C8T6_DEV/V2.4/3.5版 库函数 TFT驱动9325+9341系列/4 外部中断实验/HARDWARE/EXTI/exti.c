#include "exti.h"
#include "led.h"
#include "key.h"
#include "delay.h"
#include "usart.h"

//中断
//STM32  19个外部中断
//		 线0-15：对应外部IO口的输入中断。
//		 线16： 连PVD输出
//		 线17： 连RTC闹钟事件
//		 线18： 连USB唤醒事件
//
//每个中断线最多对应7个IO口 比如中断线0  对应GPIOA.0 GPIOB.0 GPIOC.0 GPIOD.0 GPIOE.0 GPIOF.0 GPIOG.0
//并且中断线 一次只能连接到一个IO上
//
//中断线0-4每个中断对应 一个 中断函数
//中断线5-9 共用 中断函数EXTI9_5_IRQHandler
//中断线10-15 共用中断函数EXTI15_10_IRQHandler
//
//         

//外部中断0服务程序
void EXTIX_Init(void)
{
 
 	EXTI_InitTypeDef EXTI_InitStructure;			//中断配置	  即哪个中断线  EXTI_Line0-15
																//模式 EXTI_Mode_Interrupt中断  EXTI_Mode_Event 事件
																//触发方式  EXTI_Trigger_Falling 下降沿触发
																//			EXTI_Trigger_Rising	 上升沿触发
																//			EXTI_Trigger_Rising_Falling	  任意电平触发

 	NVIC_InitTypeDef NVIC_InitStructure;			//中断参数 中断优先级


  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//使能复用功能时钟

    //GPIOA.0 中断线以及中断初始化配置   上升沿触发
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0);

  	EXTI_InitStructure.EXTI_Line=EXTI_Line0;	//KEY0			   对应中断线
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;			   //中断模式
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;		   //配置为上升沿触发
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	 	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器

    //GPIOD.2	  中断线以及中断初始化配置 下降沿触发 //KEY1
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOD,GPIO_PinSource2);
  	EXTI_InitStructure.EXTI_Line=EXTI_Line2;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;		   //配置下降沿触发
  	EXTI_Init(&EXTI_InitStructure);	  	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器


   //中断级别越低 越优先
   //两中断  抢占=响应  执行先发生
   //高优先级的抢占 可断 低优先级
   //优先级相等    高响应不可断低响应
    NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;			//使能按键KEY1所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2， 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;					//子优先级2
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure);


  	NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;			//使能按键KEY1所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;					//子优先级1 
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure);  	  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器

 
}

//外部中断1服务程序 
void EXTI0_IRQHandler(void)
{
	delay_ms(10);//消抖
	if(KEY0==1)	 	 //KEY0按键
	{				 
	GPIO_SetBits(GPIOA,GPIO_Pin_1);				//点亮LED2
	}
	EXTI_ClearITPendingBit(EXTI_Line0); //清除LINE0上的中断标志位  为下一次中断做准备
}							 

//外部中断2服务程序
void EXTI2_IRQHandler(void)
{
	delay_ms(10);//消抖
	if(KEY1==0)	  //按键KEY2
	{
	GPIO_ResetBits(GPIOA,GPIO_Pin_1);				//熄灭LED2
	}		 
	EXTI_ClearITPendingBit(EXTI_Line2);  //清除LINE2上的中断标志位  
}



 
