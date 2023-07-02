

/* http://zq281598585.taobao.com/  
启光电子	  ELH    enlighten  sunny
STM32 开发板 库函数部分	  */

/*
  I2C总线测试外部24c02 eeprom芯片
  i2c总线采用IO口模拟  PC11 SDA  PC12 SCL
  S4 按键写数据  写字符数据  A  到地址0位置
  S3 按键读取数据  将地址1的数据读取出来

*/

#include  "stm32f10x.h"
#include  "delay.h"
#include  "led.h"
#include  "tft.h"
#include  "key.h"
#include  "flash.h"
#include  "gui.h"
#include  "z24c02.h"



					 //接收数组

int main(void)
 {
 
// 	 u8 pd;


	  delay_init();	    	 //延时函数初始化	 	  
	  LED_Init();		  	 //初始化与LED连接的硬件接口
	  KEY_Init();            //初始化按键			
	  Lcd_Init();			 //LCD  初始化
	  SPI_Flash_Init();  	 //SPI FLASH 初始化
	  AT24CXX_Init();        //IIC初始化
	  TFT_CS(0);			 //打开LCD片选使能 
	  GUI_Clear(White);		   //白色清屏 

  GUI_sprintf_hzstr16x(10,30,"启光科技",Black,White);
  GUI_sprintf_hzstr16x(10,50,"welcome to MCU world!",Blue,White);
  GUI_sprintf_hzstr16x(10,70,"STM32F103RBT6",White,Red);
  GUI_sprintf_hzstr16x(10,90,"落霞与孤鹜齐飞，",Red3,White);
  GUI_sprintf_hzstr16x(10,110,"秋水共长天一色。",Red3,White);

  while(1);  

}
	    





