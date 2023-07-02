

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
 
 	 u8 pd;


	  delay_init();	    	 //延时函数初始化	 	  
	  LED_Init();		  	 //初始化与LED连接的硬件接口
	  KEY_Init();            //初始化按键			
	  Lcd_Init();			 //LCD  初始化
	  SPI_Flash_Init();  	 //SPI FLASH 初始化
	  AT24CXX_Init();        //IIC初始化
	  TFT_CS(0);			 //打开LCD片选使能 
	  GUI_Clear(White);		   //白色清屏 
	  GUI_sprintf_hzstr16x(0,0,"24C02 read and write",White,Blue);
	  GUI_sprintf_hzstr16x(0,20,"write:S4",Black,White);
	  GUI_sprintf_hzstr16x(0,40,"read:S3",Black,White);
	  GUI_sprintf_hzstr16x(0,60,"result:",Black,White);


	while(1)
	{
	 if(KEY1==0)		//PD2 	 读取E2 0地址位 的一个字节 到pd中
	 {
	   delay_ms(100);	//去抖
	   if(KEY1==0)	 
		{
		  led(1);    	//点亮LED
          pd=AT24C_Rcvone(0);    //选择要读取的地址  然后将读取的数据存入变量pd中 1读出1个字节到存入的指定变量 
		  GUI_sprintf_char(56,60,pd,Red,White,0); //显示读取出来的值    		
		}
	  }
		 //========================IIC 保存
	  if(KEY0==1)		//PA0
	  {
		delay_ms(100);	//去抖
		if(KEY0==1)
		 {
 		   led(0);			    //指示灯 灭 提示 保存成功
	  	   pd='A';		        //将预存储Count1中的值给变量pd
		   AT24C_Sendone(0,pd);	//将pd的值存入  0地址位置 存入量为1字节
		 }

	   }
	  
	 }

}
	    





