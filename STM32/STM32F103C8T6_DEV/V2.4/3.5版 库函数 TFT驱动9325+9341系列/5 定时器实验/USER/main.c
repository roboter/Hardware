

/* http://zq281598585.taobao.com/  
启光电子	  ELH    enlighten  sunny
STM32 开发板 库函数部分	  */


//定时器2  溢出中断后  进入中断 在中断中跳转 PA1外部LED控制IO



#include  "delay.h"
#include  "led.h"
#include "timer.h"


int main(void)
   {

   	delay_init();	    	 //延时函数初始化
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//设置NVIC中断分组2:2位抢占优先级，2位响应优先级	  
	LED_Init();		  	//初始化与LED连接的硬件接口
	TIM2_Int_Init(9999,7199);//20Khz的计数频率  1秒翻转一次
   
   while(1)	;

   }

