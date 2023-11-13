

/* http://zq281598585.taobao.com/  
�������	  ELH    enlighten  sunny
STM32������ �⺯������	  */

// �ж�ʵ��  ͨ���ⲿ�ж���  �� ���� PA.0  PD.2��  	������Ϊ�½��ش��� ����������exti.c��
//			 ��������������ж�	 PA.0��S4�������ж� ���ư���LED��   PD.2(S3)�����ж� ���ư���LED��
//			 ���Ҵ��� Ҳ����ͣ�Ĵ�ӡ���� �Ա�ʾ������������




#include  "delay.h"
#include  "led.h"
#include  "key.h"
#include  "usart.h"
#include "exti.h"


int main(void)
   {

   	delay_init();	    	 //��ʱ������ʼ��
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//����NVIC�жϷ���Ϊ��2  2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	                                                //һ������ ����Ҫ���׸ı�
	uart_init(9600);	    //���ڳ�ʼ��Ϊ9600  
	LED_Init();		  	    //��ʼ����LED���ӵ�Ӳ���ӿ�
	KEY_Init();				//	�����˿ڳ�ʼ��
	EXTIX_Init();		 	//�ⲿ�жϳ�ʼ��
   
 	while(1)
	{
		printf("ELH �������\r\n");	
		delay_ms(1000);
	}

   }

