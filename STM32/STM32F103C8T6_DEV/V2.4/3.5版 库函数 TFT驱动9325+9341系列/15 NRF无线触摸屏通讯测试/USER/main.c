

/* http://zq281598585.taobao.com/  
�������	  ELH    enlighten  sunny
STM32 ������ �⺯������	  */

/*
  STM32 TFT������ʵ��
  ���õ�TFTΪ9325TFT
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
#include  "nrf24l01.h"




					 //��������

int main(void)
 {
 
      struct TFT_Pointer Tp_pix;	        //���崥�������ṹ��
      u8 t; 
	  u8 mode=0;
	  u8 Buf[3];						 //��������
	  u16 pix,piy;						 //��ʱ����	   ���ڴ�����յ�������

	  delay_init();	    	 //��ʱ������ʼ��	 	  
	  LED_Init();		  	 //��ʼ����LED���ӵ�Ӳ���ӿ�
	  KEY_Init();            //��ʼ������	
	  SPI1_Init();			 //��ʼ��SPI1����
	  SPI1_SetSpeed(SPI_BaudRatePrescaler_2);//����Ϊ18Mʱ��,����ģʽ		
	  Lcd_Init();			 //LCD  ��ʼ��
	  SPI_Flash_Init();  	 // FLASH ��ʼ��
	  XPT2046_Init();		 //����оƬXPT2046 io����
	  AT24CXX_Init();        //IIC��ʼ��

	  NRF_IO_Init();         //NRF ��ӦIO���� ��ʼ��

	  TFT_CS(0);			 //��LCDƬѡʹ�� 
	  GUI_Clear(White);		   //��ɫ���� 




	  GUI_sprintf_hzstr16x(0,0,"NRF24L01 Init",White,Black);

      while(NRF24L01_Check())		//���NRF����ģ���Ƿ����� ͬʱ������spi�����ٶ�	 Ϊ9M
  	  {
		GUI_sprintf_hzstr16x(0,20,"NO NRF24L01!",Red,White);
		delay_ms(400);
		GUI_sprintf_hzstr16x(0,20,"            ",Red,White);
		delay_ms(400);

	  }

	  GUI_sprintf_hzstr16x(0,20,"NRF24L01 is ok...",Blue,White);
	  delay_ms(400);
		

	  GUI_Clear(White);		   //��ɫ����

	  GUI_sprintf_hzstr16x(0,0,"STM32-ZD NRF24L01 test",Blue,White);


	  GUI_sprintf_hzstr16x(0,30,"S4: NRF for Send",Black,White);
	  GUI_sprintf_hzstr16x(0,50,"S3: NRF for Receive",Black,White);


	while(1)
	{

	   if(KEY0==1)		     //S4  ����Ϊ����ģʽ
	   {
		delay_ms(100);
		if(KEY0==1)
		 {
		   mode=1;
		   break;
		 }
	   }
	   if(KEY1==0)		     //S3  ����Ϊ����ģʽ
	   {
		delay_ms(100);
		if(KEY1==0)
		 {
		   mode=2;
		   break;
		 }
	   }

	 }
	  if(mode==1)			//����ģʽ
	  {
	   GUI_Clear(Black);
	   GUI_sprintf_hzstr16x(0,0,"NRF24l01 Send",Yellow,Black);
	   RX_TX_Mode(1);			 //����ģʽ��ʼ��

	   	while(1)
		 {	
	       Tp_pix=TFT_Cm();	                            // ɨ�败����
	       if(Tp_pix.flag==1)                              //�Ƿ��д����¼� ���� 
			{
																				//�趨��ͼλ�� 
				Address_set(Tp_pix.x,Tp_pix.y,Tp_pix.x+2,Tp_pix.y+2,Tp_pix.x,Tp_pix.y);			//3*3����Ϊһ����Ԫ��	
			    for(t=0;t<9;t++)				
				 Lcd_Write_Data(White);
		
				
				Buf[0]= Tp_pix.x;                               //����ǰ������λ�ô��������� 
				Buf[2]= Tp_pix.y;
				Buf[1]= Tp_pix.y>>8;
		
		        nRF24L01_TxPacket(Buf);	//��������	
		        delay_ms(10);	

		    }	  	  
	      }
	   }

	  if(mode==2)			  //����ģʽ
	  {
	   GUI_Clear(Black);
	   GUI_sprintf_hzstr16x(0,0,"NRF24l01 Receive",Yellow,Black);
	   RX_TX_Mode(0);	           //����ģʽ��ʼ��

	   	while(1)
		 {	
		   led(0);								   //�ص�ָʾ��
			 if(nRF24L01_RxPacket(Buf)==0)		   //�ɼ����� 
			  {				
					  
				   pix=Buf[0];			   //�������� ��Ļ�ֱ���Ϊ320X240 һ�ֽ������װ255  320���� ����һ���ֽ����Է����ֽ�װ����
				   piy=(Buf[1]<<8)+Buf[2];

		           Address_set(pix,piy,pix+2,piy+2,pix,piy);			//3*3����Ϊһ����Ԫ��
				   for(t=0;t<9;t++)				
					Lcd_Write_Data(White);										
		
				   led(1);									   //ָʾ���ж��Ƿ���յ�����
			       delay_ms(10);								//С��ʱ
		       }
 	  
	      }
	   }

}
















