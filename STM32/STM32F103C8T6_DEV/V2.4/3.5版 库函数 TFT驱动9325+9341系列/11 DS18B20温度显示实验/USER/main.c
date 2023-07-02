

/* http://zq281598585.taobao.com/  
启光电子	  ELH    enlighten  sunny
STM32 开发板 库函数部分	  */

/*
   DS18B20   温度读取实验
   所用的IO采用  STM32 PA13  由于PA13也是 SWD接口  所以此程序 会影响SWD仿真
   所以 在TFT 初始化函数里 将所有仿真功能进行禁用
   GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE); //JTAG and SWD 全部禁用

   如果不做以上步骤 将无法进入 DS18b20初始化

   如果考虑仿真问题 就根据自己的需要选择其他IO

*/

#include  "stm32f10x.h"
#include  "delay.h"
#include  "led.h"
#include  "tft.h"
#include  "key.h"
#include  "flash.h"
#include  "gui.h"
#include  "ds18b20.h"



int main(void)
 {
 	  short temperature;	 //温度变量
	  delay_init();	    	 //延时函数初始化	 	  
	  LED_Init();		  	 //初始化与LED连接的硬件接口
	  KEY_Init();            //初始化按键			
	  Lcd_Init();			 //LCD  初始化
	  SPI_Flash_Init();  	 //SPI FLASH 初始化
	  TFT_CS(0);			 //打开LCD片选使能 
	  GUI_Clear(White);		 //清屏

	  while(ds18b20_init())
	  {
	   GUI_sprintf_hzstr16x(0,20,"DS18B20  Error",Red,White);
	   delay_ms(300);
	   GUI_sprintf_hzstr16x(0,20,"              ",Red,White);
	   delay_ms(300);	  
	  }

	  GUI_sprintf_hzstr16x(0,20,"DS18B20  ok",Black,White);

	  delay_ms(300);

	  GUI_Clear(White);		 //清屏

      GUI_sprintf_hzstr16x(0,0,"DS18B20 read temperature",Black,White);
	  GUI_sprintf_hzstr16x(0,30,"The temperature",Blue,White);
	  GUI_sprintf_hzstr16x(120,30,":   . ",Red,White);


	  while(1)
	  {
		 temperature=read_temp();										   //读取温度值
	     if(temperature<0) GUI_sprintf_char(28,30,'-',Red,White,0);
	     else GUI_sprintf_char(128,30,' ',Red,White,0);
	     GUI_sprintf_char(136,30,temperature/100%10+'0',Red,White,0);	   //显示当前温度值
	     GUI_sprintf_char(144,30,temperature/10%10+'0',Red,White,0);
	     GUI_sprintf_char(160,30,temperature%10+'0',Red,White,0);
	   }						  


 }





