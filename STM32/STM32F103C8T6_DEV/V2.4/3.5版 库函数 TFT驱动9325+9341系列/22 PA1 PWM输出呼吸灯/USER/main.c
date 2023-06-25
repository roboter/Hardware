

/* http://zq281598585.taobao.com/  
启光电子	  ELH    enlighten  sunny
STM32 开发板 库函数部分	  */


//定时器2  对PA1口进行PWM输出，输出频率为8KHz（频率可根据函数调节）
//PA1口上接着LED灯，PWM在8k下 从0到350 再从350到0 来回变化  会产生会产生呼吸灯效果



#include  "delay.h"
#include  "led.h"
#include "timer.h"


int main(void)
   {
 	u16 led_pwmval=0;
	u8 point=1;

   	delay_init();	    	 //延时函数初始化
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//设置NVIC中断分组2:2位抢占优先级，2位响应优先级	  
	LED_Init();		  	//初始化与LED连接的硬件接口
   
  	TIM2_PWM_Init(899,0);	 //不分频。PWM频率=72000/900=8Khz

   	while(1)
	{
 		delay_ms(10);	 
		if(point)led_pwmval+=1;
		else led_pwmval-=1;

 		if(led_pwmval>350)point=0;
		if(led_pwmval==0)point=1;										 
		TIM_SetCompare2(TIM2,led_pwmval);		   
	}


   }

