

/* http://zq281598585.taobao.com/  
�������	  ELH    enlighten  sunny
STM32 ������ �⺯������	  */


//��ʱ��2  ����жϺ�  �����ж� ���ж�����ת PA1�ⲿLED����IO



#include  "delay.h"
#include  "led.h"
#include "timer.h"


int main(void)
   {

   	delay_init();	    	 //��ʱ������ʼ��
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�	  
	LED_Init();		  	//��ʼ����LED���ӵ�Ӳ���ӿ�
	TIM2_Int_Init(9999,7199);//20Khz�ļ���Ƶ��  1�뷭תһ��
   
   while(1)	;

   }

