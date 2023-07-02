

/* http://zq281598585.taobao.com/  
启光电子	  ELH    enlighten  sunny
STM32开发板 库函数部分	  */

/*

OLED显示效果实验

采用本店铺OLED  OLED屏直接插到TFT接口的前7个口位置即可
oled IO使用说明			 注：OLED供电一定要3.3V
D0 SCLK  PC8
D1 SDIN  PC9
RES      PC10
DC       PA15
CS       PB8

*/

#include  "delay.h"
#include  "led.h"
#include "oled.h"


int main(void)
   {

   	delay_init();	    	 //延时函数初始化	  
	LED_Init();		  	//初始化与LED连接的硬件接口

 	OLED_Init();			//初始化OLED  

	OLED_Clear();   

 		OLED_ShowCHinese(0,0,0);//启光电子科技
		OLED_ShowCHinese(18,0,1);
		OLED_ShowCHinese(36,0,2);
		OLED_ShowCHinese(54,0,3);
		OLED_ShowCHinese(72,0,4);
		OLED_ShowCHinese(90,0,5);

	 
		OLED_ShowString(0,2,"1.3' OLED TEST");
	//	OLED_ShowString(8,2,"ZHONGJINGYUAN");  
	 	OLED_ShowString(20,4,"2015/10/13");  
		OLED_ShowString(0,6,"ASCII:");  
		OLED_ShowString(63,6,"CODE:");

   
   while(1)	
   {
  		GPIO_ResetBits(GPIOA,GPIO_Pin_1);			   //给PC13置0	
		delay_ms(800);
		GPIO_SetBits(GPIOA,GPIO_Pin_1);			   //给PC13置1
		delay_ms(800);

   }
   }

