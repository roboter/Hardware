

/* http://zq281598585.taobao.com/  
启光电子	  ELH    enlighten  sunny
STM32开发板 库函数部分	  */

// 中断实验  通过外部中断线  到 按键 PA.0  PD.2上  	并配置为下降沿触发 具体设置在exti.c中
//			 按键按下则产生中断	 PA.0（S4）产生中断 控制板载LED亮   PD.2(S3)产生中断 控制板载LED灭
//			 并且串口 也将不停的打印数据 以表示程序正在运行




#include  "delay.h"
#include  "led.h"
#include  "key.h"
#include  "usart.h"
#include "exti.h"


int main(void)
   {

   	delay_init();	    	 //延时函数初始化
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//设置NVIC中断分组为组2  2:2位抢占优先级，2位响应优先级
	                                                //一旦定义 即不要轻易改变
	uart_init(9600);	    //串口初始化为9600  
	LED_Init();		  	    //初始化与LED连接的硬件接口
	KEY_Init();				//	按键端口初始化
	EXTIX_Init();		 	//外部中断初始化
   
 	while(1)
	{
		printf("ELH 启光电子\r\n");	
		delay_ms(1000);
	}

   }

