

/* http://zq281598585.taobao.com/  
�������	  ELH    enlighten  sunny
STM32������ �⺯������	  */

/*
  STM32 �ϵ�a  TF����ʼ����ʶ��
  tf���������ǵ�TFT���ϵ�tf��ģ��   
  tf��ģ�� ����SPI1����   CSƬѡIOΪ PA4  

  TFT  ����оƬΪ ili9325	
  TFT�õ���GPIO  PBΪ���ݿ�	  CS PC.8    RS PC.9    WR PC.10     RD PA.15	  RES ����ϵͳ��λ

*/

#include  "stm32f10x.h"
#include  "delay.h"
#include  "led.h"
#include  "spi.h"
#include  "tft.h"
#include  "key.h"
#include  "flash.h"
#include  "gui.h"
#include  "z24c02.h"
#include  "xpt2046.h"
#include  "sd.h"




extern u8 SD_Type;			  //SD������				

int main(void)
 {
 	  u32 sd_size;				  //��ʱ����

	  delay_init();	    	 //��ʱ������ʼ��	 	  
	  LED_Init();		  	 //��ʼ����LED���ӵ�Ӳ���ӿ�
	  KEY_Init();            //��ʼ������	
	  SPI1_Init();			 //��ʼ��SPI1����
	  SPI1_SetSpeed(SPI_BaudRatePrescaler_2);//����Ϊ18Mʱ��,����ģʽ		
	  Lcd_Init();			 //LCD  ��ʼ��
	  SPI_Flash_Init();  	 // FLASH ��ʼ��
	  XPT2046_Init();		 //����оƬXPT2046 io����
	  AT24CXX_Init();        //IIC��ʼ��



	  TFT_CS(0);			 //��LCDƬѡʹ�� 
	  GUI_Clear(White);			  //��ɫ����

	  GUI_sprintf_hzstr16x(0,0,"TF Card Init!",Black,White);
	  
	  GUI_sprintf_hzstr16x(0,40,"TF Card Type:",Blue,White);	  //������
	  GUI_sprintf_hzstr16x(0,60,"TF Card Size:    Mb",Blue,White);	//������
	
	  if(SD_Init()==0)GUI_sprintf_hzstr16x(0,20,"TF Card  ok",Black,White);	  //��ʼ��TF��
	  else GUI_sprintf_hzstr16x(0,20,"TF Card Error",Red,White);
	
	  sd_size=SD_GetCapacity();	  //����SD������
	
	  if(SD_Type==0x04)GUI_sprintf_hzstr16x(104,40,"SD_TYPE_V2",Blue,White);	   //0-2g
	  if(SD_Type==0x06)GUI_sprintf_hzstr16x(104,40,"SD_TYPE_V2HC",Blue,White);  //2-32g
	
	  number(104,60,sd_size>>20,Red,White);   //��ʾ������  1M=1024KB  1KB=1024B  1B=8bit	   2��20�η�Ϊ1024x1024 Ҳ����M
	  while(1);  

}
	    





