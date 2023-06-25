

/* http://zq281598585.taobao.com/  
�������	  ELH    enlighten  sunny
STM32 ������ �⺯������	  */

/*
����H1838 ����ͷ ����ʵ��
�������ͷ���� PA3 IO�ڽ��մ�������	  ����ⷨ��ο�ԭ��ͼЧ��
����ң��������ʱ TFT��ʾ��������

*/

#include  "stm32f10x.h"
#include  "delay.h"
#include  "led.h"
#include  "tft.h"
#include  "key.h"
#include  "flash.h"
#include  "gui.h"
#include  "h1838.h"




int main(void)
 {
	  u8 key;

	  delay_init();	    	 //��ʱ������ʼ��	 
	  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�	  
	  LED_Init();		  	 //��ʼ����LED���ӵ�Ӳ���ӿ�
	  KEY_Init();            //��ʼ������			
	  Lcd_Init();			 //LCD  ��ʼ��
	  SPI_Flash_Init();  	 //SPI FLASH ��ʼ��

	  Remote_Init();			//������ճ�ʼ��


	  TFT_CS(0);			 //��LCDƬѡʹ�� 
	  GUI_Clear(White);		 //����



	  GUI_Clear(White);		 //����

      GUI_sprintf_hzstr16x(0,0,"H1838 test",Black,White);
	  GUI_sprintf_hzstr16x(0,30,"Please touch remote control!",Blue,White);
	  GUI_sprintf_hzstr16x(0,80,"The Decode:",Blue,White);
	 

	  while(1)
	  {
		key=Remote_Scan();	
		if(key)
		{

		   number10(88,80,key,Red,White);

		}
	   }						  


 }





