

/* http://zq281598585.taobao.com/  
启光电子	  ELH    enlighten  sunny
STM32 开发板 库函数部分	  */

/*
红外H1838 接收头 解码实验
红外接收头采用 PA3 IO口接收处理数据	  具体解法请参考原理图效果
按动遥控器按键时 TFT显示解码数据

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

	  delay_init();	    	 //延时函数初始化	 
	  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//设置NVIC中断分组2:2位抢占优先级，2位响应优先级	  
	  LED_Init();		  	 //初始化与LED连接的硬件接口
	  KEY_Init();            //初始化按键			
	  Lcd_Init();			 //LCD  初始化
	  SPI_Flash_Init();  	 //SPI FLASH 初始化

	  Remote_Init();			//红外接收初始化


	  TFT_CS(0);			 //打开LCD片选使能 
	  GUI_Clear(White);		 //清屏



	  GUI_Clear(White);		 //清屏

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





