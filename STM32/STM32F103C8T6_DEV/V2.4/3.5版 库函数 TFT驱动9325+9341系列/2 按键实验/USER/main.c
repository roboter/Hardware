

/* http://zq281598585.taobao.com/  
�������	  ELH    enlighten  sunny
STM32������ �⺯������	  */

//��������LED��ʵ��  
//�����ϵİ��� �ֱ���S3 ΪPD2  S4 ΪPA0
//��ʵ�� ͨ��S4���� �����ϵ�LED��  S3����LED��



#include  "delay.h"
#include  "led.h"
#include  "key.h"


int main(void)
   {

   	delay_init();	     //��ʱ������ʼ��	  
	LED_Init();		  	//��ʼ����LED���ӵ�Ӳ���ӿ�
	KEY_Init();         //��ʼ������
   while(1)
   {
 
        if(KEY0==1)
		  {
		    GPIO_ResetBits(GPIOA,GPIO_Pin_1);		  //��PA1��0
		  }
		if(KEY1==0)
		  {
		    GPIO_SetBits(GPIOA,GPIO_Pin_1);		  //��PA1��1
		  
		  }


   }
   }

