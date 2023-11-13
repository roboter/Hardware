

/* http://zq281598585.taobao.com/  
启光电子	  ELH    enlighten  sunny
STM32开发板 库函数部分	  */

//按键控制LED灯实验  
//板子上的按键 分别是S3 为PD2  S4 为PA0
//此实验 通过S4控制 板子上的LED灭  S3控制LED亮



#include  "delay.h"
#include  "led.h"
#include  "key.h"


int main(void)
   {

   	delay_init();	     //延时函数初始化	  
	LED_Init();		  	//初始化与LED连接的硬件接口
	KEY_Init();         //初始化按键
   while(1)
   {
 
        if(KEY0==1)
		  {
		    GPIO_ResetBits(GPIOA,GPIO_Pin_1);		  //给PA1置0
		  }
		if(KEY1==0)
		  {
		    GPIO_SetBits(GPIOA,GPIO_Pin_1);		  //给PA1置1
		  
		  }


   }
   }

