

/* http://zq281598585.taobao.com/  
�������	  ELH    enlighten  sunny
STM32 ������ �⺯������	  */

//LED��˸��ʵ��  �����ϵ�PA1�� ����LED  0�� 1��



#include  "delay.h"
#include  "led.h"


int main(void)
   {

   	delay_init();	    	 //��ʱ������ʼ��	  
	LED_Init();		  	//��ʼ����LED���ӵ�Ӳ���ӿ�
   
   while(1)
   {
  		GPIO_ResetBits(GPIOA,GPIO_Pin_1);			   //��PC13��0	
		delay_ms(800);
		GPIO_SetBits(GPIOA,GPIO_Pin_1);			   //��PC13��1
		delay_ms(800);

   }
   }

