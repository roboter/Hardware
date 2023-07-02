

/* http://zq281598585.taobao.com/  
�������	  ELH    enlighten  sunny
STM32 ������ �⺯������	  */

/*
   DS18B20   �¶ȶ�ȡʵ��
   ���õ�IO����  STM32 PA13  ����PA13Ҳ�� SWD�ӿ�  ���Դ˳��� ��Ӱ��SWD����
   ���� ��TFT ��ʼ�������� �����з��湦�ܽ��н���
   GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE); //JTAG and SWD ȫ������

   ����������ϲ��� ���޷����� DS18b20��ʼ��

   ������Ƿ������� �͸����Լ�����Ҫѡ������IO

*/

#include  "stm32f10x.h"
#include  "delay.h"
#include  "led.h"
#include  "tft.h"
#include  "key.h"
#include  "flash.h"
#include  "gui.h"
#include  "ds18b20.h"



int main(void)
 {
 	  short temperature;	 //�¶ȱ���
	  delay_init();	    	 //��ʱ������ʼ��	 	  
	  LED_Init();		  	 //��ʼ����LED���ӵ�Ӳ���ӿ�
	  KEY_Init();            //��ʼ������			
	  Lcd_Init();			 //LCD  ��ʼ��
	  SPI_Flash_Init();  	 //SPI FLASH ��ʼ��
	  TFT_CS(0);			 //��LCDƬѡʹ�� 
	  GUI_Clear(White);		 //����

	  while(ds18b20_init())
	  {
	   GUI_sprintf_hzstr16x(0,20,"DS18B20  Error",Red,White);
	   delay_ms(300);
	   GUI_sprintf_hzstr16x(0,20,"              ",Red,White);
	   delay_ms(300);	  
	  }

	  GUI_sprintf_hzstr16x(0,20,"DS18B20  ok",Black,White);

	  delay_ms(300);

	  GUI_Clear(White);		 //����

      GUI_sprintf_hzstr16x(0,0,"DS18B20 read temperature",Black,White);
	  GUI_sprintf_hzstr16x(0,30,"The temperature",Blue,White);
	  GUI_sprintf_hzstr16x(120,30,":   . ",Red,White);


	  while(1)
	  {
		 temperature=read_temp();										   //��ȡ�¶�ֵ
	     if(temperature<0) GUI_sprintf_char(28,30,'-',Red,White,0);
	     else GUI_sprintf_char(128,30,' ',Red,White,0);
	     GUI_sprintf_char(136,30,temperature/100%10+'0',Red,White,0);	   //��ʾ��ǰ�¶�ֵ
	     GUI_sprintf_char(144,30,temperature/10%10+'0',Red,White,0);
	     GUI_sprintf_char(160,30,temperature%10+'0',Red,White,0);
	   }						  


 }





