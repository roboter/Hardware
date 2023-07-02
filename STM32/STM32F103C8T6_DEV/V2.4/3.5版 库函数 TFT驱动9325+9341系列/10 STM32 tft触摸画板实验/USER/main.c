

/* http://zq281598585.taobao.com/  
�������	  ELH    enlighten  sunny
STM32 ������ �⺯������	  */

/*
  STM32 TFT������ʵ��
  ���õ�TFTΪ9325 9341��ϵ��TFT
  	   �õ���GPIO  PBΪ���ݿ�	  CS PC.8    RS PC.9    WR PC.10     RD PA.15	  RES ����ϵͳ��λ

  ������оƬ����XPT2046
  SPI1���� �� XPT2046����ͨѶ
  SPI1  PA5 6 7   XPT2046 cs  PA11	   �����ж�IO  PA12 �������ж� Ŀǰ����ѭ����ȡ

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




					 //��������

int main(void)
 {
 
      struct TFT_Pointer Tp_pix;	        //���崥�������ṹ��
      u8 t; 

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
	  GUI_Clear(Cyan);		   //��ɫ���� 
	  GUI_sprintf_hzstr16x(0,0,"STM32-ZD touch test",Blue,White);

	while(1)
	{
	    Tp_pix=TFT_Cm();	                            // ɨ�败����
	    if(Tp_pix.flag==1)                              //�Ƿ��д����¼� ���� 
	    { 
		 led(1);			//led��Ӧ
		 Address_set(Tp_pix.x,Tp_pix.y,Tp_pix.x+2,Tp_pix.y+2,Tp_pix.x,Tp_pix.y);			//3*3����Ϊһ����Ԫ��	
		 
		 for(t=0;t<9;t++)				
		  Lcd_Write_Data(Red);

		}
		 led(0);			//�ص�LED

	 }

}
	    





