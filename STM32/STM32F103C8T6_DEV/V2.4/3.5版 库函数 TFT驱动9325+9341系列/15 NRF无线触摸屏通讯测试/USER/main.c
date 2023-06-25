

/* http://zq281598585.taobao.com/  
启光电子	  ELH    enlighten  sunny
STM32 开发板 库函数部分	  */

/*
  STM32 TFT触摸屏实验
  采用的TFT为9325TFT
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
#include  "nrf24l01.h"




					 //接收数组

int main(void)
 {
 
      struct TFT_Pointer Tp_pix;	        //定义触摸变量结构体
      u8 t; 
	  u8 mode=0;
	  u8 Buf[3];						 //缓存数组
	  u16 pix,piy;						 //临时变量	   用于处理接收到的数据

	  delay_init();	    	 //延时函数初始化	 	  
	  LED_Init();		  	 //初始化与LED连接的硬件接口
	  KEY_Init();            //初始化按键	
	  SPI1_Init();			 //初始化SPI1总线
	  SPI1_SetSpeed(SPI_BaudRatePrescaler_2);//设置为18M时钟,高速模式		
	  Lcd_Init();			 //LCD  初始化
	  SPI_Flash_Init();  	 // FLASH 初始化
	  XPT2046_Init();		 //触摸芯片XPT2046 io配置
	  AT24CXX_Init();        //IIC初始化

	  NRF_IO_Init();         //NRF 相应IO配置 初始化

	  TFT_CS(0);			 //打开LCD片选使能 
	  GUI_Clear(White);		   //白色清屏 




	  GUI_sprintf_hzstr16x(0,0,"NRF24L01 Init",White,Black);

      while(NRF24L01_Check())		//检测NRF无线模块是否在线 同时配置其spi总线速度	 为9M
  	  {
		GUI_sprintf_hzstr16x(0,20,"NO NRF24L01!",Red,White);
		delay_ms(400);
		GUI_sprintf_hzstr16x(0,20,"            ",Red,White);
		delay_ms(400);

	  }

	  GUI_sprintf_hzstr16x(0,20,"NRF24L01 is ok...",Blue,White);
	  delay_ms(400);
		

	  GUI_Clear(White);		   //白色清屏

	  GUI_sprintf_hzstr16x(0,0,"STM32-ZD NRF24L01 test",Blue,White);


	  GUI_sprintf_hzstr16x(0,30,"S4: NRF for Send",Black,White);
	  GUI_sprintf_hzstr16x(0,50,"S3: NRF for Receive",Black,White);


	while(1)
	{

	   if(KEY0==1)		     //S4  设置为发射模式
	   {
		delay_ms(100);
		if(KEY0==1)
		 {
		   mode=1;
		   break;
		 }
	   }
	   if(KEY1==0)		     //S3  设置为接收模式
	   {
		delay_ms(100);
		if(KEY1==0)
		 {
		   mode=2;
		   break;
		 }
	   }

	 }
	  if(mode==1)			//发送模式
	  {
	   GUI_Clear(Black);
	   GUI_sprintf_hzstr16x(0,0,"NRF24l01 Send",Yellow,Black);
	   RX_TX_Mode(1);			 //发送模式初始化

	   	while(1)
		 {	
	       Tp_pix=TFT_Cm();	                            // 扫描触摸屏
	       if(Tp_pix.flag==1)                              //是否有触摸事件 发生 
			{
																				//设定画图位置 
				Address_set(Tp_pix.x,Tp_pix.y,Tp_pix.x+2,Tp_pix.y+2,Tp_pix.x,Tp_pix.y);			//3*3个点为一个单元点	
			    for(t=0;t<9;t++)				
				 Lcd_Write_Data(White);
		
				
				Buf[0]= Tp_pix.x;                               //将当前触摸屏位置存入数组中 
				Buf[2]= Tp_pix.y;
				Buf[1]= Tp_pix.y>>8;
		
		        nRF24L01_TxPacket(Buf);	//发送数据	
		        delay_ms(10);	

		    }	  	  
	      }
	   }

	  if(mode==2)			  //接收模式
	  {
	   GUI_Clear(Black);
	   GUI_sprintf_hzstr16x(0,0,"NRF24l01 Receive",Yellow,Black);
	   RX_TX_Mode(0);	           //接收模式初始化

	   	while(1)
		 {	
		   led(0);								   //关掉指示灯
			 if(nRF24L01_RxPacket(Buf)==0)		   //采集数据 
			  {				
					  
				   pix=Buf[0];			   //处理数据 屏幕分辨率为320X240 一字节最多能装255  320部分 大于一个字节所以分两字节装数据
				   piy=(Buf[1]<<8)+Buf[2];

		           Address_set(pix,piy,pix+2,piy+2,pix,piy);			//3*3个点为一个单元点
				   for(t=0;t<9;t++)				
					Lcd_Write_Data(White);										
		
				   led(1);									   //指示灯判断是否接收到数据
			       delay_ms(10);								//小延时
		       }
 	  
	      }
	   }

}
















