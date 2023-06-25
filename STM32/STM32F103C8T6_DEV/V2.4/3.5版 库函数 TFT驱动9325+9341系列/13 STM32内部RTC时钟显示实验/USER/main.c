

/* http://zq281598585.taobao.com/  
�������	  ELH    enlighten  sunny
STM32 ������ �⺯������	  */

/*
   STM32 �ڲ�RTC����  �� ʱ����ʾ
   STM32�ڲ�RTC���� ���ⲿDS1302����һ��  STM32���ڲ�ʱ���ǲ��ܴ洢 �����յȹ��ܵ�	 ֻ�ܴ洢32λ����ֵ
   ������Щ���ݶ�Ҫ�ú���ȥ����

   ��ʵ�����Ҫ���ܣ���ʼ��RTC���� ����ʾʱ��  ����ʱ��

*/

#include  "stm32f10x.h"
#include  "delay.h"
#include  "led.h"
#include  "tft.h"
#include  "key.h"
#include  "flash.h"
#include  "gui.h"
#include  "z24c02.h"
#include  "rtc.h"


int main(void)
 {
	  u8 time;				 //��ʱ����±�־
	  static u8  flag;		 //ָʾ����˸��־

	  delay_init();	    	 //��ʱ������ʼ��
	  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�	 	  
	  LED_Init();		  	 //��ʼ����LED���ӵ�Ӳ���ӿ�
	  KEY_Init();            //��ʼ������			
	  Lcd_Init();			 //LCD  ��ʼ��
	  SPI_Flash_Init();  	 //SPI FLASH ��ʼ��
	  AT24CXX_Init();        //IIC��ʼ��
	  TFT_CS(0);			 //��LCDƬѡʹ�� 
	  GUI_Clear(White);		   //��ɫ���� 

	  GUI_sprintf_hzstr16x(0,0,"SMT32-ZD  RTC TEST",White,Green1);


	  if(RTC_Init()==1)		//RTC��ʼ��	��ѭ���ȴ���ʼ���ɹ�
	   { 
	     GUI_sprintf_hzstr16x(60,100,"STM32-RTC Error!",White,Blue);
		 while(1);		
		}

	  GUI_sprintf_hzstr16x(60,80,"    -  -     ",Red,White);	   
	  GUI_sprintf_hzstr16x(60,102,"  :  :  ",Red,White);	


	while(1)
	{
	  if(time!=calendar.sec)
	   {
	     if(flag==0){flag=1;led(1);}		 //ָʾ����˸
		 else{flag=0;led(0);}

	   	 time=calendar.sec;
		 number(60,80,calendar.w_year,Red,White);		//��						  
		 number10(100,80,calendar.w_month,Red,White);	//��								  
		 number10(124,80,calendar.w_date,Red,White);	//��
		 number10(60,102,calendar.hour,Red,White);		//Сʱ							  
		 number10(84,102,calendar.min,Red,White);		//����							  
	   	 number10(108,102,calendar.sec,Red,White);		//��
			switch(calendar.week)
			{
				case 0:
					GUI_sprintf_hzstr16x(60,122,"Sunday   ",Blue,White);
					break;
				case 1:
					GUI_sprintf_hzstr16x(60,122,"Monday   ",Blue,White);
					break;
				case 2:
					GUI_sprintf_hzstr16x(60,122,"Tuesday  ",Blue,White);
					break;
				case 3:
					GUI_sprintf_hzstr16x(60,122,"Wednesday",Blue,White);
					break;
				case 4:
					GUI_sprintf_hzstr16x(60,122,"Thursday ",Blue,White);
					break;
				case 5:
					GUI_sprintf_hzstr16x(60,122,"Friday   ",Blue,White);
					break;
				case 6:
					GUI_sprintf_hzstr16x(60,122,"Saturday ",Blue,White);
					break;  
			}


		}
	
	}

}
	    





