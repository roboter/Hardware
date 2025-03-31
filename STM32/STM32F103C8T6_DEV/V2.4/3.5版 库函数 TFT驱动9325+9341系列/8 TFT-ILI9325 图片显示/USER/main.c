

/* http://zq281598585.taobao.com/  
启光电子	  ELH    enlighten  sunny
STM32 开发板 库函数部分	  */

/*在指定区域内显示一个180*240 的图片	（犹豫程序空间有限 所以不能全屏显示）
  程序中 用到的TFT 为 我们店的 2.4寸TFT  驱动芯片为 ili9325	
  TFT用到的GPIO  PB为数据口	  CS PC.8    RS PC.9    WR PC.10     RD PA.15	  RES 采用系统复位
  此函数 用寄存器方式配置GPIO  在TFT的数据 命令脚配置上用的是寄存器  这样能大幅度提高输出速度
*/



#include  "delay.h"
#include  "led.h"
#include  "tft.h"
#include  "picture.h"	   //为 生成的图片数据




int main(void)
 {
	 unsigned int i;
	  delay_init();	    	 //延时函数初始化	  
	  LED_Init();		  	 //初始化与LED连接的硬件接口			
	  Lcd_Init();			 //LCD  初始化
	  TFT_CS(0);			 //打开LCD片选使能 

	  GUI_Clear(Green1);		//清屏
	
	  
	  Address_set(30,40,209,279,30,40);		   //设置显示范围
	  for(i=0;i<43200;i++)				   //显示以存好的图片数据
	    {
		 Lcd_Write_Data((gImage_t[i*2+1]<<8)+(gImage_t[i*2]));
		}
	  
	  while(1);							   //将程序停在这里


 }

