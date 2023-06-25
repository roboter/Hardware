

/* http://zq281598585.taobao.com/  
启光电子	  ELH    enlighten  sunny
STM32 开发板 库函数部分	  */

//LED闪烁灯实验  板子上的PA1口 控制LED  0亮 1灭



#include  "delay.h"
#include  "led.h"


int main(void)
   {

   	delay_init();	    	 //延时函数初始化	  
	LED_Init();		  	//初始化与LED连接的硬件接口
   
   while(1)
   {
  		GPIO_ResetBits(GPIOA,GPIO_Pin_1);			   //给PC13置0	
		delay_ms(800);
		GPIO_SetBits(GPIOA,GPIO_Pin_1);			   //给PC13置1
		delay_ms(800);

   }
   }

