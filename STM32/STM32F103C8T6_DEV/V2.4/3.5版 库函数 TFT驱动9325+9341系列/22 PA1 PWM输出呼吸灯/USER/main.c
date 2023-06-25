

/* http://zq281598585.taobao.com/  
�������	  ELH    enlighten  sunny
STM32 ������ �⺯������	  */


//��ʱ��2  ��PA1�ڽ���PWM��������Ƶ��Ϊ8KHz��Ƶ�ʿɸ��ݺ������ڣ�
//PA1���Ͻ���LED�ƣ�PWM��8k�� ��0��350 �ٴ�350��0 ���ر仯  ����������������Ч��



#include  "delay.h"
#include  "led.h"
#include "timer.h"


int main(void)
   {
 	u16 led_pwmval=0;
	u8 point=1;

   	delay_init();	    	 //��ʱ������ʼ��
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�	  
	LED_Init();		  	//��ʼ����LED���ӵ�Ӳ���ӿ�
   
  	TIM2_PWM_Init(899,0);	 //����Ƶ��PWMƵ��=72000/900=8Khz

   	while(1)
	{
 		delay_ms(10);	 
		if(point)led_pwmval+=1;
		else led_pwmval-=1;

 		if(led_pwmval>350)point=0;
		if(led_pwmval==0)point=1;										 
		TIM_SetCompare2(TIM2,led_pwmval);		   
	}


   }

