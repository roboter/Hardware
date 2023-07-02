

/* http://zq281598585.taobao.com/  
启光电子	  ELH    enlighten  sunny

OV7670模块 STM32函数

选用STM32芯片   
TFT驱动IC可支持 9325 9320 9328 及9341

  程序中 用到的TFT 为 我们店的 2.4寸TFT  驱动芯片为 R61505V	
  TFT用到的GPIO  PB为数据口	PC.6  CS   PC.7  RS	  PC.8  WR   PC.9  RD	PC.10 RES
  此函数 用寄存器方式配置GPIO  在TFT的数据 命令脚配置上用的是寄存器  这样能大幅度提高输出速度
 
摄像头方面
摄像头 数据口 为PA口  AO-A7
SCL    PC11
SDA    PC12
OE	   PC3		 //片选信号(OE)
WRST   PC4		 //写指针复位
RRST   PC2		 //读指针复位
RCLK   PC1		 //读数据时钟
WEN	   PC5		 //写入FIFO使能
VSY	   PD2  	 //同步信号检测IO

整个程序流程介绍

初始化TFT   
初始化ov7670  ov7670是通过SCCB 初始化的  即 SCL 和SDA就可以初始化OV7670  SDA SCL类似于I2C效果
              所以在调模块前 一定要确定OV7670是否已经初始化
开启中断 判断帧数据是否接收
死循环 读取并显示 摄像数据

	   
*/

#include  "stm32f10x.h"
#include  "delay.h"
#include  "led.h"
#include  "tft.h"
#include  "led.h"
#include "ov7670.h"
#include  "gui.h"




extern u8 ov_sta;	//帧次数 置位标志位


//更新LCD显示
void camera_refresh(void)
{
	u32 j;
 	u16 color;
		 
	if(ov_sta==2)				//判断缓存区是否存好摄像数据
	{
	  	 
		OV7670_RRST_0;				//开始复位读指针 
		OV7670_RCK_0;
		OV7670_RCK_1;
		OV7670_RCK_0;		
		OV7670_RRST_1;				//复位读指针结束 
		OV7670_RCK_1;  


		TFT_RS_1;		 //写数据线拉高		为提高写入速度

		//此用法 是将 下面写数据的步骤完全拆开  主要是为了提高显示速度  （下面注释部分为参考部分）
                     
		for(j=0;j<76800;j++)			   //分辨率为240x320   每个颜色点要两个字节 所以 240x320x2=76800  次
		{
		  	

			OV7670_RCK_0;				 //每一次时钟跳变 读一次数据
			color=GPIOC->IDR&0XFF;	//读数据   读取颜色高字节数据
			OV7670_RCK_1; 
			color<<=8;  				 //左移8位  将高字节移到高8位  为接收低8位字节做准备
			OV7670_RCK_0;
			color|=GPIOC->IDR&0XFF;	//读数据   读取颜色低字节数据 并转化为16位 565 颜色数据
			OV7670_RCK_1; 

  		 // TFT_DATA(color);  //赋值

		    GPIOB->ODR=color;			   //对TFT并口快速写数据

//		     GPIOB->BRR=GPIO_Pin_All;	   //清寄存器数据
//             GPIOB->BSRR=color;			   //将采集的颜色值给PB口寄存器 

		    TFT_WR_0;								      //开始写入
            TFT_WR_1;
		 // Lcd_Write_Data(color);

		}   							 
		EXTI_ClearITPendingBit(EXTI_Line2);  //清除LINE8上的中断标志位
		ov_sta=0;					//开始下一次采集
	} 
}



int main(void)
 {
 u8 lightmode=0,saturation=2,brightness=2,contrast=2;
 u8 effect=0;

	  delay_init();	    	 //延时函数初始化
	  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	  LED_Init();		  	 //初始化与LED连接的硬件接口			
	  Lcd_Init();			 //LCD  初始化
	  TFT_CS(0);			 //打开LCD片选使能 
      GUI_Clear(White);		//清屏

	  	while(OV7670_Init())//初始化OV7670
	{
		GUI_sprintf_hzstr16x(20,150,"OV7670 Error!!",Blue,White);
		delay_ms(200);
	    GUI_sprintf_hzstr16x(20,150,"              ",Blue,White);
		delay_ms(200);
	}

	  GUI_Clear(Red);		//清屏		初始化成功后 红色清屏


//	 delay_ms(1500);

	 
	 //摄像头 参数设置  屏蔽后为默认效果	 	   
	OV7670_Light_Mode(lightmode);
	OV7670_Color_Saturation(saturation);
	OV7670_Brightness(brightness);
	OV7670_Contrast(contrast);
 	OV7670_Special_Effects(effect);	 

	EXTI2_Init();					   //初始化中断线
	OV7670_Window_Set(10,174,240,320);	//设置窗口
	OV7670_CS=0;					   //使能摄像头片选

	 TFT_SCAN(5);   //设置TFT扫描方向 为从下到上 从右到左
	 //这里说明一下  摄像头的成像扫描是 从上到下 从左到右

	                                         //其他屏设置方法 具体要看手册

	 Address_set(0,0,239,319,0,0);		   //9325 设置显示范围		全屏显示


//	 Address_set(0,0,319,239,0,0);		   //9341 由于扫描方向改变 9341的原点也会变 所以和其他93系列不一样

	  while(1)							   //死循环显示 摄像数据
	  {
	  camera_refresh();
	  }

						 

 }

