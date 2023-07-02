

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
 
// 	 u8 pd;


	  delay_init();	    	 //��ʱ������ʼ��	 	  
	  LED_Init();		  	 //��ʼ����LED���ӵ�Ӳ���ӿ�
	  KEY_Init();            //��ʼ������			
	  Lcd_Init();			 //LCD  ��ʼ��
	  SPI_Flash_Init();  	 //SPI FLASH ��ʼ��
	  AT24CXX_Init();        //IIC��ʼ��
	  TFT_CS(0);			 //��LCDƬѡʹ�� 
	  GUI_Clear(White);		   //��ɫ���� 

  GUI_sprintf_hzstr16x(10,30,"����Ƽ�",Black,White);
  GUI_sprintf_hzstr16x(10,50,"welcome to MCU world!",Blue,White);
  GUI_sprintf_hzstr16x(10,70,"STM32F103RBT6",White,Red);
  GUI_sprintf_hzstr16x(10,90,"��ϼ�������ɣ�",Red3,White);
  GUI_sprintf_hzstr16x(10,110,"��ˮ������һɫ��",Red3,White);

  while(1);  

}
	    





