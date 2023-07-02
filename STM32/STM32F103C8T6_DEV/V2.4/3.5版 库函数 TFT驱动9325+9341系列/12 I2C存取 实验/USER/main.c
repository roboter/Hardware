

/* http://zq281598585.taobao.com/  
�������	  ELH    enlighten  sunny
STM32 ������ �⺯������	  */

/*
  I2C���߲����ⲿ24c02 eepromоƬ
  i2c���߲���IO��ģ��  PC11 SDA  PC12 SCL
  S4 ����д����  д�ַ�����  A  ����ַ0λ��
  S3 ������ȡ����  ����ַ1�����ݶ�ȡ����

*/

#include  "stm32f10x.h"
#include  "delay.h"
#include  "led.h"
#include  "tft.h"
#include  "key.h"
#include  "flash.h"
#include  "gui.h"
#include  "z24c02.h"



					 //��������

int main(void)
 {
 
 	 u8 pd;


	  delay_init();	    	 //��ʱ������ʼ��	 	  
	  LED_Init();		  	 //��ʼ����LED���ӵ�Ӳ���ӿ�
	  KEY_Init();            //��ʼ������			
	  Lcd_Init();			 //LCD  ��ʼ��
	  SPI_Flash_Init();  	 //SPI FLASH ��ʼ��
	  AT24CXX_Init();        //IIC��ʼ��
	  TFT_CS(0);			 //��LCDƬѡʹ�� 
	  GUI_Clear(White);		   //��ɫ���� 
	  GUI_sprintf_hzstr16x(0,0,"24C02 read and write",White,Blue);
	  GUI_sprintf_hzstr16x(0,20,"write:S4",Black,White);
	  GUI_sprintf_hzstr16x(0,40,"read:S3",Black,White);
	  GUI_sprintf_hzstr16x(0,60,"result:",Black,White);


	while(1)
	{
	 if(KEY1==0)		//PD2 	 ��ȡE2 0��ַλ ��һ���ֽ� ��pd��
	 {
	   delay_ms(100);	//ȥ��
	   if(KEY1==0)	 
		{
		  led(1);    	//����LED
          pd=AT24C_Rcvone(0);    //ѡ��Ҫ��ȡ�ĵ�ַ  Ȼ�󽫶�ȡ�����ݴ������pd�� 1����1���ֽڵ������ָ������ 
		  GUI_sprintf_char(56,60,pd,Red,White,0); //��ʾ��ȡ������ֵ    		
		}
	  }
		 //========================IIC ����
	  if(KEY0==1)		//PA0
	  {
		delay_ms(100);	//ȥ��
		if(KEY0==1)
		 {
 		   led(0);			    //ָʾ�� �� ��ʾ ����ɹ�
	  	   pd='A';		        //��Ԥ�洢Count1�е�ֵ������pd
		   AT24C_Sendone(0,pd);	//��pd��ֵ����  0��ַλ�� ������Ϊ1�ֽ�
		 }

	   }
	  
	 }

}
	    





