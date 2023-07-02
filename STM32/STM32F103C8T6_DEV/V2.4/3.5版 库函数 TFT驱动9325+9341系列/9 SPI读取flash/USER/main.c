

/* http://zq281598585.taobao.com/  
启光电子	  ELH    enlighten  sunny
STM32F103RBT6 开发板 库函数部分	  */

/*SPI实验  本实验主要 开启片内SPI功能底层函数  调用库函数对SPI进行相应设置
  如果 背面板 增加了 flash芯片 （如 W25X16等） 就可以通过此程序  按键 向flash里写相应数据
  并将数据读取 显示到TFT上

  如果是第一次下载此程序 要先按S3 来进行数组数据的FLASH存储  然后在按S4 读取所存进去的数据

*/

#include  "stm32f10x.h"
#include  "delay.h"
#include  "led.h"
#include  "tft.h"
#include  "key.h"
#include  "flash.h"
#include  "gui.h"



const u8 TEXT_Buffer[]={"STM32-ZD SPI1 FLASH IS OK"};
#define SIZE sizeof(TEXT_Buffer)

//u8 scan[]={"STM32-ZD SPI1 FLASH IS OK"};	 //测试字符串
//u8 buffer[25];						 //接收数组

int main(void)
 {
 

	 u8 datatemp[SIZE];

	  delay_init();	    	 //延时函数初始化	 	  
	  LED_Init();		  	 //初始化与LED连接的硬件接口
	  KEY_Init();            //初始化按键			
	  Lcd_Init();			 //LCD  初始化
	  SPI_Flash_Init();  	 //SPI FLASH 初始化
	  TFT_CS(0);			 //打开LCD片选使能 
	  GUI_Clear(White);		//清屏


	 while(SPI_Flash_ReadID()!=W25Q16)							//检测不到W25Q64
	  {
		GUI_sprintf_hzstr16x(20,150,"25X16 Check Failed!",Blue,White);
		delay_ms(500);
		GUI_sprintf_hzstr16x(20,180,"Please Check!      ",Blue,White);
		delay_ms(500);
	  }

	 GUI_sprintf_hzstr16x(60,20,"SPI-25X16 TEST",White,Red);

	 GUI_sprintf_hzstr16x(50,60,"S3 for save DATA",Black,White);
	 GUI_sprintf_hzstr16x(50,80,"S4 for read DATA",Black,White);

	 while(1)
	 {
		if(KEY1==0)																   //PA0 
		 {
		 delay_ms(150);	//去抖
		 if(KEY1==0)
		  {
			 GUI_Clear(White);		//清屏
			 GUI_sprintf_hzstr16x(20,60,"Start Write W25X16....",Blue,White);
			 SPI_Flash_Write((u8*)TEXT_Buffer,100,SIZE);						//想flash写 已经准备好的数据
			 GUI_sprintf_hzstr16x(20,60,"W25X16 Write Finished!",Blue,White);
		  }
		 }

		if(KEY0==1)																  //PD2
		{
		 delay_ms(150);	//去抖
		 if(KEY0==1)
		  {
		     GUI_Clear(White);		//清屏
			 GUI_sprintf_hzstr16x(20,60,"Start Read W25X16.... ",Red,White);
			 SPI_Flash_Read(datatemp,100,SIZE);								//读取 存入在flash里的数据
			 GUI_sprintf_hzstr16x(20,60,"The Data Readed Is:  ",Red,White);
			 GUI_sprintf_hzstr16x(10,76,datatemp,Blue,White);					//将数据显示出来		  		  
		  }

		 }
	 }							  


 }





