

/* http://zq281598585.taobao.com/  
启光电子	  ELH    enlighten  sunny
STM32 开发板 库函数部分	  */

/*
  STM32 TFT触摸屏实验
  采用的TFT为9325 9341等系列TFT
  	   用到的GPIO  PB为数据口	  CS PC.8    RS PC.9    WR PC.10     RD PA.15	  RES 采用系统复位

  触摸屏芯片采用XPT2046
  SPI1总线 和 XPT2046数据通讯
  SPI1  PA5 6 7   XPT2046 cs  PA11	   触摸判断IO  PA12 可以用中断 目前采用循环读取

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




					 //接收数组

int main(void)
 {
 
      struct TFT_Pointer Tp_pix;	        //定义触摸变量结构体
      u8 t; 

	  delay_init();	    	 //延时函数初始化	 	  
	  LED_Init();		  	 //初始化与LED连接的硬件接口
	  KEY_Init();            //初始化按键	
	  SPI1_Init();			 //初始化SPI1总线
	  SPI1_SetSpeed(SPI_BaudRatePrescaler_2);//设置为18M时钟,高速模式		
	  Lcd_Init();			 //LCD  初始化
	  SPI_Flash_Init();  	 // FLASH 初始化
	  XPT2046_Init();		 //触摸芯片XPT2046 io配置
	  AT24CXX_Init();        //IIC初始化



	  TFT_CS(0);			 //打开LCD片选使能 
	  GUI_Clear(Cyan);		   //白色清屏 
	  GUI_sprintf_hzstr16x(0,0,"STM32-ZD touch test",Blue,White);

	while(1)
	{
	    Tp_pix=TFT_Cm();	                            // 扫描触摸屏
	    if(Tp_pix.flag==1)                              //是否有触摸事件 发送 
	    { 
		 led(1);			//led响应
		 Address_set(Tp_pix.x,Tp_pix.y,Tp_pix.x+2,Tp_pix.y+2,Tp_pix.x,Tp_pix.y);			//3*3个点为一个单元点	
		 
		 for(t=0;t<9;t++)				
		  Lcd_Write_Data(Red);

		}
		 led(0);			//关掉LED

	 }

}
	    





