

/* http://zq281598585.taobao.com/  
启光电子	  ELH    enlighten  sunny
STM32开发板 库函数部分	  */

/*
  STM32 紫电a  TF卡初始化及识别
  tf卡采用我们店TFT屏上的tf卡模块   
  tf卡模块 采用SPI1总线   CS片选IO为 PA4  

  TFT  驱动芯片为 ili9325	
  TFT用到的GPIO  PB为数据口	  CS PC.8    RS PC.9    WR PC.10     RD PA.15	  RES 采用系统复位

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




extern u8 SD_Type;			  //SD卡类型				

int main(void)
 {
 	  u32 sd_size;				  //临时变量

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
	  GUI_Clear(White);			  //白色清屏

	  GUI_sprintf_hzstr16x(0,0,"TF Card Init!",Black,White);
	  
	  GUI_sprintf_hzstr16x(0,40,"TF Card Type:",Blue,White);	  //卡类型
	  GUI_sprintf_hzstr16x(0,60,"TF Card Size:    Mb",Blue,White);	//卡容量
	
	  if(SD_Init()==0)GUI_sprintf_hzstr16x(0,20,"TF Card  ok",Black,White);	  //初始化TF卡
	  else GUI_sprintf_hzstr16x(0,20,"TF Card Error",Red,White);
	
	  sd_size=SD_GetCapacity();	  //计算SD卡容量
	
	  if(SD_Type==0x04)GUI_sprintf_hzstr16x(104,40,"SD_TYPE_V2",Blue,White);	   //0-2g
	  if(SD_Type==0x06)GUI_sprintf_hzstr16x(104,40,"SD_TYPE_V2HC",Blue,White);  //2-32g
	
	  number(104,60,sd_size>>20,Red,White);   //显示卡容量  1M=1024KB  1KB=1024B  1B=8bit	   2的20次方为1024x1024 也就是M
	  while(1);  

}
	    





