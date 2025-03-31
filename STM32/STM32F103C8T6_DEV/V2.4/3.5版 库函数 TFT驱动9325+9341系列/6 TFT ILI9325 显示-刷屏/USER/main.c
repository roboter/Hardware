

/* http://zq281598585.taobao.com/  
启光电子	  ELH    enlighten  sunny
STM32 开发板 库函数部分	  */

/*此程序 为显示TFT刷颜色程序

  程序中 用到的TFT 为 我们店的 2.4寸TFT  驱动芯片可支持  ili9325   9328  9320  9341 	
  TFT用到的GPIO  PB为数据口	  CS PC.8    RS PC.9    WR PC.10     RD PA.15	  RES 采用系统复位
  此函数 用寄存器方式配置GPIO  在TFT的数据 命令脚配置上用的是寄存器  这样能大幅度提高输出速度

*/


#include  "delay.h"
#include  "led.h"
#include  "tft.h"



int main(void)
 {
	  delay_init();	    	 //延时函数初始化	  
	  LED_Init();		  	 //初始化与LED连接的硬件接口			
	  Lcd_Init();			 //LCD  初始化
	  TFT_CS(0);			 //打开LCD片选使能 

   while(1)
   {	 	
	GUI_Clear(Red);
	led(1); //点亮LED
	delay_ms(300);
	GUI_Clear(Yellow);
	delay_ms(300);
	GUI_Clear(Green);
	delay_ms(300);
	GUI_Clear(Blue);
	led(0); //关掉LED
	delay_ms(300);
	GUI_Clear(Black);
	delay_ms(300);
	GUI_Clear(window);
	delay_ms(300);

   }
 }

