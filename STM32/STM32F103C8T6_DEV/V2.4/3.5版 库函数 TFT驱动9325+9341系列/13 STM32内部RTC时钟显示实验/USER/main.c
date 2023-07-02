

/* http://zq281598585.taobao.com/  
启光电子	  ELH    enlighten  sunny
STM32 开发板 库函数部分	  */

/*
   STM32 内部RTC调用  及 时间显示
   STM32内部RTC功能 和外部DS1302并不一样  STM32的内部时钟是不能存储 年月日等功能的	 只能存储32位的秒值
   所以这些数据都要用函数去处理

   该实验的主要功能：初始化RTC功能 并显示时间  更新时间

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
	  u8 time;				 //秒时间更新标志
	  static u8  flag;		 //指示灯闪烁标志

	  delay_init();	    	 //延时函数初始化
	  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//设置NVIC中断分组2:2位抢占优先级，2位响应优先级	 	  
	  LED_Init();		  	 //初始化与LED连接的硬件接口
	  KEY_Init();            //初始化按键			
	  Lcd_Init();			 //LCD  初始化
	  SPI_Flash_Init();  	 //SPI FLASH 初始化
	  AT24CXX_Init();        //IIC初始化
	  TFT_CS(0);			 //打开LCD片选使能 
	  GUI_Clear(White);		   //白色清屏 

	  GUI_sprintf_hzstr16x(0,0,"SMT32-ZD  RTC TEST",White,Green1);


	  if(RTC_Init()==1)		//RTC初始化	死循环等待初始化成功
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
	     if(flag==0){flag=1;led(1);}		 //指示灯闪烁
		 else{flag=0;led(0);}

	   	 time=calendar.sec;
		 number(60,80,calendar.w_year,Red,White);		//年						  
		 number10(100,80,calendar.w_month,Red,White);	//月								  
		 number10(124,80,calendar.w_date,Red,White);	//日
		 number10(60,102,calendar.hour,Red,White);		//小时							  
		 number10(84,102,calendar.min,Red,White);		//分钟							  
	   	 number10(108,102,calendar.sec,Red,White);		//秒
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
	    





