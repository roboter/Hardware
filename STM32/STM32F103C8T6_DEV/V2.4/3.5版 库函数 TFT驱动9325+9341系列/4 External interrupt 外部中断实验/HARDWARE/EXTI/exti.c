#include "exti.h"
#include "led.h"
#include "key.h"
#include "delay.h"
#include "usart.h"

//�ж�
//STM32  19���ⲿ�ж�
//		 ��0-15����Ӧ�ⲿIO�ڵ������жϡ�
//		 ��16�� ��PVD���
//		 ��17�� ��RTC�����¼�
//		 ��18�� ��USB�����¼�
//
//ÿ���ж�������Ӧ7��IO�� �����ж���0  ��ӦGPIOA.0 GPIOB.0 GPIOC.0 GPIOD.0 GPIOE.0 GPIOF.0 GPIOG.0
//�����ж��� һ��ֻ�����ӵ�һ��IO��
//
//�ж���0-4ÿ���ж϶�Ӧ һ�� �жϺ���
//�ж���5-9 ���� �жϺ���EXTI9_5_IRQHandler
//�ж���10-15 �����жϺ���EXTI15_10_IRQHandler
//
//         

//�ⲿ�ж�0�������
void EXTIX_Init(void)
{
 
 	EXTI_InitTypeDef EXTI_InitStructure;			//�ж�����	  ���ĸ��ж���  EXTI_Line0-15
																//ģʽ EXTI_Mode_Interrupt�ж�  EXTI_Mode_Event �¼�
																//������ʽ  EXTI_Trigger_Falling �½��ش���
																//			EXTI_Trigger_Rising	 �����ش���
																//			EXTI_Trigger_Rising_Falling	  �����ƽ����

 	NVIC_InitTypeDef NVIC_InitStructure;			//�жϲ��� �ж����ȼ�


  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//ʹ�ܸ��ù���ʱ��

    //GPIOA.0 �ж����Լ��жϳ�ʼ������   �����ش���
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0);

  	EXTI_InitStructure.EXTI_Line=EXTI_Line0;	//KEY0			   ��Ӧ�ж���
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;			   //�ж�ģʽ
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;		   //����Ϊ�����ش���
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	 	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���

    //GPIOD.2	  �ж����Լ��жϳ�ʼ������ �½��ش��� //KEY1
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOD,GPIO_PinSource2);
  	EXTI_InitStructure.EXTI_Line=EXTI_Line2;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;		   //�����½��ش���
  	EXTI_Init(&EXTI_InitStructure);	  	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���


   //�жϼ���Խ�� Խ����
   //���ж�  ��ռ=��Ӧ  ִ���ȷ���
   //�����ȼ�����ռ �ɶ� �����ȼ�
   //���ȼ����    ����Ӧ���ɶϵ���Ӧ
    NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;			//ʹ�ܰ���KEY1���ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�2�� 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;					//�����ȼ�2
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure);


  	NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;			//ʹ�ܰ���KEY1���ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�2 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;					//�����ȼ�1 
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure);  	  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���

 
}

//�ⲿ�ж�1������� 
void EXTI0_IRQHandler(void)
{
	delay_ms(10);//����
	if(KEY0==1)	 	 //KEY0����
	{				 
	GPIO_SetBits(GPIOA,GPIO_Pin_1);				//����LED2
	}
	EXTI_ClearITPendingBit(EXTI_Line0); //���LINE0�ϵ��жϱ�־λ  Ϊ��һ���ж���׼��
}							 

//�ⲿ�ж�2�������
void EXTI2_IRQHandler(void)
{
	delay_ms(10);//����
	if(KEY1==0)	  //����KEY2
	{
	GPIO_ResetBits(GPIOA,GPIO_Pin_1);				//Ϩ��LED2
	}		 
	EXTI_ClearITPendingBit(EXTI_Line2);  //���LINE2�ϵ��жϱ�־λ  
}



 
